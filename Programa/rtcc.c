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
#include "rtcc.h"

#include <xc.h>

#include "config.h"
#include "log.h"

static bool rtccTimeInitialized;
static bool RTCCTimeInitialized(void);
static uint8_t ConvertHexToBCD(uint8_t hexvalue);
static uint8_t ConvertBCDToHex(uint8_t bcdvalue);

int WeekDay(int year, int month, int day)
{
    static const int mnthTbl[]= {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 12};
	int y=year%100;			// just the year, remove the century part
	int centItem=(3-((year/100)%4))*2;
	int yearItem=y/12+y%12+(y%12)/4;
	int wDay=centItem+yearItem+mnthTbl[month-1]+day;
	if(month==1 || month==2)
	{	// Jan Feb correction, if leap year
		if( (y!=0 && y%4==0) || year%400==0)
		{
			wDay--;
		}
	}
	return wDay%7;
}

int g_rtcc_diferencia_anterior;

void RTCC_Initialize(void)
{
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY

    RTCCON1 = 0x00000000;
    RTCCON2 = 0x00000000;

    RTCCON1CLR = (1 << _RTCCON1_WRLOCK_POSITION);
    RTCCON1CLR = (1 << _RTCCON1_ON_POSITION);

    if(RCONbits.POR || RCONbits.BOR)
    {
        // set 2024/01/01 00:00:00
        RTCDATE = 0x24010101; //  Year/Month/Date/Wday
        RTCTIME = 0x000000;   //  hours/minutes/seconds
    }

    // DIV 15999; CLKSEL LPRC; FDIV 0; 
    RTCCON2 = 0x3E7F0001;
    RTCCON1SET = (1 << _RTCCON1_ON_POSITION);
    RTCCON1SET = (1 << _RTCCON1_WRLOCK_POSITION);

    SYSKEY = 0x00000000; //write invalid key to force lock
    
    g_rtcc_diferencia_anterior = 0;
}

bool RTCC_TimeGet(struct tm *currentTime)
{
    uint32_t register_value;
    if(RTCSTATbits.SYNC){
        return false;
    }
     
    register_value = RTCDATE;
    currentTime->tm_year = (ConvertBCDToHex((register_value & 0xFF000000) >> 24))+100;
    currentTime->tm_mon = (ConvertBCDToHex((register_value & 0xFF0000) >> 16)-1);
    currentTime->tm_mday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_wday = ConvertBCDToHex(register_value & 0xF);
    
    register_value = RTCTIME;
    currentTime->tm_hour = ConvertBCDToHex((register_value & 0xFF000000) >> 24);
    currentTime->tm_min = ConvertBCDToHex((register_value & 0xFF0000) >> 16);
    currentTime->tm_sec = ConvertBCDToHex((register_value & 0xFF00) >> 8);

    return true;
}

void RTCC_TimeSet(struct tm *initialTime)
{
    struct tm oldTime;

    RTCC_TimeGet(&oldTime);
    
    LogMessage("[RTCC_TimeSet] Cambio de hora [%i/%02i/%02i %02i:%02i:%02i] -> [%i/%02i/%02i %02i:%02i:%02i].",
            oldTime.tm_year+1900, oldTime.tm_mon+1, oldTime.tm_mday, oldTime.tm_hour,
            oldTime.tm_min, oldTime.tm_sec,initialTime->tm_year+1900, initialTime->tm_mon+1,
            initialTime->tm_mday, initialTime->tm_hour, initialTime->tm_min, initialTime->tm_sec);

    initialTime->tm_wday = WeekDay(initialTime->tm_year+1900, 
                                    initialTime->tm_mon+1, 
                                    initialTime->tm_mday);

    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY

    RTCCON1CLR = (1 << _RTCCON1_WRLOCK_POSITION);
    RTCCON1CLR = (1 << _RTCCON1_ON_POSITION);

    // set RTCC initial time
    RTCDATE = (ConvertHexToBCD(initialTime->tm_year-100) << 24) | 
                (ConvertHexToBCD(initialTime->tm_mon+1) << 16 ) | 
                (ConvertHexToBCD(initialTime->tm_mday) << 8) | 
                ConvertHexToBCD(initialTime->tm_wday) ; // YEAR/MONTH/DAY/WEEKDAY
    RTCTIME = (ConvertHexToBCD(initialTime->tm_hour) << 24) | 
                (ConvertHexToBCD(initialTime->tm_min) << 16 ) | 
                (ConvertHexToBCD(initialTime->tm_sec) << 8) ; // HOURS/MINUTES/SECOND

    RTCCON1SET = (1 << _RTCCON1_ON_POSITION);
    RTCCON1SET = (1 << _RTCCON1_WRLOCK_POSITION);

    // System Reg Lock
    SYSKEY = 0x00000000; 
}

bool RTCC_BCDTimeGet(bcdTime_t *currentTime)
{
    uint32_t register_value;
    if(RTCSTATbits.SYNC){
        return false;
    }
    
    register_value = RTCDATE;
    currentTime->tm_year = (register_value & 0xFF000000) >> 24;
    currentTime->tm_mon = (register_value & 0xFF0000) >> 16;
    currentTime->tm_mday = (register_value & 0xFF00) >> 8;
    currentTime->tm_wday = (register_value & 0xF);
    
    register_value = RTCTIME;
    currentTime->tm_hour = (register_value & 0xFF000000) >> 24;
    currentTime->tm_min = (register_value & 0xFF0000) >> 16;
    currentTime->tm_sec = (register_value & 0xFF00) >> 8;
    
    return true;
}

void RTCC_BCDTimeSet(bcdTime_t *initialTime)
{
    // System Reg Unlock
    SYSKEY = 0x00000000; 
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
    
    RTCCON1CLR = (1 << _RTCCON1_WRLOCK_POSITION);
    RTCCON1CLR = (1 << _RTCCON1_ON_POSITION);

    // set RTCC initial time
    RTCDATE = (initialTime->tm_year << 24) | (initialTime->tm_mon << 16 ) | (initialTime->tm_mday << 8) | (initialTime->tm_wday) ; // YEAR/MONTH-1/DAY-1/WEEKDAY
    RTCTIME = (initialTime->tm_hour << 24) | (initialTime->tm_min << 16 ) | (initialTime->tm_sec << 8) ; // HOURS/MINUTES/SECOND

    // Enable RTCC  
    RTCCON1SET = (1 << _RTCCON1_ON_POSITION);

    // SET WRLOCK 
    RTCCON1SET = (1 << _RTCCON1_WRLOCK_POSITION);

    // System Reg Lock
    SYSKEY = 0x00000000; 
}

static uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (hexvalue / 10) << 4;
    bcdvalue = bcdvalue | (hexvalue % 10);
    return (bcdvalue);
}

static uint8_t ConvertBCDToHex(uint8_t bcdvalue)
{
    uint8_t hexvalue;
    hexvalue = (((bcdvalue & 0xF0) >> 4)* 10) + (bcdvalue & 0x0F);
    return hexvalue;
}
