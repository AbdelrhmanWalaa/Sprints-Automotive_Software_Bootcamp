# Longest Consecutive Sequence

## Description

The Longest Consecutive Subsequence(LCS) is a subset of the original array where the numbers are in sorted order, from lowest to highest, and are in consecutive, increasing order.

## Requirements

1. Implement the insertion sort	
    - Implement all the below functions:
      1. Implement the insertionSort function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to an array of integers
<br> &emsp; &nbsp;* - Sorts the array in ascending order
<br> &emsp; &nbsp;* - Using the insertion sort algorithm
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -1 if the array is empty
<br> &emsp; &nbsp;* - returns -2 if the array size is 0 or >10
<br> &emsp; &nbsp;* - returns 0 if sorting is done without errors
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t insertionSort(int32_t *array, uint8_t arraySize);

      2. Implement the printArray function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to an array of integers
<br> &emsp; &nbsp;* - Prints all array elements
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - Nothing to return
<br> &emsp; &nbsp;*/
<br> &emsp; void printArray(int32_t *array, uint8_t arraySize);

2. Test your sorting algorithm
    - Follow the below algorithm to test your algorithm
        - Test Case 1
          - Ask the user to enter array elements
          - Enter the following elements
          - [9, 0, 7, 5, 3, 8, -10, 4, 2, 1]
          - Print the array after sorting
        - Test Case 2
          - Ask the user to enter array elements
          - Press Enter without entering any element
          - Print the array after sorting
        - Test Case 3
          - Ask the user to enter array elements
          - Enter the following elements
          - [9, 0, 7, 5, 3, 8, -10, 4, 2, 1, 6, 12]
        - Test Case 4
          - Ask the user to enter array elements
          - Enter the following elements
          - [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
          - Print the array after sorting	Deliver a screenshot and a video of your test

3. Search for the LCS	
    - Implement the lcsGetSize function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to an array,
<br> &emsp; &nbsp;* - array size, and
<br> &emsp; &nbsp;* - reference to store the size of the LCS
<br> &emsp; &nbsp;* - Using the insertion sort algorithm
<br> &emsp; &nbsp;* - The function will search for the LCS in the array and
<br> &emsp; &nbsp;* - stores its size
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -1 if the array is empty
<br> &emsp; &nbsp;* - returns -2 if the array size is 0 or >10
<br> &emsp; &nbsp;* - returns -3 if there is no LCS,
<br> &emsp; &nbsp;* (i.e all array elements are not consecutive at all)
<br> &emsp; &nbsp;* - returns 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t lcsGetSize(int32_t *array, uint8_t arraySize, uint8_t *sizeofLCS);

4. Test your algorithm
    - Follow the below algorithm to test your algorithm
        - Test Case 1
          - Ask the user to enter array elements
          - Enter the following elements
          - [9, 0, 7, 5, 3, 8, -10, 4, 2, 1]
          - Print the LCS size
        - Test Case 2
          - Ask the user to enter array elements
          - Press Enter without entering any element
        - Test Case 3
          - Ask the user to enter array elements
          - Enter the following elements
          - [9, 0, 7, 5, 3, 8, -10, 4, 2, 1, 6, 12]
        - Test Case 4
          - Ask the user to enter array elements
          - Enter the following elements
          - [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
          - Print the LCS size
        - Test Case 5 
          - Ask the user to enter array elements 
          - Enter the following elements 
          - [2, 8, 4, 10, 6, 20, 16, 12, 14, 16]

## Video
> [Longest Consecutive Sequence](https://drive.google.com/drive/folders/15otN92CZCDRFcq8DXSYa48QYMEFrAt7b?usp=sharing)
