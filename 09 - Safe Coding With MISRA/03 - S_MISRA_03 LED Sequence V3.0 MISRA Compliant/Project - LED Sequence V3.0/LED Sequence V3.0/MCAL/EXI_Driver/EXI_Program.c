/*
 * EXI_Program.c
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all External Interrupt (EXI) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *		Copyright: MIT License
 *
 *		           Copyright (c) Abdelrhman Walaa
 *
 *		           Permission is hereby granted, free of charge, to any person obtaining a copy
 *		           of this software and associated documentation files (the "Software"), to deal
 *		           in the Software without restriction, including without limitation the rights
 *		           to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *		           copies of the Software, and to permit persons to whom the Software is
 *		           furnished to do so, subject to the following conditions:
 *
 *		           The above copyright notice and this permission notice shall be included in all
 *		           copies or substantial portions of the Software.
 *
 *		           THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *		           SOFTWARE.
 */
 
/* MCAL */
#include "EXI_Interface.h"
#include "EXI_Private.h"

/*******************************************************************************************************************************************************************/
/* EXI Global Variables */

/* Global Array of 3 Pointers to Functions ( because we have 3 External Interrupts ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *Glb_ApfINTInterrupstAction[3] ) ( void ) = { STD_TYPES_NULL, STD_TYPES_NULL, STD_TYPES_NULL };

/*******************************************************************************************************************************************************************/
/* EXI Static Functions' Prototypes */

static bool EXI_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 );
static bool EXI_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue );
static bool EXI_boolIsNullPointer ( const vd *Cpy_pvdPointer );

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_enEnablePIE
 Input: u8 InterruptId and u8 SenseControl
 Output: en Error or No Error
 Description: Function to enable and configure Peripheral Interrupt Enable (PIE), by setting relevant bit for each interrupt in GICR register,
 	 	 	  then configuring Sense Control in MCUCR (case interrupt 0 or 1) or MCUCSR (case interrupt 2) registers.
*/
EXI_enErrorState_t EXI_enEnablePIE ( u8 Cpy_u8InterruptId, u8 Cpy_u8SenseControl )
{
	/* Define local variable to set the error state = OK */
	EXI_enErrorState_t Loc_enErrorState = EXI_EN_OK;
	
	/* Check 1: InterruptId and the SenseControl are in the valid range */
	if ( ( EXI_boolIsInValidRange( Cpy_u8InterruptId, EXI_U8_INT2 ) )				&&
		 ( EXI_boolIsInValidRange( Cpy_u8SenseControl, EXI_U8_SENSE_RISING_EDGE ) ) )
	{
		/* Check 1.1: Required InterruptId is INT0 */
		if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT0 ) )
		{
			/* Enable Interrupt 0 */
			SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT );
			
			/* Check 1.1.1: Required SenseControl is Low Level */
			if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_LOW_LEVEL ) )
			{
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT );
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT );
			}
			/* Check 1.1.2: Required SenseControl is Logical Change */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_LOGICAL_CHANGE ) )
			{
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT );
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT );
			}
			/* Check 1.1.3: Required SenseControl is Falling Edge */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_FALLING_EDGE ) )
			{
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT );
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT );
			}
			/* Check 1.1.4: Required SenseControl is Rising Edge */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_RISING_EDGE ) )
			{
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT );
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT );
			}
			/* Check 1.1.5: Required SenseControl is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.2: Required InterruptId is INT1 */
		else if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT1 ) )
		{
			/* Enable Interrupt 1 */
			SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT );
			
			/* Check 1.2.1: Required SenseControl is Low Level */
			if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_LOW_LEVEL ) )
			{
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT );
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT );
			}
			/* Check 1.2.2: Required SenseControl is Logical Change */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_LOGICAL_CHANGE ) )
			{
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT );
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT );
			}
			/* Check 1.2.3: Required SenseControl is Falling Edge */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_FALLING_EDGE ) )
			{
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT );
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT );
			}
			/* Check 1.2.4: Required SenseControl is Rising Edge */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_RISING_EDGE ) )
			{
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT );
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT );
			}
			/* Check 1.2.5: Required SenseControl is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.3: Required InterruptId is INT2 */
		else if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT2 ) )
		{
			/* Enable Interrupt 2 */
			SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT );
			
			/* Check 1.3.1: Required SenseControl is Falling Edge */
			if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_FALLING_EDGE ) )
			{
				CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC2_BIT );
			}
			/* Check 1.3.2: Required SenseControl is Rising Edge */
			else if ( EXI_boolAreEqualValues( Cpy_u8SenseControl, EXI_U8_SENSE_RISING_EDGE ) )
			{
				SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC2_BIT );
			}
			/* Check 1.3.3: Required SenseControl is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.4: Required InterruptId is Invalid */
		else
		{
			/* Do Nothing */
		}		
	}
	/* Check 2: InterruptId or the SenseControl is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId or SenseControl! */
		Loc_enErrorState = EXI_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_enDisablePIE
 Input: u8 InterruptId
 Output: en Error or No Error
 Description: Function to disable Peripheral Interrupt Enable (PIE), by clearing relevant bit for each interrupt in GICR register.
*/
EXI_enErrorState_t EXI_enDisablePIE ( u8 Cpy_u8InterruptId )
{
	/* Define local variable to set the error state = OK */
	EXI_enErrorState_t Loc_enErrorState = EXI_EN_OK;
	
	/* Check 1: InterruptId and the SenseControl are in the valid range */
	if ( EXI_boolIsInValidRange( Cpy_u8InterruptId, EXI_U8_INT2 ) )
	{
		/* Check 1.1: Required InterruptId is INT0 */
		if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT0 ) )
		{
			/* Disable Interrupt 0 */
			CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT );
		}
		/* Check 1.2: Required InterruptId is INT1 */
		else if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT1 ) )
		{
			/* Disable Interrupt 1 */
			CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT );
		}
		/* Check 1.3: Required InterruptId is INT1 */
		else if ( EXI_boolAreEqualValues( Cpy_u8InterruptId, EXI_U8_INT2 ) )
		{
			/* Disable Interrupt 2 */
			CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT );
		}
		/* Check 1.4: Required InterruptId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: InterruptId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId! */
		Loc_enErrorState = EXI_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_enINTSetCallBack
 Input: u8 InterruptId and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Interrupt ( InterruptId ),
 	 	 	  the address is passed through a pointer to function ( INTInterruptAction ), and then pass this address to ISR function.
*/
EXI_enErrorState_t EXI_enINTSetCallBack( u8 Cpy_u8InterruptId, void ( *Cpy_pfINTInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	EXI_enErrorState_t Loc_enErrorState = EXI_EN_OK;

	/* Check 1: InterruptId is in the valid range, and Pointer to Function is not equal to NULL */
	if ( ( EXI_boolIsInValidRange( Cpy_u8InterruptId, EXI_U8_INT2 ) )				&&
		 ( EXI_boolIsNullPointer ( Cpy_pfINTInterruptAction ) ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( INTInterruptAction ) into Global Array of Pointers to Functions ( INTInterruptsAction ) in the passed index ( InterruptId ). */
		Glb_ApfINTInterrupstAction[Cpy_u8InterruptId] = Cpy_pfINTInterruptAction;
	}
	/* Check 2: InterruptId is not in the valid range, or Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptId, or Pointer to Function is NULL! */
		Loc_enErrorState = EXI_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: EXI_boolAreEqualValues
 Input: u8 Value1 and u8 Value2
 Output: bool True or False
 Description: Function to check whether the Values passed are equal.
*/
static bool EXI_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 )
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
 Name: EXI_boolIsInValidRange
 Input: u8 Value and u8 MaxValue
 Output: bool True or False
 Description: Function to check whether the Value passed, lies within its valid range.
*/
static bool EXI_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue )
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
 Name: EXI_boolIsNullPointer
 Input: Pointer to vd Pointer
 Output: bool True or False
 Description: Function to check whether the Pointer passed, is a Null Pointer.
*/
static bool EXI_boolIsNullPointer( const vd *Cpy_pvdPointer )
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

/* ISR functions' prototypes of External Interrupt Request 0 ( INT0 ), External Interrupt Request 1 ( INT1 ), and External Interrupt Request 2 ( INT2 ) respectively */
void __vector_1( void )		__attribute__((signal));
void __vector_2( void )		__attribute__((signal));
void __vector_3( void )		__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT0 */
void __vector_1( void )
{
	/* Check: INT0 index of the Global Array is not equal to NULL */
	if ( EXI_boolIsNullPointer( Glb_ApfINTInterrupstAction[EXI_U8_INT0] ) )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT0]();
	}	
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT1 */
void __vector_2( void )
{
	/* Check: INT1 index of the Global Array is not equal to NULL */
	if ( EXI_boolIsNullPointer( Glb_ApfINTInterrupstAction[EXI_U8_INT1] ) )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT1]();
	}	
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of INT2 */
void __vector_3( void )
{
	/* Check: INT2 index of the Global Array is not equal to NULL */
	if ( EXI_boolIsNullPointer( Glb_ApfINTInterrupstAction[EXI_U8_INT2] ) )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		Glb_ApfINTInterrupstAction[EXI_U8_INT2]();
	}	
}

/*******************************************************************************************************************************************************************/