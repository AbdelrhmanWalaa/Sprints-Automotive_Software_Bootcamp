/*
 * app_config.h
 *
 *   Created on: May 16, 2023
 *       Author: Bits 0101 Tribe - https://github.com/AbdelrhmanWalaa/Obstacle-Avoidance-Car.git
 *  Description: This file contains all Application (APP) pre-build configurations, through which user can configure before using the APP.
 */ 

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* APP Configurations */

/* APP Car Rotation Directions */
#define	APP_U8_CAR_ROTATE_RGT		0
#define	APP_U8_CAR_ROTATE_LFT		1

/* DCM Port(s) */
/* Options: A:0
			B:1
			C:2
			D:3
 */
/* Right DCM */
#define	APP_U8_DCM_R_DIR_CW_PORT	3
#define	APP_U8_DCM_R_DIR_CCW_PORT	3

/* Left DCM  */
#define	APP_U8_DCM_L_DIR_CW_PORT	3
#define	APP_U8_DCM_L_DIR_CCW_PORT	3

/* DCM Pins */
/* Options: P0
			P1
			P2
			P3
			P4
			P5
			P6
			P7
 */
/* Right DCM */
#define APP_U8_DCM_R_DIR_CW_PIN		2
#define	APP_U8_DCM_R_DIR_CCW_PIN	3

/* Left DCM */
#define APP_U8_DCM_L_DIR_CW_PIN		6
#define	APP_U8_DCM_L_DIR_CCW_PIN	7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* APP_CONFIG_H_ */