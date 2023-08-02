/*
 * lcd.c
 *
 * Created: 18/4/2023 3:44:59 PM
 *  Author: Hossam
 */

#include "lcd_interface.h"
#include "lcd_private.h"

// current cursor position (0 -> 15 @line1, 16 -> 31 @line2)
static u8 u8_gs_cursor = 0;

/**
 * @brief Initializes the LCD module.
 * This function initializes the LCD module by configuring the data port,
 * configuring the LCD to 4-bit mode,setting the display to on with cursor
 * and blink, setting the cursor to increment to the right, and clearing the display.
 * It also pre-stores a bell shape at CGRAM location 0.
 *
 * @return void
 */
void LCD_init(void) {
    DIO_portInit(LCD_DATA_PORT, DIO_PORT_OUT, DIO_NO_MASK);
    DIO_portWrite(LCD_DATA_PORT, DIO_U8_PORT_LOW, DIO_NO_MASK);
    TIMER_timer0NormalModeInit(DISABLED);
    TIMER_delay_ms(LCD_MS_DELAY_INIT); // 10 ms
    LCD_sendCommand(LCD_CMD_RETURN_HOME); // Return home
    LCD_sendCommand(LCD_CMD_MODE_4Bit); // 4 bit mode, 2 lines, 5*7 matrix
    LCD_sendCommand(LCD_CMD_DCB); // Display on, Cursor on, Blink on
    LCD_sendCommand(LCD_CMD_INC_CURSOR_RIGHT); // Increment cursor (shift to right)
    LCD_sendCommand(LCD_CMD_CLEAR); // Clear display
    TIMER_delay_ms(LCD_MS_DELAY_STORE);

//	LCD_sendString((u8 *)"Hello world!\n> Hossam Elwahsh");

//    TIMER_delay_ms(LCD_MS_DELAY_STORE);

    // pre-storing bell shape at CGRAM location 0
    LCD_storeCustomCharacter(
            (u8[]) {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00},
        LCD_CUSTOMCHAR_LOC0
        );
    TIMER_delay_ms(LCD_MS_DELAY_STORE);

    // display bell top right
//    LCD_setCursor(LCD_LINE0, LCD_COL15);
//    LCD_sendChar(LCD_CUSTOMCHAR_LOC0);
}

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
void LCD_sendCommand(u8 u8_a_cmd) {

    // RS select command register
    DIO_write(LCD_CTRL_PIN_RS, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

	// send upper nibble
	DIO_portWrite(LCD_DATA_PORT, HIGHER_NIBBLE_SHIFT(u8_a_cmd), LCD_DATA_PINS_MASK);

    // Enable Pulse
    DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_HIGH);
    TIMER_delay_us(LCD_US_DELAY_PULSE);
    DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

	TIMER_delay_us(LCD_US_DELAY_HOLD);

    // send lower nibble
    DIO_portWrite(LCD_DATA_PORT, LOWER_NIBBLE_SHIFT(u8_a_cmd), LCD_DATA_PINS_MASK);

    // Enable Pulse
    DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_HIGH);
    TIMER_delay_us(LCD_US_DELAY_PULSE);
    DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

    TIMER_delay_ms(LCD_MS_DELAY_STORE); // 2ms
}

/**



    @param u8_a_data The character to be sent to the LCD display
    @return void
    */

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
void LCD_sendChar(u8 u8_a_data) {
	
	// Select Data Register
	DIO_write(LCD_CTRL_PIN_RS, LCD_CTRL_PORT, DIO_U8_PIN_HIGH);

	// Enable LCD
	DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

	// Send higher nibble
	DIO_portWrite(LCD_DATA_PORT, HIGHER_NIBBLE_SHIFT(u8_a_data), LCD_DATA_PINS_MASK);

	// Enable Pulse
	DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_HIGH);
	TIMER_delay_us(LCD_US_DELAY_PULSE);
	DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

	// Send lower nibble
	DIO_portWrite(LCD_DATA_PORT, LOWER_NIBBLE_SHIFT(u8_a_data), LCD_DATA_PINS_MASK);

	// Enable Pulse
	DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_HIGH);
	TIMER_delay_us(LCD_US_DELAY_PULSE);
	DIO_write(LCD_CTRL_PIN_EN, LCD_CTRL_PORT, DIO_U8_PIN_LOW);

	TIMER_delay_ms(LCD_MS_DELAY_CHAR);
}

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
void LCD_sendString(u8 * u8Ptr_a_str) {
	while( *u8Ptr_a_str != '\0')
	{
		if(*u8Ptr_a_str == '\n')
		{
			LCD_setCursor(u8_gs_cursor < LCD_LINE_COLS ? LCD_LINE1 : LCD_LINE0, LCD_COL0);
			u8Ptr_a_str++;
			continue;
		}
		LCD_sendChar(*u8Ptr_a_str);
        u8Ptr_a_str++;
        u8_gs_cursor++;
        if(u8_gs_cursor == LCD_LINE_COLS) LCD_setCursor(LCD_LINE1, LCD_COL0);
        else if(u8_gs_cursor == LCD_LINE_COLS * LCD_LINES_COUNT) LCD_setCursor(LCD_LINE0, LCD_COL0);
	}
}

/**
 * @brief Set the cursor position on the LCD.
 *
 * @param [in]u8_a_line the line number to set the cursor to, either LCD_LINE0 or LCD_LINE1
 * @param [in]u8_a_col the column number to set the cursor to, from LCD_COL0 to LCD_COL15
 *
 * @return STD_OK if the operation was successful, STD_NOK otherwise.
 */
u8 LCD_setCursor(u8 u8_a_line, u8 u8_a_col) {
    if(u8_a_line > LCD_LINE1 || u8_a_col > LCD_COL15) return STD_NOK;
    unsigned char firstCharAddr[] = {LCD_LINE0_ADDR, LCD_LINE1_ADDR}; // Address of the first character of each line
    LCD_sendCommand(firstCharAddr[u8_a_line] + u8_a_col);
	// update global cursor
	u8_gs_cursor = (u8_a_line * LCD_LINE_COLS) + u8_a_col;
    return STD_OK;
}

// locations: LCD_CUSTOMCHAR_LOC0 -> LOC7

/**
 * @brief Stores a custom character bitmap pattern in the CGRAM of the LCD module
 *
 * @param [in]u8_a_pattern Pointer to an array of 8 bytes representing the bitmap pattern of the custom character
 * @param [in]u8_a_location The CGRAM location where the custom character should be stored (from LCD_CUSTOMCHAR_LOC0 to 7)
 *
 * @return STD_OK if successful, otherwise STD_NOK
 */
u8 LCD_storeCustomCharacter(u8 * u8_a_pattern, u8 u8_a_location) {

    if(u8_a_location > LCD_CGRAM_LOC_COUNT) return STD_NOK;

    // set CGRAM Address
    LCD_sendCommand(LCD_CGRAM_ADDR + (u8_a_location * LCD_CGRAM_LOC_SIZE));

    // store custom character bitmap bytes
    for (int i = 0; i < LCD_CGRAM_LOC_SIZE; ++i) {
        LCD_sendChar(u8_a_pattern[i]);
    }

    return STD_OK;
}

/**
 * Clears the LCD display
 */
void LCD_clear(void)
{
    LCD_sendCommand(LCD_CMD_CLEAR);
    u8_gs_cursor = 0;
}

/**
 * Fancy right shift clear for the LCD display
 */
void LCD_shiftClear(void)
{
    for (int i = 0; i < LCD_LINE_COLS; ++i) {
        LCD_sendCommand(LCD_CMD_DISP_SHIFT_RIGHT);
        TIMER_delay_ms(LCD_MS_DELAY_SHIFT);
    }
    LCD_sendCommand(LCD_CMD_CLEAR);
    u8_gs_cursor = 0;
}