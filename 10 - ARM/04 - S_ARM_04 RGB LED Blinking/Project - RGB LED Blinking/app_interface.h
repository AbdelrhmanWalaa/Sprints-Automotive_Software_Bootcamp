/*
 * app_interface.h
 *
 *   Created on: Jun 15, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* HAL */
#include "led_interface.h"
#include "btn_interface.h"
#include "pwm_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP States */
#define APP_U8_STATE_0                    0
#define APP_U8_STATE_1                    1
#define APP_U8_STATE_2                    2
#define APP_U8_STATE_3                    3

/* APP PWM Total Period */
#define APP_U16_PWM_TOTAL_PERIOD          500

/* APP PWM Duty Cycles */
#define APP_U8_PWM_30_PERCENT_DUTY_CYCLE  30
#define APP_U8_PWM_60_PERCENT_DUTY_CYCLE  60
#define APP_U8_PWM_90_PERCENT_DUTY_CYCLE  90

/* APP PWM Total Period Divider */
#define APP_F32_PWM_TOTAL_PERIOD_DIVIDER	0.02f

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to Initialize the Application.
*/ 
void APP_initialization( void );

/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Run the basic flow of the Application. 
*/
void APP_startProgram( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */
