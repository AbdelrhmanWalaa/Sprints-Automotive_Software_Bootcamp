/*
 * gptm_linkConfig.h
 *
 *     Created on: Jun 20, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Timers (GPTM) linking configurations, through which user can configure during using the GPTM peripheral.
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

#ifndef GPTM_LINKCONFIG_H_
#define GPTM_LINKCONFIG_H_

/*******************************************************************************************************************************************************************/
/* GPTM Includes */

/* STD LIB */
#include "TM4C123GH6PM.h"

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/*******************************************************************************************************************************************************************/
/* GPTM Linking Configurations Enumerations */

/* GPTM Timer Ids */
typedef enum
{
	GPTM_EN_TIMER_0 = 0,
	GPTM_EN_TIMER_1,
	GPTM_EN_TIMER_2,
	GPTM_EN_TIMER_3,
  GPTM_EN_TIMER_4,
  GPTM_EN_TIMER_5,
  GPTM_EN_WIDE_TIMER_0,
	GPTM_EN_WIDE_TIMER_1,
	GPTM_EN_WIDE_TIMER_2,
	GPTM_EN_WIDE_TIMER_3,
	GPTM_EN_WIDE_TIMER_4,
	GPTM_EN_WIDE_TIMER_5,
  GPTM_EN_INVALID_TIMER_ID

} GPTM_enTimerId_t;

/* GPTM Timer Modes */
typedef enum
{
	GPTM_EN_ONE_SHOT_MODE = 0,
	GPTM_EN_PERIODIC_MODE,
	GPTM_EN_RTC_MODE,
	GPTM_EN_EDGE_COUNT_MODE,
	GPTM_EN_EDGE_TIME_MODE,
	GPTM_EN_PWM_MODE,
	GPTM_EN_INVALID_TIMER_MODE
	
} GPTM_enTimerMode_t;

/* GPTM Timer Uses */
typedef enum
{
	GPTM_EN_INDIVIDUAL_A = 0,
	GPTM_EN_INDIVIDUAL_B,
	GPTM_EN_CONCATUNATED,
	GPTM_EN_INVALID_TIMER_USE
	
} GPTM_enTimerUse_t;

/* GPTM Timer Interrupt Modes */
typedef enum
{
	GPTM_EN_DISABLED_INT = 0,
	GPTM_EN_ENABLED_INT,
	GPTM_EN_INVALID_TIMER_INT_MODE

} GPTM_enTimerInterruptMode_t;

/* GPTM Timer Interrupt Numbers */
typedef enum
{
	GPTM_EN_TIMER_INT_0_A = TIMER0A_IRQn,
  GPTM_EN_TIMER_INT_0_B = TIMER0B_IRQn,
	GPTM_EN_TIMER_INT_1_A = TIMER1A_IRQn,
  GPTM_EN_TIMER_INT_1_B = TIMER1B_IRQn,
	GPTM_EN_TIMER_INT_2_A = TIMER2A_IRQn,
  GPTM_EN_TIMER_INT_2_B = TIMER2B_IRQn,
	GPTM_EN_TIMER_INT_3_A = TIMER3A_IRQn,
  GPTM_EN_TIMER_INT_3_B = TIMER3B_IRQn,
	GPTM_EN_TIMER_INT_4_A = TIMER4A_IRQn,
  GPTM_EN_TIMER_INT_4_B = TIMER4B_IRQn,
	GPTM_EN_TIMER_INT_5_A = TIMER5A_IRQn,
  GPTM_EN_TIMER_INT_5_B = TIMER5B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_0_A = WTIMER0A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_0_B = WTIMER0B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_1_A = WTIMER1A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_1_B = WTIMER1B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_2_A = WTIMER2A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_2_B = WTIMER2B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_3_A = WTIMER3A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_3_B = WTIMER3B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_4_A = WTIMER4A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_4_B = WTIMER4B_IRQn,
	GPTM_EN_WIDE_TIMER_INT_5_A = WTIMER5A_IRQn,
  GPTM_EN_WIDE_TIMER_INT_5_B = WTIMER5B_IRQn,
	GPTM_EN_INVALID_TIMER_INT_NUMBER

} GPTM_enTimerInterruptNumber_t;

/* GPTM Interrupt Action */
typedef void ( *GPTM_vpfTimerInterruptAction_t ) ( void );

/*******************************************************************************************************************************************************************/
/* GPTM Linking Configurations Structure */

typedef struct
{
  GPTM_enTimerId_t               en_a_timerId;
	GPTM_enTimerMode_t             en_a_timerMode;
	GPTM_enTimerUse_t              en_a_timerUse;
	u64                            u64_a_timerStartValue;
  GPTM_enTimerInterruptMode_t    en_a_timerInterruptMode;
	GPTM_enTimerInterruptNumber_t  en_a_timerInterruptNumber;
	
} GPTM_stTimerLinkConfig_t;

/*******************************************************************************************************************************************************************/
/* GPTM External Variables */

extern GPTM_stTimerLinkConfig_t ast_gs_timersLinkConfig[1];

/*******************************************************************************************************************************************************************/

#endif /* GPTM_LINKCONFIG_H_ */
