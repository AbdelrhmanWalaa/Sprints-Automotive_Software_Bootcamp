/*
 * sort.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Sort functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef SORT_H_
#define SORT_H_

/**************************************************************************************************************************/
/* Sort Includes */
#include <stdio.h>

/**************************************************************************************************************************/
/* Sort Macros */

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;

/* Sort Return Types */
#define SORT_INT8_EMPTY_ARRAY			 -1		// If the array is empty
#define SORT_INT8_ARRAY_SIZE_LESS_10	 -2		// If the array size is 0 or >10
#define SORT_INT8_OK					  0		// If sorting is done without errors

/**************************************************************************************************************************/
/* Sort Functions' Prototypes */

int8_t insertionSort(int32_t* array, uint8_t arraySize);
void printArray(int32_t* array, uint8_t arraySize);

/**************************************************************************************************************************/

#endif /* SORT_H_ */