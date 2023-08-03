/*
 * dcm_config.h
 *
 *   Created on: Apr 11, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Direct Current Motor (DCM) pre-build configurations, through which user can configure before using the DCM peripheral.
 *    Datasheet: https://datasheetspdf.com/pdf/917207/KYSAN/RF-300CA-11440/1
 *    Model No.: RF-300CA-11440 - DCM
 */

#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* DCM Configurations */

/* DCM Speed (PWM) Port */
/* Options: A:0
			B:1
			C:2
			D:3
*/
#define DCM_U8_PWM_PORT				D

/* DCM Speed (PWM) Pin */
/* Options: P0
			P1
			P2
			P3
			P4
			P5
			P6
			P7
 */
#define DCM_U8_PWM_PIN				P4
 
/* Number of DCM(s) */
#define DCM_U8_NUMBER_OF_DCM		2

/* DCM Max Speed */
#define DCM_U8_MAX_SPEED			100

/* DCM Frequency is 200 Hz ( i.e. 0.2 KHz )  */
#define DCM_U8_FREQUENCY			0.2f

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* DCM_CONFIG_H_ */