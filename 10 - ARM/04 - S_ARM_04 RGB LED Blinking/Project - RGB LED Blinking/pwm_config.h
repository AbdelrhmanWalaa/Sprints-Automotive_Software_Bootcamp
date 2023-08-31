 /*
 * pwm_config.h
 *
 *     Created on: Jun 25, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Pulse Width Modulation (PWM) pre-build configurations, through which user can configure before using the PWM peripheral.
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

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* PWM Configurations */

/* PWM Port Id Select */
/* Options: GPIO_EN_PORTA
	          GPIO_EN_PORTB
	          GPIO_EN_PORTC
            GPIO_EN_PORTD
            GPIO_EN_PORTE
            GPIO_EN_PORTF
 */
#define PWM_U8_PORT_ID_SELECT         GPIO_EN_PORTF

/* PWM Port Bus Id Select */
/* Options: GPIO_EN_APB
            GPIO_EN_AHB
 */
#define PWM_U8_PORT_BUS_ID_SELECT     GPIO_EN_APB  

/* PWM Pin Id Select */
/* Options: GPIO_EN_PIN0
            GPIO_EN_PIN1
            GPIO_EN_PIN2
            GPIO_EN_PIN3
            GPIO_EN_PIN4
            GPIO_EN_PIN5
            GPIO_EN_PIN6
            GPIO_EN_PIN7
 */
#define PWM_U8_PIN_ID_SELECT          GPIO_EN_PIN3

/* PWM Timer Id Select */
/* Options: GPTM_EN_TIMER_0
	          GPTM_EN_TIMER_1
	          GPTM_EN_TIMER_2
	          GPTM_EN_TIMER_3
            GPTM_EN_TIMER_4
            GPTM_EN_TIMER_5
            GPTM_EN_WIDE_TIMER_0
	          GPTM_EN_WIDE_TIMER_1
	          GPTM_EN_WIDE_TIMER_2
	          GPTM_EN_WIDE_TIMER_3
	          GPTM_EN_WIDE_TIMER_4
	          GPTM_EN_WIDE_TIMER_5 
 */
#define PWM_U8_TIMER_ID_SELECT        GPTM_EN_TIMER_0

/* PWM Timer Use Select */
/* Options: GPTM_EN_INDIVIDUAL_A 
            GPTM_EN_INDIVIDUAL_B
            GPTM_EN_CONCATUNATED
 */
#define PWM_U8_TIMER_USE_SELECT       GPTM_EN_CONCATUNATED

/* PWM Periods Flags */
#define PWM_OFF_PERIOD_FLAG           0
#define PWM_ON_PERIOD_FLAG            1

/* PWM Maximum Duty Cycle */
#define PWM_U8_MAX_DUTY_CYCLE         100

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* PWM_CONFIG_H_ */
