/*
 * queue_program.c
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Queue functions' implementation.
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

/* QUEUE */
#include "queue_interface.h"
#include "queue_config.h"

/*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_createEmptyQueue
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to Queue type, initialize this Queue with NULL, and initialize the tail with -1.
*/
s8 QUEUE_createEmptyQueue( QUEUE_stQueue_t *pst_a_queue )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;
		
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_queue != STD_TYPES_NULL )
	{
		/* Step 1: Initialize Queue with NULL */
		/* Loop: Until end of Queue */
		for ( u8 u8_l_index = 0; u8_l_index < QUEUE_U8_SIZE; u8_l_index++ )
		{
			pst_a_queue->apu8_g_elements[u8_l_index] = STD_TYPES_NULL;
		}

		/* Step 2: Initialize tail with -1 */
		pst_a_queue->s8_g_tailQueue = -1;
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

//*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_enqueue
 Input: Pointer to st Queue and Pointer to u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the DataString to be stored, then stores the Pointer to DataString passed into the Queue.
*/
s8 QUEUE_enqueue( QUEUE_stQueue_t *pst_a_queue, u8 *pu8_a_dataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;
	
	/* Check 1: Pointers are not equal to NULL */
	if ( ( pst_a_queue != STD_TYPES_NULL ) && ( pu8_a_dataString != STD_TYPES_NULL ) )
	{
		/* Check 1.1: Queue is Full */
		if ( QUEUE_isFull( pst_a_queue ) == QUEUE_S8_FULL_QUEUE )
		{
			s8_l_errorState = QUEUE_S8_FULL_QUEUE;
		}
		/* Check 1.2: Queue is not Full */
		else
		{
			pst_a_queue->s8_g_tailQueue++;
			pst_a_queue->apu8_g_elements[pst_a_queue->s8_g_tailQueue] = pu8_a_dataString;
		}
	}
	/* Check 2: Pointers are equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointers are NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}
	
	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_dequeue
 Input: Pointer to st Queue and Pointer to Address of u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the DataString to be returned, then returns the dequeued Pointer to DataString.
*/
s8 QUEUE_dequeue( QUEUE_stQueue_t *pst_a_queue, u8 **ppu8_a_returnedAddressOfDataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_queue != STD_TYPES_NULL )
	{
		/* Check 1.1: Queue is Empty */
		if ( QUEUE_isEmpty( pst_a_queue ) == QUEUE_S8_EMPTY_QUEUE )
		{
			s8_l_errorState = QUEUE_S8_EMPTY_QUEUE;
		}
		/* Check 1.2: Queue is not Empty */
		else
		{
			*ppu8_a_returnedAddressOfDataString = pst_a_queue->apu8_g_elements[0];

			/* Loop: Until end of Queue, in order to shift Queue to the left */
			for ( u8 u8_l_index = 0; u8_l_index < pst_a_queue->s8_g_tailQueue; u8_l_index++ )
			{
				pst_a_queue->apu8_g_elements[u8_l_index] = pst_a_queue->apu8_g_elements[u8_l_index + 1];
			}

			pst_a_queue->apu8_g_elements[pst_a_queue->s8_g_tailQueue] = STD_TYPES_NULL;
			pst_a_queue->s8_g_tailQueue--;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_getQueueHeadValue
 Input: Pointer to st Queue and Pointer to Address of u8 HeadDataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the HeadDataString to be returned, then returns the Pointer to HeadDataString.
*/
s8 QUEUE_getQueueHeadValue( QUEUE_stQueue_t *pst_a_queue, u8 **ppu8_a_returnedAddressOfHeadDataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_queue != STD_TYPES_NULL )
	{
		/* Check 1.1: Queue is Empty */
		if ( QUEUE_isEmpty( pst_a_queue ) == QUEUE_S8_EMPTY_QUEUE )
		{
			s8_l_errorState = QUEUE_S8_EMPTY_QUEUE;
		}
		/* Check 1.2: Queue is not Empty */
		else
		{
			*ppu8_a_returnedAddressOfHeadDataString = pst_a_queue->apu8_g_elements[0];
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_isFull
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue, then checks if the Queue is Full or not.
*/
s8 QUEUE_isFull( QUEUE_stQueue_t *pst_a_queue )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_queue != STD_TYPES_NULL )
	{
		/* Check 1.1: Tail value of Queue "tail" = SIZE - 1 */
		if ( pst_a_queue->s8_g_tailQueue == QUEUE_U8_SIZE - 1 )
		{
			s8_l_errorState = QUEUE_S8_FULL_QUEUE;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: QUEUE_isEmpty
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue, then checks if the Queue is Empty or not.
*/
s8 QUEUE_isEmpty( QUEUE_stQueue_t *pst_a_queue )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = QUEUE_S8_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_queue != STD_TYPES_NULL )
	{
		/* Check 1.1: Tail value of Queue "tail" = -1 */
		if ( pst_a_queue->s8_g_tailQueue == -1 )
		{
			s8_l_errorState = QUEUE_S8_EMPTY_QUEUE;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = QUEUE_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/