/*
 * bcm_program.c
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Basic Communication Manager (BCM) functions' implementation.
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

/* SRVL */
#include "bcm_interface.h"

/*******************************************************************************************************************************************************************/
/* BCM Global Variables */

/* Global Pointers to Functions, these functions ( in APP Layer ) which those 2 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *avpf_gs_receiveCompleteInterruptActions[3]  ) ( void ) = { STD_TYPES_NULL, STD_TYPES_NULL, STD_TYPES_NULL };
static void ( *avpf_gs_transmitCompleteInterruptActions[3] ) ( void ) = { STD_TYPES_NULL, STD_TYPES_NULL, STD_TYPES_NULL };

/* Global Arrays of Pointers, to store multiple strings during Reception or Transmission, for each Communication Protocol ( i.e.: UART, SPI, and TWI respectively ). */
static u8 *apu8_gs_receiveUARTQueue[10]  = { STD_TYPES_NULL };
static u8 *apu8_gs_transmitUARTQueue[10] = { STD_TYPES_NULL };

// static u8 *apu8_gs_receiveSPIQueue[10]   = { STD_TYPES_NULL };
// static u8 *apu8_gs_transmitSPIQueue[10]  = { STD_TYPES_NULL };

// static u8 *apu8_gs_receiveTWIQueue[10]   = { STD_TYPES_NULL };
// static u8 *apu8_gs_transmitTWIQueue[10]  = { STD_TYPES_NULL };

/* Global Arrays of Enumerations, to store BCM different states during Reception or Transmission, for each Communication Protocol ( i.e.: UART, SPI, and TWI respectively ). */
static BCM_enState_t aen_gs_receiveStates[3]  = { BCM_EN_IDLE, BCM_EN_IDLE, BCM_EN_IDLE };
static BCM_enState_t aen_gs_transmitStates[3] = { BCM_EN_IDLE, BCM_EN_IDLE, BCM_EN_IDLE };

/* Global Arrays of Boolean, to  */
static bool abool_gs_firstCharToReceive[3]  = { STD_TYPES_TRUE, STD_TYPES_TRUE, STD_TYPES_TRUE };
static bool abool_gs_firstCharToTransmit[3] = { STD_TYPES_TRUE, STD_TYPES_TRUE, STD_TYPES_TRUE };

/*******************************************************************************************************************************************************************/
/* BCM Static Functions' Prototypes */

static void BCM__UARTReceiveISR ( void );
static void BCM__UARTTransmitISR( void );

// static void BCM__SPIReceiveISR ( void );
// static void BCM__SPITransmitISR( void );

// static void BCM__TWIReceiveISR ( void );
// static void BCM__TWITransmitISR( void );

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_initialization
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to initialize BCM.
*/
BCM_enErrorState_t BCM_initialization( BCM_enProtocolId_t en_a_protocolId )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range. */
	if ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL )
	{
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				//UART_linkConfigInitialization( &g_str_uart_config );
				UART_initialization();
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId! */
		en_l_errorState = BCM_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_deinitialization
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to deinitialize BCM.
*/
BCM_enErrorState_t BCM_deinitialization( BCM_enProtocolId_t en_a_protocolId )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range. */
	if ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL )
	{
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId! */
		en_l_errorState = BCM_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_receiveByte
 Input: en ProtocolId and Pointer to u8 ReturnedReceiveByte
 Output: en Error or No Error
 Description: Function to Transmit Byte.
*/
BCM_enErrorState_t BCM_receiveByte( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_returnedReceiveByte )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range and Pointer is not equal to NULL. */
	if ( ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL ) && ( pu8_a_returnedReceiveByte != STD_TYPES_NULL ) )
	{
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				UART_receiveByte( UART_EN_NON_BLOCKING_MODE, pu8_a_returnedReceiveByte );
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId or Pointer is NULL! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_receiveString
 Input: en ProtocolId and Pointer to u8 ReturnedReceiveString
 Output: en Error or No Error
 Description: Function to Receive Byte.
*/
BCM_enErrorState_t BCM_receiveString( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_returnedReceiveString )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Define local static array to store ReceiveQueuesIndexes for each Protocol. */
	static u16 au16_ls_receiveQueuesIndexes[3] = { 0, 0, 0 };
		
	/* Check 1: ProtocolId is in the valid range and Pointer is not equal to NULL. */
	if ( ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL ) && ( pu8_a_returnedReceiveString != STD_TYPES_NULL ) )
	{		
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				/* Check 1.1.1: It is the first character to Receive. */
				if ( abool_gs_firstCharToReceive[( u8 ) en_a_protocolId] == STD_TYPES_TRUE )
				{
					UART_RXCSetCallback( &BCM__UARTReceiveISR );
					UART_enableInterrupt( UART_EN_RXC_INT );
					
					abool_gs_firstCharToReceive[( u8 ) en_a_protocolId] = STD_TYPES_FALSE;
				}
				
				apu8_gs_receiveUARTQueue[ au16_ls_receiveQueuesIndexes[( u8 ) BCM_EN_PROTOCOL_0] ] = pu8_a_returnedReceiveString;
				
				au16_ls_receiveQueuesIndexes[( u8 ) en_a_protocolId]++;
				
				break;
			}
				
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
				
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
				
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId or Pointer is NULL! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_transmitByte
 Input: en ProtocolId and u8 TransmitByte
 Output: en Error or No Error
 Description: Function to Transmit Byte.
*/
BCM_enErrorState_t BCM_transmitByte( BCM_enProtocolId_t en_a_protocolId, u8 u8_a_transmitByte )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range. */
	if ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL )
	{		
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				UART_transmitByte( UART_EN_NON_BLOCKING_MODE, u8_a_transmitByte );
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_transmitString
 Input: en ProtocolId and Pointer to u8 TransmitString
 Output: en Error or No Error
 Description: Function to Transmit String.
*/
BCM_enErrorState_t BCM_transmitString( BCM_enProtocolId_t en_a_protocolId, u8 *pu8_a_transmitString )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Define local static array to store TransmitQueueIndexes for each Protocol. */
	static u16 au16_ls_transmitQueueIndexes[3] = { 0, 0, 0 };
	
	/* Check 1: ProtocolId is in the valid range and Pointer is not equal to NULL. */
	if ( ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL ) && ( pu8_a_transmitString != STD_TYPES_NULL ) )
	{		
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				/* Check 1.1.1: First Character to be Transmitted. */
				if ( abool_gs_firstCharToTransmit[( u8 ) BCM_EN_PROTOCOL_0] == STD_TYPES_TRUE )
				{
					/* Step 1: Set the Callback function. */
					UART_TXCSetCallback( &BCM__UARTTransmitISR );
					
					/* Step 2: Enable TXC Interrupt. */
					UART_enableInterrupt( UART_EN_TXC_INT );
					
					/* Step 3: Transmit the first Character of String. */
					UART_transmitByte( UART_EN_NON_BLOCKING_MODE, pu8_a_transmitString[ au16_ls_transmitQueueIndexes[( u8 ) BCM_EN_PROTOCOL_0] ] );
					
					/* Step 4: Update FirstCharToTransmit to False. */
					abool_gs_firstCharToTransmit[( u8 ) BCM_EN_PROTOCOL_0] = STD_TYPES_FALSE;
				}
				
				/* Step 5: Store TransmitString parameter in the TransmitQueue. */
				apu8_gs_transmitUARTQueue[ au16_ls_transmitQueueIndexes[( u8 ) BCM_EN_PROTOCOL_0] ] = pu8_a_transmitString;
				
				/* Step 6: Increment TransmitQueueIndexe. */
				au16_ls_transmitQueueIndexes[( u8 ) BCM_EN_PROTOCOL_0]++;
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId or Pointer is NULL! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_receiveDispatcher
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to execute the periodic actions and notifies the user with the needed events over a specific BCM instance.
*/
BCM_enErrorState_t BCM_receiveDispatcher( BCM_enProtocolId_t en_a_protocolId )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range. */
	if ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL )
	{
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				static u8 u8_ls_receiveQueueStringsIndex = 0, u8_ls_stringCharactersIndex = 0;
				u8 u8_l_receivedByte = 0;
				
				/* Check 1.1.1: ReceiveState is Ready to Receive. */	
				if ( aen_gs_receiveStates[( u8 ) BCM_EN_PROTOCOL_0] == BCM_EN_UART_READY_TO_RECEIVE )
				{
					/* Step 1: Start Receiving. */
					UART_receiveByte( UART_EN_NON_BLOCKING_MODE, &u8_l_receivedByte );
					
					/* Step 2: Store Received Byte in ReceiveQueue. */
					apu8_gs_receiveUARTQueue[u8_ls_receiveQueueStringsIndex][u8_ls_stringCharactersIndex] = u8_l_receivedByte;
						
					/* Check 1.1.1.1: String is not terminated. */
					if ( apu8_gs_receiveUARTQueue[u8_ls_receiveQueueStringsIndex][u8_ls_stringCharactersIndex] != BCM_U8_END_OF_STRING )
					{
						/* Step 3: Increment StringCharactersIndex. */
						u8_ls_stringCharactersIndex++;
					}
					/* Check 1.1.1.2: String is terminated. */
					else if ( apu8_gs_receiveUARTQueue[u8_ls_receiveQueueStringsIndex][u8_ls_stringCharactersIndex] == BCM_U8_END_OF_STRING )
					{
						/* Step 4: Reset Receiving Parameters ( i.e.: Receive is Completed ). */
						/* Reset StringCharactersIndex. */
						u8_ls_stringCharactersIndex = 0;
						/* Reset FirstCharToReceive to True. */
						abool_gs_firstCharToReceive[( u8 ) BCM_EN_PROTOCOL_0] = STD_TYPES_TRUE;
						
						/* Step 5: Increment ReceiveQueueStringsIndex. */
						u8_ls_receiveQueueStringsIndex++;						
						
						/* Step 6: Disable RXC Interrupt */
						UART_disableInterrupt( UART_EN_RXC_INT );
						
						/* Check 1.1.1.2.1: Global Pointer to Function is not equal to NULL. */
						if ( avpf_gs_receiveCompleteInterruptActions[( u8 ) BCM_EN_PROTOCOL_0] != STD_TYPES_NULL )
						{
							/* Step 7: Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( ReceiveCompleteInterruptActions ). */
							avpf_gs_receiveCompleteInterruptActions[( u8 ) BCM_EN_PROTOCOL_0]();
						}
					}
					
					/* Step 8: Update ReceiveState to Receive Complete. */
					aen_gs_receiveStates[( u8 ) BCM_EN_PROTOCOL_0] = BCM_EN_UART_RECEIVE_COMPLETE;
				}
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId! */
		en_l_errorState = BCM_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_transmitDispatcher
 Input: en ProtocolId
 Output: en Error or No Error
 Description: Function to execute the periodic actions and notifies the user with the needed events over a specific BCM instance.
*/
BCM_enErrorState_t BCM_transmitDispatcher( BCM_enProtocolId_t en_a_protocolId )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range. */
	if ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL )
	{
		/* Check 1.1: Required ProtocolId. */
		switch ( en_a_protocolId )
		{
			case BCM_EN_PROTOCOL_0:
			{
				static u8 u8_ls_transmitQueueStringsIndex = 0, u8_ls_stringCharactersIndex = 1;
				
				/* Check 1.1.1:  */
				if ( aen_gs_transmitStates[( u8 ) BCM_EN_PROTOCOL_0] == BCM_EN_UART_READY_TO_TRANSMIT )
				{
					/* check that the element being sent exists */
					if ( apu8_gs_transmitUARTQueue[u8_ls_transmitQueueStringsIndex][u8_ls_stringCharactersIndex] != '\n' )
					{
						UART_transmitByte( UART_EN_NON_BLOCKING_MODE, apu8_gs_transmitUARTQueue[u8_ls_transmitQueueStringsIndex][u8_ls_stringCharactersIndex] );
						u8_ls_stringCharactersIndex++;
					}
					/* Check if the next element in queue exists? and Terminate the sent string */
					else if ( apu8_gs_transmitUARTQueue[u8_ls_transmitQueueStringsIndex + 1] != STD_TYPES_NULL )
					{
						UART_transmitByte( UART_EN_NON_BLOCKING_MODE, BCM_U8_END_OF_STRING );
						u8_ls_stringCharactersIndex = 0;
						u8_ls_transmitQueueStringsIndex++;
					}					
					/* Terminate the sent string and reset the sending parameters */
					else if ( apu8_gs_transmitUARTQueue[u8_ls_transmitQueueStringsIndex][u8_ls_stringCharactersIndex] == '\n' )
					{
						UART_transmitByte( UART_EN_NON_BLOCKING_MODE, BCM_U8_END_OF_STRING );
						
						u8_ls_stringCharactersIndex = 1;
						
						abool_gs_firstCharToTransmit[( u8 ) BCM_EN_PROTOCOL_0] = STD_TYPES_TRUE;
						
						UART_disableInterrupt( UART_EN_TXC_INT );
						
						if ( avpf_gs_transmitCompleteInterruptActions[( u8 ) BCM_EN_PROTOCOL_0] != STD_TYPES_NULL )
						{
							avpf_gs_transmitCompleteInterruptActions[( u8 ) BCM_EN_PROTOCOL_0]();
						}
						else
						{
							/* Do Nothing. */
						}
					}
					
					aen_gs_transmitStates[( u8 ) BCM_EN_PROTOCOL_0] = BCM_EN_UART_TRANSMIT_COMPLETE;
				}
				
				break;
			}
			
			case BCM_EN_PROTOCOL_1:
			{
				/* Future Improvements. */
				break;
			}
			
			case BCM_EN_PROTOCOL_2:
			{
				/* Future Improvements. */
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}
		}
	}
	/* Check 2: ProtocolId is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId! */
		en_l_errorState = BCM_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_receiveCompleteSetCallback
 Input: en ProtocolId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( ReceiveCompleteInterruptAction ), and then pass this address to ISR function.
*/
BCM_enErrorState_t BCM_receiveCompleteSetCallback( BCM_enProtocolId_t en_a_protocolId, void ( *vpf_a_receiveCompleteInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range and Pointer to Function is not equal to NULL. */
	if ( ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL ) && ( vpf_a_receiveCompleteInterruptAction != STD_TYPES_NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( ReceiveCompleteInterruptAction ) into Global Pointer to Function ( ReceiveCompleteInterruptAction ). */
		avpf_gs_receiveCompleteInterruptActions[( u8 ) en_a_protocolId] = vpf_a_receiveCompleteInterruptAction;
	}
	/* Check 2: ProtocolId is not in the valid range or Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId or Pointer to Function is NULL! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BCM_transmitCompleteSetCallback
 Input: en ProtocolId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TransmitCompleteInterruptAction ), and then pass this address to ISR function.
*/
BCM_enErrorState_t BCM_transmitCompleteSetCallback( BCM_enProtocolId_t en_a_protocolId, void ( *vpf_a_transmitCompleteInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	BCM_enErrorState_t en_l_errorState = BCM_EN_OK;
	
	/* Check 1: ProtocolId is in the valid range and Pointer to Function is not equal to NULL. */
	if ( ( en_a_protocolId < BCM_EN_INVALID_PROTOCOL ) && ( vpf_a_transmitCompleteInterruptAction != STD_TYPES_NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( ReceiveCompleteInterruptAction ) into Global Pointer to Function ( ReceiveCompleteInterruptAction ). */
		avpf_gs_transmitCompleteInterruptActions[( u8 ) en_a_protocolId] = vpf_a_transmitCompleteInterruptAction;
	}
	/* Check 2: ProtocolId is not in the valid range or Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong ProtocolId or Pointer to Function is NULL! */
		en_l_errorState = BCM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/

static void BCM__UARTReceiveISR( void )
{
	aen_gs_receiveStates[( u8 ) BCM_EN_PROTOCOL_0] = BCM_EN_UART_READY_TO_RECEIVE;
}

/*******************************************************************************************************************************************************************/

static void BCM__UARTTransmitISR( void )
{
	aen_gs_transmitStates[( u8 ) BCM_EN_PROTOCOL_0] = BCM_EN_UART_READY_TO_TRANSMIT;
}

/*******************************************************************************************************************************************************************/

// static void BCM__SPIReceiveISR( void )
// {
// 	aen_gs_receiveStates[( u8 ) BCM_EN_PROTOCOL_1] = BCM_EN_SPI_READY_TO_RECEIVE;
// }

/*******************************************************************************************************************************************************************/

// static void BCM__SPITransmitISR( void )
// {
// 	aen_gs_transmitStates[( u8 ) BCM_EN_PROTOCOL_1] = BCM_EN_SPI_READY_TO_TRANSMIT;
// }

/*******************************************************************************************************************************************************************/

// static void BCM__TWIReceiveISR( void )
// {
// 	aen_gs_receiveStates[( u8 ) BCM_EN_PROTOCOL_2] = BCM_EN_TWI_READY_TO_RECEIVE;
// }

/*******************************************************************************************************************************************************************/

// static void BCM__TWITransmitISR( void )
// {
// 	aen_gs_transmitStates[( u8 ) BCM_EN_PROTOCOL_2] = BCM_EN_TWI_READY_TO_TRANSMIT;
// }

/*******************************************************************************************************************************************************************/