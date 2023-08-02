/*
 * gpio_linkConfig.h
 *
 *     Created on: Jun 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Input Output (GPIO) linking configurations, through which user can configure during using the GPIO peripheral.
 *  MCU Datasheet: Tiva™ TM4C123GH6PM - https://www.ti.com/lit/pdf/spms376
 *	    Copyright: MIT License
 *
 *	               Copyright (c) Abdelrhman Walaa
 *
 *	               Permission is hereby granted, free of charge, to any person obtaining a copy
 *	               of this software and associated documentation files (the "Software"), to deal
 *	               in the Software without restriction, including without limitation the rights
 *	               to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	               copies of the Software, and to permit persons to whom the Software is
 *	               furnished to do so, subject to the following conditions:
 *
 *	               The above copyright notice and this permission notice shall be included in all
 *	               copies or substantial portions of the Software.
 *
 *	               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	               IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	               FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	               AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	               LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	               SOFTWARE.
 */

#ifndef GPIO_LINKCONFIG_H_
#define GPIO_LINKCONFIG_H_

/*******************************************************************************************************************************************************************/
/* GPIO Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/*******************************************************************************************************************************************************************/
/* GPIO Linking Configurations Enumerations */

/* GPIO Port Ids */
typedef enum
{	
	GPIO_EN_PORTA = 0,
	GPIO_EN_PORTB,
	GPIO_EN_PORTC,
  GPIO_EN_PORTD,
  GPIO_EN_PORTE,
  GPIO_EN_PORTF,
  GPIO_EN_INVALID_PORT_ID

} GPIO_enPortId_t;

/* GPIO Port Bus Ids */
typedef enum
{	
	GPIO_EN_APB = 0,
	GPIO_EN_AHB,
  GPIO_EN_INVALID_BUS_ID

} GPIO_enPortBusId_t;

/* GPIO Port Modes */
typedef enum
{	
	GPIO_EN_RUN_MODE = 0,
	GPIO_EN_SLEEP_MODE,
  GPIO_EN_DEEP_SLEEP_MODE,
  GPIO_EN_INVALID_PORT_MODE

} GPIO_enPortMode_t;

/* GPIO Pin Ids */
typedef enum
{	
	GPIO_EN_PIN0 = 0,
	GPIO_EN_PIN1,
	GPIO_EN_PIN2,
  GPIO_EN_PIN3,
  GPIO_EN_PIN4,
  GPIO_EN_PIN5,
  GPIO_EN_PIN6,
  GPIO_EN_PIN7,
  GPIO_EN_INVALID_PIN_ID

} GPIO_enPinId_t;

/* GPIO Pin Modes */
typedef enum
{	
	GPIO_EN_DISABLE_PIN = 0,
	GPIO_EN_ENABLE_PIN,
	GPIO_EN_INVALID_PIN_MODE

} GPIO_enPinMode_t;

/* GPIO Pin Directions */
typedef enum
{	
	GPIO_EN_INPUT_DIR = 0,
	GPIO_EN_OUTPUT_DIR,
  GPIO_EN_INVALID_PIN_DIR

} GPIO_enPinDirection_t;

/* GPIO Pin Values */
typedef enum
{	
	GPIO_EN_PIN_LOW,
	GPIO_EN_PIN_HIGH,
  GPIO_EN_INVALID_PIN_VALUE

} GPIO_enPinValue_t;

/* GPIO Pin Pads */
typedef enum
{	
	GPIO_EN_DISABLE_PIN_PAD =0,
	GPIO_EN_ENABLE_PULL_UP,
	GPIO_EN_ENABLE_PULL_DOWN,
	GPIO_EN_ENABLE_OPEN_DRAIN,
	GPIO_EN_INVALID_PIN_PAD

} GPIO_enPinPad_t;

/* GPIO Pin Alternate Function Modes */
typedef enum
{	
	GPIO_EN_PIN_GPIO_MODE = 0,
	GPIO_EN_PIN_ALT_MODE,
  GPIO_EN_INVALID_PIN_ALT_MODE

} GPIO_enPinAlternateMode_t;

/* GPIO Pin Drives */
typedef enum
{	
	GPIO_EN_DISABLE_PIN_DRIVE = 0,
  GPIO_EN_2_MA_DRIVE,
  GPIO_EN_4_MA_DRIVE,
  GPIO_EN_8_MA_DRIVE,
  GPIO_EN_INVALID_PIN_DRIVE

} GPIO_enPinDrive_t;

/* GPIO Pin Interrupt Modes */
typedef enum
{
	GPIO_EN_DISABLE_INT = 0,
	GPIO_EN_ENABLE_INT,
	GPIO_EN_INVALID_PIN_INT_MODE

} GPIO_enPinInterruptMode_t;

/* GPIO Pin Interrupt Action */
typedef void ( *GPIO_vpfPinInterruptAction_t ) ( void );

/*******************************************************************************************************************************************************************/
/* GPIO Linking Configurations Structures */

/* GPIO Port Linking Configurations Structure */
typedef struct
{
  GPIO_enPortId_t     en_a_portId;
	GPIO_enPortBusId_t  en_a_portBusId;
  GPIO_enPortMode_t   en_a_portMode;

} GPIO_stPortLinkConfig_t;

/* GPIO Pin Linking Configurations Structure */
typedef struct
{
	GPIO_enPortId_t              en_a_portId;
	GPIO_enPortBusId_t					 en_a_portBusId;
  GPIO_enPinId_t               en_a_pinId;
	GPIO_enPinMode_t						 en_a_pinMode;
  GPIO_enPinDirection_t        en_a_pinDirection;
	GPIO_enPinValue_t			       en_a_pinValue;	
  GPIO_enPinAlternateMode_t    en_a_pinAlternateMode;
  GPIO_enPinDrive_t            en_a_pinDrive;
	GPIO_enPinPad_t							 en_a_pinPad;
  GPIO_enPinInterruptMode_t    en_a_pinInterruptMode;
  GPIO_vpfPinInterruptAction_t vpf_a_pinInterruptAcrion;

} GPIO_stPinLinkConfig_t;

/*******************************************************************************************************************************************************************/
/* GPIO External Variables */

extern GPIO_stPortLinkConfig_t ast_g_gpioPortsLinkConfig[1];
extern GPIO_stPinLinkConfig_t  ast_g_gpioPinsLinkConfig[4];

/*******************************************************************************************************************************************************************/

#endif /* GPIO_LINKCONFIG_H_ */
