/*
* app_program.c
*
 *   Created on: Jun 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
*  Description: This file contains all Application (APP) functions' implementation.
*/

/* APP */
#include "app_interface.h"

/*******************************************************************************************************************************************************************/
/* APP External Variables */

extern WDT_stLinkConfig_t st_gs_wdtLinkConfig;

/*******************************************************************************************************************************************************************/
/* APP Static Functions' Prototypes */

static void APP_testWDT( void );

/*******************************************************************************************************************************************************************/
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void )
{	
	/* MCAL Initialization */
	st_gs_wdtLinkConfig.vpf_a_interruptAction = &APP_testWDT;
	
	WDT_initalization( &st_gs_wdtLinkConfig );	
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Run the basic flow of the Application. 
*/
void APP_startProgram  ( void )
{
	/* Superloop */
	while (1)
	{
//		WDT_resetTimeoutCounter( en_g_currentWDTId );
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_testWDT
 Input: void
 Output: void
 Description: Function to test WDT peripheral.
*/
static void APP_testWDT( void )
{
	while(1);
}

/*******************************************************************************************************************************************************************/
