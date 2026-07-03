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
#include "http.h"
#include "system.h"
#include "rtcc.h"

/* **** WiFi *************************************************************** */
typedef enum
{
    WIFI_INIT = 0,
    WIFI_MODO_AP,
    WIFI_MODO_AP_OK,
    WIFI_MODO_ST,
    WIFI_MODO_ST_OK,
    WIFI_CONECTAR_A_HOST,
    WIFI_CONECTADO_A_HOST,
    WIFI_DESCONECTADO_DE_HOST,
    WIFI_ERROR,
    WIFI_ERROR_FATAL,
    WIFI_ERROR_FATAL_LOOP
} enum_control_wifi_stm;

enum_control_wifi_stm control_wifi_stm = WIFI_INIT;
unsigned int control_wifi_stm_delay;

/* **** Screen ************************************************************* */
typedef enum
{
    SCREEN_INIT = 0,
    SCREEN_SHOW_PAGE,
    SCREEN_SHOW_PAGE_LOOP,
    SCREEN_CONFIG,
    SCREEN_CONFIG_LOOP,
    SCREEN_WIFI_CONFIG,
    SCREEN_WIFI_CONFIG_LOOP,
    SCREEN_SAVER,
    SCREEN_SAVER_LOOP,
    SCREEN_OFFLINE,
    SCREEN_OFFLINE_LOOP,
    SCREEN_ERROR,
    SCREEN_ERROR_FATAL,
    SCREEN_ERROR_FATAL_LOOP
} enum_control_screen_stm;

enum_control_screen_stm control_screen_stm = SCREEN_INIT;
unsigned int control_screen_stm_delay;
unsigned int control_screen_saver_count;
char control_screen_filename[FILE_NAME_SIZE+1];
unsigned int control_screen_number;

/* **** Control ************************************************************ */
bool status_sd_ok;
bool assinc_timer_flag;
unsigned int wifi_config_timer_count;
unsigned int keep_alive_timer_count;
unsigned int reset_timer_count;
unsigned int update_firmware_timer_count;
unsigned int update_screen_timer_count;
unsigned int save_config_timer_count;

void ProcessGeneralConfig(char* in);
void ControlHostKeepAlive(void);

void DownloadFile(const char* filename, enum_control_screen_stm return_screen)
{
    DisplayOff();
    Clear(0);
    /* Imagen centrada */
    DrawBitmap(DOWNLOAD_SCREEN_BMP, 
            ((DISPLAY_X_SIZE/2)-(GetBitmapW(DOWNLOAD_SCREEN_BMP)/2)), 
            ((DISPLAY_Y_SIZE/2)-(GetBitmapH(DOWNLOAD_SCREEN_BMP)/2)) );
    DisplayBrillo(g_wifi_config.u.config.brillo_max);
    DisplayOn();

    HttpDownload(filename);

    control_screen_stm = return_screen;
}

void ControlInit( bool sd_ok )
{
    status_sd_ok = sd_ok;
    control_screen_number = 0;
    control_screen_stm_delay = 0;
    control_screen_saver_count = g_wifi_config.u.config.screen_saver_time*100;
    wifi_config_timer_count = 0;
    keep_alive_timer_count = 0;
    reset_timer_count = 0;
    update_firmware_timer_count = 0;
    update_screen_timer_count = 0;
    save_config_timer_count = 0;
    control_wifi_stm_delay = 500;
    assinc_timer_flag = false;
}

void ControlTimer( void )
{
    /* Para las cosas que necesitan el timer pero no pueden estar dentro de una int */
    assinc_timer_flag = true;
    
    if(control_screen_stm_delay) control_screen_stm_delay--;
    if(control_wifi_stm_delay) control_wifi_stm_delay--;
    if(wifi_config_timer_count) wifi_config_timer_count--;
    if(WiFiConectado() && keep_alive_timer_count) keep_alive_timer_count--;
    if(control_screen_saver_count) control_screen_saver_count--;
    if(reset_timer_count)
    {
        reset_timer_count--;
        if(reset_timer_count == 0)
        {
            SystemReset();
        }
    }
}

void ControlTask(void)
{
    if(WiFiConectado() && keep_alive_timer_count == 0)
    {
        ControlHostKeepAlive();
    }
    
    /* Para las cosas que dependen del timer pero no pueden estar en una interrupcion */
    if(assinc_timer_flag)
    {
        assinc_timer_flag = false;
        
        if(update_screen_timer_count)
        {
            update_screen_timer_count--;
            if(update_screen_timer_count == 0)
            {
                /* TODO: Logica de carga de pantallas */


            }
        }

        if(save_config_timer_count)
        {
            save_config_timer_count--;
            if(save_config_timer_count == 0)
            {
                ConfigSave();
            }

        }

        if(update_firmware_timer_count)
        {
            update_firmware_timer_count--;
            if(update_firmware_timer_count == 0)
            {
                control_screen_number = 0;
                strcpy(control_screen_filename, HOME_SCREEN_CSV);
                DownloadFile(FIRMWARE_FILENAME, SCREEN_SHOW_PAGE);
            }
        }
        
    }
}

void ControlHostKeepAlive(void)
{
    char url[256];
    char data[256];
    int rc;
    char resp_err_code[16];
    char resp_err_msg[256];
    
    sprintf(url, "%s/infoio.cgi", g_wifi_config.u.config.rqst_path);
    sprintf(data, "ID=%s&TYP=TOUCH", WiFiMAC());
    rc = HttpQueryHost(url, data, NULL, data);
    if(rc == 200)
    {
        LogMessage("[ControlHostKeepAlive] HTTP Req Ok");
        if(HTTPGetFormData(data, "error", resp_err_code))
        {
            if(HTTPGetFormData(data, "message", resp_err_msg))
            {
                if(atoi(resp_err_code) == 0)
                {
                    LogMessage("[ControlHostKeepAlive] Respuesta del sistema Ok");
                    HttpConexionOk();
                    keep_alive_timer_count = 6000;
                    /* Busco configuraciones, comandos, etc */
                    ProcessGeneralConfig(data);
                    return;
                }
                else
                {
                    LogMessage("[ControlHostKeepAlive] Respuesta del sistema [error = %s message = %s]", resp_err_code, resp_err_msg );
                }
            }
        }
    }
    else
    {
        LogMessage("[ControlHostKeepAlive] HTTP Req No Ok [%i]", rc);
    }
    HttpConexionError();
    keep_alive_timer_count = 500;
}

void ProcessGeneralConfig(char* in)
{
    char s[256];
    struct tm tm_time;
    
    if(HTTPGetFormData(in, "ap1", g_wifi_config.u.config.wifi_ap1))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ap1p", g_wifi_config.u.config.wifi_ap1_pass))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ap2", g_wifi_config.u.config.wifi_ap2))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ap2p", g_wifi_config.u.config.wifi_ap2_pass))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ce1", g_wifi_config.u.config.wifi_host1))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ce2", g_wifi_config.u.config.wifi_host2))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "path", g_wifi_config.u.config.rqst_path))
    {
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ce1p", s))
    {
        g_wifi_config.u.config.wifi_host1_port = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "ce2p", s))
    {
        g_wifi_config.u.config.wifi_host2_port = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "reset", s))
    {
        reset_timer_count = 300;
        save_config_timer_count = 150;
    }
    if(HTTPGetFormData(in, "update", s))
    {
        if( !strcmp(s, "firmware"))
        {
            update_firmware_timer_count = 300;
        }
        else if( !strcmp(s, "screen"))
        {
            update_screen_timer_count = 300;
        }
    }
    if(HTTPGetFormData(in, "brillo-max", s))
    {
        g_wifi_config.u.config.brillo_max = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "brillo-med", s))
    {
        g_wifi_config.u.config.brillo_med = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "brillo-min", s))
    {
        g_wifi_config.u.config.brillo_min = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "screen-saver", s))
    {
        g_wifi_config.u.config.screen_saver_time = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "debug", s))
    {
        g_wifi_config.u.config.debug = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "display", s))
    {
        g_wifi_config.u.config.display_type = atoi(s);
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "report", s))
    {
        g_wifi_config.u.config.report = atoi(s) * 10;
        if(g_wifi_config.u.config.report == 0)
        {
            g_wifi_config.u.config.report = 600;
        }
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "REPORT", s))
    {
        g_wifi_config.u.config.report = atoi(s) * 10;
        if(g_wifi_config.u.config.report == 0)
        {
            g_wifi_config.u.config.report = 600;
        }
        save_config_timer_count = 1000;
    }
    if(HTTPGetFormData(in, "TIME", s))
    {
        LogMessage("TIME: %s", s);
        /*             1111111111
         *   01234567890123456789
         tmp YYYY/MM/DD hh:mm:ss
         */
        if(s[4] == '/' && s[7] == '/' && s[10] == ' ' && 
                s[13] == ':' && s[16] == ':')
        {
            s[4] = 0;
            s[7] = 0;
            s[10] = 0;
            s[13] = 0;
            s[16] = 0;
            s[19] = 0;
            
            tm_time.tm_year = atoi(&s[0]) - 1900;
            tm_time.tm_mon = atoi(&s[5]) - 1;
            tm_time.tm_mday = atoi(&s[8]);
            tm_time.tm_hour = atoi(&s[11]);
            tm_time.tm_min = atoi(&s[14]);
            tm_time.tm_sec = atoi(&s[17]);

            RTCC_TimeSet(&tm_time);
        }
        else
        {
            LogMessage("[CTRLConfSys] Error de formato para TIME");
        }
    }
}

/* **** WiFi *************************************************************** */
void Control_WiFi_Task(void)
{
    WiFiCheckUnsol();
    
    if(control_wifi_stm_delay)return;

    switch(control_wifi_stm)
    {
        case WIFI_INIT:
            if(WiFiStart() == 0)
            {
                /* Modo inicial del dispositivo */
                //control_wifi_stm = WIFI_MODO_AP;
                control_wifi_stm = WIFI_MODO_ST;
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
            if(WiFiConectado() > 0)
            {
                control_wifi_stm++;
            }
            else
            {
                WiFiSwitchRouter();
                control_wifi_stm_delay = 500;
                control_wifi_stm = WIFI_MODO_ST;
            }
            break;
        case WIFI_CONECTAR_A_HOST:
            break;
        case WIFI_CONECTADO_A_HOST:
            break;
        case WIFI_DESCONECTADO_DE_HOST:
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

/* **** Screen ************************************************************* */
void BotonPressed(const char* cmd);
void TouchTask( void );
void ShowScreen(const char* filename);

void Control_Screen_Task( void )
{
    
    /* ***** Maquina de estados de pantallas ***** */
    if(control_screen_stm_delay) return;

    if( (WiFiMode() == WIFI_MODE_AP_ST || WiFiMode() == WIFI_MODE_AP) && control_screen_stm != SCREEN_WIFI_CONFIG_LOOP )
    {
        control_screen_stm = SCREEN_WIFI_CONFIG;
    }
    
    switch(control_screen_stm)
    {
        case SCREEN_INIT:
            LogMessage("[SCREEN] Init");
            /* Pantalla negra */
            DisplayOff();
            Clear(0);
            DisplayBrillo(g_wifi_config.u.config.brillo_max);
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
            LogMessage("[SCREEN] Show Page [%s]", control_screen_filename);
            control_screen_saver_count = g_wifi_config.u.config.screen_saver_time*100;
            DisplayBrillo(g_wifi_config.u.config.brillo_max);
            ShowScreen(control_screen_filename);
            control_screen_stm++;
            break;
        case SCREEN_SHOW_PAGE_LOOP:
            if(WiFiMode() == WIFI_MODE_ST && HttpOnLine())
            {
                if(control_screen_saver_count == 0 && g_wifi_config.u.config.screen_saver_time > 0)
                {
                    if( !strcmp(control_screen_filename, HOME_SCREEN_CSV))
                    {
                        control_screen_stm = SCREEN_SAVER;
                    }
                    else
                    {
                        control_screen_number = 0;
                        strcpy(control_screen_filename, HOME_SCREEN_CSV);
                        control_screen_stm = SCREEN_SHOW_PAGE;
                    }
                }
                else
                {
                    TouchTask();
                }
            }
            else
            {
                control_screen_stm = SCREEN_OFFLINE;
            }
            break;
        case SCREEN_CONFIG:
            LogMessage("[SCREEN] Config");
            DisplayBrillo(g_wifi_config.u.config.brillo_max);
            ShowScreen(CONFIG_SCREEN_CSV);
            control_screen_stm++;
            break;
        case SCREEN_CONFIG_LOOP:
            if(control_screen_saver_count == 0 && g_wifi_config.u.config.screen_saver_time > 0)
            {
                control_screen_number = 0;
                strcpy(control_screen_filename, HOME_SCREEN_CSV);
                control_screen_stm = SCREEN_SHOW_PAGE;
            }
            else
            {
                TouchTask();
            }
            break;
        case SCREEN_WIFI_CONFIG:
            LogMessage("[SCREEN] WiFi Config");
            wifi_config_timer_count = 6000;
            control_screen_stm++;
            break;
        case SCREEN_WIFI_CONFIG_LOOP:
            if(WiFiMode() == WIFI_MODE_AP_ST || WiFiMode() == WIFI_MODE_AP)
            {
                if(wifi_config_timer_count == 0)
                {
                    if(g_wifi_config.u.config.wifi_ap1[0] != 0 || g_wifi_config.u.config.wifi_ap2[0] != 0)
                    {
                        control_wifi_stm = WIFI_MODO_ST;
                    }
                    else
                    {
                        wifi_config_timer_count = 1000;
                    }
                }
                DisplayOff();
                Clear(0);
                DisplayOn();
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
            LogMessage("[SCREEN] Screen Saver");
            DisplayOff();
            Clear(0);
            /* Imagen centrada */
            DrawBitmap(INIT_SCREEN_BMP, 
                    ((DISPLAY_X_SIZE/2)-(GetBitmapW(INIT_SCREEN_BMP)/2)), 
                    ((DISPLAY_Y_SIZE/2)-(GetBitmapH(INIT_SCREEN_BMP)/2)) );
            DisplayBrillo(g_wifi_config.u.config.brillo_min);
            DisplayOn();
            control_screen_stm++;
            break;
        case SCREEN_SAVER_LOOP:
            if(HttpOnLine())
            {
                TouchTask();
            }
            else
            {
                control_screen_stm = SCREEN_OFFLINE;
            }
            break;
        case SCREEN_OFFLINE:
            LogMessage("[SCREEN] OffLine");
            DisplayBrillo(g_wifi_config.u.config.brillo_med);
            strcpy(control_screen_filename, OFFLINE_SCREEN_CSV);
            ShowScreen(control_screen_filename);
            control_screen_stm++;
            break;
        case SCREEN_OFFLINE_LOOP:
            if(HttpOnLine())
            {
                if(control_screen_saver_count == 0 && g_wifi_config.u.config.screen_saver_time > 0)
                {
                    control_screen_stm = SCREEN_SAVER;
                }
                else
                {
                    strcpy(control_screen_filename, HOME_SCREEN_CSV);
                    control_screen_number = 0;
                    control_screen_stm = SCREEN_SHOW_PAGE;
                }
            }
            else
            {
                TouchTask();
            }
            break;
        case SCREEN_ERROR:
            LogMessage("[SCREEN] Error");
            DisplayOff();
            DisplayBrillo(g_wifi_config.u.config.brillo_med);
            Clear(RED);
            DisplayOn();
            control_screen_stm_delay = 250;
            control_screen_stm = SCREEN_INIT;
            break;
        case SCREEN_ERROR_FATAL:
            LogMessage("[SCREEN] Error Fatal");
            DisplayOff();
            DisplayBrillo(g_wifi_config.u.config.brillo_med);
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

void BotonPressed(const char* cmd)
{
    LogMessage("[BotonPressed] CMD: %s", cmd);
    
    control_screen_saver_count = g_wifi_config.u.config.screen_saver_time*100;
    
    if( !memcmp(cmd, "HOME", 4))
    {
        control_screen_number = 0;
        strcpy(control_screen_filename, HOME_SCREEN_CSV);
        control_screen_stm = SCREEN_SHOW_PAGE;
    }
    else if( !memcmp(cmd, "CONFIG", 6))
    {
        control_screen_number = 0;
        control_screen_stm = SCREEN_CONFIG;
    }
    else if( !memcmp(cmd, "NEXT", 4))
    {
        if(control_screen_number < 9)
        {
            control_screen_number++;
            sprintf(control_screen_filename, "screen%u.csv", control_screen_number);
            control_screen_stm = SCREEN_SHOW_PAGE;
        }
    }
    else if( !memcmp(cmd, "PREV", 4))
    {
        if(control_screen_number > 0)
        {
            control_screen_number--;
            sprintf(control_screen_filename, "screen%u.csv", control_screen_number);
            control_screen_stm = SCREEN_SHOW_PAGE;
        }
    }
    else if( !memcmp(cmd, "WIFI", 4))
    {
        DisplayOff();
        Clear(0);
        control_wifi_stm = WIFI_MODO_AP;
    }
    else if( !memcmp(cmd, "RESET", 5))
    {
        DisplayOff();
        Clear(0);
        reset_timer_count = 100;
    }
    else if( !memcmp(cmd, "UPGRADE", 7))
    {
        DownloadFile(FIRMWARE_FILENAME, SCREEN_CONFIG);
    }
    else if( !memcmp(cmd, "SWITCH:", 7))
    {
        if(HttpOnLine() > 0)
        {
            DisplayOff();
            HTTPCommandSwitch(&cmd[7]);
            DisplayOn();
        }
    }
    else if( !memcmp(cmd, "PULSE:", 6))
    {
        if(HttpOnLine() > 0)
        {
            DisplayOff();
            HTTPCommandPulse(&cmd[6]);
            DisplayOn();
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
                LogMessage("[TOUCH] X: %u Y: %u", touch_x, touch_y);
                if(control_screen_stm == SCREEN_SAVER_LOOP)
                {
                    control_screen_number = 0;
                    strcpy(control_screen_filename, HOME_SCREEN_CSV);
                    control_screen_stm = SCREEN_SHOW_PAGE;
                }
                else
                {
                    BotonTask(touch_x, touch_y);
                }
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

void ShowScreen(const char* filename)
{
    FSFILE* f;
    int rc;
    char line[256];
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
            } while(line[line_len-1] != 0x0d && line[line_len-1] != 0x0a && line_len < 256 && rc == 1);
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
