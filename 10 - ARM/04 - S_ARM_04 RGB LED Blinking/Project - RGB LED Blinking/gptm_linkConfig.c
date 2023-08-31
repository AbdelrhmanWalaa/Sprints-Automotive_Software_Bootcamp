/*
 * gptm_linkConfig.c
 *
 *     Created on: Jun 20, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Timers (GPTM) linking configurations implementation.
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
#include "gptm_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* GPTM Global Variables */

/* GPTM Linking Configurations Structure Implementation */
GPTM_stTimerLinkConfig_t ast_gs_timersLinkConfig[1] = { { GPTM_EN_TIMER_0,
	                                                        GPTM_EN_PERIODIC_MODE,
	                                                        GPTM_EN_CONCATUNATED,
	                                                        0,
                                                          GPTM_EN_ENABLED_INT,
	                                                        GPTM_EN_TIMER_INT_0_A } };
																							
/*******************************************************************************************************************************************************************/
