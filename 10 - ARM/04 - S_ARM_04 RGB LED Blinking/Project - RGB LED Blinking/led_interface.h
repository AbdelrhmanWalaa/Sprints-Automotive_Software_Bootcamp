/*
 * led_interface.h
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
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "gpio_interface.h"

/*******************************************************************************************************************************************************************/
/* LED Macros */

/* LED IDs Counted from 0 to 7 */
#define LED_U8_0				0
#define LED_U8_1				1
#define LED_U8_2				2
#define LED_U8_3				3
#define LED_U8_4				4
#define LED_U8_5				5
#define LED_U8_6				6
#define LED_U8_7				7

/* LED Operations Counted from 0 to 2 */
#define LED_U8_ON				0
#define LED_U8_OFF			1
#define LED_U8_TOGGLE		2

/*******************************************************************************************************************************************************************/
/* LED Error States */

typedef enum 
{
	LED_EN_NOK = 0, 
	LED_EN_OK
	
} LED_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* LED Functions' Prototypes */

/*
 Name: LED_initialization
 Input: u8 LedId
 Output: en Error or No Error
 Description: Function to initialize LED peripheral, by initializing GPIO peripheral.
 */
extern LED_enErrorState_t LED_initialization( u8 u8_a_ledId );

/*
 Name: LED_setLEDPin
 Input: u8 LedId and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
extern LED_enErrorState_t LED_setLEDPin( u8 u8_a_ledId, u8 u8_a_operation );

/*******************************************************************************************************************************************************************/

#endif /* LED_INTERFACE_H_ */
