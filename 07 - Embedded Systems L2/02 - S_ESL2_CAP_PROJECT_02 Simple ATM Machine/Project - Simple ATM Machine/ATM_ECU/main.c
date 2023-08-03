/*
 * main.c
 *
 *   Created on: May 1, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This application will handle transaction main flows:	
 *					1. After Reset
 *					   1.1. Welcome message is displayed for 1s "Welcome to ATM"
 *					   1.2. "Insert a Card" message is displayed in the first line
 *					   1.3. No action can be taken further and ll other input devices are blocked until a trigger signal came from the CARD ECU
 *					---------------------------------------------------------
 *					2. After a trigger signal is received from the CARD ECU
 *					   2.1. "Enter Your PIN" message is displayed in the first line
 *					   2.2. Waiting for the input from the keypad and type it in '****' format in the second line
 *					   2.3. PIN is only four numeric characters
 *					   2.4. Pressing Enter/Zero button for 2s will initiate a communication between the ATM ECU and CARD ECU to validate if the PIN is correct or not
 *					   2.5. If PIN is not correct, repeat for further 2 trial, and then if it is still wrong, sound the alarm and lock every input in the ATM, this blocking can be revealed by hard reset
 *					   2.6. If PIN is correct, then "Enter Amount" message is displayed in the first line and wait for the amount to be entered from the keypad and appeared in the second line
 *					   2.7. Amount is float string with max 4 integer digits and 2 decimal digits "0000.00"
 *					   2.8. You can enter '0' when pressing Enter/Zero for less than 2s
 *					   2.9. After entering the amount to withdraw, several checks on the database are done to finalize the transaction
 *						    2.9.1. Check if there is an account attached to this card
 *						    2.9.2. Check if the card is blocked or not
 *							2.9.3. Check if the amount is required exceeds daily limit or not
 *							2.9.4. Check for available amount
 *					   2.10. If one of the checks failed, a declined message will appear accordingly							
 *						    2.10.1. "This fraud card" - if the card PAN is not found - Alarm will be initiated
 *							2.10.2. "This card is stolen" - if the card is blocked - Alarm will be initiated
 *							2.10.3. "Maximum limit is exceeded" - if the required amount exceeds the maximum allowed limit
 *							2.10.4. "Insufficient fund" - if the balance is lower than the required amount
 *					   2.11. If all checks are passed then "Approved Transaction" message is displayed for 1s and the remaining balance is displayed for 1s "Remaining Balance: 0000.00"
 *					   2.12. After the checks are done and messages are displayed, display "Ejecting Card" message for 1s
 *					   2.13. Repeat from the after reset again
 *					---------------------------------------------------------
 *					3. Database
 *					   3.1. The database will be hard coded array of structures that contains (PAN, Account State (blocked/running), and balance)
 *					   3.2. The maximum allowed limit will be hard coded "5000.00"
 */


#include "main.h"

int main(void)
{
    /* App initialization */
	APP_initialization();

    /* App start program */
	APP_startProgram();
}
