/*
 * TMR_Config.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) pre-build configurations, through which user can configure before using the TMR peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_CONFIG_H_
#define TMR_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* TMR Configurations' Definitions */

/*
 * 8-bit Timer/Counter0 Configurations' Definitions
 */

/* TMR0 Waveform Generation Modes */
#define TMR_U8_TMR_0_NORMAL_MODE							0
#define TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE					1
#define TMR_U8_TMR_0_CTC_MODE								2
#define TMR_U8_TMR_0_FAST_PWM_MODE							3

/* TMR0 Compare Match Output Modes */
#define TMR_U8_TMR_0_DISCONNECT_OC0_PIN						0
#define TMR_U8_TMR_0_TOG_OC0_PIN							1
#define TMR_U8_TMR_0_CLR_OC0_PIN							2
#define TMR_U8_TMR_0_SET_OC0_PIN							3

/* TMR0 Interrupt Sources */
#define TMR_U8_TMR_0_NO_INTERRUPT							0
#define TMR_U8_TMR_0_COMP_INTERRUPT							1
#define TMR_U8_TMR_0_OVF_INTERRUPT 							2

/* TMR0 Clock Sources */
#define TMR_U8_TMR_0_NO_CLOCK_SOURCE						0
#define TMR_U8_TMR_0_NO_PRESCALER							1
#define TMR_U8_TMR_0_8_PRESCALER							2
#define TMR_U8_TMR_0_64_PRESCALER							3
#define TMR_U8_TMR_0_256_PRESCALER							4
#define TMR_U8_TMR_0_1024_PRESCALER							5
#define TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		6
#define TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		7

/* End of Timer/Counter0 Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* TMR Configurations */

/*
 * 8-bit Timer/Counter0 Configurations
 */

/* TMR0 Waveform Generation Mode Select */
/* Options: TMR_U8_TMR_0_NORMAL_MODE
 *          TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE
 *          TMR_U8_TMR_0_CTC_MODE
 *          TMR_U8_TMR_0_FAST_PWM_MODE
 */
#define TMR_U8_TMR_0_MODE_SELECT			TMR_U8_TMR_0_NORMAL_MODE

/* TMR0 Compare Match Output Mode Select */
/* Options: TMR_U8_TMR_0_DISCONNECT_OC0_PIN                     // Any Mode
 *          TMR_U8_TMR_0_TOG_OC0_PIN                            // Non-PWM Modes only
 *          TMR_U8_TMR_0_CLR_OC0_PIN                            // Any Mode ( PWM -> Non-Inverting Mode )
 *          TMR_U8_TMR_0_SET_OC0_PIN                            // Any Mode ( PWM -> Inverting Mode )
 */
#define TMR_U8_TMR_0_COMP_OUTPUT_MODE		TMR_U8_TMR_0_DISCONNECT_OC0_PIN

/* TMR0 Interrupt Select */
/* Options: TMR_U8_TMR_0_NO_INTERRUPT
 * 			TMR_U8_TMR_0_COMP_INTERRUPT
 * 			TMR_U8_TMR_0_OVF_INTERRUPT
 */
#define TMR_U8_TMR_0_INTERRUPT_SELECT		TMR_U8_TMR_0_NO_INTERRUPT

/* TMR0 Clock Select */
/* Options: TMR_U8_TMR_0_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter0 stopped )
 * 			TMR_U8_TMR_0_NO_PRESCALER							// CLK IO/1   ( No prescaling )
 * 			TMR_U8_TMR_0_8_PRESCALER							// CLK IO/8   ( From prescaler )
 * 			TMR_U8_TMR_0_64_PRESCALER							// CLK IO/64  ( From prescaler )
 * 			TMR_U8_TMR_0_256_PRESCALER							// CLK IO/256 ( From prescaler )
 * 			TMR_U8_TMR_0_1024_PRESCALER							// CLK IO/1024( From prescaler )
 * 			TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		// External clock source on T0 pin. Clock on falling edge.
 * 			TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		// External clock source on T0 pin. Clock on rising edge.
 */
#define TMR_U8_TMR_0_CLOCK_SELECT			TMR_U8_TMR_0_NO_PRESCALER

/* TMR0 Other Configurations */
#define TMR_U8_TMR_0_PRELOAD_VALUE			0
#define TMR_U8_TMR_0_COMPARE_VALUE			0
#define TMR_U16_TMR_0_NUM_OF_OVERFLOWS		1

/* End of Timer/Counter0 Configurations */

/*
 * TMR Other Configurations 
 */

/* Timers Flags */
#define TMR_U8_FLAG_DOWN					0
#define TMR_U8_FLAG_UP						1

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* TMR_CONFIG_H_ */