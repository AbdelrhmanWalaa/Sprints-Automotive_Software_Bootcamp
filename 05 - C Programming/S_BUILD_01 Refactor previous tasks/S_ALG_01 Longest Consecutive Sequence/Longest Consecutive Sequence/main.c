/*
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa
 *  Description: The Longest Consecutive Subsequence(LCS) is a subset of the original array where the numbers are in sorted order, from lowest to highest, and are in consecutive, increasing order.
 */

/* Main */
#include "main.h"

int main(void)
{
    startProgram();

    return 0;
}

/**************************************************************************************************************************/
/*
 Name: startProgram
 Input: void
 Output: void
 Description: Function to start main program.
*/
void startProgram(void)
{
    int8_t errorState = 0;
    uint32_t arraysize = 0, sizeofLCS = 1;
    int32_t array[20] = { 0 };

    /* Step 1: Get array from user */
    printf("Please insert the array size: ");
    scanf("%d", &arraysize);

    printf("Please insert the array:\n");
   
    for (uint8_t index = 0; index < arraysize; index++)
    {
        scanf(" %d", &array[index]);
    }
    
    /* Step 2: Sort array using insertion sort, and get errorState */
    errorState = insertionSort(&array[0], arraysize);

    /* Check 1: Required errorState */
    switch (errorState)
    {
        /* Case 1: errorState = array is empty */
        case SORT_INT8_EMPTY_ARRAY:        printf("Array is empty!\n");          break;
        /* Case 2: errorState = size less than 10 */
        case SORT_INT8_ARRAY_SIZE_LESS_10: printf("Array size is too small!\n"); break;
        /* Case 3: errorState = OK */
        case SORT_INT8_OK:                 printArray(&array[0], arraysize);     break;
    }

    /* Step 3: Get LCS after using insertion sort, and get errorState */
    errorState = lcsGetSize(&array[0], arraysize, &sizeofLCS);

    /* Check 2: Required errorState */
    switch (errorState)
    {
        /* Case 1: errorState = array is empty */
        case LCS_INT8_EMPTY_ARRAY:        printf("Array is empty!\n");                  break;
        /* Case 2: errorState = size less than 10 */
        case LCS_INT8_ARRAY_SIZE_LESS_10: printf("No LCS, Array size is too small!\n"); break;
        /* Case 3: errorState = No LCS */
        case LCS_INT8_NO_LCS:             printf("No LCS is found!\n");                 break;
        /* Case 3: errorState = LCS found */
        case LCS_INT8_FOUND_LCS:          printf("LCS size = %d\n", sizeofLCS );        break;
    }
}

/**************************************************************************************************************************/