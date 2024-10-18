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
#include <xc.h>

#include "display.h"

#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../delay.h"

#include "font.h"

/******************* Pin and Register Definitions ********************/
// Chip Select Output bit

#define SET_DI_CS           (LATASET=(1<<4))
#define CLR_DI_CS           (LATACLR=(1<<4))
#define DI_CS_TRIS          TRISAbits.TRISA4
#define DI_CS_OC            ODCAbits.ODCA4

#define SET_DI_RD           (LATASET=(1<<0))
#define CLR_DI_RD           (LATACLR=(1<<0))
#define DI_RD_TRIS          TRISAbits.TRISA0
#define DI_RD_OC            ODCAbits.ODCA0

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

#define swap(a, b) { int t = a; a = b; b = t; }

void DisplayWriteData(unsigned char data);
void DisplayWriteCommand(unsigned char cmd);
void DisplayWriteLongCommand(unsigned int cmd);
void DrawChar(  unsigned int x, unsigned int y, unsigned char c, 
                unsigned int color,unsigned int bg, unsigned int size, bool mode);
void DrawCornerEmpty(unsigned int x0, unsigned int y0, unsigned int r, unsigned int corner, unsigned int color);
void DrawCornerFill(unsigned int x0, unsigned int y0, unsigned int r, unsigned int corner, unsigned int color);


int DisplayInit( void )
{
    DI_RESET_TRIS = 0;
    DI_RESET_OC = 0;
    DI_CS_TRIS = 0;
    DI_CS_OC = 0;
    DI_RD_TRIS = 0;
    DI_RD_OC = 0;
    DI_WR_TRIS = 0;
    DI_WR_OC = 0;
    DI_RS_TRIS = 0;
    DI_RS_OC = 0;
    DI_PORT_TRIS &= 0xFF00;
    DI_PORT_OC &= 0xFF00;

    Delayms(100);
    CLR_DI_RESET;   /* reset activado */
    SET_DI_CS;      /* display no seleccionado */
    SET_DI_RD;      /* modo lectura desactivado */
    SET_DI_WR;      /* modo escritura desactivado */
    SET_DI_RS;      /* modo comando desactivado */
    DI_PORT_OUT = (DI_PORT_IN & 0x00FF);
    Delayms(100);
    SET_DI_RESET;   /* levanto reset */
    Delayms(120);
    CLR_DI_CS;      /* Selecciono display */
    Delayms(1);
    Display_Init();
    SET_DI_CS;      /* display no seleccionado */
    Delayms(1);
    
    return 1;
}

void Clear( unsigned int color )
{
	long i;
	
    CLR_DI_CS;
	Display_XY( 0, 0, DISPLAY_X_SIZE-1, DISPLAY_Y_SIZE-1);
    for (i = 0; i < (DISPLAY_X_SIZE*DISPLAY_Y_SIZE); i++)
    {
        CLRWDT();
        DisplayWriteData((color >> 8) & 0x00FF);
        DisplayWriteData(color & 0x00FF);
    }
    SET_DI_CS;
}

void DrawPixel(unsigned int x, unsigned int y, unsigned int color)
{
    //Log("[DrawPixel] X: %u Y: %u Color: %0x%04X", x, y, color);
    CLR_DI_CS;
	Display_XY( x, y, x, y );
    DisplayWriteData((color >> 8) & 0x00FF);
    DisplayWriteData(color & 0x00FF);
    SET_DI_CS;
}

void DrawRectFill(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
	unsigned long i;
	
    CLR_DI_CS;
	Display_XY( x, y, x+w-1, y+h-1 );
    for (i = 0; i < (w * h); i++)
    {
        DisplayWriteData((color >> 8) & 0x00FF);
        DisplayWriteData(color & 0x00FF);
    }
    SET_DI_CS;
}

void DrawLineV(unsigned int x, unsigned int y, unsigned int h, unsigned int color)
{
    DrawRectFill(x, y, 1, h, color);
}

void DrawLineH(unsigned int x, unsigned int y, unsigned int w, unsigned int color)
{
    DrawRectFill(x, y, w, 1, color);
}

void DrawRectEmpty(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
    DrawLineH(x, y, w, color);
    DrawLineV(x, y, h, color);
    DrawLineH(x, y+h, w, color);
    DrawLineV(x+w, y, h, color);
}

void DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
{
	int steep = abs(y2 - y1) > abs(x2 - x1);
    
  	if (steep) 
	{
    	swap(x1, y1);
    	swap(x2, y2);
	}
	if (x1 > x2) 
	{
    	swap(x1, x2);
    	swap(y1, y2);
  	}
	
  	int dx, dy;
  	dx = x2 - x1;
  	dy = abs(y2 - y1);

	int err = dx / 2;
	int ystep;

	if (y1 < y2) 
	{
    	ystep = 1;
  	} 
	else 
	{
    	ystep = -1;
	}

	for (; x1<=x2; x1++) 
	{
    	if (steep) 
		{
      		DrawPixel(y1, x1, color);
    	} 
		else 
		{
      		DrawPixel(x1, y1, color);
    	}
    	err -= dy;
    	if (err < 0) 
		{
			y1 += ystep;
			err += dx;
    	}
  	}
}

void DrawCircleFill(unsigned int x, unsigned int y, unsigned int r, unsigned int color)
{
	DrawCornerFill(x, y, r, 0x0F, color);
}

void DrawCircleEmpty(unsigned int x, unsigned int y, unsigned int r, unsigned int color)
{
    DrawCornerEmpty(x, y, r, 0x0F, color);
}


void DrawTriangleEmpty( unsigned int x0, unsigned int y0, 
                        unsigned int x1, unsigned int y1,
                        unsigned int x2, unsigned int y2, 
                        unsigned int color)
{
    DrawLine(x0, y0, x1, y1, color);
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x0, y0, color);
}

void DrawTriangleFill( unsigned int x0, unsigned int y0, 
                        unsigned int x1, unsigned int y1,
                        unsigned int x2, unsigned int y2, 
                        unsigned int color)
{
	int a, b, y, last;
    
  	if (y0 > y1) 
	{
    	swap(y0, y1); 
		swap(x0, x1);
  	}
  	if (y1 > y2) 
	{
    	swap(y2, y1); 
		swap(x2, x1);
  	}
  	if (y0 > y1) 
	{
    	swap(y0, y1); 
		swap(x0, x1);
  	}

	if(y0 == y2) 
	{ 
    	a = b = x0;
    	if(x1 < a)
    	{
			a = x1;
    	}
    	else if(x1 > b)
    	{
			b = x1;
    	}
    	if(x2 < a)
    	{
			a = x2;
    	}
    	else if(x2 > b)
    	{
			b = x2;
    	}
    	DrawLineH(a, y0, b-a+1, color);
    	return;
	}
  	int dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
	long sa = 0, sb = 0;
    
	if(y1 == y2)
	{
		last = y1; 
	}
  	else
  	{
		last = y1-1; 
  	}

  	for(y=y0; y<=last; y++) 
	{
    	a   = x0 + sa / dy01;
    	b   = x0 + sb / dy02;
    	sa += dx01;
    	sb += dx02;
    	if(a > b)
    	{
			swap(a,b);
    	}
    	DrawLineH(a, y, b-a+1, color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
    	a   = x1 + sa / dy12;
    	b   = x0 + sb / dy02;
    	sa += dx12;
    	sb += dx02;
    	if(a > b)
    	{
			swap(a,b);
    	}
		DrawLineH(a, y, b-a+1, color);
	}
}

void DrawCornerEmpty(unsigned int x0, unsigned int y0, unsigned int r, unsigned int corner, unsigned int color)
{
	int f     = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x     = 0;
	int y     = r;
    
	while (x<y) 
	{
        CLRWDT();
    	if (f >= 0) 
		{
      		y--;
      		ddF_y += 2;
      		f += ddF_y;
    	}
	    x++;
	    ddF_x += 2;
	    f += ddF_x;
	    if (corner & 0x4) 
		{
			DrawPixel(x0 + x, y0 + y, color);
			DrawPixel(x0 + y, y0 + x, color);
	    } 
	    if (corner & 0x2) 
		{
			DrawPixel(x0 + x, y0 - y, color);
			DrawPixel(x0 + y, y0 - x, color);
	    }
	    if (corner & 0x8) 
		{
			DrawPixel(x0 - y, y0 + x, color);
			DrawPixel(x0 - x, y0 + y, color);
	    }
	    if (corner & 0x1)
		{
			DrawPixel(x0 - y, y0 - x, color);
	 		DrawPixel(x0 - x, y0 - y, color);
	    }
  	}
}

void DrawCornerFill(unsigned int x0, unsigned int y0, unsigned int r, unsigned int corner, unsigned int color)
{
	int f     = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x     = 0;
	int y     = r;
    
	while (x<y) 
	{
        CLRWDT();
    	if (f >= 0) 
		{
      		y--;
      		ddF_y += 2;
      		f += ddF_y;
    	}
	    x++;
	    ddF_x += 2;
	    f += ddF_x;
	    if (corner & 0x4) 
		{
			DrawLine(x0, y0, x0 + x, y0 + y, color);
			DrawLine(x0, y0, x0 + y, y0 + x, color);
	    } 
	    if (corner & 0x2) 
		{
			DrawLine(x0, y0, x0 + x, y0 - y, color);
			DrawLine(x0, y0, x0 + y, y0 - x, color);
	    }
	    if (corner & 0x8) 
		{
			DrawLine(x0, y0, x0 - y, y0 + x, color);
			DrawLine(x0, y0, x0 - x, y0 + y, color);
	    }
	    if (corner & 0x1)
		{
			DrawLine(x0, y0, x0 - y, y0 - x, color);
	 		DrawLine(x0, y0, x0 - x, y0 - y, color);
	    }
  	}
}

void DrawRoundRectangleFill(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2, unsigned int radius, unsigned int color)
{
    int i;
	int w = x2 - x1 + 1, h = y2 - y1 + 1;
	if (w < 0) 
	{ 
		x1 = x2; 
		w = -w; 
	}
 	if (h < 0) 
	{ 
		y1 = y2; 
		h = -h; 
	}


	DrawCornerFill(x1+radius, y1+radius, radius, 1, color);
	DrawCornerFill(x1+w-radius-1, y1+radius, radius, 2, color);
    for(i = y1; i < (y1+radius); i++)
    {
        DrawLineH(x1+radius, i, w-2*radius, color); 
    }
    for(i = i; i < (y1+h-radius); i++)
    {
        DrawLineH(x1, i, w, color); 
    }
    for(i = i; i < (y1+h); i++)
    {
        DrawLineH(x1+radius, i, w-2*radius, color); 
    }
	DrawCornerFill(x1+w-radius-1, y1+h-radius-1, radius, 4, color);
	DrawCornerFill(x1+radius, y1+h-radius-1, radius, 8, color);
}

void DrawRoundRectangleEmpty(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned int color)
{
	int w = x2 - x1 + 1, h = y2 - y1 + 1;
	if (w < 0) 
	{ 
		x1 = x2; 
		w = -w; 
	}
 	if (h < 0) 
	{ 
		y1 = y2; 
		h = -h; 
	}
	DrawLineH(x1+radius, y1, w-2*radius, color); 
	DrawLineH(x1+radius, y1+h-1, w-2*radius, color); 
	DrawLineV(x1, y1+radius, h-2*radius, color); 
  	DrawLineV(x1+w-1, y1+radius, h-2*radius, color);
	DrawCornerEmpty(x1+radius, y1+radius, radius, 1, color);
	DrawCornerEmpty(x1+w-radius-1, y1+radius, radius, 2, color);
	DrawCornerEmpty(x1+w-radius-1, y1+h-radius-1, radius, 4, color);
	DrawCornerEmpty(x1+radius, y1+h-radius-1, radius, 8, color);
}

void DrawText(const char* text, unsigned int x, unsigned int y,
            unsigned int size, unsigned int text_color, unsigned int bg_color)
{
	int pos;
	unsigned int len;
    unsigned int text_x, text_y;
    unsigned char ch;
	const char *p = (const char *)text;

	if (x == CENTER || x == RIGHT) 
	{
		len = strlen(text) * 6 * size;		
		pos = (DISPLAY_X_SIZE - len); 
		if (x == CENTER)
		{
			x = pos/2;
		}
		else
		{
			x = pos - 1;
		}
	}

    text_x = x;
    text_y = y;
	while(1)
	{
		ch = *(p++);

		if(ch == 0)
        {
            break;
        }
        else if (ch == '\n') 
        {
            text_y += (size * 8);
            text_x  = 0;
        } 
        else if(ch == '\r')
        {
        }
        else 
        {
            DrawChar(text_x, text_y, ch, text_color, bg_color, size, false);
            text_x += (size * 6);		
        }	
	}	
}

/* TODO: Revisar scrol que no funciona */
void VertScroll(unsigned int top, unsigned int scrollines, int offset)
{
    int bfa = DISPLAY_Y_SIZE - top - scrollines; 
    int vsp;
    
    if (offset <= -scrollines || offset >= scrollines)
    {
		offset = 0; //valid scroll
    }
	vsp = top + offset; // vertical start position
    if (offset < 0)
    {
        vsp += scrollines;          //keep in unsigned range
    }
    
    DisplayWriteLongCommand(0x0033);
    DisplayWriteData(top >> 8);         //TFA
    DisplayWriteData(top);
    DisplayWriteData(scrollines >> 8);  //VSA
    DisplayWriteData(scrollines);
    DisplayWriteData(bfa >> 8);         //BFA
    DisplayWriteData(bfa);
    
    DisplayWriteLongCommand(0x0037);
    DisplayWriteData(vsp >> 8);         //VSP
    DisplayWriteData(vsp);

    if (offset == 0) 
    {
        DisplayWriteLongCommand(0x0013);
    }
}

/* ************************************************************************* */
/* Solo uso interno */
/* ************************************************************************* */
void DisplayWriteData(unsigned char data)
{
    DI_PORT_OUT = ( (DI_PORT_IN & 0xFF00) | (data & 0x00FF) );
    CLR_DI_WR;
    SET_DI_WR;
}

void DisplayWriteCommand(unsigned char cmd)
{
    CLR_DI_RS;

    DI_PORT_OUT = ( (DI_PORT_IN & 0xFF00) | (cmd & 0x00FF) );
    CLR_DI_WR;
    SET_DI_WR;

    SET_DI_RS;
}

void DisplayWriteLongCommand(unsigned int cmd)
{
    CLR_DI_RS;

    DI_PORT_OUT = ( (DI_PORT_IN & 0xFF00) | ((cmd>>8) & 0x00FF) );
    CLR_DI_WR;
    SET_DI_WR;

    DI_PORT_OUT = ( (DI_PORT_IN & 0xFF00) | (cmd & 0x00FF) );
    CLR_DI_WR;
    SET_DI_WR;

    SET_DI_RS;
}

void DrawChar(  unsigned int x, unsigned int y, unsigned char c, 
                unsigned int color,unsigned int bg, unsigned int size, bool mode)
{
    unsigned char line;
    int i, j;

	if((x >= DISPLAY_X_SIZE) || (y >= DISPLAY_Y_SIZE) || ((x + 6 * size - 1) < 0) || ((y + 8 * size - 1) < 0))
	{
    	return;
	}
    
  	if(c >= 176)
  	{
		c++; 
  	}
    
	for (i = 0; i < 6; i++) 
	{
    	if (i == 5)
    	{
      		line = 0x0;
    	}
    	else
    	{
      		line = default_font[(c*5)+i];
    	}
    	for (j = 0; j < 8; j++) 
		{
      		if (line & 0x1) 
			{
        		if (size == 1)
        		{
        			DrawPixel(x+i, y+j, color);
        		}
        		else 
				{  
					DrawRectFill(x+(i*size), y+(j*size), size, size, color);
        		}
        	} 
			else if (bg != color) 				
			{
				if(!mode)
				{
	        		if (size == 1) 
	        		{
	        			DrawPixel(x+i, y+j, bg);
	        		}
	        		else 
					{  
						DrawRectFill(x+i*size, y+j*size, size, size, bg);
					}
				}
			}
      		line >>= 1;
    	}
    }
}
