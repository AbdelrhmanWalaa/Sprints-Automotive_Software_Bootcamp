/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/* APP Includes */
/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* MCAL */
#include "../MCAL/timer/timer_interface.h"
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/spi/spi_interface.h"
#include "../MCAL/exi/exi_interface.h"

/* HAL */
#include "../HAL/lcd/lcd_interface.h"
#include "../HAL/kpd/kpd_interface.h"
#include "../HAL/buzzer/buzzer.h"
#include "../HAL/mbtn/mbtn_interface.h"

/* APP Macros */
#define APP_ACTION_SHOW_CURSOR LCD_changeCursor(1);
#define APP_ACTION_HIDE_CURSOR LCD_changeCursor(0);
#define APP_MAX_DB_SIZE 20
#define APP_MAX_TRIALS  3
#define APP_PIN_DIGITS  4
#define APP_PIN_CHAR     '*'
#define APP_ZERO_CHAR    '0'


/* APP Delays */
#define APP_DELAY_WELCOME_MSG   1000
#define APP_DELAY_ERROR_MSG     1000
#define APP_DELAY_APPROVED_MSG  1000
#define APP_DELAY_SPI           50


/* APP STATES */
#define APP_STATE_LAUNCH        0
#define APP_STATE_INSERT_PIN    1
#define APP_STATE_TRANSACTING   2
#define APP_STATE_LOCKED        51
#define APP_STATE_TEST     250

/* APP ATM/Master COMM COMMANDS */
#define APP_CMD_ATM_PIN_READY           0xC1 // ATM sends PIN is ready
#define APP_CMD_ATM_WAIT_FOR_CARD_RESP  0xC2 // ATM waits for CARD response
#define APP_CMD_ATM_PAN_REQ             0xC3 // ATM requests PAN
#define APP_CMD_ATM_PAN_LEN_REQ         0xC4 // ATM requests PAN length
#define APP_CMD_ATM_PAN_INDEX_0_REQ     0xA0 // ATM requests PAN digit with index 0
#define APP_CMD_ATM_PAN_OK              0xF0 // ATM receives full PAN digits

/* APP CARD/Slave COMM RESPONSES */
#define APP_RESP_CARD_ACK				0x1A // CARD responses with Acknowledge
#define APP_RESP_CARD_PIN_INDEX_0_REQ	0xA0 // CARD requests PIN digit with index 0
#define APP_RESP_CARD_PIN_INDEX_1_REQ	0xA1 // CARD requests PIN digit with index 1
#define APP_RESP_CARD_PIN_INDEX_2_REQ	0xA2 // CARD requests PIN digit with index 2
#define APP_RESP_CARD_PIN_INDEX_3_REQ	0xA3 // CARD requests PIN digit with index 3
#define APP_RESP_CARD_PIN_OK			0xF0 // CARD responses with PIN verification OK, PIN matches
#define APP_RESP_CARD_PIN_WRONG			0xF5 // CARD responses with PIN verification Wrong, PIN doesn't match

/* APP Button */
#define APP_BTN_ENTER_ZERO 2        // PIN 2
#define APP_BTN_ENTER_ZERO_PORT 1   // PORT B

/* APP Actions */

/* APP Typedefs */
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    f32 f32_balance;
    EN_accountState_t en_state;
    u8 u8_primaryAccountNumber[20];
}ST_accountsDB_t;



/* APP Functions' Prototypes */


/**
 * @brief Initializes the application by initializing the MCAL and HAL components.
 *
 * @details This function initializes the external interrupt, SPI, timer0, buzzer, button, keypad, and LCD.
 * It also clears the LCD's display and switches to the entry point state.
 *
 * @return void
 */
void APP_initialization(void);

/**
 * @brief Start the application program flow for ATM
 *
 * This function starts the application program and enters an infinite loop that continuously polls
 * the application state and executes the corresponding actions according to the current state.
 *
 * @return void
 */
void APP_startProgram(void);

/**
 * @brief Used to switch between app states to initialize standard UI elements before main app flow (loop)
 *
 * @param [in]u8_a_state state to set (APP_STATE_LAUNCH, APP_STATE_...)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state);

/**
 * Ran when an INT0 interrupt is fired / Card inserted, switches app state to INSERT_PIN
 */
void APP_trigger(void);

#endif /* APP_INTERFACE_H_ */