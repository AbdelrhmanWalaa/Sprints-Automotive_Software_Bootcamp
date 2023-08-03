/*
 * kpd_config.h
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Keypad (KPD) pre-build configurations, through which user can configure before using the KPD peripheral.
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with KPD: */

/*
									   -----------                   ----------
									  | ATmega32  |                 |   KPD    |
									  |           |                 |          |
									  |        PC2|---------------->|R1        |
									  |           |                 |          |
									  |        PC5|<----------------|C1        |
									  |        PC6|<----------------|C2        |
									   -----------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* KPD Configurations */

/* KPD Port(s) */
/* Options: A:0
			B:1
			C:2
			D:3
 */
#define KPD_U8_INPUT_PORT		2
#define KPD_U8_OUTPUT_PORT		2

/* KPD Pins */
/* Options: P0
			P1
			P2
			P3
			P4
			P5
			P6
			P7
 */
/* KPD Rows */
#define KPD_U8_R1_PIN			P2

/* KPD Columns */
#define KPD_U8_C1_PIN			P5
#define KPD_U8_C2_PIN			P6

/* KPD Output and Input Pins */
/* Options: 1.Rows:    KPD_U8_R1_PIN
 *
 *          2.Columns: KPD_U8_C1_PIN
 *                     KPD_U8_C2_PIN
 */
#define KPD_U8_OUTPUT_PIN1		KPD_U8_R1_PIN

#define KPD_U8_INPUT_PIN1		KPD_U8_C1_PIN
#define KPD_U8_INPUT_PIN2		KPD_U8_C2_PIN

/* KPD Configured Keys */
#define KPD_AU8_KEYS	  	  { { '1', '2' } }

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* KPD_CONFIG_H_ */