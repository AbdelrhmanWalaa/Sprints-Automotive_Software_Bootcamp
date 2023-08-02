/*
* app_program.c
*
 *   Created on: Jun 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
*  Description: This file contains all Application (APP) functions' implementation.
*/

/* APP */
#include "app_interface.h"

/*******************************************************************************************************************************************************************/
/* APP External Variables */

extern GPIO_stPortLinkConfig_t ast_gs_gpioPortsLinkConfig[1];
extern GPIO_stPinLinkConfig_t  ast_gs_gpioPinsLinkConfig[4];

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
	/* Define local variable to set the counter value = 0. */
	u8 u8_l_counter = 0;
	
	/* Superloop */
	while (1)
	{
		/* Step 1: Get the BTN state. */
		BTN_getBTNState( BTN_U8_3, &u8_l_btnValue );
		
		/* Check 1: BTNValue is Low. */
		if ( u8_l_btnValue == BTN_U8_LOW )
		{
			/* Check 1.1: Required Counter. */
			switch ( u8_l_counter )
			{
				case 0:
				{
					/* Step 2.1: Turn on Red Led, and turn off Blue and Green Leds. */
					LED_setLEDPin( LED_U8_0, LED_U8_ON );
					LED_setLEDPin( LED_U8_1, LED_U8_OFF );
					LED_setLEDPin( LED_U8_2, LED_U8_OFF );
					
					/* Step 2.2: Increment Counter. */
					u8_l_counter++;
					
					break;
				}
				
				case 1:
				{
					/* Step 2.3: Turn on Green Led, and turn off Red and Blue Leds. */
					LED_setLEDPin( LED_U8_0, LED_U8_OFF );
					LED_setLEDPin( LED_U8_1, LED_U8_OFF );
					LED_setLEDPin( LED_U8_2, LED_U8_ON );
					
					/* Step 2.4: Increment Counter. */
					u8_l_counter++;
					
					break;
				}
				
				case 2:
				{
					/* Step 2.5: Turn on Blue Led, and turn off Red and Green Leds. */
					LED_setLEDPin( LED_U8_0, LED_U8_OFF );
					LED_setLEDPin( LED_U8_1, LED_U8_ON );
					LED_setLEDPin( LED_U8_2, LED_U8_OFF );
					
					/* Step 2.6: Increment Counter. */
					u8_l_counter++;
					
					break;
				}
				
				case 3:
				{
					/* Step 2.7: Turn on all Leds. */
					LED_setLEDPin( LED_U8_0, LED_U8_ON );
					LED_setLEDPin( LED_U8_1, LED_U8_ON );
					LED_setLEDPin( LED_U8_2, LED_U8_ON );
					
					/* Step 2.8: Increment Counter. */
					u8_l_counter++;
					
					break;
				}
				
				case 4:
				{
					/* Step 2.9: Turn off all Leds. */
					LED_setLEDPin( LED_U8_0, LED_U8_OFF );
					LED_setLEDPin( LED_U8_1, LED_U8_OFF );
					LED_setLEDPin( LED_U8_2, LED_U8_OFF );
					
					/* Step 2.10: Reset Counter. */
					u8_l_counter = 0;
					
					break;
				}
				
				default:
				{
					/* Do Nothing. */
					break;
				}
			}
			
			/* Step 3: Delay a short period. */
			DELAY_simpleDelay();
		}
	}
}

/*******************************************************************************************************************************************************************/
