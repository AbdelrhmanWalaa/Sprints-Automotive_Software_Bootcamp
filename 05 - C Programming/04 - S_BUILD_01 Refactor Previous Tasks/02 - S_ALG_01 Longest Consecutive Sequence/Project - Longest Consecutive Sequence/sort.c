/*
 * sort.c
 *
 *     Created on: Apr 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Sort functions' implementation.
 */

 /* Sort */
#include "sort.h"

/**************************************************************************************************************************/
/*
 Name: insertionSort
 Input: Pointer int32 to array, uint8 arraySize
 Output: int8 errorState
 Description: Function to take a reference to an array of integers, sorts the array in ascending order, using the insertion sort algorithm
*/
int8_t insertionSort(int32_t* array, uint8_t arraySize)
{
	int8_t errorState = SORT_INT8_OK;

	/* Check 1: array is empty */
	if (array == NULL)
	{
		errorState = SORT_INT8_EMPTY_ARRAY;
	}
	/* Check 2: arraySize is less than 10 */
	else if (arraySize < 10)
	{
		errorState = SORT_INT8_ARRAY_SIZE_LESS_10;
	}
	/* Check 3: Array can be sorted */
	else
	{	
		int8_t index, index2;
		int32_t current;

		/* Loop: Until the end of the array */
		for (index = 1; index < arraySize; index++) 
		{
			current = array[index];
			index2 = index - 1;

			while ((index2 >= 0) && (current < array[index2]))
			{
				array[index2 + 1] = array[index2];
				index2 = index2 - 1;
			}
			array[index2 + 1] = current;
		}		
	}

	return errorState;
}

/**************************************************************************************************************************/
/*
 Name: printArray
 Input: Pointer int32 to array, uint8 arraySize
 Output: void
 Description: Function to take a reference to an array of integers, and prints all array elements.
*/
void printArray(int32_t* array, uint8_t arraySize)
{
	printf("Sorted Array: ");

	for (uint8_t index = 0; index < arraySize; index++)
	{
		printf("%d ", array[index]);
	}

	printf("\n");
}

/**************************************************************************************************************************/