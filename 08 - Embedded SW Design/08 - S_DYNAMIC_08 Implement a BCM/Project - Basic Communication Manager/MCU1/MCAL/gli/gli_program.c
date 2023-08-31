/*
 * gli_program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) functions' implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "gli_private.h"
#include "gli_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: GLI_enableGIE
 Input: void
 Output: void
 Description: Function to set I bit in SREG, to enable the Global Interrupt Enable (GIE).
*/
void GLI_enableGIE ( void )
{
	SET_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: GLI_disableGIE
 Input: void
 Output: void
 Description: Function to clear I bit in SREG, to disable the Global Interrupt Enable (GIE).
*/
void GLI_disableGIE( void )
{
	CLR_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/