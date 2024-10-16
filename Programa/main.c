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
 * 02   RA0         OUT                 Display RD
 * 03   RA1         OUT                 Display Reset
 * 04   RB0         OUT                 Display Data0   
 * 05   RB1         OUT                 Display Data1   
 * 06   RB2         OUT                 Display Data2
 * 07   RB3         OUT                 Display Data3
 * 08   Vss
 * 09   RA2/AN5     OUT                 Display WR      (Touch YP)
 * 10   RA3/AN6     OUT                 Display RS/CD   (Touch XM)
 * 11   RB4         OUT                 Display Data4
 * 12   RA4         OUT                 Display         CS
 * 13   Vdd
 * 14   RB5         OUT                 Display Data5
 * 15   RB6         OUT                 Display Data6   (Touch XP)
 * 16   RB7         OUT                 Display Data7   (Touch YM)
 * 17   U3TX        U3TX -> RP13        WiFi Rx
 * 18   U3RX        U3RX -> RP14        WiFi Tx
 * 19   U2TX        U2TX -> RP18        Debug
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
#include "log.h"
#include "delay.h"
#include "sd/fsio.h"
#include "display/di_bus.h"
#include "boton.h"

volatile bool main_core_timer_flag;
volatile bool main_core_timer_flag_x10;
volatile unsigned char main_core_timer_count_x10;
volatile bool main_core_timer_flag_x100;
volatile unsigned char main_core_timer_count_x100;
volatile bool main_core_timer_flag_x1000;
volatile unsigned char main_core_timer_count_x1000;

void BotonPressed(const char* name);

void Pagina1(void);
void Pagina2(void);
void Pagina3(void);
void Pagina4(void);

bool sd_ok;
bool display_ok;
unsigned int touch_pressed;
unsigned int touch_x, touch_y;

int main(void)
{
    main_core_timer_flag = false;
    main_core_timer_flag_x10 = false;
    main_core_timer_count_x10 = 0;
    main_core_timer_flag_x100 = false;
    main_core_timer_count_x100 = 0;
    main_core_timer_flag_x1000 = false;
    main_core_timer_count_x1000 = 0;
    sd_ok = false;
    display_ok = false;
    touch_pressed = 0;
    
    ConfigInit();
    LogInit();


    if(DisplayInit())
    {
        Log("[display] Init Ok");
        display_ok = true;
        Delayms(1000);
    }
    else
    {
        Log("[display] Init Error");
        display_ok = false;
    }

    if(display_ok)
    {
        Clear(0);
        Delayms(5000);
        DrawCircleEmpty(120, 160, 80, WHITE);
    }

    if(FSInit())
    {
        Log("[sd] Init Ok");
        sd_ok = true;
    }
    else
    {
        Log("[sd] Init Error");
    }
    
    if(display_ok)
    {
        DrawCircleFill(120, 160, 78, RED);
        Delayms(1000);
    }
    
    TouchInit();

    if(display_ok)
    {
        DrawCircleFill(120, 160, 78, BLUE);
        Delayms(1000);
    }

    if(display_ok)
    {
        DrawCircleFill(120, 160, 78, GREEN);
        Delayms(1000);
    }
    
    if(display_ok)
    {
        DrawCircleFill(120, 160, 78, BLACK);
        Delayms(1000);
    }

    if(display_ok)
    {
        Clear(0);
        DrawText(" Init Ok ", CENTER, 100,
            4, WHITE, BLUE);
        Delayms(3000);
        Clear(0);
    }
    
    Log("[main] Init Ok");
    Pagina1();
    
    while(1)
    {
        CLRWDT();
        if(main_core_timer_flag)
        {
            main_core_timer_flag = false;
            

        }
        else if(main_core_timer_flag_x10)
        {
            main_core_timer_flag_x10 = false;

            
        }
        else if(main_core_timer_flag_x100)
        {
            main_core_timer_flag_x100 = false;

            
        }
        else if(main_core_timer_flag_x1000)
        {
            main_core_timer_flag_x1000 = false;
            
        }
        
        if(TouchIsPressed( &touch_x, &touch_y, NULL ))
        {
            if( !touch_pressed)
            {
                touch_pressed = 1;

                Log("[TOUCH] X: %u y: %u", Touch2DisplayX(touch_x), Touch2DisplayY(touch_y));
                if(BotonTask( Touch2DisplayX(touch_x), Touch2DisplayY(touch_y) ))
                {
                    touch_pressed = 1000;
                }
                
                
                
            }
        }
        else
        {
            if(touch_pressed) touch_pressed--;
        }
        
        
        
        
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

void BotonPressed(const char* cmd)
{
    Log("[BotonPressed] CMD: %s", cmd);
}

void Pagina1(void)
{
    Clear(0);
    InitBotones(BotonPressed);

    BotonAdd(  "Boton 1", "CMD_BOTON1_PRESSED", 20, 20, 200, 75, RGB(150,0,0), RED, WHITE);
    BotonAdd(  "Boton 2", "CMD_BOTON2_PRESSED", 20, 105, 200, 75, RGB(150,0,0), RED, WHITE);
    
    BotonDraw();
}

void Pagina2(void)
{
    
}

void Pagina3(void)
{
    
}

void Pagina4(void)
{
    
}

