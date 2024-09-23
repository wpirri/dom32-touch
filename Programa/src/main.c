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

/* *****************************************************************************
 * Asignacion de pines para PIC32MM0064GPL028 en Dom32Term
 * 1    MCLR / Vpp                      Programaciïon/Debug/Reset
 * 2    RA0                             DEBUG_TX
 * 3    RA1/AN1                         LCD_WR / TOUCH_YP (An)  J3-2
 * 4    RB0                             LCD_D0                  J1-8
 * 5    RB1                             LCD_D1                  J1-7
 * 6    RB2/AN4                         LCD_D2                  J2-6
 * 7    RB3/AN11                        LCD_D3                  J2-5
 * 8    Vss                             Vss
 * 9    RA2/AN5                         LCD_RS / TOUCH_XM (An)  J3-3
 * 10   RA3        COMMAND/DATA         LCD_CS                  J3-4
 * 11   RB4        CHIP SELECT          LCD_D4                  J2-4
 * 12   RA4/OC                          LCD_RST                 J3-5 WiFi_RST
 * 13   Vdd                             +3v3
 * 14   RB5                             LCD_D5                  J2-3
 * 15   RB6                             LCD_D6 / TOUCH_XP       J2-2
 * 16   RB7                             LCD_D7 / TOUCH_YM       J2-1
 * 17   RB8/RP7/SCK1                    SD_SCK                  J1-3
 * 18   RB9/RP8/SDO1                    SD_DO                   J1-4
 * 19   RC9/RP19                        SD_DI                   J1-5
 * 20   VCap                            Cap 100n + 10uF
 * 21   RB10/RP17/PGED2                 LED_STATUS
 * 22   RB11/RP18/PGEC2                 LED_MODO
 * 23   Vusb                            Vusb                            
 * 24   RB13/RP13                       SD_CS                   J1-6
 * 25   RB14/RP19                       WiFi_TX
 * 26   RB15/RP10                       WiFi_RX
 * 27   AVss                            Vss
 * 28   AVdd                            +3v3
 * 
 * LCD_RD                  J3-1 -> +3v3
 * 
 * 
 * LCD Driver ILI9341 (240x320) - AFY240320B0-2.4N6NTM-R
 * 
 * ****************************************************************************/

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

