/*
 * lcd_interface.h
 *
 * Created: 18/4/2023 3:45:22 PM
 *  Author: Hossam
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* Includes */
#include "../../LIB/std.h"
#include "lcd_config.h"
#include "../../MCAL/timer/timer_interface.h"

/* Macros */

// LCD Lines
#define LCD_LINE0   0
#define LCD_LINE1   1

// LCD Columns
#define LCD_COL0	0
#define LCD_COL1	1
#define LCD_COL2	2
#define LCD_COL3	3
#define LCD_COL4	4
#define LCD_COL5	5
#define LCD_COL6	6
#define LCD_COL7	7
#define LCD_COL8	8
#define LCD_COL9	9
#define LCD_COL10	10
#define LCD_COL11	11
#define LCD_COL12	12
#define LCD_COL13	13
#define LCD_COL14	14
#define LCD_COL15	15

// LCD Custom Chars Locations
#define LCD_CUSTOMCHAR_LOC0	0
#define LCD_CUSTOMCHAR_LOC1	1
#define LCD_CUSTOMCHAR_LOC2	2
#define LCD_CUSTOMCHAR_LOC3	3
#define LCD_CUSTOMCHAR_LOC4	4
#define LCD_CUSTOMCHAR_LOC5	5
#define LCD_CUSTOMCHAR_LOC6	6
#define LCD_CUSTOMCHAR_LOC7	7

/* Custom Chars */
#define LCD_CUSTOM_SOLID_BLOCK 0xFF

/* Prototypes */

/**
 * @brief Initializes the LCD module.
 * This function initializes the LCD module by configuring the data port,
 * configuring the LCD to 4-bit mode,setting the display to on with cursor
 * and blink, setting the cursor to increment to the right, and clearing the display.
 * It also pre-stores a bell shape at CGRAM location 0.
 *
 * @return void
 */
void LCD_init(void);


/**
 * @brief Sends a command to the LCD controller
 *
 * Sends the upper nibble of the command to the LCD's data pins, selects the command register by setting RS to low,
 * generates an enable pulse, delays for a short period, then sends the lower nibble of the command and generates
 * another enable pulse. Finally, it delays for a longer period to ensure the command has been executed by the LCD
 * controller.
 *
 * @param [in]u8_a_cmd The command to be sent
 */
void LCD_sendCommand(u8 u8_a_cmd);

/**
 * @brief Sends a single character to the LCD display
 *
 * This function sends a single character to the LCD display by selecting the data register and sending the
 * higher nibble and lower nibble of the character through the data port.
 * The function uses a pulse on the enable pin to signal the LCD to read the data on the data port.
 * The function also includes delays to ensure proper timing for the LCD to read the data.
 *
 * @param [in]u8_a_data single char ASCII data to show
 */
void LCD_sendChar(u8 u8_a_data);

/**
 * @brief Displays a null-terminated string on the LCD screen.
 *
 * This function iterates through a null-terminated string and displays it
 * on the LCD screen. If the character '\\n' is encountered, the cursor is
 * moved to the beginning of the next line.
 *
 * @param [in]u8Ptr_a_str A pointer to the null-terminated string to be displayed.
 *
 * @return void
 */
void LCD_sendString(u8 * u8Ptr_a_str);

/**
 * @brief Set the cursor position on the LCD.
 *
 * @param [in]u8_a_line the line number to set the cursor to, either LCD_LINE0 or LCD_LINE1
 * @param [in]u8_a_col the column number to set the cursor to, from LCD_COL0 to LCD_COL15
 *
 * @return STD_OK if the operation was successful, STD_NOK otherwise.
 */
u8 LCD_setCursor(u8 u8_a_line, u8 u8_a_col);

/**
 * @brief Stores a custom character bitmap pattern in the CGRAM of the LCD module
 *
 * @param [in]u8_a_pattern Pointer to an array of 8 bytes representing the bitmap pattern of the custom character
 * @param [in]u8_a_location The CGRAM location where the custom character should be stored (from LCD_CUSTOMCHAR_LOC0 to 7)
 *
 * @return STD_OK if successful, otherwise STD_NOK
 */
u8 LCD_storeCustomCharacter(u8 * u8_a_pattern, u8 u8_a_location);

/**
 * Clears the LCD display
 */
void LCD_clear(void);

/**
 * Fancy right shift clear for the LCD display
 */
void LCD_shiftClear(void);
#endif /* LCD_INTERFACE_H_ */