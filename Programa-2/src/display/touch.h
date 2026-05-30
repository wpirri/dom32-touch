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
#ifndef _TOUCH_H_
#define	_TOUCH_H_

#include <xc.h>
#include <stdbool.h>

#define TOUCH_XP_TRIS   TRISBbits.TRISB6
#define SET_TOUCH_XP    (LATBSET=(1<<6))
#define CLR_TOUCH_XP    (LATBCLR=(1<<6))

#define TOUCH_XM_TRIS   TRISAbits.TRISA3
#define SET_TOUCH_XM    (LATASET=(1<<3))
#define CLR_TOUCH_XM    (LATACLR=(1<<3))
#define TOUCH_XM_ANA    ANSELAbits.ANSA3    /* AN6 */

#define TOUCH_YP_TRIS   TRISAbits.TRISA2
#define SET_TOUCH_YP    (LATASET=(1<<2))
#define CLR_TOUCH_YP    (LATACLR=(1<<2))
#define TOUCH_YP_ANA    ANSELAbits.ANSA2    /* AN5 */

#define TOUCH_YM_TRIS   TRISBbits.TRISB7
#define SET_TOUCH_YM    (LATBSET=(1<<7))
#define CLR_TOUCH_YM    (LATBCLR=(1<<7))

void TouchInit( void );
bool TouchIsPressed( unsigned int *x, unsigned int *y, unsigned int *z );

unsigned int Touch2DisplayX(unsigned int xt);
unsigned int Touch2DisplayY(unsigned int yt);


#endif	/* _TOUCH_H_ */

