/***************************************************************************
    Copyright (C) 2017   Walter Pirri

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
#include "clog.h"

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define LOG_BUFFER_LEN 1024
char _log_buffer[LOG_BUFFER_LEN+1];

void LogInit(void)
{
    LogMessage("LOG Init.");
}

void LogMessage(const char* msg, ...)
{
    va_list args;

    va_start (args, msg);
    vsnprintf(_log_buffer, (LOG_BUFFER_LEN-2), msg, args);
    va_end(args);
    strcat(_log_buffer, "\r\n");

    
    printf(_log_buffer);
}
