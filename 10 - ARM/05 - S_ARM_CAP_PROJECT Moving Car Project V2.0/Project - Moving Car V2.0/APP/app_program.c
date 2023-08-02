/*
 * app_program.c
 *
 *   Created on: Jun 25, 2023
 *       Author: Bits 0101 Tribe - 
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_interface.h"
#include "app_config.h"

/*******************************************************************************************************************************************************************/
/* APP Global Variables */

/* Global Array to store DCM configurations */
DCM_ST_CONFIG ast_g_DCMs[2] =
{
	{ APP_DCM_R_DIR_CW_PORT, APP_DCM_R_DIR_CW_PIN, APP_DCM_R_DIR_CCW_PORT, APP_DCM_R_DIR_CCW_PIN },
	{ APP_DCM_L_DIR_CW_PORT, APP_DCM_L_DIR_CW_PIN, APP_DCM_L_DIR_CCW_PORT, APP_DCM_L_DIR_CCW_PIN }
};

/* Global variable to store appMode */
static uint8 u8_gs_appMode = APP_CAR_STOP;

/* Global variable to store diagonalFlag */
static uint8 u8_gs_diagonalFlag = APP_LONG_DGNL;

/*******************************************************************************************************************************************************************/
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void )
{	
	/* HAL Initialization */
	LED_init( APP_MOVE_FWD_LD_LED_PORT, APP_MOVE_FWD_LD_LED_PIN );
	LED_init( APP_MOVE_FWD_SD_LED_PORT, APP_MOVE_FWD_SD_LED_PIN );	
	LED_init( APP_STOP_LED_PORT, APP_STOP_LED_PIN );
	LED_init( APP_ROTATE_LED_PORT, APP_ROTATE_LED_PIN );
	
	INT_init( APP_STOP_BTN_PORT, APP_STOP_BTN_PIN, ENU_FALLING, &APP_stopCar );
	INT_init( APP_START_BTN_PORT, APP_START_BTN_PIN, ENU_FALLING, &APP_startCar );
	
	DCM_initialization( ast_g_DCMs );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Start the basic flow of the Application. 
*/
void APP_startProgram( void )
{	
	/* Toggle forever */
  while (1)
	{
		/* Check 1: Required appMode is "CAR_STOP" mode */
 		if ( u8_gs_appMode == APP_CAR_STOP )
		{
			/* Step A1: Turn on "STOP" LED, and turn off other LEDs */
			LED_digitalWrite( APP_MOVE_FWD_LD_LED_PORT, APP_MOVE_FWD_LD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_MOVE_FWD_SD_LED_PORT, APP_MOVE_FWD_SD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_STOP_LED_PORT, APP_STOP_LED_PIN, ENU_PIN_HIGH );
			LED_digitalWrite( APP_ROTATE_LED_PORT, APP_ROTATE_LED_PIN, ENU_PIN_LOW );	
						
			/* Step A2: Stop both motors */
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_STOP );
		}		
		/* Check 2: Required appMode is "CAR_START" mode */
		else if ( u8_gs_appMode == APP_CAR_START )
		{
			/* Step B1: Delay 1 sec. */
			delay_ms( TIMER1_ID, APP_STARTING_DELAY );
			
			/* Check 2.1: appMode is not "CAR_STOP" mode */
			if ( u8_gs_appMode != APP_CAR_STOP )
			{
				/* Step B2: Update appMode to "CAR_MOVE_FWD_LD" mode */
				u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
			}
		}
		/* Check 3: Required appMode is "CAR_MOVE_FWD_LD" mode */
		else if ( u8_gs_appMode == APP_CAR_MOVE_FWD_LD )	
		{
			/* Step C1: Update diagonalFlag to "LONG_DGNL" */
			u8_gs_diagonalFlag = APP_LONG_DGNL;
			
			/* Step C2: Turn on "MOVE_FWD_LD" LED, and turn off other LEDs */
			LED_digitalWrite( APP_MOVE_FWD_LD_LED_PORT, APP_MOVE_FWD_LD_LED_PIN, ENU_PIN_HIGH );
			LED_digitalWrite( APP_MOVE_FWD_SD_LED_PORT, APP_MOVE_FWD_SD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_STOP_LED_PORT, APP_STOP_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_ROTATE_LED_PORT, APP_ROTATE_LED_PIN, ENU_PIN_LOW );		
			
			/* Step C3: Car moves for 3 sec. with 50% of speed */
			DCM_controlDCMSpeed( APP_FWD_LD_SPEED );
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_ROTATE_CW );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_ROTATE_CW );			
      delay_ms( TIMER1_ID, APP_FWD_LD_DURATION );
						
			/* Step C4: Stop both motors */
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_STOP );

			/* Check 3.1: appMode is not "CAR_STOP" mode */
			if ( u8_gs_appMode != APP_CAR_STOP )
			{
				/* Step C5: Update appMode to "CAR_ROT_90_DEG" mode */
				u8_gs_appMode = APP_CAR_ROT_90_DEG;
			}
		}		
		/* Check 4: Required appMode is "CAR_ROT_90_DEG" mode */
		else if ( u8_gs_appMode == APP_CAR_ROT_90_DEG )		
		{
			/* Step D1: Turn on "ROTATE" LED, and turn off other LEDs */
			LED_digitalWrite( APP_MOVE_FWD_LD_LED_PORT, APP_MOVE_FWD_LD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_MOVE_FWD_SD_LED_PORT, APP_MOVE_FWD_SD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_STOP_LED_PORT, APP_STOP_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_ROTATE_LED_PORT, APP_ROTATE_LED_PIN, ENU_PIN_HIGH );
			
      /* Step D2: Delay 0.5 sec. */
			delay_ms( TIMER1_ID, APP_ROTATION_DELAY );
			
			/* Step D3: Car rotates for 620 msec. with 50% of speed */
			DCM_controlDCMSpeed( 50 );
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_ROTATE_CW );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_ROTATE_CCW );
      delay_ms( TIMER1_ID, APP_ROTATION_DURATION );
						
			/* Step D4: Stop both motors */
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_STOP );			
			
      /* Step D5: Delay 0.5 sec. */
			delay_ms( TIMER1_ID, APP_ROTATION_DELAY );

			/* Check 4.1: appMode is not "CAR_STOP" mode */
      if ( u8_gs_appMode != APP_CAR_STOP )
			{
				/* Step D6: Update appMode to "CAR_MOVE_FWD_SD" or "CAR_MOVE_FWD_LD" modes */
				/* Check 4.1.1: Required diagonalFlag is "SHORT_DGNL" */
				if ( u8_gs_diagonalFlag == APP_SHORT_DGNL )
				{
					u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
				}
				/* Check 4.1.2: Required diagonalFlag is "LONG_DGNL" */
				else if ( u8_gs_diagonalFlag == APP_LONG_DGNL )
				{
					u8_gs_appMode = APP_CAR_MOVE_FWD_SD;
				}
				else
				{
					u8_gs_diagonalFlag = APP_LONG_DGNL; 
					u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
				}
			}
		}
		/* Check 5: Required appMode is "CAR_MOVE_FWD_SD" mode */
		else if ( u8_gs_appMode == APP_CAR_MOVE_FWD_SD )		
		{
			/* Step E1: Update diagonalFlag to "SHORT_DGNL" */
			u8_gs_diagonalFlag = APP_SHORT_DGNL;
			
			/* Step E2: Turn on "MOVE_FWD_SD" LED, and turn off other LEDs */
			LED_digitalWrite( APP_MOVE_FWD_LD_LED_PORT, APP_MOVE_FWD_LD_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_MOVE_FWD_SD_LED_PORT, APP_MOVE_FWD_SD_LED_PIN, ENU_PIN_HIGH );
			LED_digitalWrite( APP_STOP_LED_PORT, APP_STOP_LED_PIN, ENU_PIN_LOW );
			LED_digitalWrite( APP_ROTATE_LED_PORT, APP_ROTATE_LED_PIN, ENU_PIN_LOW );
			
			/* Step E3: Car moves for 2 sec. with 30% of speed */
			DCM_controlDCMSpeed( APP_FWD_SD_SPEED );
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_ROTATE_CW );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_ROTATE_CW );			
      delay_ms( TIMER1_ID, APP_FWD_SD_DURATION );
						
			/* Step E4: Stop both motors */
			DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_STOP );

			/* Check 5.1: appMode is not "CAR_STOP" mode */
      if ( u8_gs_appMode != APP_CAR_STOP )
			{
				/* Step E5: Update appMode to "CAR_ROT_90_DEG" mode */
        u8_gs_appMode = APP_CAR_ROT_90_DEG;
      }
		}		
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_stopCar
 Input: void
 Output: void
 Description: Function to Start the car. 
*/
void APP_startCar( void )
{
	/* Check 1: appMode is not "CAR_STOP" mode */
	if ( u8_gs_appMode != APP_CAR_STOP )
	{
		return;
	}
	/* Check 2: appMode is "CAR_STOP" mode */
	else
	{
		/* Update appMode to "CAR_START" mode */
		u8_gs_diagonalFlag = APP_LONG_DGNL;
		u8_gs_appMode = APP_CAR_START;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_stopCar
 Input: void
 Output: void
 Description: Function to Stop the car. 
*/
void APP_stopCar( void )
{
	/* Step 1: Update appMode to "CAR_STOP" mode */
  u8_gs_appMode = APP_CAR_STOP;
	
	/* Step 2: Stop both motors */
	DCM_controlDCM( &ast_g_DCMs[APP_RIGHT_DCM], DCM_U8_STOP );
	DCM_controlDCM( &ast_g_DCMs[APP_LEFT_DCM], DCM_U8_STOP );
}

/*******************************************************************************************************************************************************************/
