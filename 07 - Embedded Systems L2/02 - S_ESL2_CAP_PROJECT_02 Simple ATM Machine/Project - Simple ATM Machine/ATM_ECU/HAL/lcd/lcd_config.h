/*
 * 4-Bit mode LCD Interfacing Config File
 * lcd_config.h
 *
 * Created: 18/4/2023 3:45:35 PM
 *  Author: Hossam
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../MCAL/dio/dio_interface.h"


/** LCD Data */
/* LCD_DATA_PORT Options
 * PORT_A: 0
 * PORT_B: 1
 * PORT_C: 2
 * PORT_D: 3
 * */
#define LCD_DATA_PORT 0

// DATA PINS
#define LCD_DATA_PIN_D4     DIO_U8_PIN_4
#define LCD_DATA_PIN_D5     DIO_U8_PIN_5
#define LCD_DATA_PIN_D6     DIO_U8_PIN_6
#define LCD_DATA_PIN_D7     DIO_U8_PIN_7
#define LCD_DATA_PINS_MASK    DIO_MASK_BITS_4_5_6_7

/** LCD Control */
/* LCD_CTRL_PORT Options
 * PORT_A: 0
 * PORT_B: 1
 * PORT_C: 2
 * PORT_D: 3
 * */
#define LCD_CTRL_PORT 0
#define LCD_CTRL_PIN_RS     DIO_U8_PIN_1
#define LCD_CTRL_PIN_RW     DIO_U8_PIN_2
#define LCD_CTRL_PIN_EN     DIO_U8_PIN_3


#define HIGHER_NIBBLE_SHIFT(cmd)    cmd
#define LOWER_NIBBLE_SHIFT(cmd)     cmd << 4


#endif /* LCD_CONFIG_H_ */