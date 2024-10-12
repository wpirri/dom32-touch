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

void BUSWriteCommand(unsigned char data_out);
void BUSWriteData(unsigned char data_out);

void DisplayInit( void )
{
    BUSWriteCommand(0xCB);  
    BUSWriteData(0x39); 
    BUSWriteData(0x2C); 
    BUSWriteData(0x00); 
    BUSWriteData(0x34); 
    BUSWriteData(0x02); 

    BUSWriteCommand(0xCF);  
    BUSWriteData(0x00); 
    BUSWriteData(0XC1); 
    BUSWriteData(0X30); 

    BUSWriteCommand(0xE8);  
    BUSWriteData(0x85); 
    BUSWriteData(0x00); 
    BUSWriteData(0x78); 

    BUSWriteCommand(0xEA);  
    BUSWriteData(0x00); 
    BUSWriteData(0x00); 
 
    BUSWriteCommand(0xED);  
    BUSWriteData(0x64); 
    BUSWriteData(0x03); 
    BUSWriteData(0X12); 
    BUSWriteData(0X81); 

    BUSWriteCommand(0xF7);  
    BUSWriteData(0x20); 
  
    BUSWriteCommand(0xC0);    //Power control 
    BUSWriteData(0x23);   //VRH[5:0] 
 
    BUSWriteCommand(0xC1);    //Power control 
    BUSWriteData(0x10);   //SAP[2:0];BT[3:0] 

    BUSWriteCommand(0xC5);    //VCM control 
    BUSWriteData(0x3e);   //Contrast
    BUSWriteData(0x28); 
 
    BUSWriteCommand(0xC7);    //VCM control2 
    BUSWriteData(0x86);   //--
 
    BUSWriteCommand(0x36);    // Memory Access Control 
    BUSWriteData(0x48);   

    BUSWriteCommand(0x3A);    
    BUSWriteData(0x55); 

    BUSWriteCommand(0xB1);    
    BUSWriteData(0x00);  
    BUSWriteData(0x18); 
 
    BUSWriteCommand(0xB6);    // Display Function Control 
    BUSWriteData(0x08); 
    BUSWriteData(0x82);
    BUSWriteData(0x27);  

    BUSWriteCommand(0x11);    //Exit Sleep 
    Delayms(120); 
				
    BUSWriteCommand(0x29);    //Display on 
    BUSWriteCommand(0x2c); 
}

void DisplayXY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	BUSWriteCommand(DISPLAY_CMD_CASET);
	BUSWriteData(x1 >> 8);
	BUSWriteData(x1);
	BUSWriteData(x2 >> 8);
	BUSWriteData(x2);
    
	BUSWriteCommand(DISPLAY_CMD_PASET); 
	BUSWriteData(y1 >> 8);
	BUSWriteData(y1);
	BUSWriteData(y2 >> 8);
	BUSWriteData(y2);
    
	BUSWriteCommand(DISPLAY_CMD_RAMWR); 
}

