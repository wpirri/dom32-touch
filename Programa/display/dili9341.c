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
#include "dili9341.h"

#include "../delay.h"

void DisplayWriteCommand(unsigned char cmd);
void DisplayWriteData(unsigned char data);

void Display_Init( void )
{
    /* **** Display Arduino **** */
    DisplayWriteCommand(ILI9341_SOFTRESET);         //Soft Reset
    Delayms(50);
    DisplayWriteCommand(ILI9341_DISPLAYOFF);        //Display Off
    DisplayWriteCommand(ILI9341_INTERFACECONTROL);  //Interface Control needs EXTC=1 MV_EOR=0, TM=0, RIM=0
    DisplayWriteData(0x01);
    DisplayWriteData(0x01);
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_POWERCONTROLB);     //Power Control B [00 81 30]
    DisplayWriteData(0x00);
    DisplayWriteData(0x81);
    DisplayWriteData(0x30);
    DisplayWriteCommand(ILI9341_POWERONSEQ);        //Power On Seq [55 01 23 01]
    DisplayWriteData(0x64);
    DisplayWriteData(0x03);
    DisplayWriteData(0x12);
    DisplayWriteData(0x81);
    DisplayWriteCommand(ILI9341_DRIVERTIMINGA);     //Driver Timing A [04 11 7A]
    DisplayWriteData(0x85);
    DisplayWriteData(0x10);
    DisplayWriteData(0x78);
    DisplayWriteCommand(ILI9341_POWERCONTROLA);     //Power Control A [39 2C 00 34 02]
    DisplayWriteData(0x39);
    DisplayWriteData(0x2C);
    DisplayWriteData(0x00);
    DisplayWriteData(0x34);
    DisplayWriteData(0x02);
    DisplayWriteCommand(ILI9341_RUMPRATIO);         //Pump Ratio [10]
    DisplayWriteData(0x20);
    DisplayWriteCommand(ILI9341_DRIVERTIMINGB);     //Driver Timing B [66 00]
    DisplayWriteData(0x00);
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_RGBSIGNAL);         //RGB Signal [00] 
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_INVERSIONCONRTOL);  //Inversion Control [02] .kbv NLA=1, NLB=1, NLC=1
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_POWERCONTROL1);     //Power Control 1 [26]
    DisplayWriteData(0x21);
    DisplayWriteCommand(ILI9341_POWERCONTROL2);     //Power Control 2 [00]
    DisplayWriteData(0x11);
    DisplayWriteCommand(ILI9341_VCOMCONTROL1);      //VCOM 1 [31 3C]
    DisplayWriteData(0x3F);
    DisplayWriteData(0x3C);
    DisplayWriteCommand(ILI9341_VCOMCONTROL2);      //VCOM 2 [C0]
    DisplayWriteData(0xB5);
    DisplayWriteCommand(ILI9341_MEMCONTROL);
    DisplayWriteData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    DisplayWriteCommand(ILI9341_PIXELFORMAT);       //Pixel read=565, write=565.
    DisplayWriteData(0x55);
    DisplayWriteCommand(ILI9341_FRAMECONTROL);      //Frame Control [00 1B]
    DisplayWriteData(0x00);
    DisplayWriteData(0x1B);
    DisplayWriteCommand(ILI9341_MEMORYACCESS);      //Memory Access [00]
    DisplayWriteData(0x48);
    DisplayWriteCommand(ILI9341_ENABLE3G);          //Enable 3G [02]
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_GAMMASET);          //Gamma Set [01]
    DisplayWriteData(0x01);
    DisplayWriteCommand(ILI9341_UNDEFINE0);
    DisplayWriteData(0x0f);
    DisplayWriteData(0x26);
    DisplayWriteData(0x24);
    DisplayWriteData(0x0b);
    DisplayWriteData(0x0e);
    DisplayWriteData(0x09);
    DisplayWriteData(0x54);
    DisplayWriteData(0xa8);
    DisplayWriteData(0x46);
    DisplayWriteData(0x0c);
    DisplayWriteData(0x17);
    DisplayWriteData(0x09);
    DisplayWriteData(0x0f);
    DisplayWriteData(0x07);
    DisplayWriteData(0x00);
    DisplayWriteCommand(ILI9341_UNDEFINE1);
    DisplayWriteData(0x00);
    DisplayWriteData(0x19);
    DisplayWriteData(0x1b);
    DisplayWriteData(0x04);
    DisplayWriteData(0x10);
    DisplayWriteData(0x07);
    DisplayWriteData(0x2a);
    DisplayWriteData(0x47);
    DisplayWriteData(0x39);
    DisplayWriteData(0x03);
    DisplayWriteData(0x06);
    DisplayWriteData(0x06);
    DisplayWriteData(0x30);
    DisplayWriteData(0x38);
    DisplayWriteData(0x0f);
    DisplayWriteCommand(ILI9341_ENTRYMODE);
    DisplayWriteData(0x07);
    DisplayWriteCommand(ILI9341_SLEEPOUT);            //Sleep Out
    Delayms(150);
    DisplayWriteCommand(ILI9341_DISPLAYON);          //Display On
}

void Display_XY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	DisplayWriteCommand(ILI9341_COLADDRSET);
	DisplayWriteData(x1 >> 8);
	DisplayWriteData(x1);
	DisplayWriteData(x2 >> 8);
	DisplayWriteData(x2);
    
	DisplayWriteCommand(ILI9341_PAGEADDRSET); 
	DisplayWriteData(y1 >> 8);
	DisplayWriteData(y1);
	DisplayWriteData(y2 >> 8);
	DisplayWriteData(y2);
    
	DisplayWriteCommand(ILI9341_MEMORYWRITE); 
}

