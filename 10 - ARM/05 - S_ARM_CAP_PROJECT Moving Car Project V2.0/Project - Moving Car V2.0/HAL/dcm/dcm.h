 /*
  * dcm.h
  *
  *   Created on: Apr 11, 2023
  *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
  *  Description: This file contains all Direct Current Motor (DCM) functions' prototypes and definitions (Macros) to avoid magic numbers.
  *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
  *    Model No.: RF-300CA-11440 - DCM
  */

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DCM Includes */

/* LIB */
#include "../../LIB/std_types.h"
#include "../../LIB/common_macros.h"

/* HAL */
#include "../pwm/pwm.h"

/* MCAL */
#include "../../MCAL/gpio/gpio.h"

/*******************************************************************************************************************************************************************/
/* DCM Macros */

/* DCM CW and CCW Configurations */
typedef struct
{
	uint8 u8_g_directionCWPort;
	uint8 u8_g_directionCWPin;
	uint8 u8_g_directionCCWPort;
	uint8 u8_g_directionCCWPin;
	
} DCM_ST_CONFIG;

/* DCM Control Modes */
#define DCM_U8_STOP				  0
#define DCM_U8_ROTATE_CW		2
#define DCM_U8_ROTATE_CCW		3

/*******************************************************************************************************************************************************************/
/* DCM Configurations */

/* DCM Speed (PWM) Port */
/* Options: ENU_PORT_A
 *          ENU_PORT_B
 *          ENU_PORT_C
 *          ENU_PORT_D
 *          ENU_PORT_D
 *          ENU_PORT_E
 *          ENU_PORT_F
 */
#define DCM_U8_PWM_PORT				 ENU_PORT_A    // MOTOR 1 ENABLE

/* DCM Speed (PWM) Pin */
/* Options: ENU_PIN_0
 *          ENU_PIN_1
 *          ENU_PIN_2
 *          ENU_PIN_3
 *          ENU_PIN_4
 *          ENU_PIN_5
 *          ENU_PIN_6
 *          ENU_PIN_7 
 */
#define DCM_U8_PWM_PIN			    ENU_PIN_5    // MOTOR 1 ENABLE

/* DCM Speed (PWM) Timer */
/* Options: TIMER0_ID 
 *          TIMER1_ID 
 *          TIMER2_ID	
 *          TIMER3_ID	
 *          TIMER4_ID	
 *          TIMER5_ID	
 *          TIMER6_ID	
 *          TIMER7_ID	
 *          TIMER8_ID	
 *          TIMER9_ID
 *				  TIMER10_ID
 *          TIMER11_ID
 */        
#define DCM_U8_PWM_TIMER			  TIMER0_ID
 
/* Number of DCM(s) */
#define DCM_U8_NUMBER_OF_DCM		2

/* DCM Max Speed */
#define DCM_U8_MAX_SPEED			  100

/* DCM Frequency is 40 Hz ( i.e. 0.04 KHz => 25 msec )  */
#define DCM_U8_PERIOD					  25

/* End of Configurations */

/*******************************************************************************************************************************************************************/
/* DCM Functions' Prototypes */

/*
 Name: DCM_initialization
 Input: Pointer to st DCMConfig
 Output: en Error or No Error
 Description: Function to Initialize DCM peripheral.
*/
enu_error_state_t DCM_initialization ( DCM_ST_CONFIG *pst_a_DCMConfig );

/*
 Name: DCM_controlDCM
 Input: Pointer to st DCMConfig and u8 ControlMode
 Output: en Error or No Error
 Description: Function Control DCM with one of DCM Modes.
*/
enu_error_state_t DCM_controlDCM     ( DCM_ST_CONFIG *pst_a_DCMConfig, uint8 u8_a_controlMode );

/*
 Name: DCM_controlDCMSpeed
 Input: u8 SpeedPercentage
 Output: en Error or No Error
 Description: Function Control DCM Speed.
*/
enu_error_state_t DCM_controlDCMSpeed( uint8 u8_a_speedPercentage );

/*******************************************************************************************************************************************************************/

#endif /* DCM_INTERFACE_H_ */
