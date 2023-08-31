/*
 * stack_interface.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Stack functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* STACK Includes */

/* LIB */
#include "../../std_types/std_types.h"

/* STACK */
#include "stack_config.h"

/*******************************************************************************************************************************************************************/
/* STACK Macros */

/* STACK Error States */
#define STACK_S8_FULL_STACK			 -1		// If the Stack is full
#define STACK_S8_EMPTY_STACK		 -2		// If the Stack is empty
#define STACK_S8_NULL_PTR			  0		// If there is a NULL pointer
#define STACK_S8_OK					  1		// If the Stack neither full nor empty

/* STACK Data Structure */
typedef struct
{
	u8 *apu8_g_elements[STACK_U8_SIZE];     // Array of Pointers to u8 Elements
	s8 s8_g_topStack;				   		// Index value of Stack Top
	
} STACK_stStack_t;

/*******************************************************************************************************************************************************************/
/* STACK Functions' Prototypes */

/*
 Name: STACK_createEmptyStack
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to Stack type, initialize this Stack with NULL, and initialize the top with -1.
*/
extern s8 STACK_createEmptyStack( STACK_stStack_t *pst_a_stack );

/*
 Name: STACK_push
 Input: Pointer to st Stack and Pointer to u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the DataString to be stored, then stores the Pointer to DataString passed into the Stack.
*/
extern s8 STACK_push( STACK_stStack_t *pst_a_stack, u8 *pu8_a_dataString );

/*
 Name: STACK_pop
 Input: Pointer to st Stack and Pointer to Address of u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the DataString to be returned, then returns the popped Pointer to DataString.
*/
extern s8 STACK_pop( STACK_stStack_t *pst_a_stack, u8 **ppu8_a_returnedAddressOfDataString );

/*
 Name: STACK_getStackTopValue
 Input: Pointer to st Stack and Pointer to Address of u8 TopDataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the TopDataString to be returned, then returns the Pointer to TopDataString.
*/
extern s8 STACK_getStackTopValue( STACK_stStack_t *pst_a_stack, u8 **ppu8_a_returnedAddressOfTopDataString );

/*
 Name: STACK_isFull
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack, then checks if the Stack is Full or not.
*/
extern s8 STACK_isFull( STACK_stStack_t *pst_a_stack );

/*
 Name: STACK_isEmpty
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack, then checks if the Stack is Empty or not.
*/
extern s8 STACK_isEmpty( STACK_stStack_t *pst_a_stack );

/*******************************************************************************************************************************************************************//**************************************************************************************************************************/

#endif /* STACK_INTERFACE_H_ */