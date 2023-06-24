/*
 * APP_Program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' implementation.
 *	  Copyright: MIT License
 *
 *	             Copyright (c) Abdelrhman Walaa
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
 *	             SOFTWARE.
 */

/* APP */
#include "APP_Interface.h"
#include "APP_Config.h"

/*******************************************************************************************************************************************************************/
/* APP Global Variables */

/* Global variable to store NumberOfBTNTicks */
static u8 Glb_u8NumberOfBTN0Ticks = 0, Glb_u8NumberOfBTN1Ticks = 0;

/*******************************************************************************************************************************************************************/ 
/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize the application.
*/
vd APP_vdInitialization( void )
{
	/* HAL Initialization */
	LED_enInitialization( LED_U8_PORT_A, LED_U8_PIN_0 );
	LED_enInitialization( LED_U8_PORT_A, LED_U8_PIN_1 );
	LED_enInitialization( LED_U8_PORT_A, LED_U8_PIN_2 );
	LED_enInitialization( LED_U8_PORT_A, LED_U8_PIN_3 );
	
	BTN_enInitializationINTMode( BTN_U8_INT_0, BTN_U8_SENSE_FALLING_EDGE, &APP_vdChangeLEDsSequence );
	BTN_enInitializationINTMode( BTN_U8_INT_1, BTN_U8_SENSE_FALLING_EDGE, &APP_vdChangeBlinkMode );
	
	/* MCAL Initialization */
	TMR_vdTMR0Initialization();
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
vd APP_vdStartProgram( void )
{	
	u8 Loc_Au8LEDsSequence[8] = { APP_U8_PRESS_0_SEQ, APP_U8_PRESS_1_SEQ, APP_U8_PRESS_2_SEQ, APP_U8_PRESS_3_SEQ, APP_U8_PRESS_4_SEQ, APP_U8_PRESS_5_SEQ, APP_U8_PRESS_6_SEQ, APP_U8_PRESS_7_SEQ };
		
	const u16 Loc_Au16OnPeriods[5]  = { 100, 200, 300, 500, 800 };	
	const u16 Loc_Au16OffPeriods[5] = { 900, 800, 700, 500, 200 };	
	
	/* Toggle forever */
	while (1)
	{
		LED_enSetLEDsPort( LED_U8_PORT_A, Loc_Au8LEDsSequence[Glb_u8NumberOfBTN0Ticks], LED_U8_ON );
		/* Delay OnPeriod */
		TMR_enDelayMS( TMR_U8_TMR0, Loc_Au16OnPeriods[Glb_u8NumberOfBTN1Ticks] );
		
		LED_enSetLEDsPort( LED_U8_PORT_A, Loc_Au8LEDsSequence[Glb_u8NumberOfBTN0Ticks], LED_U8_OFF );
		/* Delay OffPeriod */
		TMR_enDelayMS( TMR_U8_TMR0, Loc_Au16OffPeriods[Glb_u8NumberOfBTN1Ticks] );			
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdChangeLEDsSequence
 Input: void
 Output: void
 Description: Function to change LEDs Sequence using EXI peripheral.
*/
vd APP_vdChangeLEDsSequence( void )
{
	/* Increment NumberOfBTNTicks */
	Glb_u8NumberOfBTN0Ticks++;
	
	/* Check: NumberOfBTNTicks reaches 8 */
	if ( Glb_u8NumberOfBTN0Ticks == 8 )
	{
		/* Reset NumberOfBTNTicks */
		Glb_u8NumberOfBTN0Ticks = 0;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdChangeBlinkMode
 Input: void
 Output: void
 Description: Function to change Blink Mode using EXI peripheral.
*/
vd APP_vdChangeBlinkMode( void )
{
	/* Increment NumberOfBTNTicks */
	Glb_u8NumberOfBTN1Ticks++;
	
	/* Check: NumberOfBTNTicks reaches 5 */
	if ( Glb_u8NumberOfBTN1Ticks == 5 )
	{
		/* Reset NumberOfBTNTicks */
		Glb_u8NumberOfBTN1Ticks = 0;
	}
}

/*******************************************************************************************************************************************************************/