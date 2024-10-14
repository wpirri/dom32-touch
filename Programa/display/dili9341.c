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

void DisplayWriteCommand(unsigned char data_out);
void DisplayWriteData(unsigned char data_out);

void Display_Init( void )
{
    DisplayWriteCommand(0xCB);  
    DisplayWriteData(0x39); 
    DisplayWriteData(0x2C); 
    DisplayWriteData(0x00); 
    DisplayWriteData(0x34); 
    DisplayWriteData(0x02); 

    DisplayWriteCommand(0xCF);  
    DisplayWriteData(0x00); 
    DisplayWriteData(0XC1); 
    DisplayWriteData(0X30); 

    DisplayWriteCommand(0xE8);  
    DisplayWriteData(0x85); 
    DisplayWriteData(0x00); 
    DisplayWriteData(0x78); 

    DisplayWriteCommand(0xEA);  
    DisplayWriteData(0x00); 
    DisplayWriteData(0x00); 
 
    DisplayWriteCommand(0xED);  
    DisplayWriteData(0x64); 
    DisplayWriteData(0x03); 
    DisplayWriteData(0X12); 
    DisplayWriteData(0X81); 

    DisplayWriteCommand(0xF7);  
    DisplayWriteData(0x20); 
  
    DisplayWriteCommand(0xC0);    //Power control 
    DisplayWriteData(0x23);   //VRH[5:0] 
 
    DisplayWriteCommand(0xC1);    //Power control 
    DisplayWriteData(0x10);   //SAP[2:0];BT[3:0] 

    DisplayWriteCommand(0xC5);    //VCM control 
    DisplayWriteData(0x3e);   //Contrast
    DisplayWriteData(0x28); 
 
    DisplayWriteCommand(0xC7);    //VCM control2 
    DisplayWriteData(0x86);   //--
 
    DisplayWriteCommand(0x36);    // Memory Access Control 
    DisplayWriteData(0x48);   

    DisplayWriteCommand(0x3A);    
    DisplayWriteData(0x55); 

    DisplayWriteCommand(0xB1);    
    DisplayWriteData(0x00);  
    DisplayWriteData(0x18); 
 
    DisplayWriteCommand(0xB6);    // Display Function Control 
    DisplayWriteData(0x08); 
    DisplayWriteData(0x82);
    DisplayWriteData(0x27);  

    DisplayWriteCommand(0x11);    //Exit Sleep 
    Delayms(120); 
				
    DisplayWriteCommand(0x29);    //Display on 
    DisplayWriteCommand(0x2c); 
}

void Display_XY( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
{
	DisplayWriteCommand(0x2A);
	DisplayWriteData(x1 >> 8);
	DisplayWriteData(x1);
	DisplayWriteData(x2 >> 8);
	DisplayWriteData(x2);
    
	DisplayWriteCommand(0x2B); 
	DisplayWriteData(y1 >> 8);
	DisplayWriteData(y1);
	DisplayWriteData(y2 >> 8);
	DisplayWriteData(y2);
    
	DisplayWriteCommand(0x2C); 
}

