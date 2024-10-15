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
#ifndef _DILI9341_H_
#define	_DILI9341_H_

#define DISPLAY_X_SIZE 240
#define DISPLAY_Y_SIZE 320

#define ILI9341_SOFTRESET          0x01
#define ILI9341_SLEEPIN            0x10
#define ILI9341_SLEEPOUT           0x11
#define ILI9341_NORMALDISP         0x13
#define ILI9341_INVERTOFF          0x20
#define ILI9341_INVERTON           0x21
#define ILI9341_GAMMASET           0x26
#define ILI9341_DISPLAYOFF         0x28
#define ILI9341_DISPLAYON          0x29
#define ILI9341_COLADDRSET         0x2A
#define ILI9341_PAGEADDRSET        0x2B
#define ILI9341_MEMORYWRITE        0x2C
#define ILI9341_MEMORYACCESS       0x36
#define ILI9341_PIXELFORMAT        0x3A
#define ILI9341_RGBSIGNAL          0xB0
#define ILI9341_FRAMECONTROL       0xB1
#define ILI9341_INVERSIONCONRTOL   0xB4
#define ILI9341_DISPLAYFUNC        0xB6
#define ILI9341_ENTRYMODE          0xB7
#define ILI9341_POWERCONTROL1      0xC0
#define ILI9341_POWERCONTROL2      0xC1
#define ILI9341_VCOMCONTROL1       0xC5
#define ILI9341_VCOMCONTROL2       0xC7
#define ILI9341_POWERCONTROLB      0xCF
#define ILI9341_POWERCONTROLA      0xCB
#define ILI9341_UNDEFINE0          0xE0
#define ILI9341_UNDEFINE1          0xE1
#define ILI9341_DRIVERTIMINGA      0xE8
#define ILI9341_DRIVERTIMINGB      0xEA
#define ILI9341_POWERONSEQ         0xED
#define ILI9341_ENABLE3G           0xF2
#define ILI9341_INTERFACECONTROL   0xF6
#define ILI9341_RUMPRATIO          0xF7
#define ILI9341_MEMCONTROL         0x36
#define ILI9341_MADCTL             0x36

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04


void Display_Init( void );
void Display_XY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );

#endif /* _DILI9341_H_ */