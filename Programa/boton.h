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
#ifndef _BOTON_H_
#define	_BOTON_H_

void InitBotones( void* handler );

void BotonAdd(  const char *name, const char *cmd,
                unsigned int x, unsigned int y,
                unsigned int w, unsigned int h,
                unsigned int f_color, unsigned int b_color, unsigned int n_color);

void BotonDraw( void );
int BotonTask( unsigned int x, unsigned int y );

#endif	/* _BOTON_H_ */

