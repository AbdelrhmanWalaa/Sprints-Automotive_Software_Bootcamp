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

/*******************************************************************************************************************************************************************/
/* BTN Functions' Prototypes */

void BTN_init( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber );
void BTN_read( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, u8 *pu8_a_returnedState );

/*******************************************************************************************************************************************************************/

#endif /* BTN_INTERFACE_H_ */