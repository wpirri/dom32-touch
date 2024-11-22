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

/* ****************************************************************************
 * Dom32Touch - Bastidor Tactil para sistema de domótica
 * 
 * PIC21MM00256GPM028
 * ESP-WROOM-02D
 * MicroSD
 * Display 2.4'' c/Driver ILI9341
 * Touch resistivo
 * 
 * Asignacion de pines del procesador
 * 
 *      Port        Funcionalidad       Conectado a
 * ----------------------------------------------------------------------------
 * 01   MCLR        Reset               Tact Switch
 * 02   RA0         OUT                 Display Back Ligth
 * 03   RA1         OUT                 Display Reset
 * 04   RB0         OUT                 Display Data0   
 * 05   RB1         OUT                 Display Data1   
 * 06   RB2         OUT                 Display Data2
 * 07   RB3         OUT                 Display Data3
 * 08   Vss
 * 09   RA2/AN5     OUT                 Display WR      (Touch YP)
 * 10   RA3/AN6     OUT                 Display RS/CD   (Touch XM)
 * 11   RB4         OUT                 Display Data4
 * 12   RA4         OUT                 Display CS
 * 13   Vdd
 * 14   RB5         OUT                 Display Data5
 * 15   RB6         OUT                 Display Data6   (Touch XP)
 * 16   RB7         OUT                 Display Data7   (Touch YM)
 * 17   U3TX        U3TX -> RP13        WiFi Rx
 * 18   U3RX        U3RX -> RP14        WiFi Tx
 * 19   U2TX/RC9    U2TX -> RP18        Debug / Beep
 * 20   VCap
 * 21   RB10        OUT                 WiFi Reset
 * 22   RB11        OUT                 MicroSD CS
 * 23   Vusb
 * 24   SCK2OUT     SCK2OUT -> RP15     MicroSD SCK
 * 25   SDI2        SDI2 -> RP16        MicroSD MISO
 * 26   SDO2        SDO2 -> RP17        MicroSD MOSI
 * 27   AVss
 * 28   AVdd
 * 
 * ***************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "beep.h"
#include "log.h"
#include "delay.h"
#include "sd/fsio.h"
#include "display/display.h"
#include "wifi.h"
#include "http.h"
#include "control.h"
#include "rtcc.h"

volatile bool main_core_timer_flag;
volatile bool main_core_timer_flag_x10;
volatile unsigned char main_core_timer_count_x10;
volatile bool main_core_timer_flag_x100;
volatile unsigned char main_core_timer_count_x100;
volatile bool main_core_timer_flag_x1000;
volatile unsigned char main_core_timer_count_x1000;
volatile unsigned char main_brillo_count;

int main(void)
{
    main_core_timer_flag = false;
    main_core_timer_flag_x10 = false;
    main_core_timer_count_x10 = 0;
    main_core_timer_flag_x100 = false;
    main_core_timer_count_x100 = 0;
    main_core_timer_flag_x1000 = false;
    main_core_timer_count_x1000 = 0;
    main_brillo_count = 0;
    
    g_wifi_info.status.brillo = g_wifi_info.f.config.brillo_med;
    
    LogInit();
    ConfigInit();
    if(FSInit())
    {
        g_wifi_info.status.flag_sd_ok = true;
    }
    RTCC_Initialize();
    DisplayInit();
    //DrawSampleScreen();
    Clear(0);
    ConfigLoad();    
    TouchInit();
    WiFiInit();
    HTTPInit();
    CTRLInit();

    strncpy(g_wifi_info.status.up_fw, __DATE__ " " __TIME__, 
            sizeof(g_wifi_info.status.up_fw)-1);
    
    Log("[main] Init Ok");
    
    /* TODO: Sacar esto. Es para probar */
    g_wifi_info.f.config.screen_saver_time = 60;
    g_wifi_info.f.config.brillo_max = 100;
    g_wifi_info.f.config.brillo_med = 30;
    g_wifi_info.f.config.brillo_min = 0;
   
    while(1)
    {
        CLRWDT();
        
        WiFiTask();
        HTTPTask();
        CTRLTask();

        /* ***** Divisiones del TIMER ************************************** */
        if(main_core_timer_flag)
        {
            main_core_timer_flag = false;
            /* 10ms / 100/s */
            

        }
        else if(main_core_timer_flag_x10)
        {
            main_core_timer_flag_x10 = false;
            /* 100ms / 10/s */

            WiFiTimer();
            HTTPTimer();
            CTRLTimer();
            ConfigTimer();
        }
        else if(main_core_timer_flag_x100)
        {
            main_core_timer_flag_x100 = false;
            /* 1000ms / 1/s */
            
            
        }
        else if(main_core_timer_flag_x1000)
        {
            main_core_timer_flag_x1000 = false;
            /* 10000ms / c/10s */
            
        }
        /* ***************************************************************** */
    }
    return 0;
}

void __attribute__ ((vector(_CORE_TIMER_VECTOR), interrupt(IPL1SOFT))) _CORE_TIMER_ISR(void)
{
    uint32_t static compare = CORE_TIMER_COMPARE_VAL;

    // Update the compare value
    compare = compare + CORE_TIMER_COMPARE_VAL;
    _CP0_SET_COMPARE(compare);
    IFS0CLR= 1 << _IFS0_CTIF_POSITION;

    main_core_timer_flag = true;
    TimerBeep();
    main_core_timer_count_x10++;
    if(main_core_timer_count_x10 >= 10)
    {
        main_core_timer_count_x10 = 0;
        main_core_timer_flag_x10 = true;
        main_core_timer_count_x100++;
        if(main_core_timer_count_x100 >= 10)
        {
            main_core_timer_count_x100 = 0;
            main_core_timer_flag_x100 = true;
            main_core_timer_count_x1000++;
            if(main_core_timer_count_x1000 >= 10)
            {
                main_core_timer_count_x1000 = 0;
                main_core_timer_flag_x1000 = true;
            }
        }
    }
}

void __attribute__ ( ( vector(_TIMER_1_VECTOR) , interrupt(IPL7SOFT) ) ) _TIMER1_IRS ( void )
{
    IFS0CLR = _IFS0_T1IF_MASK; //Clear T1IF

#ifndef DEBUG_ON
    if(g_beep_flag)
    {
        LATCINV = (1 << 9);
    }
#endif /* DEBUG_ON */
    if(g_wifi_info.status.brillo == 0)
    {
        CLR_DI_BKL;
    }
    else if(g_wifi_info.status.brillo == 100)
    {
        SET_DI_BKL;
    }
    else if(main_brillo_count < 10)
    {
        main_brillo_count++;
        if(main_brillo_count == (g_wifi_info.status.brillo / 10) )
        {
            CLR_DI_BKL;
        }
    }
    else
    {
        main_brillo_count = 0;
        SET_DI_BKL;
    }

}

