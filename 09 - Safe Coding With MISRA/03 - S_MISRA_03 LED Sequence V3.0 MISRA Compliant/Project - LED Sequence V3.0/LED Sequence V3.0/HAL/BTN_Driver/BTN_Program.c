/*
 * BTN_Program.c
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
#include "BTN_Interface.h"

/*******************************************************************************************************************************************************************/
/* BTN Static Functions' Prototypes */

static bool BTN_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 );
static bool BTN_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue );
static bool BTN_boolIsNullPointer ( const vd *Cpy_pvdPointer );

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_enInitializationNMLMode
 Input: u8 BTNPortId and u8 BTNPinId
 Output: en Error or No Error
 Description: Function to initialize BTN pin in NML Mode.
*/
BTN_enErrorState_t BTN_enInitializationNMLMode( u8 Cpy_u8BTNPortId, u8 Cpy_u8BTNPinId )
{
	/* Define local variable to set the error state = OK */
	BTN_enErrorState_t Loc_enErrorState = BTN_EN_OK;
	
	/* Check 1: BTNPortId and BTNPinId are in the valid range */
	if ( ( BTN_boolIsInValidRange( Cpy_u8BTNPortId, BTN_U8_PORT_D ) )			&&
		 ( BTN_boolIsInValidRange( Cpy_u8BTNPinId, BTN_U8_PIN_7 ) ) )
	{
		/* Step 1: Set BTN Pin Direction as Input */
		DIO_enSetPinDirection( Cpy_u8BTNPortId, Cpy_u8BTNPinId, DIO_U8_PIN_INPUT );
		
		/* Step 2: Enable Pull-up Internal Resistor */
		DIO_enSetPinValue( Cpy_u8BTNPortId, Cpy_u8BTNPinId, DIO_U8_PIN_HIGH );
	}
	/* Check 2: BTNPortId or BTNPinId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong BTNPortId or BTNPinId! */
		Loc_enErrorState = BTN_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_enInitializationINTMode
 Input: u8 InterruptId, u8 InterruptSenseControl, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to initialize BTN pin in INT Mode.
*/
BTN_enErrorState_t BTN_enInitializationINTMode( u8 Cpy_u8InterruptId, u8 Cpy_u8InterruptSenseControl, void ( *Cpy_pfInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	BTN_enErrorState_t Loc_enErrorState = BTN_EN_OK;
		
	/* Check 1: InterruptId and InterruptSenseControl are in the valid range, and Pointer to Function is not equal to NULL */
	if ( ( BTN_boolIsInValidRange( Cpy_u8InterruptId, BTN_U8_INT_2 ) )							&&
		 ( BTN_boolIsInValidRange( Cpy_u8InterruptSenseControl, BTN_U8_SENSE_RISING_EDGE ) )	&&
		 ( BTN_boolIsNullPointer ( Cpy_pfInterruptAction ) ) )
	{
		/* Step 1: Enable GLI peripheral */
		GLI_vdEnableGIE();
				
		/* Step 2: Set the Callback Function */
		EXI_enINTSetCallBack( Cpy_u8InterruptId, Cpy_pfInterruptAction );
		
		/* Step 3: Enable EXI peripheral */
		/* Check 1.1: Required InterruptSenseControl is Sense Falling Edge */
		if ( BTN_boolAreEqualValues( Cpy_u8InterruptSenseControl, BTN_U8_SENSE_FALLING_EDGE ) )
		{
			/* Step 3.1: Enable Pull-up Internal Resistor */
			/* Check 1.1.1: Required InterruptId is INT0 */
			if ( BTN_boolAreEqualValues( Cpy_u8InterruptId, BTN_U8_INT_0 ) )
			{
				DIO_enSetPinDirection( DIO_U8_PORTD, DIO_U8_PIN2, DIO_U8_PIN_INPUT );
				DIO_enSetPinValue( DIO_U8_PORTD, DIO_U8_PIN2, DIO_U8_PIN_HIGH );
			}
			/* Check 1.1.2: Required InterruptId is INT1 */
			else if ( BTN_boolAreEqualValues( Cpy_u8InterruptId, BTN_U8_INT_1 ) )
			{
				DIO_enSetPinDirection( DIO_U8_PORTD, DIO_U8_PIN3, DIO_U8_PIN_INPUT );
				DIO_enSetPinValue( DIO_U8_PORTD, DIO_U8_PIN3, DIO_U8_PIN_HIGH );
			}
			/* Check 1.1.3: Required InterruptId is INT2 */
			else if ( BTN_boolAreEqualValues( Cpy_u8InterruptId, BTN_U8_INT_1 ) )
			{
				DIO_enSetPinDirection( DIO_U8_PORTB, DIO_U8_PIN2, DIO_U8_PIN_INPUT );
				DIO_enSetPinValue( DIO_U8_PORTB, DIO_U8_PIN2, DIO_U8_PIN_HIGH );
			}
			/* Check 1.1.4: Required InterruptId is Invalid */
			else
			{
				/* Do Nothing */
			}
			
			/* Step 3.2: Enable EXI peripheral */
			EXI_enEnablePIE( Cpy_u8InterruptId, EXI_U8_SENSE_FALLING_EDGE );
		}
		/* Check 1.2: Required InterruptSenseControl is Sense Rising Edge */
		else if ( BTN_boolAreEqualValues( Cpy_u8InterruptSenseControl, BTN_U8_SENSE_RISING_EDGE ) )
		{
			EXI_enEnablePIE( Cpy_u8InterruptId, EXI_U8_SENSE_RISING_EDGE );
		}
		/* Check 1.2: Required InterruptSenseControl is Invalid */
		else
		{
			/* Do Nothing */
		}		
	}
	/* Check 2: InterruptId or InterruptSenseControl is not in the valid range, or Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptId or InterruptSenseControl, or Pointer to Function is NULL! */
		Loc_enErrorState = BTN_EN_NOK;
	}
			
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_u8GetBTNState
 Input: u8 BTNPortId, u8 BTNPinId and Pointer to u8 ReturnedBTNState
 Output: en Error or No Error
 Description: Function to get BTN state.
*/
BTN_enErrorState_t BTN_enGetBTNState( u8 Cpy_u8BTNPortId, u8 Cpy_u8BTNPinId,  u8 *Cpy_pu8ReturnedBTNState )
{
	/* Define local variable to set the error state = OK */
	BTN_enErrorState_t Loc_enErrorState = BTN_EN_OK;
	
	/* Check 1: BTNPortId and BTNPinId are in the valid range, and Pointer is not equal to NULL */
	if ( ( BTN_boolIsInValidRange( Cpy_u8BTNPortId, BTN_U8_PORT_D ) )		&&
		 ( BTN_boolIsInValidRange( Cpy_u8BTNPinId, BTN_U8_PIN_7 ) )			&&
		 ( BTN_boolIsNullPointer ( Cpy_pu8ReturnedBTNState ) ) )
	{
		DIO_enGetPinValue( Cpy_u8BTNPortId, Cpy_u8BTNPinId, Cpy_pu8ReturnedBTNState );	
	}
	/* Check 2: BTNPortId or BTNPinId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong BTNPortId or BTNPinId, or Pointer is NULL! */
		Loc_enErrorState = BTN_EN_NOK;
	}
		
	return Loc_enErrorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_boolAreEqualValues
 Input: u8 Value1 and u8 Value2
 Output: bool True or False
 Description: Function to check whether the Values passed are equal.
*/
static bool BTN_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 )
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
 Name: BTN_boolIsInValidRange
 Input: u8 Value and u8 MaxValue
 Output: bool True or False
 Description: Function to check whether the Value passed, lies within its valid range.
*/
static bool BTN_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue )
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
/*
 Name: BTN_boolIsNullPointer
 Input: Pointer to vd Pointer
 Output: bool True or False
 Description: Function to check whether the Pointer passed, is a Null Pointer.
*/
static bool BTN_boolIsNullPointer( const vd *Cpy_pvdPointer )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
		
	/* Check: Pointer passed is a Null Pointer */
	if ( Cpy_pvdPointer == STD_TYPES_NULL )
	{
		/* Update error state = FALSE, Null Pointer! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
		
	return Loc_boolErrorState;
}

/*******************************************************************************************************************************************************************/