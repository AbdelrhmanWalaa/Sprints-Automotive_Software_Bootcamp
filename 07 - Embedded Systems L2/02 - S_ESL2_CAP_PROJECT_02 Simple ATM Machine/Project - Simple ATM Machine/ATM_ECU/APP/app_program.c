/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hossam Elwahsh - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_interface.h"

/* Declaration and Initialization */
/* Accounts Database */
ST_accountsDB_t accountsDB[APP_MAX_DB_SIZE] =                                /* Visa */
        /* Balance   |  State |        PAN        */  /* Balance    |  State |        PAN       */
        {{9999.99f,    BLOCKED, "4728459258966333"},
         {5805.5f,     BLOCKED, "4946084897338284"},
         {9360.12f,   RUNNING, "4728451059691228"},
         {1600.58f,   RUNNING, "4573762093153876"},
         {520.9f,      RUNNING, "4127856791257426"},
         {6900.33f,    RUNNING, "4946099660091878"},
         {5000.0f,  RUNNING, "4946069587908256"},
         {2560.0f,    RUNNING, "4946085117749481"},
         {8950.0f,   RUNNING, "4946099683908835"},
         {2000.0f,   RUNNING, "4834699064563433"},

                                /* MasterCard */
         {6860.3f,    RUNNING, "5183150660610263"},
         {5000.3f,     RUNNING, "5400829062340903"},
         {1800.0f,  RUNNING, "5191786640828580"},
         {4080.0f,    RUNNING, "5367052744350494"},
         {1890.45f,   RUNNING, "5248692364161088"},
         {7751.0f,  RUNNING, "5419558003040483"},
         {3026.0f,  RUNNING, "5116136307216426"},
         {9362.0f,  RUNNING, "5335847432506029"},
         {1066.0f, RUNNING, "5424438206113309"},
         {1824.0f,     RUNNING, "5264166325336492"}};

/* Global variables */
f32 f32_g_maxAllowedDailyLimit = 5000.0f; // Maximum allowed daily transaction limit
u8 u8_g_appState = APP_STATE_LAUNCH; // Current App State
u8 str_g_currentPAN[20] = {'\0'};

/**
 * @brief Initializes the application by initializing the MCAL and HAL components.
 *
 * @details This function initializes the external interrupt, SPI, timer0, buzzer, button, keypad, and LCD.
 * It also clears the LCD's display and switches to the entry point state.
 *
 * @return void
 */
void APP_initialization(void) {

    /** MCAL Initialization */
    // Init and enable external Interrupt
    EXI_enablePIE(MASTER_REQ_RECEIVE_INT, MASTER_REQ_RECEIVE_SENSE);
    EXI_intSetCallBack(MASTER_REQ_RECEIVE_INT, APP_trigger);

    SPI_init();  // Init SPI
    TIMER_timer0NormalModeInit(DISABLED); // Init timer0

    /** HAL Initialization */
    BUZZER_init();  // Init Buzzer
    MBTN_init(APP_BTN_ENTER_ZERO, APP_BTN_ENTER_ZERO_PORT);  // Init Btn (0/Enter)
    KPD_initKPD();  // Init Keypad
    LCD_init();     // Init LCD
    LCD_clear();    // Clear LCD's display

    APP_switchState(u8_g_appState); // switch to entry point state
}

/**
 * @brief Start the application program flow for ATM
 *
 * This function starts the application program and enters an infinite loop that continuously polls
 * the application state and executes the corresponding actions according to the current state.
 *
 * @return void
 */
void APP_startProgram(void) {
    while (1) {
        switch (u8_g_appState) {
            case APP_STATE_TEST:
                LCD_sendString((u8 *) "STARTING...");
                LCD_setCursor(LCD_LINE1, LCD_COL0);

                LCD_sendString((u8 *) "Sending: ");

                // ss enable
//                DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);
                u8 count = 0;
                char buffer[5];
                while (1) {
                    SPI_transceiver(count);
                    sprintf(buffer, "%d", count);
                    LCD_setCursor(LCD_LINE1, LCD_COL10);
                    LCD_sendString((u8 *) buffer);
                    count++;
                    TIMER_delay_ms(APP_DELAY_SPI);
                    if (count == 8) {
                        count = 0;
                        SPI_stop();
                    }
                }

                /* Receiver test slave code */
                /*u8 count = SPI_U8_DUMMY_VAL;

                SPI_init();

                while(1)
                {
                    count = SPI_transceiver(count);
                }*/

                break;
            case APP_STATE_LAUNCH:
                // ignored
                break;
            case APP_STATE_INSERT_PIN:

                LCD_clear(); // Clear LCD
                u8 u8_l_trials = 0; // Init PIN trials
                u8 u8_l_currentPin[APP_PIN_DIGITS+1]; // Init array buffer for PIN digits + a null character
                u8 currentPosition; // Current cursor position to track PIN digits entry
                while (u8_l_trials < APP_MAX_TRIALS) {
                    currentPosition = 0; // Current cursor position to track PIN digits entry

                    LCD_clear(); // Clear LCD
                    LCD_setCursor(LCD_LINE0, LCD_COL1);   // Center of first line for the next msg
                    LCD_sendString((u8 *) "Enter Your PIN");    // Display "Enter Your PIN" message and wait
                    LCD_setCursor(LCD_LINE1, LCD_COL6);   // Center of second line for the next msg
                    LCD_sendString((u8 *) "____");              // Display Placeholders for PIN
                    LCD_setCursor(LCD_LINE1, LCD_COL6);   // first pin digit position
                    APP_ACTION_SHOW_CURSOR

                    // Poll inputs
                    u8 u8_l_btn = KPD_U8_KEY_NOT_PRESSED;
                    /* Wait for 4 digits pin input */
                    while (currentPosition < APP_PIN_DIGITS) {
                        // keypad poll
                        KPD_getPressedKey(&u8_l_btn);
                        if (u8_l_btn != KPD_U8_KEY_NOT_PRESSED) {
                            u8_l_currentPin[currentPosition] = u8_l_btn;
                            LCD_sendChar(APP_PIN_CHAR);
                            currentPosition++;
                        }
                        // Check Enter/Zero button short/long press
                        u8 u8_l_btnState = MBTN_STATE_NOT_PRESSED;
                        MBTN_getBtnState(APP_BTN_ENTER_ZERO, APP_BTN_ENTER_ZERO_PORT, &u8_l_btnState);
                        if(u8_l_btnState == MBTN_STATE_RELEASED)
                        {
                            u8_l_currentPin[currentPosition] = APP_ZERO_CHAR;
                            LCD_sendChar(APP_PIN_CHAR);
                            currentPosition++;
                        }
                    }
                    APP_ACTION_HIDE_CURSOR

                    // wait for Enter Button Press (long press for 2 or more seconds)
                    u8 u8_l_btnState = MBTN_STATE_NOT_PRESSED;

                    // block until long press
                    while(u8_l_btnState != MBTN_STATE_LONG_RELEASED)
                    {
                        // Wait until long press
                        MBTN_getBtnState(APP_BTN_ENTER_ZERO, APP_BTN_ENTER_ZERO_PORT, &u8_l_btnState);
                    }

                    // long press was detected, resuming

                    // verify PIN
                    LCD_clear();
                    
                    LCD_setCursor(LCD_LINE0, LCD_COL2);
                    LCD_sendString((u8 *) "Please wait\nVerifying");
                    // to bypass verification enable this break
                    // break;

                    // PIN ready ACK from slave
                    u8 u8_l_response = 0;
                    while(u8_l_response != APP_RESP_CARD_ACK)
                    {
                        u8_l_response = SPI_transceiver(APP_CMD_ATM_PIN_READY);
                        TIMER_delay_ms(APP_DELAY_SPI);
                    }

                    u8_l_response = 0;
                    u8 u8_l_cursor = LCD_COL9;
                    while (u8_l_response != APP_RESP_CARD_PIN_OK && u8_l_response != APP_RESP_CARD_PIN_WRONG) {

                        // progress bar UI
                        //region Progress bar UI
                        LCD_setCursor(LCD_LINE1, u8_l_cursor);
                        LCD_sendChar('.');
                        if(u8_l_cursor == LCD_COL15) {
                            u8_l_cursor = LCD_COL8;
                            LCD_setCursor(LCD_LINE1, LCD_COL9);
                            LCD_sendString((u8 *)"        ");
                        }
                        u8_l_cursor++;
                        //endregion

                        u8_l_response = SPI_transceiver(APP_CMD_ATM_WAIT_FOR_CARD_RESP);
                        switch (u8_l_response) {
                            case APP_RESP_CARD_PIN_INDEX_0_REQ:
                                SPI_transceiver(u8_l_currentPin[0]);
                                break;
                            case APP_RESP_CARD_PIN_INDEX_1_REQ:
                                SPI_transceiver(u8_l_currentPin[1]);
                                break;
                            case APP_RESP_CARD_PIN_INDEX_2_REQ:
                                SPI_transceiver(u8_l_currentPin[2]);
                                break;
                            case APP_RESP_CARD_PIN_INDEX_3_REQ:
                                SPI_transceiver(u8_l_currentPin[3]);
                                break;
                            default:
                                // ignore
                                break;
                        }
                        TIMER_delay_ms(APP_DELAY_SPI);
                    }
                    if (u8_l_response == APP_RESP_CARD_PIN_OK) {
                        break;
                    } else if (u8_l_response == APP_RESP_CARD_PIN_WRONG) {
                        u8_l_trials++;

                        LCD_clear(); // clear LCD, reset cursor
                        u8 str_l_wrongPinMessage[16]; // string buffer for wrong pin message UI
                        sprintf((char *) str_l_wrongPinMessage, "Wrong PIN (%d/3)", u8_l_trials); // convert trials to text
                        LCD_sendString(str_l_wrongPinMessage); // show wrong msg on LCD

                        TIMER_delay_ms(APP_DELAY_ERROR_MSG);
                    }
                }

                if (u8_l_trials >= 3) // PIN WRONG 3 times
                { // Wrong PIN for 3 u8_l_trials lock the system
                    APP_switchState(APP_STATE_LOCKED);
                    break; // case APP_STATE_INSERT_PIN Break
                }

                // PIN OK, fetch account data (PAN)
                LCD_clear();
                LCD_sendString((u8 *) "Retrieving\naccount data...");
                u8 u8_l_response = 0;
                // Start PAN request SPI comm and wait for ACK
                while(u8_l_response != APP_RESP_CARD_ACK)
                {
                    u8_l_response = SPI_transceiver(APP_CMD_ATM_PAN_REQ);
                    TIMER_delay_ms(APP_DELAY_SPI);
                }


                // Request PAN length
                u8 u8_l_panLength = 0;
                while(u8_l_panLength < 16 || u8_l_panLength > 19) // Valid PAN Length
                {
                    u8_l_panLength = SPI_transceiver(APP_CMD_ATM_PAN_LEN_REQ);
                    TIMER_delay_ms(APP_DELAY_SPI);
                }

                // Fetch All PAN digits (with validation)
                u8 u8_l_currentPanIndex = 0;
                u8 u8_l_cursor = LCD_COL12;
                while(u8_l_currentPanIndex < u8_l_panLength)
                {
                    // progress bar UI
                    //region Progress bar UI
                    LCD_setCursor(LCD_LINE1, u8_l_cursor);
                    LCD_sendChar('.');
                    if(u8_l_cursor == LCD_COL15) {
                        u8_l_cursor = LCD_COL11;
                        LCD_setCursor(LCD_LINE1, LCD_COL12);
                        LCD_sendString((u8 *)"    ");
                    }
                    u8_l_cursor++;
                    //endregion

                    u8_l_response = SPI_transceiver(APP_CMD_ATM_PAN_INDEX_0_REQ + u8_l_currentPanIndex);
                    if(u8_l_response >= '0' && u8_l_response <= '9') // valid ASCII number
                    {
                        str_g_currentPAN[u8_l_currentPanIndex] = u8_l_response;
                        u8_l_currentPanIndex++;
                    }
                    TIMER_delay_ms(APP_DELAY_SPI);
                }

                str_g_currentPAN[u8_l_currentPanIndex] = '\0'; // null-terminating character

                u8_l_response = 0;
                while(u8_l_response != APP_RESP_CARD_ACK)
                {
                    u8_l_response = SPI_transceiver(APP_CMD_ATM_PAN_OK);
                    TIMER_delay_ms(APP_DELAY_SPI);
                }

                APP_switchState(APP_STATE_TRANSACTING);
                break; // case APP_STATE_INSERT_PIN Break
            case APP_STATE_TRANSACTING:
                APP_ACTION_SHOW_CURSOR

                LCD_setCursor(LCD_LINE1, LCD_COL4);
                u8 u8_l_currentPosition = 0; // LCD digits position tracking

                u8 str_l_transactionAmount[8] = "0000.00";

                u8 u8_l_btnValue = KPD_U8_KEY_NOT_PRESSED;

                /* Wait for 6 digits pin input */
                while (u8_l_currentPosition < 7) {
                    KPD_getPressedKey(&u8_l_btnValue); // Poll keypad
                    if (u8_l_btnValue != KPD_U8_KEY_NOT_PRESSED) { // a keypad key was pressed

                        LCD_sendChar(u8_l_btnValue); // display pressed key digit on LCD
                        str_l_transactionAmount[u8_l_currentPosition] = u8_l_btnValue; // save digit value

                        if (u8_l_currentPosition == 3) {
                            // skip decimal point placeholder on LCD
                            u8_l_currentPosition += 2;
                            LCD_setCursor(LCD_LINE1, LCD_COL9);
                        } else u8_l_currentPosition++;
                    }

                    /** Enter/Zero button poll */
                    u8 u8_l_btnState = MBTN_STATE_NOT_PRESSED;
                    MBTN_getBtnState(APP_BTN_ENTER_ZERO,APP_BTN_ENTER_ZERO_PORT, &u8_l_btnState);
                    if(u8_l_btnState == MBTN_STATE_RELEASED)
                    {
                        // short press
                        LCD_sendChar(APP_ZERO_CHAR); // display pressed key digit on LCD
                        str_l_transactionAmount[u8_l_currentPosition] = APP_ZERO_CHAR; // save digit value

                        if (u8_l_currentPosition == 3) {
                            // skip decimal point placeholder on LCD
                            u8_l_currentPosition += 2;
                            LCD_setCursor(LCD_LINE1, LCD_COL9);
                        } else u8_l_currentPosition++;
                    }
                        // break out of amount entry if long press (ENTER) was pressed -> continue trx flow
                    else if(u8_l_btnState == MBTN_STATE_LONG_RELEASED && (strcmp((char *) str_l_transactionAmount, "0000.00") != 0)) break;

                    /* End Enter/Zero button poll */
                    if(u8_l_currentPosition == 7) // repeat from start if reached end of number placeholders
                    {
                        u8_l_currentPosition = 0;
                        LCD_setCursor(LCD_LINE1, LCD_COL4);
                    }
                }
                APP_ACTION_HIDE_CURSOR
                KPD_disableKPD(); // Disable keypad

                LCD_clear();
                LCD_setCursor(LCD_LINE0, LCD_COL1);
                LCD_sendString((u8 *) "Please wait...");
                TIMER_delay_ms(700);

                // Checks
                // 1. Account exists
                /* Loop: Until Account is found or until the end of accountsDB */
                u8 u8_l_accountExists = 0;
                u8 u8_l_accountIndex = 0;

                for (u8 i = 0; i < APP_MAX_DB_SIZE; i++) {
                    /* Check 1: Account exists */
                    if (!strcmp((char *) str_g_currentPAN, (char *) accountsDB[i].u8_primaryAccountNumber)) {
                        /* Account is Found! */
                        u8_l_accountExists = 1;
                        u8_l_accountIndex = i;
                        break;
                    }
                }

                LCD_shiftClear();
                if (!u8_l_accountExists) {
                    LCD_setCursor(LCD_LINE0, LCD_COL0);
                    LCD_sendString((u8 *) "   Fraud Card   ");
                    APP_switchState(APP_STATE_LOCKED);
                    break;
                }

                // Check 2. card is running or blocked
                if (accountsDB[u8_l_accountIndex].en_state == BLOCKED) {
                    LCD_setCursor(LCD_LINE0, LCD_COL0);
                    LCD_sendString((u8 *) "  Stolen Card   ");
                    APP_switchState(APP_STATE_LOCKED);
                    break;
                }

                // transaction amount in float
                f32 f32_l_transactionAmount = atof((char *) str_l_transactionAmount);

                // Check 3. Amount Exceeds daily limit ?
                if(f32_l_transactionAmount > f32_g_maxAllowedDailyLimit)
                {
                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL0);
                    LCD_sendString((u8 *) "Max limit is\nexceeded");
                    TIMER_delay_ms(APP_DELAY_ERROR_MSG);
                    APP_switchState(APP_STATE_TRANSACTING); // re-ask for amount to withdraw
                    break;
                }

                // Check 4. Check for account balance covering required amount
                if(f32_l_transactionAmount > accountsDB[u8_l_accountIndex].f32_balance)
                {
                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL0);
                    LCD_sendString((u8 *) "Insufficient\nFunds");
                    TIMER_delay_ms(APP_DELAY_ERROR_MSG);    // Delay
                    APP_switchState(APP_STATE_TRANSACTING); // re-ask for amount to withdraw
                    break;
                }else{
                    // update balance in DB
                    accountsDB[u8_l_accountIndex].f32_balance -= f32_l_transactionAmount;

                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL4); // Center of first line for the next msg
                    LCD_sendString((u8 *) "Approved");
                    LCD_setCursor(LCD_LINE1, LCD_COL2); // Center of second line for the next msg
                    LCD_sendString((u8 *) "Transaction");
                    TIMER_delay_ms(APP_DELAY_APPROVED_MSG);

                    u8 str_l_newBalanceMsg[17];
                    // convert new balance to string
                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL2); // Center of first line for the next msg

                    sprintf(
                            (char*)str_l_newBalanceMsg,
                            "New Balance:\n    %ld.%d",
                            (long)accountsDB[u8_l_accountIndex].f32_balance,
                            (u8)((accountsDB[u8_l_accountIndex].f32_balance - (long)accountsDB[u8_l_accountIndex].f32_balance)*100.0f)
                    );
                    LCD_sendString((u8 *) str_l_newBalanceMsg);   // Show new balance on LCD
                    TIMER_delay_ms(APP_DELAY_APPROVED_MSG);     // Delay

                    // Show "Ejecting Card" for one second
                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL4); // Center of  first line for the next msg
                    LCD_sendString((u8 *)"Ejecting");
                    LCD_setCursor(LCD_LINE1, LCD_COL6); // Center of second line for the next msg
                    LCD_sendString((u8 *)"Card");
                    TIMER_delay_ms(APP_DELAY_APPROVED_MSG); // Delay
                    APP_switchState(APP_STATE_LAUNCH); // Repeat from after reset
                }
                break;
            default:
                // Ignored
                break;
        }
    }
}


/**
 * @brief Used to switch between app states to initialize standard UI elements before main app flow (loop)
 *
 * @param [in]u8_a_state state to set (APP_STATE_LAUNCH, APP_STATE_...)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state) {
    switch (u8_a_state) {
        case APP_STATE_LAUNCH:
            LCD_clear();
            KPD_enableKPD();
            LCD_setCursor(LCD_LINE0, LCD_COL1);
            LCD_sendString((u8 *) "Welcome to ATM");    // Display welcome message on LCD for 1 second
            LCD_setCursor(LCD_LINE1, LCD_COL1);
            LCD_sendString((u8 *) "Hacker  Kermit");  // Display team name
            TIMER_delay_ms(APP_DELAY_WELCOME_MSG);
            LCD_clear();
            LCD_setCursor(LCD_LINE0, LCD_COL2);
            LCD_sendString((u8 *) "Insert Card");     // Display Insert card message and wait
            break;
        case APP_STATE_TRANSACTING:
            KPD_enableKPD();   // Enable keypad
            LCD_clear();
            LCD_setCursor(LCD_LINE0, LCD_COL2);  // Center of first line for the next msg
            LCD_sendString((u8 *) "Enter Amount");      // Display "Enter Amount" message and wait
            LCD_setCursor(LCD_LINE1, LCD_COL4);  // Center of first line for the next msg
            LCD_sendString((u8 *) "0000.00");           // Display Placeholders for Amount

            break;
        case APP_STATE_LOCKED:
            LCD_setCursor(LCD_LINE1, LCD_COL0);
            LCD_sendString((u8 *) "System Locked ");
            LCD_sendChar(LCD_CUSTOMCHAR_LOC0);
            KPD_disableKPD();   // Disable keypad
            BUZZER_on();        // Alarm ON
        default:
            // ignored
            break;
    }
    u8_g_appState = u8_a_state; // globally set new app state
}

/**
 * Ran when an INT0 interrupt is fired / Card inserted, switches app state to INSERT_PIN
 */
void APP_trigger(void) {
    // receive SPI data
    if (u8_g_appState == APP_STATE_LAUNCH) u8_g_appState = APP_STATE_INSERT_PIN;
}