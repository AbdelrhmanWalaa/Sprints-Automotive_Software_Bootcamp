/*
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa
 *  Description: The problem of checking if an input string of parentheses is balanced or not is a classic problem in Computer Science. The goal is to determine if a given string contains properly balanced and nested parentheses. This problem can be solved using a stack data structure. A stack is a Last-In-First-Out (LIFO) data structure that allows you to push and pop elements in a certain order.
 */

/* Main */
#include "main.h"

int main(void)
{
    startProgram();

    system("pause");

    return 0;
}

/**************************************************************************************************************************/
/*
 Name: startTestProgram
 Input: void
 Output: void
 Description: Function to test main stack program.
*/
void startTestProgram(void)
{
    int8_t errorState = STACK_INT8_OK;
    uint8_t data = 0;
    
    printf("/**************************************/\n");
    printf("/******** Test Case 1 & 2 & 3 *********/\n");
    printf("/**************************************/\n");
    printf("\n");

    /* Test Case 1: Create an empty stack */
    ST_stack_t newStack;
    createEmptyStack(&newStack);

    /* Test Case 2: Push 5 different characters to the stack */
    for (uint8_t number = 0; number < 5; number++)
    {
        errorState = push(&newStack, number);
    }

    if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is Full!\n");
    }

    /* Test Case 3: Print all stack data */
    errorState = printStack(&newStack);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is FULL!\n");
    }

    printf("\n");
    printf("/**************************************/\n");
    printf("/******** Test Case 4 & 5 & 6 *********/\n");
    printf("/**************************************/\n");
    printf("\n");

    /* Test Case 4: Pop one character from the stack */
    errorState = pop(&newStack, &data);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }

    /* Test Case 5: Print the stack's top */    
    errorState = getStackTop(&newStack, &data);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Stack top = %d\n", data);
    }

    /* Test Case 6: Print all stack data */
    errorState = printStack(&newStack);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is FULL!\n");
    }

    printf("\n");
    printf("/**************************************/\n");
    printf("/******** Test Case 7 & 8 & 9 *********/\n");
    printf("/**************************************/\n");
    printf("\n");

    /* Test Case 7: Push another 7 different characters to the stack */
    for (uint8_t number = 4; number < 10; number++)
    {
        errorState = push(&newStack, number);
    }

    if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is Full!\n");
    }

    /* Test Case 8: Print the stack's top */
    errorState = getStackTop(&newStack, &data);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Stack top = %d\n", data);
    }

    /* Test Case 9: Print all stack data */
    errorState = printStack(&newStack);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is FULL!\n");
    }

    printf("\n");
    printf("/**************************************/\n");
    printf("/******* Test Case 10 & 11 & 12 *******/\n");
    printf("/**************************************/\n");
    printf("\n");

    /* Test Case 10: Pop 4 characters from the stack */
    for (uint8_t index = 0; index < 4; index++)
    {
        errorState = pop(&newStack, &data);
    }

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }

    /* Test Case 11: Print the stack's top */
    errorState = getStackTop(&newStack, &data);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Stack top = %d\n", data);
    }

    /* Test Case 12: Print all stack data */
    errorState = printStack(&newStack);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is FULL!\n");
    }

    printf("\n");
    printf("/**************************************/\n");
    printf("/******* Test Case 13 & 14 & 15 *******/\n");
    printf("/**************************************/\n");
    printf("\n");

    /* Test Case 10: Pop 7 more times from the stack */
    for (uint8_t index = 0; index < 7; index++)
    {
        errorState = pop(&newStack, &data);
    }

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }

    /* Test Case 11: Print the stack's top */
    errorState = getStackTop(&newStack, &data);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Stack top = %d\n", data);
    }

    /* Test Case 12: Print all stack data */
    errorState = printStack(&newStack);

    if (errorState == STACK_INT8_EMPTY_STACK)
    {
        printf("Stack is Empty!\n");
    }
    else if (errorState == STACK_INT8_FULL_STACK)
    {
        printf("Stack is FULL!\n");
    }
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
    int8_t errorState = BLPAR_INT8_BALANCED;

    uint8_t expressions[10][50] = { "{(2+3)}", "{((2+3)}", "[(2+3)]", "{(2+3)/((3+3)*(15-10))}", "(2+3)/((3+3)*(15-10))", "{{2+3)/((3+3)*(15-10)))", "{(2+3(/((3+3)*(15-10))}", "{(2+3)/((3+3(*)15-10))}", "})2+3)/((3+3)*(15-10))}", "{(2+3)/(<3+3>*(15-10))}" };

    /* Loop: Until the end of expressions */
    for (uint8_t index = 0; index < 10; index++)
    {        
        errorState = isBalancedParentheses(&expressions[index]);

        /* Check: Expression is balanced or not */
        (errorState == BLPAR_INT8_BALANCED) ? printf("Expression %d: \"%s\" is balanced!", index + 1, expressions[index]) : printf("Expression %d: \"%s\" is not balanced!", index + 1, expressions[index]);

        printf("\n\n");
    }
}

/**************************************************************************************************************************/