/*
 * wdt_linkConfig.c
 *
 *     Created on: Jun 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Watchdog Timer (WDT) linking configurations implementation.
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

/* MCAL */
#include "wdt_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* WDT Global Variables */

/* WDT Linking Configurations Structure Implementation */
WDT_stLinkConfig_t st_gs_wdtLinkConfig = { WDT_EN_ID_0, 					// st_gs_wdtLinkConfig.en_a_id
																					 1000,									// st_gs_wdtLinkConfig.u32_a_timeoutMS
																					 WDT_EN_DISABLE_RST,		// st_gs_wdtLinkConfig.en_a_resetMode
																					 WDT_EN_ENABLE_INT,			// st_gs_wdtLinkConfig.en_a_interruptMode
																					 WDT_EN_NORMAL_INT,			// st_gs_wdtLinkConfig.en_a_interruptType
																					 STD_TYPES_NULL,				// st_gs_wdtLinkConfig.vpf_a_interruptAction
																					 WDT_EN_ENABLE_STALL }; // st_gs_wdtLinkConfig.en_a_stallMode

/*******************************************************************************************************************************************************************/
