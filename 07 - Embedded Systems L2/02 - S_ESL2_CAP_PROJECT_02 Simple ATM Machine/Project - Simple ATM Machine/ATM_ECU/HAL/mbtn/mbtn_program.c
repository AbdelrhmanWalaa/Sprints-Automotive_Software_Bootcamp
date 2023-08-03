/*
 * BTN_Program.c
 *
 *   Created on: 3 May 2023
 *       Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *  Description: This file contains all Multifunctional Button (MBTN) functions' implementation.
 */

/* HAL */
#include "mbtn_interface.h"

/* Private Macros */
#define MBTN_STATE_PRESSED  1

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
u8 MBTN_init(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber) {
    if (DIO_init(u8_a_pinNumber, en_a_portNumber, DIO_IN) == DIO_OK) {
        // init timer
        TIMER_timer0NormalModeInit(DISABLED);
        // enable pull up resistor
        DIO_write(u8_a_pinNumber, en_a_portNumber, DIO_U8_PIN_HIGH);
        return STD_OK;
    }
    return STD_NOK;
}

/**
 * @brief This function gets the state of a mechanical button (pressed, not pressed, long press)
 *
 * @param [in]u8_a_pinNumber The pin number of the button
 * @param [in]en_a_portNumber The port number of the button
 * @param [out]u8Ptr_a_returnedBtnState A pointer to the variable to store the button state (pressed, not pressed, long press)
 *
 * @return Returns the status of the function (STD_OK, STD_NOK)
 */
u8 MBTN_getBtnState(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber, u8 * u8Ptr_a_returnedBtnState) {
    /* Define local variable to set the error state = OK */

    /* Check 1: MBTN is in the valid range, and Pointer is not equal to NULL */
    if ((u8_a_pinNumber <= MAX_PIN_NUMBER) && (en_a_portNumber <= MAX_PORT_NUMBER) && (u8Ptr_a_returnedBtnState != NULL)) {

        /** Button Poll */
        u8 u8_l_mBtnState = MBTN_STATE_RELEASED;
        u16 u16_l_elapsedTime = 0;

        DIO_read(u8_a_pinNumber, en_a_portNumber, &u8_l_mBtnState);
        if(u8_l_mBtnState == MBTN_STATE_PRESSED)
        {
            while(u8_l_mBtnState != MBTN_STATE_RELEASED)
            {
                TIMER_delay_ms(MBTN_DELAY_BTN_POLL); // wait 50ms
                u16_l_elapsedTime += MBTN_DELAY_BTN_POLL;
                DIO_read(u8_a_pinNumber, en_a_portNumber, &u8_l_mBtnState);
                if(u8_l_mBtnState == MBTN_STATE_RELEASED && u16_l_elapsedTime < MBTN_DELAY_LONG_PRESS)
                {
                    // short press
                    *u8Ptr_a_returnedBtnState = MBTN_STATE_RELEASED;
                }
                if(u16_l_elapsedTime > MBTN_DELAY_LONG_PRESS) // long press
                {
                    // long press
                    *u8Ptr_a_returnedBtnState = MBTN_STATE_LONG_RELEASED;
                    break; // break from state check loop
                }
            }
        }else{
            // not pressed at all
            *u8Ptr_a_returnedBtnState = MBTN_STATE_NOT_PRESSED;
        }

        return STD_OK;
    }
    else {
        /* Update error state = NOK, wrong BTNId or Pointer is NULL! */
        return STD_NOK;
    }
}
