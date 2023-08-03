/*
* app_program.c
*
*   Created on: May 16, 2023
*       Author: Bits 0101 Tribe - https://github.com/AbdelrhmanWalaa/Obstacle-Avoidance-Car.git
*  Description: This file contains all Application (APP) functions' implementation.
*/

/* APP */
#include "app_config.h"
#include "app_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

DCM_ST_CONFIG ast_g_DCMs[2] =
{
	{ APP_U8_DCM_R_DIR_CW_PORT, APP_U8_DCM_R_DIR_CW_PIN, APP_U8_DCM_R_DIR_CCW_PORT, APP_U8_DCM_R_DIR_CCW_PIN },
	{ APP_U8_DCM_L_DIR_CW_PORT, APP_U8_DCM_L_DIR_CW_PIN, APP_U8_DCM_L_DIR_CCW_PORT, APP_U8_DCM_L_DIR_CCW_PIN }
};
 
/* Global variable to store appMode */
u8 u8_g_select = APP_U8_CAR_ROTATE_RGT;
 
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
	GLI_enableGIE();
	
	/* HAL Initialization */
	BTN_init( C, P4 );
	LCD_init();
	KPD_initialization();
	US_init( B, P3, EN_INT2 );
	DCM_initialization( ast_g_DCMs );
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
	u8 u8_l_keyValue = KPD_U8_KEY_NOT_PRESSED;
	u8 u8_l_btnValue;

	while ( u8_l_keyValue != '1' )
	{
		KPD_getPressedKey( &u8_l_keyValue );
	}
	
	TMR0_timeoutMS( 5000 );
	
	LCD_setCursor( 0, 0 );
	LCD_sendString( ( u8* ) "Set Def. Rot." );
	
	while( !g_timeout_flag )
	{
		LCD_setCursor( 1, 0 );
		
		if ( u8_g_select == APP_U8_CAR_ROTATE_RGT )
		{
			LCD_sendString( ( u8* ) "Right" );
		}
		else
		{
			LCD_sendString( ( u8* ) "Left" );
		}

		BTN_read( C, P4, &u8_l_btnValue );
		
		if ( u8_l_btnValue == LOW )
		{
			u8_g_select = ~u8_g_select;
			
			while ( u8_l_btnValue == LOW )
			{
				BTN_read( C, P4, &u8_l_btnValue );
			}
		}
	}
	
	LCD_clear();

	DCM_controlDCMSpeed( 30 );
	DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
	DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
	
	LCD_setCursor( 0, 0 );
	LCD_sendString( ( u8* ) "Speed:00% Dir:S" );
	
	TMR0_delayMS( 2000 );
	
	u16 u16_l_distance = 0;
	
	u16_l_distance = US_readDistance();
	
	LCD_setCursor( 1, 0 );
	
	LCD_sendString( ( u8* ) "Dist.:     cm");
	LCD_setCursor( 1, 7 );
	LCD_floatToString( u16_l_distance );
	
	/* Toggle forever */
	while (1)
	{
		/************************************************************************************/
		/*****************************First State********************************************/
		/************************************************************************************/
		u16_l_distance = US_readDistance();
		
		LCD_setCursor( 1, 7 );
		LCD_floatToString(u16_l_distance);
			
		if ( u16_l_distance > 70 )
		{
			TMR0_timeoutMS( 5000 );
			
			while( !g_timeout_flag && u16_l_distance > 70 )
			{
				DCM_controlDCMSpeed( 30 );
				DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CW );
				DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CW );
				
				u16_l_distance = US_readDistance();
				
				LCD_setCursor( 0, 6 );
				LCD_sendString( ( u8* ) "30" );
				LCD_setCursor( 0,14 );
				LCD_sendCharacter( 'F' );
				LCD_setCursor( 1, 7 );
				LCD_floatToString( u16_l_distance );
				
				APP_stopCar();
			}
			while( u16_l_distance > 70 )
			{
				DCM_controlDCMSpeed( 50 );
				DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CW );
				DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CW );
				
				u16_l_distance = US_readDistance();
				
				LCD_setCursor( 0, 6 );
				LCD_sendString( ( u8* ) "50" );
				LCD_setCursor( 0, 14 );
				LCD_sendCharacter( 'F' );
				LCD_setCursor( 1, 7 );
				LCD_floatToString( u16_l_distance );
				
				APP_stopCar();
			}
		}
		/************************************************************************************/
		/*****************************Second State*******************************************/
		/************************************************************************************/
		else if ( ( u16_l_distance <= 70 ) && ( u16_l_distance > 30 ) )
		{
			DCM_controlDCMSpeed( 30 );
			DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CW );
			DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CW );
			
			u16_l_distance = US_readDistance();
			
			LCD_setCursor( 0, 6 );
			LCD_sendString( ( u8* ) "30" );
			LCD_setCursor( 0, 14 );
			LCD_sendCharacter( 'F' );
			LCD_setCursor( 1, 7 );
			LCD_floatToString( u16_l_distance );
			
			APP_stopCar();
		}
		/************************************************************************************/
		/*****************************Third State********************************************/
		/************************************************************************************/
		else if ( ( u16_l_distance <= 30 ) && ( u16_l_distance > 20 ) )
		{
			DCM_controlDCMSpeed( 30 );
			DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
			
			u16_l_distance = US_readDistance();
			
			LCD_setCursor( 0,6 );
			LCD_sendString( ( u8* ) "00" );
			LCD_setCursor(0,14);
			LCD_sendCharacter('S');
			
			while( u16_l_distance <= 30 )
			{
				DCM_controlDCMSpeed( 30 );
				DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CCW );
				DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CCW );
				
				u16_l_distance = US_readDistance();
				
				LCD_setCursor( 0, 6 );
				LCD_sendString( ( u8* ) "30" );
				LCD_setCursor( 0, 14 );
				LCD_sendCharacter( 'B' );
				LCD_setCursor( 1 ,7 );
				LCD_floatToString( u16_l_distance );
				APP_stopCar();
			}
			
			if ( u8_g_select == APP_U8_CAR_ROTATE_RGT )
			{
				DCM_controlDCMSpeed( 30 );
				DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CCW );
				DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CW );
				
				LCD_setCursor( 0 ,6 );
				LCD_sendString( ( u8* ) "30" );
				LCD_setCursor( 0, 14 );
				LCD_sendCharacter( 'R' );
			}
			
			else
			{
				DCM_controlDCMSpeed( 30 );
				DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CW );
				DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CCW );
				
				LCD_setCursor( 0, 6 );
				LCD_sendString( ( u8* ) "30" );
				LCD_setCursor( 0, 14 );
				LCD_sendCharacter( 'R' );
			}
			
			TMR0_delayMS( 600 );
			
			u16_l_distance = US_readDistance();
			
			LCD_setCursor( 1, 7 );
			LCD_floatToString( u16_l_distance );
			
			DCM_controlDCMSpeed( 30 );
			DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
			
			LCD_setCursor( 0, 6 );
			LCD_sendString( ( u8* ) "00" );
			LCD_setCursor( 0, 14 );
			LCD_sendCharacter( 'S' );
			APP_stopCar();
		}
		/************************************************************************************/
		/*****************************Forth State********************************************/
		/************************************************************************************/
		else if ( u16_l_distance <= 20 )
		{
			DCM_controlDCMSpeed( 30 );
			DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
			DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
			
			u16_l_distance = US_readDistance();
			
			LCD_setCursor( 0, 6 );
			LCD_sendString( ( u8* ) "00" );
			LCD_setCursor( 0, 14 );
			LCD_sendCharacter( 'S' );
			LCD_setCursor( 1, 7 );
			LCD_floatToString( u16_l_distance );
			
			u8 u8_l_counter = 0;
			
			while ( ( u8_l_counter < 4 ) && ( u16_l_distance <= 20 ) )
			{
				APP_stopCar();
				
				u16_l_distance = US_readDistance();
				
				u8_l_counter++;
				
				if ( u8_g_select == APP_U8_CAR_ROTATE_RGT )
				{
					DCM_controlDCMSpeed( 30 );
					DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CCW );
					DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CW );
					
					LCD_setCursor( 1, 0 );
					LCD_sendString((u8*)"Speed:30% Dir:R");
				}
				
				else
				{
					DCM_controlDCMSpeed( 30 );
					DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_ROTATE_CW );
					DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_ROTATE_CCW );
					
					LCD_setCursor( 1, 0 );
					LCD_sendString( ( u8* ) "Speed:30% Dir:R" );
				}
				
				TMR0_delayMS( 600 );
			}
			
			if ( u8_l_counter == 4 )
			{
				while( u16_l_distance <= 20 )
				{
					DCM_controlDCMSpeed( 30 );
					DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
					DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
					
					u16_l_distance = US_readDistance();
					
					LCD_setCursor( 0, 6 );
					LCD_sendString( ( u8* ) "00" );
					LCD_setCursor( 0, 14 );
					LCD_sendCharacter( 'S' );
					APP_stopCar();
				}
			}
			
			APP_stopCar();
		}
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_stopCar
 Input: void
 Output: void
 Description: Function to Stop the car. 
*/
vd APP_stopCar( void )
{
	u8 u8_l_keyValue = KPD_U8_KEY_NOT_PRESSED;
	
	KPD_getPressedKey( &u8_l_keyValue );
	
	if ( u8_l_keyValue == '2' )
	{
		DCM_controlDCMSpeed( 30 );
		DCM_controlDCM( &ast_g_DCMs[0], DCM_U8_STOP );
		DCM_controlDCM( &ast_g_DCMs[1], DCM_U8_STOP );
		
		LCD_setCursor( 0, 0 );
		LCD_sendString( ( u8* ) "Speed:00% Dir:S" );
		
		while ( u8_l_keyValue != '1' )
		{
			KPD_getPressedKey( &u8_l_keyValue );
		}
	}	
}

/*******************************************************************************************************************************************************************/