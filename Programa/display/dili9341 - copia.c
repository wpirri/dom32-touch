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
    SPIWriteCommand(0xCB);  
    SPIWriteData(0x39); 
    SPIWriteData(0x2C); 
    SPIWriteData(0x00); 
    SPIWriteData(0x34); 
    SPIWriteData(0x02); 

    SPIWriteCommand(0xCF);  
    SPIWriteData(0x00); 
    SPIWriteData(0XC1); 
    SPIWriteData(0X30); 

    SPIWriteCommand(0xE8);  
    SPIWriteData(0x85); 
    SPIWriteData(0x00); 
    SPIWriteData(0x78); 

    SPIWriteCommand(0xEA);  
    SPIWriteData(0x00); 
    SPIWriteData(0x00); 
 
    SPIWriteCommand(0xED);  
    SPIWriteData(0x64); 
    SPIWriteData(0x03); 
    SPIWriteData(0X12); 
    SPIWriteData(0X81); 

    SPIWriteCommand(0xF7);  
    SPIWriteData(0x20); 
  
    SPIWriteCommand(0xC0);    //Power control 
    SPIWriteData(0x23);   //VRH[5:0] 
 
    SPIWriteCommand(0xC1);    //Power control 
    SPIWriteData(0x10);   //SAP[2:0];BT[3:0] 

    SPIWriteCommand(0xC5);    //VCM control 
    //Contrast
    //SPIWriteData(0x3e);
    //SPIWriteData(0x28); 
    SPIWriteData(0x2b); 
    SPIWriteData(0x2b); 
 
    //VCM control2 
    //SPIWriteCommand(0xC7);    
    //SPIWriteData(0x86);
 
    SPIWriteCommand(0x36);    // Memory Access Control 
    SPIWriteData(0x48);   

    //SPIWriteCommand(0x3A);    
    //SPIWriteData(0x55); 

    SPIWriteCommand(0xB1);    
    SPIWriteData(0x00);  
    SPIWriteData(0x18); 
 
    SPIWriteCommand(0xB6);    // Display Function Control 
    //SPIWriteData(0x08); 
    //SPIWriteData(0x82);
    //SPIWriteData(0x27);  
    SPIWriteData(0x0a);
    SPIWriteData(0x02);

    SPIWriteCommand(0xF2);    // 3Gamma Function Disable 
    SPIWriteData(0x00); 
 
    SPIWriteCommand(0x26);    //Gamma curve selected 
    SPIWriteData(0x01); 

    SPIWriteCommand(0xE0);    //Set Gamma 
    SPIWriteData(0x0F); 
    SPIWriteData(0x31); 
    SPIWriteData(0x2B); 
    SPIWriteData(0x0C); 
    SPIWriteData(0x0E); 
    SPIWriteData(0x08); 
    SPIWriteData(0x4E); 
    SPIWriteData(0xF1); 
    SPIWriteData(0x37); 
    SPIWriteData(0x07); 
    SPIWriteData(0x10); 
    SPIWriteData(0x03); 
    SPIWriteData(0x0E); 
    SPIWriteData(0x09); 
    SPIWriteData(0x00); 

    SPIWriteCommand(0XE1);    //Set Gamma 
    SPIWriteData(0x00); 
    SPIWriteData(0x0E); 
    SPIWriteData(0x14); 
    SPIWriteData(0x03); 
    SPIWriteData(0x11); 
    SPIWriteData(0x07); 
    SPIWriteData(0x31); 
    SPIWriteData(0xC1); 
    SPIWriteData(0x48); 
    SPIWriteData(0x08); 
    SPIWriteData(0x0F); 
    SPIWriteData(0x0C); 
    SPIWriteData(0x31); 
    SPIWriteData(0x36); 
    SPIWriteData(0x0F); 

    //SPIWriteCommand(0x11);    //Exit Sleep 
    //Delayms(120); 
				
    //SPIWriteCommand(0x29);    //Display on 
    //SPIWriteCommand(0x2c);     
}

void DisplayXY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	SPIWriteCommand(0x2a);
	SPIWriteData(x1 >> 8);
	SPIWriteData(x1);
	SPIWriteData(x2 >> 8);
	SPIWriteData(x2);
    
	SPIWriteCommand(0x2b); 
	SPIWriteData(y1 >> 8);
	SPIWriteData(y1);
	SPIWriteData(y2 >> 8);
	SPIWriteData(y2);
    
	SPIWriteCommand(0x2c); 
}

