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
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void )
{
	/* HAL Initialization */
	LED_initialization( LED_U8_2 );
	BTN_initialization( BTN_U8_3 );	
	PWM_initialization( PWM_U8_2 );
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
			
			/* Check 1.1: Required State is State 0. */
			if ( u8_l_state == APP_U8_STATE_0 )
			{
				PWM_enable( APP_U16_PWM_TOTAL_PERIOD, PWM_EN_TIME_MS, APP_U8_PWM_30_PERCENT_DUTY_CYCLE );
				
				u8_l_state = APP_U8_STATE_1;
			}
			/* Check 1.2: Required State is State 1. */
			else if ( u8_l_state == APP_U8_STATE_1 )
			{
				PWM_enable( APP_U16_PWM_TOTAL_PERIOD, PWM_EN_TIME_MS, APP_U8_PWM_60_PERCENT_DUTY_CYCLE );
				
				u8_l_state = APP_U8_STATE_2;				
			}
			/* Check 1.3: Required State is State 2. */
			else if ( u8_l_state == APP_U8_STATE_2 )
			{
				PWM_enable( APP_U16_PWM_TOTAL_PERIOD, PWM_EN_TIME_MS, APP_U8_PWM_90_PERCENT_DUTY_CYCLE );
				
				u8_l_state = APP_U8_STATE_3;
			}
			/* Check 1.4: Required State is State 3. */
			else if ( u8_l_state == APP_U8_STATE_3 )
			{
				PWM_disable();
				LED_setLEDPin( LED_U8_2, LED_U8_OFF );
				u8_l_state = APP_U8_STATE_0;
			}
			/* Check 1.5: Required State is Invalid. */
			else
			{
				/* Do Nothing. */
			}
		}
		/* Check 2: BTNValue is High. */
		else
		{
			/* Do Nothing. */
		}
	}
}

/*******************************************************************************************************************************************************************/
