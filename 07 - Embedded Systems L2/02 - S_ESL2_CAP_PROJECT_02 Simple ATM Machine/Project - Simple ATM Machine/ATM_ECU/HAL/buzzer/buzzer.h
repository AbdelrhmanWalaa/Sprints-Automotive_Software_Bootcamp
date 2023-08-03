/*
 * File   : buzzer.h
 *
 * Author: Tarek Gohry
 * 
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/dio/dio_interface.h"


/* Macros */
/* LCD_DATA_PORT Options
 * PORT_A: 0
 * PORT_B: 1
 * PORT_C: 2
 * PORT_D: 3
 * */
#define BUZ_PORT 1
#define BUZ_PIN 3

/* Prototypes */

/**
* @brief initialize the buzzer pin
*
* @return void
*/
void BUZZER_init();

/**
* @brief turn the buzzer on
*
* @return void
*/
void BUZZER_on();

/**
* @brief turn the buzzer off
*
* @return void
*/
void BUZZER_off();

#endif /* BUZZER_H_ */