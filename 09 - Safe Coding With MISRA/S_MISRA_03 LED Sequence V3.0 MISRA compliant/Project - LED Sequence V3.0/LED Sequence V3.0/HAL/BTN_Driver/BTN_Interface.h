/*
 * BTN_Interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* BTN Includes */

/* LIB */
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_Driver/DIO_Interface.h"
#include "../../MCAL/GLI_Driver/GLI_Interface.h"
#include "../../MCAL/EXI_Driver/EXI_Interface.h"

/*******************************************************************************************************************************************************************/
/* BTN Macros */

/* BTN and DIO Port Connection ( NML Mode ) */
#define BTN_U8_PORT_A		  DIO_U8_PORTA
#define BTN_U8_PORT_B		  DIO_U8_PORTB
#define BTN_U8_PORT_C		  DIO_U8_PORTC
#define BTN_U8_PORT_D		  DIO_U8_PORTD

/* BTN and DIO Pin Connection ( NML Mode ) */
#define BTN_U8_PIN_0		  DIO_U8_PIN0
#define BTN_U8_PIN_1		  DIO_U8_PIN1
#define BTN_U8_PIN_2		  DIO_U8_PIN2
#define BTN_U8_PIN_3		  DIO_U8_PIN3
#define BTN_U8_PIN_4		  DIO_U8_PIN4
#define BTN_U8_PIN_5		  DIO_U8_PIN5
#define BTN_U8_PIN_6		  DIO_U8_PIN6
#define BTN_U8_PIN_7		  DIO_U8_PIN7

/* BTN and Interrupt Id ( EXI Mode ) Counted from 0 to 2 */
#define BTN_U8_INT_0					0
#define BTN_U8_INT_1					1
#define BTN_U8_INT_2					2

/* BTN and Interrupt Sense Control ( EXI Mode ) Counted from 0 to 1 */
#define BTN_U8_SENSE_FALLING_EDGE		0
#define BTN_U8_SENSE_RISING_EDGE		1

/*******************************************************************************************************************************************************************/
/* BTN Error States */

typedef enum {
	BTN_EN_NOK = 0, BTN_EN_OK
} BTN_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* BTN Functions' Prototypes */

/*
 Name: BTN_enInitializationNMLMode
 Input: u8 BTNPortId and u8 BTNPinId
 Output: en Error or No Error
 Description: Function to initialize BTN pin in NML Mode.
*/
extern BTN_enErrorState_t BTN_enInitializationNMLMode( u8 Cpy_u8BTNPortId, u8 Cpy_u8BTNPinId );

/*
 Name: BTN_enInitializationINTMode
 Input: u8 InterruptId, u8 InterruptSenseControl, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to initialize BTN pin in INT Mode.
*/
extern BTN_enErrorState_t BTN_enInitializationINTMode( u8 Cpy_u8InterruptId, u8 Cpy_u8InterruptSenseControl, void ( *Cpy_pfInterruptAction ) ( void ) );

/*
 Name: BTN_enGetBTNState
 Input: u8 BTNPortId, u8 BTNPinId and Pointer to u8 ReturnedBTNState
 Output: en Error or No Error
 Description: Function to get BTN state.
*/
extern BTN_enErrorState_t BTN_enGetBTNState( u8 Cpy_u8BTNPortId, u8 Cpy_u8BTNPinId,  u8 *Cpy_pu8ReturnedBTNState );

/*******************************************************************************************************************************************************************/

#endif /* BTN_INTERFACE_H_ */