/*
 * APP_Program.c
 *
 *     Created on: Mar 27, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "APP_Interface.h"

uint8_t board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
uint8_t configArray[2] = { 0 };

/**************************************************************************************************************************/
/*
 Name: startProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
void    startProgram   ( void )
{
    uint8_t gameState = 2;

    drawBoard( &board[0] );
    setPlayerConfig( &configArray[0] );

    /* Loop: Until any of the player wins, or a match draw takes place */
    while ( gameState == 2 )
    {
        loadAndUpdate( 1 );
        drawBoard( &board[0] );
        getGameState( &board[0], &gameState );
       
        /* Check 1: Player one wins, gameState is updated to 0, after his/her move */
        if ( gameState == 0 )
        {
            printf( "\n\n Player 1 wins" );
            break;
        }

        /* Check 2: No player wins the match, gameState is updated to 1, after his/her move */
        if ( gameState == 1 )
        {
            printf( "\n\n Draw\n Game Over!!" );
            break;
        }

        loadAndUpdate( 2 );
        drawBoard( &board[0] );
        getGameState( &board[0], &gameState );
        
        /* Check 3: Player one wins, gameState is updated to 0, after his/her move */
        if ( gameState == 0 )
        {
            printf( "\n\n Player 2 wins" );
            break;
        }
    }    
}

/**************************************************************************************************************************/
/*
 Name: drawBoard
 Input: Pointer to uint8_t board
 Output: void
 Description: Function to print out X-O board.
*/
void drawBoard( uint8_t* board )
{
    uint8_t counter = 0;

    printf("\n\t\t");

    /* Loop: Until the end of the X-O board to print all cells */
    for (uint8_t cell = 0; cell < 9; cell++ )
    {
        /* Check: Newline encountered */
        if ( counter > 2 )
        {
            printf( "\n\t\t" );
            counter = 0;
        }

        /* Print out the cell and increment the counter */
        printf( "%c ", board[cell] );
        counter++;
    }
}

/**************************************************************************************************************************/
/*
 Name: updateBoard
 Input: Pointer to uint8_t board, uint8_t position, and uint8_t value
 Output: void
 Description: Function to update the X-O board after each player valid selection. 
*/
void updateBoard( uint8_t* board, uint8_t position, uint8_t value )
{
    board[position] = value;
}

/**************************************************************************************************************************/
/*
 Name: getPlayerSymbol
 Input: uint8_t playerNumber, and Pointer to uint8_t symbol
 Output: uint8_t return state
 Description: Function to get the player's preferred symbol before the match. 
*/
uint8_t getPlayerSymbol( uint8_t playerNumber, uint8_t* symbol )
{
    /* Get the player's preferred symbol */
    printf( "\n\n Player %d choose X or O: ", playerNumber ); 
    scanf( " %c", symbol );

    /* Check: Required symbol */
    switch ( *symbol )
    {
        /* Case 1: 'X' smallcase or uppercase */
        case 'X':
        case 'x':
            *symbol = 'X';
            return 0;

        /* Case 2: 'O' smallcase or uppercase */
        case 'O':
        case 'o':
            *symbol = 'O';
            return 0;

        /* Case 3: Any other invalid symbol */
        default:
            return 1;            
    }
}

/**************************************************************************************************************************/
/*
 Name: setPlayerConfig
 Input: Pointer to uint8_t configArray
 Output: void
 Description: Function to set the player's preferred symbol before the match.
*/
void setPlayerConfig( uint8_t* configArray )
{
    /* Loop 1: Until player one enters a valid symbol */
    while ( getPlayerSymbol( 1, &configArray[0] ) )
    {
        printf( " \nWrong Input " );
    }

    /* Loop 2: Until player two enters a valid symbol */
    while ( ( getPlayerSymbol( 2, &configArray[1] ) ) || ( configArray[0] == configArray[1] ) )
    {
        printf( " \nWrong Input " );
    }
}

/**************************************************************************************************************************/
/*
 Name: loadAndUpdate
 Input: uint8_t playerNumber
 Output: void
 Description: Function to get each player move, and checks its validity, and then updates the board with valid one.
*/
void loadAndUpdate( uint8_t playerNumber )
{
    uint32_t cellNumber = 0;

    /* Loop: Until the player enters a valid move, and an empty cell */
    do
    {
        printf( "\n\n Player %d Choose the cell number: ", playerNumber );        
        scanf( "%d", &cellNumber);

    } while ( ( ( cellNumber == 0 ) || ( cellNumber > 9 ) ) || ( board[cellNumber - 1] == 'X' ) || ( board[cellNumber - 1] == 'O' ) );
   
    /* Update the X-O board with the new valid move */
    updateBoard( &board[0], cellNumber - 1, configArray[playerNumber - 1] );
}

/**************************************************************************************************************************/
/*
 Name: getGameState
 Input: Pointer to uint8_t board and Pointer to uint8_t gameState
 Output: void
 Description: Function to get the game state after each player's turn.
*/
void    getGameState( uint8_t* board, uint8_t* gameState )
{
    /* Check 1: Player wins the match */
    if ( ( ( board[0] == board[1] ) && ( board[1] == board[2] ) )     /* 1st Row */
      || ( ( board[3] == board[4] ) && ( board[4] == board[5] ) )     /* 2nd Row */
      || ( ( board[6] == board[7] ) && ( board[7] == board[8] ) )     /* 3rd Row */
      || ( ( board[0] == board[3] ) && ( board[3] == board[6] ) )     /* 1st Col */
      || ( ( board[1] == board[4] ) && ( board[4] == board[7] ) )     /* 2nd Col */
      || ( ( board[2] == board[5] ) && ( board[5] == board[8] ) )     /* 3rd Col */
      || ( ( board[0] == board[4] ) && ( board[4] == board[8] ) )     /* 1st Dgl */
      || ( ( board[2] == board[4] ) && ( board[4] == board[6] ) ) )   /* 2nd Dgl */
    {
        /* Update gameState with 0 for Winning */
        *gameState = 0;
        return;
    }
    /* Check 2: No player wins the match */
    else
    {
        /* Loop: Until the end of board to check each cell */
        for (uint8_t index = 0; index < 9; index++)
        {
            /* Check 3: Game is not yet finished */
            if ( ( board[index] != 'X' ) && ( board[index] != 'O' ) )
            {
                /* Update gameState with 2 for Continuing */
                *gameState = 2;
                return;
            }
        }

        /* Update gameState with 1 for Drawing */
        *gameState = 1;
        return;
    }
}

/**************************************************************************************************************************/