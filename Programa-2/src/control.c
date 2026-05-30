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
#include "control.h"

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "log.h"
#include "sd/fsio.h"
#include "config.h"
#include "rtcc.h"
#include "display/display.h"
#include "display/touch.h"
#include "wifi/wifi.h"
#include "misc/boton.h"
#include "misc/strfunc.h"
#include "misc/bitmap.h"
#include "misc/beep.h"

typedef enum
{
    INIT = 0,
    SHOW_POWER,
    WAIT_WIFI,
    SHOW_PAGE,
    SHOW_PAGE_LOOP,
    WIFI_CONFIG,
    SCREEN_SAVER,
    SCREEN_SAVER_LOOP,
    OFFLINE,
    OFFLINE_LOOP,
    DISPLAY_DISABLE,
    DISPLAY_DISABLE_LOOP,
    DISPLAY_ENABLE,
    ERROR
} enum_control_stm;

enum_control_stm control_stm = INIT;
bool status_sd_ok = false;
bool status_wifi_ok = false;
unsigned int progress_bar_x = 0;
unsigned int control_stm_delay = 0;
unsigned int control_screen_saver_count = 0;
char control_screen_filename[FILE_NAME_SIZE+1];
unsigned int control_screen_number;

#define MAX_LINE_LEN 255

void BotonPressed(const char* cmd)
{

}

void TouchTask( void )
{


}

void ShowScreen(const char* filename)
{
    FSFILE* f;
    int rc;
    char line[MAX_LINE_LEN+1];
    unsigned int line_len;
    char str_tmp[256];
    
    char btn_text[BOTON_TEXT_LEN+1];
    char btn_cmd[BOTON_CMD_LEN+1];
    int btn_x;
    int btn_y;
    int btn_w;
    int btn_h;
    int btn_color_f;
    int btn_color_b;
    int btn_color_n;
    int color_fondo = 0;
    char btn_icono[FILE_NAME_SIZE+1];
    int orientacion;

    DisplayOff();

    InitBotones(BotonPressed);

    LogMessage("[ShowScreen] Cargando: %s", filename);
    f = FSfopen(filename, FS_READ);
    if(f)
    {
        do {
            /* Leo una l�nea */
            line_len = 0;
            do {
                rc = FSfread(&line[line_len++], 1, 1, f);
            } while(line[line_len-1] != 0x0d && line[line_len-1] != 0x0a && line_len < MAX_LINE_LEN && rc == 1);
            line[--line_len] = 0;
            if(line_len > 0 && line[0] != '#')
            {
                /* Analizo la linea */
                if( memcmp(line, "BOTON_REDONDO,", 14) == 0 )
                {
                    /* Boton con texto o sin y con o sin icono */
                    if(str_section(line, ',', 1, btn_text) == 0) btn_text[0] = 0;
                    if(str_section(line, ',', 2, btn_cmd) == 0) btn_cmd[0] = 0;
                    if(str_section(line, ',', 3, str_tmp)) btn_x = atoi(str_tmp);
                    else btn_x = 0;
                    if(str_section(line, ',', 4, str_tmp)) btn_y = atoi(str_tmp);
                    else btn_y = 0;
                    if(str_section(line, ',', 5, str_tmp)) btn_w = atoi(str_tmp);
                    else btn_w = 0;
                    if(str_section(line, ',', 6, str_tmp)) btn_h = atoi(str_tmp);
                    else btn_h = 0;
                    if(str_section(line, ',', 7, str_tmp)) btn_color_f = atoi(str_tmp);
                    else btn_color_f = 0;
                    if(str_section(line, ',', 8, str_tmp)) btn_color_b = atoi(str_tmp);
                    else btn_color_b = 0;
                    if(str_section(line, ',', 9, str_tmp)) btn_color_n = atoi(str_tmp);
                    else btn_color_n = 0;
                    if(str_section(line, ',', 10, btn_icono) == 0) btn_icono[0] = 0;
                    if(str_section(line, ',', 11, str_tmp)) orientacion = atoi(str_tmp);
                    else orientacion = 0;
                    
                    BotonAdd(btn_text,
                            btn_cmd,
                            btn_x,btn_y,btn_w,btn_h, 
                            BOTON_BORDE, BOTON_REDONDO,
                            btn_color_f, btn_color_b, btn_color_n,
                            ((btn_icono[0])?btn_icono: NULL), orientacion);
                }
                else if( memcmp(line, "BOTON_CUADRADO,", 15) == 0 )
                {
                    /* Boton con texto o sin y con o sin icono */
                    if(str_section(line, ',', 1, btn_text) == 0) btn_text[0] = 0;
                    if(str_section(line, ',', 2, btn_cmd) == 0) btn_cmd[0] = 0;
                    if(str_section(line, ',', 3, str_tmp)) btn_x = atoi(str_tmp);
                    else btn_x = 0;
                    if(str_section(line, ',', 4, str_tmp)) btn_y = atoi(str_tmp);
                    else btn_y = 0;
                    if(str_section(line, ',', 5, str_tmp)) btn_w = atoi(str_tmp);
                    else btn_w = 0;
                    if(str_section(line, ',', 6, str_tmp)) btn_h = atoi(str_tmp);
                    else btn_h = 0;
                    if(str_section(line, ',', 7, str_tmp)) btn_color_f = atoi(str_tmp);
                    else btn_color_f = 0;
                    if(str_section(line, ',', 8, str_tmp)) btn_color_b = atoi(str_tmp);
                    else btn_color_b = 0;
                    if(str_section(line, ',', 9, str_tmp)) btn_color_n = atoi(str_tmp);
                    else btn_color_n = 0;
                    if(str_section(line, ',', 10, btn_icono) == 0) btn_icono[0] = 0;
                    if(str_section(line, ',', 11, str_tmp)) orientacion = atoi(str_tmp);
                    else orientacion = 0;
                    
                    BotonAdd(btn_text,
                            btn_cmd,
                            btn_x,btn_y,btn_w,btn_h, 
                            BOTON_BORDE, BOTON_CUADRADO,
                            btn_color_f, btn_color_b, btn_color_n,
                            ((btn_icono[0])?btn_icono: NULL), orientacion);
                }
                else if( memcmp(line, "FONDO,", 6) == 0 )
                {
                    if(str_section(line, ',', 1, str_tmp) == 0) break;
                    color_fondo = atoi(str_tmp);
                }
            }
        } while(rc == 1);
        FSfclose(f);
    }
    Clear(color_fondo);
    BotonDraw();

    DisplayOn();
}

void ControlInit( bool sd_ok )
{
    status_sd_ok = sd_ok;
    control_screen_number = 0;
    
}

void ControlTask( void )
{
    
    /* ***** Maquina de estados principal ***** */
    if(control_stm_delay) return;
    
    switch(control_stm)
    {
        case INIT:
            /* Pantalla negra */
            DisplayOff();
            Clear(0);
            control_stm++;
            break;
        case SHOW_POWER:
            /* Imagen centrada */
            DrawBitmap(INIT_SCREEN_BMP, 
                    ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                    ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
            DisplayOn();
            if(status_sd_ok)
            {
                progress_bar_x = 0;
                control_stm++;
            }
            else
            {
                control_stm_delay = 300;
                Beeps(10);
                control_stm = ERROR;
            }
            break;
        case WAIT_WIFI:
            /* Linea de progreso falsa */
            //DrawLineV(DISPLAY_X_SIZE/10, DISPLAY_Y_SIZE-5, 5, BLUE);
            if(WiFiStart() != 0) 
            {
                Beeps(10);
                control_stm = ERROR;
            }
            strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
            control_stm++;
            break;
        case SHOW_PAGE:
            control_screen_saver_count = 0;
            ShowScreen(control_screen_filename);
            control_stm++;
            break;
        case SHOW_PAGE_LOOP:
            if(WiFiMode() == 1)
            {
                if( !strcmp(control_screen_filename, CONFIG_SCREEN_CSV))
                {
                    TouchTask();
                }
                else
                {
                    if(WiFiConectado())
                    {
                        TouchTask();
                    }
                    else
                    {
                        strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
                        control_stm = OFFLINE;
                    }
                }
            }
            else if(WiFiMode() == 3)
            {
                control_stm = WIFI_CONFIG;
            }
            else
            {
                strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
                control_stm = OFFLINE;
            }
            break;
        case WIFI_CONFIG:
            break;
        case SCREEN_SAVER:
            break;
        case SCREEN_SAVER_LOOP:
            break;
        case OFFLINE:
            strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
            ShowScreen(control_screen_filename);
            g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_med;
            control_stm++;
            break;
        case OFFLINE_LOOP:
            if(g_wifi_info.status.wifi_mode == 3)
            {
                control_stm = WIFI_CONFIG;
            }
            else if(g_wifi_info.status.host_conectado)
            {
                strcpy(control_screen_filename, HOME_SCREEN_CSV);
                control_screen_number = 0;
                control_stm = SHOW_PAGE;
            }
            else
            {
                TouchTask();
            }
            break;
        case DISPLAY_DISABLE:
            break;
        case DISPLAY_DISABLE_LOOP:
            break;
        case DISPLAY_ENABLE:
            break;
        default: /* ERROR y no contempladas */

            break;
    } /* switch */
    
}

void ControlTimerInt( void )
{
    if(control_stm_delay) control_stm_delay--;
    
}
