/*
 * dio_program.c
 *
 *     Created on: May 16, 2023
 *         Author: Mohamed Abdelsalam - https://github.com/m3adel
 *    Description: This file contains all Digital Input Output (DIO) functions' implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "dio_private.h"
#include "dio_config.h"
#include "dio_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_init
 Input: en PortNumber, en PinNumber, and en PinDirection
 Output: void
 Description: Function to initialize Pin direction.
*/
void DIO_init ( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, EN_DIO_PinDirection en_a_pinDirection )
{
	switch(en_a_portNumber)
	{
		case A:
		if (en_a_pinDirection == OUT)
			{
				SET_BIT( DIO_U8_DDRA_REG , en_a_pinNumber );    //Set Initial PortA Direction
			}
			else if (en_a_pinDirection == IN)
			{
				CLR_BIT( DIO_U8_DDRA_REG ,en_a_pinNumber);   //clear Initial PortA Direction
			}
		break;
		case B:
			if (en_a_pinDirection == OUT)
			{
				SET_BIT( DIO_U8_DDRB_REG , en_a_pinNumber );    //Set Initial PortB Direction
			}
			else if (en_a_pinDirection == IN)
			{
				CLR_BIT( DIO_U8_DDRB_REG , en_a_pinNumber );   //clear Initial PortB Direction
			}
		break;
		case C:
			if (en_a_pinDirection == OUT)
			{
				SET_BIT( DIO_U8_DDRC_REG , en_a_pinNumber );    //Set Initial PortC Direction
			}
			else if (en_a_pinDirection == IN)
			{
				CLR_BIT( DIO_U8_DDRC_REG  , en_a_pinNumber );   //clear Initial PortC Direction
			}
		break;
		case D:
			if (en_a_pinDirection == OUT)
			{
				SET_BIT( DIO_U8_DDRD_REG , en_a_pinNumber );    //Set Initial PortD Direction
			}
			else if (en_a_pinDirection == IN)
			{
				CLR_BIT( DIO_U8_DDRD_REG , en_a_pinNumber );   //clear Initial PortD Direction
			}
		break;
	}	
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_write
 Input: en PortNumber, en PinNumber, and en PinValue
 Output: void
 Description: Function to set Pin value.
*/
void DIO_write ( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, EN_DIO_PinValue en_a_pinValue )
{
	switch(en_a_portNumber)
	{
		case A:
			if (en_a_pinValue == HIGH)
			{
				SET_BIT( DIO_U8_PORTA_REG , en_a_pinNumber );	//Set value of pinNumber in PortA
			}
			else if (en_a_pinValue == LOW)
			{
				CLR_BIT( DIO_U8_PORTA_REG , en_a_pinNumber );	//clear value of pinNumber in PortA
			}
		break;
		case B:
			if (en_a_pinValue == HIGH)
			{
				SET_BIT( DIO_U8_PORTB_REG , en_a_pinNumber );	//Set value of pinNumber in PortB
			}
			else if (en_a_pinValue == LOW)
			{
				CLR_BIT( DIO_U8_PORTB_REG , en_a_pinNumber );	//clear value of pinNumber in PortB
			}
		break;
		case C:
			if (en_a_pinValue == HIGH)
			{
				SET_BIT( DIO_U8_PORTC_REG , en_a_pinNumber );	//Set value of pinNumber in PortC
			}
			else if (en_a_pinValue == LOW)
			{
				CLR_BIT( DIO_U8_PORTC_REG , en_a_pinNumber );	//clear value of pinNumber in PortC
			}
		break;
		case D:
			if (en_a_pinValue == HIGH)
			{
				SET_BIT( DIO_U8_PORTD_REG , en_a_pinNumber );	//Set value of pinNumber in PortD
			}
			else if (en_a_pinValue == LOW)
			{
				CLR_BIT( DIO_U8_PORTD_REG , en_a_pinNumber );	//clear value of pinNumber in PortD
			}
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_read
 Input: en PortNumber, en PinNumber, and Pointer to u8 ReturnedData
 Output: void
 Description: Function to get Pin value.
*/
void DIO_read ( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber, u8 *pu8_a_returnedData )
{	
	switch(en_a_portNumber)
	{
		case A:
			*pu8_a_returnedData = GET_BIT( DIO_U8_PINA_REG , en_a_pinNumber );
		break;
		case B:
			*pu8_a_returnedData = GET_BIT( DIO_U8_PINB_REG , en_a_pinNumber );
		break;
		case C:
			*pu8_a_returnedData = GET_BIT( DIO_U8_PINC_REG , en_a_pinNumber );
		break;
		case D:
			*pu8_a_returnedData = GET_BIT( DIO_U8_PIND_REG , en_a_pinNumber );
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_toggle
 Input: en portNumber and en PinNumber
 Output: void
 Description: Function to toggle Pin value.
*/
void DIO_toggle ( EN_DIO_PortNumber en_a_portNumber, EN_DIO_PinNumber en_a_pinNumber )
{
	switch(en_a_portNumber)
	{
		case A:
			TOG_BIT( DIO_U8_PORTA_REG , en_a_pinNumber );
		break;
		case B:
			TOG_BIT( DIO_U8_PORTB_REG , en_a_pinNumber );
		break;
		case C:
			TOG_BIT( DIO_U8_PORTC_REG , en_a_pinNumber );
		break;
		case D:
			TOG_BIT( DIO_U8_PORTD_REG , en_a_pinNumber );
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_setPortDirection
 Input: en PortNumber and en PortDirection
 Output: void
 Description: Function to set Port direction.
*/
void DIO_setPortDirection ( EN_DIO_PortNumber en_a_portNumber, u8 u8_a_portDirection )
{
	switch(en_a_portNumber)
	{
		case A:
			DIO_U8_DDRA_REG = u8_a_portDirection;
		break;
		case B:
			DIO_U8_DDRB_REG = u8_a_portDirection;
		break;
		case C:
			DIO_U8_DDRC_REG = u8_a_portDirection;
		break;
		case D:
			DIO_U8_DDRD_REG = u8_a_portDirection;
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_setPortValue
 Input: en PortNumber and u8 PortValue
 Output: void
 Description: Function to set Port value.
*/
void DIO_setPortValue ( EN_DIO_PortNumber en_a_portNumber, u8 u8_a_portValue )
{
	switch(en_a_portNumber)
	{
		case A:
			DIO_U8_PORTA_REG = u8_a_portValue;
		break;
		case B:
			DIO_U8_PORTB_REG = u8_a_portValue;
		break;
		case C:
			DIO_U8_PORTC_REG = u8_a_portValue;
		break;
		case D:
			DIO_U8_PORTD_REG = u8_a_portValue;
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_getPortValue
 Input: en PortNumber and Pointer to u8 ReturnedPortValue
 Output: void
 Description: Function to get Port value.
*/
void DIO_getPortValue ( EN_DIO_PortNumber en_a_portNumber, u8 *pu8_a_returnedPortValue )
{
	switch(en_a_portNumber)
	{
		case A:
			*pu8_a_returnedPortValue = DIO_U8_PINA_REG;
		break;
		case B:
			*pu8_a_returnedPortValue = DIO_U8_PINB_REG;
		break;
		case C:
			*pu8_a_returnedPortValue = DIO_U8_PINC_REG;
		break;
		case D:
			*pu8_a_returnedPortValue = DIO_U8_PIND_REG;
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_setHigherNibble
 Input: en portNumber and u8 Data
 Output: void
 Description: Function to set Higher Nibble of Port.
*/
void DIO_setHigherNibble ( EN_DIO_PortNumber en_a_portNumber, u8 u8_a_data )
{
	switch(en_a_portNumber)
	{
		case A:
			UPPER_NIBBLE( DIO_U8_PORTA_REG, u8_a_data );
		break;	
		case B:
			UPPER_NIBBLE( DIO_U8_PORTB_REG, u8_a_data );
		break;
		case C:	
			UPPER_NIBBLE( DIO_U8_PORTC_REG, u8_a_data );
		break;
		case D:
			UPPER_NIBBLE( DIO_U8_PORTD_REG, u8_a_data );
		break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: DIO_setLowerNibble
 Input: en PortNumber and u8 Data
 Output: void
 Description: Function to set LOWER Nibble of Port.
*/
void DIO_setLowerNibble ( EN_DIO_PortNumber en_a_portNumber, u8 u8_a_data )
{
	switch(en_a_portNumber)
	{
		case A:
			LOWER_NIBBLE( DIO_U8_PORTA_REG, u8_a_data );
		break;
		case B:
			LOWER_NIBBLE( DIO_U8_PORTB_REG, u8_a_data );
		break;
		case C:
			LOWER_NIBBLE( DIO_U8_PORTC_REG, u8_a_data );
		break;
		case D:
			LOWER_NIBBLE( DIO_U8_PORTD_REG, u8_a_data );
		break;
	}
}

/*******************************************************************************************************************************************************************/