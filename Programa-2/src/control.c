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
    SCREEN_INIT = 0,
    SCREEN_SHOW_PAGE,
    SCREEN_SHOW_PAGE_LOOP,
    SCREEN_WIFI_CONFIG,
    SCREEN_SAVER,
    SCREEN_SAVER_LOOP,
    SCREEN_OFFLINE,
    SCREEN_OFFLINE_LOOP,
    SCREEN_ERROR,
    SCREEN_ERROR_FATAL,
    SCREEN_ERROR_FATAL_LOOP
} enum_control_screen_stm;

enum_control_screen_stm control_screen_stm = SCREEN_INIT;
bool status_sd_ok;
bool status_wifi_ok;
unsigned int control_screen_stm_delay;
unsigned int control_screen_saver_count;
char control_screen_filename[FILE_NAME_SIZE+1];
unsigned int control_screen_number;

typedef enum
{
    WIFI_INIT = 0,
    WIFI_MODO_AP,
    WIFI_MODO_AP_OK,
    WIFI_MODO_ST,
    WIFI_MODO_ST_OK,
    WIFI_CONECTAR_A_AP,
    WIFI_CONECTADO_A_AP,
    WIFI_ERROR,
    WIFI_ERROR_FATAL,
    WIFI_ERROR_FATAL_LOOP
} enum_control_wifi_stm;

enum_control_wifi_stm control_wifi_stm = WIFI_INIT;
unsigned int control_wifi_stm_delay;

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
    status_wifi_ok = false;
    control_screen_number = 0;
    control_screen_stm_delay = 0;
    control_screen_saver_count = 0;
    
    control_wifi_stm_delay = 500;
}

void Control_Screen_Task( void )
{
    
    /* ***** Maquina de estados de pantallas ***** */
    if(control_screen_stm_delay) return;
    
    switch(control_screen_stm)
    {
        case SCREEN_INIT:
            /* Pantalla negra */
            DisplayOff();
            Clear(0);
            DisplayBrillo(g_wifi_info.f.config.brillo_max);
            if(status_sd_ok)
            {
                /* Imagen centrada */
                DrawBitmap(INIT_SCREEN_BMP, 
                        ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                        ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
                DisplayOn();
                control_screen_stm_delay = 250;
                control_screen_stm = SCREEN_OFFLINE;
            }
            else
            {
                control_screen_stm = SCREEN_ERROR_FATAL;
            }
            break;
        case SCREEN_SHOW_PAGE:
            control_screen_saver_count = 0;
            ShowScreen(control_screen_filename);
            control_screen_stm++;
            break;
        case SCREEN_SHOW_PAGE_LOOP:
            if(WiFiMode() == WIFI_MODE_ST)
            {
                if(WiFiOnLine())
                {
                    TouchTask();
                }
                else
                {
                    control_screen_stm = SCREEN_OFFLINE;
                }
            }
            else if(WiFiMode() == WIFI_MODE_AP_ST || WiFiMode() == WIFI_MODE_AP)
            {
                control_screen_stm = SCREEN_WIFI_CONFIG;
            }
            else
            {
                control_screen_stm = SCREEN_OFFLINE;
            }
            break;
        case SCREEN_WIFI_CONFIG:
            if(WiFiMode() == WIFI_MODE_AP_ST || WiFiMode() == WIFI_MODE_AP)
            {
                Clear(0);
                strcpy(control_screen_filename, WIFI_SCREEN_BMP);
                DrawBitmap(control_screen_filename, 
                        ((DISPLAY_X_SIZE/2)-(GetBitmapW(control_screen_filename)/2)), 
                        ((DISPLAY_Y_SIZE/2)-(GetBitmapH(control_screen_filename)/2)) );
                control_screen_stm_delay = 20;
            }
            else
            {
                control_screen_stm = SCREEN_OFFLINE;
            }
            break;
        case SCREEN_SAVER:
            DisplayOff();
            /* Imagen centrada */
            DrawBitmap(INIT_SCREEN_BMP, 
                    ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                    ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
            DisplayBrillo(g_wifi_info.f.config.brillo_min);
            DisplayOn();
            control_screen_stm++;
            break;
        case SCREEN_SAVER_LOOP:
            if(WiFiOnLine())
            {
                TouchTask();
            }
            else
            {
                control_screen_stm = SCREEN_OFFLINE;
            }
            break;
        case SCREEN_OFFLINE:
            strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
            ShowScreen(control_screen_filename);
            DisplayBrillo(g_wifi_info.f.config.brillo_med);
            control_screen_stm++;
            break;
        case SCREEN_OFFLINE_LOOP:
            if(WiFiMode() == WIFI_MODE_AP_ST || WiFiMode() == WIFI_MODE_AP)
            {
                control_screen_stm = SCREEN_WIFI_CONFIG;
            }
            else if(WiFiOnLine())
            {
                strcpy(control_screen_filename, HOME_SCREEN_CSV);
                control_screen_number = 0;
                control_screen_stm = SCREEN_SHOW_PAGE;
            }
            else
            {
                TouchTask();
            }
            break;
        case SCREEN_ERROR:
            DisplayOff();
            DisplayBrillo(g_wifi_info.f.config.brillo_med);
            Clear(RED);
            DisplayOn();
            control_screen_stm_delay = 250;
            control_screen_stm = SCREEN_INIT;
            break;
        case SCREEN_ERROR_FATAL:
            DisplayOff();
            DisplayBrillo(g_wifi_info.f.config.brillo_med);
            Clear(BLUE);
            DrawText("ERROR", CENTER, DISPLAY_Y_SIZE/2, 4, WHITE, BLUE);
            DisplayOn();
            control_screen_stm++;
            break;
        case SCREEN_ERROR_FATAL_LOOP:
            break;
        default: /*  */
            control_screen_stm = SCREEN_ERROR_FATAL;
            break;
    } /* switch */
    
}

void Control_WiFi_Task(void)
{
    WiFiCheckUnsol();
    
    if(control_wifi_stm_delay)return;

    switch(control_wifi_stm)
    {
        case WIFI_INIT:
            if(WiFiStart() == 0)
            {
                control_wifi_stm = WIFI_MODO_AP;
            }
            else
            {
                control_wifi_stm_delay = 500;
            }
            break;
        case WIFI_MODO_AP:
            if(WiFiSetMode(WIFI_MODE_AP) == 0)
            {
                control_wifi_stm++;
            }
            else
            {
                control_wifi_stm = WIFI_ERROR;
            }
            break;
        case WIFI_MODO_AP_OK:
            break;
        case WIFI_MODO_ST:
            if(WiFiSetMode(WIFI_MODE_ST) == 0)
            {
                control_wifi_stm++;
            }
            else
            {
                control_wifi_stm = WIFI_ERROR;
            }
            break;
        case WIFI_MODO_ST_OK:
            break;
        case WIFI_CONECTAR_A_AP:
            break;
        case WIFI_CONECTADO_A_AP:
            break;
        case WIFI_ERROR:
            break;
        case WIFI_ERROR_FATAL:
            break;
        case WIFI_ERROR_FATAL_LOOP:
            break;
        default:
            break;
    }    
}

void ControlTimerInt( void )
{
    if(control_screen_stm_delay) control_screen_stm_delay--;
    if(control_wifi_stm_delay) control_wifi_stm_delay--;
    
}
