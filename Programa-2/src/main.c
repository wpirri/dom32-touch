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

/* ****************************************************************************
 * Dom32Touch - Bastidor Tactil para sistema de dom�tica
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
 * **************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "log.h"
#include "sd/fsio.h"
#include "rtcc.h"
#include "display/display.h"
#include "display/touch.h"
#include "wifi/wifi.h"
#include "control.h"

/* ************************************************************************* */
// FDEVOPT
#pragma config SOSCHP = OFF    //Secondary Oscillator High Power Enable bit->SOSC oprerates in normal power mode.
#pragma config ALTI2C = OFF    //Alternate I2C1 Pins Location Enable bit->Primary I2C1 pins are used
#pragma config FUSBIDIO = OFF    //USBID pin control->USBID pin is controlled by the USB module
#pragma config FVBUSIO = OFF    //VBUS Pin Control->VBUS pin is controlled by the USB module

// FICD
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config ICS = PGx2               // ICE/ICD Communication Channel Selection bits (Communicate on PGEC3/PGED3)

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config RETVR = OFF              // Retention Voltage Regulator Enable bit (Retention regulator is disabled)
#pragma config LPBOREN = ON    //Downside Voltage Protection Enable bit->Low power BOR is enabled, when main BOR is disabled

// FWDT
#pragma config SWDTPS = PS1048576    //Sleep Mode Watchdog Timer Postscale Selection bits->1:1048576
#pragma config FWDTWINSZ = PS25_0    //Watchdog Timer Window Size bits->Watchdog timer window size is 25%
#pragma config WINDIS = OFF    //Windowed Watchdog Timer Disable bit->Watchdog timer is in non-window mode
#pragma config RWDTPS = PS1024    //Run Mode Watchdog Timer Postscale Selection bits->1:1024
#pragma config RCLKSEL = LPRC    //Run Mode Watchdog Timer Clock Source Selection bits->Clock source is LPRC (same as for sleep mode)
#pragma config FWDTEN = ON    //Watchdog Timer Enable bit->WDT is enabled

// FOSCSEL
#pragma config FNOSC = PLL    //Oscillator Selection bits->Primary or FRC oscillator with PLL
#pragma config PLLSRC = FRC    //System PLL Input Clock Selection bit->FRC oscillator is selected as PLL reference input on device reset
#pragma config SOSCEN = OFF    //Secondary Oscillator Enable bit->Secondary oscillator is disabled
#pragma config IESO = ON    //Two Speed Startup Enable bit->Two speed startup is enabled
#pragma config POSCMOD = OFF    //Primary Oscillator Selection bit->Primary oscillator is disabled
#pragma config OSCIOFNC = OFF    //OFF para RA4 como Digital I/O
#pragma config SOSCSEL = ON    //Secondary Oscillator External Clock Enable bit->SCLKI pin configured for Digital mode
#pragma config FCKSM = CSECME    //Clock Switching and Fail-Safe Clock Monitor Enable bits->Clock switching is enabled; Fail-safe clock monitor is enabled

// FSEC
#pragma config CP = OFF                 // Code Protection Enable bit (Code protection is disabled)
/* ************************************************************************* */


int main(void)
{
    bool status_sd_ok = false;
   
    /* ********************************************************************* */
    /*  Setting the Output Latch SFR(s) */
    LATA = 0x00000000;
    LATB = 0x00000000;
    LATC = 0x00000000;

    /* ********************************************************************* */
    /* Setting the GPIO Direction SFR(s) */
    TRISA = 0xFFFFFFFF;
    TRISB = 0xFFFFFFFF;
    TRISC = 0xFFFFFFFF;
    
    /* ********************************************************************* */
    /* Setting the Weak Pull Up and Weak Pull Down SFR(s) */
    CNPDA = 0x00000000;
    CNPDB = 0x00000000;
    CNPDC = 0x00000000;
    CNPUA = 0x00000000;
    CNPUB = 0x00000000;
    CNPUC = 0x00000000;

    /* ********************************************************************* */
    /* Setting the Open Drain SFR(s) */
    ODCA = 0x00000000;
    ODCB = 0x00000000;
    ODCC = 0x00000000;

    /* ********************************************************************* */
    /* Setting the Analog/Digital Configuration SFR(s) */
    ANSELA = 0x00000000;
    ANSELB = 0x00000000;

    /* ********************************************************************* */
    /* Modulo CPP */
    CCP1CON1 = 0x00000000;    
    CCP2CON1 = 0x00000000;    
    CCP3CON1 = 0x00000000;    
    
    /* ********************************************************************* */
    /* Change notification */
    CNCONB = 0x00000000;
    /* ********************************************************************* */
    /* OSCILLATOR Init */
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    // CF No Clock Failure; FRCDIV FRC/1; SLPEN Device will enter Idle mode when a WAIT instruction is issued; NOSC SPLL; SOSCEN disabled; CLKLOCK Clock and PLL selections are not locked and may be modified; OSWEN Complete; 
    OSCCON = 0x100;
    // TUN Center frequency; 
    OSCTUN = 0x0;
    // PLLODIV 1:1; PLLMULT 3x; PLLICLK FRC; 
    SPLLCON = 0x10080;
    // SWRST disabled; 
    RSWRST = 0x0;
    // WDTO disabled; GNMI disabled; CF disabled; WDTS disabled; NMICNT 0; LVD disabled; SWNMI disabled; 
    RNMICON = 0x0;
    // SBOREN disabled; VREGS disabled; RETEN disabled; 
    PWRCON = 0x0;
    // WDTO disabled; EXTR disabled; POR disabled; SLEEP disabled; BOR disabled; PORIO disabled; IDLE disabled; PORCORE disabled; BCFGERR disabled; CMR disabled; BCFGFAIL disabled; SWR disabled; 
    RCON = 0x0;
    // ON disabled; DIVSWEN disabled; RSLP disabled; ROSEL SYSCLK; OE disabled; SIDL disabled; RODIV 0; 
    REFO1CON = 0x0;
    // ROTRIM 0; 
    REFO1TRIM = 0x0;
    // SPDIVRDY disabled; 
    CLKSTAT = 0x0;
    // System Reg Lock
    SYSKEY = 0x00000000; 

    RCON = 0x00000000;
    /* ********************************************************************* */
    /* Core Timer */
    // Set the count value
    _CP0_SET_COUNT(0x0); 
    // Set the compare value
    _CP0_SET_COMPARE(CORE_TIMER_COMPARE_VAL); 
    // Interrupcion
    //    Priority: 1
    IPC0bits.CTIP = 1;
    //    Sub Priority: 0
    IPC0bits.CTIS = 0;
     // Enable the interrupt
    IEC0bits.CTIE = 1;
    /* ********************************************************************* */
    /* TIMER1 */
    IPC4bits.T1IP = 0x0001 ;
    IFS0CLR = _IFS0_T1IF_MASK; //Clear T1IF
    TMR1 = 0 ;
    T1CON = 0x00000000;
    T1CONbits.TCKPS0 = 0;
    T1CONbits.TCKPS1 = 0;
    T1CONbits.ON = 1;
    PR1 = 3427;
    // Enable TIMER1 Int
    IEC0bits.T1IE = 1 ;
    /* INTERRUPT Initialize */
    // Enable Multi Vector Configuration
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
    /* ********************************************************************* */
    LogInit(true, false);
    
    if( FSInit() )
    {
        status_sd_ok = true;
        LogMessage("[MAIN] File System Ok");
    }
    else
    {
        status_sd_ok = false;
        LogMessage("[MAIN] File System Error");
    }

    LogMessage("[MAIN] Init RTCC");
    RTCC_Initialize();

    LogMessage("[MAIN] Init Display");
    DisplayInit();

    LogMessage("[MAIN] Init Touch");
    TouchInit();

    LogMessage("[MAIN] Init WiFi");
    WiFiInit();

    
    
    
    ControlInit(status_sd_ok);
    /* Reset POR y BOR 
       Se hace a lo último así las distintas inicializaciones pueden verificar
       si vengo de un Power On */
    if(RCONbits.POR || RCONbits.BOR)
    {
        /* Power-Up*/
    }
    RCONbits.POR = 0;
    RCONbits.BOR = 0;

    LogMessage("[MAIN] Init End");
    while(1)
    {
        CLRWDT();
        ControlTask();
        

    }
    return 0;
}
