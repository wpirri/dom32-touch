/***************************************************************************
    Copyright (C) 2024   Walter Pirri

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
#include "log.h"

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "config.h"
#include "sd/fsio.h"
#include "rtcc.h"

void LogInit(void)
{
    LogMessage("[log] Init Ok");
}

void WriteToSerial(const char* msg)
{
    while(*msg)
    {
        while(U2STAbits.UTXBF);
        U2TXREG = *msg++;
    }
}


void LogMessage(const char* msg, ...)
{
    FSFILE *f;
    va_list arg;
    char str[2048];
    char *p;
    struct tm stm;
    char str_time[16];
    char str_filename[TOTAL_FILE_SIZE+1];
    
    if( !g_wifi_info.status.debug) return;
    
    va_start(arg, msg);
    vsnprintf(str, 1021, msg, arg);
    va_end(arg);
    strcat(str, "\r\n");

    if(RTCC_TimeGet(&stm))
    {
        sprintf(str_time, "%02i:%02i:%02i - ",
                stm.tm_hour, stm.tm_min, stm.tm_sec);
        sprintf(str_filename, "lg%02i%02i%02i.log",
                stm.tm_year-100, stm.tm_mon+1, stm.tm_mday);
    }
    else
    {
        str_time[0] = 0;
        strcpy(str_filename, "default.log");
    }

    /* Escribir al Serial */
    WriteToSerial(&str_time[0]);
    WriteToSerial(&str[0]);

    /* Escribir a archivo */
    if(g_wifi_info.status.flag_sd_ok)
    {
        f = FSfopen(str_filename, FS_APPEND);
        if(f)
        {
            if(strlen(str_time))
            {
                FSfwrite(str_time, 1, strlen(str_time), f);
            }
            FSfwrite(str, 1, strlen(str), f);
            FSfclose(f);
        }
        else
        {
            WriteToSerial("[log] ERROR: Al abrir el archivo [");
            WriteToSerial(str_filename);
            WriteToSerial("]\r\n");
        }
    }
    else
    {
        WriteToSerial("[log] ERROR: Micro SD no accesible\r\n");
    }
}
