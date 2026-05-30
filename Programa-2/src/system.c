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
#include "system.h"

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "display/display.h"
#include "wifi/wifi.h"
#include "control.h"

/* * Manejo de excepciones ************************************************** */
static enum {
    EXCEP_IRQ = 0,            // interrupt
    EXCEP_AdEL = 4,            // address error exception (load or ifetch)
    EXCEP_AdES,                // address error exception (store)
    EXCEP_IBE,                // bus error (ifetch)
    EXCEP_DBE,                // bus error (load/store)
    EXCEP_Sys,                // syscall
    EXCEP_Bp,                // breakpoint
    EXCEP_RI,                // reserved instruction
    EXCEP_CpU,                // coprocessor unusable
    EXCEP_Overflow,            // arithmetic overflow
    EXCEP_Trap,                // trap (possible divide by zero)
    EXCEP_IS1 = 16,            // implementation specfic 1
    EXCEP_CEU,                // CorExtend Unuseable
    EXCEP_C2E                // coprocessor 2
} _excep_code;

void __attribute__((weak, nomips16)) _general_exception_handler (void)
{
    static unsigned int _excep_addr;
    static char* _except_str;
    
    asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
    asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

    _excep_code = (_excep_code & 0x0000007C) >> 2;

    switch(_excep_code){
        case EXCEP_IRQ: _except_str = "interrupt"; break;
        case EXCEP_AdEL: _except_str = "address error exception (load or ifetch)"; break;
        case EXCEP_AdES: _except_str = "address error exception (store)"; break;
        case EXCEP_IBE: _except_str = "bus error (ifetch)"; break;
        case EXCEP_DBE: _except_str = "bus error (load/store)"; break;
        case EXCEP_Sys: _except_str = "syscall"; break;
        case EXCEP_Bp: _except_str = "breakpoint"; break;
        case EXCEP_RI: _except_str = "reserved instruction"; break;
        case EXCEP_CpU: _except_str = "coprocessor unusable"; break;
        case EXCEP_Overflow: _except_str = "arithmetic overflow"; break;
        case EXCEP_Trap: _except_str = "trap (possible divide by zero)"; break;
        case EXCEP_IS1: _except_str = "implementation specfic 1"; break;
        case EXCEP_CEU: _except_str = "CorExtend Unuseable"; break;
        case EXCEP_C2E: _except_str = "coprocessor 2"; break;
    }

    while(1) { CLRWDT(); }
}

void __attribute__ ((vector(_CORE_TIMER_VECTOR), interrupt(IPL1SOFT))) _CORE_TIMER_ISR(void)
{
    uint32_t static compare = CORE_TIMER_COMPARE_VAL;

    // Update the compare value
    compare = compare + CORE_TIMER_COMPARE_VAL;
    _CP0_SET_COMPARE(compare);
    IFS0CLR= 1 << _IFS0_CTIF_POSITION;
    /* ********************************************************************* */
    /* 100 interrupciones por segundo                                        */
    /* ********************************************************************* */
    WiFiTimerInt();
    ControlTimerInt();

}

void __attribute__ ( ( vector(_TIMER_1_VECTOR) , interrupt(IPL7SOFT) ) ) _TIMER1_IRS ( void )
{
    IFS0CLR = _IFS0_T1IF_MASK; //Clear T1IF
    /* ********************************************************************* */
    DisplayTaskBrillo();
}

