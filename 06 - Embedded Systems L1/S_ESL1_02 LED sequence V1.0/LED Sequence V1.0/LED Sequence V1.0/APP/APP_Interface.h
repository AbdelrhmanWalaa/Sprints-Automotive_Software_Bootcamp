/*
 * APP_Interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../MCAL/DIO_Driver/DIO_Interface.h"

/* HAL */
#include "../HAL/LED_Driver/LED_Interface.h"
#include "../HAL/BTN_Driver/BTN_Interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* LEDs Sequence States */
#define APP_U8_PRESS_0_SEQ			0xF0
#define APP_U8_PRESS_1_SEQ			0xF1
#define APP_U8_PRESS_2_SEQ			0xF3
#define APP_U8_PRESS_3_SEQ			0xF7
#define APP_U8_PRESS_4_SEQ			0xFF
#define APP_U8_PRESS_5_SEQ			0xFE
#define APP_U8_PRESS_6_SEQ			0xFC
#define APP_U8_PRESS_7_SEQ			0xF8

/* BTN States */
#define APP_U8_BTN_PRESSED			0
#define APP_U8_BTN_NOT_PRESSED		1

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

vd APP_vdInitialization      ( void );
vd APP_vdStartProgram        ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */