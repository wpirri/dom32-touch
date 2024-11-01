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

#include "display/display.h"
#include "sd/fsio.h"
#include "bitmap.h"
#include "log.h"

#define MAX_BOTONES 10
#define BOTON_TEXT_SIZE 3
#define BOTON_FONT_H 6
#define BOTON_FONT_W 6

typedef struct _BOTON
{
    char name[32];
    char cmd[64];
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    unsigned int f_color;
    unsigned int b_color;
    unsigned int n_color;
    char icon[FILE_NAME_SIZE+1];
} BOTON;

BOTON array_botones[MAX_BOTONES];

void (*BotonHandler)(const char* cmd);

void BotonDefaultHandler(const char* cmd){}



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

void BotonAdd(  const char *name, const char *cmd,
                unsigned int x, unsigned int y,
                unsigned int w, unsigned int h,
                unsigned int f_color, unsigned int b_color, unsigned int n_color,
                const char* icon_file)
{
    int i;
    
    for(i = 0; i < MAX_BOTONES; i++)
    {
        if( !array_botones[i].name[0])
        {
            strcpy(array_botones[i].name, name);
            if(cmd) strcpy(array_botones[i].cmd, cmd);
            else array_botones[i].cmd[0] = 0;
            array_botones[i].x = x;
            array_botones[i].y = y;
            array_botones[i].w = w;
            array_botones[i].h = h;
            array_botones[i].f_color = f_color;
            array_botones[i].b_color = b_color;
            array_botones[i].n_color = n_color;
            if(icon_file)
            {
                if(*icon_file)
                {
                    strcpy(array_botones[i].icon, icon_file);
                }
                else array_botones[i].icon[0] = 0;
            }
            else array_botones[i].icon[0] = 0;
            break;
        }
    }
    
    
}

void BotonDraw( void )
{
    int i;
    unsigned int text_x, text_y;
    unsigned int icon_offset_y;
    
    for(i = 0; i < MAX_BOTONES; i++)
    {
        if( !array_botones[i].name[0]) break;
        
        Log("[BotonDraw] %s X: %u Y: %u", array_botones[i].name, array_botones[i].x, array_botones[i].y);
        
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
        
        /* Centrado en el boton verticalmente */
        text_y = (array_botones[i].y + (array_botones[i].h / 2) - (BOTON_TEXT_SIZE * BOTON_FONT_H / 2));
        if(array_botones[i].icon[0])
        {
            /* Texto centrado entre el icono y el final del boton */
            text_x = (array_botones[i].x + ( (GetBitmapW(array_botones[i].icon)+(array_botones[i].h/5))/2) + (array_botones[i].w/2) - (strlen(array_botones[i].name) * BOTON_FONT_W * BOTON_TEXT_SIZE / 2));
        }
        else
        {
            /* Texto centrado en el boton */
            text_x = (array_botones[i].x + (array_botones[i].w/2) - (strlen(array_botones[i].name) * BOTON_FONT_W * BOTON_TEXT_SIZE / 2));
        }
        DrawText(array_botones[i].name,
                /* Posisión X del texto */
                text_x,
                /* Posisión Y del texto */
                text_y,
                BOTON_TEXT_SIZE,
                array_botones[i].n_color,
                array_botones[i].f_color);

        if(array_botones[i].icon[0])
        {
            icon_offset_y = array_botones[i].y + (array_botones[i].h/2) - (GetBitmapH(array_botones[i].icon)/2);
            DrawBitmapTransparent(array_botones[i].icon, array_botones[i].x + (array_botones[i].h/10), icon_offset_y);
        }
    }
}

int BotonTask( unsigned int x, unsigned int y )
{
    int i;
    
    
    for(i = 0; i < MAX_BOTONES; i++)
    {
        if( !array_botones[i].name[0]) break;
        if( x > array_botones[i].x &&
            x < (array_botones[i].x + array_botones[i].w) &&
            y > array_botones[i].y &&
            y < (array_botones[i].y + array_botones[i].h) )
        {
            (*BotonHandler)(array_botones[i].cmd);
            return 1;
        }
    }
    return 0;
}
