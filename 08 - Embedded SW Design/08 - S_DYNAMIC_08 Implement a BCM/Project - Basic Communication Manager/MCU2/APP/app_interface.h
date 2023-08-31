/*
 * app_interface.h
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/std_types/std_types.h"
#include "../LIB/bit_math/bit_math.h"

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/gli/gli_interface.h"
#include "../MCAL/uart/uart_interface.h"

/* HAL */

/* SRVL */
#include "../SRVL/bcm/bcm_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization( void );
void APP_startProgram  ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */