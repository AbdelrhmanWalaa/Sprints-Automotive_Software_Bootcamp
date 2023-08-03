/*
 * pwm_config.h
 *
 *     Created on: May 17, 2023
 *         Author: Hazem Ashraf - https://github.com/hazemashrafali
 *    Description: This file contains all Pulse Width Modulation (PWM) pre-build configurations, through which user can configure before using the PWM peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* PWM Configurations */

/* Max Duty Cycle Value */
#define PWM_U8_MAX_DUTY_CYCLE						100

/* TMR2 Clock Sources */
#define TMR_U16_TMR_2_NO_CLOCK_SOURCE				0
#define TMR_U16_TMR_2_NO_PRESCALER					1
#define TMR_U16_TMR_2_8_PRESCALER					8
#define TMR_U16_TMR_2_32_PRESCALER					32
#define TMR_U16_TMR_2_64_PRESCALER					64
#define TMR_U16_TMR_2_128_PRESCALER					128
#define TMR_U16_TMR_2_256_PRESCALER					256
#define TMR_U16_TMR_2_1024_PRESCALER				1024

/* PWM Flag States */
#define PWM_U8_FLAG_DOWN							0
#define PWM_U8_FLAG_UP								1

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* PWM_CONFIG_H_ */