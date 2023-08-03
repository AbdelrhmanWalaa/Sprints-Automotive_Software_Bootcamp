/*
 * main.c
 *
 *   Created on: Jun 1, 2023
 *       Author: Bits 0101 Tribe - https://github.com/AbdelrhmanWalaa/Small-OS.git
 *  Description: Embedded C application that implements a small operating system, where tasks are
 *               periodic and non-preemptive.
 *	  Copyright: MIT License
 *
 *	             Copyright (c) Bits 0101 Tribe
 *
 *	             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	             of this software and associated documentation files (the "Software"), to deal
 *	             in the Software without restriction, including without limitation the rights
 *	             to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	             copies of the Software, and to permit persons to whom the Software is
 *	             furnished to do so, subject to the following conditions:
 *
 *	             The above copyright notice and this permission notice shall be included in all
 *	             copies or substantial portions of the Software.
 *
 *	             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	             FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *               SOFTWARE.
 */

/* Main */
#include "main.h"

// static u8 u8_gs_task1Id;
// static u8 u8_gs_task2Id;

int main(void)
{
// 	GLI_enableGIE();
// 	LED_initialization( LED_U8_0 );
// 	LED_initialization( LED_U8_1 );
// 	
// 	SOS_init();
// 	
// 	/* Create Tasks */
// 	SOS_create_task( APP_taskToggleLED0, 0, 300, &u8_gs_task1Id );
// 	SOS_create_task( APP_taskToggleLED1, 5, 500, &u8_gs_task2Id );
// 		
// 	/* Start OS */
// 	SOS_run();
		
	APP_initialization();
	APP_startProgram();
	
	return 0;
}