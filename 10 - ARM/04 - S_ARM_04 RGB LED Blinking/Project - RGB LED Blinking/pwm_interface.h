/*
 * pwm_interface.h
 *
 *     Created on: Jun 25, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Pulse Width Modulation (PWM) functions' prototypes, link configurations, and definitions (Macros) to avoid magic numbers.
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

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* PWM Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "gpio_interface.h"
#include "gptm_interface.h"

/*******************************************************************************************************************************************************************/
/* PWM Macros */

/* PWM IDs Counted from 0 to 7 */
#define PWM_U8_0		    0
#define PWM_U8_1		    1
#define PWM_U8_2		    2
#define PWM_U8_3		    3
#define PWM_U8_4		    4
#define PWM_U8_5		    5
#define PWM_U8_6		    6
#define PWM_U8_7		    7

/*******************************************************************************************************************************************************************/
/* PWM Enumerations */

/* PWM Time Units */
typedef enum
{
	PWM_EN_TIME_US,
	PWM_EN_TIME_MS,
	PWM_EN_TIME_SEC,
	PWM_EN_INVALID_TIME_UNIT
	
} PWM_enTimeUnit_t;

/* PWM Error States */
typedef enum
{
	PWM_EN_NOK = 0, 
	PWM_EN_OK
	
} PWM_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* PWM Functions' Prototypes */

/*
 Name: PWM_initialization
 Input: u8 PWMId
 Output: en Error or No Error
 Description: Function to initialize PWM peripheral, by initializing GPIO and GPTM peripherals.
*/
extern PWM_enErrorState_t PWM_initialization( u8 u8_a_pwmId );

/*
 Name: PWM_enable
 Input: u8 DutyCycle
 Output: en Error or No Error
 Description: Function to enable PWM.
*/
extern PWM_enErrorState_t PWM_enable( u64 u64_a_totalPeriod, PWM_enTimeUnit_t en_a_timeUnit, u8 u8_a_dutyCycle );

/*
 Name: PWM_disable
 Input: void
 Output: void
 Description: Function to disable PWM.
*/
extern void PWM_disable( void );

/*******************************************************************************************************************************************************************/

#endif /* PWM_INTERFACE_H_ */
