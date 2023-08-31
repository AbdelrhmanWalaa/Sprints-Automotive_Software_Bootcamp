/*
 * uart_private.h
 *
 *     Created on: May 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) registers' locations and description.
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

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* UART Registers' Locations */

#define	UART_U8_UDR_REG		    *( ( volatile  u8 * ) 0x2C )

#define	UART_U8_UCSRA_REG		*( ( volatile  u8 * ) 0x2B )
#define	UART_U8_UCSRB_REG		*( ( volatile  u8 * ) 0x2A )
#define	UART_U8_UCSRC_REG		*( ( volatile  u8 * ) 0x40 )

#define	UART_U8_UBRRL_REG		*( ( volatile  u8 * ) 0x29 )
#define	UART_U8_UBRRH_REG		*( ( volatile  u8 * ) 0x40 )

/*******************************************************************************************************************************************************************/
/* UART Registers' Description */

/* UART Control and Status Register A - UCSRA */
/* Bit 7 - RXC: UART Receive Complete */
#define UART_U8_RXC_BIT		    7
/* Bit 6 – TXC: UART Transmit Complete */
#define UART_U8_TXC_BIT	    	6
/* Bit 5 - UDRE: UART Data Register Empty */
#define UART_U8_UDRE_BIT    	5
/* Bit 4 - FE: Frame Error */
#define UART_U8_FE_BIT	    	4
/* Bit 3 - DOR: Data OverRun */
#define UART_U8_DOR_BIT	    	3
/* Bit 2 - PE: Parity Error */
#define UART_U8_PE_BIT	    	2
/* Bit 1 - U2X: Double the USART Transmission Speed */
#define UART_U8_U2X_BIT	    	1
/* Bit 0 - MPCM: Multi-processor Communication Mode */
#define UART_U8_MPCM_BIT	    0
/* End of UCSRA Register */

/* UART Control and Status Register B - UCSRB */
/* Bit 7 - RXCIE: RX Complete Interrupt Enable */
#define UART_U8_RXCIE_BIT		7
/* Bit 6 - TXCIE: TX Complete Interrupt Enable */
#define UART_U8_TXCIE_BIT		6
/* Bit 5 - UDRIE: UART Data Register Empty Interrupt Enable */
#define UART_U8_UDRIE_BIT		5
/* Bit 4 - RXEN: Receiver Enable */
#define UART_U8_RXEN_BIT		4
/* Bit 3 - TXEN: Transmitter Enable */
#define UART_U8_TXEN_BIT		3
/* Bit 2 - UCSZ2: Character Size */
#define UART_U8_UCSZ2_BIT		2
/* Bit 1 - RXB8: Receive Data Bit 8 */
#define UART_U8_RXB8_BIT		1
/* Bit 0 - TXB8: Transmit Data Bit 8 */
#define UART_U8_TXB8_BIT		0
/* End of UCSRB Register */

/* UART Control and Status Register C - UCSRC */
/* Bit 7 - URSEL: Register Select */
#define UART_U8_URSEL_BIT		7
/* Bit 6 - UMSEL: USART Mode Select */
#define UART_U8_UMSEL_BIT		6
/* Bit 5:4 - UPM1:0: Parity Mode */
#define UART_U8_UPM1_BIT		5
#define UART_U8_UPM0_BIT		4
/* Bit 3 - USBS: Stop Bit Select */
#define UART_U8_USBS_BIT		3
/* Bit 2:1 - UCSZ1:0: Character Size */
#define UART_U8_UCSZ1_BIT		2
#define UART_U8_UCSZ0_BIT		1
/* Bit 0 - UCPOL: Clock Polarity */
#define UART_U8_UCPOL_BIT		0
/* End of UCSRC Register */

/*******************************************************************************************************************************************************************/
/* UART Private Macros */

/* UART Commonly Used Oscillator Frequencies */
/*             Baud Rates:            */	/*  2.4k |  4.8k |  9.6k | 14.4k | 19.2k | 28.8k | 38.4k | 57.8k */   /*  FCPU  */
#define UART_AU16_NORMAL_SPEED_BAUD_RATES  { {  25   ,  12   ,  6    ,   3   ,   2   ,   1   ,   1   ,   0   },   /*  1 MHz */ \
											 {  51   ,  25   ,  12   ,   8   ,   6   ,   3   ,   2   ,   1   },   /*  2 MHz */ \
											 {  103  ,  51   ,  25   ,   16  ,   12  ,   8   ,   6   ,   3   },   /*  4 MHz */ \
											 {  207  ,  103  ,  51   ,   34  ,   25  ,   16  ,   12  ,   8   },   /*  8 MHz */ \
											 {  416  ,  207  ,  103  ,   68  ,   51  ,   34  ,   25  ,   16  },   /* 16 MHz */ \
											 {  520  ,  259  ,  129  ,   86  ,   64  ,   42  ,   32  ,   21  } }  /* 20 MHz */

/*             Baud Rates:            */    /*  2.4k |  4.8k |  9.6k | 14.4k | 19.2k | 28.8k | 38.4k | 57.8k */   /*  FCPU  */
#define UART_AU16_DOUBLE_SPEED_BAUD_RATES  { {  51   ,  25   ,  12   ,   8   ,   6   ,   3   ,   2   ,   1   },   /*  1 MHz */ \
											 {  103  ,  51   ,  25   ,   16  ,   12  ,   8   ,   6   ,   3   },   /*  2 MHz */ \
											 {  207  ,  103  ,  51   ,   34  ,   25  ,   16  ,   12  ,   8   },   /*  4 MHz */ \
											 {  416  ,  207  ,  103  ,   68  ,   51  ,   34  ,   25  ,   16  },   /*  8 MHz */ \
											 {  832  ,  416  ,  207  ,   138 ,   103 ,   68  ,   51  ,   34  },   /* 16 MHz */ \
											 {  1041 ,  520  ,  259  ,   173 ,   129 ,   86  ,   64  ,   42  } }  /* 20 MHz */ 

/*******************************************************************************************************************************************************************/

#endif /* UART_PRIVATE_H_ */