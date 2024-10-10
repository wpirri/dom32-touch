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
// Chip Select Output bit
#define DI_CS               LATBbits.LATB6
#define DI_CS_TRIS          TRISBbits.TRISB6
#define DI_CS_OC            ODCBbits.ODCB6
// Data / Command
#define DI_DC               PORTBbits.RB10
#define DI_DC_TRIS          TRISBbits.TRISB10
#define DI_DC_OC            ODCBbits.ODCB10
// Reset
#define DI_RESET            LATBbits.LATB11
#define DI_RESET_TRIS       TRISBbits.TRISB11
#define DI_RESET_OC         ODCBbits.ODCB11
// SCK
#define SPI_SCK_TRIS       TRISBbits.TRISB8
#define SPI_SCK_OC         ODCBbits.ODCB8
// SDI
#define SPI_SDI_TRIS        TRISCbits.TRISC9
#define SPI_SDI_OC          ODCCbits.ODCC9
// SDO
#define SPI_SDO_TRIS        TRISBbits.TRISB9
#define SPI_SDO_OC          ODCBbits.ODCB9

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

void SPIWriteData(unsigned char data_out)
{
    while( !SPITBE );
    SPIxBUF = data_out;

	while( !SPIRBF );		// wait receive data available
    unsigned char ch = SPIxBUF; ch = ch;
}
void SPIWriteCommand(unsigned char data_out)
{
    DI_DC = 0;  /* Command */
    Delayms(1);
    
    SPIWriteData(data_out);
            
    DI_DC = 1;  /* Data */
    Delayms(1);
}

void SPIInit()
{
    DI_CS = 1;      /* Display no seleccionado */

    /* Configuro el IO de SPI */
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
    
    SPI_SCK_TRIS = 0;
    SPI_SCK_OC = 1;
    SPI_SDO_TRIS = 0;                  // define SDO1 as output (master or slave)
    SPI_SDO_OC = 1;
    SPI_SDI_TRIS = 1;                  // define SDI1 as input (master or slave)

    /* Configuro el timing del SPI */
    SPIENABLE = 0;
    SPIxSTAT = 0x0000;               // power on state 
    //SPI module initilization depends on processor type
    SPIBRG = 59;
    SPIxCONbits.MSTEN = 1;  /*5*/
    SPIxCONbits.CKP = 0;    /*6*/
    SPIxCONbits.CKE = 1;    /*8*/
    SPIxCONbits.SMP = 1;    /*9*/

    /* Enciendo el modulo */
    SPIENABLE = 1;          // 15 - enable synchronous serial port
    
    Delayms(30);
    
    /* Genero 80 pulsos de clock */
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
    SPIWriteData(0xff);
}

int SPIDisplayInit( bool init_spi )
{
    DI_CS_TRIS = 0;
    DI_CS_OC = 1;
    DI_DC_TRIS = 0;
    DI_DC_OC = 1;
    DI_RESET_TRIS = 0;
    DI_RESET_OC = 1;

    DI_CS = 1;      /* Display no seleccionado */
    DI_DC = 1;      /* Command = 0; Data = 1 */
    DI_RESET = 1;
    Delayms(10);
    DI_RESET = 0;

    /* Si el bus spi no es compartido lo inicializo */
    if(init_spi) SPIInit();

    while( !SPITBE );
    
    Delayms(15);
    DI_RESET = 1;
    Delayms(120);
    
    DI_CS = 0;
    Delayms(1);
    DisplayInit();
    DI_CS = 1;
    Delayms(1);
    
    return 0;
}

void SPIDisplayClear( unsigned char color )
{
	long i;
	
    while( !SPITBE );

    DI_CS = 0;
    Delayms(1);
	DisplayXY( 0, 0, DISPLAY_X_SIZE-1, DISPLAY_Y_SIZE-1);
    for (i = 0; i < (DISPLAY_X_SIZE*DISPLAY_Y_SIZE); i++)
    {
        CLRWDT();
        SPIWriteData(color);
    }
    DI_CS = 1;
    Delayms(1);

}

void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char color)
{
	long i;
	
    while( !SPITBE );

    DI_CS = 0;
    Delayms(1);
	DisplayXY( x, y, x+w-1, y+h-1 );
    for (i = 0; i < (w * h); i++)
    {
        SPIWriteData(color);
    }
    DI_CS = 1;
    Delayms(1);
}

void DrawPixel(unsigned int x, unsigned int y, unsigned char color)
{
    while( !SPITBE );

    DI_CS = 0;
    Delayms(1);
	DisplayXY( x, y, x, y );
    SPIWriteData(color);
    DI_CS = 1;
    Delayms(1);
}
