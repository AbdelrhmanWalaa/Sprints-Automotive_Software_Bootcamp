/*
 * TMR_Interface.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* TMR Includes */

/* STD LIB */
#include <math.h>

/* LIB */
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/MCU_Config/MCU_Config.h"

/*******************************************************************************************************************************************************************/
/* TMR Macros */

/* The 3 Timers counted from 0 to 2 */
#define TMR_U8_TMR0							0
#define TMR_U8_TMR1 						1
#define TMR_U8_TMR2 						2

/*******************************************************************************************************************************************************************/
/* TMR Functions' prototypes */

vd TMR_vdTMR0Initialization  ( void );

u8 TMR_u8EnableTMR		     ( u8 Cpy_u8TimerId );
u8 TMR_u8DisableTMR		     ( u8 Cpy_u8TimerId );

u8 TMR_u8DelayMS			 ( u8 Cpy_u8TimerId, u32 Cpy_u32Delay );

u8 TMR_u8GetOVFFlagStatus	 ( u8 Cpy_u8TimerId, u8 *Cpy_pu8FlagStatus );
u8 TMR_u8ClearOVFFlag		 ( u8 Cpy_u8TimerId );

/*******************************************************************************************************************************************************************/

#endif /* TMR_INTERFACE_H_ */