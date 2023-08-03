/*
 * twi_cfg.h
 *
 * Created: 5/1/2023 11:18:25 AM
 *  Author: Mahmoud Mowafey
 */ 


#ifndef TWI_CFG_H_
#define TWI_CFG_H_

#include <math.h>

#ifndef F_CPU
#define F_CPU								1000000UL
#endif

#define SCL_CLK          400000U


//#define I2C_PRESCALER    ( ( ( TWI_U8_TWSR_REG & ( 1<< TWPS1 ) ) << 1 ) | ( TWI_U8_TWSR_REG & ( 1<< TWPS0 ) ) )

/*define the bit rate*/
//#define BIT_RATE  ( ( ( F_CPU / I2C_SCL ) - 16 ) / ( 2*pow( 4, I2C_PRESCALER ) ) )

#define BITRATE(TWI_U8_TWSR_REG)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWI_U8_TWSR_REG&((1<<TWPS0)|(1<<TWPS1)))))

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define TWPS0  0
#define TWPS1  1
//#define TWPS2  0
#define TWS3  3
#define TWS4  4
#define TWS5  5
#define TWS6  6
#define TWS7  7

#define TWIE   0
//#define TWPS1  1
#define TWEN   2
#define TWWC   3
#define TWSTO  4
#define TWSTA  5
#define TWEA   6
#define TWINT  7

/* define the TWI registers */
#define    TWI_U8_TWBR_REG        * ( ( volatile  u8 * ) 0x20 )
#define    TWI_U8_TWCR_REG        * ( ( volatile  u8 * ) 0x56 )
#define    TWI_U8_TWSR_REG        * ( ( volatile  u8 * ) 0x21 )
#define    TWI_U8_TWDR_REG        * ( ( volatile  u8 * ) 0x23 )
#define    TWI_U8_TWAR_REG        * ( ( volatile  u8 * ) 0x22 )

#endif /* TWI_CFG_H_ */