/*
 * stack.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Stack functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef STACK_H_
#define STACK_H_

/**************************************************************************************************************************/
/* Stack Includes */
#include <stdio.h>

/**************************************************************************************************************************/
/* Stack Macros */

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;

#define STACK_SIZE	10

typedef struct stack {
	uint8_t elements[STACK_SIZE];
	int8_t top;
}ST_stack_t;

/* Stack Return Types */
#define STACK_INT8_FULL_STACK			 -1		// If the stack is full
#define STACK_INT8_EMPTY_STACK			 -2		// If the stack is empty
#define STACK_INT8_OK					  0		// If the stack neither full nor empty

/**************************************************************************************************************************/
/* Stack Functions' Prototypes */

void createEmptyStack(ST_stack_t* stack);
int8_t push(ST_stack_t* stack, uint8_t data);
int8_t pop(ST_stack_t* stack, uint8_t* data);
int8_t printStack(ST_stack_t* stack);
int8_t getStackTop(ST_stack_t* stack, uint8_t* topData);
int8_t isFull(ST_stack_t* stack);
int8_t isEmpty(ST_stack_t* stack);

/**************************************************************************************************************************/

#endif /* STACK_H_ */