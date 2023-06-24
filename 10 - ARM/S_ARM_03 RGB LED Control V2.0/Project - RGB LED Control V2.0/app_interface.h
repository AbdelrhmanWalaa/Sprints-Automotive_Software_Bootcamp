/*
 * app_interface.h
 *
 *   Created on: Jun 15, 2023
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

/* HAL */
#include "delay_interface.h"
#include "led_interface.h"
#include "btn_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP States */
#define APP_U8_STATE_0        0
#define APP_U8_STATE_1        1
#define APP_U8_STATE_2        2
#define APP_U8_STATE_3        3
#define APP_U8_STATE_4        4

/* APP Flag States */
#define APP_U8_FLAG_DOWN      0
#define APP_U8_FLAG_UP        1

/* APP Delay 1 sec. */
#define APP_U8_DELAY_1_SEC    1000

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

/*
 Name: APP_updateTimeoutFlag
 Input: void
 Output: void
 Description: Function to be called when a 1 sec passes. 
*/
void APP_updateTimeoutFlag( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */
