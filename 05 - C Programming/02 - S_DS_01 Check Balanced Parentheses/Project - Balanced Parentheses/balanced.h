/*
 * balanced.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Balanced Parentheses functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef BALANCED_H_
#define BALANCED_H_

/**************************************************************************************************************************/
/* Balanced Includes */
#include <stdio.h>
#include "stack.h"

/**************************************************************************************************************************/
/* Balanced Macros */

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;

/* Balanced Return Types */
#define BLPAR_INT8_NOT_BALANCED			 -1		// If the parentheses are not balanced
#define BLPAR_INT8_NO_PAR_USED			 -2		// If neither of parentheses - {, }, (, ) - is used
#define BLPAR_INT8_BALANCED				  0		// If the stack neither full nor empty

/**************************************************************************************************************************/
/* Balanced Functions' Prototypes */

int8_t isBalancedParentheses(uint8_t* expression);

/**************************************************************************************************************************/

#endif /* BALANCED_H_ */