/*
* app_program.c
*
 *   Created on: Jun 15, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
*  Description: This file contains all Application (APP) functions' implementation.
*/

/* APP */
#include "app_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Global Variables */

static u8 u8_gs_timeoutFlag = APP_U8_FLAG_DOWN;

/*******************************************************************************************************************************************************************/
/* APP External Variables */



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
	DELAY_initialization();
	DELAY_setCallback( &APP_updateTimeoutFlag );
	
	LED_initialization( LED_U8_0 );
	LED_initialization( LED_U8_1 );
	LED_initialization( LED_U8_2 );
	
	BTN_initialization( BTN_U8_3 );	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Run the basic flow of the Application. 
*/
void APP_startProgram( void )
{
	/* Define local variable to set the BTN value = HIGH. */
	u8 u8_l_btnValue = BTN_U8_HIGH;
	/* Define local variable to set the State value = 0. */
	u8 u8_l_state = APP_U8_STATE_0;
	
	/* Superloop */
	while (1)
	{
		/* Step 1: Get the BTN state. */
		BTN_getBTNState( BTN_U8_3, &u8_l_btnValue );
		
		/* Check 1: BTNValue is Low. */
		if ( u8_l_btnValue == BTN_U8_LOW )
		{
			/* Loop: Until BTN is unpressed */
			while( u8_l_btnValue == BTN_U8_LOW )
			{
				BTN_getBTNState( BTN_U8_3, &u8_l_btnValue );
			}
			
			/* Step 2: Update TimeoutFlag to DOWN */
			u8_gs_timeoutFlag = APP_U8_FLAG_DOWN;
			
			/* Check 1.1: Required State is State 0. */
			if ( u8_l_state == APP_U8_STATE_0 )
			{
				/* Turn on Red Led, and turn off Blue and Green Leds. */
				LED_setLEDPin( LED_U8_0, LED_U8_ON );
				LED_setLEDPin( LED_U8_1, LED_U8_OFF );
				LED_setLEDPin( LED_U8_2, LED_U8_OFF );
				
				/* Delay 1 sec. */
				DELAY_setDelayMS( APP_U8_DELAY_1_SEC );
				
				/* Increment State. */
				u8_l_state = APP_U8_STATE_1;
			}
			/* Check 1.2: Required State is State 1. */
			else if ( u8_l_state == APP_U8_STATE_1 )
			{
				/* Turn on Green Led, and turn off Red and Blue Leds. */
				LED_setLEDPin( LED_U8_0, LED_U8_OFF );
				LED_setLEDPin( LED_U8_1, LED_U8_OFF );
				LED_setLEDPin( LED_U8_2, LED_U8_ON );
				
				/* Delay 1 sec. */
				DELAY_setDelayMS( APP_U8_DELAY_1_SEC );
				
				/* Increment State. */
				u8_l_state = APP_U8_STATE_2;
			}
			/* Check 1.3: Required State is State 2. */
			else if ( u8_l_state == APP_U8_STATE_2 )
			{
				/* Turn on Blue Led, and turn off Red and Green Leds. */
				LED_setLEDPin( LED_U8_0, LED_U8_OFF );
				LED_setLEDPin( LED_U8_1, LED_U8_ON );
				LED_setLEDPin( LED_U8_2, LED_U8_OFF );
				
				/* Delay 1 sec. */
				DELAY_setDelayMS( APP_U8_DELAY_1_SEC );
				
				/* Increment State. */
				u8_l_state = APP_U8_STATE_3;
			}
			/* Check 1.4: Required State is State 3. */
			else if ( u8_l_state == APP_U8_STATE_3 )
			{
				/* Turn on all Leds. */
				LED_setLEDPin( LED_U8_0, LED_U8_ON );
				LED_setLEDPin( LED_U8_1, LED_U8_ON );
				LED_setLEDPin( LED_U8_2, LED_U8_ON );
				
				/* Delay 1 sec. */
				DELAY_setDelayMS( APP_U8_DELAY_1_SEC );
				
				/* Increment State. */
				u8_l_state = APP_U8_STATE_4;
			}
			/* Check 1.5: Required State is State 4. */
			else if ( u8_l_state == APP_U8_STATE_4 )
			{
				/* Turn off all Leds. */
				LED_setLEDPin( LED_U8_0, LED_U8_OFF );
				LED_setLEDPin( LED_U8_1, LED_U8_OFF );
				LED_setLEDPin( LED_U8_2, LED_U8_OFF );
				
				/* Reset State. */
				u8_l_state = APP_U8_STATE_0;
			}			
		}
		/* Check 1.6: Required State is Invalid. */
		else
		{
			/* Do Nothing. */
		}
		
		/* Check 2: TimeoutFlag to UP */
		if ( u8_gs_timeoutFlag == APP_U8_FLAG_UP )
		{
			/* Turn off all Leds. */
			LED_setLEDPin( LED_U8_0, LED_U8_OFF );
			LED_setLEDPin( LED_U8_1, LED_U8_OFF );
			LED_setLEDPin( LED_U8_2, LED_U8_OFF );
		}
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_updateTimeoutFlag
 Input: void
 Output: void
 Description: Function to be called when a 1 sec passes. 
*/
void APP_updateTimeoutFlag( void )
{
	/* Step 2: Update TimeoutFlag to UP */
	u8_gs_timeoutFlag = APP_U8_FLAG_UP;
}

/*******************************************************************************************************************************************************************/
