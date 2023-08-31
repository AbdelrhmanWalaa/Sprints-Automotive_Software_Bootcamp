/*
 * stack_program.c
 *
 *     Created on: Apr 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Stack functions' implementation.
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

/* STACK */
#include "stack_interface.h"
#include "stack_config.h"

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_createEmptyStack
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to Stack type, initialize this Stack with NULL, and initialize the top with -1.
*/
s8 STACK_createEmptyStack( STACK_stStack_t *pst_a_stack )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
		
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_stack != STD_TYPES_NULL )
	{
		/* Step 1: Initialize Stack with NULL */
		/* Loop: Until end of Stack */
		for ( u8 u8_l_index = 0; u8_l_index < STACK_U8_SIZE; u8_l_index++ )
		{
			pst_a_stack->apu8_g_elements[u8_l_index] = STD_TYPES_NULL;
		}

		/* Step 2: Initialize top with -1 */
		pst_a_stack->s8_g_topStack = -1;
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_push
 Input: Pointer to st Stack and Pointer to u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the DataString to be stored, then stores the Pointer to DataString passed into the Stack.
*/
s8 STACK_push( STACK_stStack_t *pst_a_stack, u8 *pu8_a_dataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
	
	/* Check 1: Pointers are not equal to NULL */
	if ( ( pst_a_stack != STD_TYPES_NULL ) && ( pu8_a_dataString != STD_TYPES_NULL ) )
	{
		/* Check 1.1: Stack is Full */
		if ( STACK_isFull( pst_a_stack ) == STACK_S8_FULL_STACK )
		{
			s8_l_errorState = STACK_S8_FULL_STACK;
		}
		/* Check 1.2: Stack is not Full */
		else
		{
			pst_a_stack->s8_g_topStack++;
			pst_a_stack->apu8_g_elements[pst_a_stack->s8_g_topStack] = pu8_a_dataString;
		}
	}
	/* Check 2: Pointers are equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointers are NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}
	
	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_pop
 Input: Pointer to st Stack and Pointer to Address of u8 DataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the DataString to be returned, then returns the popped Pointer to DataString.
*/
s8 STACK_pop( STACK_stStack_t *pst_a_stack, u8 **ppu8_a_returnedAddressOfDataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
		
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_stack != STD_TYPES_NULL )
	{
		/* Check 1.1: Stack is Empty */
		if ( STACK_isEmpty( pst_a_stack ) == STACK_S8_EMPTY_STACK)
		{
			s8_l_errorState = STACK_S8_EMPTY_STACK;
		}
		/* Check 1.2: Stack is not Empty */
		else
		{
			*ppu8_a_returnedAddressOfDataString = pst_a_stack->apu8_g_elements[pst_a_stack->s8_g_topStack];
			
			pst_a_stack->apu8_g_elements[pst_a_stack->s8_g_topStack] = STD_TYPES_NULL;
			pst_a_stack->s8_g_topStack--;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}
	
	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_getStackTopValue
 Input: Pointer to st Stack and Pointer to Address of u8 TopDataString
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack and reference to the TopDataString to be returned, then returns the Pointer to TopDataString.
*/
s8 STACK_getStackTopValue( STACK_stStack_t *pst_a_stack, u8 **ppu8_a_returnedAddressOfTopDataString )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_stack != STD_TYPES_NULL )
	{
		/* Check 1.1: Stack is Empty */
		if ( STACK_isEmpty( pst_a_stack ) == STACK_S8_EMPTY_STACK)
		{
			s8_l_errorState = STACK_S8_EMPTY_STACK;
		}
		/* Check 1.2: Stack is not Empty */
		else
		{
			*ppu8_a_returnedAddressOfTopDataString = pst_a_stack->apu8_g_elements[pst_a_stack->s8_g_topStack];
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}
	
	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_isFull
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack, then checks if the Stack is Full or not.
*/
s8 STACK_isFull( STACK_stStack_t *pst_a_stack )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_stack != STD_TYPES_NULL )
	{
		/* Check 1.1: Top value of Stack "top" = SIZE - 1 */
		if ( pst_a_stack->s8_g_topStack == STACK_U8_SIZE - 1 )
		{
			s8_l_errorState = STACK_S8_FULL_STACK;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STACK_isEmpty
 Input: Pointer to st Stack
 Output: s8 Error or No Error
 Description: Function to take a reference to the Stack, then checks if the Stack is Empty or not.
*/
s8 STACK_isEmpty( STACK_stStack_t *pst_a_stack )
{
	/* Define local variable to set the error state = OK */
	s8 s8_l_errorState = STACK_S8_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_stack != STD_TYPES_NULL )
	{
		/* Check 1.1: Top value of Stack "top" = -1 */
		if ( pst_a_stack->s8_g_topStack == -1 )
		{
			s8_l_errorState = STACK_S8_EMPTY_STACK;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NULL PTR, Pointer is NULL! */
		s8_l_errorState = STACK_S8_NULL_PTR;
	}

	return s8_l_errorState;
}

/*******************************************************************************************************************************************************************/