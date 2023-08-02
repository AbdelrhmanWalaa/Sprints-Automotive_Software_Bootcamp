/*
 * wdt_linkConfig.h
 *
 *     Created on: Jun 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Watchdog Timer (WDT) linking configurations, through which user can configure during using the WDT peripheral.
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

#ifndef WDT_LINKCONFIG_H_
#define WDT_LINKCONFIG_H_

/*******************************************************************************************************************************************************************/
/* WDT Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/*******************************************************************************************************************************************************************/
/* WDT Link Configurations */

/* WDT Ids */
typedef enum
{	
	WDT_EN_ID_0 = 0,
	WDT_EN_ID_1,
	WDT_EN_INVALID_ID

} WDT_enId_t;

/* WDT Reset Modes */
typedef enum
{
	WDT_EN_DISABLE_RST = 0,
	WDT_EN_ENABLE_RST,
	WDT_EN_INVALID_RST_MODE

} WDT_enResetMode_t;

/* WDT Interrupt Modes */
typedef enum
{
	WDT_EN_DISABLE_INT = 0,
	WDT_EN_ENABLE_INT,
	WDT_EN_INVALID_INT_MODE

} WDT_enInterruptMode_t;

/* WDT Interrupt Types */
typedef enum
{
	WDT_EN_DISABLED_INT = 0,
	WDT_EN_NORMAL_INT,
	WDT_EN_NMI_INT,
	WDT_EN_INVALID_INT_TYPE

} WDT_enInterruptType_t;

/* WDT Interrupt Action */
typedef void ( *WDT_vpfInterruptAction_t ) ( void );

/* WDT Stall Modes */
typedef enum
{
	WDT_EN_DISABLE_STALL = 0,
	WDT_EN_ENABLE_STALL,
	WDT_EN_INVALID_STALL_MODE

} WDT_enStallMode_t;

/* WDT Linking Configurations Structure */
typedef struct
{
	WDT_enId_t 							 	en_a_id;
	u32 											u32_a_timeoutMS;
	WDT_enResetMode_t 				en_a_resetMode;
	WDT_enInterruptMode_t 	 	en_a_interruptMode;
  WDT_enInterruptType_t 	 	en_a_interruptType;
	WDT_vpfInterruptAction_t 	vpf_a_interruptAction;
	WDT_enStallMode_t 			 	en_a_stallMode;

} WDT_stLinkConfig_t;

/*******************************************************************************************************************************************************************/
/* WDT External Variables */

extern WDT_stLinkConfig_t st_gs_wdtLinkConfig;

/*******************************************************************************************************************************************************************/

#endif /* WDT_LINKCONFIG_H_ */
