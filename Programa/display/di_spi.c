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

#include "di_spi.h"

#include "../config.h"
#include "../delay.h"

#include "dili9341.h"

/******************* Pin and Register Definitions ********************/
// SPI Configuration
// Define the SPI frequency
#define SPI_FREQUENCY			(20000000)
// Description: Display-SPI Chip Select Output bit
#define DI_CS               LATBbits.LATB6
// Description: Display-SPI Chip Select TRIS bit
#define DI_CS_TRIS          TRISBbits.TRISB6
// Description: Display-SPI 
#define DI_DC               PORTBbits.RB5
// Description: Display-SPI 
#define DI_DC_TRIS          TRISBbits.TRISB5
// Description: Display-SPI
#define DI_RESET            LATAbits.LATA4
// Description: Display-SPI
#define DI_RESET_TRIS       TRISAbits.TRISA4
// Description: Display-SPI
#define DI_RESET_OC         ODCAbits.ODCA4
// Description: The main SPI control register
#define SPIxCON              SPI2CON
// Description: The SPI status register
#define SPIxSTAT             SPI2STAT
// Description: The SPI Buffer
#define SPIxBUF              SPI2BUF
// Description: The bitwise define for the SPI control register (i.e. _____bits)
#define SPIxCONbits         SPI2CONbits
// Description: The bitwise define for the SPI status register (i.e. _____bits)
#define SPIRBF              SPI2STATbits.SPIRBF
//
#define SPITBE              SPI2STATbits.SPITBE
//
#define __SPIxCONbits_t     __SPI2CONbits_t
// Description: The enable bit for the SPI module
#define SPIENABLE           SPI2CONbits.ON
// Description: The definition for the SPI baud rate generator register (PIC32)
#define SPIBRG			    SPI2BRG
// Tris pins for SCK/SDI/SDO lines
// Description: The TRIS bit for the SCK pin
#define SPICLOCK            TRISBbits.TRISB8
// Description: The TRIS bit for the SDI pin
#define SPIIN               TRISCbits.TRISC9
// Description: The TRIS bit for the SDO pin
#define SPIOUT              TRISBbits.TRISB9

void SPIInit()
{
    SPIENABLE = 0;
    SPIxSTAT = 0x0000;               // power on state 

    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    // unlock PPS
    RPCONbits.IOLOCK = 0;
    // Mapeo de SPI */
    RPOR3bits.RP14R = 8;        // RP9 -> SPI2:SDO2
    RPOR3bits.RP13R = 9;       // RP13 -> SPI2:SCK2OUT
    RPINR11bits.SDI2R = 18;    // SPI2:SDI2 -> RP18
    // lock   PPS
    RPCONbits.IOLOCK = 1; 
    // System Reg Lock
    SYSKEY = 0x00000000; 

    SPICLOCK = 0;
    SPIOUT = 0;                  // define SDO1 as output (master or slave)
    SPIIN = 1;                  // define SDI1 as input (master or slave)
    
    //SPI module initilization depends on processor type
    SPIBRG = 0;
    
    SPIxCONbits.MSTEN = 1;  /*5*/
    SPIxCONbits.CKP = 0;    /*6*/
    SPIxCONbits.CKE = 1;    /*8*/
    SPIxCONbits.SMP = 1;    /*9*/
    
    SPIENABLE = 1;          // 15 - enable synchronous serial port
    
    Delayms(30);
}




void SPIWriteCommand(unsigned char data_out)
{
    while( !SPITBE );
    DI_DC = 0;  /* Command */
    Delayms(1);
    SPIxBUF = data_out;
    while( !SPITBE );
    DI_DC = 1;  /* Data */
    Delayms(1);
}

void SPIWriteData(unsigned char data_out)
{
    while( !SPITBE );
    SPIxBUF = data_out;
    while( !SPITBE );
}

int SPIDisplayInit( void )
{
    DI_CS_TRIS = 0;
    DI_DC_TRIS = 0;
    DI_RESET_TRIS = 0;
    DI_RESET_OC = 1;

    DI_CS = 1;      /* Display no seleccionado */
    DI_DC = 1;      /* Command = 0; Data = 1 */
    DI_RESET = 1;
    Delayms(5);
    DI_RESET = 0;

    /* Si el bus spi no es compartido lo inicializo */
    SPIInit();

    Delayms(15);
    DI_RESET = 1;
    Delayms(15);
    
    DI_CS = 0;
    Delayms(1);
    DisplayInit();
    DI_CS = 1;
    
    return 0;
}

void SPIDisplayClear( void )
{
	long i;
	
    DI_CS = 0;
    Delayms(1);
	DisplayXY( 0, 0, DISPLAY_X_SIZE, DISPLAY_Y_SIZE );
    for (i=0; i<((DISPLAY_X_SIZE+1)*(DISPLAY_Y_SIZE+1)); i++)
    {
        SPIWriteData(0x00);
    }
    DI_CS = 1;
}
