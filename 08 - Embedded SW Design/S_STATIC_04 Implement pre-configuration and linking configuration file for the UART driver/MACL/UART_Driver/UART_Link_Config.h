/*
 * UART_Link_Config.h
 *
 *     Created on: May 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) linking configurations, through which user can configure during using the UART peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* UART Link Configurations */

/* UART Modes */
typedef enum
{
    UART_EN_ASYNC_MODE,
    UART_EN_SYNC_MODE
} UART_EN_MODE;

/* UART Transmission Speeds */
typedef enum
{
    UART_EN_NORMAL_SPEED,
    UART_EN_DOUBLE_SPEED
} UART_EN_SPEED;

/* UART Multi-processor Communication Mode */
typedef enum
{
    UART_EN_MPCM_DISABLED,
    UART_EN_MPCM_ENABLED
} UART_EN_MPCM;

/* UART Receiver RX */
typedef enum
{
    UART_EN_RX_DISABLED,
    UART_EN_RX_ENABLED
} UART_EN_RX_ENABLE;

/* UART Transmitter TX */
typedef enum
{
    UART_EN_TX_DISABLED,
    UART_EN_TX_ENABLED
} UART_EN_TX_ENABLE;

/* UART RX Complete Interrupt */
typedef enum
{
    UART_EN_RX_INT_DISABLED,
    UART_EN_RX_INT_ENABLED
} UART_EN_RX_INT_ENABLE;

/* TX Complete Interrupt */
typedef enum
{
    UART_EN_TX_INT_DISABLED,
    UART_EN_TX_INT_ENABLED
} UART_EN_TX_INT_ENABLE;

/* UART Data Register Empty Interrupt */
typedef enum
{
    UART_EN_UDRE_INT_DISABLED,
    UART_EN_UDRE_INT_ENABLED
} UART_EN_UDRE_INT_ENABLE;

/* UART Parity Modes */
typedef enum
{
    UART_EN_PARITY_MODE_DISABLED,
    UART_EN_EVEN_PARITY_MODE,
    UART_EN_ODD_PARITY_MODE
} UART_EN_PARITY_MODE;

/* UART Stop Bit(s) */
typedef enum
{
    UART_EN_ONE_STOP_BIT,
    UART_EN_TWO_STOP_BIT
} UART_EN_STOP_BIT_SELECT;

/* UART Data Bits */
typedef enum
{
    UART_EN_5_BITS_DATA,
    UART_EN_6_BITS_DATA,
    UART_EN_7_BITS_DATA,
    UART_EN_8_BITS_DATA,
    UART_EN_9_BITS_DATA
} UART_EN_DATA_BITS_SELECT;

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
} UART_EN_BAUD_RATE_SELECT;

typedef struct
{
    UART_EN_MODE UART_stMode;
    UART_EN_SPEED UART_stSpeed;
    UART_EN_MPCM UART_stMPCM;
    UART_EN_RX_ENABLE UART_stRXEnable;
    UART_EN_TX_ENABLE UART_stTXEnable;
    UART_EN_RX_INT_ENABLE UART_RXInterruptEnable;
    UART_EN_TX_INT_ENABLE UART_TXInterruptEnable;
    UART_EN_UDRE_INT_ENABLE UART_UDREInterruptEnable;
    UART_EN_PARITY_MODE UART_stParityMode;
    UART_EN_STOP_BIT_SELECT UART_stStopBit;
    UART_EN_DATA_BITS_SELECT UART_stDataBits;
    UART_EN_BAUD_RATE_SELECT UART_stBaudRate;
} UART_ST_LINK_CONFIG;

/* End of Link Configurations */

/*******************************************************************************************************************************************************************/

#endif /* UART_CONFIG_H_ */