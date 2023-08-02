/*
 * wdt_interface.h
 *
 *     Created on: Jun 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Watchdog Timer (WDT) functions' prototypes, link configurations, and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: Tiva™ TM4C123GH6PM - https://www.ti.com/lit/pdf/spms376
 *	    Copyright: MIT License
 *
 *	               Copyright (c) Abdelrhman Walaa
 *
 *	               Permission is hereby granted, free of charge, to any person obtaining a copy
 *	               of this software and associated documentation files (the "Software"), to deal
 *	               in the Software without restriction, including without limitation the rights
 *	               to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	               copies of the Software, and to permit persons to whom the Software is
 *	               furnished to do so, subject to the following conditions:
 *
 *	               The above copyright notice and this permission notice shall be included in all
 *	               copies or substantial portions of the Software.
 *
 *	               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	               IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	               FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	               AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	               LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	               SOFTWARE.
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* WDT Includes */

/* STD LIB */
#include "TM4C123.h"

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "wdt_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* WDT Error States */

typedef enum
{
	WDT_EN_NOK = 0, 
	WDT_EN_OK
	
} WDT_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* WDT Functions' Prototypes */

/*
 Name: WDT_initalization
 Input: Pointer to st LinkConfig
 Output: en Error or No Error
 Description: Function to initialize WDT peripheral using Linking Configurations.
*/
extern WDT_enErrorState_t WDT_initalization( const WDT_stLinkConfig_t *pst_a_linkConfig );

/*
 Name: WDT_resetTimeoutCounter
 Input: en Id
 Output: en Error or No Error
 Description: Function to Reset the Timeout Counter.
*/
extern WDT_enErrorState_t WDT_resetTimeoutCounter( WDT_enId_t en_a_wdtId );

/*
 Name: WDT_getInterruptStatus
 Input: en Id and Pointer to bool ReturnedInterruptStatus
 Output: en Error or No Error
 Description: Function to Get WDT Interrupt Status.
*/
extern WDT_enErrorState_t WDT_getInterruptStatus( WDT_enId_t en_a_wdtId, bool *pbool_a_returnedInterruptStatus );

/*
 Name: WDT_deinitalization
 Input: en Id
 Output: en Error or No Error
 Description: Function to deinitialize WDT using the passed Id.
*/
extern WDT_enErrorState_t WDT_deinitalization( WDT_enId_t en_a_wdtId );

/*******************************************************************************************************************************************************************/

#endif /* WDT_INTERFACE_H_ */
