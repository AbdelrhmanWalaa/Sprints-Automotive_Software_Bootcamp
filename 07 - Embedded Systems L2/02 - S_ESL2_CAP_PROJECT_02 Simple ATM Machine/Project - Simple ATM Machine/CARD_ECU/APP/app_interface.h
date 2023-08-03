/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"
#include <string.h>

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/timer/timer_interface.h"
#include "../MCAL/twi/twi.h"
#include "../MCAL/spi/spi_interface.h"
#include "../MCAL/uart/uart_interface.h"

/* HAL */
#include "../HAL/eeprom/External_EEPROM.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_U8_PROG_MODE		0
#define APP_U8_USER_MODE		1
#define APP_U8_CHECK_MODE		2

/* APP Flag States */
#define APP_U8_FLAG_DOWN		0
#define APP_U8_FLAG_UP			1

/* APP PAN & PIN Addresses */
#define APP_U16_PAN_ADDRESS		0x0000
#define APP_U16_PIN_ADDRESS		0x0018

/* APP Data (PAN & PIN) in Memory (EEPROM) States */
#define APP_U8_DATA_NOT_FOUND	0
#define APP_U8_DATA_FOUND		1

/* APP ATM/Master COMM COMMANDS */
#define APP_CMD_ATM_PIN_READY           0xC1 // ATM sends PIN is ready
#define APP_CMD_ATM_PAN_REQ             0xC3 // ATM requests PAN
#define APP_CMD_ATM_PAN_LEN_REQ         0xC4 // ATM requests PAN length
#define APP_CMD_ATM_PAN_INDEX_0_REQ     0xA0 // ATM requests PAN digit with index 0
#define APP_CMD_ATM_PAN_OK              0xF0 // ATM receives full PAN digits

/* APP CARD/Slave COMM RESPONSES */
#define APP_RESP_CARD_ACK				0x1A // CARD responses with Acknowledge
#define APP_RESP_CARD_PIN_INDEX_0_REQ	0xA0 // CARD requests PIN digit with index 0
#define APP_RESP_CARD_PIN_OK			0xF0 // CARD responses with PIN verification OK, PIN matches
#define APP_RESP_CARD_PIN_WRONG			0xF5 // CARD responses with PIN verification Wrong, PIN doesn't match

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization   ( void );
void APP_startProgram	  ( void );

u8   APP_checkDataInMemory( void );
void APP_checkUserInput	  ( void );

void APP_programmerMode   ( void );

void APP_receivePANFromTerminal( void );
void APP_receivePINFromTerminal( void );

void APP_userMode	      ( void );

u8	 APP_receivePINFromATM( void );
void APP_sendPANToATM	  ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */