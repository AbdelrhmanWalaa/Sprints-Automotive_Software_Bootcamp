/*
 * dcm_program.c
 *
 *   Created on: Apr 11, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) functions' implementation.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM
 */

/* HAL */
#include "dcm_config.h"
#include "dcm_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_initialization
 Input: Pointer to st DCMConfig
 Output: u8 Error or No Error
 Description: Function to Initialize DCM peripheral.
*/
u8 DCM_initialization ( DCM_ST_CONFIG *pst_a_DCMConfig )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_DCMConfig != NULL )	
	{
		/* Loop: Until the number of configured DCM(s) is initialized */
		for ( u8 u8_l_index = 0; u8_l_index < DCM_U8_NUMBER_OF_DCM; u8_l_index++ )
		{
			/* Step 1: Initialize initial direction of DCM, in both Direction Pins */
			DIO_init( pst_a_DCMConfig[u8_l_index].u8_g_directionCWPort, pst_a_DCMConfig[u8_l_index].u8_g_directionCWPin, OUT );
			DIO_init( pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPort, pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPin, OUT );
		
			/* Step 2: Initialize initial value of DCM, in both Direction Pins */
			DIO_write( pst_a_DCMConfig[u8_l_index].u8_g_directionCWPort, pst_a_DCMConfig[u8_l_index].u8_g_directionCWPin, LOW );
			DIO_write( pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPort, pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPin, LOW );		
		}
		
		/* Step 3: Initialize PWM */
		PWM_initialization( DCM_U8_PWM_PORT, DCM_U8_PWM_PIN, DCM_U8_FREQUENCY );
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		u8_l_errorState = STD_TYPES_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_controlDCM
 Input: Pointer to st DCMConfig and u8 ControlMode
 Output: u8 Error or No Error
 Description: Function Control DCM with one of DCM Modes.
*/
u8 DCM_controlDCM     ( DCM_ST_CONFIG *pst_a_DCMConfig, u8 u8_a_controlMode )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;

	/* Check 1: Pointer is not equal to NULL and ControlMode is in the valid range */
	if ( ( pst_a_DCMConfig != NULL ) && ( u8_a_controlMode <= DCM_U8_ROTATE_CCW ) )
	{
		/* Check 1.1: Required ControlMode */
		switch ( u8_a_controlMode )
		{
			case DCM_U8_STOP:
				DIO_write( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, LOW );
				DIO_write( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, LOW );
			break;
			
			case DCM_U8_ROTATE_CW:
				DIO_write( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, HIGH );
				DIO_write( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, LOW );
			break;
			
			case DCM_U8_ROTATE_CCW:
				DIO_write( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, LOW );
				DIO_write( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, HIGH );
			break;
		}	
	}
	/* Check 2: Pointer is equal to NULL, or ControlMode is not in the valid range */
	else
	{
		/* Update error state = NOK, Pointer is NULL, or wrong ControlMode! */
		u8_l_errorState = STD_TYPES_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_controlDCMSpeed
 Input: u8 SpeedPercentage
 Output: u8 Error or No Error
 Description: Function Control DCM Speed.
*/
u8 DCM_controlDCMSpeed( u8 u8_a_speedPercentage )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;

	/* Check 1: SpeedPercentage are in the valid range */
	if ( u8_a_speedPercentage <= DCM_U8_MAX_SPEED )
	{
		PWM_generatePWM( u8_a_speedPercentage );
	}	
	/* Check 2: SpeedPercentage is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong SpeedPercentage! */
		u8_l_errorState = STD_TYPES_NOK;
	}
		
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/