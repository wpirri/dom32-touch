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
#include "beep.h"

#include <xc.h>

#include <stdbool.h>

#include "../config.h"

volatile unsigned char g_beep_len;
volatile unsigned char g_beep_count;
volatile bool g_beep_flag;

void InitBeep( void )
{
    g_beep_flag = 0;
    
}

void TimerBeep( void )
{
    if(g_beep_len)
    {
        g_beep_len--;
        if(g_beep_len == 0)
        {
            if(g_beep_count)
            {
                g_beep_count--;
                if(g_beep_count == 0)
                {
                    g_beep_flag = 0;
                }
                else
                {
                    g_beep_flag = (g_beep_count&0x01)?0:1;
                    g_beep_len = 10;
                }
            }
            else
            {
                g_beep_flag = 0;
            }
        }
    }
    else
    {
        g_beep_flag = 0;
    }
}

void TaskBeep( void )
{
    if(g_beep_flag && g_wifi_config.u.config.debug == 0)
    {
        LATCINV = (1 << 9);
    }
}

void Beep(int len)
{
    g_beep_flag = 1;
    g_beep_len = len;
    g_beep_count = 0;
}

void Beeps(int count)
{
    Beep(20);
    g_beep_count = count*2;
}
