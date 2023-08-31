/*
 * bcm_interface.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Basic Communication Manager (BCM) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *	  Copyright: MIT License
 *
 *	             Copyright (c) Abdelrhman Walaa
 *
 *	             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	             of this software and associated documentation files (the "Software"), to deal
 *	             in the Software without restriction, including without limitation the rights
 *	             to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	             copies of the Software, and to permit persons to whom the Software is
 *	             furnished to do so, subject to the following conditions:
 *
 *	             The above copyright notice and this permission notice shall be included in all
 *	             copies or substantial portions of the Software.
 *
 *	             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	             FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	             SOFTWARE.
 */

#ifndef BCM_INTERFACE_H_
#define BCM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* BCM Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"
#include "../../LIB/data_structures/queue/queue_interface.h"

/* MCAL */
#include "../../MCAL/uart/uart_interface.h"

/*******************************************************************************************************************************************************************/
/* BCM Macros */

#define BCM_U8_END_OF_STRING	'&'

/* BCM Protocols Ids */
typedef enum
{
	BCM_EN_PROTOCOL_0 = 0,	// UART Protocol
	BCM_EN_PROTOCOL_1,		// SPI Protocol
	BCM_EN_PROTOCOL_2,		// TWI Protocol
	BCM_EN_INVALID_PROTOCOL
	
} BCM_enProtocolId_t;

/* BCM States */
typedef enum
{
	BCM_EN_IDLE = 0,
	
	/* UART Protocol */
	BCM_EN_UART_READY_TO_RECEIVE,
	BCM_EN_UART_RECEIVE_COMPLETE,
	BCM_EN_UART_READY_TO_TRANSMIT,
	BCM_EN_UART_TRANSMIT_COMPLETE,
	
	/* SPI Protocol */
	BCM_EN_SPI_READY_TO_RECEIVE,
	BCM_EN_SPI_RECEIVE_COMPLETE,
	BCM_EN_SPI_READY_TO_TRANSMIT,
	BCM_EN_SPI_TRANSMIT_COMPLETE,
		
	/* TWI Protocol */
	BCM_EN_TWI_READY_TO_RECEIVE,
	BCM_EN_TWI_RECEIVE_COMPLETE,
	BCM_EN_TWI_READY_TO_TRANSMIT,
	BCM_EN_TWI_TRANSMIT_COMPLETE,
	
	BCM_EN_INVALID_STATE

} BCM_enState_t;

/* BCM Error States */
typedef enum
{
	BCM_EN_NOK = 0,
	BCM_EN_OK
	
} BCM_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* BCM Functions' Prototypes */

/*
 Name: BCM_initialization
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to initialize BCM.
*/
extern BCM_enErrorState_t BCM_initialization( BCM_enProtocolId_t en_a_protocolId );

/*
 Name: BCM_deinitialization
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to deinitialize BCM.
*/
extern BCM_enErrorState_t BCM_deinitialization( BCM_enProtocolId_t en_a_protocolId );

/*
 Name: BCM_receiveByte
 Input: en ProtocolId and Pointer to u8 ReturnedReceiveByte
 Output: en Error or No Error
 Description: Function to Transmit Byte.
*/
extern BCM_enErrorState_t BCM_receiveByte( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_returnedReceiveByte );

/*
 Name: BCM_receiveString
 Input: en ProtocolId and Pointer to u8 ReturnedReceiveString
 Output: en Error or No Error
 Description: Function to Receive Byte.
*/
extern BCM_enErrorState_t BCM_receiveString( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_returnedReceiveString );

/*
 Name: BCM_transmitByte
 Input: en ProtocolId and u8 TransmitByte
 Output: en Error or No Error
 Description: Function to Transmit Byte.
*/
extern BCM_enErrorState_t BCM_transmitByte( BCM_enProtocolId_t en_a_protocolId, u8 u8_a_transmitByte );

/*
 Name: BCM_transmitString
 Input: en ProtocolId and Pointer to u8 TransmitString
 Output: en Error or No Error
 Description: Function to Transmit String.
*/
extern BCM_enErrorState_t BCM_transmitString( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_transmitString );

/*
 Name: BCM_receiveDispatcher
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to execute the periodic actions and notifies the user with the needed events over a specific BCM instance.
*/
extern BCM_enErrorState_t BCM_receiveDispatcher( BCM_enProtocolId_t en_a_protocolId );

/*
 Name: BCM_transmitDispatcher
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to execute the periodic actions and notifies the user with the needed events over a specific BCM instance.
*/
extern BCM_enErrorState_t BCM_transmitDispatcher( BCM_enProtocolId_t en_a_protocolId );

/*
 Name: BCM_receiveCompleteSetCallback
 Input: en ProtocolId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( ReceiveCompleteInterruptAction ), and then pass this address to ISR function.
*/
extern BCM_enErrorState_t BCM_receiveCompleteSetCallback( BCM_enProtocolId_t en_a_protocolId, void ( *vpf_a_receiveCompleteInterruptAction ) ( void ) );

/*
 Name: BCM_transmitCompleteSetCallback
 Input: en ProtocolId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TransmitCompleteInterruptAction ), and then pass this address to ISR function.
*/
extern BCM_enErrorState_t BCM_transmitCompleteSetCallback( BCM_enProtocolId_t en_a_protocolId, void ( *vpf_a_transmitCompleteInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* BCM_INTERFACE_H_ */