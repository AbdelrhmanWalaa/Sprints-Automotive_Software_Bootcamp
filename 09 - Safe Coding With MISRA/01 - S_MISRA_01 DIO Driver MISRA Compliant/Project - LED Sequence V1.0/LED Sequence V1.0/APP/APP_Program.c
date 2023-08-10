/*
 * APP_Program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "APP_Config.h"
#include "APP_Interface.h"

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
	LED_vdInitialization();
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
vd APP_vdStartProgram  ( void )
{	
	u8 Loc_u8BTNState = APP_U8_BTN_NOT_PRESSED, Loc_u8NumberOfBTNTicks = 0;
	
	u8 Loc_Au8LEDsSequence[8] = { APP_U8_PRESS_0_SEQ, APP_U8_PRESS_1_SEQ, APP_U8_PRESS_2_SEQ, APP_U8_PRESS_3_SEQ, APP_U8_PRESS_4_SEQ, APP_U8_PRESS_5_SEQ, APP_U8_PRESS_6_SEQ, APP_U8_PRESS_7_SEQ };
	
	/* Toggle forever */
	while (1)
	{
		BTN_u8GetBTNState( BTN_U8_3, &Loc_u8BTNState );
		
		/* Check 1: Button is Pressed */
		if ( Loc_u8BTNState == APP_U8_BTN_PRESSED )
		{
			/* Loop: Until button is not Pressed */
			while ( Loc_u8BTNState == APP_U8_BTN_PRESSED )
			{
				BTN_u8GetBTNState( BTN_U8_3, &Loc_u8BTNState );
			}
			
			/* Increment NumberOfBTNTicks */
			Loc_u8NumberOfBTNTicks++;
			
			/* Check 1.1: NumberOfBTNTicks reaches 8 */
			if ( Loc_u8NumberOfBTNTicks == 8 )
			{
				/* Reset NumberOfBTNTicks */
				Loc_u8NumberOfBTNTicks = 0;
			}
		}
		
		LED_u8SetLEDPort( Loc_Au8LEDsSequence[Loc_u8NumberOfBTNTicks], LED_U8_ON );			
	}
}