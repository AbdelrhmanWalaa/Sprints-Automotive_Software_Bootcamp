/*
 * queue_interface.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Queue functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef QUEUE_INTERFACE_H_
#define QUEUE_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* QUEUE Includes */

/* LIB */
#include "../../std_types/std_types.h"

/* QUEUE */
#include "queue_config.h"

/*******************************************************************************************************************************************************************/
/* QUEUE Macros */

/* QUEUE Error States */
#define QUEUE_S8_FULL_QUEUE			 -1		// If the Queue is full
#define QUEUE_S8_EMPTY_QUEUE		 -2		// If the Queue is empty
#define QUEUE_S8_NULL_PTR			  0		// If there is a NULL pointer
#define QUEUE_S8_OK					  1		// If the Queue neither full nor empty

/* QUEUE Data Structure */
typedef struct
{
	u8 *apu8_g_elements[QUEUE_U8_SIZE];     // Array of Pointers to u8 Elements
	s8 s8_g_tailQueue;						// Index value of Queue Tail
	
} QUEUE_stQueue_t;

/*******************************************************************************************************************************************************************/
/* QUEUE Functions' Prototypes */

/*
 Name: QUEUE_createEmptyQueue
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to Queue type, initialize this Queue with NULL, and initialize the tail with -1.
*/
extern s8 QUEUE_createEmptyQueue( QUEUE_stQueue_t *pst_a_queue );

/*
 Name: QUEUE_enqueue
 Input: Pointer to st Queue and Pointer to u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the DataString to be stored, then stores the Pointer to DataString passed into the Queue.
*/
extern s8 QUEUE_enqueue( QUEUE_stQueue_t *pst_a_queue, u8 *pu8_a_dataString );

/*
 Name: QUEUE_dequeue
 Input: Pointer to st Queue and Pointer to Address of u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the DataString to be returned, then returns the dequeued Pointer to DataString.
*/
extern s8 QUEUE_dequeue( QUEUE_stQueue_t *pst_a_queue, u8 **ppu8_a_returnedAddressOfDataString );

/*
 Name: QUEUE_getQueueHeadValue
 Input: Pointer to st Queue and Pointer to Address of u8 HeadDataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue and reference to the HeadDataString to be returned, then returns the Pointer to HeadDataString.
*/
extern s8 QUEUE_getQueueHeadValue( QUEUE_stQueue_t *pst_a_queue, u8 **ppu8_a_returnedAddressOfHeadDataString );

/*
 Name: QUEUE_isFull
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue, then checks if the Queue is Full or not.
*/
extern s8 QUEUE_isFull( QUEUE_stQueue_t *pst_a_queue );

/*
 Name: QUEUE_isEmpty
 Input: Pointer to st Queue
 Output: s8 Error or No Error
 Description: Function to take a reference to the Queue, then checks if the Queue is Empty or not.
*/
extern s8 QUEUE_isEmpty( QUEUE_stQueue_t *pst_a_queue );

/*******************************************************************************************************************************************************************/

#endif /* QUEUE_INTERFACE_H_ */