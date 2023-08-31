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
u8 arr[30]="BCM Operating";
u8 arrx[100] = {0};


/*
 Name: APP_receiveComplete
 Input: void
 Output: void
 Description: Function to be called back when reception is completed.
*/
void APP_receiveComplete( void )
{
	DIO_write( A, P1, HIGH );
}

/*
 Name: APP_transmitComplete
 Input: void
 Output: void
 Description: Function to be called back when transmission is completed.
*/
void APP_transmitComplete( void )
{
	DIO_write( A, P0, HIGH );
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
//	UART_initialization();
	
	BCM_initialization( BCM_EN_PROTOCOL_0 );
	
	BCM_receiveCompleteSetCallback( BCM_EN_PROTOCOL_0, &APP_receiveComplete );
	BCM_transmitCompleteSetCallback( BCM_EN_PROTOCOL_0, &APP_transmitComplete );
				
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
//	u8 data;
		
	/* Toggle forever */
	while (1)
	{
// 		UART_receiveByte( UART_EN_BLOCKING_MODE, &data );
// 		UART_transmitByte( UART_EN_BLOCKING_MODE, data );

		BCM_receiveDispatcher( BCM_EN_PROTOCOL_0 );
		BCM_transmitDispatcher( BCM_EN_PROTOCOL_0 );
	
//		BCM_receiveDispatcher(BCM_EN_PROTOCOL_0);
//		if (arrx[0] != 0)
//		{
//			DIO_write( A, P0, HIGH );
			//BCM_transmitString(BCM_EN_PROTOCOL_0, arrx);
//		}
		//BCM_transmitDispatcher(BCM_EN_PROTOCOL_0);
	}
}

/*******************************************************************************************************************************************************************/