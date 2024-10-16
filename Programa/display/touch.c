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

#include "touch.h"

#include "../config.h"
#include "../log.h"
#include "dili9341.h"

#define TOUCH_XP        LATBbits.LATB6
#define TOUCH_XP_TRIS   TRISBbits.TRISB6

#define TOUCH_XM        LATAbits.LATA3
#define TOUCH_XM_TRIS   TRISAbits.TRISA3
#define TOUCH_XM_ANA    ANSELAbits.ANSA3    /* AN6 */

#define TOUCH_YP        LATAbits.LATA2
#define TOUCH_YP_TRIS   TRISAbits.TRISA2
#define TOUCH_YP_ANA    ANSELAbits.ANSA2    /* AN5 */

#define TOUCH_YM        LATBbits.LATB7
#define TOUCH_YM_TRIS   TRISBbits.TRISB7

#define MUESTREOS_ADC       5

#define swap(a, b) { int t = a; a = b; b = t; }

unsigned int ReadADCChannel(unsigned int channel);

unsigned int ReadTouchX();
unsigned int ReadTouchY();
unsigned int ReadTouchPressure();

unsigned int touch_max_x;
unsigned int touch_min_x;
unsigned int touch_max_y;
unsigned int touch_min_y;

void TouchInit( void )
{
    AD1CON2bits.VCFG = 0 ;
	// Clock from peripheral clock TPB
	AD1CON3bits.ADRC = 0;
	// ADC clock TAD = 8 peripheral clock TPB
	AD1CON3bits.ADCS = 8;
    // Set auto conversion trigger
    AD1CON1bits.SSRC = 7;
    AD1CON3bits.SAMC = 0b10000;
    AD1CON1bits.FORM = 0b100;
    AD1CON2bits.SMPI = 0;
    
    touch_max_x = TOUCH_MAX_X;
    touch_min_x = TOUCH_MIN_X;
    touch_max_y = TOUCH_MAX_Y;
    touch_min_y = TOUCH_MIN_Y;
}

bool TouchIsPressed( unsigned int *x, unsigned int *y, unsigned int *z )
{
    bool xp_tris, xm_tris, yp_tris, ym_tris;
    unsigned int yp, xm, zz;

    /* Copio los estados de los pines que voy a usar */
    xp_tris = TOUCH_XP_TRIS;
    xm_tris = TOUCH_XM_TRIS;
    yp_tris = TOUCH_YP_TRIS;
    ym_tris = TOUCH_YM_TRIS;

    // Leo analog YP (AN5)
    yp = ReadTouchY();
    // Leo analog XM (AN6)
    xm = ReadTouchX();
    //
    zz = ReadTouchPressure();

    Log("[TouchIsPressed] X: %u Y: %u Z: %u", xm, yp, zz);

    if(y) *y = yp;
    if(x) *x = xm;
    if(z) *z = zz;   

    /* Devuelvo todo a su estado anterior */
    TOUCH_XM_ANA = 0;
    TOUCH_YP_ANA = 0;
    TOUCH_XP_TRIS = xp_tris;
    TOUCH_XM_TRIS = xm_tris;
    TOUCH_YP_TRIS = yp_tris;
    TOUCH_YM_TRIS = ym_tris;
    
    return (zz < 1000);
}

unsigned int ReadADCChannel(unsigned int channel)
{
    int i, j;
    unsigned int muestras[MUESTREOS_ADC];
    
	// Select input ANx
    AD1CHSbits.CH0SA = channel;
	// Turn on the ADC
	AD1CON1bits.ON = 1;
    for(i = 0; i < MUESTREOS_ADC; i++)
    {
        // Start sampling...
        AD1CON1bits.SAMP = 1;
        // Delay at least 1 TAD
        Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop();
        Nop(); Nop(); Nop(); Nop();
        // Reset ADC interrupt flag
        IFS1CLR = _IFS1_AD1IF_MASK;
        // Start converting ...
        AD1CON1bits.SAMP = 0;
        // Wait for the result
        while (IFS1bits.AD1IF == 0);
        // Get ADC value
        muestras[i] = ADC1BUF0;
    }
    // Turn off the ADC
    AD1CON1bits.ON = 0;
    
    /* Ordeno */
    for(i = 0; i < (MUESTREOS_ADC-1); i++)
    {
        for(j = i; j < (MUESTREOS_ADC-1); j++)
        {
            if(muestras[j] > muestras[j+1])
            {
               swap(muestras[j], muestras[j+1]);
            }
        }
    }
    Log("[ReadADCChannel] muestras: %u %u [%u] %u %u",
            muestras[0],muestras[1],muestras[2],muestras[3],muestras[4]);
    /* Devuelvo el del medio */
    return muestras[MUESTREOS_ADC/2];
}

unsigned int ReadTouchX()
{
    TOUCH_YP_TRIS = 0;
    TOUCH_YM_TRIS = 0;
    TOUCH_XP_TRIS = 1;
    TOUCH_XM_TRIS = 1;

    TOUCH_YP_ANA = 0;
    TOUCH_XM_ANA = 1;

    TOUCH_YP = 1;
    TOUCH_YM = 0;
    
    // Leo analog XM (AN6)
    return ReadADCChannel(6);
}

unsigned int ReadTouchY()
{
    TOUCH_YP_TRIS = 1;
    TOUCH_YM_TRIS = 1;
    TOUCH_XP_TRIS = 0;
    TOUCH_XM_TRIS = 0;

    TOUCH_YP_ANA = 1;
    TOUCH_XM_ANA = 0;

    TOUCH_XP = 1;
    TOUCH_XM = 0;

    // Leo analog YP (AN5)
    return ReadADCChannel(5);
}

unsigned int ReadTouchPressure()
{
    unsigned long z0;
    unsigned int z1, z2;
    
    TOUCH_XP_TRIS = 0;
    TOUCH_XP = 0;
    TOUCH_YM_TRIS = 0;
    TOUCH_YM = 1;

    TOUCH_XM_TRIS = 1;
    TOUCH_XM_ANA = 1;
    TOUCH_YP_TRIS = 1;
    TOUCH_YP_ANA = 1;

    // Leo analog YP (AN5)
    z2 = ReadADCChannel(5);
    // Leo analog XM (AN6)
    z1 = ReadADCChannel(6);
    
    if(z1 > 20 && z2 < 1000)
    {
        z1 = 1023 - z1;
        z0 = (z1+z2)/2;
    }
    else
    {
        z0 = 1023;
    }
    
    return (unsigned int)z0;
    
}

unsigned int Touch2DisplayX(unsigned int xt)
{
    if(xt > touch_max_x) 
    {
        touch_max_x = xt;
    }

    if(xt < touch_min_x) 
    {
        touch_min_x = xt;
    }

    return ((xt-touch_min_x)*DISPLAY_X_SIZE/(touch_max_x-touch_min_x));
}

unsigned int Touch2DisplayY(unsigned int yt)
{
    if(yt > touch_max_y) 
    {
        touch_max_y = yt;
    }

    if(yt < touch_min_y) 
    {
        touch_min_y = yt;
    }

    return ((yt-touch_min_y)*DISPLAY_Y_SIZE/(touch_max_y-touch_min_y));
}
