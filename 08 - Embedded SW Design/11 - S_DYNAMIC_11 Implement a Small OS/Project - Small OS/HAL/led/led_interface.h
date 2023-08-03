/*
 * led_interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Light Emitting Diode (LED) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* LED Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"

/*******************************************************************************************************************************************************************/
/* LED Macros */

/* The 8 LEDs counted from 0 to 7 */
#define LED_U8_0		0
#define LED_U8_1		1
#define LED_U8_2		2
#define LED_U8_3		3
#define LED_U8_4		4
#define LED_U8_5		5
#define LED_U8_6		6
#define LED_U8_7		7

/* LED 3 Operations counted from 0 to 2  */
#define LED_U8_ON		0
#define LED_U8_OFF		1
#define LED_U8_TOGGLE	2

/*******************************************************************************************************************************************************************/
/* LED Functions' Prototypes */

u8 LED_initialization( u8 u8_a_ledId );
u8 LED_setLEDPin     ( u8 u8_a_ledId, u8 u8_a_operation );

/*******************************************************************************************************************************************************************/

#endif /* LED_INTERFACE_H_ */