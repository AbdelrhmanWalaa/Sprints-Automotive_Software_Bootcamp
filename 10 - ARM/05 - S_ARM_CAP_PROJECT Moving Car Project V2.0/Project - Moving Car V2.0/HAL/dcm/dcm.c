/*
 * dcm.c
 *
 *   Created on: Apr 11, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) functions' implementation.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM
 */

/* HAL */
#include "dcm.h"

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_initialization
 Input: Pointer to st DCMConfig
 Output: en Error or No Error
 Description: Function to Initialize DCM peripheral.
*/
enu_error_state_t DCM_initialization( DCM_ST_CONFIG *pst_a_DCMConfig )
{
	/* Define local variable to set the error state = SUCCESS */
	enu_error_state_t en_l_errorState = SUCCESS;
	
	str_gpio_config_t st_l_configCWDirection;
	str_gpio_config_t st_l_configCCWDirection;

	/* Check 1: Pointer is not equal to NULL */
	if ( pst_a_DCMConfig != NULL_PTR )	
	{
		/* Loop: Until the number of configured DCM(s) is initialized */
		for ( uint8 u8_l_index = 0; u8_l_index < DCM_U8_NUMBER_OF_DCM; u8_l_index++ )
		{
			/* Step 1: Initialize DCM, in both Directions Pins */			
			st_l_configCWDirection.enu_gpio_current_level 		= ENU_PIN_CUR_8MA;
			st_l_configCWDirection.enu_gpio_internal_attach 	= ENU_PIN_PUR;
			st_l_configCWDirection.enu_gpio_pin_direction 		= ENU_PIN_OUTPUT;
			st_l_configCWDirection.enu_gpio_pin_id 					  = pst_a_DCMConfig[u8_l_index].u8_g_directionCWPin;
			st_l_configCWDirection.enu_gpio_pin_level 				= ENU_PIN_LOW;
			st_l_configCWDirection.enu_gpio_pin_mode 				  = ENU_DIGITAL_MODE;
			st_l_configCWDirection.enu_gpio_port_id 					= pst_a_DCMConfig[u8_l_index].u8_g_directionCWPort;
			GPIO_init(&st_l_configCWDirection);
			
			st_l_configCCWDirection.enu_gpio_current_level 		= ENU_PIN_CUR_8MA;
			st_l_configCCWDirection.enu_gpio_internal_attach 	= ENU_PIN_PUR;
			st_l_configCCWDirection.enu_gpio_pin_direction 		= ENU_PIN_OUTPUT;
			st_l_configCCWDirection.enu_gpio_pin_id 					= pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPin;
			st_l_configCCWDirection.enu_gpio_pin_level 				= ENU_PIN_LOW;
			st_l_configCCWDirection.enu_gpio_pin_mode 				= ENU_DIGITAL_MODE;
			st_l_configCCWDirection.enu_gpio_port_id 					= pst_a_DCMConfig[u8_l_index].u8_g_directionCCWPort;
			GPIO_init(&st_l_configCCWDirection);
		}
		
		/* Step 2: Initialize PWM */
		PWM_Init( DCM_U8_PWM_PORT, DCM_U8_PWM_PIN, DCM_U8_PWM_TIMER );
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = FAILED, Pointer is NULL! */
		en_l_errorState = FAILED;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_controlDCM
 Input: Pointer to st DCMConfig and u8 ControlMode
 Output: en Error or No Error
 Description: Function Control DCM with one of DCM Modes.
*/
enu_error_state_t DCM_controlDCM( DCM_ST_CONFIG *pst_a_DCMConfig, uint8 u8_a_controlMode )
{
	/* Define local variable to set the error state = SUCCESS */
	enu_error_state_t en_l_errorState = SUCCESS;

	/* Check 1: Pointer is not equal to NULL and ControlMode is in the valid range */
	if ( ( pst_a_DCMConfig != NULL_PTR ) && ( u8_a_controlMode <= DCM_U8_ROTATE_CCW ) )
	{
		/* Check 1.1: Required ControlMode is STOP */
		if ( u8_a_controlMode == DCM_U8_STOP )
		{
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, ENU_PIN_LOW );
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, ENU_PIN_LOW );
		}
		/* Check 1.2: Required ControlMode is ROTATE_CW */
		else if ( u8_a_controlMode == DCM_U8_ROTATE_CW )
		{
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, ENU_PIN_HIGH );
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, ENU_PIN_LOW );				
		}
		/* Check 1.3: Required ControlMode is ROTATE_CCW */
		else if ( u8_a_controlMode == DCM_U8_ROTATE_CCW )
		{
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCWPort, pst_a_DCMConfig->u8_g_directionCWPin, ENU_PIN_LOW );
			GPIO_digitalWrite( pst_a_DCMConfig->u8_g_directionCCWPort, pst_a_DCMConfig->u8_g_directionCCWPin, ENU_PIN_HIGH );		
		}
	}
	/* Check 2: Pointer is equal to NULL, or ControlMode is not in the valid range */
	else
	{
		/* Update error state = FAILED, Pointer is NULL, or Wrong ControlMode! */
		en_l_errorState = FAILED;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: DCM_controlDCMSpeed
 Input: u8 SpeedPercentage
 Output: en Error or No Error
 Description: Function Control DCM Speed.
*/
enu_error_state_t DCM_controlDCMSpeed( uint8 u8_a_speedPercentage )
{
	/* Define local variable to set the error state = SUCCESS */
	enu_error_state_t en_l_errorState = SUCCESS;

	/* Check 1: SpeedPercentage are in the valid range */
	if ( u8_a_speedPercentage <= DCM_U8_MAX_SPEED )
	{
		PWM_start( DCM_U8_PWM_TIMER, DCM_U8_PERIOD, MSEC, u8_a_speedPercentage );
	}	
	/* Check 2: SpeedPercentage is not in the valid range */
	else
	{
		/* Update error state = FAILED, Pointer is NULL! */
		en_l_errorState = FAILED;
	}
		
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
