/***************************************************************************
    Copyright (C) 2025   Walter Pirri

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
#ifndef _RTCC_H_
#define _RTCC_H_

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>


typedef struct tm bcdTime_t;

void RTCC_Initialize(void);
bool RTCC_TimeGet(struct tm *currentTime);
void RTCC_TimeSet(struct tm *initialTime);
bool RTCC_BCDTimeGet(bcdTime_t *currentTime);
void RTCC_BCDTimeSet(bcdTime_t *initialTime);

#endif // _RTCC_H_
