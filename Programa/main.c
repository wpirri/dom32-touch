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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log.h"
#include "delay.h"
#include "sd/fsio.h"


int main(void)
{
    SearchRec f_record;

    ConfigInit();
    Delayms(100);
    LogInit();

    if(FSInit())
    {
        Log("[sd] Init Ok");

        if(FindFirst ("*.*", ATTR_MASK, &f_record) == 0)
        {
            Log("[sd] *** Archivos **********");
            do
            {
                Log(" - %s", f_record.filename);
            } while(FindNext(&f_record) == 0);
        }
    }
    else
    {
        Log("[sd] Init Error");
    }

    LATAbits.LATA4 = 1;
    Log("[main] Init Ok");
    while(1)
    {
        CLRWDT();
        LATAbits.LATA0 = 1 - PORTAbits.RA0;
        
        
        
        
        
        
        
    }
    return 0;
}
