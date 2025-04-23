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
#include <xc.h>

#include "uart3.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WIFI_UART_RX_BYTEQ_LENGTH 4096

static uint8_t * volatile rxTail;
static uint8_t * rxHead;
static uint8_t * volatile txHead;
static bool volatile rxOverflowed;
static uint8_t rxQueue[WIFI_UART_RX_BYTEQ_LENGTH+1] ;

void UART3_Init(void)
{
    rxHead = rxQueue;
    rxTail = rxQueue;
    rxOverflowed = 0;

    /* ********************************************************************* */
    /* Configuración de los pines */
    // Tx
    TRISBbits.TRISB8 = 0;
    // Rx
    TRISBbits.TRISB9 = 1;
    // Reset
    TRISBbits.TRISB10 = 0;
    ODCBbits.ODCB10 = 1;
    /* ********************************************************************* */
    /* Configuración de interrupción */
    //    UTXI: UART 3 Error
    //    Priority: 1
        IPC15bits.U3EIP = 1;
    //    Sub Priority: 0
        IPC15bits.U3EIS = 0;
    //    UTXI: UART 3 Transmission
    //    Priority: 1
    //    IPC13bits.U3TXIP = 1;
    //    Sub Priority: 0
    //    IPC13bits.U3TXIS = 0;
    //    URXI: UART 3 Reception
    //    Priority: 1
        IPC14bits.U3RXIP = 1;
    //    Sub Priority: 0
        IPC14bits.U3RXIS = 0;
    /* Configuración del UART */
    /* ********************************************************************* */
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    /* ********************************************************************* */
    // Config PPS
    // unlock PPS
    RPCONbits.IOLOCK = 0;
    // Mapeo de UART3
    RPOR3bits.RP13R = 6;       // UART3:U3TX -> RP13
    RPINR8bits.U3RXR = 14;     // RP14 -> UART3:U3RX
    // lock   PPS
    RPCONbits.IOLOCK = 1; 
    /* ********************************************************************* */
    // System Reg Lock
    SYSKEY = 0x00000000; 
    /* ********************************************************************* */
    
    
    /* ********************************************************************* */
    /* Configuración del la UART */
    /* ************************************************************************** */
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    /* ************************************************************************** */

    IEC1bits.U3TXIE = 0;
    IEC1bits.U3RXIE = 0;

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    U3MODE = (0x8008 & ~(1<<15));  // disabling UART
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U3STA = 0x0;
    // BaudRate = 115200; Frequency = 24000000 Hz; BRG 51; 
    U3BRG = 0x33;

    IEC1bits.U3RXIE = 1;

     //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U3STASET = _U3STA_UTXEN_MASK;
    U3MODESET = _U3MODE_ON_MASK;  // enabling UART ON bit
    U3STASET = _U3STA_URXEN_MASK; 

    /* ************************************************************************** */
    // System Reg Lock
     SYSKEY = 0x00000000; 
}

bool UART3_IsRxReady(void)
{    
    return !(rxHead == rxTail);
}


void UART3_Write(unsigned int ch)
{
    while(U3STAbits.UTXBF);
    U3TXREG = ch;
}

unsigned char UART3_Read( void)
{
    unsigned char data = 0;

    while (rxHead == rxTail );
    
    data = *rxHead;

    rxHead++;

    if (rxHead == (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH))
    {
        rxHead = rxQueue;
    }
    return data;
}

/* ************************************************************************* */

void __attribute__ ((vector(_UART3_RX_VECTOR), interrupt(IPL1SOFT))) _UART3_RX( void )
{
    while((U3STAbits.URXDA == 1))
    {
        *rxTail = U3RXREG;

        // Will the increment not result in a wrap and not result in a pure collision?
        // This is most often condition so check first
        if ( ( rxTail    != (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH-1)) &&
             ((rxTail+1) != rxHead) )
        {
            rxTail++;
        } 
        else if ( (rxTail == (rxQueue + WIFI_UART_RX_BYTEQ_LENGTH-1)) &&
                  (rxHead !=  rxQueue) )
        {
            // Pure wrap no collision
            rxTail = rxQueue;
        } 
        else // must be collision
        {
            rxOverflowed = true;
        }

    }

    IFS1CLR= 1 << _IFS1_U3RXIF_POSITION;
}

bool UART3_Overflow()
{
    unsigned char c;
    
    if(rxOverflowed)
    {
        rxHead = rxQueue;
        rxTail = rxQueue;
        while((U3STAbits.URXDA == 1)) { c = U3RXREG; }
        c = c;
        rxOverflowed = false;
        return true;
    }
    return false;
}

void __attribute__ ((vector(_UART3_ERR_VECTOR), interrupt(IPL1SOFT))) _UART3_ERR ( void )
{
    unsigned char c;

    if ((U3STAbits.OERR == 1))
    {
        U3STACLR = _U3STA_OERR_MASK; 
    }
    
    rxHead = rxQueue;
    rxTail = rxQueue;
    while((U3STAbits.URXDA == 1)) { c = U3RXREG; }
    c = c;
    IFS1CLR= 1 << _IFS1_U3EIF_POSITION;
}
