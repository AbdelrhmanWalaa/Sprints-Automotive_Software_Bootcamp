/*
 * MBTN_Interface.h
 *
 *   Created on: 3 May 2023
 *       Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *  Description: This file contains all Multifunctional Button (MBTN) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

/* BTN Includes */

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/timer/timer_interface.h"

/* Macros */
#define MAX_PIN_NUMBER  7
#define MAX_PORT_NUMBER 3

/* Delays */
#define MBTN_DELAY_LONG_PRESS    2000
#define MBTN_DELAY_BTN_POLL      50

/* Button States */
// button was pressed and released shortly
#define MBTN_STATE_RELEASED 0
// button was long pressed and released
#define MBTN_STATE_LONG_RELEASED 2
// button isn't pressed
#define MBTN_STATE_NOT_PRESSED 3

/* MBTN Functions' Prototypes */

/**
 * @brief Initializes a push button connected to a specific pin in a specific port.
 *
 * This function initializes a push button connected to a specific pin in a specific port.
 * It configures the pin as input, enables the pull-up resistor, and initializes the timer.
 *
 * @param [in]u8_a_pinNumber The number of the pin to which the button is connected.
 * @param [in]en_a_portNumber The port to which the button is connected.
 *
 * @return Returns the state of the initialization operation. STD_OK if successful and STD_NOK if failed.
 */
u8 MBTN_init(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber);

/**
 * @brief This function gets the state of a mechanical button (pressed, not pressed, long press)
 *
 * @param [in]u8_a_pinNumber The pin number of the button
 * @param [in]en_a_portNumber The port number of the button
 * @param [out]u8Ptr_a_returnedBtnState A pointer to the variable to store the button state (pressed, not pressed, long press)
 *
 * @return Returns the status of the function (STD_OK, STD_NOK)
 */
u8 MBTN_getBtnState(u8 u8_a_btnId, EN_DIO_PORT_T en_a_portNumber, u8 *u8ptr_a_returnedBtnState);

#endif /* BTN_INTERFACE_H_ */