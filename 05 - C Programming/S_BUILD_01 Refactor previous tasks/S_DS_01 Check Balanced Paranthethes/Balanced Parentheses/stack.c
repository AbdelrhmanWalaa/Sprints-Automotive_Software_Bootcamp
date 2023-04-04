/*
 * stack.c
 *
 *     Created on: Apr 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Stack functions' implementation.
 */

/* Stack */
#include "stack.h"

/**************************************************************************************************************************/
/*
 Name: createEmptyStack
 Input: Pointer stack structure
 Output: void
 Description: Function to take a reference to stack type, initialize this stack with zeros,and initialize the top with -1.
*/
void createEmptyStack(ST_stack_t *stack)
{
	/* Step 1: Initialize newStack with zeros */
	/* Loop: Until end of stack */
	for (uint8_t index = 0; index < STACK_SIZE; index++)
	{
		stack->elements[index] = 0;
	}

	/* Step 2: Initialize top with -1 */
	stack->top = -1;
}

/**************************************************************************************************************************/
/*
 Name: push
 Input: Pointer stack structure and Pointer to uint8 data
 Output: int8 errorState
 Description: Function to take a reference to the stack and data to store, then stores the data passed into the stack.
*/
int8_t push(ST_stack_t *stack, uint8_t data)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check 1: Stack is full */
	if (isFull(stack) == STACK_INT8_FULL_STACK)
	{
		errorState = STACK_INT8_FULL_STACK;
	}
	/* Check 2: Stack is not full */
	else
	{
		stack->top++;
		stack->elements[stack->top] = data;		
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: pop
 Input: Pointer stack structure and uint8 data
 Output: int8 errorState
 Description: Function to take a reference to the stack, then stores the data popped from the stack in a data variable.
*/
int8_t pop(ST_stack_t *stack, uint8_t *data)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check 1: Stack is empty */
	if (isEmpty(stack) == STACK_INT8_EMPTY_STACK)
	{
		errorState = STACK_INT8_EMPTY_STACK;
	}
	/* Check 2: Stack is not empty */
	else
	{
		*data = stack->elements[stack->top];
		stack->elements[stack->top] = '\0';
		stack->top--;
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: printStack
 Input: Pointer stack structure
 Output: int8 errorState
 Description: Function to take a reference to the stack, then prints all stack's data starting from the top.
*/
int8_t printStack(ST_stack_t *stack)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check 1: Stack is empty */
	if (isEmpty(stack) == STACK_INT8_EMPTY_STACK)
	{
		errorState = STACK_INT8_EMPTY_STACK;
	}
	/* Check 2: Stack is not empty */
	else
	{
		/* Check 2.1: Stack is full */
		if (isFull(stack) == STACK_INT8_FULL_STACK)
		{
			errorState = STACK_INT8_FULL_STACK;
		}
			
		/* Loop: Until the of the stack */
		for (int8_t index = stack->top; index > -1; index--)
		{
			printf(" %d", stack->elements[index]);
		}

		printf("\n");
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: getStackTop
 Input: Pointer stack structure and Pointer to uint8 topData
 Output: int8 errorState
 Description: Function to take a reference to the stack, then stores its top data into a variable.
*/
int8_t getStackTop(ST_stack_t *stack, uint8_t *topData)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check 1: Stack is empty */
	if (isEmpty(stack) == STACK_INT8_EMPTY_STACK)
	{
		errorState = STACK_INT8_EMPTY_STACK;
	}
	/* Check 2: Stack is not empty */
	else
	{
		*topData = stack->elements[stack->top];
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: isFull
 Input: Pointer stack structure
 Output: int8 errorState
 Description: Function to take a reference to the stack, then checks if the stack is full or not.
*/
int8_t isFull(ST_stack_t *stack)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check: Top value of stack "top" = 9 */
	if (stack->top == 9)
	{
		errorState = STACK_INT8_FULL_STACK;
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: isEmpty
 Input: Pointer stack structure
 Output: int8 errorState
 Description: Function to take a reference to the stack, then checks if the stack is empty or not.
*/
int8_t isEmpty(ST_stack_t *stack)
{
	int8_t errorState = STACK_INT8_OK;

	/* Check: Top value of stack "top" = -1 */
	if (stack->top == -1)
	{
		errorState = STACK_INT8_EMPTY_STACK;
	}

	return errorState;
}

/**************************************************************************************************************************/