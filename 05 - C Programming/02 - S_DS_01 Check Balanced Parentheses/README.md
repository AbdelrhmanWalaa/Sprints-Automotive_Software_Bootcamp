# Balanced Parentheses

## Description

The problem of checking if an input string of parentheses is balanced or not is a classic problem in Computer Science. The goal is to determine if a given string contains properly balanced and nested parentheses. This problem can be solved using a stack data structure. A stack is a Last-In-First-Out (LIFO) data structure that allows you to push and pop elements in a certain order.

## Requirements

1. Implement your stack:
    - Maximum stack size is 10.

    - Please use the below typedef
<br> &emsp; typedef struct stack {
<br> &emsp; &emsp; uint8_t elements[STACK_SIZE];
<br> &emsp; &emsp; int8_t top;
<br> &emsp; } ST_stack_t; // Type

    - Implement all the below functions
        1. Implement the createEmptyStack function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to a stacks type
<br> &emsp; &nbsp;* - Initialize this stack with Zeros
<br> &emsp; &nbsp;* - Initialize the top with -1
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - Nothing to return
<br> &emsp; &nbsp;*/
<br> &emsp; void createEmptyStack(ST_stack_t *stack);

        2. Implement the push function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack and data to store
<br> &emsp; &nbsp;* - Stores the data passed into the stack
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -1 if the stack is full
<br> &emsp; &nbsp;* - returns 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t push(ST_stack_t *stack, uint8_t data);

        3. Implement the pop function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack
<br> &emsp; &nbsp;* - Stores the data popped from the stack in a data variable
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -2 if the stack is empty
<br> &emsp; &nbsp;* - returns 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t pop(ST_stack_t *stack, uint8_t *data);

        4. Implement the printStack function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack
<br> &emsp; &nbsp;* - Prints all stack's data starting from the top
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -1 if the stack is full
<br> &emsp; &nbsp;* - returns -2 if the stack is empty
<br> &emsp; &nbsp;* - returns 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t printStack(ST_stack_t *stack);

        5. Implement the getStackTop function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack
<br> &emsp; &nbsp;* - Stores its top data into a variable
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -2 if the stack is empty
<br> &emsp; &nbsp;* - 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t getStackTop(ST_stack_t *stack, uint8_t *topData);

        6. Implement the isFull function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack
<br> &emsp; &nbsp;* - Checks if the stack is full or not
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -1 if the stack is full
<br> &emsp; &nbsp;* - 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t isFull(ST_stack_t *stack);

        7. Implement the isEmpty function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes a reference to the stack
<br> &emsp; &nbsp;* - Checks if the stack is empty or not
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -2 if the stack is empty
<br> &emsp; &nbsp;* - 0 otherwise
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t isEmpty(ST_stack_t *stack);

2. Test your stack
    - Follow the below algorithm to test your stack
      - Create an empty stack
      - Push 5 different characters to the stack
      - Print all stack data
      - Pop one character from the stack
      - Print the stack's top
      - Print all stack data
      - Push another 7 different characters to the stack
      - Print the stack's top
      - Print all stack data
      - Pop 4 characters from the stack
      - Print the stack's top 
      - Print all stack data
      - Pop 7 more times from the stack
      - Print the stack's top 
      - Print all stack data

3. Implement the check functionality
    - Use the stack data structure you implemented and implement an algorithm to check if a mathematical expression has
      balanced parentheses or not.
      
    - Implement the below function
<br> &emsp; /* Description:
<br> &emsp; &nbsp;* - This function takes an expression array max 10 characters
<br> &emsp; &nbsp;* - Checks if the parentheses are balanced or not
<br> &emsp; &nbsp;* - Checks the following parentheses types {, }, (, ) only
<br> &emsp; &nbsp;* Return:
<br> &emsp; &nbsp;* - returns -2 if the neither of paranthethes is used
<br> &emsp; &nbsp;* - returns -1 if the parentheses are not balanced
<br> &emsp; &nbsp;* - returns 0 if the parentheses are balanced
<br> &emsp; &nbsp;*/
<br> &emsp; int8_t isBalancedParanthethes(uint8_t *expression);

4. Test your algorithm
    - Follow the below algorithm to test your algorithm
        - Test Case 1
            - Ask the user for an expression
            - Write this expression {(2+3)}
        - Test Case 2
            - Ask the user for an expression
            - Write this expression {((2+3)}
        - Test Case 3
            - Ask the user for an expression
            - Write this expression [(2+3)]
        - Test Case 4
            - Ask the user for an expression
            - Write this expression {(2+3)/((3+3)*(15-10))}
        - Test Case 5
            - Ask the user for an expression
            - Write this expression (2+3)/((3+3)*(15-10))
        - Test Case 6
            - Ask the user for an expression
            - Write this expression {{2+3)/((3+3)*(15-10)))
        - Test Case 7
            - Ask the user for an expression
            - Write this expression {(2+3(/((3+3)*(15-10))}
        - Test Case 8
            - Ask the user for an expression
            - Write this expression {(2+3)/((3+3(*)15-10))}
        - Test Case 9
            - Ask the user for an expression
            - Write this expression })2+3)/((3+3)*(15-10))}
        - Test Case 10
            - Ask the user for an expression
            - Write this expression {(2+3)/(<3+3>*(15-10))}

## Video
> [Balanced Parentheses](https://drive.google.com/drive/folders/1axx-MDP6cWa-0yTK01rXzJot89ecI3Cq?usp=sharing)
