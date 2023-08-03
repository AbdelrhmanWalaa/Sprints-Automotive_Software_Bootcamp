/*
 * lcd_program.c
 *
 *   Created on: MAY 16, 2023
 *       Author: Mohamed Abdelsalam - https://github.com/m3adel
 *  Description: This file contains all Liquid Crystal Display (LCD) functions' implementation.
 *    Datasheet: https://datasheetspdf.com/pdf/746281/Topway/LMB161ABC-1/1
 *    Model No.: LMB161A - LCD
 */

/* HAL */
#include "lcd_config.h"
#include "lcd_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_init
 Input: void
 Output: void
 Description: Function to initialize (both 4 Bit and 8 Bit Modes) LCD.
*/
void LCD_init ( void )
{	
	#if Mode == bit_8							//if LCD mode chosen in 8bit mode
	DIO_init (LCD_Data_Port, D7 ,OUT);			//make data7 pin output
	DIO_init (LCD_Data_Port, D6 ,OUT);			//make data6 pin output
	DIO_init (LCD_Data_Port, D5 ,OUT);			//make data5 pin output
	DIO_init (LCD_Data_Port, D4 ,OUT);			//make data4 pin output
	DIO_init (LCD_Data_Port, D3 ,OUT);			//make data3 pin output
	DIO_init (LCD_Data_Port, D2 ,OUT);			//make data2 pin output
	DIO_init (LCD_Data_Port, D1 ,OUT);			//make data1 pin output
	DIO_init (LCD_Data_Port, D0 ,OUT);			//make data0 pin output
	DIO_init (LCD_cmmnd_Port, EN ,OUT);			//make enable pin output
	DIO_init (LCD_cmmnd_Port, RW ,OUT);			//make Rw pin output
	DIO_init (LCD_cmmnd_Port, RS ,OUT);			//make Rs pin output
	//_delay_ms(20);							//LCD power on delay is always more than 15ms
	TMR0_delayMS(20);
	LCD_sendCommand(0x38);						//initialization LCD 16x2 in 8bit mode
	LCD_sendCommand(0x0C);						//display on cursor off
	LCD_sendCommand(0x06);						//auto increment cursor
	LCD_sendCommand(0x01);						//clear display
	LCD_sendCommand(0x80);						//cursor at home position
	#elif Mode == bit_4							//if LCD mode chosen in 4bit mode
	DIO_init (LCD_Data_cmmnd_Port, D7 ,OUT);	//make data7 pin output
	DIO_init (LCD_Data_cmmnd_Port, D6 ,OUT);	//make data6 pin output
	DIO_init (LCD_Data_cmmnd_Port, D5 ,OUT);	//make data5 pin output
	DIO_init (LCD_Data_cmmnd_Port, D4 ,OUT);	//make data4 pin output
	DIO_init (LCD_Data_cmmnd_Port, EN ,OUT);	//make enable pin output
	DIO_init (LCD_Data_cmmnd_Port, RW ,OUT);	//make rw pin output
	DIO_init (LCD_Data_cmmnd_Port, RS ,OUT);	//make rs pin output
	//_delay_ms(20);							//LCD power on delay is always more than 15ms
	TMR0_delayMS(20);
	LCD_sendCommand(0x02);						//initialization LCD in 4bit mode
	LCD_sendCommand(0x28);						//2 lines, 8x5 pixels in 4bit mode
	LCD_sendCommand(0x0C);						//display on cursor off
	LCD_sendCommand(0x06);						//auto increment cursor
	LCD_sendCommand(0x01);						//clear display
	LCD_sendCommand(0x80);						//cursor at home position
	#endif
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_sendCommand
 Input: u8 Cmnd
 Output: void
 Description: Function to send a Command to LCD through Data pins.
*/
void LCD_sendCommand ( u8 u8_a_cmnd )
{
	#if Mode == bit_8									//if LCD mode chosen in 8bit mode
	DIO_setPortValue(LCD_Data_Port,u8_a_cmnd);			//LCD Data Port = u8_a_cmnd
	DIO_write (LCD_cmmnd_Port, RS, LOW);				//RS = 0 Command register
	DIO_write (LCD_cmmnd_Port, RW, LOW);				//RW = 0 write operation
	DIO_write (LCD_cmmnd_Port, EN, HIGH);				//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_cmmnd_Port, EN, LOW);				//EN = 0 low pulse
	//_delay_ms(3);										//delay 3ms
	TMR0_delayMS(3);
	#elif Mode == bit_4									//if LCD mode chosen in 4bit mode
	DIO_setHigherNibble(LCD_Data_cmmnd_Port, u8_a_cmnd);//Sending upper nipple of u8_a_cmnd to LCD Data Port
	DIO_write (LCD_Data_cmmnd_Port, RS ,LOW);			//RS = 0 Command register
	DIO_write (LCD_Data_cmmnd_Port, RW, LOW);			//RW = 0 write operation
	DIO_write (LCD_Data_cmmnd_Port, EN, HIGH);			//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_Data_cmmnd_Port, EN ,LOW);			//EN = 0 low pulse
	//_delay_ms(2);										//delay 2ms
	TMR0_delayMS(2);
	DIO_setLowerNibble(LCD_Data_cmmnd_Port , u8_a_cmnd);//Sending lower nipple of u8_a_cmnd to LCD Data Port
	DIO_write (LCD_Data_cmmnd_Port, RS ,LOW);			//RS = 0 Command register
	DIO_write (LCD_Data_cmmnd_Port, RW ,LOW);			//RW = 0 write operation
	DIO_write (LCD_Data_cmmnd_Port, EN ,HIGH);			//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_Data_cmmnd_Port, EN ,LOW);			//EN = 0 low pulse
	//_delay_ms(3);										//delay 3ms
	TMR0_delayMS(3);
	#endif
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_sendCharacter
 Input: u8 Char
 Output: void
 Description: Function to send a Character to LCD through Data pins.
*/
void LCD_sendCharacter ( u8 u8_a_char )
{
	#if Mode == bit_8									//if LCD mode chosen in 8bit mode
	DIO_setPortValue(LCD_Data_Port,u8_a_char);			//LCD Data Port = char data
	DIO_write (LCD_cmmnd_Port, RS ,HIGH);				//RS = 1 Data register
	DIO_write (LCD_cmmnd_Port, RW ,LOW);				//RW = 0 write operation
	DIO_write (LCD_cmmnd_Port, EN ,HIGH);				//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_cmmnd_Port, EN ,LOW);				//EN = 0 low pulse
	//_delay_ms(1);										//delay 1ms
	TMR0_delayMS(1);
	#elif Mode == bit_4									//if LCD mode chosen in 4bit mode
	DIO_setHigherNibble(LCD_Data_cmmnd_Port, u8_a_char);//Sending upper nipple of char data to LCD Data Port
	DIO_write (LCD_Data_cmmnd_Port, RS ,HIGH);			//RS = 1 Data register
	DIO_write (LCD_Data_cmmnd_Port, RW ,LOW);			//RW = 0 write operation
	DIO_write (LCD_Data_cmmnd_Port, EN ,HIGH);			//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_Data_cmmnd_Port, EN ,LOW);			//EN = 0 low pulse
	//_delay_ms(2);										//delay 2ms
	TMR0_delayMS(2);
	DIO_setLowerNibble(LCD_Data_cmmnd_Port, u8_a_char);	//Sending lower nipple of char data to LCD Data Port
	DIO_write (LCD_Data_cmmnd_Port, RS ,HIGH);			//RS = 1 Data register
	DIO_write (LCD_Data_cmmnd_Port, RW ,LOW);			//RW = 0 write operation
	DIO_write (LCD_Data_cmmnd_Port, EN ,HIGH);			//EN = 1 high pulse
	//_delay_us(1);										//delay 1us is always more than 450ns
	TMR0_delayMS(1);
	DIO_write (LCD_Data_cmmnd_Port, EN ,LOW);			//EN = 0 low pulse
	//_delay_ms(2);										//delay 2ms
	TMR0_delayMS(2);
	#endif
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_clear
 Input: void
 Output: void
 Description: Function to clear LCD display screen in DDRAM.
*/
void LCD_clear ( void )
{
	/* Step 1: Send Display Clear control command */
	LCD_sendCommand(0x01);					//clear display
	/* Step 2: Delay more than 1.53 ms */
	//_delay_ms(2);							//delay 2ms
	TMR0_delayMS(2);
	LCD_sendCommand(0x80);					//cursor at home position
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_setCursor
 Input: u8 Row and u8 Column
 Output: void
 Description: Function to set the Address Counter (AC) of LCD to a certain location in DDRAM.
*/
void LCD_setCursor ( u8 u8_a_row, u8 u8_a_column )
{
	if (u8_a_row == 0 && u8_a_column<16)
	LCD_sendCommand((u8_a_column & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (u8_a_row == 1 && u8_a_column<16)
	LCD_sendCommand((u8_a_column & 0x0F)|0xC0);	/* Command of first row and required position<16 */	
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_sendString
 Input: Pointer to u8 String
 Output: void
 Description: Function to send an array of characters to LCD through Data pins (From CGROM to DDRAM).
*/
void LCD_sendString ( u8 *pu8_a_string )
{
	u16 i;
	
	for(i = 0; pu8_a_string[i]!= '\0'; i++)
	{
		LCD_sendCharacter(pu8_a_string[i]);
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_floatToString
 Input: f32 FloatValue
 Output: void
 Description: Function to send a float (one decimal) number (positive or negative) to LCD through Data pins (From CGROM to DDRAM).
*/
void LCD_floatToString (f32 f32_a_floatValue)
{
	u8 u8_l_pattern[10] , u8_l_tempRearrange, u8_l_digitCount=0,i,j;
	u32 u32_l_number;
	f32 temp_float = f32_a_floatValue * 10;
	u32_l_number = temp_float;
	
	for (i=0;u32_l_number>0;i++)
	{
		u8_l_pattern[i] = ((u32_l_number%10) +'0');
		u32_l_number/=10;
		u8_l_digitCount++;
	}
	
	for (j=0,i--;i>j;j++)
	{
		u8_l_tempRearrange = u8_l_pattern[i];
		u8_l_pattern[i] = u8_l_pattern[j];
		u8_l_pattern[j] = u8_l_tempRearrange;
		i--;
	}
	
	u8_l_pattern[u8_l_digitCount] =u8_l_pattern[u8_l_digitCount - 1];
	u8_l_pattern[u8_l_digitCount - 1] = '.';
	u8_l_pattern[u8_l_digitCount + 1] = '\0';
	LCD_sendString( u8_l_pattern );
}

/*******************************************************************************************************************************************************************/
/*
 Name: LCD_createCustomCharacter
 Input: Pointer to u8 Pattern and u8 Location
 Output: void
 Description: Function to send character (stored in array -Special Char- byte by byte) and store it in CGRAM, then display it on DDRAM (From CGRAM to DDRAM).
*/
void LCD_createCustomCharacter ( u8 *pu8_a_pattern, u8 u8_a_location )
{
	u8 i;
	LCD_sendCommand(( 0x40 + (u8_a_location*8)));
	
	for(i = 0; i<8; i++)
	{
		LCD_sendCharacter( pu8_a_pattern[i] );
	}
}

/*******************************************************************************************************************************************************************/