/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for DEGUG_TX pin ***/
#define DEGUG_TX_Get()               ((PORTA >> 0) & 0x1)
#define DEGUG_TX_PIN                  GPIO_PIN_RA0

/*** Macros for LCD_WR pin ***/
#define LCD_WR_Set()               (LATASET = (1<<1))
#define LCD_WR_Clear()             (LATACLR = (1<<1))
#define LCD_WR_Toggle()            (LATAINV= (1<<1))
#define LCD_WR_OutputEnable()      (TRISACLR = (1<<1))
#define LCD_WR_InputEnable()       (TRISASET = (1<<1))
#define LCD_WR_Get()               ((PORTA >> 1) & 0x1)
#define LCD_WR_PIN                  GPIO_PIN_RA1

/*** Macros for LCD_D0 pin ***/
#define LCD_D0_Set()               (LATBSET = (1<<0))
#define LCD_D0_Clear()             (LATBCLR = (1<<0))
#define LCD_D0_Toggle()            (LATBINV= (1<<0))
#define LCD_D0_OutputEnable()      (TRISBCLR = (1<<0))
#define LCD_D0_InputEnable()       (TRISBSET = (1<<0))
#define LCD_D0_Get()               ((PORTB >> 0) & 0x1)
#define LCD_D0_PIN                  GPIO_PIN_RB0

/*** Macros for LCD_D1 pin ***/
#define LCD_D1_Set()               (LATBSET = (1<<1))
#define LCD_D1_Clear()             (LATBCLR = (1<<1))
#define LCD_D1_Toggle()            (LATBINV= (1<<1))
#define LCD_D1_OutputEnable()      (TRISBCLR = (1<<1))
#define LCD_D1_InputEnable()       (TRISBSET = (1<<1))
#define LCD_D1_Get()               ((PORTB >> 1) & 0x1)
#define LCD_D1_PIN                  GPIO_PIN_RB1

/*** Macros for LCD_D2 pin ***/
#define LCD_D2_Set()               (LATBSET = (1<<2))
#define LCD_D2_Clear()             (LATBCLR = (1<<2))
#define LCD_D2_Toggle()            (LATBINV= (1<<2))
#define LCD_D2_OutputEnable()      (TRISBCLR = (1<<2))
#define LCD_D2_InputEnable()       (TRISBSET = (1<<2))
#define LCD_D2_Get()               ((PORTB >> 2) & 0x1)
#define LCD_D2_PIN                  GPIO_PIN_RB2

/*** Macros for LCD_D3 pin ***/
#define LCD_D3_Set()               (LATBSET = (1<<3))
#define LCD_D3_Clear()             (LATBCLR = (1<<3))
#define LCD_D3_Toggle()            (LATBINV= (1<<3))
#define LCD_D3_OutputEnable()      (TRISBCLR = (1<<3))
#define LCD_D3_InputEnable()       (TRISBSET = (1<<3))
#define LCD_D3_Get()               ((PORTB >> 3) & 0x1)
#define LCD_D3_PIN                  GPIO_PIN_RB3

/*** Macros for LCD_RS pin ***/
#define LCD_RS_Set()               (LATASET = (1<<2))
#define LCD_RS_Clear()             (LATACLR = (1<<2))
#define LCD_RS_Toggle()            (LATAINV= (1<<2))
#define LCD_RS_OutputEnable()      (TRISACLR = (1<<2))
#define LCD_RS_InputEnable()       (TRISASET = (1<<2))
#define LCD_RS_Get()               ((PORTA >> 2) & 0x1)
#define LCD_RS_PIN                  GPIO_PIN_RA2

/*** Macros for LCD_CS pin ***/
#define LCD_CS_Set()               (LATASET = (1<<3))
#define LCD_CS_Clear()             (LATACLR = (1<<3))
#define LCD_CS_Toggle()            (LATAINV= (1<<3))
#define LCD_CS_OutputEnable()      (TRISACLR = (1<<3))
#define LCD_CS_InputEnable()       (TRISASET = (1<<3))
#define LCD_CS_Get()               ((PORTA >> 3) & 0x1)
#define LCD_CS_PIN                  GPIO_PIN_RA3

/*** Macros for LCD_D4 pin ***/
#define LCD_D4_Set()               (LATBSET = (1<<4))
#define LCD_D4_Clear()             (LATBCLR = (1<<4))
#define LCD_D4_Toggle()            (LATBINV= (1<<4))
#define LCD_D4_OutputEnable()      (TRISBCLR = (1<<4))
#define LCD_D4_InputEnable()       (TRISBSET = (1<<4))
#define LCD_D4_Get()               ((PORTB >> 4) & 0x1)
#define LCD_D4_PIN                  GPIO_PIN_RB4

/*** Macros for RESET pin ***/
#define RESET_Set()               (LATASET = (1<<4))
#define RESET_Clear()             (LATACLR = (1<<4))
#define RESET_Toggle()            (LATAINV= (1<<4))
#define RESET_OutputEnable()      (TRISACLR = (1<<4))
#define RESET_InputEnable()       (TRISASET = (1<<4))
#define RESET_Get()               ((PORTA >> 4) & 0x1)
#define RESET_PIN                  GPIO_PIN_RA4

/*** Macros for LCD_D5 pin ***/
#define LCD_D5_Set()               (LATBSET = (1<<5))
#define LCD_D5_Clear()             (LATBCLR = (1<<5))
#define LCD_D5_Toggle()            (LATBINV= (1<<5))
#define LCD_D5_OutputEnable()      (TRISBCLR = (1<<5))
#define LCD_D5_InputEnable()       (TRISBSET = (1<<5))
#define LCD_D5_Get()               ((PORTB >> 5) & 0x1)
#define LCD_D5_PIN                  GPIO_PIN_RB5

/*** Macros for LCD_D6 pin ***/
#define LCD_D6_Set()               (LATBSET = (1<<6))
#define LCD_D6_Clear()             (LATBCLR = (1<<6))
#define LCD_D6_Toggle()            (LATBINV= (1<<6))
#define LCD_D6_OutputEnable()      (TRISBCLR = (1<<6))
#define LCD_D6_InputEnable()       (TRISBSET = (1<<6))
#define LCD_D6_Get()               ((PORTB >> 6) & 0x1)
#define LCD_D6_PIN                  GPIO_PIN_RB6

/*** Macros for LCD_D7 pin ***/
#define LCD_D7_Set()               (LATBSET = (1<<7))
#define LCD_D7_Clear()             (LATBCLR = (1<<7))
#define LCD_D7_Toggle()            (LATBINV= (1<<7))
#define LCD_D7_OutputEnable()      (TRISBCLR = (1<<7))
#define LCD_D7_InputEnable()       (TRISBSET = (1<<7))
#define LCD_D7_Get()               ((PORTB >> 7) & 0x1)
#define LCD_D7_PIN                  GPIO_PIN_RB7

/*** Macros for SD_SCK pin ***/
#define SD_SCK_Get()               ((PORTB >> 8) & 0x1)
#define SD_SCK_PIN                  GPIO_PIN_RB8

/*** Macros for SD_SDO pin ***/
#define SD_SDO_Get()               ((PORTB >> 9) & 0x1)
#define SD_SDO_PIN                  GPIO_PIN_RB9

/*** Macros for SD_SDI pin ***/
#define SD_SDI_Get()               ((PORTC >> 9) & 0x1)
#define SD_SDI_PIN                  GPIO_PIN_RC9

/*** Macros for LED_STATUS pin ***/
#define LED_STATUS_Set()               (LATBSET = (1<<10))
#define LED_STATUS_Clear()             (LATBCLR = (1<<10))
#define LED_STATUS_Toggle()            (LATBINV= (1<<10))
#define LED_STATUS_OutputEnable()      (TRISBCLR = (1<<10))
#define LED_STATUS_InputEnable()       (TRISBSET = (1<<10))
#define LED_STATUS_Get()               ((PORTB >> 10) & 0x1)
#define LED_STATUS_PIN                  GPIO_PIN_RB10

/*** Macros for LED_MODO pin ***/
#define LED_MODO_Set()               (LATBSET = (1<<11))
#define LED_MODO_Clear()             (LATBCLR = (1<<11))
#define LED_MODO_Toggle()            (LATBINV= (1<<11))
#define LED_MODO_OutputEnable()      (TRISBCLR = (1<<11))
#define LED_MODO_InputEnable()       (TRISBSET = (1<<11))
#define LED_MODO_Get()               ((PORTB >> 11) & 0x1)
#define LED_MODO_PIN                  GPIO_PIN_RB11

/*** Macros for SD_CS pin ***/
#define SD_CS_Set()               (LATBSET = (1<<13))
#define SD_CS_Clear()             (LATBCLR = (1<<13))
#define SD_CS_Toggle()            (LATBINV= (1<<13))
#define SD_CS_OutputEnable()      (TRISBCLR = (1<<13))
#define SD_CS_InputEnable()       (TRISBSET = (1<<13))
#define SD_CS_Get()               ((PORTB >> 13) & 0x1)
#define SD_CS_PIN                  GPIO_PIN_RB13

/*** Macros for WIFI_TX pin ***/
#define WIFI_TX_Get()               ((PORTB >> 14) & 0x1)
#define WIFI_TX_PIN                  GPIO_PIN_RB14

/*** Macros for WIFI_RX pin ***/
#define WIFI_RX_Get()               ((PORTB >> 15) & 0x1)
#define WIFI_RX_PIN                  GPIO_PIN_RB15


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/
#define    GPIO_PORT_A   (0U)
#define    GPIO_PORT_B   (1U)
#define    GPIO_PORT_C   (2U)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/
#define    GPIO_PIN_RA0   (0U)
#define    GPIO_PIN_RA1   (1U)
#define    GPIO_PIN_RA2   (2U)
#define    GPIO_PIN_RA3   (3U)
#define    GPIO_PIN_RA4   (4U)
#define    GPIO_PIN_RB0   (16U)
#define    GPIO_PIN_RB1   (17U)
#define    GPIO_PIN_RB2   (18U)
#define    GPIO_PIN_RB3   (19U)
#define    GPIO_PIN_RB4   (20U)
#define    GPIO_PIN_RB5   (21U)
#define    GPIO_PIN_RB6   (22U)
#define    GPIO_PIN_RB7   (23U)
#define    GPIO_PIN_RB8   (24U)
#define    GPIO_PIN_RB9   (25U)
#define    GPIO_PIN_RB10   (26U)
#define    GPIO_PIN_RB11   (27U)
#define    GPIO_PIN_RB13   (29U)
#define    GPIO_PIN_RB14   (30U)
#define    GPIO_PIN_RB15   (31U)
#define    GPIO_PIN_RC9   (41U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE   (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xFU), (uint32_t)(value) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xFU)) & 0x1U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xFU)) & 0x1U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
