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
#define BUZ_PORT PORT_B
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