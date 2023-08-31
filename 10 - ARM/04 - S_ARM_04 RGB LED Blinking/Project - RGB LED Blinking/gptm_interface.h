/*
 * gptm_interface.h
 *
 *     Created on: Jun 20, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Timers (GPTM) functions' prototypes, link configurations, and definitions (Macros) to avoid magic numbers.
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

#ifndef GPTM_INTERFACE_H_
#define GPTM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* GPTM Includes */

/* STD LIB */
#include "TM4C123.h"
#include "math.h"

/* LIB */
#include "std_types.h"
#include "bit_math.h"
#include "mcu_config.h"

/* MCAL */
#include "gptm_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* GPTM Enumerations */

/* GPTM Error States */
typedef enum
{
	GPTM_EN_NOK = 0, 
	GPTM_EN_OK
	
} GPTM_enErrorState_t;

/* GPTM Time Units */
typedef enum
{
	GPTM_EN_TIME_US,
	GPTM_EN_TIME_MS,
	GPTM_EN_TIME_SEC,
	GPTM_EN_INVALID_TIME_UNIT
	
} GPTM_enTimeUnit_t;

/*******************************************************************************************************************************************************************/
/* GPTM Functions' Prototypes */

/*
 Name: GPTM_initialization
 Input: Pointer to Array of st TimerLinkConfig and u8 NumberOfTimers
 Output: en Error or No Error
 Description: Function to initialize GPTM peripheral using Linking Configurations.
*/
extern GPTM_enErrorState_t GPTM_initialization( const GPTM_stTimerLinkConfig_t *past_a_timersLinkConfig, u8 u8_a_numberOfTimers );

/*
 Name: GPTM_setTimer
 Input: en TimerId, en TimerUse, u64 Time, and en TimeUnit
 Output: en Error or No Error
 Description: Function to set GPTM peripheral to count in microseconds( us ), milliseconds ( ms ), and seconds ( sec ).
*/
extern GPTM_enErrorState_t GPTM_setTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, u64 u64_a_time, GPTM_enTimeUnit_t en_a_timeUnit );

/*
 Name: GPTM_enableTimer
 Input: en TimerId and en TimerUse
 Output: en Error or No Error
 Description: Function to enable GPTM.
*/
extern GPTM_enErrorState_t GPTM_enableTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse );

/*
 Name: GPTM_disableTimer
 Input: en TimerId and en TimerUse
 Output: en Error or No Error
 Description: Function to disable GPTM.
*/
extern GPTM_enErrorState_t GPTM_disableTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse );

/*
 Name: GPTM_enableInterrupt
 Input: en TimerInterruptNumber
 Output: en Error or No Error
 Description: Function to enable GPTM Interrupt.
*/
extern GPTM_enErrorState_t GPTM_enableInterrupt( GPTM_enTimerInterruptNumber_t en_a_timerInterruptNumber );

/*
 Name: GPTM_disableInterrupt
 Input: en TimerInterruptNumber
 Output: en Error or No Error
 Description: Function to disable GPTM Interrupt.
*/
extern GPTM_enErrorState_t GPTM_disableInterrupt( GPTM_enTimerInterruptNumber_t en_a_timerInterruptNumber );

/*
 Name: GPTM_getTimeoutStatusFlag
 Input: en TimerId, en TimerUse, and Pointer to u8 TimeoutStatusFlag
 Output: en Error or No Error
 Description: Function to get GPTM clear Timeout Status Flag.
*/
extern GPTM_enErrorState_t GPTM_getTimeoutStatusFlag( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, u8 *pu8_a_timeoutStatusFlag );

/*
 Name: GPTM_clearTimeoutStatusFlag
 Input: en TimerId and en TimerUse,
 Output: en Error or No Error
 Description: Function to clear GPTM clear Timeout Status Flag.
*/
extern GPTM_enErrorState_t GPTM_clearTimeoutStatusFlag( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse );

/*
 Name: GPTM_setCallback
 Input: en TimerId, en TimerUse, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function of the passed Timer ( TimerId ),
							the address is passed through a pointer to function ( TimerInterruptAction ), and then pass this address to IRQ function.
*/
extern GPTM_enErrorState_t GPTM_setCallback( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, void ( *vpf_a_timerInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* GPTM_INTERFACE_H_ */
