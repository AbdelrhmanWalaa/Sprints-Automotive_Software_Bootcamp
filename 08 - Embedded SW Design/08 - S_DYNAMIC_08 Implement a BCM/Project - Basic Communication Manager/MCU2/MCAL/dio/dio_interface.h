/*
 * dio_interface.h
 *
 *     Created on: May 16, 2023
 *         Author: Mohamed Abdelsalam - https://github.com/m3adel
 *    Description: This file contains all Digital Input Output (DIO) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DIO Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"

/*******************************************************************************************************************************************************************/
/* DIO Macros */

/* Port Numbers */
typedef enum {
	A, B, C, D
} EN_DIO_PortNumber;

/* Pin Numbers */
typedef enum {
	P0,	P1,	P2,	P3,	P4,	P5,	P6,	P7
} EN_DIO_PinNumber;

/* Pin Directions */
typedef enum {
	IN,	OUT
} EN_DIO_PinDirection;

/* Pin Values */
typedef enum {
	LOW, HIGH, INPUT_FLOATING, INPUT_PULLUP_RESISTOR
} EN_DIO_PinValue;

/*******************************************************************************************************************************************************************/
/* DIO Functions' Prototypes */

void DIO_init (EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, EN_DIO_PinDirection en_a_pinDirection);
void DIO_write (EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, EN_DIO_PinValue en_a_pinValue);
void DIO_read (EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, u8 *pu8_a_returnedData);
void DIO_toggle (EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber);
void DIO_setPortDirection (EN_DIO_PortNumber en_a_portNumber, u8 u8_a_portDirection);
void DIO_setPortValue (EN_DIO_PortNumber en_a_portNumber, u8 u8_a_portValue);
void DIO_getPortValue (EN_DIO_PortNumber en_a_portNumber, u8 *pu8_a_returnedPortValue);
void DIO_setHigherNibble (EN_DIO_PortNumber en_a_portNumber, u8 u8_a_data);
void DIO_setLowerNibble (EN_DIO_PortNumber en_a_portNumber, u8 u8_a_data);

/*******************************************************************************************************************************************************************/

#endif /* DIO_INTERFACE_H_ */

