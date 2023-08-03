/*
 * pwm_interface.h
 *
 *     Created on: May 17, 2023
 *         Author: Hazem Ashraf - https://github.com/hazemashrafali
 *    Description: This file contains all Pulse Width Modulation (PWM) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* PWM Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"
#include "../../LIB/mcu_config/mcu_config.h"

/*******************************************************************************************************************************************************************/
/* PWM Macros */

/* The 4 Ports counted from 0 to 3 */
#define DIO_U8_PORTA		0
#define DIO_U8_PORTB		1
#define DIO_U8_PORTC		2
#define DIO_U8_PORTD		3

/* The 8 Pins counted from 0 to 7 */
#define DIO_U8_PIN0			0
#define DIO_U8_PIN1			1
#define DIO_U8_PIN2			2
#define DIO_U8_PIN3			3
#define DIO_U8_PIN4			4
#define DIO_U8_PIN5			5
#define DIO_U8_PIN6			6
#define DIO_U8_PIN7			7

/*******************************************************************************************************************************************************************/
/* PWM Functions' prototypes */

u8 PWM_initialization( u8 u8_a_portId, u8 u8_a_pinId, f32 f32_a_pwmFrequency );
u8 PWM_generatePWM   ( u8 u8_a_dutyCycle );

/*******************************************************************************************************************************************************************/

#endif /* PWM_INTERFACE_H_ */