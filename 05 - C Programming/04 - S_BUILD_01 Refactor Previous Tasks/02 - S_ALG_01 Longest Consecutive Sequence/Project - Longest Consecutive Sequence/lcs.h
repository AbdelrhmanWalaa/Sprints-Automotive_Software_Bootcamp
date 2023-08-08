/*
 * lcs.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Longest Consecutive Sequence (LCS) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef LCS_H_
#define LCS_H_

/**************************************************************************************************************************/
/* LCS Includes */
#include <stdio.h>

/**************************************************************************************************************************/
/* LCS Macros */

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef signed int int32_t;

/* LCS Return Types */
#define LCS_INT8_EMPTY_ARRAY		 -1		// If the array is empty
#define LCS_INT8_ARRAY_SIZE_LESS_10	 -2		// If the array size is 0 or >10
#define LCS_INT8_NO_LCS				 -3		// If there is no LCS
#define LCS_INT8_FOUND_LCS	          0		// Otherwise

/**************************************************************************************************************************/
/* LCS Functions' Prototypes */

int8_t lcsGetSize(int32_t* array, uint8_t arraySize, uint8_t* sizeofLCS);

/**************************************************************************************************************************/

#endif /* LCS_H_ */