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
#ifndef _DI_BUS_H_
#define	_DI_BUS_H_

#include <xc.h>
#include <stdbool.h>

#include "dili9341.h"
#include "touch.h"

                             /*  r     g    b */
#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define MAGENTA      0xF81F  /* 255,   0, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x780F  /* 128,   0, 128 */
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xFD20  /* 255, 165,   0 */
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF81F  /* 255,   0, 255 */

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define RGB(r,g,b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

/******************* Pin and Register Definitions ********************/
// Chip Select Output bit

#define SET_DI_CS           (LATASET=(1<<4))
#define CLR_DI_CS           (LATACLR=(1<<4))
#define DI_CS_TRIS          TRISAbits.TRISA4
#define DI_CS_OC            ODCAbits.ODCA4

//#define SET_DI_RD           (LATASET=(1<<0))
//#define CLR_DI_RD           (LATACLR=(1<<0))
//#define DI_RD_TRIS          TRISAbits.TRISA0
//#define DI_RD_OC            ODCAbits.ODCA0

#define SET_DI_WR           (LATASET=(1<<2))
#define CLR_DI_WR           (LATACLR=(1<<2))
#define DI_WR_TRIS          TRISAbits.TRISA2
#define DI_WR_OC            ODCAbits.ODCA2
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
// Back Ligth
#define SET_DI_BKL          (LATASET=(1<<0))
#define CLR_DI_BKL          (LATACLR=(1<<0))
#define DI_BKL_TRIS         TRISAbits.TRISA0
#define DI_BKL_OC           ODCAbits.ODCA0

int DisplayInit( void );

void DisplaySleep( unsigned int on_off);

void Clear( unsigned int color );
void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
void DrawRectFill(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
void DrawLineV(unsigned int x, unsigned int y, unsigned int h, unsigned int color);
void DrawLineH(unsigned int x, unsigned int y, unsigned int w, unsigned int color);
void DrawRectEmpty(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
void DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
void DrawCircleFill(unsigned int x, unsigned int y, unsigned int r, unsigned int color);
void DrawCircleEmpty(unsigned int x, unsigned int y, unsigned int r, unsigned int color);
void DrawTriangleEmpty( unsigned int x0, unsigned int y0, 
                        unsigned int x1, unsigned int y1,
                        unsigned int x2, unsigned int y2, 
                        unsigned int color);
void DrawTriangleFill( unsigned int x0, unsigned int y0, 
                        unsigned int x1, unsigned int y1,
                        unsigned int x2, unsigned int y2, 
                        unsigned int color);
void DrawCornerEmpty(unsigned int x0, unsigned int y0, unsigned int r, unsigned int corner, unsigned int color);
void DrawRoundRectangleFill(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2, unsigned int radius, unsigned int color);
void DrawRoundRectangleEmpty(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned int color);
void DrawText(const char* text, unsigned int x, unsigned int y,
            unsigned int size, unsigned int text_color, unsigned int bg_color);
void VertScroll(unsigned int top, unsigned int scrollines, int offset);

void DrawSampleScreen( void );

#endif	/* _DI_BUS_H_ */

