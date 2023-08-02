/*
 * app_interface.h
 *
 *   Created on: Jun 25, 2023
 *       Author: Bits 0101 Tribe - 
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_
#define APP_INTERFACE_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"

/* HAL */
#include "../HAL/led/led.h"
#include "../HAL/button/button.h"
#include "../HAL/dcm/dcm.h"
#include "../HAL/delay/delay.h"
#include "../HAL/exti/exti.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_CAR_STOP			    0
#define APP_CAR_START			    1
#define APP_CAR_MOVE_FWD_LD		2
#define APP_CAR_ROT_90_DEG		3
#define APP_CAR_MOVE_FWD_SD		4

/* APP Diagonals Values */
#define APP_SHORT_DGNL			  0
#define APP_LONG_DGNL		   	  1

/* APP DCMs Values */
#define APP_RIGHT_DCM				  0
#define APP_LEFT_DCM		   	  1

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
 Description: Function to Start the basic flow of the Application. 
*/
void APP_startProgram( void );

/*
 Name: APP_stopCar
 Input: void
 Output: void
 Description: Function to Start the car. 
*/
void APP_startCar( void );

/*
 Name: APP_stopCar
 Input: void
 Output: void
 Description: Function to Stop the car. 
*/
void APP_stopCar( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_ */
