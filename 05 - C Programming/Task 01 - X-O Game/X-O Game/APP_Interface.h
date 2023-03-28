/*
 * APP_Interface.h
 *
 *     Created on: Mar 27, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/**************************************************************************************************************************/
/* APP Includes */

#pragma warning(disable : 4996)

/* STD LIB */
#include <stdio.h>
#include <stdlib.h>

/* LIB */
#include "../X-O Game/STD_TYPES.h"

/**************************************************************************************************************************/
/* APP Functions' prototypes */

void    startProgram   ( void );
void    drawBoard      ( uint8_t *board );
void    updateBoard    ( uint8_t *board, uint8_t position, uint8_t value );
uint8_t getPlayerSymbol( uint8_t playerNumber, uint8_t* symbol );
void    setPlayerConfig( uint8_t *configArray );
void    loadAndUpdate  ( uint8_t playerNumber );
void    getGameState   ( uint8_t *board, uint8_t *gameState );  

/**************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */