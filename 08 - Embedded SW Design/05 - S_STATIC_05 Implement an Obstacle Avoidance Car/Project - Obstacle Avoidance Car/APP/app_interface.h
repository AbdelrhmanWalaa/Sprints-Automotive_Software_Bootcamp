/*
 * app_interface.h
 *
 *   Created on: May 16, 2023
 *       Author: Bits 0101 Tribe - https://github.com/AbdelrhmanWalaa/Obstacle-Avoidance-Car.git
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
#include "../MCAL/tmr0/tmr0_interface.h"

/* HAL */
#include "../HAL/btn/btn_interface.h"
#include "../HAL/lcd/lcd_interface.h"
#include "../HAL/kpd/kpd_interface.h"
#include "../HAL/dcm/dcm_interface.h"
#include "../HAL/us/us_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization( void );
void APP_startProgram  ( void );
void APP_stopCar	   ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */