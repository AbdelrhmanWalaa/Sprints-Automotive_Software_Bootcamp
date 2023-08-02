/*
 * app_interface.h
 *
 *   Created on: Jun 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "wdt_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void );

/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Run the basic flow of the Application. 
*/
void APP_startProgram( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */
