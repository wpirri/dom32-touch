/* *****************************************************************************
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
 ******************************************************************************/

/* *****************************************************************************
 * Asignacion de pines para PIC32MM0064GPL028 en Dom32Term
 * 1    MCLR / Vpp                      Programaciïon/Debug/Reset
 * 2    RA0                             LED_STATUS
 * 3    RA1							    LED_MODO
 * 4    RB0                             PGED1
 * 5    RB1                             PGEC1
 * 6    RB2                             LED_INFO
 * 7    RB3
 * 8    Vss                             Vss
 * 9    RA2/RP3/U2TX                    DEBUG
 * 10   RA3
 * 11   RB4
 * 12   RA4                             LCD_RST (OC)
 * 13   Vdd                             +3v3
 * 14   RB5								LCD_CD
 * 15   RB6								LCD_CS
 * 16   RB7								SD_CS
 * 17   RB8/RP7/SCK2OUT                 SCK
 * 18   RB9/RP8/SDO2                    MOSI
 * 19   RC9/RP19/SDI2                   MISO
 * 20   VCap                            Cap 100n + 10uF
 * 21   RB10
 * 22   RB11
 * 23   Vusb                            Vusb                            
 * 24   RB13							WiFi_RST (OC)
 * 25   RB14/RP19/U1TX                  WiFi_TX
 * 26   RB15/RP10/U1RX                  WiFi_RX
 * 27   AVss                            Vss
 * 28   AVdd                            +3v3
 ******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "clog.h"
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

volatile bool timer1_flag_1x;
volatile bool timer1_flag_10x;
volatile unsigned char  timer1_count_10x;

void TIMER1(uint32_t status, uintptr_t context);

int main ( void )
{
    timer1_flag_1x = false;
    timer1_flag_10x = false;
    timer1_count_10x = 0;
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    LogInit();
    
    TMR1_CallbackRegister( TIMER1, 0 );
    TMR1_Start();
    
    LED_MODO_Set();
    
    while ( true )
    {
        WDT_Clear();
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        if(timer1_flag_1x)
        {
            timer1_flag_1x = false;
            
            LED_STATUS_Toggle();
        }

        if(timer1_flag_10x)
        {
            timer1_flag_10x = false;
            
            LogMessage("Toggle");
            LED_MODO_Toggle();
            LED_INFO_Toggle();
        }




    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/* INT Handler */
void TIMER1(uint32_t status, uintptr_t context)
{
    timer1_flag_1x = true;
    
    timer1_count_10x++;
    if(timer1_count_10x >= 10)
    {
        timer1_count_10x = 0;
        timer1_flag_10x = true;
    }
}

/*******************************************************************************
 End of File
*/

