/*
 * stmr_private.h
 *
 *     Created on: Jun 15, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all System Timer (STMR) registers' locations and description.
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

#ifndef STMR_PRIVATE_H_
#define STMR_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* STMR Registers' Locations */

#define STMR_U32_STCTRL_REG						*( ( volatile  u32 * ) 0xE000E010 ) // SysTick Control and Status Register - page 138
#define STMR_U32_STRELOAD_REG      		*( ( volatile  u32 * ) 0xE000E014 ) // SysTick Reload Value Register       - page 140
#define STMR_U32_STCURRENT_REG     	  *( ( volatile  u32 * ) 0xE000E018 ) // SysTick Current Value Register      - page 141

/*******************************************************************************************************************************************************************/
/* STMR Registers' Description */

/* SysTick Control and Status Register - STCTRL */
/* Bit 16 - COUNT: Count Flag */
/* Value Description:
 * 	 0 	 The SysTick timer has not counted to 0 since the last time
 *       this bit was read.
 * 	 1 	 The SysTick timer has counted to 0 since the last time
 *       this bit was read.
 */
#define STMR_U8_COUNT_BIT         16

/* Bit 2 - CLK_SRC: Clock Source */
/* Value Description:
 * 	 0 	 Precision internal oscillator (PIOSC) divided by 4
 * 	 1 	 System clock
 */
#define STMR_U8_CLK_SRC_BIT       2

/* Bit 1 - INTEN: Interrupt Enable */
/* Value Description:
 * 	 0 	 Interrupt generation is disabled. Software can use the
 *       COUNT bit to determine if the counter has ever reached 0.
 * 	 1 	 An interrupt is generated to the NVIC when SysTick counts
 *       to 0.
 */
#define STMR_U8_INTEN_BIT         1

/* Bit 0 - ENABLE: Enable */
/* Value Description:
 * 	 0 	 The counter is disabled.
 * 	 1 	 Enables SysTick to operate in a multi-shot way. That is, the
 *       counter loads the RELOAD value and begins counting down.
 *       On reaching 0, the COUNT bit is set and an interrupt is
 *       generated if enabled by INTEN. The counter then loads the
 *       RELOAD value again and begins counting.
 */
#define STMR_U8_ENABLE_BIT          0
/* End of STCTRL Register */

/*******************************************************************************************************************************************************************/
/* STMR Private Macros */

/* STMR Register Resolution */
#define STMR_U8_RESOLUTION					24

/* STMR Maximum Reload Value */
#define STMR_U32_MAX_RELOAD_VALUE		16777215UL

/*******************************************************************************************************************************************************************/

#endif /* STMR_PRIVATE_H_ */
