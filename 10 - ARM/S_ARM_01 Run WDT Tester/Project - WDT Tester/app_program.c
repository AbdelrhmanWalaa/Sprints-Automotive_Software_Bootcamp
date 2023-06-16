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
/* APP Global Variables */

static WDT_st_Link_Config_t st_gs_wdtLinkConfig;

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
	st_gs_wdtLinkConfig.en_a_id 							= WDT_EN_ID_0;
	st_gs_wdtLinkConfig.u32_a_timeoutMS 			= 1000;
	st_gs_wdtLinkConfig.en_a_resetMode 				= WDT_EN_DISABLE_RST;
	st_gs_wdtLinkConfig.en_a_interruptMode 		= WDT_EN_ENABLE_INT;
	st_gs_wdtLinkConfig.en_a_interruptType 		= WDT_EN_NORMAL_INT;
	st_gs_wdtLinkConfig.vpf_a_interruptAction = &APP_testWDT;
	st_gs_wdtLinkConfig.en_a_stallMode 				= WDT_EN_ENABLE_STALL;
	
	/* MCAL Initialization */
	WDT_initalization( &st_gs_wdtLinkConfig );
	
	en_g_currentWDTId = WDT_EN_ID_0;
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
