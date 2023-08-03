/*
 * led_program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Light Emitting Diode (LED) functions' implementation.
 */

/* HAL */
#include "led_interface.h"
#include "led_config.h"

/*******************************************************************************************************************************************************************/
/*
 Name: LED_initialization
 Input: u8 LedId
 Output: u8 Error or No Error
 Description: Function to initialize LED peripheral.
*/
u8 LED_initialization( u8 u8_a_ledId )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: LEDId is in the valid range */
	if ( u8_a_ledId <= LED_U8_7 )
	{
		DIO_init  ( LED_U8_PORT, u8_a_ledId, OUT );
		DIO_write ( LED_U8_PORT, u8_a_ledId, LOW );
	}
	/* Check 2: LEDId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
		
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_setLEDPin
 Input: u8 LedId and u8 Operation
 Output: u8 Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
u8 LED_setLEDPin     ( u8 u8_a_ledId, u8 u8_a_operation )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: LEDId and Operation are in the valid range */
	if ( ( u8_a_ledId <= LED_U8_7 ) && ( u8_a_operation <= LED_U8_TOGGLE ) )
	{
		/* Check 1.1: Required Operation */
		switch ( u8_a_operation )
		{
			case LED_U8_ON:
				/* Check 1.1.1: Required LEDId */
				switch ( u8_a_ledId )
				{
					case LED_U8_0: DIO_write( LED_U8_PORT, LED_U8_0_PIN, HIGH ); break;
					case LED_U8_1: DIO_write( LED_U8_PORT, LED_U8_1_PIN, HIGH ); break;
					case LED_U8_2: DIO_write( LED_U8_PORT, LED_U8_2_PIN, HIGH ); break;
					case LED_U8_3: DIO_write( LED_U8_PORT, LED_U8_3_PIN, HIGH ); break;
					case LED_U8_4: DIO_write( LED_U8_PORT, LED_U8_4_PIN, HIGH ); break;
					case LED_U8_5: DIO_write( LED_U8_PORT, LED_U8_5_PIN, HIGH ); break;
					case LED_U8_6: DIO_write( LED_U8_PORT, LED_U8_6_PIN, HIGH ); break;
					case LED_U8_7: DIO_write( LED_U8_PORT, LED_U8_7_PIN, HIGH ); break;
				}				
			break;
			
			case LED_U8_OFF:
				/* Check 1.1.2: Required LEDId */
				switch ( u8_a_ledId )
				{
					case LED_U8_0: DIO_write( LED_U8_PORT, LED_U8_0_PIN, LOW ); break;
					case LED_U8_1: DIO_write( LED_U8_PORT, LED_U8_1_PIN, LOW ); break;
					case LED_U8_2: DIO_write( LED_U8_PORT, LED_U8_2_PIN, LOW ); break;
					case LED_U8_3: DIO_write( LED_U8_PORT, LED_U8_3_PIN, LOW ); break;
					case LED_U8_4: DIO_write( LED_U8_PORT, LED_U8_4_PIN, LOW ); break;
					case LED_U8_5: DIO_write( LED_U8_PORT, LED_U8_5_PIN, LOW ); break;
					case LED_U8_6: DIO_write( LED_U8_PORT, LED_U8_6_PIN, LOW ); break;
					case LED_U8_7: DIO_write( LED_U8_PORT, LED_U8_7_PIN, LOW ); break;
				}				
			break;
			
			case LED_U8_TOGGLE:
				/* Check 1.1.3: Required LEDId */
				switch ( u8_a_ledId )
				{
					case LED_U8_0: DIO_toggle( LED_U8_PORT, LED_U8_0_PIN ); break;
					case LED_U8_1: DIO_toggle( LED_U8_PORT, LED_U8_1_PIN ); break;
					case LED_U8_2: DIO_toggle( LED_U8_PORT, LED_U8_2_PIN ); break;
					case LED_U8_3: DIO_toggle( LED_U8_PORT, LED_U8_3_PIN ); break;
					case LED_U8_4: DIO_toggle( LED_U8_PORT, LED_U8_4_PIN ); break;
					case LED_U8_5: DIO_toggle( LED_U8_PORT, LED_U8_5_PIN ); break;
					case LED_U8_6: DIO_toggle( LED_U8_PORT, LED_U8_6_PIN ); break;
					case LED_U8_7: DIO_toggle( LED_U8_PORT, LED_U8_7_PIN ); break;
				}
			break;
		}
	}
	/* Check 2: LEDId or Operation is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDId or Operation! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
		
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/