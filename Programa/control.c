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
#include "strfunc.h"
#include "delay.h"

#include "sd/fsio.h"

#include "display/display.h"
#include "boton.h"
#include "bitmap.h"

#define TOUCH_DELAY 100

typedef enum
{
    INIT = 0,
    SHOW_POWER,
    WAIT_WIFI,
    SHOW_PAGE,
    LOOP,
    SCREEN_SAVER,
    ON_TOUCH,
    ERROR
} control_stm;

unsigned int g_control_notificar;
unsigned int g_control_init_complete;
unsigned int g_control_update_firmware;
unsigned int g_ctrl_count_reset;
unsigned int g_ctrl_current_screen;
control_stm g_ctrl_stm;
unsigned int g_ctrl_stm_delay;
char g_show_filename[FILE_NAME_SIZE+1];

void ShowScreen(const char* filename);
void TouchTask( void );
void BotonPressed(const char* name);

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
    g_ctrl_stm = INIT;
    g_ctrl_stm_delay = 0;
    g_ctrl_current_screen = 0;
    strcpy(g_show_filename, "home.csv");
    
/* Primer notificacion */
    CTRLNotificarStatus(100);
}

void CTRLTask( void )
{
    static int x = 0;
    
    if(g_ctrl_stm_delay) return;
    switch(g_ctrl_stm)
    {
        case INIT:
            /* Pantalla negra */
            Clear(0);
            g_ctrl_stm++;
            break;
        case SHOW_POWER:
            /* Centro imagen de 100x100 */
            DrawBitmap("power.bmp", ((DISPLAY_X_SIZE/2)-50), ((DISPLAY_Y_SIZE/2)-50) );
            x = 0;
            g_ctrl_stm++;
            break;
        case WAIT_WIFI:
            if(g_wifi_info.status.wifi_ok)
            {
                g_ctrl_stm++;
            }
            else if(x < DISPLAY_X_SIZE)
            {
                /* Linea de progreso falsa */
                DrawLineV(x, DISPLAY_Y_SIZE-5, 5, BLUE);
                x++;
                g_ctrl_stm_delay = 1;
            }
            else
            {
                g_ctrl_stm = ERROR;
            }

            break;
        case SHOW_PAGE:
            ShowScreen(g_show_filename);
            g_ctrl_stm++;
            break;
        case LOOP:
            TouchTask();
            break;
        case SCREEN_SAVER:

            break;
        case ON_TOUCH:

            break;
        case ERROR:
        default:
            Clear(0);
            DrawText("Error", CENTER, DISPLAY_Y_SIZE/2, 4, RED, BLACK);
            break;
    }
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
    
    if(g_ctrl_stm_delay) g_ctrl_stm_delay--;
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





void BotonPressed(const char* cmd)
{
    Log("[BotonPressed] CMD: %s", cmd);
    if( !memcmp(cmd, "HOME", 4))
    {
        strcpy(g_show_filename, "home.csv");
        g_ctrl_current_screen = 0;
        g_ctrl_stm = SHOW_PAGE;
    }
    else if( !memcmp(cmd, "MENU", 4))
    {
        strcpy(g_show_filename, "menu.csv");
        g_ctrl_current_screen = 0;
        g_ctrl_stm = SHOW_PAGE;
    }
    else if( !memcmp(cmd, "NEXT", 4))
    {
        if(g_ctrl_current_screen < 9)
        {
            g_ctrl_current_screen++;
            sprintf(g_show_filename, "screen%u.csv", g_ctrl_current_screen);
            g_ctrl_stm = SHOW_PAGE;
        }
    }
    else if( !memcmp(cmd, "PREV", 4))
    {
        if(g_ctrl_current_screen > 0)
        {
            g_ctrl_current_screen--;
            sprintf(g_show_filename, "screen%u.csv", g_ctrl_current_screen);
            g_ctrl_stm = SHOW_PAGE;
        }
    }
    else if( !memcmp(cmd, "WIFI", 4))
    {
        strcpy(g_show_filename, "wifi.csv");
        g_ctrl_stm = SHOW_PAGE;
    }
    else if( !memcmp(cmd, "RESET", 5))
    {
        CTRLReset();
    }
    else if( !memcmp(cmd, "UPGRADE", 7))
    {
        g_control_update_firmware = 300;
    }
    else if( !memcmp(cmd, "SWITCH:", 7))
    {
        HTTPCommandSwitch(&cmd[7]);
    }
}

void TouchTask( void )
{
    static bool touch_pressed = false;
    static unsigned int touch_counter = 0;
    unsigned int touch_x, touch_y;

    if(TouchIsPressed( &touch_x, &touch_y, NULL ))
    {
        if(touch_counter < TOUCH_DELAY)
        {
            touch_counter++;
            
            if(touch_counter == TOUCH_DELAY && !touch_pressed)
            {
                touch_pressed = true;
                Log("[TOUCH] X: %u y: %u", touch_x, touch_y);
                BotonTask(touch_x, touch_y);
            }
        }
    }
    else
    {
        if(touch_counter)
        {
            touch_counter--;
            if(touch_counter == 0)
            {
                touch_pressed = false;
            }
        }
    }
}

#define MAX_LINE_LEN 255

void ShowScreen(const char* filename)
{
    FSFILE* f;
    int rc;
    char line[MAX_LINE_LEN+1];
    unsigned int line_len;
    char str_tmp[256];
    
    char btn_name[32];
    char btn_cmd[64];
    int btn_x;
    int btn_y;
    int btn_w;
    int btn_h;
    int btn_color_f;
    int btn_color_b;
    int btn_color_n;
    char btn_icono[FILE_NAME_SIZE+1];

    Clear(0);
    InitBotones(BotonPressed);

    Log("[ShowScreen] Cargando: %s", filename);
    f = FSfopen(filename, FS_READ);
    if(f)
    {
        do {
            /* Leo una línea */
            line_len = 0;
            do {
                rc = FSfread(&line[line_len++], 1, 1, f);
            } while(line[line_len-1] != 0x0d && line[line_len-1] != 0x0a && line_len < MAX_LINE_LEN && rc == 1);
            line[--line_len] = 0;
            if(line_len > 0 && line[0] != '#')
            {
                /* Analizo la línea */
                if( !memcmp(line, "BOTON1", 6) )
                {
                    /* Boton con texto y con o sin icono */
                    if(str_section(line, ',', 1, btn_name) == 0) break;
                    if(str_section(line, ',', 2, btn_cmd) == 0) break;
                    if(str_section(line, ',', 3, str_tmp) == 0) break;
                    btn_x = atoi(str_tmp);
                    if(str_section(line, ',', 4, str_tmp) == 0) break;
                    btn_y = atoi(str_tmp);
                    if(str_section(line, ',', 5, str_tmp) == 0) break;
                    btn_w = atoi(str_tmp);
                    if(str_section(line, ',', 6, str_tmp) == 0) break;
                    btn_h = atoi(str_tmp);
                    if(str_section(line, ',', 7, str_tmp) == 0) break;
                    btn_color_f = atoi(str_tmp);
                    if(str_section(line, ',', 8, str_tmp) == 0) break;
                    btn_color_b = atoi(str_tmp);
                    if(str_section(line, ',', 9, str_tmp) == 0) break;
                    btn_color_n = atoi(str_tmp);
                    if(str_section(line, ',', 10, btn_icono) == 0)
                    {
                        btn_icono[0] = 0;
                    }
                    BotonAdd(btn_name,
                            btn_cmd,
                            btn_x,btn_y,btn_w,btn_h, 
                            btn_color_f, btn_color_b, btn_color_n,
                            ((strlen(btn_icono))?btn_icono: NULL) );
                }
            }
        } while(rc == 1);
        FSfclose(f);
    }
    BotonDraw();
    
}