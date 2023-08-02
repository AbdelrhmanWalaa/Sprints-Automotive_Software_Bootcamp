/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit Team
 *  Description: This file contains all Application (APP) functions' implementation.
 */ 

/* APP */
#include "app_interface.h"

/* ***************************************************************************************************************/
/* Declaration and Initialization */

/* Global variable to store appMode */
extern u8 u8_g_timeOut;
u16 u16_g_desiredTemperatureValue = DEFAULT_TEMP;
u8 u8_g_currentAppState = STATE_ADJUST;

/**
 * @brief Initializes the application and its components.
 *
 * This function initializes the timers, temperature sensor, buzzer, keypad,
 * LCD and other components required for the application to function. It also
 * displays a welcome message and sets the initial temperature to 20 degrees
 * Celsius. Finally, it switches the application state to adjust the AC control
 * procedure.
 */
void APP_initialization( void )
{
	/* Initializing timers */
	TIMER_timer0NormalModeInit( DISABLED );
	TIMER_timer2NormalModeInit( ENABLED );
    /* Initialize temperature sensor */
	TEMPSENSOR_init();
    /* Initialize Buzzer */
    BUZZER_init();
    /* Initialize Keypad */
    KPD_initKPD();
    /* initialize LCD */
 	LCD_init();
     /* Clear LCD */
    LCD_clear();
    // Jump to 1st line Center
	LCD_setCursor(0,4);
    // Show welcome Message
    LCD_sendString((u8 *)"Welcome\n Hacker  Kermit");
    TIMER_delay_ms(WELCOME_MSG_DELAY);
    // Fancy shift right clear LCD
	LCD_shiftClear();
    // Show default temperature
    LCD_sendString((u8 *)"   AC Control\ndefault temp: 20");
    TIMER_delay_ms(WELCOME_MSG_DELAY);
    // Normal LCD Immediate clear
	LCD_clear();

    APP_switchState(STATE_ADJUST); // start adjust AC Control procedure
}


/**
 * @brief Start the AC Control program.
 *
 * This function contains the main program loop that controls the AC system.
 * It switches between two states, adjust and running, and performs different tasks
 * in each state based on user input and temperature readings.
 *
 * @return void.
 */
void APP_startProgram  ( void )
{
    while (1)
    {
        switch (u8_g_currentAppState) {

            case STATE_ADJUST:
                // run the adjust temp screen and algorithm
                {
                    /* Check if keypad keys are pressed */
                    u8 u8_l_pressedkey = KPD_U8_KEY_NOT_PRESSED;

                    KPD_getPressedKey(&u8_l_pressedkey);

                    if(u8_l_pressedkey == BTN_INCREMENT || u8_l_pressedkey == BTN_DECREMENT)
                    {
                        // reset timeout after 10 seconds if no key is pressed
                        TIMER_intDelay_ms(TIMEOUT_MS_DELAY);
                        // increment or decrement desired temperature w.r.t which button was pressed
                        APP_changeTemp(u8_l_pressedkey == BTN_INCREMENT ? ACTION_INCREMENT : ACTION_DECREMENT);
                    }
                    else if(u8_l_pressedkey == BTN_SET)
                    {
                        // cancel timeout check (timer)
                        TIMER_timer2Stop();
                        // switch app to running state
                        APP_switchState(STATE_RUNNING);
                    }

                    if(u8_g_timeOut == 1) {

                        // reset timeout flag
                        u8_g_timeOut = 0;
                        // use default temperature
                        u16_g_desiredTemperatureValue = DEFAULT_TEMP;

                        // switch app to running state
                        APP_switchState(STATE_RUNNING);
                    }
                }
                break;

            case STATE_RUNNING:
            {
                // read current temperature from sensor
                u16 u16_l_currentTemp = DEFAULT_TEMP;
                TEMPSENSOR_getValue(&u16_l_currentTemp);

                // update current reading on LCD
                LCD_setCursor(LCD_LINE1, LCD_COL14);

				//edit the LCD_sendString
                u8 u8_l_currentTempStr[5];
                sprintf((char *)u8_l_currentTempStr, "%d", u16_l_currentTemp);
                LCD_sendString(u8_l_currentTempStr);

                /* Check if keypad keys are pressed */
                u8 u8_l_pressedkey = KPD_U8_KEY_NOT_PRESSED;

                KPD_getPressedKey(&u8_l_pressedkey);

                if(u8_l_pressedkey == BTN_RESET_TO_DEFAULT)
                {
                    // reset app to default
                    APP_resetToDefault();
                    continue;
                }
                else if(u8_l_pressedkey == BTN_ADJUST)
                {
                    // return back to adjust mode
                    APP_switchState(STATE_ADJUST);
                    continue;
                }

                // Check if current temperature is higher than desired
                // in a real world situation we should turn the compressor ON to cool the air
                if(u16_l_currentTemp > u16_g_desiredTemperatureValue)
                {
                    // show bell/buzzer icon
                    LCD_setCursor(LCD_LINE0, LCD_COL15); // last char in first line
                    LCD_sendChar(LCD_CUSTOMCHAR_LOC0); // show bell/buzzer icon on LCD

                    // turn on the buzzer sound
                    BUZZER_on();
                }else{
                    // clear bell/buzzer icon
                    LCD_setCursor(LCD_LINE0, LCD_COL15); // last char in first line
                    LCD_sendChar(' '); // clear buzzer icon

                    // turn buzzer off
                    BUZZER_off();
                }
            }
                break;


            default:
                //
                break;
        }
    }
}

/**
 * @brief Switch between AC states "running" and "adjust"
 *
 * @param [in]u8_a_state state to set (STATE_RUNNING/STATE_ADJUST)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state){
    switch (u8_a_state) {
        case  STATE_RUNNING:
        {
            // disable Inc/Dec/Set keys
            KPD_disableKPD();

            // turn buzzer off
            BUZZER_off();

            // Clear LCD
            LCD_clear();

            /* Initialize constant "running" state UI text */
            // set cursor to start of second line
            LCD_setCursor(LCD_LINE1, LCD_COL0);
            LCD_sendString( (u8 *) "Current temp: ");
            u8_g_currentAppState = u8_a_state;
            break;
        }
        case STATE_ADJUST:
        {
            // disable Inc/Dec/Set keys
            KPD_enableKPD();

            // turn buzzer off
            BUZZER_off();

            LCD_clear();
            LCD_sendString((u8 *) "Please choose\nthe required tmp");
            TIMER_delay_ms(REQ_TMP_MSG_DELAY);
            LCD_clear();
            LCD_sendString((u8 *) "    Controls\n1(+) 2(-) 3(set)");
            TIMER_delay_ms(CONTROLS_MSG_DELAY);
            LCD_shiftClear();

            u8 tempVisualizer[17];
            sprintf((char *)tempVisualizer, "Min:18 %d Max:35", u16_g_desiredTemperatureValue);
            LCD_sendString(tempVisualizer);

            // Next Line
            LCD_setCursor(LCD_LINE1,LCD_COL0);

            u8 str_l_tempPattern[17] = "";
            // -1 to compensate LCD size only allowing 16 chars because the range of our AC temperature
            // is from MINIMUM_TEMP (18) to MAXIMUM_TEMP (35) which is 17 steps
            memset(str_l_tempPattern, '|', u16_g_desiredTemperatureValue - MINIMUM_TEMP);
            LCD_sendString(str_l_tempPattern);

            /* timout 10 seconds */
            TIMER_intDelay_ms(TIMEOUT_MS_DELAY);    // timeout after 10 seconds if no key is pressed
            u8_g_currentAppState = u8_a_state;
            break;
        }
        default:
            // ignored
            break;
    }
}

/**
 * @brief Updates the desired temperature value based on user input.
 *
 * @param [in]u8_a_action The action to perform on the temperature value (ACTION_INCREMENT/ACTION_DECREMENT).
 *
 * This function updates the UI temperature value and progress bar based on the provided action.
 * If the new desired temperature value is out of range (MAXIMUM_TEMP or MINIMUM_TEMP), the function will
 * buzz the user and revert the value back to the original.
 */
void APP_changeTemp(u8 u8_a_action)
{
    /* Update UI temp value */
    if (
            !((u16_g_desiredTemperatureValue == MAXIMUM_TEMP && u8_a_action == ACTION_INCREMENT) ||
             (u16_g_desiredTemperatureValue == MINIMUM_TEMP && u8_a_action == ACTION_DECREMENT))
        ){

        /* Update UI temperature progress bar */
        if(u8_a_action == ACTION_INCREMENT)
        {
            /* Corner Cases */
            // incrementing from before max, because LCD has only 16 chars we can't show a step
            if(u16_g_desiredTemperatureValue == (MAXIMUM_TEMP - 1))
            {
                LCD_setCursor(LCD_LINE1, LCD_COL15);
                LCD_sendChar(0xFF); // black square to visualize MAX/END
            }
            else if(u16_g_desiredTemperatureValue == (MINIMUM_TEMP)){
                LCD_setCursor(LCD_LINE1, LCD_COL0);
                LCD_sendChar('|');
            }
            else{
                LCD_setCursor(LCD_LINE1, u16_g_desiredTemperatureValue - MINIMUM_TEMP);
                LCD_sendChar('|');
            }

            u16_g_desiredTemperatureValue++; // increment temperature

        } else if (u8_a_action == ACTION_DECREMENT)
        {
            /* Corner Cases */
            // decrementing from maximum temp
            if(u16_g_desiredTemperatureValue == (MINIMUM_TEMP + 1))
            {
                LCD_setCursor(LCD_LINE1, LCD_COL0);
                LCD_sendChar(0xFF); // black square to visualize MAX/END
            }
            else if(u16_g_desiredTemperatureValue == MAXIMUM_TEMP)
            {
                LCD_setCursor(LCD_LINE1, LCD_COL15);
                LCD_sendChar('|'); // regular step to indictate before MAX temp
            } else{
                LCD_setCursor(LCD_LINE1, u16_g_desiredTemperatureValue - MINIMUM_TEMP - 1);
                LCD_sendChar(' ');
            }

            u16_g_desiredTemperatureValue--; // decrement temperature
        }

        // Update UI with new desired temp
        LCD_setCursor(LCD_LINE0, LCD_COL7);
        u8 u8_l_currentTempStr[3];
        sprintf((char *)u8_l_currentTempStr, "%d", u16_g_desiredTemperatureValue);
        LCD_sendString(u8_l_currentTempStr);

    } else{
        // bad entry, buzz user
        BUZZER_on();
        TIMER_delay_ms(WRONG_ENTRY_BUZZ_DELAY);
        BUZZER_off();
    }
}

/**
 * @brief Resets the desired temperature value to the default temperature.
 */
void APP_resetToDefault()
{
    u16_g_desiredTemperatureValue = DEFAULT_TEMP;
    LCD_clear();
    LCD_sendString((u8 *) "Reset to default   Temp: 20");
    TIMER_delay_ms(RESET_MSG_DELAY);
    APP_switchState(STATE_RUNNING);
}

