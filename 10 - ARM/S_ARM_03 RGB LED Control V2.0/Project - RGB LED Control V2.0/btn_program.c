/*
 * btn_program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) functions' implementation.
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
#include "btn_interface.h"

/*******************************************************************************************************************************************************************/
/* BTN External Variables */

extern GPIO_stPortLinkConfig_t ast_g_gpioPortsLinkConfig[1];
extern GPIO_stPinLinkConfig_t  ast_g_gpioPinsLinkConfig[4];

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_initialization
 Input: u8 BTNId
 Output: en Error or No Error
 Description: Function to initialize BTN peripheral, by initializing GPIO peripheral.
*/
BTN_enErrorState_t BTN_initialization( u8 u8_a_btnId )
{
	/* Define local variable to set the error state = OK. */
	BTN_enErrorState_t Loc_enErrorState = BTN_EN_OK;
	
	/* Check 1: BTNId is in the valid range. */
	if ( u8_a_btnId <= BTN_U8_7 )
	{
		/* Step 1: Initialize Port. */
		GPIO_initalization( ast_g_gpioPortsLinkConfig, 1 );
		
		/* Step 2: Configure Pin. */
		GPIO_configurePin( &ast_g_gpioPinsLinkConfig[u8_a_btnId], 1 );
	}
	/* Check 2: BTNId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong BTNPinId! */
		Loc_enErrorState = BTN_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_getBTNState
 Input: u8 BTNId and Pointer to u8 ReturnedBTNState
 Output: en Error or No Error
 Description: Function to get BTN state.
*/
BTN_enErrorState_t BTN_getBTNState( u8 u8_a_btnId, u8 *pu8_a_returnedBTNState )
{
	/* Define local variable to set the error state = OK. */
	BTN_enErrorState_t Loc_enErrorState = BTN_EN_OK;
	
	/* Define local variable to set the BTN value = HIGH. */
	GPIO_enPinValue_t en_l_btnValue = GPIO_EN_PIN_HIGH;
	
	/* Check 1: BTNId is in the valid range, and Pointer is not equal to NULL. */
	if ( ( u8_a_btnId <= BTN_U8_7 )                     &&
		   ( pu8_a_returnedBTNState != STD_TYPES_NULL ) )
	{
		GPIO_getPinValue( ast_g_gpioPinsLinkConfig[u8_a_btnId].en_a_portId, ast_g_gpioPinsLinkConfig[u8_a_btnId].en_a_portBusId, ast_g_gpioPinsLinkConfig[u8_a_btnId].en_a_pinId, &en_l_btnValue );
		
		/* Check 1.1: Required BTNValue. */
		switch ( en_l_btnValue )
		{
			case GPIO_EN_PIN_LOW : *pu8_a_returnedBTNState = BTN_U8_LOW;  break;
			case GPIO_EN_PIN_HIGH: *pu8_a_returnedBTNState = BTN_U8_HIGH; break;
			default:                  /* Do Nothing. */                   break;
		}
	}
	/* Check 2: BTNId is not in the valid range, or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong BTNId, or Pointer is NULL! */
		Loc_enErrorState = BTN_EN_NOK;
	}
		
	return Loc_enErrorState;	
}

/*******************************************************************************************************************************************************************/
