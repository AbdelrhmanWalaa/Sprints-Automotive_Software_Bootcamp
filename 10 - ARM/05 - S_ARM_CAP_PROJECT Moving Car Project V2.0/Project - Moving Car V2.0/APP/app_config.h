/*
 * app_config.h
 *
 *   Created on: Jun 25, 2023
 *       Author: Bits 0101 Tribe - 
 *  Description: This file contains all Application (APP) pre-build configurations, through which user can configure before using the APP.
 */ 

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* APP Configurations */

/* LED(s) Configurations */
/* LED(s) Port(s) */
/* Options: ENU_PORT_A
 *          ENU_PORT_B
 *          ENU_PORT_C
 *          ENU_PORT_D
 *          ENU_PORT_D
 *          ENU_PORT_E
 *          ENU_PORT_F
 */
#define APP_MOVE_FWD_LD_LED_PORT 		ENU_PORT_F     // LED 0
#define APP_MOVE_FWD_SD_LED_PORT  	ENU_PORT_F     // LED 1
#define APP_STOP_LED_PORT	      		ENU_PORT_F     // LED 2
#define APP_ROTATE_LED_PORT	    		ENU_PORT_F     // LED 3

/* LED(s) Pin(s) */
/* Options: ENU_PIN_0
 *          ENU_PIN_1
 *          ENU_PIN_2
 *          ENU_PIN_3
 *          ENU_PIN_4
 *          ENU_PIN_5
 *          ENU_PIN_6
 *          ENU_PIN_7 
 */
#define APP_MOVE_FWD_LD_LED_PIN  		ENU_PIN_3      // LED 0
#define APP_MOVE_FWD_SD_LED_PIN  		ENU_PIN_3      // LED 1
#define APP_STOP_LED_PIN	      		ENU_PIN_1      // LED 2
#define APP_ROTATE_LED_PIN	    		ENU_PIN_2      // LED 3

/* End of LED(s) Configurations */

/* BUTTON(s) Configurations */
/* BUTTON(s) Port(s) */
/* Options: ENU_PORT_A
 *          ENU_PORT_B
 *          ENU_PORT_C
 *          ENU_PORT_D
 *          ENU_PORT_D
 *          ENU_PORT_E
 *          ENU_PORT_F
 */
#define APP_STOP_BTN_PORT	      		ENU_PORT_F     // PUSH BUTTON 0
#define APP_START_BTN_PORT					ENU_PORT_F     // PUSH BUTTON 1

/* BUTTON(s) Pin(s) */
/* Options: ENU_PIN_0
 *          ENU_PIN_1
 *          ENU_PIN_2
 *          ENU_PIN_3
 *          ENU_PIN_4
 *          ENU_PIN_5
 *          ENU_PIN_6
 *          ENU_PIN_7 
 */
#define APP_STOP_BTN_PIN 	      		ENU_PIN_0      // PUSH BUTTON 0
#define APP_START_BTN_PIN			  		ENU_PIN_4      // PUSH BUTTON 1
/* End of BUTTON(s) Configurations */

/* DCM(s) Configurations */
/* DCM(s) Port(s) */
/* Options: ENU_PORT_A
 *          ENU_PORT_B
 *          ENU_PORT_C
 *          ENU_PORT_D
 *          ENU_PORT_D
 *          ENU_PORT_E
 *          ENU_PORT_F
 */
/* Right DCM */
#define	APP_DCM_R_DIR_CW_PORT				ENU_PORT_E     // MOTOR DRIVER DIRECTION 1A
#define	APP_DCM_R_DIR_CCW_PORT			ENU_PORT_E     // MOTOR DRIVER DIRECTION 2A

/* Left DCM  */
#define	APP_DCM_L_DIR_CW_PORT				ENU_PORT_A     // MOTOR DRIVER DIRECTION 2B
#define	APP_DCM_L_DIR_CCW_PORT			ENU_PORT_A     // MOTOR DRIVER DIRECTION 2B

/* DCM(s) Pin(s) */
/* Options: ENU_PIN_0
 *          ENU_PIN_1
 *          ENU_PIN_2
 *          ENU_PIN_3
 *          ENU_PIN_4
 *          ENU_PIN_5
 *          ENU_PIN_6
 *          ENU_PIN_7 
 */
/* Right DCM */
#define APP_DCM_R_DIR_CW_PIN				ENU_PIN_4     // MOTOR DRIVER DIRECTION 1A
#define	APP_DCM_R_DIR_CCW_PIN				ENU_PIN_5     // MOTOR DRIVER DIRECTION 2A

/* Left DCM */
#define APP_DCM_L_DIR_CW_PIN				ENU_PIN_7     // MOTOR DRIVER DIRECTION 1B
#define	APP_DCM_L_DIR_CCW_PIN				ENU_PIN_6     // MOTOR DRIVER DIRECTION 2B
/* End of DCM(s) Configurations */

/* Delays/Timing Config */
#define APP_STARTING_DELAY      		1000
#define APP_FWD_LD_DURATION     		1500
#define APP_FWD_LD_SPEED         		50
#define APP_ROTATION_DELAY      		500
#define APP_ROTATION_DURATION   		450
#define APP_FWD_SD_DURATION     		1000
#define APP_FWD_SD_SPEED         		30

/* APP_BREAK_FLAG */
#define APP_BREAK_FLAG_DOWN     		0
#define APP_BREAK_FLAG_UP       		1

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* APP_CONFIG_H_ */
