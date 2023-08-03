
#ifndef I2C_H_
#define I2C_H_


#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"
#include "twi_cfg.h"


/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/*
* initializing the I2C protocol
*
* Parameters
*       	[in] void
* Return
*   	    [out] void
*
*/
void TWI_init(void);
/*
* Send the start bit to start the I2C frame
*
* Parameters
*       	[in] void
* Return
*   	[out] void
*
*/
void TWI_start(void);
/*
* Send the stop bit to stop the I2C frame
*
* Parameters
*       	[in] void
* Return
*   	[out] void
*
*/
void TWI_stop(void);
/*
* write one byte via I2C
*
* Parameters
*       	[in] data
* Return
*   	   [out] void
*
*/
void TWI_write(u8 data);

/*
* read one byte with send Ack via I2C
*
* Parameters
*       	[in] void
* Return
*   	Received byte
*
*/
u8 TWI_readWithAck(void); //read with send Ack

/*
* read one byte with send NAck via I2C
*
* Parameters
*       	[in] void
* Return
*   	Received byte
*
*/
u8 TWI_readWithNAck(void); //read without send Ack

/*
* check the last operation via get the data of status register
*
* Parameters
*       	[in] void
* Return
*   	current status
*
*/
u8 TWI_getStatus(void);


#endif /* I2C_H_ */
