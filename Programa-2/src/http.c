/***************************************************************************
    Copyright (C) 2026   Walter Pirri

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
#include "http.h"

#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "defines.h"
#include "log.h"
#include "config.h"
#include "wifi/wifi.h"

int g_http_c_host_conectado;
int g_http_c_go_host_conectado;

const char http_c_xml_200[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n"
                              "Content-Type: text/xml\r\n\r\n";
const char http_c_http_200[] = "HTTP/1.1 200 OK\r\n"
                               "Connection: close\r\n"
                               "Content-Type: text/html\r\n"
                               "Cache-Control: no-cache\r\n\r\n";
const char http_c_http_404[] = "HTTP/1.1 404 Not found\r\n"
                               "Connection: close\r\n\r\n"
                               "404: File not found\r\n";
/* POST
 * 1.- %s: URI
 * 2.- %s: Host
 * 3.- %d: Content-Length
 * 4.- %s: datos
 */
const char http_c_http_post[] = "POST %s HTTP/1.1\r\n"
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
const char http_c_http_get[] = "GET %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "Connection: close\r\n"
                               "User-Agent: Dom32io/1.00 (Microchip;PIC32)\r\n"
                               "Accept: text/html,text/xml\r\n\r\n";

void HttpInit(void)
{
    g_http_c_host_conectado = 0;
    g_http_c_go_host_conectado = 0;

}

int HttpOnLine( void )
{
    if(WiFiConectado() == 0) g_http_c_host_conectado = 0;
    return (g_http_c_host_conectado > 0)?1:0;
}

void HttpSwitchHost( void )
{
    if(g_http_c_go_host_conectado == 1) g_http_c_go_host_conectado = 2;
    else                              g_http_c_go_host_conectado = 1;
}

void HttpTask(void)
{
    
}

void HttpTimerInt(void)
{
    
}

int HttpQueryHost(const char* url, const char* msg_send, char* msg_resp)
{
    char* host;
    int port;
    char http_buffer[4096];
    int rc;

    if(WiFiConectado() == 0)
    {
        LogMessage("[HTTP] HttpQueryHost: WiFi no conectado");
        return (-1);
    }
    
    /* Selección de host y port */
    if(g_http_c_host_conectado == 0)
    {
        if(g_wifi_info.f.config.wifi_host1[0] == 0 &&
           g_wifi_info.f.config.wifi_host2[0] == 0  ) return (-1);
        if(g_http_c_go_host_conectado == 0) g_http_c_go_host_conectado = 1;
        if(g_http_c_go_host_conectado == 1 && g_wifi_info.f.config.wifi_host1[0])
        {
            g_http_c_go_host_conectado = 2;
        }
        else if(g_http_c_go_host_conectado == 2 && g_wifi_info.f.config.wifi_host2[0])
        {
            g_http_c_go_host_conectado = 1;
        }
    }    

    if(g_http_c_go_host_conectado == 1)
    {
        host = &g_wifi_info.f.config.wifi_host1[0];
        port = g_wifi_info.f.config.wifi_host1_port;
    }
    else
    {
        host = &g_wifi_info.f.config.wifi_host2[0];
        port = g_wifi_info.f.config.wifi_host2_port;
    }

    if(port == 0)
    {
        if(g_wifi_info.f.config.enable_https) port = 443;
        else port = 80;
    }

    /* POST
     * 1.- %s: URI
     * 2.- %s: Host
     * 3.- %d: Content-Length
     * 4.- %s: datos
     */
    sprintf(http_buffer, http_c_http_post, 
            url, host, strlen(msg_send), msg_send);
    rc = WiFiQueryHost(host, port, http_buffer, http_buffer);
    if(rc < 0)
    {
        LogMessage("[HTTP] HttpQueryHost: Error en WiFiQueryHost");
        return (-1);
    }
    else
    {
        LogMessage("[HTTP] HttpQueryHost: recibidos %i bytes", rc);
        LogMessage(http_buffer);

        
    }
    return 0;
}