/*
 * btn_interface.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) functions' prototypes and definitions (Macros) to avoid magic numbers.
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

#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* BTN Includes */

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "gpio_interface.h"

/*******************************************************************************************************************************************************************/
/* BTN Macros */

/* BTN IDs Counted from 0 to 7 */
#define BTN_U8_0		    0
#define BTN_U8_1		    1
#define BTN_U8_2		    2
#define BTN_U8_3		    3
#define BTN_U8_4		    4
#define BTN_U8_5		    5
#define BTN_U8_6		    6
#define BTN_U8_7		    7

/* BTN Values Counted from 0 to 1 */
#define BTN_U8_LOW		  0
#define BTN_U8_HIGH		  1

/*******************************************************************************************************************************************************************/
/* BTN Error States */

typedef enum
{
	BTN_EN_NOK = 0,
	BTN_EN_OK
	
} BTN_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* BTN Functions' Prototypes */

/*
 Name: BTN_initialization
 Input: u8 BTNId
 Output: en Error or No Error
 Description: Function to initialize BTN peripheral, by initializing GPIO peripheral.
*/
extern BTN_enErrorState_t BTN_initialization( u8 u8_a_btnId );

/*
 Name: BTN_getBTNState
 Input: u8 BTNId and Pointer to u8 ReturnedBTNState
 Output: en Error or No Error
 Description: Function to get BTN state.
*/
extern BTN_enErrorState_t BTN_getBTNState( u8 u8_a_btnId, u8 *pu8_a_returnedBTNState );

/*******************************************************************************************************************************************************************/

#endif /* BTN_INTERFACE_H_ */
