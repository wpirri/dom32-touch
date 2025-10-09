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
#include "beep.h"

#define TOUCH_DELAY 100
#define RETURN_TO_HOME 600
#define BOTON_BORDE 6
#define BOTON_REDONDO 15
#define BOTON_CUADRADO 0
#define HOME_SCREEN_CSV    "screen0.csv"
#define CONFIG_SCREEN_CSV  "config.csv"
#define OFFLINE_SCREEN_CSV "offline.csv"
#define INIT_SCREEN_BMP    "power.bmp"
#define WIFI_SCREEN_BMP    "wifi.bmp"

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
} control_stm;

typedef enum
{
    US_INIT = 0,
    US_WAITH,
    US_GET_LIST,
    US_GET_LIST_WAITH,
    US_GET_LIST_END,
    US_OPEN_LIST_FILES,
    US_GET_LIST_FILES,
    US_GET_LIST_FILES_WAITH,
    US_GET_LIST_FILES_NEXT,
    US_GET_LIST_FILES_END,
    US_ERROR
} update_screen_stm;

unsigned int g_control_init_complete;
unsigned int g_control_update_firmware;
unsigned int g_ctrl_count_reset;
unsigned int g_ctrl_count_return_to_home;

unsigned int g_ctrl_current_screen;
control_stm g_ctrl_stm;
control_stm g_ctrl_stm_ant;
unsigned int g_ctrl_stm_delay;
unsigned int g_screen_saver_count;
unsigned int g_update_screen_timeout_count;
char g_show_filename[FILE_NAME_SIZE+1];
update_screen_stm g_us_last_stm;
update_screen_stm g_us_stm;
unsigned int g_us_waith;
unsigned char g_us_list_item;
FSFILE* g_us_list_file;

void ShowScreen(const char* filename);
void TouchTask( void );
void BotonPressed(const char* name);
void UpdateScreenTask( void );

void CTRLNotificarStatus( int time )
{
    if(time == 0)
    {
        g_wifi_info.status.control_notificar = g_wifi_info.f.config.report;
    }
    else if(time < g_wifi_info.status.control_notificar || g_wifi_info.status.control_notificar == 0)
    {
        g_wifi_info.status.control_notificar = time;
    }
    LogMessage("Notificar en %i segundos", g_wifi_info.status.control_notificar/10);
}

void CTRLInit( void )
{
    g_wifi_info.status.control_notificar = 0;
    g_control_init_complete = 0;
    g_ctrl_count_reset = 0;
    g_control_update_firmware = 0;
    g_ctrl_stm = INIT;
    g_ctrl_stm_ant = ERROR;
    g_ctrl_stm_delay = 0;
    g_ctrl_current_screen = 0;
    g_screen_saver_count = 0;
    g_update_screen_timeout_count = 0;
    strcpy(g_show_filename, HOME_SCREEN_CSV);
    g_ctrl_count_return_to_home = 0;
    g_us_stm = US_INIT;
    g_us_last_stm = US_ERROR;
    g_us_waith = 0;
    g_us_list_item = 0;
    g_us_list_file = NULL;
/* Primer notificacion */
    CTRLNotificarStatus(100);
}

void CTRLTask( void )
{
    static int x = 0;
    
    if(g_ctrl_stm_delay) return;
    
    if(g_ctrl_stm != g_ctrl_stm_ant)
    {
        LogMessage("[CTRLTask] STM %i -> %i", g_ctrl_stm_ant, g_ctrl_stm);
        g_ctrl_stm_ant = g_ctrl_stm;
    }
    
    switch(g_ctrl_stm)
    {
        case INIT:
            /* Pantalla negra */
            g_wifi_info.status.brillo = 0;
            Clear(0);
            g_ctrl_stm++;
            break;
        case SHOW_POWER:
            /* Imagen centrada */
            DrawBitmap(INIT_SCREEN_BMP, 
                    ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                    ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
            g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_max;
            if(g_wifi_info.status.flag_sd_ok)
            {
                x = 0;
                g_ctrl_stm++;
            }
            else
            {
                g_ctrl_stm_delay = 30;
                Beeps(10);
                g_ctrl_stm = ERROR;
            }
            break;
        case WAIT_WIFI:
            if(g_wifi_info.status.wifi_mode == 1)
            {
                /* Modo Normal */
                if(g_wifi_info.status.host_conectado)
                {
                    strcpy(g_show_filename, HOME_SCREEN_CSV);
                    g_ctrl_current_screen = 0;
                    g_ctrl_stm = SHOW_PAGE;
                }
                else
                {
                    strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
                    g_ctrl_stm = OFFLINE;
                }
                Beeps(3);
            }
            else if(g_wifi_info.status.wifi_mode == 3)
            {
                /* Modo Configuracion */
                g_ctrl_stm = WIFI_CONFIG;
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
                Beeps(10);
                g_ctrl_stm = ERROR;
            }
            break;
        case SHOW_PAGE:
            g_screen_saver_count = 0;
            ShowScreen(g_show_filename);
            g_ctrl_stm++;
            break;
        case SHOW_PAGE_LOOP:
            if(g_wifi_info.status.wifi_mode == 1)
            {
                if( !strcmp(g_show_filename, CONFIG_SCREEN_CSV))
                {
                    TouchTask();
                }
                else
                {
                    if(g_wifi_info.status.host_conectado)
                    {
                        TouchTask();
                    }
                    else
                    {
                        strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
                        g_ctrl_stm = OFFLINE;
                    }
                }
            }
            else if(g_wifi_info.status.wifi_mode == 3)
            {
                g_ctrl_stm = WIFI_CONFIG;
            }
            break;
        case WIFI_CONFIG:
            if(g_wifi_info.status.wifi_mode == 3)
            {
                Clear(0);
                strcpy(g_show_filename, WIFI_SCREEN_BMP);
                DrawBitmap(g_show_filename, 
                        ((DISPLAY_X_SIZE/2)-(GetBitmapW(g_show_filename)/2)), 
                        ((DISPLAY_Y_SIZE/2)-(GetBitmapH(g_show_filename)/2)) );
                g_ctrl_stm_delay = 20;
                Beeps(2);
                g_screen_saver_count = 0;
            }
            else
            {
                if(g_wifi_info.status.host_conectado)
                {
                    strcpy(g_show_filename, HOME_SCREEN_CSV);
                    g_ctrl_stm = SHOW_PAGE;
                }
                else
                {
                    strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
                    g_ctrl_stm = OFFLINE;
                }
                g_ctrl_current_screen = 0;
            }
            break;
        case SCREEN_SAVER:
            g_wifi_info.status.brillo = 0;
            Clear(0);
            DrawBitmap(INIT_SCREEN_BMP, 
                    ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                    ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
            g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_min;
            g_ctrl_stm++;
            break;
        case SCREEN_SAVER_LOOP:
            if(TouchIsPressed( NULL, NULL, NULL ))
            {
                strcpy(g_show_filename, HOME_SCREEN_CSV);
                g_ctrl_current_screen = 0;
                g_ctrl_stm = SHOW_PAGE;
            }
            else if(g_wifi_info.status.host_conectado == 0)
            {
                g_ctrl_stm = OFFLINE;
            }
            break;
        case OFFLINE:
            strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
            ShowScreen(g_show_filename);
            g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_med;
            g_ctrl_stm++;
            break;
        case OFFLINE_LOOP:
            if(g_wifi_info.status.wifi_mode == 3)
            {
                g_ctrl_stm = WIFI_CONFIG;
            }
            else if(g_wifi_info.status.host_conectado)
            {
                strcpy(g_show_filename, HOME_SCREEN_CSV);
                g_ctrl_current_screen = 0;
                g_ctrl_stm = SHOW_PAGE;
            }
            else
            {
                TouchTask();
            }
            break;
        case DISPLAY_DISABLE:
            strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
            ShowScreen(g_show_filename);
            g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_med;
            g_ctrl_stm++;
            break;
        case DISPLAY_DISABLE_LOOP:
            break;
        case DISPLAY_ENABLE:
            g_ctrl_stm = OFFLINE;
            break;
        case ERROR:
        default:
            Clear(0);
            DrawText("Error", CENTER, DISPLAY_Y_SIZE/2, 4, RED, BLACK);
            break;
    }
    
    UpdateScreenTask();
}

/* Se llama 10 veces por segundo - 100ms */
void CTRLTimer( void )
{
    if( !strcmp(g_show_filename, HOME_SCREEN_CSV))
    {
        g_ctrl_count_return_to_home = 0;
    }
    else if( g_wifi_info.status.host_conectado && (g_ctrl_stm == SHOW_PAGE_LOOP) )
    {
        if(g_ctrl_count_return_to_home < RETURN_TO_HOME)
        {
            g_ctrl_count_return_to_home++;
            if(g_ctrl_count_return_to_home == RETURN_TO_HOME)
            {
                strcpy(g_show_filename, HOME_SCREEN_CSV);
                g_ctrl_current_screen = 0;
                g_ctrl_stm = SHOW_PAGE;
            }
        }
    }
    
    if(g_wifi_info.status.host_conectado == 0 && g_wifi_info.status.control_notificar > (g_wifi_info.f.config.report/10))
    {
        g_wifi_info.status.control_notificar = (g_wifi_info.f.config.report/10);
    }

    if( g_wifi_info.status.control_notificar > 0 &&
        g_wifi_info.status.wifi_mode == 1 &&
        g_wifi_info.status.wifi_conectado_ok != 0 )
    {
        g_wifi_info.status.control_notificar--;
        if(g_wifi_info.status.control_notificar == 0)
        {
            /* Levanto el flag para que
             * en adelante los cambios cuenten */
            g_control_init_complete = 1;
            HTTPNotificarStatus();
            /* programo un reintento, si hay respuesta Ok luego se extiende el tiempo */
            g_wifi_info.status.control_notificar = (g_wifi_info.f.config.report/10);
        }
    }
    else if(g_wifi_info.status.control_notificar == 0)
    {
        /* notifico segun lo configurado */
        g_wifi_info.status.control_notificar = g_wifi_info.f.config.report;
    }
    
    /* Control de reset */
    if(g_ctrl_count_reset && (g_ctrl_stm == SHOW_PAGE_LOOP || g_ctrl_stm == SCREEN_SAVER_LOOP) )
    {
        g_ctrl_count_reset--;
        if(g_ctrl_count_reset == 0)
        {
            ConfigSave();
            LogMessage("[CTRL] RESET.");
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
            if(HTTPGetFile(DOWNLOAD_PATH"/"FIRMWARE_FILENAME, NULL) <= 0 )
            {
                UpdateFirmware();
            }
        }
    }
    
    if(g_ctrl_stm_delay) g_ctrl_stm_delay--;
    
    /* Screen saver */
    if( g_wifi_info.f.config.screen_saver_time > 0 && 
        g_screen_saver_count < (g_wifi_info.f.config.screen_saver_time * 10) &&
        g_ctrl_stm == SHOW_PAGE_LOOP )
    {
        g_screen_saver_count++;
        if(g_screen_saver_count >= (g_wifi_info.f.config.screen_saver_time * 10) )
        {
            g_ctrl_stm = SCREEN_SAVER;
        }
    }
    
    if(g_update_screen_timeout_count)
    {
        g_update_screen_timeout_count--;
        if(g_update_screen_timeout_count == 0)
        {
            LogMessage("TIME-OUT procesando listado de archivos para download");
            g_us_stm = US_ERROR;
        }
    }
    
    if(g_us_waith > 0)
    {
        g_us_waith--;
    }
}

void CTRLConfSys(char* in)
{
    char tmp[64];
    bool change = false;
    struct tm tm_time;

    LogMessage("[CTRLConfSys] %s", in);

    if(HTTPGetFormData(in, "UPDATE-FW", tmp))
    {
        LogMessage("********** Actualizar Firmware **********");
        UpdateFirmware();
    }
    
    if(HTTPGetFormData(in, "report", tmp))
    {
        change = true;
        g_wifi_info.f.config.report = atoi(tmp) * 10;
        if(g_wifi_info.f.config.report == 0)
        {
            g_wifi_info.f.config.report = 600;
        }
        LogMessage("Keep Alive: %is", g_wifi_info.f.config.report/10);
    }
    
    if(HTTPGetFormData(in, "REPORT", tmp))
    {
        change = true;
        g_wifi_info.f.config.report = atoi(tmp) * 10;
        if(g_wifi_info.f.config.report == 0)
        {
            g_wifi_info.f.config.report = 600;
        }
        LogMessage("Keep Alive: %is", g_wifi_info.f.config.report/10);
    }
    
    if(HTTPGetFormData(in, "TIME", tmp))
    {
        LogMessage("TIME: %s", tmp);
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
            tm_time.tm_mon = atoi(&tmp[5]) - 1;
            tm_time.tm_mday = atoi(&tmp[8]);
            tm_time.tm_hour = atoi(&tmp[11]);
            tm_time.tm_min = atoi(&tmp[14]);
            tm_time.tm_sec = atoi(&tmp[17]);

            RTCC_TimeSet(&tm_time);
        }
        else
        {
            LogMessage("[CTRLConfSys] Error de formato para TIME");
        }
    }
    
    if(change)
    {
        g_wifi_info.f.config.io_config_default = 0;
        g_wifi_info.status.save_config = 150;
    }
}

void CTRLReset( int seg )
{
    /* reset en 3 seg */
    LogMessage("[CTRL] RESET solicitado.");
    if(seg == 0) seg = 3;
    g_ctrl_count_reset = seg * 10;
}

void BotonPressed(const char* cmd)
{
    LogMessage("[BotonPressed] CMD: %s", cmd);
    
    g_screen_saver_count = 0;
    
    if( !memcmp(cmd, "HOME", 4))
    {
        if(g_wifi_info.status.host_conectado)
        {
            strcpy(g_show_filename, HOME_SCREEN_CSV);
            g_ctrl_stm = SHOW_PAGE;
        }
        else
        {
            strcpy(g_show_filename, OFFLINE_SCREEN_CSV);
            g_ctrl_stm = OFFLINE;
        }
        g_ctrl_current_screen = 0;
    }
    else if( !memcmp(cmd, "CONFIG", 6))
    {
        strcpy(g_show_filename, CONFIG_SCREEN_CSV);
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
            snprintf(g_show_filename, FILE_NAME_SIZE, "screen%u.csv", g_ctrl_current_screen);
            g_ctrl_stm = SHOW_PAGE;
        }
    }
    else if( !memcmp(cmd, "WIFI", 4))
    {
        Clear(0);
        g_wifi_info.status.wifi_start_ap = true;
    }
    else if( !memcmp(cmd, "RESET", 5))
    {
        Clear(0);
        CTRLReset(0);
    }
    else if( !memcmp(cmd, "UPGRADE", 7))
    {
        Clear(0);
        UpdateFirmware();
    }
    else if( !memcmp(cmd, "SWITCH:", 7))
    {
        if(g_wifi_info.status.host_conectado)
        {
            g_wifi_info.status.sombra = 10;
            HTTPCommandSwitch(&cmd[7]);
        }
    }
    else if( !memcmp(cmd, "PULSE:", 6))
    {
        if(g_wifi_info.status.host_conectado)
        {
            g_wifi_info.status.sombra = 10;
            HTTPCommandPulse(&cmd[6]);
        }
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
                LogMessage("[TOUCH] X: %u y: %u", touch_x, touch_y);
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


    g_wifi_info.status.brillo = 0;
    InitBotones(BotonPressed);

    LogMessage("[ShowScreen] Cargando: %s", filename);
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
                if(g_wifi_info.status.debug)
                {
                    LogMessage("[ShowScreen] Leido: %s", line);
                }
                /* Analizo la línea */
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
    g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_max;

}

void UpdateScreenTask( void )
{
    int rc;
    char download_filename[256];
    char line[256];
    unsigned char line_len;
    
    if(g_us_waith) return;

    if(g_us_last_stm != g_us_stm)
    {
        LogMessage("[UpdateScreenTask] STM: %d -> %d", g_us_last_stm, g_us_stm);
        g_us_last_stm = g_us_stm;
    }
    
    switch(g_us_stm)
    {
        case US_INIT:
            EnableDisplay();
            if(g_us_list_file) FSfclose(g_us_list_file);
            g_update_screen_timeout_count = 0;
            g_us_stm++;
            break;
        case US_WAITH:
            break;
        case US_GET_LIST:
            DisableDisplay();
            /* Pido el listado de archivos */
            sprintf(download_filename, "%s/touch/%s/%s", DOWNLOAD_PATH, g_wifi_info.status.hw_mac, SCREEN_FILENAME);
            LogMessage("[UpdateScreenTask] Solicitando listado de archivos [%s]", download_filename);
            if(HTTPGetFile(download_filename, NULL) > 0 )
            {
                g_update_screen_timeout_count = 600;
                g_us_stm++;
            }
            else
            {
                g_us_waith = 600;
            }
            break;
        case US_GET_LIST_WAITH:
            break;
        case US_GET_LIST_END:
            LogMessage("[UpdateScreenTask] Listado de archivos Ok");
            g_us_waith = 50;
            g_us_stm++;
            break;
        case US_OPEN_LIST_FILES:
            LogMessage("[UpdateScreenTask] Analizando el listado de archivos");
            g_us_list_file = FSfopen(SCREEN_FILENAME, FS_READ);
            if(g_us_list_file)
            {
                g_update_screen_timeout_count = 600;
                g_us_stm++;
            }
            else
            {
                g_us_stm = US_ERROR;
            }
            break;
        case US_GET_LIST_FILES:
            /* Leo una línea */
            line_len = 0;
            do {
                rc = FSfread(&line[line_len++], 1, 1, g_us_list_file);
            } while(line[line_len-1] != 0x0d && line[line_len-1] != 0x0a && line_len < 255 && rc == 1);
            
            if(rc == 1)
            {
                if(line[line_len-1] == 0x0d || line[line_len-1] == 0x0a)
                {
                    line_len--;
                }

                if(line_len > 0)
                {
                    line[line_len] = 0;
                    if(line[0] != '#')
                    {
                        /* Me traigo el archivo */
                        LogMessage("[UpdateScreenTask] Solicitando [%s] del listado de archivos", download_filename);
                        snprintf(download_filename, sizeof(download_filename)-1, "%s/touch/%s/%s", DOWNLOAD_PATH, g_wifi_info.status.hw_mac, line);
                        if(HTTPGetFile(download_filename, NULL) > 0 )
                        {
                            g_update_screen_timeout_count = 600;
                            g_us_stm++;
                        }
                        else
                        {
                            g_us_waith = 600;
                        }
                    }
                }
            }
            else
            {
                g_us_stm = US_GET_LIST_FILES_END;
            }
            break;
        case US_GET_LIST_FILES_WAITH:
            break;
        case US_GET_LIST_FILES_NEXT:
            LogMessage("[UpdateScreenTask] Archivo del listado Ok");
            g_us_stm = US_GET_LIST_FILES;
            g_us_waith = 50;
            break;
        case US_GET_LIST_FILES_END:
            LogMessage("[UpdateScreenTask] Final del listado de archivos");
            FSfclose(g_us_list_file);
            g_us_list_file = NULL;
            g_us_stm = US_INIT;
            break;
        case US_ERROR:
            LogMessage("[UpdateScreenTask] ERROR. Volviendo a INIT");
            g_us_stm = US_INIT;
            break;
    }
    
    
    
}

void UpdateFirmware( void )
{
    /* Actualizar firmware en 5 seg */
    g_control_update_firmware = 50;
}

void UpdateScreens( void )
{
    if(g_us_stm == US_WAITH) g_us_stm++;
}

void UpdateEndDownload( void )
{
    if(g_us_stm == US_GET_LIST_WAITH ||
       g_us_stm == US_GET_LIST_FILES_WAITH ) g_us_stm++;
}

void DisableDisplay()
{
    g_ctrl_stm = DISPLAY_DISABLE;
}

void EnableDisplay()
{
    if(g_ctrl_stm == DISPLAY_DISABLE_LOOP)
    {
        g_ctrl_stm = DISPLAY_ENABLE;
    }
}
