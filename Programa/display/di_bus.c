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

#include "di_bus.h"

#include "../config.h"
#include "../delay.h"

#include "dili9341.h"

/******************* Pin and Register Definitions ********************/
// Chip Select Output bit

#define SET_DI_CS           (LATASET=(1<<2))
#define CLR_DI_CS           (LATACLR=(1<<2))
#define DI_CS_TRIS          TRISAbits.TRISA2
#define DI_CS_OC            ODCAbits.ODCA2

#define SET_DI_RD           (LATASET=(1<<0))
#define CLR_DI_RD           (LATACLR=(1<<0))
#define DI_RD_TRIS          TRISAbits.TRISA0
#define DI_RD_OC            ODCAbits.ODCA0

#define SET_DI_WR           (LATASET=(1<<4))
#define CLR_DI_WR           (LATACLR=(1<<4))
#define DI_WR_TRIS          TRISAbits.TRISA4
#define DI_WR_OC            ODCAbits.ODCA4
// 
#define SET_DI_RS           (LATASET=(1<<3))
#define CLR_DI_RS           (LATACLR=(1<<3))
#define DI_RS_TRIS          TRISAbits.TRISA3
#define DI_RS_OC            ODCAbits.ODCA3
// Reset
#define SET_DI_RESET        (LATASET=(1<<1))
#define CLR_DI_RESET        (LATACLR=(1<<1))
#define DI_RESET_TRIS       TRISAbits.TRISA1
#define DI_RESET_OC         ODCAbits.ODCA1
// Display Bus
#define DI_PORT_IN          PORTB
#define DI_PORT_OUT         LATB
#define DI_PORT_TRIS        TRISB
#define DI_PORT_OC          ODCB

void BUSWriteData(unsigned char data_out)
{
    DI_PORT_OUT = ( (DI_PORT_IN & 0xFF00) | (data_out & 0x00FF) );
    SET_DI_RD;
    CLR_DI_WR;
    Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();
    SET_DI_WR;
}
void BUSWriteCommand(unsigned char data_out)
{
    CLR_DI_RS;
    BUSWriteData(data_out);
    SET_DI_RS;
}

int BUSDisplayInit( void )
{
    DI_RESET_TRIS = 0;
    DI_RESET_OC = 0;
    DI_CS_TRIS = 0;
    DI_CS_OC = 0;
    DI_RD_TRIS = 0;
    DI_RD_OC = 0;
    DI_WR_TRIS = 0;
    DI_WR_OC = 0;
    DI_RS_TRIS = 0;
    DI_RS_OC = 0;
    DI_PORT_TRIS &= 0xFF00;
    DI_PORT_OC &= 0xFF00;

    Delayms(100);
    CLR_DI_RESET;   /* reset activado */
    SET_DI_CS;      /* display no seleccionado */
    SET_DI_RD;      /* modo lectura desactivado */
    SET_DI_WR;      /* modo escritura desactivado */
    SET_DI_RS;      /* modo comando desactivado */
    DI_PORT_OUT = (DI_PORT_IN & 0x00FF);
    Delayms(100);
    SET_DI_RESET;   /* levanto reset */
    Delayms(120);
    CLR_DI_CS;      /* Selecciono display */
    Delayms(1);
    DisplayInit();
    SET_DI_CS;      /* display no seleccionado */
    Delayms(1);
    
    return 1;
}

void BUSDisplayClear( unsigned char color )
{
	long i;
	
    CLR_DI_CS;
    Delayms(1);
	DisplayXY( 0, 0, DISPLAY_X_SIZE-1, DISPLAY_Y_SIZE-1);
    for (i = 0; i < (DISPLAY_X_SIZE*DISPLAY_Y_SIZE); i++)
    {
        CLRWDT();
        BUSWriteData(color);
    }
    Delayms(1);
    SET_DI_CS;
}

void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char color)
{
	long i;
	
    CLR_DI_CS;
    Delayms(1);
	DisplayXY( x, y, x+w-1, y+h-1 );
    for (i = 0; i < (w * h); i++)
    {
        BUSWriteData(color);
    }
    Delayms(1);
    SET_DI_CS;
}

void DrawPixel(unsigned int x, unsigned int y, unsigned char color)
{
    CLR_DI_CS;
    Delayms(1);
	DisplayXY( x, y, x, y );
    BUSWriteData(color);
    Delayms(1);
    SET_DI_CS;
}
