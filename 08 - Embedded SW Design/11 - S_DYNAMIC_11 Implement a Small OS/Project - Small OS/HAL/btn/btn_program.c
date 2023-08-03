/*
 * btn_program.c
 *
 *   Created on: May 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Button (BTN) functions' implementation.
 */

/* HAL */
#include "btn_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_initializationNMLMode
 Input: u8 BTNPortId and u8 BTNPinId
 Output: u8 Error or No Error
 Description: Function to initialize BTN pin in NML Mode.
*/
u8 BTN_initializationNMLMode( u8 u8_a_btnPortId, u8 u8_a_btnPinId  )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
		
	/* Check 1: BTNPortId and BTNPinId are in the valid range */
	if ( ( u8_a_btnPortId <= BTN_U8_DIO_PORTD ) && ( u8_a_btnPinId <= BTN_U8_DIO_PIN7 ) )
	{
		/* Step 1: Initialize BTN as input */
		DIO_init( u8_a_btnPortId, u8_a_btnPinId, IN );
		
		/* Step 2: Enable Pull-up internal resistor */
		DIO_write( u8_a_btnPortId, u8_a_btnPinId, HIGH );
	}		
	/* Check 2: BTNPortId or BTNPinId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong BTNPortId or BTNPinId! */
		u8_l_errorState = STD_TYPES_NOK;
	}
		
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_initializationEXIMode
 Input: u8 EXIId, u8 EXISenseControl, and Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to initialize BTN pin in EXI Mode.
*/
u8 BTN_initializationEXIMode( u8 u8_a_EXIId, u8 u8_a_EXISenseControl, void ( *pf_a_EXIAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
		
	/* Check 1: EXIId and EXISenseControl are in the valid range, and Pointer to Function is not equal to NULL */
	if ( ( u8_a_EXIId <= BTN_U8_EXI_2 ) && ( u8_a_EXISenseControl <= BTN_U8_EXI_SENSE_RISING_EDGE ) && ( pf_a_EXIAction != NULL ) )
	{
		/* Step 1: Enable GLI peripheral */
		GLI_enableGIE();
		
		/* Step 2: Set the CallBack Function and Enable the EXI peripheral */
		EXI_intSetCallBack( u8_a_EXIId, pf_a_EXIAction );
		
		/* Check 1.1: Required EXISenseControl */
		switch( u8_a_EXISenseControl )
		{
			case BTN_U8_EXI_SENSE_FALLING_EDGE: EXI_enablePIE( u8_a_EXIId, EXI_U8_SENSE_FALLING_EDGE ); break;
			case BTN_U8_EXI_SENSE_RISING_EDGE : EXI_enablePIE( u8_a_EXIId, EXI_U8_SENSE_RISING_EDGE  ); break;
		}		
	}
	/* Check 2: EXIId or EXISenseControl is not in the valid range, or Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong EXIId or EXISenseControl, or Pointer to Function is NULL! */
		u8_l_errorState = STD_TYPES_NOK;
	}
			
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_getBTNState
 Input: u8 BTNPortId, u8 BTNPinId and Pointer to u8 ReturnedBTNState
 Output: u8 Error or No Error
 Description: Function to get BTN state.
*/
u8 BTN_getBTNState          ( u8 u8_a_btnPortId, u8 u8_a_btnPinId,  u8 *pu8_a_returnedBTNState )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
		
	/* Check 1: BTNPortId and BTNPinId are in the valid range, and Pointer is not equal to NULL */
	if ( ( u8_a_btnPortId <= BTN_U8_DIO_PORTD ) && ( u8_a_btnPinId <= BTN_U8_DIO_PIN7 ) && ( pu8_a_returnedBTNState != NULL ) )
	{
		DIO_read( u8_a_btnPortId, u8_a_btnPinId, pu8_a_returnedBTNState );	
	}
	/* Check 2: BTNPortId or BTNPinId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong BTNPortId or BTNPinId, or Pointer is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}
		
	return Loc_u8ErrorState;
	
}

/*******************************************************************************************************************************************************************/