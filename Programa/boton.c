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
#include "boton.h"

#include <string.h>

#include "display/di_bus.h"

#define MAX_BOTONES 10

typedef struct _BOTON
{
    char name[32];
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    unsigned int f_color;
    unsigned int b_color;
    unsigned int n_color;
} BOTON;

BOTON array_botones[MAX_BOTONES];

void (*BotonHandler)(const char* name);

void BotonDefaultHandler(const char* name){}



void InitBotones( void* handler )
{
    if(handler)
    {
        BotonHandler = handler;
    }
    else
    {
        BotonHandler = BotonDefaultHandler;
    }
    memset(array_botones, 0, sizeof(array_botones));
    
    
}

void BotonAdd(  const char *name, unsigned int x, unsigned int y,
                unsigned int w, unsigned int h,
                unsigned int f_color, unsigned int b_color, unsigned int n_color)
{
    int i;
    
    for(i = 0; i < MAX_BOTONES; i++)
    {
        if( !array_botones[i].name[0])
        {
            strcpy(array_botones[i].name, name);
            array_botones[i].x = x;
            array_botones[i].y = y;
            array_botones[i].w = w;
            array_botones[i].h = h;
            array_botones[i].f_color = f_color;
            array_botones[i].b_color = b_color;
            array_botones[i].n_color = n_color;
            break;
        }
    }
    
    
}

void BotonDraw( void )
{
    int i;
    
    for(i = 0; i < MAX_BOTONES; i++)
    {
        if( !array_botones[i].name[0]) break;
        DrawRoundRectangleFill(array_botones[i].x,
                array_botones[i].y, 
                array_botones[i].x+array_botones[i].w,
                array_botones[i].y+array_botones[i].h, 
                array_botones[i].h/5,
                array_botones[i].f_color);
        DrawRoundRectangleEmpty(array_botones[i].x,
                array_botones[i].y, 
                array_botones[i].x+array_botones[i].w,
                array_botones[i].y+array_botones[i].h, 
                array_botones[i].h/5,
                array_botones[i].b_color);
        DrawText(array_botones[i].name,
                array_botones[i].x+10,
                array_botones[i].y+10,
                2,
                array_botones[i].n_color,
                array_botones[i].f_color);
    }
}

void BotonTask( unsigned int x, unsigned int y )
{
    
}
