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

void SPIWriteCommand(unsigned char data_out);
void SPIWriteData(unsigned char data_out);

void DisplayInit( void )
{
    // Reset
    SPIWriteCommand(0x01);
    Delayms(150);
    SPIWriteCommand(0x28);  
    SPIWriteCommand(0x3A);  
    SPIWriteData(0x55); 
    
    // Init
    SPIWriteCommand(0xF6);  
    SPIWriteData(0x01); 
    SPIWriteData(0x01); 
    SPIWriteData(0x00); 
    SPIWriteCommand(0xCF);  
    SPIWriteData(0x00); 
    SPIWriteData(0X81); 
    SPIWriteData(0X30); 
    SPIWriteCommand(0xED);  
    SPIWriteData(0x64); 
    SPIWriteData(0x03); 
    SPIWriteData(0X12); 
    SPIWriteData(0X81); 
    SPIWriteCommand(0xE8);  
    SPIWriteData(0x85); 
    SPIWriteData(0x10); 
    SPIWriteData(0x78); 
    SPIWriteCommand(0xCB);  
    SPIWriteData(0x39); 
    SPIWriteData(0x2C); 
    SPIWriteData(0x00); 
    SPIWriteData(0x34); 
    SPIWriteData(0x02); 
    SPIWriteCommand(0xF7);  
    SPIWriteData(0x20); 
    SPIWriteCommand(0xEA);  
    SPIWriteData(0x00); 
    SPIWriteData(0x00); 
    SPIWriteCommand(0xB0);  
    SPIWriteData(0x00); 
    SPIWriteCommand(0xB1);  
    SPIWriteData(0x00); 
    SPIWriteData(0x1B); 
    SPIWriteCommand(0xB4);  
    SPIWriteData(0x00); 
    SPIWriteCommand(0xC0);  
    SPIWriteData(0x21); 
    SPIWriteCommand(0xC1);  
    SPIWriteData(0x11); 
    SPIWriteCommand(0xB1);  
    SPIWriteData(0x00); 
    SPIWriteCommand(0xC5);  
    SPIWriteData(0x3F); 
    SPIWriteData(0x3C); 
    SPIWriteCommand(0xC7);  
    SPIWriteData(0xB5); 
    SPIWriteCommand(0x36);  
    SPIWriteData(0x48); 
    SPIWriteCommand(0xF2);  
    SPIWriteData(0x00); 
    SPIWriteCommand(0x26);  
    SPIWriteData(0x01); 
    SPIWriteCommand(0xE0);    //Set Gamma 
    SPIWriteData(0x0F); 
    SPIWriteData(0x26); 
    SPIWriteData(0x24); 
    SPIWriteData(0x0B); 
    SPIWriteData(0x0E); 
    SPIWriteData(0x09); 
    SPIWriteData(0x54); 
    SPIWriteData(0xA8); 
    SPIWriteData(0x46); 
    SPIWriteData(0x0C); 
    SPIWriteData(0x17); 
    SPIWriteData(0x09); 
    SPIWriteData(0x0F); 
    SPIWriteData(0x07); 
    SPIWriteData(0x00); 

    SPIWriteCommand(0XE1);    //Set Gamma 
    SPIWriteData(0x00); 
    SPIWriteData(0x19); 
    SPIWriteData(0x1B); 
    SPIWriteData(0x04); 
    SPIWriteData(0x10); 
    SPIWriteData(0x07); 
    SPIWriteData(0x2A); 
    SPIWriteData(0x47); 
    SPIWriteData(0x39); 
    SPIWriteData(0x03); 
    SPIWriteData(0x06); 
    SPIWriteData(0x06); 
    SPIWriteData(0x30); 
    SPIWriteData(0x38); 
    SPIWriteData(0x0F); 
    
    Delayms(100);
    
    // Wake on
    SPIWriteCommand(0x11);
    Delayms(150);
    SPIWriteCommand(0x29);  
    
}

void DisplayXY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	SPIWriteCommand(0x2A);
	SPIWriteData(x1 >> 8);
	SPIWriteData(x1);
	SPIWriteData(x2 >> 8);
	SPIWriteData(x2);
    
	SPIWriteCommand(0x2B); 
	SPIWriteData(y1 >> 8);
	SPIWriteData(y1);
	SPIWriteData(y2 >> 8);
	SPIWriteData(y2);
    
	SPIWriteCommand(0x2c); 
}

