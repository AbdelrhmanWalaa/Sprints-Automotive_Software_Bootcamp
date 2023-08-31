/*
 * main.c
 *
 *   Created on: Apr 1, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: Embedded C application controlling a four-driving wheel robot, moving it in a rectangular shape, 
 *               and avoid any obstacles (any object) in front.
 */

/* Main */
#include "main.h"

int main(void)
{
	APP_initialization();
	APP_startProgram();
	
	return 0;
}