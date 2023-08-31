/*
 * uart_linkConfig.h
 *
 *     Created on: May 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) linking configurations, through which user can configure during using the UART peripheral.
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

#ifndef UART_LINKCONFIG_H_
#define UART_LINKCONFIG_H_

/*******************************************************************************************************************************************************************/
/* UART Link Configurations */

/* UART Modes */
typedef enum
{
    UART_EN_ASYNC_MODE,
    UART_EN_SYNC_MODE

} UART_enMode_t;

/* UART Transmission Speeds */
typedef enum
{
    UART_EN_NORMAL_SPEED,
    UART_EN_DOUBLE_SPEED

} UART_enSpeed_t;

/* UART Multi-processor Communication Mode */
typedef enum
{
    UART_EN_MPCM_DISABLED,
    UART_EN_MPCM_ENABLED

} UART_enMPCM_t;

/* UART Receiver RX */
typedef enum
{
    UART_EN_RX_DISABLED,
    UART_EN_RX_ENABLED

} UART_enRXEnable_t;

/* UART Transmitter TX */
typedef enum
{
    UART_EN_TX_DISABLED,
    UART_EN_TX_ENABLED

} UART_enTXEnable_t;

/* UART RX Complete Interrupt */
typedef enum
{
    UART_EN_RX_INT_DISABLED,
    UART_EN_RX_INT_ENABLED

} UART_enRXInterruptEnable_t;

/* TX Complete Interrupt */
typedef enum
{
    UART_EN_TX_INT_DISABLED,
    UART_EN_TX_INT_ENABLED

} UART_enTXInterruptEnable_t;

/* UART Data Register Empty Interrupt */
typedef enum
{
    UART_EN_UDRE_INT_DISABLED,
    UART_EN_UDRE_INT_ENABLED

} UART_enUDREInterruptEnable_t;

/* UART Parity Modes */
typedef enum
{
    UART_EN_PARITY_MODE_DISABLED,
    UART_EN_EVEN_PARITY_MODE,
    UART_EN_ODD_PARITY_MODE

} UART_enParityMode_t;

/* UART Stop Bit(s) */
typedef enum
{
    UART_EN_ONE_STOP_BIT,
    UART_EN_TWO_STOP_BIT

} UART_enStopBitsSelect_t;

/* UART Data Bits */
typedef enum
{
    UART_EN_5_DATA_BITS,
    UART_EN_6_DATA_BITS,
    UART_EN_7_DATA_BITS,
    UART_EN_8_DATA_BITS,
    UART_EN_9_DATA_BITS

} UART_enDataBitsSelect_t;

/* UART Baud Rates ( Symbol Per Second -> Bit Per Second ( bps ) ) */
typedef enum
{
    UART_EN_BAUD_RATE_2400,
    UART_EN_BAUD_RATE_4800,
    UART_EN_BAUD_RATE_9600,
    UART_EN_BAUD_RATE_14400,
    UART_EN_BAUD_RATE_19200,
    UART_EN_BAUD_RATE_28800,
    UART_EN_BAUD_RATE_38400,
    UART_EN_BAUD_RATE_57600
	
} UART_enBaudRateSelect_t;

/* UART Linking Configurations Structure */
typedef struct
{
    UART_enMode_t				 en_g_mode;
    UART_enSpeed_t				 en_g_speed;
    UART_enMPCM_t				 en_g_MPCM;
    UART_enRXEnable_t			 en_g_RXEnable;
    UART_enTXEnable_t			 en_g_TXEnable;
    UART_enRXInterruptEnable_t	 en_g_RXInterruptEnable;
    UART_enTXInterruptEnable_t	 en_g_TXInterruptEnable;
    UART_enUDREInterruptEnable_t en_g_UDREInterruptEnable;
    UART_enParityMode_t			 en_g_parityMode;
    UART_enStopBitsSelect_t		 en_g_stopBit;
    UART_enDataBitsSelect_t		 en_g_dataBits;
    UART_enBaudRateSelect_t		 en_g_baudRate;

} UART_stLinkConfig_t;

/* End of Link Configurations */

/*******************************************************************************************************************************************************************/

#endif /* UART_LINKCONFIG_H_ */