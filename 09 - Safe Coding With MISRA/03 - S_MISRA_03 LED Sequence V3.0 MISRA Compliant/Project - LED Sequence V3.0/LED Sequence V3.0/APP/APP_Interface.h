/*
 * APP_Interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *	  Copyright: MIT License
 *
 *	             Copyright (c) Abdelrhman Walaa
 *
 *	             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	             of this software and associated documentation files (the "Software"), to deal
 *	             in the Software without restriction, including without limitation the rights
 *	             to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	             copies of the Software, and to permit persons to whom the Software is
 *	             furnished to do so, subject to the following conditions:
 *
 *	             The above copyright notice and this permission notice shall be included in all
 *	             copies or substantial portions of the Software.
 *
 *	             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	             FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	             SOFTWARE.
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"

/* MCAL */
#include "../MCAL/TMR_Driver/TMR_Interface.h"

/* HAL */
#include "../HAL/LED_Driver/LED_Interface.h"
#include "../HAL/BTN_Driver/BTN_Interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP BTN States */
#define APP_U8_BTN_PRESSED			0
#define APP_U8_BTN_NOT_PRESSED		1

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize the application.
*/
vd APP_vdInitialization( void );

/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start the program.
*/
vd APP_vdStartProgram( void );

/*
 Name: APP_vdChangeLEDsSequence
 Input: void
 Output: void
 Description: Function to change LEDs Sequence using EXI peripheral.
*/
vd APP_vdChangeLEDsSequence( void );

/*
 Name: APP_vdChangeBlinkMode
 Input: void
 Output: void
 Description: Function to change Blink Mode using EXI peripheral.
*/
vd APP_vdChangeBlinkMode( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */