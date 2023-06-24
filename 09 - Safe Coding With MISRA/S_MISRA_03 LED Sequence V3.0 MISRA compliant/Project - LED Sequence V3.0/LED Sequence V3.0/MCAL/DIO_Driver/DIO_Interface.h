/*
 * DIO_Interface.h
 *
 *     Created on: Mar 31, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Digital Input Output (DIO) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *		Copyright: MIT License
 *
 *		           Copyright (c) Abdelrhman Walaa
 *
 *		           Permission is hereby granted, free of charge, to any person obtaining a copy
 *		           of this software and associated documentation files (the "Software"), to deal
 *		           in the Software without restriction, including without limitation the rights
 *		           to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *		           copies of the Software, and to permit persons to whom the Software is
 *		           furnished to do so, subject to the following conditions:
 *
 *		           The above copyright notice and this permission notice shall be included in all
 *		           copies or substantial portions of the Software.
 *
 *		           THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *		           SOFTWARE.
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DIO Includes */

/* LIB */
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

/*******************************************************************************************************************************************************************/
/* DIO Macros */

/* DIO Ports Counted from 0 to 3 */
#define DIO_U8_PORTA		0
#define DIO_U8_PORTB		1
#define DIO_U8_PORTC		2
#define DIO_U8_PORTD		3

/* DIO Ports' Directions as Input = 0 or Output = 255 */
#define DIO_U8_PORT_INPUT	0
#define DIO_U8_PORT_OUTPUT	255

/* DIO Ports' Values as Low = 0 or High = 255 */
#define DIO_U8_PORT_LOW		0
#define DIO_U8_PORT_HIGH	255

/* DIO Pins Counted from 0 to 7 */
#define DIO_U8_PIN0			0
#define DIO_U8_PIN1			1
#define DIO_U8_PIN2			2
#define DIO_U8_PIN3			3
#define DIO_U8_PIN4			4
#define DIO_U8_PIN5			5
#define DIO_U8_PIN6			6
#define DIO_U8_PIN7			7

/* DIO Pins' Directions as Input = 0 or Output = 1 */
#define DIO_U8_PIN_INPUT	0
#define DIO_U8_PIN_OUTPUT	1

/* DIO Pins' Values as Low = 0 or High = 1 */
#define DIO_U8_PIN_LOW		0
#define DIO_U8_PIN_HIGH		1

/*******************************************************************************************************************************************************************/
/* DIO Error States */

typedef enum {
	DIO_EN_NOK = 0, DIO_EN_OK
} DIO_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* DIO Functions' Prototypes */

/*
 Name: DIO_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize DIO peripheral.
*/
extern void DIO_vdInitialization( void );

/*
 Name: DIO_enSetPinDirection
 Input: u8 PortId, u8 PinId, and u8 PinDirection
 Output: en Error or No Error
 Description: Function to set Pin direction.
*/
extern DIO_enErrorState_t DIO_enSetPinDirection( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 Cpy_u8PinDirection );

/*
 Name: DIO_enSetPinValue
 Input: u8 PortId, u8 PinId, and u8 PinValue
 Output: en Error or No Error
 Description: Function to set Pin value.
*/
extern DIO_enErrorState_t DIO_enSetPinValue( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 Cpy_u8PinValue );

/*
 Name: DIO_enGetPinValue
 Input: u8 PortId, u8 PinId, and Pointer to u8 ReturnedPinValue
 Output: en Error or No Error
 Description: Function to get Pin value.
*/
extern DIO_enErrorState_t DIO_enGetPinValue( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 *Cpy_pu8ReturnedPinValue );

/*
 Name: DIO_enTogglePinValue
 Input: u8 PortId and u8 PinId
 Output: en Error or No Error
 Description: Function to toggle Pin value.
*/
extern DIO_enErrorState_t DIO_enTogglePinValue( u8 Cpy_u8PortId, u8 Cpy_u8PinId );

/*
 Name: DIO_enSetPortDirection
 Input: u8 PortId and u8 PortDirection
 Output: en Error or No Error
 Description: Function to set Port direction.
*/
extern DIO_enErrorState_t DIO_enSetPortDirection( u8 Cpy_u8PortId, u8 Cpy_u8PortDirection );

/*
 Name: DIO_enSetPortValue
 Input: u8 PortId and u8 PortValue
 Output: en Error or No Error
 Description: Function to set Port value.
*/
extern DIO_enErrorState_t DIO_enSetPortValue( u8 Cpy_u8PortId, u8 Cpy_u8PortValue );

/*
 Name: DIO_enGetPortValue
 Input: u8 PortId and Pointer to u8 ReturnedPortValue
 Output: en Error or No Error
 Description: Function to get Port value.
*/
extern DIO_enErrorState_t DIO_enGetPortValue( u8 Cpy_u8PortId, u8 *Cpy_pu8ReturnedPortValue );

/*
 Name: DIO_enTogglePortValue
 Input: u8 PortId
 Output: en Error or No Error
 Description: Function to toggle Port value.
*/
extern DIO_enErrorState_t DIO_enTogglePortValue( u8 Cpy_u8PortId );

/*******************************************************************************************************************************************************************/

#endif /* DIO_INTERFACE_H_ */