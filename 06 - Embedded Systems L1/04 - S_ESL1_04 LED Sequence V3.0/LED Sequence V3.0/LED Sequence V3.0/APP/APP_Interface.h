/*
 * APP_Interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../MCAL/GLI_Driver/GLI_Interface.h"
#include "../MCAL/EXI_Driver/EXI_Interface.h"
#include "../MCAL/TMR_Driver/TMR_Interface.h"

/* HAL */
#include "../HAL/LED_Driver/LED_Interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* BTN States */
#define APP_U8_BTN_PRESSED			0
#define APP_U8_BTN_NOT_PRESSED		1

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

vd APP_vdInitialization    ( void );
vd APP_vdStartProgram      ( void );
vd APP_vdChangeLEDsSequence( void );
vd APP_vdChangeBlinkMode   ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */