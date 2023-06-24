/*
 * DIO_Program.c
 *
 *     Created on: Mar 31, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Digital Input Output (DIO) functions' implementation.
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
#include "DIO_Interface.h"
#include "DIO_Config.h"
#include "DIO_Private.h"

/*******************************************************************************************************************************************************************/
/* DIO Static Functions' Prototypes */

static bool DIO_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 );
static bool DIO_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue );
static bool DIO_boolIsNullPointer ( const vd *Cpy_pvdPointer );

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize DIO peripheral.
*/
void DIO_vdInitialization( void )
{
	/* Set Initial Port Direction */
	/* PORTA */
	DIO_U8_DDRA_REG = DIO_FN_CONC( DIO_U8_PA7_INITIAL_DIRECTION, DIO_U8_PA6_INITIAL_DIRECTION, DIO_U8_PA5_INITIAL_DIRECTION, DIO_U8_PA4_INITIAL_DIRECTION, DIO_U8_PA3_INITIAL_DIRECTION, DIO_U8_PA2_INITIAL_DIRECTION, DIO_U8_PA1_INITIAL_DIRECTION, DIO_U8_PA0_INITIAL_DIRECTION );
	/* PORTB */
	DIO_U8_DDRB_REG = DIO_FN_CONC( DIO_U8_PB7_INITIAL_DIRECTION, DIO_U8_PB6_INITIAL_DIRECTION, DIO_U8_PB5_INITIAL_DIRECTION, DIO_U8_PB4_INITIAL_DIRECTION, DIO_U8_PB3_INITIAL_DIRECTION, DIO_U8_PB2_INITIAL_DIRECTION, DIO_U8_PB1_INITIAL_DIRECTION, DIO_U8_PB0_INITIAL_DIRECTION );
	/* PORTC */
	DIO_U8_DDRC_REG = DIO_FN_CONC( DIO_U8_PC7_INITIAL_DIRECTION, DIO_U8_PC6_INITIAL_DIRECTION, DIO_U8_PC5_INITIAL_DIRECTION, DIO_U8_PC4_INITIAL_DIRECTION, DIO_U8_PC3_INITIAL_DIRECTION, DIO_U8_PC2_INITIAL_DIRECTION, DIO_U8_PC1_INITIAL_DIRECTION, DIO_U8_PC0_INITIAL_DIRECTION );
	/* PORTD */
	DIO_U8_DDRD_REG = DIO_FN_CONC( DIO_U8_PD7_INITIAL_DIRECTION, DIO_U8_PD6_INITIAL_DIRECTION, DIO_U8_PD5_INITIAL_DIRECTION, DIO_U8_PD4_INITIAL_DIRECTION, DIO_U8_PD3_INITIAL_DIRECTION, DIO_U8_PD2_INITIAL_DIRECTION, DIO_U8_PD1_INITIAL_DIRECTION, DIO_U8_PD0_INITIAL_DIRECTION );
	
	/* Set Initial Port Value */
	/* PORTA */
	DIO_U8_PORTA_REG = DIO_FN_CONC( DIO_U8_PA7_INITIAL_VALUE, DIO_U8_PA6_INITIAL_VALUE, DIO_U8_PA5_INITIAL_VALUE, DIO_U8_PA4_INITIAL_VALUE, DIO_U8_PA3_INITIAL_VALUE, DIO_U8_PA2_INITIAL_VALUE, DIO_U8_PA1_INITIAL_VALUE, DIO_U8_PA0_INITIAL_VALUE );
	/* PORTB */
	DIO_U8_PORTB_REG = DIO_FN_CONC( DIO_U8_PB7_INITIAL_VALUE, DIO_U8_PB6_INITIAL_VALUE, DIO_U8_PB5_INITIAL_VALUE, DIO_U8_PB4_INITIAL_VALUE, DIO_U8_PB3_INITIAL_VALUE, DIO_U8_PB2_INITIAL_VALUE, DIO_U8_PB1_INITIAL_VALUE, DIO_U8_PB0_INITIAL_VALUE );
	/* PORTC */
	DIO_U8_PORTC_REG = DIO_FN_CONC( DIO_U8_PC7_INITIAL_VALUE, DIO_U8_PC6_INITIAL_VALUE, DIO_U8_PC5_INITIAL_VALUE, DIO_U8_PC4_INITIAL_VALUE, DIO_U8_PC3_INITIAL_VALUE, DIO_U8_PC2_INITIAL_VALUE, DIO_U8_PC1_INITIAL_VALUE, DIO_U8_PC0_INITIAL_VALUE );
	/* PORTD */
	DIO_U8_PORTD_REG = DIO_FN_CONC( DIO_U8_PD7_INITIAL_VALUE, DIO_U8_PD6_INITIAL_VALUE, DIO_U8_PD5_INITIAL_VALUE, DIO_U8_PD4_INITIAL_VALUE, DIO_U8_PD3_INITIAL_VALUE, DIO_U8_PD2_INITIAL_VALUE, DIO_U8_PD1_INITIAL_VALUE, DIO_U8_PD0_INITIAL_VALUE );
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enSetPinDirection
 Input: u8 PortId, u8 PinId, and u8 PinDirection
 Output: en Error or No Error
 Description: Function to set Pin direction.
*/
DIO_enErrorState_t DIO_enSetPinDirection( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 Cpy_u8PinDirection )
{
	/* Define local variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId, PinId, and PinDirection are in the valid range */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&& 
		 ( DIO_boolIsInValidRange( Cpy_u8PinId, DIO_U8_PIN7 ) )					&& 
		 ( DIO_boolIsInValidRange( Cpy_u8PinDirection, DIO_U8_PIN_OUTPUT ) ) )
	{
		/* Check 1.1: Required PinDirection is Input */
		if ( DIO_boolAreEqualValues( Cpy_u8PinDirection, DIO_U8_PIN_INPUT ) )
		{
			/* Check 1.1.1: Required PortId is PortA */
			if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
			{
				CLR_BIT( DIO_U8_DDRA_REG, Cpy_u8PinId );
			}
			/* Check 1.1.2: Required PortId is PortB */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
			{
				CLR_BIT( DIO_U8_DDRB_REG, Cpy_u8PinId );
			}
			/* Check 1.1.3: Required PortId is PortC */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
			{
				CLR_BIT( DIO_U8_DDRC_REG, Cpy_u8PinId );
			}
			/* Check 1.1.4: Required PortId is PortD */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
			{
				CLR_BIT( DIO_U8_DDRD_REG, Cpy_u8PinId );		
			}
			/* Check 1.1.5: Required PortId is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.2: Required PinDirection is Output */
		else if ( DIO_boolAreEqualValues( Cpy_u8PinDirection, DIO_U8_PIN_OUTPUT ) )
		{
			/* Check 1.2.1: Required PortId is PortA */
			if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
			{
				SET_BIT( DIO_U8_DDRA_REG, Cpy_u8PinId );
			}
			/* Check 1.2.2: Required PortId is PortB */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
			{
				SET_BIT( DIO_U8_DDRB_REG, Cpy_u8PinId );
			}
			/* Check 1.2.3: Required PortId is PortC */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
			{
				SET_BIT( DIO_U8_DDRC_REG, Cpy_u8PinId );
			}
			/* Check 1.2.4: Required PortId is PortD */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
			{
				SET_BIT( DIO_U8_DDRD_REG, Cpy_u8PinId );
			}
			/* Check 1.2.5: Required PortId is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.3: Required PinDirection is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId, PinId, or PinDirection is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId, PinId, or PinDirection! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enSetPinValue
 Input: u8 PortId, u8 PinId, and u8 PinValue
 Output: en Error or No Error
 Description: Function to set Pin value.
*/
DIO_enErrorState_t DIO_enSetPinValue ( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 Cpy_u8PinValue )
{
	/* Define local variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId, PinId, and PinValue are in the valid range */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
		 ( DIO_boolIsInValidRange( Cpy_u8PinId, DIO_U8_PIN7 ) )					&&
		 ( DIO_boolIsInValidRange( Cpy_u8PinValue, DIO_U8_PIN_HIGH ) ) )
	{
		/* Check 1.1: Required PinValue is Low */
		if ( DIO_boolAreEqualValues( Cpy_u8PinValue, DIO_U8_PIN_LOW ) )
		{
			/* Check 1.1.1: Required PortId is PortA */
			if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
			{
				CLR_BIT( DIO_U8_PORTA_REG, Cpy_u8PinId );
			}
			/* Check 1.1.2: Required PortId is PortB */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
			{
				CLR_BIT( DIO_U8_PORTB_REG, Cpy_u8PinId );
			}
			/* Check 1.1.3: Required PortId is PortC */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
			{
				CLR_BIT( DIO_U8_PORTC_REG, Cpy_u8PinId );
			}
			/* Check 1.1.4: Required PortId is PortD */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
			{
				CLR_BIT( DIO_U8_PORTD_REG, Cpy_u8PinId );
			}
			/* Check 1.1.5: Required PortId is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.2: Required PinValue is High */
		else if ( DIO_boolAreEqualValues( Cpy_u8PinValue, DIO_U8_PIN_HIGH ) )
		{
			/* Check 1.2.1: Required PortId is PortA */
			if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
			{
				SET_BIT( DIO_U8_PORTA_REG, Cpy_u8PinId );
			}
			/* Check 1.2.2: Required PortId is PortB */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
			{
				SET_BIT( DIO_U8_PORTB_REG, Cpy_u8PinId );
			}
			/* Check 1.2.3: Required PortId is PortC */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
			{
				SET_BIT( DIO_U8_PORTC_REG, Cpy_u8PinId );
			}
			/* Check 1.2.4: Required PortId is PortD */
			else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
			{
				SET_BIT( DIO_U8_PORTD_REG, Cpy_u8PinId );
			}
			/* Check 1.2.5: Required PortId is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.3: Required PinValue is Invalid */
		else
		{
			/* Do Nothing */
		}		
	}
	/* Check 2: PortId, PinId, or PinValue is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId, PinId, or PinValue! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enGetPinValue
 Input: u8 PortId, u8 PinId, and Pointer to u8 ReturnedPinValue
 Output: en Error or No Error
 Description: Function to get Pin value.
*/
DIO_enErrorState_t DIO_enGetPinValue ( u8 Cpy_u8PortId, u8 Cpy_u8PinId, u8 *Cpy_pu8ReturnedPinValue )
{
	/* Define local variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId and PinId are in the valid range, and Pointer is not equal to NULL */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
		 ( DIO_boolIsInValidRange( Cpy_u8PinId, DIO_U8_PIN7 ) )					&&
		 ( DIO_boolIsNullPointer ( Cpy_pu8ReturnedPinValue ) ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			*Cpy_pu8ReturnedPinValue = GET_BIT( DIO_U8_PINA_REG, Cpy_u8PinId );
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			*Cpy_pu8ReturnedPinValue = GET_BIT( DIO_U8_PINB_REG, Cpy_u8PinId );
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			*Cpy_pu8ReturnedPinValue = GET_BIT( DIO_U8_PINC_REG, Cpy_u8PinId );
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			*Cpy_pu8ReturnedPinValue = GET_BIT( DIO_U8_PIND_REG, Cpy_u8PinId );
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId or PinId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong PortId, PinId, or Pointer is NULL! */
		Loc_enErrorState = DIO_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enTogglePinValue
 Input: u8 PortId and u8 PinId
 Output: en Error or No Error
 Description: Function to toggle Pin value.
*/
DIO_enErrorState_t DIO_enTogglePinValue ( u8 Cpy_u8PortId, u8 Cpy_u8PinId )
{
	/* Define local variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId and PinId are in the valid range */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
		 ( DIO_boolIsInValidRange( Cpy_u8PinId, DIO_U8_PIN7 ) ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			TOG_BIT( DIO_U8_PORTA_REG, Cpy_u8PinId );
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			TOG_BIT( DIO_U8_PORTB_REG, Cpy_u8PinId );
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			TOG_BIT( DIO_U8_PORTC_REG, Cpy_u8PinId );
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			TOG_BIT( DIO_U8_PORTD_REG, Cpy_u8PinId );
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId or PinId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId or PinId! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enSetPortDirection
 Input: u8 PortId and u8 PortDirection
 Output: en Error or No Error
 Description: Function to set Port direction.
*/
DIO_enErrorState_t DIO_enSetPortDirection ( u8 Cpy_u8PortId, u8 Cpy_u8PortDirection )
{
	/* Define local variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId and PortDirection are the valid range */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
	   ( ( DIO_boolAreEqualValues( Cpy_u8PortDirection, DIO_U8_PORT_INPUT ) )	|| 
		 ( DIO_boolAreEqualValues( Cpy_u8PortDirection, DIO_U8_PORT_OUTPUT ) ) ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			DIO_U8_DDRA_REG = Cpy_u8PortDirection;
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			DIO_U8_DDRB_REG = Cpy_u8PortDirection;
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			DIO_U8_DDRC_REG = Cpy_u8PortDirection;
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			DIO_U8_DDRD_REG = Cpy_u8PortDirection;
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId or PortDirection is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId or PortDirection! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enSetPortValue
 Input: u8 PortId and u8 PortValue
 Output: en Error or No Error
 Description: Function to set Port value.
*/
DIO_enErrorState_t DIO_enSetPortValue ( u8 Cpy_u8PortId, u8 Cpy_u8PortValue )
{
	/* Define Local Variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId and PortValue are in the valid range */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
	     ( DIO_boolIsInValidRange( Cpy_u8PortValue, DIO_U8_PORT_HIGH ) ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			DIO_U8_PORTA_REG = Cpy_u8PortValue;
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			DIO_U8_PORTB_REG = Cpy_u8PortValue;
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			DIO_U8_PORTC_REG = Cpy_u8PortValue;
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			DIO_U8_PORTD_REG = Cpy_u8PortValue;
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId or PortValue is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId or PortValue! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enGetPortValue
 Input: u8 PortId and Pointer to u8 ReturnedPortValue
 Output: en Error or No Error
 Description: Function to get Port value.
*/
DIO_enErrorState_t DIO_enGetPortValue ( u8 Cpy_u8PortId, u8 *Cpy_pu8ReturnedPortValue )
{
	/* Define Local Variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Check 1: PortId is in the valid range, and Pointer is not equal to NULL */
	if ( ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )				&&
		 ( DIO_boolIsNullPointer ( Cpy_pu8ReturnedPortValue ) ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			*Cpy_pu8ReturnedPortValue = DIO_U8_PINA_REG;
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			*Cpy_pu8ReturnedPortValue = DIO_U8_PINB_REG;
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			*Cpy_pu8ReturnedPortValue = DIO_U8_PINC_REG;
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			*Cpy_pu8ReturnedPortValue = DIO_U8_PIND_REG;
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}		
	}
	/* Check 2: PortId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong PortId, or Pointer is NULL! */
		Loc_enErrorState = DIO_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_enTogglePortValue
 Input: u8 PortId
 Output: en Error or No Error
 Description: Function to toggle Port value.
*/
DIO_enErrorState_t DIO_enTogglePortValue ( u8 Cpy_u8PortId )
{
	/* Define Local Variable to set the error state = OK */
	DIO_enErrorState_t Loc_enErrorState = DIO_EN_OK;
	
	/* Define Local Variable to get Port Value */
	u8 Loc_u8PortValue;

	/* Check 1: PortId is in the valid range */
	if ( DIO_boolIsInValidRange( Cpy_u8PortId, DIO_U8_PORTD ) )
	{
		/* Check 1.1: Required PortId is PortA */
		if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTA ) )
		{
			DIO_enGetPortValue( DIO_U8_PORTA, &Loc_u8PortValue );
			DIO_enSetPortValue( DIO_U8_PORTA, ~Loc_u8PortValue );
		}
		/* Check 1.2: Required PortId is PortB */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTB ) )
		{
			DIO_enGetPortValue( DIO_U8_PORTB, &Loc_u8PortValue );
			DIO_enSetPortValue( DIO_U8_PORTB, ~Loc_u8PortValue );
		}
		/* Check 1.3: Required PortId is PortC */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTC ) )
		{
			DIO_enGetPortValue( DIO_U8_PORTC, &Loc_u8PortValue );
			DIO_enSetPortValue( DIO_U8_PORTC, ~Loc_u8PortValue );
		}
		/* Check 1.4: Required PortId is PortD */
		else if ( DIO_boolAreEqualValues( Cpy_u8PortId, DIO_U8_PORTD ) )
		{
			DIO_enGetPortValue( DIO_U8_PORTD, &Loc_u8PortValue );
			DIO_enSetPortValue( DIO_U8_PORTD, ~Loc_u8PortValue );
		}
		/* Check 1.1.5: Required PortId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: PortId is not in the valid range*/
	else
	{
		/* Update error state = NOK, wrong PortId! */
		Loc_enErrorState = DIO_EN_NOK;
	}
		
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_boolAreEqualValues
 Input: u8 Value1 and u8 Value2
 Output: bool True or False
 Description: Function to check whether the Values passed are equal.
*/
static bool DIO_boolAreEqualValues ( u8 Cpy_u8Value1, u8 Cpy_u8Value2 )
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
 Name: DIO_boolIsInValidRange
 Input: u8 Value and u8 MaxValue
 Output: bool True or False
 Description: Function to check whether the Value passed, lies within its valid range.
*/
static bool DIO_boolIsInValidRange ( u8 Cpy_u8Value, u8 Cpy_u8MaxValue )
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
 Name: DIO_boolIsNullPointer
 Input: Pointer to vd Pointer
 Output: bool True or False
 Description: Function to check whether the Pointer passed, is a Null Pointer.
*/
static bool DIO_boolIsNullPointer ( const vd *Cpy_pvdPointer )
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