/*
 * stmr_interface.h
 *
 *     Created on: Jun 15, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all System Timer (STMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef STMR_INTERFACE_H_
#define STMR_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* STMR Includes */

/* STD LIB */
#include "TM4C123.h"
#include "math.h"

/* LIB */
#include "std_types.h"
#include "bit_math.h"
#include "mcu_config.h"

/* MCAL */
#include "stmr_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* STMR Error States */

typedef enum
{
	STMR_EN_NOK = 0, 
	STMR_EN_OK
	
} STMR_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* STMR Functions' Prototypes */

/*
 Name: STMR_initialization
 Input: Pointer to st TimerLinkConfig
 Output: en Error or No Error
 Description: Function to initialize STMR Timer peripheral using Linking Configurations.
*/
extern STMR_enErrorState_t STMR_initialization( const STMR_stTimerLinkConfig_t *pst_a_timerLinkConfig );

/*
 Name: STMR_setTimerMS
 Input: u32 TimeMS
 Output: void
 Description: Function to set STMR peripheral to count MS.
*/
extern void STMR_setTimerMS( u32 u32_a_timeMS );

/*
 Name: STMR_enableTimer
 Input: void
 Output: void
 Description: Function to enable STMR.
*/
extern void STMR_enableTimer( void );

/*
 Name: STMR_disableTimer
 Input: void
 Output: void
 Description: Function to disable STMR.
*/
extern void STMR_disableTimer( void );

/*
 Name: STMR_enableInterrupt
 Input: void
 Output: void
 Description: Function to enable STMR Interrupt.
*/
extern void STMR_enableInterrupt( void );

/*
 Name: STMR_disableInterrupt
 Input: void
 Output: void
 Description: Function to disable STMR Interrupt.
*/
extern void STMR_disableInterrupt( void );

/*
 Name: STMR_setCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function, the address is 
              passed through a pointer to function ( TimerInterruptAction ), and then pass this address to IRQ function.
*/
extern STMR_enErrorState_t STMR_setCallback( void ( *vpf_a_timerInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* STMR_INTERFACE_H_ */
