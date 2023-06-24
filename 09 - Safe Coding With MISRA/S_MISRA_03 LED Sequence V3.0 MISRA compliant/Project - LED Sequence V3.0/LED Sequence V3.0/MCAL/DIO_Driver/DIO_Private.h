/*
 * DIO_Private.h
 *
 *     Created on: Mar 31, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Digital Input Output (DIO) registers' locations and other private Macros.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 *		Copyright: MIT License
 *
 *		           Copyright (c) Abdelrhman Walaa
 *
 *		           Permission is hereby granted, free of charge, to any person obtaining a copy
 *		           of this software and associated documentation files (the "Software"), to deal
 *		           in the Software without restriction, including without limitation the rights
 *		           to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *		           copies of the Software, and to permit persons to whom the Software is
 *		           furnished to do so, subject to the following conditions:
 *
 *		           The above copyright notice and this permission notice shall be included in all
 *		           copies or substantial portions of the Software.
 *
 *		           THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *		           SOFTWARE.
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* DIO Registers' Locations */

#define DIO_U8_PORTA_REG	    *( ( volatile u8 * ) 0x3B )
#define DIO_U8_DDRA_REG		    *( ( volatile u8 * ) 0x3A )
#define DIO_U8_PINA_REG		    *( ( volatile u8 * ) 0x39 )

#define DIO_U8_PORTB_REG	    *( ( volatile u8 * ) 0x38 )
#define DIO_U8_DDRB_REG		    *( ( volatile u8 * ) 0x37 )
#define DIO_U8_PINB_REG		    *( ( volatile u8 * ) 0x36 )

#define DIO_U8_PORTC_REG	    *( ( volatile u8 * ) 0x35 )
#define DIO_U8_DDRC_REG		    *( ( volatile u8 * ) 0x34 )
#define DIO_U8_PINC_REG		    *( ( volatile u8 * ) 0x33 )

#define DIO_U8_PORTD_REG	    *( ( volatile u8 * ) 0x32 )
#define DIO_U8_DDRD_REG		    *( ( volatile u8 * ) 0x31 )
#define DIO_U8_PIND_REG		    *( ( volatile u8 * ) 0x30 )

/*******************************************************************************************************************************************************************/

/* Concatenate Functions Like Macros */
#define DIO_FN_CONC( P7, P6, P5, P4, P3, P2, P1, P0 )			DIO_FN_CONC_HELP( P7, P6, P5, P4, P3, P2, P1, P0 )
#define DIO_FN_CONC_HELP( P7, P6, P5, P4, P3, P2, P1, P0 )		0b##P7##P6##P5##P4##P3##P2##P1##P0

/*******************************************************************************************************************************************************************/

#endif /* DIO_PRIVATE_H_ */