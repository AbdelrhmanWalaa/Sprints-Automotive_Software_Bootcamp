/*
 * LED_Interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Light Emitting Diode (LED) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *	  Copyright: MIT License
 *
 *	             Copyright (c) Abdelrhman Walaa
 *
 *	             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	             of this software and associated documentation files (the "Software"), to deal
 *	             in the Software without restriction, including without limitation the rights
 *	             to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	             copies of the Software, and to permit persons to whom the Software is
 *	             furnished to do so, subject to the following conditions:
 *
 *	             The above copyright notice and this permission notice shall be included in all
 *	             copies or substantial portions of the Software.
 *
 *	             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	             FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	             SOFTWARE.
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* LED Includes */

/* LIB */
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"

/*******************************************************************************************************************************************************************/
/* LED Macros */

/* LED and DIO Port Connection */
#define LED_U8_PORT_A		DIO_U8_PORTA
#define LED_U8_PORT_B		DIO_U8_PORTB
#define LED_U8_PORT_C		DIO_U8_PORTC
#define LED_U8_PORT_D		DIO_U8_PORTD

/* LED and DIO Pin Connection */
#define LED_U8_PIN_0		DIO_U8_PIN0
#define LED_U8_PIN_1		DIO_U8_PIN1
#define LED_U8_PIN_2		DIO_U8_PIN2
#define LED_U8_PIN_3		DIO_U8_PIN3
#define LED_U8_PIN_4		DIO_U8_PIN4
#define LED_U8_PIN_5		DIO_U8_PIN5
#define LED_U8_PIN_6		DIO_U8_PIN6
#define LED_U8_PIN_7		DIO_U8_PIN7

/* LED Operations Counted from 0 to 2  */
#define LED_U8_ON			0
#define LED_U8_OFF			1
#define LED_U8_TOGGLE		2

/*******************************************************************************************************************************************************************/
/* LED Error States */

typedef enum {
	LED_EN_NOK = 0, LED_EN_OK
} LED_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* LED Functions' Prototypes */

/*
 Name: LED_enInitialization
 Input: u8 LedId
 Output: en Error or No Error
 Description: Function to initialize LED peripheral, by initializing DIO peripheral.
 */
extern LED_enErrorState_t LED_enInitialization( u8 Cpy_u8LEDPortId, u8 Cpy_u8LEDPinId );

/*
 Name: LED_enSetLEDPin
 Input: u8 LEDPortId, u8 LedId, and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
extern LED_enErrorState_t LED_enSetLEDPin( u8 Cpy_u8LEDPortId, u8 Cpy_u8LEDPinId, u8 Cpy_u8Operation );

/*
 Name: LED_enSetLEDsPort
 Input: u8 LEDsPortId, u8 LEDsPortValue, and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LEDs on or off.
*/
extern LED_enErrorState_t LED_enSetLEDsPort( u8 Cpy_u8LEDsPortId, u8 Cpy_u8LEDsPortValue, u8 Cpy_u8Operation );

/*******************************************************************************************************************************************************************/

#endif /* LED_INTERFACE_H_ */