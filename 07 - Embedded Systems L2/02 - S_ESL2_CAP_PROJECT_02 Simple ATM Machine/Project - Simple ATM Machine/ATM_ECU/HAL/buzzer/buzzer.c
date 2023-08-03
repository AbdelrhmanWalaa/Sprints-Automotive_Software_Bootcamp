/*
 * File   : buzzer.h
 *
 * Author: Tarek Gohry
 * 
 */ 

#include "buzzer.h"

/**
* @brief initialize the buzzer pin
*
* @return void
*/
void BUZZER_init()
{
	DIO_init(BUZ_PIN, BUZ_PORT, DIO_OUT);
}

/**
* @brief turn the buzzer on
*
* @return void
*/
void BUZZER_on()
{
	DIO_write(BUZ_PIN, BUZ_PORT, DIO_U8_PIN_HIGH);
}

/**
* @brief turn the buzzer off
*
* @return void
*/
void BUZZER_off()
{
	DIO_write(BUZ_PIN, BUZ_PORT, DIO_U8_PIN_LOW);
}
