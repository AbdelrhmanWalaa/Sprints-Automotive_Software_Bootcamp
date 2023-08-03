/*
 * twi.c
 *
 * Created: 5/1/2023 4:23:43 PM
 *  Author: Mahmoud Mowafey
 */

#include "twi.h"

 /*
 * initializing the I2C protocol
 *
 * Parameters
 *       	[in] void
 * Return
 *   	    [out] void
 *
 */
void TWI_init(void)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=1Mhz */
    TWI_U8_TWBR_REG = 0x02;
    TWI_U8_TWSR_REG = 0x00;

    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWI_U8_TWAR_REG = 0x02;  

    TWI_U8_TWCR_REG = (1 << TWEN); /* enable TWI */
}

/*
* Send the start bit to start the I2C frame
*
* Parameters
*       	[in] void
* Return
*   	[out] void
*
*/
void TWI_start(void)
{
    /*
     * Clear the TWINT flag before sending the start bit TWINT=1
     * send the start bit by TWSTA=1
     * Enable TWI Module TWEN=1
     */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWI_U8_TWCR_REG Register (start bit is send successfully) */
    while (BIT_IS_CLEAR(TWI_U8_TWCR_REG, TWINT));
}

/*
* Send the stop bit to stop the I2C frame
*
* Parameters
*       	[in] void
* Return
*   	[out] void
*
*/
void TWI_stop(void)
{
    /*
     * Clear the TWINT flag before sending the stop bit TWINT=1
     * send the stop bit by TWSTO=1
     * Enable TWI Module TWEN=1
     */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*
* write one byte via I2C
*
* Parameters
*       	[in] data
* Return
*   	   [out] void
*
*/
void TWI_write(u8 data)
{
    /* Put data On TWI data Register */
    TWI_U8_TWDR_REG = data;
    /*
     * Clear the TWINT flag before sending the data TWINT=1
     * Enable TWI Module TWEN=1
     */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWI_U8_TWCR_REG Register(data is send successfully) */
    while (BIT_IS_CLEAR(TWI_U8_TWCR_REG, TWINT));
}

/*
* read one byte with send Ack via I2C
*
* Parameters
*       	[in] void
* Return
*   	Received byte
*
*/
u8 TWI_readWithAck(void)
{
    /*
     * Clear the TWINT flag before reading the data TWINT=1
     * Enable sending ACK after reading or receiving data TWEA=1
     * Enable TWI Module TWEN=1
     */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWI_U8_TWCR_REG Register (data received successfully) */
    while (BIT_IS_CLEAR(TWI_U8_TWCR_REG, TWINT));
    /* Read Data */
    return TWI_U8_TWDR_REG;
}

/*
* read one byte with send NAck via I2C
*
* Parameters
*       	[in] void
* Return
*   	Received byte
*
*/
u8 TWI_readWithNAck(void)
{
    /*
     * Clear the TWINT flag before reading the data TWINT=1
     * Enable TWI Module TWEN=1
     */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWI_U8_TWCR_REG Register (data received successfully) */
    while (BIT_IS_CLEAR(TWI_U8_TWCR_REG, TWINT));
    /* Read Data */
    return TWI_U8_TWDR_REG;
}

/*
* check the last operation via get the data of status register
*
* Parameters
*       	[in] void
* Return
*   	current status
*
*/
u8 TWI_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWI_U8_TWSR_REG & 0xF8;
    return status;
}
