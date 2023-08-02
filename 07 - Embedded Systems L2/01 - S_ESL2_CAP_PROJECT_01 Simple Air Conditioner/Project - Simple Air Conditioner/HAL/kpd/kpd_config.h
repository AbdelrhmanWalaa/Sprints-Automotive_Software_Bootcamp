/*
 * kpd_config.h
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Keypad (KPD) pre-build configurations, through which user can configure before using the KPD peripheral.
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with KPD: */
/*
 									  -----------                   ----------
									 | ATmega32  |                 |   KPD    |
									 |           |                 |          |
									 |        PA1|---------------->|R1        |
									 |        PA2|---------------->|R2        |
									 |           |                 |          |
									 |        PA4|<----------------|C1        |
									 |        PA5|<----------------|C2        |
									 |        PA6|<----------------|C3        |
									  -----------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* KPD Configurations */

/* KPD Port(s) */
/* Options: PORT_A:0
			PORT_B:1
			PORT_C:2
			PORT_D:3
 */
#define KPD_U8_INPUT_PORT		2
#define KPD_U8_OUTPUT_PORT		2

/* KPD Pins */
/* Options: DIO_U8_PIN_0
			DIO_U8_PIN_1
			DIO_U8_PIN_2
			DIO_U8_PIN_3
			DIO_U8_PIN_4
			DIO_U8_PIN_5
			DIO_U8_PIN_6
			DIO_U8_PIN_7
 */
/* KPD Rows */
#define KPD_U8_R1_PIN			DIO_U8_PIN_2
#define KPD_U8_R2_PIN			DIO_U8_PIN_3

/* KPD Columns */
#define KPD_U8_C1_PIN			DIO_U8_PIN_5
#define KPD_U8_C2_PIN			DIO_U8_PIN_6
#define KPD_U8_C3_PIN			DIO_U8_PIN_7

/* KPD Output and Input Pins */
/* Options: 1.Rows:    KPD_U8_R1_PIN
 * 			           KPD_U8_R2_PIN
 *
 *          2.Columns: KPD_U8_C1_PIN
 *                     KPD_U8_C2_PIN
 *                     KPD_U8_C3_PIN
 */
#define KPD_U8_OUTPUT_PIN1		KPD_U8_R1_PIN
#define KPD_U8_OUTPUT_PIN2		KPD_U8_R2_PIN

#define KPD_U8_INPUT_PIN1		KPD_U8_C1_PIN
#define KPD_U8_INPUT_PIN2		KPD_U8_C2_PIN
#define KPD_U8_INPUT_PIN3		KPD_U8_C3_PIN

/* KPD Configured Keys */
#define KPD_AU8_KEYS	  	  { { '1', '2',  '3'  },  \
								{ '4', '5', '6' } }

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* KPD_CONFIG_H_ */