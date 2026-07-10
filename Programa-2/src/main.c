/***************************************************************************
    Copyright (C) 2026   Walter Pirri

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

/* ****************************************************************************
 * Dom32Touch - Bastidor Tactil para sistema de dom�tica
 * 
 * PIC21MM00256GPM028
 * ESP-WROOM-02D
 * MicroSD
 * Display 2.4'' c/Driver ILI9341
 * Touch resistivo
 * 
 * Asignacion de pines del procesador
 * 
 *      Port        Funcionalidad       Conectado a
 * ----------------------------------------------------------------------------
 * 01   MCLR        Reset               Tact Switch
 * 02   RA0         OUT                 Display Back Ligth
 * 03   RA1         OUT                 Display Reset
 * 04   RB0         OUT                 Display Data0   
 * 05   RB1         OUT                 Display Data1   
 * 06   RB2         OUT                 Display Data2
 * 07   RB3         OUT                 Display Data3
 * 08   Vss
 * 09   RA2/AN5     OUT                 Display WR      (Touch YP)
 * 10   RA3/AN6     OUT                 Display RS/CD   (Touch XM)
 * 11   RB4         OUT                 Display Data4
 * 12   RA4         OUT                 Display CS
 * 13   Vdd
 * 14   RB5         OUT                 Display Data5
 * 15   RB6         OUT                 Display Data6   (Touch XP)
 * 16   RB7         OUT                 Display Data7   (Touch YM)
 * 17   U3TX        U3TX -> RP13        WiFi Rx
 * 18   U3RX        U3RX -> RP14        WiFi Tx
 * 19   U2TX/RC9    U2TX -> RP18        Debug / Beep
 * 20   VCap
 * 21   RB10        OUT                 WiFi Reset
 * 22   RB11        OUT                 MicroSD CS
 * 23   Vusb
 * 24   SCK2OUT     SCK2OUT -> RP15     MicroSD SCK
 * 25   SDI2        SDI2 -> RP16        MicroSD MISO
 * 26   SDO2        SDO2 -> RP17        MicroSD MOSI
 * 27   AVss
 * 28   AVdd
 * 
 * **************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "system.h"
#include "log.h"
#include "sd/fsio.h"
#include "config.h"
#include "rtcc.h"
#include "display/display.h"
#include "display/touch.h"
#include "wifi/wifi.h"
#include "control.h"
#include "http.h"

int main(void)
{
    bool status_sd_ok = false;
   
    SystemInit();
    
    LogInit(true, false);
    
    if( FSInit() )
    {
        status_sd_ok = true;
        LogMessage("[MAIN] File System Ok");
    }
    else
    {
        status_sd_ok = false;
        LogMessage("[MAIN] File System Error");
    }
    LogMessage("[MAIN] Compilacion " __DATE__ " " __TIME__ ".");
    LogMessage("[MAIN] Compilador " __VERSION__ ".");
    
    FSremove(FIRMWARE_FILENAME);

    LogMessage("[MAIN] Configuracion");
    ConfigInit();
    if(status_sd_ok) ConfigLoad();
    DumpConfig();

    LogMessage("[MAIN] Init RTCC");
    RTCC_Initialize();

    LogMessage("[MAIN] Init Display");
    DisplayInit();
    DisplayBrillo(g_wifi_config.u.config.brillo_max);

    LogMessage("[MAIN] Init Touch");
    TouchInit();

    LogMessage("[MAIN] Init WiFi");
    WiFiInit();

    LogMessage("[MAIN] Init Http");
    HttpInit();
    
    LogMessage("[MAIN] Init STM");
    ControlInit(status_sd_ok);
    /* Reset POR y BOR 
       Se hace a lo último así las distintas inicializaciones pueden verificar
       si vengo de un Power On */
    if(RCONbits.POR || RCONbits.BOR)
    {
        /* Power-Up*/
    }
    RCONbits.POR = 0;
    RCONbits.BOR = 0;

    LogMessage("[MAIN] Init End");
    while(1)
    {
        CLRWDT();
        ControlTask();
        Control_Screen_Task();
        Control_WiFi_Task();
    }
    return 0;
}
