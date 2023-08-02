/*
 * delay_interface.h
 *
 *     Created on: Jun 15, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Delay (DELAY) functions' prototypes, link configurations, and definitions (Macros) to avoid magic numbers.
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

#ifndef DELAY_INTERFACE_H_
#define DELAY_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DELAY Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "stmr_interface.h"

/*******************************************************************************************************************************************************************/
/* DELAY Error States */

typedef enum
{
	DELAY_EN_NOK = 0, 
	DELAY_EN_OK
	
} DELAY_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* DELAY Functions' Prototypes */

/*
 Name: DELAY_initialization
 Input: void
 Output: void
 Description: Function to initialize DELAY peripheral, by initializing STMR peripheral.
 */
extern void DELAY_initialization( void );

/*
 Name: DELAY_setDelayMS
 Input: u32 DelayMS
 Output: void
 Description: Function to set DELAY peripheral to count MS, using STMR peripheral.
*/
extern void DELAY_setDelayMS( u32 u32_a_delayMS );

/*
 Name: DELAY_setCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function, the address is 
              passed through a pointer to function ( DelayInterruptAction ), and then pass this address to IRQ function.
*/
extern DELAY_enErrorState_t DELAY_setCallback( void ( *vpf_a_delayInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* DELAY_INTERFACE_H_ */
