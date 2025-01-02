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

#include "config.h"
#include "sd/fsio.h"

void LogInit(void)
{
    if(g_wifi_info.status.flag_sd_ok)
    {
        FSremove(LOG_FILE_NAME);
    }
    LogMessage("[log] Init Ok");
}

void LogMessage(const char* msg, ...)
{
#ifdef LOG_TO_FILE
    FSFILE *f;
#endif
    va_list arg;
    char str[2048];
    char *p;
    
    va_start(arg, msg);
    vsnprintf(str, 1021, msg, arg);
    va_end(arg);
    strcat(str, "\r\n");
    
    if(g_wifi_info.f.config.debug)
    {
        p = &str[0];
        while(*p)
        {
            while(U2STAbits.UTXBF);
            U2TXREG = *p++;
        }
    }
    
#ifdef LOG_TO_FILE
    if(g_wifi_info.status.flag_sd_ok)
    {
        f = FSfopen(LOG_FILE_NAME, FS_APPEND);
        if(f)
        {
            FSfwrite(str, 1, sizeof(str), f);
            FSfclose(f);
        }
    }
#endif
}
