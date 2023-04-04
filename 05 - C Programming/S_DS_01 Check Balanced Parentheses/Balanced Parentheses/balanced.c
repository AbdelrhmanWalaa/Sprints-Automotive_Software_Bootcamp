/*
 * stack.c
 *
 *     Created on: Apr 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Balanced Parentheses functions' implementation.
 */

 /* Balanced */
#include "balanced.h"

/**************************************************************************************************************************/
/*
 Name: isBalancedParentheses
 Input: Pointer uint8 expression
 Output: int8 errorState
 Description: Function to take an expression array max 10 characters, checks if the parentheses are balanced or not, and checks the following parentheses types {, }, (, ) only.
*/
int8_t isBalancedParentheses(uint8_t *expression)
{
	int8_t errorState = BLPAR_INT8_NO_PAR_USED;
	uint8_t data = 0, index = 0;

	/* Step 1: Create an empty stack */
	ST_stack_t newStack;
	createEmptyStack(&newStack);

	/* Step 2: Check the expression */
	/* Loop: Until the end of expression */
	while (expression[index] != '\0')
	{
		/* Check 1: Required character */
		switch (expression[index])
		{
			/* Case 1: Parenthesis is '{' or '(' */
			case '{':
			case '(':
				push(&newStack, expression[index]);
				break;

			/* Case 2: Parenthesis is '}' or ')' */
			case '}':
			case ')':

				/* Check 1.1: Stack is not empty */
				if (pop(&newStack, &data) != STACK_INT8_EMPTY_STACK)
				{
					/* Check 1.1.1: Each parenthesis matches to the other */
					if (((data == '{') && (expression[index] == '}')) || ((data == '(') && (expression[index] == ')')))
					{
						
						errorState = BLPAR_INT8_BALANCED;
					}
					/* Check 1.1.2: Each parenthesis doesn't matche to the other */
					else
					{
						errorState = BLPAR_INT8_NOT_BALANCED;
					}
				}
				/* Check 1.1: Stack is empty */
				else
				{
					errorState = BLPAR_INT8_NOT_BALANCED;
				}
				break;		
		}

		/* Check 2: ErrorState is updated to Not_Balanced */
		if (errorState == BLPAR_INT8_NOT_BALANCED)
		{
			break;
		}

		index++;
	}

	return errorState;
}

/**************************************************************************************************************************/