/*
 * EXI_Interface.h
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all External Interrupt (EXI) functions' prototypes and definitions (Macros) to avoid magic numbers.
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
 
#ifndef EXI_INTERFACE_H_
#define EXI_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* EXI Includes */

 /* LIB */
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

/*******************************************************************************************************************************************************************/
/* EXI Macros */

/* EXI Counted from 0 to 2 Counted from 0 to 2 */
#define EXI_U8_INT0						0
#define EXI_U8_INT1 					1
#define EXI_U8_INT2 					2

/* EXI Sense Controls Counted from 0 to 3 */
#define EXI_U8_SENSE_LOW_LEVEL			0
#define EXI_U8_SENSE_LOGICAL_CHANGE		1
#define EXI_U8_SENSE_FALLING_EDGE		2
#define EXI_U8_SENSE_RISING_EDGE		3

/*******************************************************************************************************************************************************************/
/* EXI Error States */

typedef enum {
	EXI_EN_NOK = 0, EXI_EN_OK
} EXI_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* EXI Functions' Prototypes */

/*
 Name: EXI_enEnablePIE
 Input: u8 InterruptId and u8 SenseControl
 Output: en Error or No Error
 Description: Function to enable and configure Peripheral Interrupt Enable (PIE), by setting relevant bit for each interrupt in GICR register,
 	 	 	  then configuring Sense Control in MCUCR (case interrupt 0 or 1) or MCUCSR (case interrupt 2) registers.
*/
extern EXI_enErrorState_t EXI_enEnablePIE( u8 Cpy_u8InterruptId, u8 Cpy_u8SenseControl );

/*
 Name: EXI_enDisablePIE
 Input: u8 InterruptId
 Output: en Error or No Error
 Description: Function to disable Peripheral Interrupt Enable (PIE), by clearing relevant bit for each interrupt in GICR register.
*/
extern EXI_enErrorState_t EXI_enDisablePIE( u8 Cpy_u8InterruptId );

/*
 Name: EXI_enINTSetCallBack
 Input: u8 InterruptId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Interrupt ( InterruptId ),
 	 	 	  the address is passed through a pointer to function ( INTInterruptAction ), and then pass this address to ISR function.
*/
extern EXI_enErrorState_t EXI_enINTSetCallBack( u8 Cpy_u8InterruptId, void ( *Cpy_pfINTInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* EXTI_INTERFACE_H_ */