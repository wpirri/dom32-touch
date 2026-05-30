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
#include "wifi.h"

#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../defines.h"
#include "uart3.h"
#include "../log.h"

#define WIFI_RESET_SetHigh()    (LATBSET=(1<<10))
#define WIFI_RESET_SetLow()     (LATBCLR=(1<<10))
#define UART_WRITE              UART3_Write
#define UART_OVERFLOW           UART3_Overflow
#define UART_ISRXREADY          UART3_IsRxReady
#define UART_READ               UART3_Read

volatile unsigned int g_wifi_c_timer_count;
int g_wifi_c_status;
int g_wifi_c_mode;
int g_wifi_c_conectado;


void WifiWrite( const char *buffer )
{
    if(buffer)
    {
        LogMessage("[WIFI] WifiWrite [%-.100s]", buffer);
        while(*buffer)
        {
            UART_WRITE((uint8_t)*buffer);
            buffer++;
        }
    }
}

void WifiWriteLine( const char *line )
{
    if(line)
    {
        LogMessage("[WIFI] WifiWriteLine [%-.100s]", line);
        while(*line)
        {
            UART_WRITE((uint8_t)*line);
            line++;
        }
    }
    UART_WRITE('\r');
    UART_WRITE('\n');
}

int WifiReadAt( char *data, unsigned int max_data, char at, int to )
{
    unsigned int read_len = 0;
    char ch = at+1;
    
    if(UART_OVERFLOW()) return (-1);

    g_wifi_c_timer_count = to;
    do {
        CLRWDT();
        while( UART_ISRXREADY() && ch != at && read_len < max_data && g_wifi_c_timer_count > 0)
        {
            ch = UART_READ();
            if(data && ch != 0x0d && ch != 0x0a)
            {
                *data = ch;
                data++;
            }
            read_len++;
        }
    } while (ch != at && read_len < max_data && g_wifi_c_timer_count > 0);

    if(g_wifi_c_timer_count == 0) return (-1);

    if(data) *data = 0;
    return read_len;
}

int WifiReadCount( char *data, unsigned int count, int to )
{
    unsigned int read_count = 0;
    char ch;
    
    if(UART_OVERFLOW()) return (-1);

    g_wifi_c_timer_count = to;
    do {
        CLRWDT();
        while( UART_ISRXREADY() && read_count < count && g_wifi_c_timer_count > 0)
        {
            ch = UART_READ();
            if(data)
            {
                *data = ch;
                data++;
            }
            read_count++;
        }
    } while (read_count < count && g_wifi_c_timer_count > 0);
    
    if(g_wifi_c_timer_count == 0) return (-1);

    return read_count;
}

/* ************************************************************************* */

void WiFiInit( void )
{
    g_wifi_c_timer_count = 0;
    g_wifi_c_status = 0;
    g_wifi_c_mode = 0;
    g_wifi_c_conectado = 0;
    UART3_Init();
}

void WiFiTimerInt( void )
{
    if(g_wifi_c_timer_count) g_wifi_c_timer_count--;
}

int WiFiStatus( void )
{
    return g_wifi_c_status;
}

int WiFiMode( void )
{
    return g_wifi_c_mode;
}

int WiFiConectado( void )
{
    return g_wifi_c_conectado;
}

void WiFiWait(int t)
{
    g_wifi_c_timer_count = t;
    while(g_wifi_c_timer_count > 0)
    {
        CLRWDT();
    }
}

int WiFiCommand(const char* cmd, const char* wait, int to)
{
    char buffer[256];
    
    g_wifi_c_timer_count = to;
    WifiWriteLine(cmd);
    do
    {
        if(WifiReadAt(buffer, 255, '\n', g_wifi_c_timer_count) < 0)
        {
            LogMessage("[WIFI] TIMEOUT: Esperando [%s]", wait);
            return (-1);
        }
        if( !strstr(buffer, wait))
        {
            LogMessage("[WIFI] %s -> [%s]", cmd, buffer);
        }
    } while( !strstr(buffer, wait));
    LogMessage("[WIFI] %s -> %s", cmd, wait);
    return 0;
}

int WiFiStart( void )
{
    LogMessage("[WIFI] Start");
    /* Reseteo el módulo. Bajo y subo el pin de reset */
    WIFI_RESET_SetLow();
    WiFiWait(50);
    WIFI_RESET_SetHigh();
    /* Leo y descarto lo que pueda tirar cuando levanta */
    WifiReadCount(NULL, 9999, 100);
    /* Trato de volverlo a fábrica y espero ready 10 seg */
    if(WiFiCommand("AT+RESTORE", "ready", 1000) < 0) return (-1);
    /* ECHO OFF */
    if(WiFiCommand("ATE0", "OK", 150) < 0) return (-1);
    /* Version */
    if(WiFiCommand("AT+GMR", "OK", 300) < 0) return (-1);
    /* Check soporte SSL */
    if(WiFiCommand("AT+CIPSSLCCONF?", "OK", 150) < 0) return (-1);
    return 0;
}
