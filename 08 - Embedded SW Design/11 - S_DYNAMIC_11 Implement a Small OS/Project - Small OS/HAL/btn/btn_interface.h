/*
 * btn_interface.h
 *
 *   Created on: May 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Button (BTN) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* BTN Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/gli/gli_interface.h"
#include "../../MCAL/exi/exi_interface.h"

/*******************************************************************************************************************************************************************/
/* BTN Macros */

/* BTN and DIO Connection Port ( NML Mode ) */
#define BTN_U8_DIO_PORTA				0
#define BTN_U8_DIO_PORTB				1
#define BTN_U8_DIO_PORTC				2
#define BTN_U8_DIO_PORTD				3

/* BTN and DIO Connection Pin ( NML Mode ) */
#define BTN_U8_DIO_PIN0					0
#define BTN_U8_DIO_PIN1					1
#define BTN_U8_DIO_PIN2					2
#define BTN_U8_DIO_PIN3					3
#define BTN_U8_DIO_PIN4					4
#define BTN_U8_DIO_PIN5					5
#define BTN_U8_DIO_PIN6					6
#define BTN_U8_DIO_PIN7					7

/* BTN and EXI Connection ( EXI Mode ) */
#define BTN_U8_EXI_0					0
#define BTN_U8_EXI_1					1
#define BTN_U8_EXI_2					2

/* BTN and EXI Sense Control ( EXI Mode ) */
#define BTN_U8_EXI_SENSE_FALLING_EDGE	0
#define BTN_U8_EXI_SENSE_RISING_EDGE	1

/*******************************************************************************************************************************************************************/
/* BTN Functions' Prototypes */

u8 BTN_initializationNMLMode( u8 u8_a_btnPortId, u8 u8_a_btnPinId );
u8 BTN_initializationEXIMode( u8 u8_a_EXIId, u8 u8_a_EXISenseControl, void ( *pf_a_EXIAction ) ( void ) );

u8 BTN_getBTNState          ( u8 u8_a_btnPortId, u8 u8_a_btnPinId, u8 *pu8_a_returnedBTNState );

/*******************************************************************************************************************************************************************/

#endif /* BTN_INTERFACE_H_ */