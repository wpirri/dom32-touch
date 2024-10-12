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

volatile bool main_core_timer_flag;
volatile bool main_core_timer_flag_x10;
volatile unsigned char main_core_timer_count_x10;
volatile bool main_core_timer_flag_x100;
volatile unsigned char main_core_timer_count_x100;
volatile bool main_core_timer_flag_x1000;
volatile unsigned char main_core_timer_count_x1000;

bool sd_ok;
bool display_ok;

int main(void)
{
    SearchRec f_record;

    main_core_timer_flag = false;
    main_core_timer_flag_x10 = false;
    main_core_timer_count_x10 = 0;
    main_core_timer_flag_x100 = false;
    main_core_timer_count_x100 = 0;
    main_core_timer_flag_x1000 = false;
    main_core_timer_count_x1000 = 0;
    sd_ok = false;
    display_ok = false;

    ConfigInit();
    LogInit();

    /*
    if(FSInit())
    {
        Log("[sd] Init Ok");
        sd_ok = true;
    }
    else
    {
        Log("[sd] Init Error");
    }
    */

    if(BUSDisplayInit())
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
        Log("[display] clear");
        BUSDisplayClear(0);
    }
    
    Log("[main] Init Ok");
    
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
            
            if(display_ok)
            {
                Log("[display] azul");
                BUSDisplayClear(DI_BLUE);
            }

            if(sd_ok)
            {
                if(FindFirst ("*.*", ATTR_MASK, &f_record) == 0)
                {
                    Log("[sd] *** Archivos **********");
                    do
                    {
                        Log("[sd] - %s", f_record.filename);
                    } while(FindNext(&f_record) == 0);
                }
            }

            
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
