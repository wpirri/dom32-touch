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

#define DISPLAY_CMD_NOP        0x00     ///< No-op register
#define DISPLAY_CMD_SWRESET    0x01     ///< Software reset register
#define DISPLAY_CMD_RDDID      0x04     ///< Read display identification information
#define DISPLAY_CMD_RDDST      0x09     ///< Read Display Status

#define DISPLAY_CMD_SLPIN      0x10     ///< Enter Sleep Mode
#define DISPLAY_CMD_SLPOUT     0x11     ///< Sleep Out
#define DISPLAY_CMD_PTLON      0x12     ///< Partial Mode ON
#define DISPLAY_CMD_NORON      0x13     ///< Normal Display Mode ON

#define DISPLAY_CMD_RDMODE     0x0A     ///< Read Display Power Mode
#define DISPLAY_CMD_RDMADCTL   0x0B     ///< Read Display MADCTL
#define DISPLAY_CMD_RDPIXFMT   0x0C     ///< Read Display Pixel Format
#define DISPLAY_CMD_RDIMGFMT   0x0D     ///< Read Display Image Format
#define DISPLAY_CMD_RDSELFDIAG 0x0F     ///< Read Display Self-Diagnostic Result

#define DISPLAY_CMD_INVOFF     0x20     ///< Display Inversion OFF
#define DISPLAY_CMD_INVON      0x21     ///< Display Inversion ON
#define DISPLAY_CMD_GAMMASET   0x26     ///< Gamma Set
#define DISPLAY_CMD_DISPOFF    0x28     ///< Display OFF
#define DISPLAY_CMD_DISPON     0x29     ///< Display ON

#define DISPLAY_CMD_CASET      0x2A     ///< Column Address Set
#define DISPLAY_CMD_PASET      0x2B     ///< Page Address Set
#define DISPLAY_CMD_RAMWR      0x2C     ///< Memory Write
#define DISPLAY_CMD_RAMRD      0x2E     ///< Memory Read

#define DISPLAY_CMD_PTLAR      0x30     ///< Partial Area
#define DISPLAY_CMD_MADCTL     0x36     ///< Memory Access Control
#define DISPLAY_CMD_VSCRSADD   0x37     ///< Vertical Scrolling Start Address
#define DISPLAY_CMD_PIXFMT     0x3A     ///< COLMOD: Pixel Format Set

#define DISPLAY_CMD_FRMCTR1    0xB1     ///< Frame Rate Control (In Normal Mode/Full Colors)
#define DISPLAY_CMD_FRMCTR2    0xB2     ///< Frame Rate Control (In Idle Mode/8 colors)
#define DISPLAY_CMD_FRMCTR3    0xB3     ///< Frame Rate control (In Partial Mode/Full Colors)
#define DISPLAY_CMD_INVCTR     0xB4     ///< Display Inversion Control
#define DISPLAY_CMD_DFUNCTR    0xB6     ///< Display Function Control

#define DISPLAY_CMD_PWCTR1     0xC0     ///< Power Control 1
#define DISPLAY_CMD_PWCTR2     0xC1     ///< Power Control 2
#define DISPLAY_CMD_PWCTR3     0xC2     ///< Power Control 3
#define DISPLAY_CMD_PWCTR4     0xC3     ///< Power Control 4
#define DISPLAY_CMD_PWCTR5     0xC4     ///< Power Control 5
#define DISPLAY_CMD_VMCTR1     0xC5     ///< VCOM Control 1
#define DISPLAY_CMD_VMCTR2     0xC7     ///< VCOM Control 2

#define DISPLAY_CMD_RDID1      0xDA     ///< Read ID 1
#define DISPLAY_CMD_RDID2      0xDB     ///< Read ID 2
#define DISPLAY_CMD_RDID3      0xDC     ///< Read ID 3
#define DISPLAY_CMD_RDID4      0xDD     ///< Read ID 4

#define DISPLAY_CMD_GMCTRP1    0xE0     ///< Positive Gamma Correction
#define DISPLAY_CMD_GMCTRN1    0xE1     ///< Negative Gamma Correction

void DisplayInit( void );
void DisplayXY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );

#endif /* _DILI9341_H_ */