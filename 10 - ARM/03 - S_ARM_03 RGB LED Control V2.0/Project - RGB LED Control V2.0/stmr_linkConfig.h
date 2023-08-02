/*
 * stmr_linkConfig.h
 *
 *     Created on: Jun 15, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all System Timer (STMR) linking configurations, through which user can configure during using the STMR peripheral.
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

#ifndef STMR_LINKCONFIG_H_
#define STMR_LINKCONFIG_H_

/*******************************************************************************************************************************************************************/
/* STMR Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/*******************************************************************************************************************************************************************/
/* STMR Linking Configurations Enumerations */

/* STMR Timer Clock Sources */
typedef enum
{	
	STMR_EN_PIOSC_DIV_BY_4 = 0,
	STMR_EN_SYSTEM_CLK,
  STMR_EN_INVALID_CLK_SRC

} STMR_enTimerClockSource_t;

/* STMR Timer Modes */
typedef enum
{
	STMR_EN_DISABLE_TIMER = 0,
	STMR_EN_ENABLE_TIMER,
	STMR_EN_INVALID_TIMER_MODE

} STMR_enTimerMode_t;

/* STMR Timer Interrupt Modes */
typedef enum
{
	STMR_EN_DISABLED_TIMER_INT = 0,
	STMR_EN_ENABLED_TIMER_INT,
	STMR_EN_INVALID_TIMER_INT_MODE

} STMR_enTimerInterruptMode_t;

/* STMR Timer Interrupt Action */
typedef void ( *STMR_vpfTimerInterruptAction_t ) ( void );

/*******************************************************************************************************************************************************************/
/* STMR Linking Configurations Structures */

/* STMR Linking Configurations Structure */
typedef struct
{
	STMR_enTimerClockSource_t      en_a_timerClockSource;
  STMR_enTimerMode_t             en_a_timerMode;
	STMR_enTimerInterruptMode_t    en_a_timerInterruptMode;
	STMR_vpfTimerInterruptAction_t vpf_a_timerInterruptAction;
	
} STMR_stTimerLinkConfig_t;

/*******************************************************************************************************************************************************************/
/* STMR External Variables */

extern STMR_stTimerLinkConfig_t  st_g_stmrTimerLinkConfig;

/*******************************************************************************************************************************************************************/

#endif /* STMR_LINKCONFIG_H_ */
