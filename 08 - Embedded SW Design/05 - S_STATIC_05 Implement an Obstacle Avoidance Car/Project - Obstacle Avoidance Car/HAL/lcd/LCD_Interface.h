/*
 * lcd_interface.h
 *
 *   Created on: MAY 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Liquid Crystal Display (LCD) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* LCD Includes */

/* LIB */
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"
#include "../../LIB/mcu_config/mcu_config.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/tmr0/tmr0_interface.h"

/*******************************************************************************************************************************************************************/

/* The LCD's DDRAM ( 80 locations ) is divided as the following:
 *
 * LCD Line1 ( 40 locations ): From location 0->39 ( Only 0->15 are displayed  )
 * Starting address of LCD Line1 : Dec.-> 0, Hex.-> 0x00
 *
 * LCD Line2 ( 40 locations ): From location 64->104 ( Only 64->79 are displayed  )
 * Starting address of LCD Line2 : Dec.-> 64, Hex.-> 0x40
 */

/*******************************************************************************************************************************************************************/
/* LCD Functions' Prototypes */

void LCD_init ( void );
void LCD_sendCommand ( u8 u8_a_cmnd );
void LCD_sendCharacter ( u8 u8_a_char );
void LCD_clear ( void );
void LCD_setCursor ( u8 u8_a_row, u8 u8_a_column );
void LCD_sendString ( u8 *pu8_a_string );
void LCD_floatToString ( f32 f32_a_floatValue );
void LCD_createCustomCharacter ( u8 *pu8_a_pattern, u8 u8_a_location );

/*******************************************************************************************************************************************************************/

#endif /* LCD_INTERFACE_H_ */

