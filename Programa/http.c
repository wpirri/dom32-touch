/***************************************************************************
    Copyright (C) 2020   Walter Pirri

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/
#define _IN_HTTP_C_
#include "http.h"
#undef _IN_HTTP_C_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "wifi.h"
#include "config.h"
#include "log.h"
#include "sd/fsio.h"
#include "control.h"
#include "strfunc.h"
#include "beep.h"

#define DOWNLOAD_TEMP_FILE_NAME "download.tmp"

const char xml_200[] =      "HTTP/1.1 200 OK\r\nConnection: close\r\n"
                            "Content-Type: text/xml\r\n\r\n";
const char http_200[] =     "HTTP/1.1 200 OK\r\n"
                            "Connection: close\r\n"
                            "Content-Type: text/html\r\n"
                            "Cache-Control: no-cache\r\n\r\n";
const char http_404[] =     "HTTP/1.1 404 Not found\r\n"
                            "Connection: close\r\n\r\n"
                            "404: File not found\r\n";
/* POST
 * 1.- %s: URI
 * 2.- %s: Host
 * 3.- %d: Content-Length
 * 4.- %s: datos
 */
const char http_post[] =    "POST %s HTTP/1.1\r\n"
                            "Host: %s\r\n"
                            "Connection: keep-alive\r\n"
                            "Content-Length: %d\r\n"
                            "User-Agent: Dom32io/1.00 (Microchip;PIC32)\r\n"
                            "Accept: text/html,text/xml\r\n"
                            "Content-Type: application/x-www-form-urlencoded\r\n\r\n%s";
/*
 * GET
 * 1.- %s: URI
 * 2.- %s: Host
 */
const char http_get[] =     "GET %s HTTP/1.1\r\n"
                            "Host: %s\r\n"
                            "Connection: close\r\n"
                            "User-Agent: Dom32io/1.00 (Microchip;PIC32)\r\n"
                            "Accept: text/html,text/xml\r\n\r\n";

unsigned int http_process_tmp_file;
char http_process_tmp_file_to_name[FILE_NAME_SIZE+1];

int ReadLine(char *buffer, size_t max_len, FSFILE *fs);

unsigned int g_download_file_count;

int HTTPGetFile(const char* filename, const char* params)
{
    char tmp_uri[MAX_HTTP_URI+1];
    char tmp_rqst[MAX_HTTP_DATA+1];

    if( !filename ) return (-1);
    if( !g_wifi_info.status.flag_sd_ok) return (-1);

    Log("[HTTPGetFile] Solicitando archivo %s.", filename);
    
    if(params)
    {
        snprintf(tmp_uri, MAX_HTTP_URI, "%s?%s", filename, params);
    }
    else
    {
        strncpy(tmp_uri, filename, MAX_HTTP_URI);
    }
    /*
     * GET
     * 1.- %s: URI
     * 2.- %s: Host
     */
    snprintf(tmp_rqst, MAX_HTTP_DATA, http_get,
             tmp_uri,
             g_wifi_host);
    if(HTTPAddOutput(tmp_uri, true, tmp_rqst, 250) <= 0)
    {
        /* No fue posible enviar */
        return 0;
    }
    return strlen(tmp_rqst);
}

int HTTPInitTmpFile(const char* buffer, int len)
{
    FSFILE* f;
    int rc = (-1);

    if( !http_buffer_output.download) return (-1);

    Log("[HTTPInitTmpFile] %-.20s (%d)", buffer, len);
    f = FSfopen(DOWNLOAD_TEMP_FILE_NAME, FS_WRITE);
    if(f)
    {
        rc = FSfwrite(buffer, 1, len, f);
        FSfclose(f);
    }
    
    if(len < WIFI_READ_LINE_BUFFER_LEN)
    {
        /* Es un archivo chico */
        /* Procesar archivo temporal */
        http_process_tmp_file = 50;
        strncpy(http_process_tmp_file_to_name, http_buffer_output.filename, FILE_NAME_SIZE);
        g_end_download = true;
    }
    
    return rc;
}

int HTTPAddTmpFile(const char* buffer, int len)
{
    FSFILE* f;
    int rc = (-1);

    Log("[HTTPAddTmpFile] %-.20s (%d)", buffer, len);
    if( !http_buffer_output.download)
    {
        Log("[HTTPAddTmpFile] ERROR: Download no iniciado");
        return (-1);
    }
    
    f = FSfopen(DOWNLOAD_TEMP_FILE_NAME, FS_APPEND);
    if(f)
    {
        rc = FSfwrite(buffer, 1, len, f);
        FSfclose(f);
    }
    return rc;
}

int HTTPEndTmpFile(const char* filename, const char* buffer, int len)
{
    int rc = 0;

    Log("[HTTPEndTmpFile] %-.20s (%d) -> %s", buffer, len, filename);
    if(len)
    {
        rc = HTTPAddTmpFile(buffer, len);
    }
    /* Procesar archivo temporal */
    http_process_tmp_file = 50;
    strncpy(http_process_tmp_file_to_name, filename, FILE_NAME_SIZE);
    g_end_download = true;
    return rc;
}

/*
 Sirve solo para archivos de texto
 */
void HTTPProcessTmpFile(const char* tmpname, const char* filename)
{
    char buffer[256];
    char*p;
    char*p_ipd_len;
    int len;
    int ipd_len;
    FSFILE* fi;
    FSFILE* fo;
    bool descartar;

    Log("[HTTPProcessTmpFile] %s -> %s", tmpname, filename);
    fi = FSfopen(tmpname, FS_READ);
    if(fi)
    {
        fo = FSfopen(filename, FS_WRITE);
        if(fo)
        {
            ipd_len = 0;
            descartar = TRUE;
            while( (len = ReadLine(buffer, 255, fi)) > 0 )
            {
                CLRWDT();
                
                buffer[len] = 0;
                
                if( len == 2 && buffer[0] == 0x0d && buffer[1] == 0x0a )
                {
                    /* Descarto todo hasta el final de la cabecera HTTP */
                    descartar = FALSE;
                    /* Descarto todo lo que esté fuera del bloque +IPD */
                    if(ipd_len > len) ipd_len -= len;
                    else ipd_len = 0;
                }
                else if(ipd_len)
                {
                    if( !descartar)
                    {
                        p = &buffer[0];
                        FSfwrite(p, 1, (ipd_len > len)?len:ipd_len, fo);
                    }
                    /* Descarto todo lo que esté fuera del bloque +IPD */
                    if(ipd_len > len) ipd_len -= len;
                    else ipd_len = 0;
                }
                else if( buffer[0] == '+' &&
                         buffer[1] == 'I' &&
                         buffer[2] == 'P' &&
                         buffer[3] == 'D'  )
                {
                    /* Comienzo de in bloque +IPD,0,1460: */
                    p = &buffer[0];
                    /* Salteo la primer coma */
                    while(*p != ',') { p++; len--; }
                    p++; len--;
                    /* Salteo la segunda coma coma */
                    while(*p != ',') { p++; len--; }
                    p++; len--;
                    /*  */
                    p_ipd_len = p;
                    /* Voy hasta el fin de la cabecera +IPD */
                    while(*p != ':') { p++; len--; }
                    *p = 0;
                    ipd_len = atoi(p_ipd_len);
                    p++; len--;
                    /*   Estoy aca: v
                     *  +IPD,0,1460:___ */
                    if( !descartar)
                    {
                        /* Escribo el resto de la linea */
                        FSfwrite(p, 1, (ipd_len > len)?len:ipd_len, fo);
                    }
                    /* Descarto todo lo que esté fuera del bloque +IPD */
                    if(ipd_len > len) ipd_len -= len;
                    else ipd_len = 0;
                }
            }                
            FSfclose(fo);
        }
        FSfclose(fi);
        Beeps(3);
    }        
}

int ReadLine(char *buffer, size_t max_len, FSFILE *fs)
{
    int len = 0;

    while(FSfread(buffer, 1, 1, fs) && len < max_len)
    {
        len++;
        if(*buffer == 0x0a) break;
        buffer++;
    }
    return len;
}

int Convert2CharToHex(const char* h)
{
    int h1, h2;
    
    if( (*h) >= '0' && (*h) <= '9' )
    {
        h1 = ((*h)-'0');
    }
    else if( (*h) >= 'A' && (*h) <= 'F' )
    {
        h1 = ((*h)-'A'+10);
    }
    else if( (*h) >= 'a' && (*h) <= 'f' )
    {
        h1 = ((*h)-'a'+10);
    }
    else
    {
        h1 = 0;
    }
    h++;
    if( (*h) >= '0' && (*h) <= '9' )
    {
        h2 = ((*h)-'0');
    }
    else if( (*h) >= 'A' && (*h) <= 'F' )
    {
        h2 = ((*h)-'A'+10);
    }
    else if( (*h) >= 'a' && (*h) <= 'f' )
    {
        h2 = ((*h)-'a'+10);
    }
    else
    {
        h2 = 0;
    }

    return ((h1*16)+h2);
}

int HttpDecodeFormData(char* out, const char* in, unsigned int max_out)
{
    int len = 0;
    
    Log("HttpDecodeFormData");

    if(!in || !out) return (-1);
    
    while(*in)
    {
        if(*in == 0x25) /* % */
        {
            in++;
            *out = (unsigned char)Convert2CharToHex(in);
            in += 2;
        }
        else
        {
            *out = *in;
            in++;
        }
        out++;
        len++;
        if(len >= max_out) break;
    }
    *out = 0;
    return (len < max_out)?len:(-1);
}

int HttpGetRequest(const char *buffer, char *request, int max_len)
{
	int rc = 0;
    
    Log("HttpGetRequest");
    
	while(*buffer && *buffer != '/') buffer++;
	if( !(*buffer)) return 0;
	while(*buffer && *buffer != ' ' && rc < max_len)
	{
		*request = *buffer;
		buffer++;
		request++;
		rc++;
	}
	*request = 0;
	return (rc < max_len)?rc:(-1);
}

int HTTPGetFormData(char *buffer, const char *label, char *value)
{
    char *p;
    int len = 0;
    
    p = buffer;
    do
    {
        p = strstr(p, label);
        if(p)
        {
            p += strlen(label);
            if(*p == '=')
            {
                p++;
                while(*p && *p != '&')
                {
                    *value = *p;
                    p++;
                    value++;
                    len++;
                }
                *value = 0;
            }
        }
    } while(p);
    
    return len;
}

int HTTPHeadResponse(const char *http_head)
{
    char str[4];
    char *p1;
    
    Log("[HTTPHeadResponse] %-.20s", http_head); 

    if(http_head)
    {
        /* Busco el código de respuesta http en la cabecera
         * "HTTP/1.1 200 OK\r\n" */
        p1 = strchr(http_head, ' ');
        if(p1)
        {
            str[0] = *(++p1);
            str[1] = *(++p1);
            str[2] = *(++p1);
            str[3] = 0;
            return atoi(str);
        }
    }
    return 0;
}

int HTTPFormResponse(const char *http_data)
{
    char str[16];
    
    Log("[HTTPFormResponse] %-.100s", http_data); 

    if(http_data)
    {
        if( strchr(http_data, '{') && 
            strchr(http_data, ':') && 
            strchr(http_data, ',') && 
            strchr(http_data, '}')  )
        {
            Log("[HTTPFormResponse] Respuesta en formato JSON no esperada");
            return 99;
        }
        else if( strchr(http_data, '=') )
        {
            Log("[HTTPFormResponse] Respuesta en formato de formulario");
            if(HTTPGetFormData((char*)http_data, "error", str))
            {
                Log("[HTTPFormResponse] Respuesta con error: %s", str);
                return atoi(str);
            }
            else
            {
                /* Si no encuentra la leyenda error no hay error */
                return 0;
            }
        }
        else
        {
            /* Si no dice nada asumo no error */
            return 0;
        }
    }
    return (-1);
}

/*<html>
<head>
<title>Dom32IO</title>
</head>
<style>
body{background-color:grey;font-size:24pt;}
#it{height:75;font-size:24pt}
</style>
<body>
<form method="post">
<h1>WiFi</h1>
<hr />
<h2 >AP1:</h2>
&nbsp;<input id="it" type="text" name="ap1" value="%s">&nbsp;<input id="it" type="text" name="ap1p" value="%s"><br>
<h2 >AP2:</h2>
&nbsp;<input id="it" type="text" name="ap2" value="%s">&nbsp;<input id="it" type="text" name="ap2p" value="%s"><br>
<br>
<br>
&nbsp;&nbsp;<input id="it"  type="submit" value="Guardar">
</form>
</body>
</html>
*/
void HttpReturnWiFiFormConfig(char *out, int max_len)
{
    snprintf(out, max_len, 
            "%s"
            "<html>\n"
            "<head>\n"
            "<title>Dom32IO</title>\n"
            "</head>\n"
            "<style>\n"
            "body{background-color:grey;font-size:24pt;}\n"
            "#it{height:75;font-size:24pt}\n"
            "</style>\n"
            "<body>\n"
            "<form method=\"post\">\n"
            "<h1>WiFi</h1>\n"
            "<p>MAC: %s</p>\n"
            "<hr />\n"
            "<h2>AP1:</h2>\n"
            "&nbsp;<input id=\"it\" type=\"text\" name=\"ap1\" value=\"%s\">&nbsp;<input  id=\"it\" type=\"text\" name=\"ap1p\" value=\"%s\"><br>\n"
            "<h2>AP2:</h2>\n"
            "&nbsp;<input id=\"it\" type=\"text\" name=\"ap2\" value=\"%s\">&nbsp;<input  id=\"it\" type=\"text\" name=\"ap2p\" value=\"%s\"><br>\n"
            "<h2>Central:</h2>\n"
            "&nbsp;<input id=\"it\" type=\"text\" name=\"ce1\" value=\"%s\">&nbsp;<input  id=\"it\" type=\"text\" name=\"ce2\" value=\"%s\"><br>\n"
            "<h2>Path:</h2>\n"
            "&nbsp;<input id=\"it\" type=\"text\" name=\"path\" value=\"%s\"><br>\n"
            "<br>\n"
            "<br>\n"
            "&nbsp;&nbsp;<input  id=\"it\" type=\"submit\" value=\"Guardar\">"
            "</form>\n"
            "</body>\n"
            "</html>\n",
            http_200,
            g_wifi_info.status.hw_mac,
            g_wifi_info.f.config.wifi_ap1, g_wifi_info.f.config.wifi_ap1_pass,
            g_wifi_info.f.config.wifi_ap2, g_wifi_info.f.config.wifi_ap2_pass,
            g_wifi_info.f.config.wifi_host1, g_wifi_info.f.config.wifi_host2,
            g_wifi_info.f.config.rqst_path);
}

void HttpReturnWiFiConfig(char *out, int max_len)
{
    snprintf(out, max_len,
            "%sID=%s&TYP=IO&ap1=%s&ap1p=%s&ap2=%s&ap2p=%s&ce1=%s&ce1p=%u&ce2=%s&ce2p=%u&report=%u&rqst=%s",
            http_200,
            g_wifi_info.status.hw_mac,
            g_wifi_info.f.config.wifi_ap1, g_wifi_info.f.config.wifi_ap1_pass,
            g_wifi_info.f.config.wifi_ap2, g_wifi_info.f.config.wifi_ap2_pass,
            g_wifi_info.f.config.wifi_host1, g_wifi_info.f.config.wifi_host1_port,
            g_wifi_info.f.config.wifi_host2, g_wifi_info.f.config.wifi_host2_port,
            g_wifi_info.f.config.report/10, g_wifi_info.f.config.rqst_path);
}

void HttpReturnResult(char *out, const char* result, int max_len)
{
    snprintf(out, max_len,
        "%sID=%s&TYP=IO&RESULT=%s",
        http_200,
        g_wifi_info.status.hw_mac,
        result);
    
    Log("[HttpReturnResult] %s - data-len: %d", result, strlen(out));
}

void HttpProcessWiFiFormConfig(char* in)
{
    HTTPGetFormData(in, "ap1", g_wifi_info.f.config.wifi_ap1);
    HTTPGetFormData(in, "ap1p", g_wifi_info.f.config.wifi_ap1_pass);
    HTTPGetFormData(in, "ap2", g_wifi_info.f.config.wifi_ap2);
    HTTPGetFormData(in, "ap2p", g_wifi_info.f.config.wifi_ap2_pass);
    HTTPGetFormData(in, "ce1", g_wifi_info.f.config.wifi_host1);
    HTTPGetFormData(in, "ce2", g_wifi_info.f.config.wifi_host2);
    HTTPGetFormData(in, "path", g_wifi_info.f.config.rqst_path);
    g_wifi_info.status.save_config = 50;
}

void HttpProcessCommand(char* in)
{
    char cmd[32];
    
    Log("[HttpProcessCommand] [%.100s]", in);
    if(HTTPGetFormData(in, "Command", cmd))
    {
        Log("[HttpProcessCommand] Comando");
        if( !strcmp(cmd, "Download"))
        {
            Log("[HttpProcessCommand] Comando Download");
            if(HTTPGetFormData(in, "Filename", g_download_file_name))
            {
                Log("[HttpProcessCommand] Comando Download Filename: %s", g_download_file_name);
            }
        }
    }
}

/* *****************************************************************************
 * Inicializacion, llamar al inicio
 * ************************************************************************** */
void HTTPInit( void )
{
    memset(&http_buffer_input, 0, sizeof(http_data));
    memset(&http_buffer_output, 0, sizeof(http_data));
    memset(&http_buffer_response, 0, sizeof(http_data));
    g_download_file_name[0] = 0;
    http_process_tmp_file = 0;
    g_download_file_count = 0;
}

/* *****************************************************************************
 * Tareas de HTTP, llamar desde el loop de procesamiento
 * ************************************************************************** */
void HTTPTask( void )
{
    /* Proceso requerimientos */
    if(http_buffer_input.type == 'G')
    {
        /* GET */
        Log("[HTTPTask] GET: %s %u bytes", http_buffer_input.uri, strlen(http_buffer_input.data));
        if( !strcmp(http_buffer_input.uri, "/"))
        {
            if(g_wifi_info.status.wifi_mode == 3)
            {
                HttpReturnWiFiFormConfig(http_buffer_response.data, MAX_HTTP_DATA);
            }
            else
            {
                strncpy(http_buffer_response.data, http_404, MAX_HTTP_DATA);
            }
        }
        else if( !strcmp(http_buffer_input.uri, "/reset.htm"))
        {
            CTRLReset();
            HttpReturnResult(http_buffer_response.data, "Ok", MAX_HTTP_DATA);
        }
        else
        {
            strncpy(http_buffer_response.data, http_404, MAX_HTTP_DATA);
        }
        http_buffer_response.type = 'H';
        http_buffer_response.timeout = 100;
        Log("[HTTPTask] Respondiendo: %s %u bytes",
                http_buffer_response.data, strlen(http_buffer_response.data));
    }
    else if(http_buffer_input.type == 'P')
    {
        Log("[HTTPTask] PUT/POST: %s %u bytes",
                http_buffer_input.uri, strlen(http_buffer_input.data));
        if( !strcmp(http_buffer_input.uri, "/"))
        {
            HttpProcessWiFiFormConfig(http_buffer_input.data);
            HttpReturnWiFiFormConfig(http_buffer_response.data, MAX_HTTP_DATA);
        }
        else if( !strcmp(http_buffer_input.uri, "/command.cgi"))
        {
            HttpProcessCommand(http_buffer_input.data);
            HttpReturnResult(http_buffer_response.data, "Ok", MAX_HTTP_DATA);
        }
        else if( !strcmp(http_buffer_input.uri, "/wifi.cgi"))
        {
            HttpProcessWiFiFormConfig(http_buffer_input.data);
            HttpReturnWiFiConfig(http_buffer_response.data, MAX_HTTP_DATA);
        }
        else
        {
            strncpy(http_buffer_response.data, http_404, MAX_HTTP_DATA);
        }
        /* Completo la respuesta */
        http_buffer_response.type = 'H';
        http_buffer_response.timeout = 100;
        Log("[HTTPTask] Respondiendo: %s %u bytes",
                http_buffer_response.data, strlen(http_buffer_response.data));
    }
    /* Proceso respuestas */
    else if(http_buffer_input.type == 'H')
    {
        /* Se trata de una respuesta HTTP/1... */
        if(http_buffer_input.http_rc == 200 &&
           http_buffer_input.form_rc == 0 )
        {
            /* Ok */
            g_wifi_info.status.host_conectado = 1;
        }
        else
        {
            /* Error */
            WifiSwitchHost();
        }
        g_wifi_info.status.count_inactividad = 0;
    }
    else if(http_buffer_input.type)
    {
        Log("[HTTPTask] typ: %c DESCONOCIDO %-.100s",
                http_buffer_input.type,
                http_buffer_input.data);
    }
    http_buffer_input.type = 0;
}

/* *****************************************************************************
 * Se lo llama 10 veces por segundo
 * ************************************************************************** */
void HTTPTimer( void )
{
    if(http_buffer_input.type && http_buffer_input.timeout)
    {
        http_buffer_input.timeout--;
        if(http_buffer_input.timeout == 0)
        {
            http_buffer_input.type = 0;
            Log("[HTTPTimer] TIMEOUT de mensaje entrante");
        }
    }

    if(http_buffer_output.type && http_buffer_output.timeout)
    {
        http_buffer_output.timeout--;
        if(http_buffer_output.timeout == 0)
        {
            http_buffer_output.type = 0;
            Log("[HTTPTimer] TIMEOUT de mensaje saliente");
        }
    }

    if(http_buffer_response.type && http_buffer_response.timeout)
    {
        http_buffer_response.timeout--;
        if(http_buffer_response.timeout == 0)
        {
            http_buffer_response.type = 0;
            Log("[HTTPTimer] De respuesta saliente");
        }
    }
    
    if(http_process_tmp_file)
    {
        http_process_tmp_file--;
        if(http_process_tmp_file == 0)
        {
            HTTPProcessTmpFile(DOWNLOAD_TEMP_FILE_NAME, http_process_tmp_file_to_name);
            FSremove(DOWNLOAD_TEMP_FILE_NAME);
            if( !strcmp(http_process_tmp_file_to_name, FIRMWARE_FILENAME))
            {
                CTRLReset();
            }
        }
    }
    
    if(http_buffer_output.type == 0 &&
       http_buffer_input.type == 0 &&
       http_buffer_response.type == 0 &&
       g_download_file_name[0] )
    {
        if(g_download_file_count == 0)
        {
            g_download_file_count = 50;
        }
        else
        {
            g_download_file_count--;
            if(g_download_file_count == 0)
            {
                HTTPGetFile(g_download_file_name, (g_download_file_params[0])?g_download_file_params:NULL);
                g_download_file_name[0] = 0;
                g_download_file_params[0] = 0;
            }
        }
    }


}

/* *****************************************************************************
 * Agrega un mensaje HTTP entrante para su tratamiento segun su tipo
 * P - POST recibido, hay que procesar
 * G - GET recibido, hay que procesar
 * H - Una respuesta
 * ************************************************************************** */
int HTTPAddInput(int id, const char* buffer)
{
    char *p;

    if(http_buffer_input.type)
    {
        Log("[HTTPAddInput] Buffer de entrada ocupado");
        return (-1);
    }
    
    Log("[HTTPAddInput] %-.100s...", buffer);
    
    if(*buffer == 'G' || *buffer == 'P')
    {
        /* Requerimiento */
        http_buffer_input.type = *buffer;
        http_buffer_input.id = id;
        http_buffer_input.timeout = 50;

        if(HttpGetRequest(buffer, http_buffer_input.uri, MAX_HTTP_URI) <= 0)
        {
            Log("[HTTPAddInput] URI Overflow");
            return (-1);
        }
        if(http_buffer_input.type == 'P')
        {
            /* PUT / POST */
            p = strstr(buffer, "\r\n\r\n");
            if(p)
            {
                p += 4;
                if(HttpDecodeFormData(http_buffer_input.data, p, MAX_HTTP_DATA) <= 0)
                {
                    Log("[HTTPAddInput] FORM Overflow");
                    return (-1);
                }
            }
        }
        return 1;
    }
    else if(*buffer == 'H')
    {
        /* Respuesta */
        Log("[HTTPAddInput] Respuesta");
        http_buffer_input.type = *buffer;
        http_buffer_input.http_rc = HTTPHeadResponse(buffer);
        http_buffer_input.timeout = 50;
        if(http_buffer_input.http_rc == 200)
        {
            p = strstr(buffer, "\r\n\r\n");
            if(p)
            {
                p += 4;
                if(HttpDecodeFormData(http_buffer_input.data, p, MAX_HTTP_DATA) <= 0)
                {
                    Log("[HTTPAddInput] FORM Overflow");
                    return (-1);
                }
                http_buffer_input.form_rc = HTTPFormResponse(http_buffer_input.data);
                if(http_buffer_input.form_rc != 0)
                {
                    Log("[HTTPAddInput] FORM Error %i", http_buffer_input.form_rc);
                }
            }
            return 1;
        }
        else
        {
            Log("[HTTPAddInput] HTTP Error %i", http_buffer_input.http_rc);
            http_buffer_input.form_rc = 0;
        }
    }
    return 0;
}
    
int HTTPAddOutput(const char* filename, bool download, const char* buffer, unsigned int to_cs)
{
    int i;
    
    if(http_buffer_output.type)
    {
        Log("[HTTPAddOutput] Buffer de salida ocupado");
        return (-1);
    }
    
    Log("[HTTPAddOutput] %-.100s...", buffer);
    
    http_buffer_output.timeout = to_cs;
    http_buffer_output.type = *buffer;
    http_buffer_output.id = 0;
    http_buffer_output.download = (download)?1:0;
    /* Saco HttpDecodeFormData cuando genero un mensaje saliente porque
     * necesito que est�n las secuencias de escape
    if(HttpDecodeFormData(http_buffer_output.data, buffer, MAX_HTTP_DATA) <= 0)
    {
        Log("[HTTPAddInput] FORM Overflow");
        return (-1);
    }
    */
    strncpy(http_buffer_output.data, buffer, MAX_HTTP_DATA);
    /* Avanzo hasta la ultima '/' para dejar el nombre sin path */
    while(strchr(filename, '/'))
    {
        while(*filename != '/') filename++;
        filename++;
    }
    
    /* copio solo caracteres validos */
    for(i = 0; *filename; filename++)
    {
        if( (*filename >= '0' && *filename <= '9') ||
            (*filename >= 'a' && *filename <= 'z') ||
            (*filename >= 'A' && *filename <= 'Z') ||
             *filename == '.' || *filename == '_' )
        {
            http_buffer_output.filename[i++] = *filename;
        }
    }
    http_buffer_output.filename[i] = 0;

    return 1;
}

int HTTPAddResponse(int id, const char* buffer)
{
    if(http_buffer_response.type)
    {
        Log("[HTTPAddResponse] Buffer de salida ocupado");
        return (-1);
    }
    
    Log("[HTTPAddResponse] %-.100s...", buffer);
    
    http_buffer_response.timeout = 100;
    http_buffer_response.type = 'H';
    http_buffer_response.id = id;
    if(HttpDecodeFormData(http_buffer_response.data, buffer, MAX_HTTP_DATA) <= 0)
    {
        Log("[HTTPAddResponse] FORM Overflow");
        return (-1);
    }
    return 1;
}

/* *****************************************************************************
 * Genera un mensaje WEB con formato de formulario POST
 * y lo copia a un buffer (respuesta) o encola para enviar (notificación)
 * ************************************************************************** */
int HTTPNotificarStatus()
{
    char tmp_uri[MAX_HTTP_URI+1];
    char tmp_data[MAX_HTTP_DATA+1];
    char tmp_rqst[MAX_HTTP_DATA+1];
    
    /* Parte fija con la MAC y las entradas y salidas */
    snprintf(tmp_data, MAX_HTTP_DATA,
        "ID=%s&TYP=TOUCH", g_wifi_info.status.hw_mac);
    
    /* Version del stack AT del ESP-02 */
    if((MAX_HTTP_DATA - strlen(tmp_data) > sizeof(g_wifi_info.status.wifi_at)))
    {
        snprintf(&tmp_data[strlen(tmp_data)], MAX_HTTP_DATA - strlen(tmp_data), 
                "&AT=%s", g_wifi_info.status.wifi_at);
    }
    /* Version del SDK del ESP-02 */
    if((MAX_HTTP_DATA - strlen(tmp_data) > sizeof(g_wifi_info.status.wifi_sdk)))
    {
        snprintf(&tmp_data[strlen(tmp_data)], MAX_HTTP_DATA - strlen(tmp_data), 
                "&SDK=%s", g_wifi_info.status.wifi_sdk);
    }
    /* Compilacion del firmware */
    if((MAX_HTTP_DATA - strlen(tmp_data) > sizeof(g_wifi_info.status.up_fw)))
    {
        snprintf(&tmp_data[strlen(tmp_data)], MAX_HTTP_DATA - strlen(tmp_data), 
                "&FW=%s", g_wifi_info.status.up_fw);
    }

    /* Agrego solicitud de configuración */
    if(g_wifi_info.f.config.io_config_default && (MAX_HTTP_DATA - strlen(tmp_data) > 10) )
    {
        strcat(tmp_data, "&GETCONF=1");
    }
    
    snprintf(tmp_uri, MAX_HTTP_URI, "%s/infoio.cgi", g_wifi_info.f.config.rqst_path);
    /* POST
     * 1.- %s: URI
     * 2.- %s: Host
     * 3.- %d: Content-Length
     * 4.- %s: datos
     */
    snprintf(tmp_rqst, MAX_HTTP_DATA, http_post,
            tmp_uri,
            g_wifi_host,
            strlen(tmp_data),
            tmp_data);

    Log("[HTTPNotificarStatus] - data-len: %d", strlen(tmp_rqst));

    if(HTTPAddOutput(tmp_uri, false, tmp_rqst, 250) <= 0)
    {
        /* No fue posible enviar */
        return 0;
    }
    
    return strlen(tmp_rqst);
}

int HTTPCommandSwitch( const char *obj_name )
{
    /*
     newAJAXCommand('/cgi-bin/abmassign.cgi?funcion=switch&Objeto=".$Nombre."'
     */
    char tmp_uri[MAX_HTTP_URI+1];
    char tmp_rqst[MAX_HTTP_DATA+1];

    Log("[HTTPCommandSwitch] %s", obj_name);

    snprintf(tmp_uri, MAX_HTTP_URI, 
            "%s/abmassign.cgi?funcion=switch&Objeto=%s",
            g_wifi_info.f.config.rqst_path,
            obj_name);
    url_encode(tmp_uri, tmp_uri);
    /*
     * GET
     * 1.- %s: URI
     * 2.- %s: Host
     */
    snprintf(tmp_rqst, MAX_HTTP_DATA, http_get,
             tmp_uri,
             g_wifi_host);
    if(HTTPAddOutput(tmp_uri, false, tmp_rqst, 250) <= 0)
    {
        /* No fue posible enviar */
        return 0;
    }
    return strlen(tmp_rqst);
}

int HTTPCommandPulse( const char *obj_name )
{
    /*
     newAJAXCommand('/cgi-bin/abmassign.cgi?funcion=switch&Objeto=".$Nombre."'
     */
    char tmp_uri[MAX_HTTP_URI+1];
    char tmp_rqst[MAX_HTTP_DATA+1];

    Log("[HTTPCommandSwitch] %s", obj_name);

    snprintf(tmp_uri, MAX_HTTP_URI, 
            "%s/abmassign.cgi?funcion=pulse&Objeto=%s",
            g_wifi_info.f.config.rqst_path,
            obj_name);
    url_encode(tmp_uri, tmp_uri);
    /*
     * GET
     * 1.- %s: URI
     * 2.- %s: Host
     */
    snprintf(tmp_rqst, MAX_HTTP_DATA, http_get,
             tmp_uri,
             g_wifi_host);
    if(HTTPAddOutput(tmp_uri, false, tmp_rqst, 250) <= 0)
    {
        /* No fue posible enviar */
        return 0;
    }
    return strlen(tmp_rqst);
}
