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
    AD1CON1bits.FORM = 0b00;
    AD1CON2bits.SMPI = 0;
}

bool TouchIsPressed( unsigned int *x, unsigned int *y, unsigned int *z )
{
    bool pressed, xp_tris, xm_tris, yp_tris, ym_tris;
    unsigned int yp, xm;
    unsigned int z1, z2;
    float rtouch;

    xp_tris = TOUCH_XP_TRIS;
    xm_tris = TOUCH_XM_TRIS;
    yp_tris = TOUCH_YP_TRIS;
    ym_tris = TOUCH_YM_TRIS;
    pressed = false;

    
    /* ************************** */
    TOUCH_YP_TRIS = 1;
    TOUCH_YM_TRIS = 1;
    TOUCH_XP_TRIS = 0;
    TOUCH_XM_TRIS = 0;

    TOUCH_YP_ANA = 1;
    TOUCH_XM_ANA = 0;

    TOUCH_XP = 1;
    TOUCH_XM = 0;

	// Select RA2/AN5 input
    AD1CHSbits.CH0SA = 5;
	// Turn on the ADC
	AD1CON1bits.ON = 1;
	// Start sampling...
	AD1CON1bits.SAMP = 5;
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
    yp = ((ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3+ADC1BUF4)/5);
    // Turn off the ADC
    AD1CON1bits.ON = 0;
    /* ************************** */
    TOUCH_YP_TRIS = 0;
    TOUCH_YM_TRIS = 0;
    TOUCH_XP_TRIS = 1;
    TOUCH_XM_TRIS = 1;

    TOUCH_YP_ANA = 0;
    TOUCH_XM_ANA = 1;

    TOUCH_YP = 1;
    TOUCH_YM = 0;
    
	// Select RA3/AN6 input
    AD1CHSbits.CH0SA = 6;
	// Turn on the ADC
	AD1CON1bits.ON = 1;
	// Start sampling...
	AD1CON1bits.SAMP = 5;
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
    xm = ((ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3+ADC1BUF4)/5);
    // Turn off the ADC
    AD1CON1bits.ON = 0;
    /* ************************** */
    if(y) *y = yp;
    if(x) *x = xm;
    /* ************************** */
    TOUCH_XP_TRIS = 0;
    TOUCH_XP = 0;
    TOUCH_YM_TRIS = 0;
    TOUCH_YM = 1;

    TOUCH_XM_TRIS = 1;
    TOUCH_XM_ANA = 1;
    TOUCH_YP_TRIS = 1;
    TOUCH_YP_ANA = 1;

    // Leo analog YP (AN5)






    
    


    // Get ADC value
    z2 = ADC1BUF0;
    /* ************************** */
    // Leo analog XM (AN6)

    
    
    
    
    
    
    
    
    
    
    // Get ADC value
    z1 = ADC1BUF0;
    /* ************************** */
    
    rtouch = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= xm;
    rtouch *= 300;
    rtouch /= 1024;

    if(z) *z = rtouch;   
    
    TOUCH_XM_ANA = 0;
    TOUCH_YP_ANA = 0;
    TOUCH_XP_TRIS = xp_tris;
    TOUCH_XM_TRIS = xm_tris;
    TOUCH_YP_TRIS = yp_tris;
    TOUCH_YM_TRIS = ym_tris;
    return pressed;
}
