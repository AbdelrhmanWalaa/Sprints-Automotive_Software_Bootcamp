/*
 * app_program.c
 *
 *   Created on: Jun 1, 2023
 *       Author: Bits 0101 Tribe - https://github.com/AbdelrhmanWalaa/Small-OS.git
 *  Description: This file contains all Application (APP) functions' implementation.
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

/* APP */
#include "app_interface.h"
#include "app_config.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global variable to store appMode */
static u8 u8_g_startFlag = APP_U8_FLAG_DOWN;

static u8 u8_gs_task1Id;
static u8 u8_gs_task2Id;
 
/*******************************************************************************************************************************************************************/
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void )
{
	/* HAL Initialization */
	BTN_initializationEXIMode( BTN_U8_EXI_0, BTN_U8_EXI_SENSE_FALLING_EDGE, &APP_stopSOS );
	BTN_initializationEXIMode( BTN_U8_EXI_1, BTN_U8_EXI_SENSE_FALLING_EDGE, &APP_startSOS );
	LED_initialization( LED_U8_4 );
	LED_initialization( LED_U8_5 );
		
	/* MWL Initialization */
	SOS_init();
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Start the basic flow of the Application. 
*/
void APP_startProgram  ( void )
{
	/* Create Tasks */
	SOS_create_task( APP_taskToggleLED0, 0, 300, &u8_gs_task1Id );
	SOS_create_task( APP_taskToggleLED1, 5, 500, &u8_gs_task2Id );
	
	/* Loop: Until Start BTN is pressed */
	while ( u8_g_startFlag == APP_U8_FLAG_DOWN );
		
	/* Start OS */
	SOS_run();
	
	/* Unreachable Code */
	while (1);
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startSOS
 Input: void
 Output: void
 Description: Function to Start the Operating System. 
*/
void APP_startSOS      ( void )
{
	u8_g_startFlag = APP_U8_FLAG_UP;
	SOS_updateSOSStatus( SOS_U8_ENABLE_SOS );	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_stopSOS
 Input: void
 Output: void
 Description: Function to Stop the Operating System.
*/
void APP_stopSOS       ( void )
{
	SOS_updateSOSStatus( SOS_U8_DISABLE_SOS );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_taskToggleLED0
 Input: void
 Output: void
 Description: Function to implement task 1 logic.
*/
void APP_taskToggleLED0( void )
{
	LED_setLEDPin( LED_U8_4, LED_U8_TOGGLE );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_taskToggleLED1
 Input: void
 Output: void
 Description: Function to implement task 2 logic.
*/
void APP_taskToggleLED1( void )
{
	LED_setLEDPin( LED_U8_5, LED_U8_TOGGLE );
}

/*******************************************************************************************************************************************************************/