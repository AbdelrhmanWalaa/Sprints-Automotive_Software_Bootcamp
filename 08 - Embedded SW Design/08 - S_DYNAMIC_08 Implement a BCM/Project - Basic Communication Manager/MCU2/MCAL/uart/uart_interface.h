/*
 * uart_interface.h
 *
 *     Created on: May 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* UART Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"
#include "../../LIB/mcu_config/mcu_config.h"

/* MCAL */
#include "uart_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* UART Enumerations */

/* UART Interrupt Ids */
typedef enum
{
	UART_EN_RXC_INT = 0,
	UART_EN_UDRE_INT,
	UART_EN_TXC_INT,
	UART_EN_INVALID_INT_ID
	
} UART_enInterruptId_t;

/* UART Reception/Transmission Blocking Modes */
typedef enum
{	
	UART_EN_BLOCKING_MODE = 0,
	UART_EN_NON_BLOCKING_MODE,
	UART_EN_INVALID_BLOCK_MODE
	
} UART_enBlockMode_t;

/* UART Error States */
typedef enum
{
	UART_EN_NOK = 0,
	UART_EN_OK
	
} UART_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* UART Functions' prototypes */

/*
 Name: UART_initialization
 Input: void
 Output: void
 Description: Function to initialize UART peripheral using Pre-compile Configurations.
*/
extern void UART_initialization( void );

/*
 Name: UART_linkConfigInitialization
 Input: Pointer to stLinkConfig
 Output: en Error or No Error
 Description: Function to initialize UART peripheral using Linking Configurations.
*/
extern UART_enErrorState_t UART_linkConfigInitialization( const UART_stLinkConfig_t *pst_a_linkConfig );

/*
 Name: UART_receiveByte
 Input: en BlockMode and Pointer to u8 ReturnedReceiveByte
 Output: en Error or No Error
 Description: Function to Receive Byte using both Blocking and Non-blocking Modes, with Timeout mechanism.
*/
extern UART_enErrorState_t UART_receiveByte( UART_enBlockMode_t en_a_blockMode, u8 *pu8_a_returnedReceiveByte );

/*
 Name: UART_transmitByte
 Input: en BlockMode and u8 TransmitByte
 Output: en Error or No Error
 Description: Function to Transmit Byte using both Blocking and Non-blocking Modes, with Timeout mechanism.
*/
extern UART_enErrorState_t UART_transmitByte( UART_enBlockMode_t u8_a_blockMode, u8 u8_a_transmitByte );

/*
 Name: UART_enableInterrupt
 Input: en InterruptId
 Output: en Error or No Error
 Description: Function to enable UART different interrupts.
*/
extern UART_enErrorState_t UART_enableInterrupt( UART_enInterruptId_t en_a_interruptId );

/*
 Name: UART_disableInterrupt
 Input: en InterruptId
 Output: en Error or No Error
 Description: Function to disable UART different interrupts.
*/
extern UART_enErrorState_t UART_disableInterrupt( UART_enInterruptId_t en_a_interruptId );

/*
 Name: UART_RXCSetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( RXCInterruptAction ), and then pass this address to ISR function.
*/
extern UART_enErrorState_t UART_RXCSetCallback( void ( *vpf_a_RXCInterruptAction ) ( void ) );

/*
 Name: UART_UDRESetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( UDREInterruptAction ), and then pass this address to ISR function.
*/
extern UART_enErrorState_t UART_UDRESetCallback( void ( *vpf_a_UDREInterruptAction ) ( void ) );

/*
 Name: UART_TXCSetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TXCInterruptAction ), and then pass this address to ISR function.
*/
extern UART_enErrorState_t UART_TXCSetCallback( void ( *vpf_a_TXCInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* UART_INTERFACE_H_ */