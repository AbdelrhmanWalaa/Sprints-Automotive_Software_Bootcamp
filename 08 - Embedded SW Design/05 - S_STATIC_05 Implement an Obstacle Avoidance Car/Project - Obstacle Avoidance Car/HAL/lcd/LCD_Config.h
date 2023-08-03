/*
 * lcd_config.h
 *
 *   Created on: MAY 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Liquid Crystal Display (LCD) pre-build configurations, through which user can configure before using the LCD peripheral.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* ATmega32(L) interfacing with LCD: */
/*
									  -----------                   ----------
									 | ATmega32  |                 |   LCD    |
									 |           |                 |          |
									 |        PC0|---------------->|RS        |
									 |        PC1|---------------->|RW        |
									 |        PC2|---------------->|E         |
									 |           |                 |          |
									 |        PD0|---------------->|D0        |
									 |        PD1|---------------->|D1        |
									 |        PD2|---------------->|D2        |
									 |        PD3|---------------->|D3        |
									 |        PD4|---------------->|D4        |
									 |        PD5|---------------->|D5        |
									 |        PD6|---------------->|D6        |
									 |        PD7|---------------->|D7        |
									  -----------                   ----------
 */

/*******************************************************************************************************************************************************************/
/* LCD Configurations Definitions */


							/************************************************************************/
							/*                            LCD Settings							     */
							/************************************************************************/

/************************************************************************/
/* LCD Modes */               
#define bit_4 4
#define bit_8 8

/************************************************************************/
/************************************************************************/
/*  Mode for data transfer Choose ( bit_4 or bit_8 )                                                                     */
/************************************************************************/
#define Mode bit_4
/************************************************************************/
/************************************************************************/
/*							Definitions										*/
/************************************************************************/
/*
						4 bits mode definitions
*/
#if Mode == bit_4						//if LCD mode chosen in 4bit mode
#define D7 P7							//Data7 is connected to Pin Number is 7
#define D6 P6							//Data6 is connected to Pin Number is 6
#define D5 P5							//Data5 is connected to Pin Number is 5
#define D4 P4							//Data4 is connected to Pin Number is 4
#define EN P3							//EN is connected to Pin Number is 3
#define RW P2							//RW is connected to Pin Number is 2
#define RS P1							//RS is connected to Pin Number is 1
#define LCD_Data_cmmnd_Port A			//Data and Command pins connected to Port A
/*
						8 bits mode definitions
*/
#elif Mode == bit_8					//if LCD mode chosen in 8bit mode
#define D7 P7						//Data7 is connected to Pin Number is 7
#define D6 P6						//Data6 is connected to Pin Number is 6
#define D5 P5						//Data5 is connected to Pin Number is 5
#define D4 P4						//Data4 is connected to Pin Number is 4
#define D3 P3						//Data3 is connected to Pin Number is 3
#define D2 P2						//Data2 is connected to Pin Number is 2
#define D1 P1						//Data1 is connected to Pin Number is 1
#define D0 P0						//Data0 is connected to Pin Number is 0
#define RS P0						//RS Pin Number is 0
#define RW P1						//RW Pin Number is 1
#define EN P2						//EN Pin Number is 2
#define LCD_Data_Port A				//Data pins connected to Port A
#define LCD_cmmnd_Port B			//Command pins is connected to Port B
#endif

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/

#endif /* LCD_CONFIG_H_ */