/*
 * btn_program.c
 *
 *   Created on: May 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Button (BTN) functions' implementation.
 */

/* HAL */
#include "btn_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_init
 Input: en PortNumber and en PinNumber
 Output: void
 Description: Function to initialize BTN pin as INPUT.
*/
void BTN_init( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber )
{
	DIO_init( en_a_portNumber, en_a_pinNumber, IN );	
	DIO_write( en_a_portNumber, en_a_pinNumber, HIGH );
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_read
 Input: en PortNumber, en PinNumber, and Pointer to u8 ReturnedBTNState
 Output: void
 Description: Function to get BTN state.
*/
void BTN_read( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, u8 *pu8_a_returnedBTNState )
{
	DIO_read( en_a_portNumber, en_a_pinNumber, pu8_a_returnedBTNState );
}

/*******************************************************************************************************************************************************************/