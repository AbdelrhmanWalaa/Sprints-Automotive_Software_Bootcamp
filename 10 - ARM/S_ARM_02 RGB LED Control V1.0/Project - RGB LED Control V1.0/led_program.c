/*
 * led_program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Light Emitting Diode (LED) functions' implementation.
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

/* HAL */
#include "led_interface.h"

/*******************************************************************************************************************************************************************/
/* LED External Variables */

extern GPIO_stPortLinkConfig_t ast_gs_gpioPortsLinkConfig[1];
extern GPIO_stPinLinkConfig_t  ast_gs_gpioPinsLinkConfig[4];

/*******************************************************************************************************************************************************************/
/*
 Name: LED_initialization
 Input: u8 LedId
 Output: en Error or No Error
 Description: Function to initialize LED peripheral, by initializing GPIO peripheral.
 */
LED_enErrorState_t LED_initialization( u8 u8_a_ledId )
{
	/* Define local variable to set the error state = OK. */
	LED_enErrorState_t Loc_enErrorState = LED_EN_OK;
		
	/* Check 1: LEDId is in the valid range. */
	if ( u8_a_ledId <= LED_U8_7 )
	{
		/* Step 1: Initialize Port. */
		GPIO_initalization( ast_gs_gpioPortsLinkConfig, 1 );
		
		/* Step 2: Configure Pin. */
		GPIO_configurePin( &ast_gs_gpioPinsLinkConfig[u8_a_ledId], 1 );
	}
	/* Check 2: LEDId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong LEDPinId! */
		Loc_enErrorState = LED_EN_NOK;
	}
	
	return Loc_enErrorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_setLEDPin
 Input: u8 LedId and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
LED_enErrorState_t LED_setLEDPin( u8 u8_a_ledId, u8 u8_a_operation )
{
	/* Define local variable to set the error state = OK. */
	LED_enErrorState_t Loc_enErrorState = LED_EN_OK;
		
	/* Check 1: LEDId and Operation are in the valid range. */
	if ( ( u8_a_ledId <= LED_U8_7 ) 			      &&
		   ( u8_a_operation <= LED_U8_TOGGLE ) )
	{
		/* Check 1.1: Required Operation. */
		switch ( u8_a_operation )
		{
			case LED_U8_ON    : GPIO_setPinValue   ( ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portBusId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_pinId ); break;
			case LED_U8_OFF   : GPIO_clearPinValue ( ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portBusId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_pinId ); break;
			case LED_U8_TOGGLE: GPIO_togglePinValue( ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_portBusId, ast_gs_gpioPinsLinkConfig[u8_a_ledId].en_a_pinId ); break;
			default:                                                                                                /* Do Nothing. */                                                                             break;
		}
	}
	/* Check 2: LEDId or Operation is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong LEDId, or Operation! */
		Loc_enErrorState = LED_EN_NOK;
	}
		
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
