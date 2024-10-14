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

#include <stdbool.h>

#define BLACK   0x0000
#define BLUE    0xF800
#define RED     0x07E0
#define GREEN   0x001F
#define WHITE   0xFFFF

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

//#define RGB(r,g,b) (((r>>3)<<8)|((g>>3)<<3)|(b>>3))

int DisplayInit( void );

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
#endif	/* _DI_BUS_H_ */

