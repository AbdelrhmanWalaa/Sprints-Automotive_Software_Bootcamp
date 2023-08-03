/*
 * mcu_config.h
 *
 *     Created on: Dec 19, 2022
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *	    Copyright: MIT License
 *
 *	               Copyright (c) Abdelrhman Walaa
 *
 *	               Permission is hereby granted, free of charge, to any person obtaining a copy
 *	               of this software and associated documentation files (the "Software"), to deal
 *	               in the Software without restriction, including without limitation the rights
 *	               to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	               copies of the Software, and to permit persons to whom the Software is
 *	               furnished to do so, subject to the following conditions:
 *
 *	               The above copyright notice and this permission notice shall be included in all
 *	               copies or substantial portions of the Software.
 *
 *	               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	               IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	               FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	               AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	               LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	               SOFTWARE.
 */

#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* MCU Configurations' Definitions */

#define MCU_U8_FCPU_1_MHZ		0
#define MCU_U8_FCPU_2_MHZ		1
#define MCU_U8_FCPU_4_MHZ		2
#define MCU_U8_FCPU_8_MHZ		3
#define MCU_U8_FCPU_16_MHZ		4
#define MCU_U8_FCPU_20_MHZ		5

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* MCU Configurations */

/* FCPU Select */
/* Options: MCU_U8_FCPU_1_MHZ
 *			MCU_U8_FCPU_2_MHZ
 *			MCU_U8_FCPU_4_MHZ
 *			MCU_U8_FCPU_8_MHZ
 *			MCU_U8_FCPU_16_MHZ
 *			MCU_U8_FCPU_20_MHZ
*/
#define MCU_U8_FCPU_SELECT		MCU_U8_FCPU_8_MHZ

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#if ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_1_MHZ )
	#define F_CPU	1000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_2_MHZ )
	#define F_CPU	2000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_4_MHZ )
	#define F_CPU	4000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_8_MHZ )
	#define F_CPU	8000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_16_MHZ )
	#define F_CPU	16000000UL
#elif ( MCU_U8_FCPU_SELECT == MCU_U8_FCPU_20_MHZ )
	#define F_CPU	20000000UL
#endif

#include <util/delay.h>

/*******************************************************************************************************************************************************************/

#endif /* MCU_CONFIG_H_ */