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
/* Declaration and Initialization */

/* Global variable to store NumberOfBTNTicks */
static u8 Glb_u8NumberOfBTNTicks = 0;

/*******************************************************************************************************************************************************************/ 
/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize the application.
*/
vd APP_vdInitialization    ( void )
{
	/* HAL Initialization */
	LED_vdInitialization();
	
	/* MCAL Initialization */
	GLI_vdEnableGIE();
	EXI_u8INTSetCallBack( EXI_U8_INT0, &APP_vdChangeLEDsSequence );
	EXI_u8EnablePIE( EXI_U8_INT0, EXI_U8_SENSE_FALLING_EDGE );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
vd APP_vdStartProgram      ( void )
{	
	u8 Loc_Au8LEDsSequence[8] = { APP_U8_PRESS_0_SEQ, APP_U8_PRESS_1_SEQ, APP_U8_PRESS_2_SEQ, APP_U8_PRESS_3_SEQ, APP_U8_PRESS_4_SEQ, APP_U8_PRESS_5_SEQ, APP_U8_PRESS_6_SEQ, APP_U8_PRESS_7_SEQ };
	
	/* Toggle forever */
	while (1)
	{
		LED_u8SetLEDPort( Loc_Au8LEDsSequence[Glb_u8NumberOfBTNTicks], LED_U8_ON );					
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdChangeLEDsSequence
 Input: void
 Output: void
 Description: Function to change LEDs sequence using EXI peripheral.
*/
vd APP_vdChangeLEDsSequence( void )
{
	/* Increment NumberOfBTNTicks */
	Glb_u8NumberOfBTNTicks++;
	
	/* Check: NumberOfBTNTicks reaches 8 */
	if ( Glb_u8NumberOfBTNTicks == 8 )
	{
		/* Reset NumberOfBTNTicks */
		Glb_u8NumberOfBTNTicks = 0;
	}
}

/*******************************************************************************************************************************************************************/