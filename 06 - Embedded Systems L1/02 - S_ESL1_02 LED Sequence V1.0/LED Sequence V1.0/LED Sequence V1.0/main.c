/*
 * main.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This Application uses ATmega32 to control some LEDs lighting sequence according to button pressing.
 */

/* APP */
#include "APP/APP_Interface.h"

int main(void)
{
	APP_vdInitialization();
	APP_vdStartProgram();
}