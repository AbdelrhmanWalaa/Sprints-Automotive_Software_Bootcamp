/*
 * lcs.c
 *
 *     Created on: Apr 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Longest Consecutive Sequence (LCS) functions' implementation.
 */

 /* LCS */
#include "lcs.h"

/**************************************************************************************************************************/
/*
 Name: lcsGetSize
 Input: Pointer int32 to array, uint8 arraySize, and Pointer to uint8 sizeofLCS
 Output: int8 errorState
 Description: Function to take a reference to an array, array size, and reference to store the size of the LCS, using the insertion sort algorithm. The function will search for the LCS in the array and stores its size.
*/
int8_t lcsGetSize(int32_t* array, uint8_t arraySize, uint8_t* sizeofLCS)
{
	int8_t errorState = LCS_INT8_FOUND_LCS;

	/* Check 1: array is empty */
	if (array == NULL)
	{
		errorState = LCS_INT8_EMPTY_ARRAY;
	}
	/* Check 2: arraySize is less than 10 */
	else if (arraySize < 10)
	{
		errorState = LCS_INT8_ARRAY_SIZE_LESS_10;
	}
	/* Check 3: Array can be sorted */
	else
	{
		uint8_t maxLCS = 1;

		/* Loop: Until the end of array */
		for (uint8_t index = 0; index < arraySize - 1; index++)
		{
			/* Check 3.1: current array element + 1 = next array element */
			if ((array[index] + 1) == (array[index + 1]))
			{
				maxLCS++;

				if (maxLCS > *sizeofLCS)
				{
					*sizeofLCS = maxLCS;
				}
			}
			/* Check 3.2: current array element + 1 != next array element */
			else
			{
				maxLCS = 1;
			}
		}

		/* Check 3.3: No LCS is found */
		if (*sizeofLCS == 1)
		{
			errorState = LCS_INT8_NO_LCS;
		}
	}

	return errorState;
}

/**************************************************************************************************************************/