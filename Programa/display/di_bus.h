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

#define DI_BLACK 0x0000         ///< 0, 0, 0
#define DI_NAVY 0x000F          ///< 0, 0, 123
#define DI_DARKGREEN 0x03E0     ///< 0, 125, 0
#define DI_DARKCYAN 0x03EF      ///< 0, 125, 123
#define DI_MAROON 0x7800        ///< 123, 0, 0
#define DI_PURPLE 0x780F        ///< 123, 0, 123
#define DI_OLIVE 0x7BE0         ///< 123, 125, 0
#define DI_LIGHTGREY 0xC618     ///< 198, 195, 198
#define DI_DARKGREY 0x7BEF      ///< 123, 125, 123
#define DI_BLUE 0x001F          ///< 0, 0, 255
#define DI_GREEN 0x07E0         ///< 0, 255, 0
#define DI_CYAN 0x07FF          ///< 0, 255, 255
#define DI_RED 0xF800           ///< 255, 0, 0
#define DI_MAGENTA 0xF81F       ///< 255, 0, 255
#define DI_YELLOW 0xFFE0        ///< 255, 255, 0
#define DI_WHITE 0xFFFF         ///< 255, 255, 255
#define DI_ORANGE 0xFD20        ///< 255, 165, 0
#define DI_GREENYELLOW 0xAFE5   ///< 173, 255, 41
#define DI_PINK 0xFC18          ///< 255, 130, 198

#define RGB(r,g,b) ( r << 16 | g << 8 | b )

int BUSDisplayInit( void );

void BUSDisplayClear( unsigned char color );

void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char color);
void DrawPixel(unsigned int x, unsigned int y, unsigned char color);


#endif	/* _DI_BUS_H_ */

