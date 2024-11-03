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
#include <xc.h>
 /*
 	TODO: Seleccion de host de destino
    TODO: Agregar soporte SSL
 	TODO: Modo de conexiones solo salientes
 */

#define SET_RESET           (LATBSET=(1<<10))
#define CLR_RESET           (LATBCLR=(1<<10))

#define _IN_WIFI_C_
#include "wifi.h"
#undef _IN_WIFI_C_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "strfunc.h"
#include "http.h"
#include "config.h"
#include "log.h"
#include "delay.h"
#include "sd/fsio.h"

#define WIFI_READ_LINE_BUFFER_LEN 1023
#define TIMER_AP_VALUE 600

typedef enum
{
    INVALID = 0,
    RESET,
    START,
    CLEAN,
    INIT,
    UPGRADE,
    APMODE,
    STMODE,
    HTTP_RESP,
    HTTP_REQ,
    LISTAP,
    LOOP,
    ERROR
} task_stm;

const char *task_stm_label[] = {
    "INVALID",
    "RESET",
    "START",
    "CLEAN",
    "INIT",
    "UPGRADE",
    "APMODE",
    "STMODE",
    "HTTP_RESP",
    "HTTP_REQ",
    "LISTAP",
    "LOOP",
    "ERROR"};

task_stm g_wifi_task_stm;
task_stm g_wifi_task_stm_last;
unsigned int g_wifi_timer_ap;
unsigned int g_wifi_task_stm_step;
unsigned int g_wifi_task_stm_step_last;
unsigned int g_wifi_task_stm_delay;
unsigned int g_wifi_task_stm_timeout;
unsigned int g_wifi_task_retry;
unsigned char g_wifi_send_error_count;
unsigned char g_wifi_recv_error_count;
char g_wifi_read_line_buffer[WIFI_READ_LINE_BUFFER_LEN+1];
int g_wifi_read_line_buffer_index;
char g_wifi_http_filename[FILE_NAME_SIZE+1];
unsigned char g_wifi_read_line_buffer_timer;
bool g_wifi_read_line_wait_crlf;
bool g_wifi_wait_more_data;
char g_wifi_cmd[256];

bool g_wifi_need_upgrade;
bool g_wifi_fast_start;


#define WIFI_UART_RX_BYTEQ_LENGTH 4095

static uint8_t * volatile rxTail;
static uint8_t * rxHead;
static uint8_t * volatile txHead;
static bool volatile rxOverflowed;
static uint8_t rxQueue[WIFI_UART_RX_BYTEQ_LENGTH+1] ;

void WifiSerialInit(void)
{
    rxHead = rxQueue;
    rxTail = rxQueue;
    rxOverflowed = 0;

    /* ************************************************************************** */
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    /* ************************************************************************** */

    IEC1bits.U3TXIE = 0;
    IEC1bits.U3RXIE = 0;

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    U3MODE = (0x8008 & ~(1<<15));  // disabling UART
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U3STA = 0x0;
    // BaudRate = 115200; Frequency = 24000000 Hz; BRG 51; 
    U3BRG = 0x33;

    IEC1bits.U3RXIE = 1;

     //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U3STASET = _U3STA_UTXEN_MASK;
    U3MODESET = _U3MODE_ON_MASK;  // enabling UART ON bit
    U3STASET = _U3STA_URXEN_MASK; 

    /* ************************************************************************** */
    // System Reg Lock
     SYSKEY = 0x00000000; 
}

bool WifiSerialIsRxReady(void)
{    
    return !(rxHead == rxTail);
}


void WifiSerialWrite(unsigned int ch)
{
    while(U3STAbits.UTXBF);
    U3TXREG = ch;
}

unsigned char WifiSerialRead( void)
{
    unsigned char data = 0;

    while (rxHead == rxTail );
    
    data = *rxHead;

    rxHead++;

    if (rxHead == (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH))
    {
        rxHead = rxQueue;
    }
    return data;
}



void WifiTaskSTMSet(task_stm st, unsigned int delay, unsigned int to)
{
    g_wifi_task_stm = st;
    g_wifi_task_stm_delay = delay;
    g_wifi_task_stm_timeout = to;
    g_wifi_task_stm_step = 0;
    g_wifi_task_stm_step_last = (-1);
}

void WifiWrite( const char *buffer )
{
    if(buffer)
    {
        Log("[WifiWrite] %-.100s", buffer);
        while(*buffer)
        {
            WifiSerialWrite(*buffer);
            buffer++;
        }
    }
}

void WifiWriteLine( const char *line )
{
    if(line)
    {
        Log("[WifiWriteLine] %-.100s", line);
        while(*line)
        {
            WifiSerialWrite(*line);
            line++;
        }
    }
    WifiSerialWrite('\r');
    WifiSerialWrite('\n');
}

/*
    Return: = 0 - No se recibiï¿½ lo que se esperaba y ninguna acciï¿½n no solicitada
            > 0 - Se recibiï¿½ algo no solicitado rc = nuevo estado
            < 0 - Se recibio lo que se esperaba
*/
int WifiWaitLine(const char *line1, const char *line2, const char *line3, const char *line4, const char *line5)
{
    int rc = 0;
    unsigned char c = 0;

    while(WifiSerialIsRxReady())
    {
        c = WifiSerialRead();
        g_wifi_read_line_buffer_timer = 3;

        /* Si estoy esperando fin de linea ... */
        if(g_wifi_read_line_wait_crlf)
        {
            /* salgo del loop cuando lo recibo */
            if(c == 0x0A || c == 0x0D) break;
            /* elimino todo lo recibido si recibo ascii extendido */
            if(c > 127)
            {
                g_wifi_read_line_buffer_timer = 0;
                g_wifi_read_line_buffer_index = 0;
                return 0;
            }
        }
        /*voy agregando los datos al buffer */
        if(g_wifi_read_line_buffer_index < WIFI_READ_LINE_BUFFER_LEN)
        {
            /* Se agrega el caracter a la lï¿½nea */
            g_wifi_read_line_buffer[g_wifi_read_line_buffer_index] = c;
            g_wifi_read_line_buffer_index++;
            g_wifi_read_line_buffer[g_wifi_read_line_buffer_index] = 0;
            /* Detecto la llegada de datos por TCP y dejo de esperar el fin de linea */
            if(g_wifi_read_line_buffer_index == 4)
            {
                /*+IPD*/
                if(g_wifi_read_line_buffer[0] == '+' &&
                   g_wifi_read_line_buffer[1] == 'I' &&
                   g_wifi_read_line_buffer[2] == 'P' &&
                   g_wifi_read_line_buffer[3] == 'D'  )
                {
                    g_wifi_read_line_wait_crlf = false;
                }
            }
            /* Si el buffer estÃ¡ lleno, salgo */
            if(g_wifi_read_line_buffer_index == WIFI_READ_LINE_BUFFER_LEN) break;
        }
    }   
    
    if(g_wifi_wait_more_data && ((g_wifi_read_line_buffer_timer == 0) || (g_wifi_read_line_buffer_index == WIFI_READ_LINE_BUFFER_LEN)) )
    {
        if((g_wifi_read_line_buffer_timer == 0))
        {
            /* time-out esperando mas datos */
            HTTPEndTmpFile(http_buffer_output.filename, 
                    g_wifi_read_line_buffer, 
                    g_wifi_read_line_buffer_index);
            g_wifi_wait_more_data = false;
            g_wifi_read_line_buffer_index = 0;
        }
        else if(g_wifi_read_line_buffer_index == WIFI_READ_LINE_BUFFER_LEN)
        {
            /* buffer lleno esperando mas datos */
            HTTPAddTmpFile(g_wifi_read_line_buffer, g_wifi_read_line_buffer_index);
            g_wifi_read_line_buffer_index = 0;
        }
    }
    /* Detecto el final de linea o time-out recibiendo datos */
    else if( (g_wifi_read_line_wait_crlf && (c == 0x0A || c == 0x0D)) || (g_wifi_read_line_buffer_timer == 0) )
    {
        g_wifi_read_line_wait_crlf = true;
        g_wifi_read_line_buffer_timer = 0;

        while(g_wifi_read_line_buffer_index)
        {
            if(line1)
            {
#ifdef DEBUG_WIFI
                Log("WifiWaitLine: esperando:%.80s / recibido: %.80s", line1, g_wifi_read_line_buffer);
#endif
                if( !memcmp(line1, g_wifi_read_line_buffer, strlen(line1)))
                {
                    Log("[WifiWaitLine] Encontrado: %s", line1);
                    rc = 1;  /* Se recibiï¿½ lo que se esperaba */
                }
            }
            if(rc == 0 && line2)
            {
#ifdef DEBUG_WIFI
                Log("WifiWaitLine: esperando:%.80s / recibido: %.80s", line2, g_wifi_read_line_buffer);
#endif
                if( !memcmp(line2, g_wifi_read_line_buffer, strlen(line2)))
                {
                    Log("[WifiWaitLine] Encontrado: %s", line2);
                    rc = 2;  /* Se recibiï¿½ lo que se esperaba */
                }
            }
            if(rc == 0 && line3)
            {
#ifdef DEBUG_WIFI
                Log("WifiWaitLine: esperando:%.80s / recibido: %.80s", line3, g_wifi_read_line_buffer);
#endif
                if( !memcmp(line3, g_wifi_read_line_buffer, strlen(line3)))
                {
                    Log("[WifiWaitLine] Encontrado: %s", line3);
                    rc = 3;  /* Se recibiï¿½ lo que se esperaba */
                }
            }
            if(rc == 0 && line4)
            {
#ifdef DEBUG_WIFI
                Log("WifiWaitLine: esperando:%.80s / recibido: %.80s", line4, g_wifi_read_line_buffer);
#endif
                if( !memcmp(line4, g_wifi_read_line_buffer, strlen(line4)))
                {
                    Log("[WifiWaitLine] Encontrado: %s", line4);
                    rc = 4;  /* Se recibiï¿½ lo que se esperaba */
                }
            }
            if(rc == 0 && line5)
            {
#ifdef DEBUG_WIFI
                Log("WifiWaitLine: esperando:%.80s / recibido: %.80s", line5, g_wifi_read_line_buffer);
#endif
                if( !memcmp(line5, g_wifi_read_line_buffer, strlen(line5)))
                {
                    Log("[WifiWaitLine] Encontrado: %s", line5);
                    rc = 5;  /* Se recibiï¿½ lo que se esperaba */
                }
            }
            
            if(rc == 0)
            {
                rc = WifiCheckUnsol();
            }
            else
            {
                g_wifi_read_line_buffer_index = 0;
            }
        }
    }
    else if(g_wifi_read_line_buffer_index == WIFI_READ_LINE_BUFFER_LEN)
    {
        /*+IPD*/
        if(g_wifi_read_line_buffer[0] == '+' &&
           g_wifi_read_line_buffer[1] == 'I' &&
           g_wifi_read_line_buffer[2] == 'P' &&
           g_wifi_read_line_buffer[3] == 'D'  )
        {
            rc = WifiCheckUnsol();
            g_wifi_wait_more_data = true;
            g_wifi_read_line_buffer_index = 0;
        }
    }
    return rc;
}

int WifiWaitPrompt(const char prompt)
{
    while(WifiSerialIsRxReady())
    {
        if(WifiSerialRead() == prompt) return 1;
    }
    return 0;
}

int WifiCheckUnsol( void )
{
    char str[16];
    int id;
    int len;
    char *p;
    char tmp_buffer[WIFI_READ_LINE_BUFFER_LEN+1];

    if( !memcmp(g_wifi_read_line_buffer, "+IPD,", 5)) /* Datos socket */
    {
        /*
        +IPD,0,442:<datos>
        */
        Log("[WifiCheckUnsol] %-.100s", g_wifi_read_line_buffer);

        id = 0;
        len = 0;
        
        if(str_section(g_wifi_read_line_buffer, ',', 1, str))
        {
            id = atoi(str);
        }
        if(str_section(g_wifi_read_line_buffer, ',', 2, str))
        {
            len = atoi(str);
        }
        /* dejo en el buffer solo el HTTP */
        p = strchr(g_wifi_read_line_buffer, ':');
        if(p)
        {
            if( g_wifi_read_line_buffer_index == WIFI_READ_LINE_BUFFER_LEN)
            {
                /* Si el buffer está lleno debe ser un download */
                if(HTTPInitTmpFile(g_wifi_read_line_buffer, WIFI_READ_LINE_BUFFER_LEN) < 0)
                {
                    /* No había download pendiente */
                    Log("[WifiCheckUnsol] HTTP input overflow: %-.100s", g_wifi_read_line_buffer);
                }
            }
            else
            {
	            p++;
	            tmp_buffer[0] = 0;
	            if(*(p+len))
	            {
	                strcpy(tmp_buffer, (p+len));
	            }
	            *(p+len) = 0;
	            HTTPAddInput(id, p);
	            if(tmp_buffer[0])
	            {
	                strcpy(g_wifi_read_line_buffer, tmp_buffer);
	                g_wifi_read_line_buffer_index = strlen(g_wifi_read_line_buffer);
	                Log("[WifiCheckUnsol] Resto: %-.100s", g_wifi_read_line_buffer);
	            }
	            else
	            {
	            	g_wifi_read_line_buffer_index = 0;
	            }
			}            
        }
        else
        {
        	g_wifi_read_line_buffer_index = 0;
        }
    }
    else if( !memcmp(g_wifi_read_line_buffer, "WIFI CONNECTED", 14))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WIFI] Conectado al AP [%s].", 
                ((g_wifi_info.status.wifi_ap_select == 1)?g_wifi_info.f.config.wifi_ap1:g_wifi_info.f.config.wifi_ap2));
        g_wifi_info.status.wifi_conectado = g_wifi_info.status.wifi_ap_select;
    }
    else if( !memcmp(g_wifi_read_line_buffer, "WIFI DISCONNECTED", 17))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WiFi] Deconectado del AP.");
        if(g_wifi_info.status.wifi_conectado)
        {
            g_wifi_info.status.wifi_conectado = 0;
            g_wifi_info.status.wifi_ap_select = (g_wifi_info.status.wifi_ap_select == 1)?2:1;
            return STMODE;
        }
    }
    else if( !memcmp(g_wifi_read_line_buffer, "+STA_CONNECTED", 8))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WiFi] Cliente conectado.");
        /* Cliente conectado al AP */
        g_wifi_timer_ap = 0; // para que no salga de modo AP
    }
    else if( !memcmp(g_wifi_read_line_buffer, "+STA_DISCONNECTED", 8))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WiFi] Cliente desconectado.");
        /* Cliente desconectado al AP */
        g_wifi_timer_ap = 50; // para que salga en seguida del modo AP
    }
    else if( !memcmp(g_wifi_read_line_buffer, "+CIFSR:", 7))
    {
        g_wifi_read_line_buffer_index = 0;
        /* AT+CIFSR
         * +CIFSR:STAIP,"0.0.0.0"
         * +CIFSR:STAMAC,"80:7d:3a:62:03:60"
         */
        if( !memcmp(&g_wifi_read_line_buffer[7], "STAMAC", 6))
        {
            Log("[WiFi] MAC %.17s", &g_wifi_read_line_buffer[15]);
            g_wifi_info.status.hw_mac[0]  = g_wifi_read_line_buffer[15];
            g_wifi_info.status.hw_mac[1]  = g_wifi_read_line_buffer[16];
            g_wifi_info.status.hw_mac[2]  = g_wifi_read_line_buffer[18];
            g_wifi_info.status.hw_mac[3]  = g_wifi_read_line_buffer[19];
            g_wifi_info.status.hw_mac[4]  = g_wifi_read_line_buffer[21];
            g_wifi_info.status.hw_mac[5]  = g_wifi_read_line_buffer[22];
            g_wifi_info.status.hw_mac[6]  = g_wifi_read_line_buffer[24];
            g_wifi_info.status.hw_mac[7]  = g_wifi_read_line_buffer[25];
            g_wifi_info.status.hw_mac[8]  = g_wifi_read_line_buffer[27];
            g_wifi_info.status.hw_mac[9]  = g_wifi_read_line_buffer[28];
            g_wifi_info.status.hw_mac[10] = g_wifi_read_line_buffer[30];
            g_wifi_info.status.hw_mac[11] = g_wifi_read_line_buffer[31];
            g_wifi_info.status.hw_mac[12] = 0;
        }
    }
    else if( !memcmp(g_wifi_read_line_buffer, "AT version:", 11))
    {
        g_wifi_read_line_buffer_index = 0;
        /*
         * AT version:1.6.2.0(Apr 13 2018 11:10:59)
         * AT version:1.7.4.0(May 11 2020 19:13:04)
         */
        Log("[WiFi] %s.", g_wifi_read_line_buffer);
        strncpy(g_wifi_info.status.wifi_at, &g_wifi_read_line_buffer[11], sizeof(g_wifi_info.status.wifi_at)-1);
        //if(strstr(g_wifi_read_line_buffer, "1.6.2.0"))
        //{
        //    Log("[WiFi] El firware necesita upgrade.");
        //    g_wifi_need_upgrade = true;
        //}
    }
    else if( !memcmp(g_wifi_read_line_buffer, "SDK version:", 12))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WiFi] %s.", g_wifi_read_line_buffer);
        strncpy(g_wifi_info.status.wifi_sdk, &g_wifi_read_line_buffer[12], sizeof(g_wifi_info.status.wifi_sdk)-1);
    }
    else if( !memcmp(g_wifi_read_line_buffer, "compile time:", 13))
    {
        g_wifi_read_line_buffer_index = 0;
        Log("[WiFi] %s.", g_wifi_read_line_buffer);
    }
    else
    {
        g_wifi_read_line_buffer_index = 0;
    }
    return 0;
}

void WifiSwitchHost( void )
{
    if(g_wifi_host == &g_wifi_info.f.config.wifi_host1[0] && g_wifi_info.f.config.wifi_host2[0] != 0)
    {
        g_wifi_host = &g_wifi_info.f.config.wifi_host2[0];
        g_wifi_port = (g_wifi_info.f.config.wifi_host2_port)?g_wifi_info.f.config.wifi_host2_port:((g_wifi_info.f.config.enable_https)?443:80);
    }
    else
    {
        g_wifi_host = &g_wifi_info.f.config.wifi_host1[0];
        g_wifi_port = (g_wifi_info.f.config.wifi_host1_port)?g_wifi_info.f.config.wifi_host1_port:((g_wifi_info.f.config.enable_https)?443:80);
    }
}

int WifiTaskInit( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskInit] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0:
            Log("[WifiTaskInit] RESTORE factory defaults.");
            /* Restore a fabrica y espero a que el modulo se reinicie */
            WifiWriteLine("AT+RESTORE");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 100;
            break;
        case 1:
            if(WifiWaitLine("ready", 0, 0, 0, 0) || g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 2:
            /* ECHO OFF */
            WifiWriteLine("ATE0");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 3:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 4:
            /* Version */
            WifiWriteLine("AT+GMR");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 5:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 6:
            /* Check soporte SSL */
            WifiWriteLine("AT+CIPSSLCCONF?");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 7:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                g_wifi_info.status.wifi_ssl_capable = true;
                Log("[WifiTaskInit] Con soporte SSL");
                // Puede faltar
                // AT+CIPSSLSIZE=4096
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                g_wifi_info.status.wifi_ssl_capable = false;
                Log("[WifiTaskInit] Sin soporte SSL");
                //g_wifi_need_upgrade = true;
            }
            break;
        case 8:
        default:
            rc = LOOP;
            break;
    }
    return rc;
}

int WifiTaskAPMode( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskAPMode] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0:
            /* Bajo los servers */
            WifiWriteLine("AT+CIPSERVER=0");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 10;
            g_wifi_info.status.wifi_mode = 0;
            g_wifi_info.status.host_conectado = 0;
            break;
        case 1:
            /* No controlo error */
            if(WifiWaitLine("OK", 0, 0, 0, 0) || g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 2:
            /* Modo AP+Sta */
            WifiWriteLine("AT+CWMODE=3");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 3:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                g_wifi_info.status.wifi_mode = 3;
                g_wifi_info.status.wifi_ok = true;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 4:
            /* MAC e IP */
            WifiWriteLine("AT+CIFSR");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 5:
            if(WifiWaitLine("OK", 0, 0, 0, 0) || g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 6:
            /* Nombre del AP */
            sprintf(g_wifi_cmd, "AT+CWSAP=\"Dom32touch-%s\",\"\",1,0,4,0",
                    &g_wifi_info.status.hw_mac[6]);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 7:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 8:
            /* Multiconexion */
            WifiWriteLine("AT+CIPMUX=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 9:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 10:
            /* Instancias del server */
            WifiWriteLine("AT+CIPSERVERMAXCONN=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 11:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                /* Los mÃ³dulos con firmware viejo no soportan este comando */
                Log("[WifiTaskAPMode] AT+CIPSERVERMAXCONN no soportado.");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 12:
            /* Listen */
            WifiWriteLine("AT+CIPSERVER=1,80");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 13:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                Log("[WifiTaskAPMode] ********** Modo Configuracion **********");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                rc = (-1);
            }
            break;
        case 14:
        default:
            g_wifi_timer_ap = TIMER_AP_VALUE;
            rc = LOOP;
            break;
    }
    return rc;
}

int WifiTaskSTMode( void )
{
    int rc = 0;
    char *ap, *pass;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskSTMode] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0:
            //Log("--> Modo STA.\n");
            /* Bajo los servers */
            WifiWriteLine("AT+CIPSERVER=0");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 100;
            g_wifi_info.status.wifi_mode = 0;
            g_wifi_info.status.host_conectado = 0;
            break;
        case 1:
            if(WifiWaitLine("OK", 0, 0, 0, 0) || g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 2:
            /* Modo Sta */
            WifiWriteLine("AT+CWMODE=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 100;
            break;
        case 3:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                g_wifi_info.status.wifi_ok = true;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                //Log("TIMEOUT esperando OK\n");
                rc = (-1);
            }
            break;
        case 4:
            /* Multiconexion */
            WifiWriteLine("AT+CIPMUX=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 5:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                //Log("TIMEOUT esperando OK\n");
                rc = (-1);
            }
            break;
        case 6:
            /* Instancias del server */
            WifiWriteLine("AT+CIPSERVERMAXCONN=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 7:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskSTMode] AT+CIPSERVERMAXCONN no soportado.");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 8:
            /* MAC e IP */
            WifiWriteLine("AT+CIFSR");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 9:
            if(WifiWaitLine("OK", 0, 0, 0, 0) || g_wifi_task_stm_timeout == 0)
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 10/*8*/:
            /* Listen */
            WifiWriteLine("AT+CIPSERVER=1,80");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 11/*9*/:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                //Log("TIMEOUT esperando OK\n");
                rc = (-1);
            }
            break;
        case 12/*10*/:
            /* Reconnect */
            WifiWriteLine("AT+CWAUTOCONN=1");
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 13/*11*/:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                g_wifi_info.status.wifi_mode = 1;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                //Log("TIMEOUT esperando OK\n");
                rc = (-1);
            }
            break;
        case 14/*12*/:
            /* Si el actual no existe cambio al que exista */
            if(g_wifi_info.status.wifi_ap_select == 1 &&
               g_wifi_info.f.config.wifi_ap1[0] == 0 &&
               g_wifi_info.f.config.wifi_ap2[0] != 0)
            {
                g_wifi_info.status.wifi_ap_select = 2;
            }
            
            if(g_wifi_info.status.wifi_ap_select == 2 &&
               g_wifi_info.f.config.wifi_ap2[0] == 0 &&
               g_wifi_info.f.config.wifi_ap1[0] != 0)
            {
                g_wifi_info.status.wifi_ap_select = 1;
            }
            
            ap = ((g_wifi_info.status.wifi_ap_select == 1)?g_wifi_info.f.config.wifi_ap1:g_wifi_info.f.config.wifi_ap2);
            pass = ((g_wifi_info.status.wifi_ap_select == 1)?g_wifi_info.f.config.wifi_ap1_pass:g_wifi_info.f.config.wifi_ap2_pass);
            if(*ap)
            {
                Log("[WifiTaskSTMode] Conectando con AP %s (%s).", ap, pass);
                /* Connect to AP */
                if(*pass)
                {
                    /* Con clave */
                    sprintf(g_wifi_cmd, "AT+CWJAP=\"%s\",\"%s\"", ap, pass);
                }
                else
                {
                    /* Sin clave */
                    sprintf(g_wifi_cmd, "AT+CWJAP=\"%s\"", ap);
                }
                WifiWriteLine(g_wifi_cmd);
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 300;
                g_wifi_info.status.wifi_conectado = 0;
                g_wifi_info.status.host_conectado = 0;
            }
            else
            {
                /* No hay AP definido */
                Log("[WifiTaskSTMode] ERROR: No hay AP definido.");
                rc = LOOP;
            }
            break;
        case 15/*13*/:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                Log("[WifiTaskSTMode] ********** Modo normal **********");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskSTMode] Error de conexion con AP.");
                Log("[WifiTaskSTMode] Reconectando...");
                g_wifi_info.status.wifi_ap_select = (g_wifi_info.status.wifi_ap_select == 1)?2:1;
                //rc = (-1);
                rc = STMODE;
            }
            break;
            // Puede faltar                
            // AT+CIPSNTPCFG=1,8	 // set SNTP timezone
            // AT+CIPSNTPTIME? // get SNTP time
        default:
            rc = LOOP;
            break;
    }
    return rc;
}

int WifiTaskUpgrade( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskUpgrade] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0:
            Log("[WifiTaskUpgrade] Firmware Upgrade.\n");
            /* Bajo los servers */
            WifiWriteLine("AT+CIPUPDATE");
            g_wifi_task_stm_step = 1;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 1200;
            break;
        case 1:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step = 2;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskUpgrade] Upgrade TIMEOUT.");
                g_wifi_task_stm_step = 0;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        default:
            rc = RESET;
            break;
    }
    return rc;
}

int WifiTaskHttpResp( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskHttpResp] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }
    switch(g_wifi_task_stm_step)
    {
        case 0:
            g_wifi_task_retry = 0;
            if(http_buffer_response.type && 
               http_buffer_response.id >= 0) g_wifi_task_stm_step++;
            else rc = LOOP;
            break;
        case 1: /* Preparando envÃ­o de datos */
            Log("[WifiTaskHttpResp] Enviando");
            sprintf(g_wifi_cmd, "AT+CIPSEND=%d,%d", 
                    http_buffer_response.id, 
                    strlen(http_buffer_response.data));
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 15;
            break;
        case 2: /* Esperando prompt para envÃ­o de datos */
            if(WifiWaitPrompt('>'))
            {
                g_wifi_task_stm_step++;
                g_wifi_recv_error_count = 0;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpResp] TIME-OUT: Esperando PROMPT");
                g_wifi_task_stm_step = 7; /* -> Send ERROR */
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 3: /* Enviando datos */
            WifiWrite(http_buffer_response.data);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 4: /* Esperando Ok de envÃ­o de datos */
            if(WifiWaitLine("SEND OK", 0, 0, 0, 0))
            {
                /* Si es una respuesta saliente sigue un close */
                Log("[WifiTaskHttpResp] SEND Ok");
                g_wifi_task_stm_step ++;
                g_wifi_recv_error_count = 0;
                g_wifi_task_stm_delay = 5;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                /* Si es una respuesta saliente sigue un close */
                Log("[WifiTaskHttpResp] TIME-OUT: Esperando OK de SEND");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 5: /* CLOSE */
            Log("[WifiTaskHttpResp] Cerrando");
            sprintf(g_wifi_cmd, "AT+CIPCLOSE=%d", http_buffer_response.id);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 6: /* Esperando el Ok del CLOSE */
            sprintf(g_wifi_cmd, "%d,CLOSED", http_buffer_response.id);
            if(WifiWaitLine(g_wifi_cmd, "UNLINK", "OK", 0, 0))
            {
                Log("[WifiTaskHttpResp] CLOSE Ok");
                g_wifi_task_stm_step+=2;
                g_wifi_recv_error_count = 0;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpResp] TIME-OUT: Esperando Ok de CLOSE");
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 7: /* Send Error o time-out */
            sprintf(g_wifi_cmd, "AT+CIPCLOSE=%d", http_buffer_response.id);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 15;
            g_wifi_task_stm_timeout = 0;
            break;
        case 8: /* Borro el mensaje de respuesta */
            http_buffer_response.type = 0;
            g_wifi_task_stm_step++;
            g_wifi_recv_error_count = 0;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 0;
            break;
        default:
            rc = LOOP;
            break;
    }
    return rc;
}

int WifiTaskHttpReq( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskHttpReq] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0: /* Conectando */
            g_wifi_task_retry = 0;
            g_wifi_task_stm_step++;
        case 1: /* rtome para retry */
            Log("[WifiTaskHttpReq] Conectando a: %s:%i",  g_wifi_host, g_wifi_port);
            sprintf(g_wifi_cmd, "AT+CIPSTART=%d,\"%s\",\"%s\",%d",
                    http_buffer_output.id,
                    (g_wifi_info.f.config.enable_https)?"SSL":"TCP",
                    g_wifi_host,
                    g_wifi_port);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 30;
            break;
        case 2: /* Esperando Ok de conexiÃ³n */
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpReq] Open Error");
                g_wifi_task_stm_step = 11; /* -> Open ERROR */
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 3: /* Preparando envÃ­o de datos */
            Log("[WifiTaskHttpReq] Enviando");
            sprintf(g_wifi_cmd, "AT+CIPSEND=%d,%d",
                    http_buffer_output.id,
                    strlen(http_buffer_output.data));
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 15;
            break;
        case 4: /* Esperando prompt para envÃ­o de datos */
            if(WifiWaitPrompt('>'))
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpReq] TIME-OUT: Esperando PROMPT");
                g_wifi_task_stm_step = 10; /* -> Send ERROR */
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 5: /* Enviando datos */
            WifiWrite(http_buffer_output.data);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 25;
            break;
        case 6: /* Esperando Ok de envÃ­o de datos */
            if(WifiWaitLine("SEND OK", 0, 0, 0, 0))
            {
                Log("[WifiTaskHttpReq] SEND Ok");
                /* Si es un requerimiento saliente espero respuesta */
                g_wifi_fast_start = true;
                g_wifi_send_error_count = 0;
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = http_buffer_output.timeout;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpReq] TIME-OUT: Esperando Ok de SEND");
                g_wifi_send_error_count = 0;
                g_wifi_task_stm_step = 10; /* Send Error */
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 7: /* Esperando CLOSE del server o datos */
            sprintf(g_wifi_cmd, "%d,CLOSED", http_buffer_output.id);
            if(WifiWaitLine(g_wifi_cmd, "UNLINK", "OK", 0, 0))
            {
                /* Libero el buffer */
                http_buffer_output.type = 0;
                Log("[WifiTaskHttpReq] CLOSE del Server");
                rc = LOOP;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                /* Libero el buffer */
                http_buffer_output.type = 0;
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            break;
        case 8:
            Log("[WifiTaskHttpReq] Cerrando");
            sprintf(g_wifi_cmd, "AT+CIPCLOSE=%d", http_buffer_output.id);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 15;
            break;
        case 9: /* Listo */
            sprintf(g_wifi_cmd, "%d,CLOSED", http_buffer_output.id);
            if(WifiWaitLine(g_wifi_cmd, "UNLINK", "OK", 0, 0))
            {
                Log("[WifiTaskHttpReq] Cerrado");
                rc = LOOP;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                Log("[WifiTaskHttpReq] TIME-OUT: Esperando Ok de CLOSE");
                rc = LOOP;
            }
            break;
        case 10:
            /* Send Error */
            sprintf(g_wifi_cmd, "AT+CIPCLOSE=%d", http_buffer_output.id);
            WifiWriteLine(g_wifi_cmd);
            g_wifi_task_stm_step++;
            g_wifi_task_stm_delay = 15;
            g_wifi_task_stm_timeout = 0;
            break;
        case 11: /* Open Error y Reintentos */
            g_wifi_send_error_count++;
            g_wifi_task_retry++;
            if(g_wifi_task_retry < 2)
            {
                WifiSwitchHost();
                g_wifi_task_stm_step = 1; /* -> Retry */
                g_wifi_task_stm_delay = 15;
                g_wifi_task_stm_timeout = 0;
            }
            else
            {
                g_wifi_task_stm_step++;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
                /* Libero el buffer */
                http_buffer_output.type = 0;
                g_wifi_info.status.host_conectado = 0;
            }
            break;
        default:
            rc = LOOP;
            break;
    }
    return rc;
}

int WifiTaskLoop( void )
{
    int rc = 0;

    if(g_wifi_send_error_count >= 5)
    {
        return (-1);
    }
    else if(g_wifi_recv_error_count >= 5)
    {
        return (-1);
    }
    /* Espero no solicitados */
    else if((rc = WifiWaitLine(0, 0, 0, 0, 0)) > 0)
    {
        return rc;
    }
    else if(g_wifi_info.status.wifi_start_ap)
    {
        g_wifi_info.status.wifi_start_ap = false;
        if(g_wifi_fast_start)
        {
            Log("[WifiTaskLoop] Ir a modo ST.");
            return STMODE;
        }
        else
        {
            Log("[WifiTaskLoop] Ir a modo AP.");
            return APMODE;
        }
    }
    else if(http_buffer_response.type)
    {
        return HTTP_RESP;
    }
    else if(http_buffer_output.type)
    {
        return HTTP_REQ;
    }
    else if(g_wifi_need_upgrade && g_wifi_info.status.wifi_conectado)
    {
        return UPGRADE;
    }
    
    return 0;
}

int WifiTaskListAP( void )
{
    int rc = 0;

    if(g_wifi_task_stm_step != g_wifi_task_stm_step_last)
    {
        Log("[WifiTaskListAP] STM %i -> %i",
                g_wifi_task_stm_step_last,
                g_wifi_task_stm_step);
        g_wifi_task_stm_step_last = g_wifi_task_stm_step;
    }

    switch(g_wifi_task_stm_step)
    {
        case 0:
            //Log("--> List AP.\n");
            WifiWriteLine("AT+CWLAP");
            g_wifi_task_stm_step = 1;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 50;
            break;
        case 1:
            if(WifiWaitLine("OK", 0, 0, 0, 0))
            {
                g_wifi_task_stm_step = 2;
                g_wifi_task_stm_delay = 0;
                g_wifi_task_stm_timeout = 0;
            }
            else if(g_wifi_task_stm_timeout == 0)
            {
                //Log("TIMEOUT esperando Ok\n");
                rc = (-1);
            }
            break;
        default:
            g_wifi_task_stm_step = 0;
            g_wifi_task_stm_delay = 0;
            g_wifi_task_stm_timeout = 0;
            rc = LOOP;
            break;
    }
    return rc;
}

/* *****************************************************************************
 * 
 * ************************************************************************** */
void WiFiInit( void )
{
    g_wifi_task_stm = RESET;
    g_wifi_task_stm_last = INVALID;
    g_wifi_task_stm_delay = 0;
    g_wifi_need_upgrade = false;
    g_wifi_send_error_count = 0;
    g_wifi_recv_error_count = 0;
    g_wifi_fast_start = true/*false*/;

    /* ********************************************************************* */
    /* Configuración de los pines */
    // Tx
    TRISBbits.TRISB8 = 0;
    // Rx
    TRISBbits.TRISB9 = 1;
    // Reset
    TRISBbits.TRISB10 = 0;
    ODCBbits.ODCB10 = 1;
    /* ********************************************************************* */
    /* Configuración de interrupción */
    //    UTXI: UART 3 Error
    //    Priority: 1
        IPC15bits.U3EIP = 1;
    //    Sub Priority: 0
        IPC15bits.U3EIS = 0;
    //    UTXI: UART 3 Transmission
    //    Priority: 1
    //    IPC13bits.U3TXIP = 1;
    //    Sub Priority: 0
    //    IPC13bits.U3TXIS = 0;
    //    URXI: UART 3 Reception
    //    Priority: 1
        IPC14bits.U3RXIP = 1;
    //    Sub Priority: 0
        IPC14bits.U3RXIS = 0;
    /* Configuración del UART */
    /* ********************************************************************* */
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    /* ********************************************************************* */
    // Config PPS
    // unlock PPS
    RPCONbits.IOLOCK = 0;
    // Mapeo de UART3
    RPOR3bits.RP13R = 6;       // UART3:U3TX -> RP13
    RPINR8bits.U3RXR = 14;     // RP14 -> UART3:U3RX
    // lock   PPS
    RPCONbits.IOLOCK = 1; 
    /* ********************************************************************* */
    // System Reg Lock
    SYSKEY = 0x00000000; 
    /* ********************************************************************* */

    
    WifiSerialInit();
    
    g_wifi_host = &g_wifi_info.f.config.wifi_host1[0];
    g_wifi_port = (g_wifi_info.f.config.wifi_host1_port)?g_wifi_info.f.config.wifi_host1_port:((g_wifi_info.f.config.enable_https)?443:80);
}

/* *****************************************************************************
 * 
 * ************************************************************************** */
void WiFiTask( void )
{
    int rc;
    
    if(g_wifi_task_stm_delay) return;
    
    if(g_wifi_task_stm != g_wifi_task_stm_last)
    {
        Log("[WiFiTask] STM %s -> %s",
                task_stm_label[g_wifi_task_stm_last],
                task_stm_label[g_wifi_task_stm]);
        g_wifi_task_stm_last = g_wifi_task_stm;
    }

    switch(g_wifi_task_stm)
    {
        case INVALID:
        case RESET:
			Log("[WiFiTask] RESET");
            CLR_RESET;
            g_wifi_task_stm_timeout = 0;
            g_wifi_task_stm_step = 0;
            g_wifi_read_line_buffer_index = 0;
            g_wifi_read_line_buffer_timer = 0;
            g_wifi_read_line_wait_crlf = true;
            g_wifi_wait_more_data = false;
            g_wifi_task_stm_delay = 30;

            g_wifi_send_error_count = 0;
            g_wifi_recv_error_count = 0;

            g_wifi_info.status.wifi_conectado = 0;
            g_wifi_info.status.wifi_ap_select = 1;
            g_wifi_info.status.wifi_start_ap = true;
            g_wifi_timer_ap = 0;
            g_wifi_info.status.wifi_mode = 0;
            g_wifi_info.status.host_conectado = 0;
            
            WifiTaskSTMSet(START, 50, 0);
            break;
        case START:
			//Log("START\n");
            SET_RESET;
            g_wifi_task_stm_delay = 10;
            WifiTaskSTMSet(CLEAN, 5, 50);
            break;
        case CLEAN:
            /* Me quedo recibiendo un rato la basura de la POST del ESP-02 */
            /* No es basura, pero se ve como basura porque esta a otra velocidad */
            g_wifi_task_stm_delay = 0;
            WifiWaitLine(0, 0, 0, 0, 0);
            if(g_wifi_task_stm_timeout == 0)
            {
                WifiTaskSTMSet(INIT, 0, 0);
            }
            break;
        case INIT:
            rc = WifiTaskInit();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case UPGRADE:
            rc = WifiTaskUpgrade();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case APMODE:
            rc = WifiTaskAPMode();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case STMODE:
            rc = WifiTaskSTMode();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case LISTAP:
            rc = WifiTaskListAP();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case HTTP_RESP:
            rc = WifiTaskHttpResp();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case HTTP_REQ:
            rc = WifiTaskHttpReq();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        case LOOP:
            rc = WifiTaskLoop();
            if(rc > 0)      WifiTaskSTMSet(rc, 0, 0);
            else if(rc < 0) WifiTaskSTMSet(RESET, 0, 0);
            break;
        default:    /* ERROR */
			Log("***** SOFTWARE ERROR ***** RESET *****");
            WifiTaskSTMSet(RESET, 0, 0);
            break;
    }
}

/* *****************************************************************************
 *    Se llama 10 veces por egundo
 * ************************************************************************** */
void WiFiTimer( void )
{
    if(g_wifi_task_stm_delay) g_wifi_task_stm_delay--;
    if(g_wifi_task_stm_timeout) g_wifi_task_stm_timeout--;
    if(g_wifi_timer_ap)
    {
        g_wifi_timer_ap--;
        if(g_wifi_timer_ap == 0)
        {
            /* Vuelvo al modo normal */
            g_wifi_task_stm = STMODE;
        }
    }
    
    if(g_wifi_read_line_buffer_timer) g_wifi_read_line_buffer_timer--;
    
}

/* ************************************************************************* */


void __attribute__ ((vector(_UART3_RX_VECTOR), interrupt(IPL1SOFT))) _UART3_RX( void )
{
    while((U3STAbits.URXDA == 1))
    {
        *rxTail = U3RXREG;

        // Will the increment not result in a wrap and not result in a pure collision?
        // This is most often condition so check first
        if ( ( rxTail    != (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH-1)) &&
             ((rxTail+1) != rxHead) )
        {
            rxTail++;
        } 
        else if ( (rxTail == (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH-1)) &&
                  (rxHead !=  rxQueue) )
        {
            // Pure wrap no collision
            rxTail = rxQueue;
        } 
        else // must be collision
        {
            rxOverflowed = true;
        }

    }

    IFS1CLR= 1 << _IFS1_U3RXIF_POSITION;
}

void __attribute__ ((vector(_UART3_ERR_VECTOR), interrupt(IPL1SOFT))) _UART3_ERR ( void )
{
    if ((U3STAbits.OERR == 1))
    {
        U3STACLR = _U3STA_OERR_MASK; 
    }

     IFS1CLR= 1 << _IFS1_U3EIF_POSITION;
}
