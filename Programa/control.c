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
#define _IN_CONTROL_C_
#include "control.h"
#undef _IN_CONTROL_C_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "http.h"
#include "log.h"
#include "rtcc.h"

unsigned int g_control_notificar;
unsigned int g_control_init_complete;
unsigned int g_control_update_firmware;
unsigned int g_ctrl_count_reset;

void CTRLNotificarStatus( int time )
{
    if(time == 0) time = 1;
    
    if(time < g_control_notificar || g_control_notificar == 0)
    {
        Log("Notificar en %i segundos", time/10);
        g_control_notificar = time;
    }
}

void CTRLInit( void )
{
    g_control_notificar = 0;
    g_control_init_complete = 0;
    g_control_update_firmware = 0;
    g_ctrl_count_reset = 0;
    
/* Primer notificacion */
    CTRLNotificarStatus(100);
}

void CTRLTask( void )
{
    
}

/* Se llama 10 veces por segundo - 100ms */
void CTRLTimer( void )
{
    if(g_wifi_info.status.host_conectado == 0 && g_control_notificar > 100)
    {
        g_control_notificar = 100;
    }

    if( g_control_notificar > 0 &&
        g_wifi_info.status.wifi_mode == 1 &&
        g_wifi_info.status.wifi_conectado != 0 )
    {
        g_control_notificar--;
        if(g_control_notificar == 0)
        {
            /* Levanto el flag para que
             * en adelante los cambios cuenten */
            g_control_init_complete = 1;
            if( !HTTPNotificarStatus() )
            {
                /* programo un reintento */
                CTRLNotificarStatus(10);
            }
        }
    }
    else if(g_control_notificar == 0)
    {
        /* notifico segun lo configurado */
        CTRLNotificarStatus(g_wifi_info.f.config.report);
    }
    
    /* Control de reset */
    if(g_ctrl_count_reset)
    {
        g_ctrl_count_reset--;
        if(g_ctrl_count_reset == 0)
        {
            ConfigSave();
            Log("[CTRL] RESET.");
            /* The following code illustrates a software Reset */
            // assume interrupts are disabled
            // assume the DMA controller is suspended
            // assume the device is locked
            /* perform a system unlock sequence */
            // starting critical sequence
            SYSKEY = 0x00000000; //write invalid key to force lock
            SYSKEY = 0xAA996655; //write key1 to SYSKEY
            SYSKEY = 0x556699AA; //write key2 to SYSKEY
            /* set SWRST bit to arm reset */
            RSWRSTSET = 1;
            /* read RSWRST register to trigger reset */
            unsigned int dummy; dummy = RSWRST;
            /* prevent any unwanted code execution until reset occurs*/
            while(dummy | 1);
        }
    }
    
    if(g_control_update_firmware && g_wifi_info.status.flag_sd_ok)
    {
        g_control_update_firmware--;
        if(g_control_update_firmware == 0)
        {
            HTTPGetFile(DOWNLOAD_PATH"/"FIRMWARE_FILENAME, NULL);
        }
    }
    
}

void CTRLConfSys(char* in)
{
    char tmp[64];
    bool change = false;
    struct tm tm_time;

    Log("[CTRLConfSys] %s", in);

    if(HTTPGetFormData(in, "UPDATE-FW", tmp))
    {
        Log("********** Actualizar Firmware **********");
        /* Actualizar firmware en 30 seg */
        g_control_update_firmware = 300;
    }
    
    if(HTTPGetFormData(in, "report", tmp))
    {
        change = true;
        g_wifi_info.f.config.report = atoi(tmp) * 10;
        if(g_wifi_info.f.config.report == 0)
        {
            g_wifi_info.f.config.report = 600;
        }
        Log("Keep Alive: %is", g_wifi_info.f.config.report/10);
    }
    
    if(HTTPGetFormData(in, "REPORT", tmp))
    {
        change = true;
        g_wifi_info.f.config.report = atoi(tmp) * 10;
        if(g_wifi_info.f.config.report == 0)
        {
            g_wifi_info.f.config.report = 600;
        }
        Log("Keep Alive: %is", g_wifi_info.f.config.report/10);
    }
    
    if(HTTPGetFormData(in, "TIME", tmp))
    {
        Log("TIME: %s", tmp);
        /*             1111111111
         *   01234567890123456789
         tmp YYYY/MM/DD hh:mm:ss
         */
        if(tmp[4] == '/' && tmp[7] == '/' && tmp[10] == ' ' && 
                tmp[13] == ':' && tmp[16] == ':')
        {
            tmp[4] = 0;
            tmp[7] = 0;
            tmp[10] = 0;
            tmp[13] = 0;
            tmp[16] = 0;
            tmp[19] = 0;
            
            tm_time.tm_year = atoi(&tmp[0]) - 1900;
            tm_time.tm_mon = atoi(&tmp[5]);
            tm_time.tm_mday = atoi(&tmp[8]);
            tm_time.tm_hour = atoi(&tmp[11]);
            tm_time.tm_min = atoi(&tmp[14]);
            tm_time.tm_sec = atoi(&tmp[17]);

            RTCC_TimeSet(&tm_time);
        }
        else
        {
            Log("[CTRLConfSys] Error de formato para TIME");
        }
    }
    
    if(change)
    {
        g_wifi_info.f.config.io_config_default = 0;
        g_wifi_info.status.save_config = 150;
    }
}

void CTRLReset( void )
{
    /* reset en 10 seg */
    Log("[CTRL] RESET solicitado.");
    g_ctrl_count_reset = 100;
}
