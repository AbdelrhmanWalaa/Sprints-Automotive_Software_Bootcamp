/*
 * LED_Program.c
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
#include "LED_Interface.h"

/*******************************************************************************************************************************************************************/
/* LED Static Functions' Prototypes */

static bool LED_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 );
static bool LED_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue );

/*******************************************************************************************************************************************************************/
/*
 Name: LED_enInitialization
 Input: u8 LedId
 Output: en Error or No Error
 Description: Function to initialize LED peripheral, by initializing DIO peripheral.
 */
LED_enErrorState_t LED_enInitialization( u8 Cpy_u8LEDPortId, u8 Cpy_u8LEDPinId )
{
	/* Define local variable to set the error state = OK */
	LED_enErrorState_t Loc_enErrorState = LED_EN_OK;
		
	/* Check 1: LEDPortId and LEDPinId are in the valid range */
	if ( ( LED_boolIsInValidRange( Cpy_u8LEDPortId, LED_U8_PORT_D ) )			&&
		 ( LED_boolIsInValidRange( Cpy_u8LEDPinId, LED_U8_PIN_7 ) ) )
	{
		/* Step 1: Set LED Pin Direction as Output */
		DIO_enSetPinDirection( Cpy_u8LEDPortId, Cpy_u8LEDPinId, DIO_U8_PIN_OUTPUT );
				
		/* Step 2: Set LED Pin Value as Low */
		DIO_enSetPinValue( Cpy_u8LEDPortId, Cpy_u8LEDPinId, DIO_U8_PIN_LOW );
	}
	/* Check 2: LEDPortId or LEDPinId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDPortId or LEDPinId! */
		Loc_enErrorState = LED_EN_NOK;
	}
	
	return Loc_enErrorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_enSetLEDPin
 Input: u8 LEDPortId, u8 LedId, and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LED on, off, or toggle.
*/
LED_enErrorState_t LED_enSetLEDPin( u8 Cpy_u8LEDPortId, u8 Cpy_u8LEDPinId, u8 Cpy_u8Operation )
{
	/* Define local variable to set the error state = OK */
	LED_enErrorState_t Loc_enErrorState = LED_EN_OK;
		
	/* Check 1: LEDPortId, LEDPinId, and Operation are in the valid range */
	if ( ( LED_boolIsInValidRange( Cpy_u8LEDPortId, LED_U8_PORT_D ) )			&&
		 ( LED_boolIsInValidRange( Cpy_u8LEDPinId, LED_U8_PIN_7 ) )				&&
		 ( LED_boolIsInValidRange( Cpy_u8Operation, LED_U8_TOGGLE ) ) )
	{
		/* Check 1.1: Required Operation is On */
		if ( LED_boolAreEqualValues( Cpy_u8Operation, LED_U8_ON ) )
		{
			DIO_enSetPinValue( Cpy_u8LEDPortId, Cpy_u8LEDPinId, DIO_U8_PIN_HIGH );
		}
		/* Check 1.2: Required Operation is Off */
		else if ( LED_boolAreEqualValues( Cpy_u8Operation, LED_U8_OFF ) )
		{
			DIO_enSetPinValue( Cpy_u8LEDPortId, Cpy_u8LEDPinId, DIO_U8_PIN_LOW );
		}
		/* Check 1.3: Required Operation is Toggle */
		else if ( LED_boolAreEqualValues( Cpy_u8Operation, LED_U8_TOGGLE ) )
		{
			DIO_enTogglePinValue( Cpy_u8LEDPortId, Cpy_u8LEDPinId );
		}
		/* Check 1.4: Required Operation is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: LEDPortId, LEDPinId, or Operation is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDPortId, LEDPinId, or Operation! */
		Loc_enErrorState = LED_EN_NOK;
	}
		
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_enSetLEDsPort
 Input: u8 LEDsPortId, u8 LEDsPortValue, and u8 Operation
 Output: en Error or No Error
 Description: Function to switch LEDs on or off.
*/
LED_enErrorState_t LED_enSetLEDsPort( u8 Cpy_u8LEDsPortId, u8 Cpy_u8LEDsPortValue, u8 Cpy_u8Operation )
{
	/* Define local variable to set the error state = OK */
	LED_enErrorState_t Loc_enErrorState = LED_EN_OK;
		
	/* Check 1: LEDsPortId and Operation are in the valid range */
	if ( ( LED_boolIsInValidRange( Cpy_u8LEDsPortId, LED_U8_PORT_D ) )			&& 
		 ( LED_boolIsInValidRange( Cpy_u8Operation, LED_U8_OFF ) ) )
	{
		/* Check 1.1: Required Operation is On */
		if ( LED_boolAreEqualValues( Cpy_u8Operation, LED_U8_ON ) )
		{
			DIO_enSetPortValue( Cpy_u8LEDsPortId, Cpy_u8LEDsPortValue );
		}
		/* Check 1.2: Required Operation is Off */
		else if ( LED_boolAreEqualValues( Cpy_u8Operation, LED_U8_OFF ) )
		{
			DIO_enSetPortValue( Cpy_u8LEDsPortId, 0 );
		}
		/* Check 1.3: Required Operation is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: LEDsPortId or Operation is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong LEDsPortId or Operation! */
		Loc_enErrorState = LED_EN_NOK;
	}
		
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_boolAreEqualValues
 Input: u8 Value1 and u8 Value2
 Output: bool True or False
 Description: Function to check whether the Values passed are equal.
*/
static bool LED_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
		
	/* Check: Values passed are equal */
	if ( Cpy_u8Value1 != Cpy_u8Value2 )
	{
		/* Update error state = FALSE, Different Values! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
		
	return Loc_boolErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: LED_boolIsInValidRange
 Input: u8 Value and u8 MaxValue
 Output: bool True or False
 Description: Function to check whether the Value passed, lies within its valid range.
*/
static bool LED_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
	
	/* Check: Value passed lies within its valid range */
	if ( Cpy_u8Value > Cpy_u8MaxValue )
	{
		/* Update error state = FALSE, Wrong Value! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
	
	return Loc_boolErrorState;
}

/*******************************************************************************************************************************************************************/