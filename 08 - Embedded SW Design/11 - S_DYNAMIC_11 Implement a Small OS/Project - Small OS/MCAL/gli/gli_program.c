/*
 * gli_program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) functions' implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *	    Copyright: MIT License
 *
 *	               Copyright (c) Abdelrhman Walaa
 *
 *	               Permission is hereby granted, free of charge, to any person obtaining a copy
 *	               of this software and associated documentation files (the "Software"), to deal
 *	               in the Software without restriction, including without limitation the rights
 *	               to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	               copies of the Software, and to permit persons to whom the Software is
 *	               furnished to do so, subject to the following conditions:
 *
 *	               The above copyright notice and this permission notice shall be included in all
 *	               copies or substantial portions of the Software.
 *
 *	               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	               IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	               FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	               AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	               LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	               SOFTWARE.
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