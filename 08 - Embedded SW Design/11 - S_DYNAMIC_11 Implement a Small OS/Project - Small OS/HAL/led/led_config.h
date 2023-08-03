/*
 * led_config.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Light Emitting Diode (LED) pre-build configurations, through which user can configure before using the LCD peripheral.
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* LED Configurations */

/* LED Port */
/* Options: A
			B
			C
			D
 */
#define LED_U8_PORT			B

/* LED Pin(s) */
/* Options: P0
			P1
			P2
			P3
			P4
			P5
			P6
			P7
 */
#define LED_U8_0_PIN		P0
#define LED_U8_1_PIN		P1
#define LED_U8_2_PIN		P2
#define LED_U8_3_PIN		P3
#define LED_U8_4_PIN		P4
#define LED_U8_5_PIN		P5
#define LED_U8_6_PIN		P6
#define LED_U8_7_PIN		P7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* LED_CONFIG_H_ */