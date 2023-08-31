/*
 * app_program.c
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_interface.h"
#include "app_config.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */
u8 arr[30]="Confirm BCM Operating";
u8 arrx[30] = {0};


void app_sendComplete (void)
{
	DIO_write( A, P0, HIGH );
}

void app_receiveComplete (void)
{
	DIO_write( A, P1, HIGH );
}

 
/*******************************************************************************************************************************************************************/
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization(void)
{
	/* MCAL Initialization */
	DIO_init( A, P0, OUT );
	DIO_init( A, P1, OUT );
	
	GLI_enableGIE();
	
	/* HAL Initialization */
	
	BCM_initialization( BCM_EN_PROTOCOL_0 );
	
	BCM_receiveCompleteSetCallback( BCM_EN_PROTOCOL_0, &app_receiveComplete );
	BCM_transmitCompleteSetCallback( BCM_EN_PROTOCOL_0, &app_sendComplete );
				
	BCM_transmitString( BCM_EN_PROTOCOL_0, arr );
	BCM_receiveString( BCM_EN_PROTOCOL_0, arrx );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Start the basic flow of the Application. 
*/
void APP_startProgram  (void)
{
	/* Toggle forever */
	while (1)
	{
		BCM_receiveDispatcher( BCM_EN_PROTOCOL_0 );
		BCM_transmitDispatcher( BCM_EN_PROTOCOL_0 );
	}
}

/*******************************************************************************************************************************************************************/