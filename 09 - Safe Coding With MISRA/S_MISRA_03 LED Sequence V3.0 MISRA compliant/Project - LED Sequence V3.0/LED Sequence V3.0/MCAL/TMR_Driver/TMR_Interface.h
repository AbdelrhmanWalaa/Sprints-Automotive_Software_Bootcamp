/*
 * TMR_Interface.h
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *		Copyright: MIT License
 *
 *		           Copyright (c) Abdelrhman Walaa
 *
 *		           Permission is hereby granted, free of charge, to any person obtaining a copy
 *		           of this software and associated documentation files (the "Software"), to deal
 *		           in the Software without restriction, including without limitation the rights
 *		           to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *		           copies of the Software, and to permit persons to whom the Software is
 *		           furnished to do so, subject to the following conditions:
 *
 *		           The above copyright notice and this permission notice shall be included in all
 *		           copies or substantial portions of the Software.
 *
 *		           THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *		           SOFTWARE.
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

/* TMR Counted from 0 to 2 */
#define TMR_U8_TMR0					0
#define TMR_U8_TMR1 				1
#define TMR_U8_TMR2 				2

/*******************************************************************************************************************************************************************/
/* TMR Error States */

typedef enum {
	TMR_EN_NOK = 0, TMR_EN_OK
} TMR_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* TMR Functions' prototypes */

/*
 Name: TMR_vdTMR0Initialization
 Input: void
 Output: void
 Description: Function to Initialize TMR0 peripheral.
*/
extern void TMR_vdTMR0Initialization( void );

/*
 Name: TMR_enEnableTMR
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Enable TMR peripheral.
*/
extern TMR_enErrorState_t TMR_enEnableTMR( u8 Cpy_u8TimerId );

/*
 Name: TMR_enDisableTMR
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Disable TMR peripheral.
*/
extern TMR_enErrorState_t TMR_enDisableTMR( u8 Cpy_u8TimerId );

/*
 Name: TMR_enDelayMS
 Input: u8 TimerId and u32 Delay
 Output: en Error or No Error
 Description: Function to use TMR peripheral as Delay in MS.
*/
extern TMR_enErrorState_t TMR_enDelayMS( u8 Cpy_u8TimerId, u32 Cpy_u32Delay );

/*
 Name: TMR_enGetOVFFlagStatus
 Input: u8 TimerId and Pointer to u8 ReturnedFlagStatus
 Output: en Error or No Error
 Description: Function to Get status of the OVF Flag in TMR peripheral.
*/
extern TMR_enErrorState_t TMR_enGetOVFFlagStatus( u8 Cpy_u8TimerId, u8 *Cpy_pu8FlagStatus );

/*
 Name: TMR_enClearOVFFlag
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Clear the OVF Flag in TMR peripheral.
*/
extern TMR_enErrorState_t TMR_enClearOVFFlag( u8 Cpy_u8TimerId );

/*******************************************************************************************************************************************************************/

#endif /* TMR_INTERFACE_H_ */