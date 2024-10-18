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
#ifndef _BITMAP_H_
#define	_BITMAP_H_

int DrawBitmap(const char *filename, unsigned int x0, unsigned int y0);
unsigned int GetBitmapW(const char *filename);
unsigned int GetBitmapH(const char *filename);




#endif	/* _BITMAP_H_ */

