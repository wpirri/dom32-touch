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

unsigned int DIgetcSPI(void)
{
	while( !SPIRBF );		// wait receive data available
	return (SPIxBUF);
}

void DIputcSPI(BYTE data_out)
{
    while( !SPITBE );
    SPIxBUF = data_out;
}

int DiInit( void )
{
    DI_CS_TRIS = 0;
    DI_DC_TRIS = 0;
    DI_RESET_TRIS = 0;
    DI_RESET_OC = 1;

    DI_CS = 1;      /* Display no seleccionado */
    DI_DC = 1;      /*  */
    DI_RESET = 0;   /* Reset display */

    
    
    
    
    
    return 0;
}
