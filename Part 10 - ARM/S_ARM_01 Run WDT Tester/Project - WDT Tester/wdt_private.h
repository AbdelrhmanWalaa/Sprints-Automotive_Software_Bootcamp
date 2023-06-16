/*
 * wdt_private.h
 *
 *     Created on: Jun 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Watchdog Timer (WDT) registers' locations and description.
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

#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* WDT Registers' Locations */

#define WDT_U32_WDTLOAD_REG( WDT_U8_ID )					*( ( volatile  u32 * ) ( 0x40000000 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTVALUE_REG( WDT_U8_ID )					*( ( volatile  u32 * ) ( 0x40000004 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTCTL_REG( WDT_U8_ID )						*( ( volatile  u32 * ) ( 0x40000008 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTICR_REG( WDT_U8_ID )						*( ( volatile  u32 * ) ( 0x4000000C + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTRIS_REG( WDT_U8_ID )						*( ( volatile  u32 * ) ( 0x40000010 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTMIS_REG( WDT_U8_ID )						*( ( volatile  u32 * ) ( 0x40000014 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTTEST_REG( WDT_U8_ID )					*( ( volatile  u32 * ) ( 0x40000418 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTLOCK_REG( WDT_U8_ID )					*( ( volatile  u32 * ) ( 0x40000C00 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )

#define WDT_U32_WDTPERIPHID4_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FD0 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID5_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FD4 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID6_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FD8 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID7_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FDC + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID0_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FE0 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID1_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FE4 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID2_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FE8 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPERIPHID3_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FEC + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )

#define WDT_U32_WDTPCELLID0_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FF0 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPCELLID1_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FF4 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPCELLID2_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FF8 + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )
#define WDT_U32_WDTPCELLID3_REG( WDT_U8_ID )			*( ( volatile  u32 * ) ( 0x40000FFC + ( WDT_U8_ID == 0 ? 0 : 0x1000 ) ) )

#define WDT_U32_RCGCWD_REG												*( ( volatile  u32 * ) 0x400FE600 )

/*******************************************************************************************************************************************************************/
/* WDT Registers' Description */

/* Watchdog Control - WDTCTL */
/* Bit 31 - WRC: Write Complete */
/* Value Description:
 * 	 0 	 A write access to one of the WDT1 registers is in progress.
 * 	 1 	 A write access is not in progress, and WDT1 registers can be 
 *			 read or written.
 *
 * Note: This bit is reserved for WDT0 and has a reset value of 0. 
 */
#define WDT_U8_WRC_BIT		    	31

/* Bit 2 - INTTYPE: Watchdog Interrupt Type */
/* Value Description:
 * 	 0 	 Watchdog interrupt is a standard interrupt.
 * 	 1 	 Watchdog interrupt is a non-maskable interrupt.
 */
#define WDT_U8_INTTYPE_BIT		  2

/* Bit 1 - RESEN: Watchdog Reset Enable */
/* Value Description:
 * 	 0 	 Disabled.
 * 	 1 	 Enable the Watchdog module reset output.
 */
#define WDT_U8_RESEN_BIT		    1

/* Bit 0 - INTEN: Watchdog Interrupt Enable */
/* Value Description:
 * 	 0 	 Interrupt event disabled. Once this bit is set, it can only be
 *			 cleared by a hardware reset or a software reset initiated by
 *			 setting the appropriate bit in the Watchdog Timer Software
 *			 Reset (SRWD) register.
 * 	 1 	 Interrupt event enabled. Once enabled, all writes are ignored.
 *			 Setting this bit enables the Watchdog Timer.
 */
#define WDT_U8_INTEN_BIT		    0
/* End of WDTCTL Register */

/* Watchdog Raw Interrupt Status - WDTRIS */
/* Bit 0 - WDTRIS: Watchdog Raw Interrupt Status */
/* Value Description:
 * 	 0 	 The watchdog has not timed out.
 * 	 1 	 A watchdog time-out event has occurred.
 */
#define WDT_U8_WDTRIS_BIT		    0
/* End of WDTRIS Register */

/* Watchdog Masked Interrupt Status - WDTMIS */
/* Bit 0 - WDTMIS: Watchdog Masked Interrupt Status */
/* Value Description:
 * 	 0 	 The watchdog has not timed out or the watchdog timer interrupt
 *			 is masked.
 * 	 1 	 A watchdog time-out event has been signalled to the interrupt
 * 			 controller.
 */
#define WDT_U8_WDTMIS_BIT		    0
/* End of WDTMIS Register */

/* Watchdog Test - WDTTEST */
/* Bit 8 - STALL: Watchdog Stall Enable */
/* Value Description:
 * 	 0 	 The watchdog timer continues counting if the microcontroller is
 *			 stopped with a debugger.
 * 	 1 	 If the microcontroller is stopped with a debugger, the watchdog
 *			 timer stops counting. Once the microcontroller is restarted, the
 *			 watchdog timer resumes counting.
 */
#define WDT_U8_STALL_BIT		    8
/* End of WDTTEST Register */

/* Watchdog Timer Run Mode Clock Gating Control - RCGCWD */
/* Bit 1 - R1: Watchdog Timer 1 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 Watchdog module 1 is disabled.
 * 	 1 	 Enable and provide a clock toWatchdogmodule 1 in Runmode.
 */
#define WDT_U8_R1_BIT		    		1

/* Bit 0 - R0: Watchdog Timer 0 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 Watchdog module 0 is disabled.
 * 	 1 	 Enable and provide a clock toWatchdogmodule 0 in Runmode.
 */
#define WDT_U8_R0_BIT		    		0
/* End of RCGCWD Register */

/*******************************************************************************************************************************************************************/

#endif /* WDT_PRIVATE_H_ */
