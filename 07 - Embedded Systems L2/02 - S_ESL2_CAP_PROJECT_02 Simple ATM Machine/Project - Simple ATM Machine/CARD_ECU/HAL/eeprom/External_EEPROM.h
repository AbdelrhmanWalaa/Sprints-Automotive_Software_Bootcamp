/*
 * External_EEPROM.c
 * Created: 3/5/2023 3:40 AM
 * Author : Mahmoud Mowafey
 *
*/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

// #define EEPROM_ERROR 0
// #define EEPROM_SUCCESS 1

#include "../../MCAL/twi/twi.h"
#include "../../MCAL/timer/timer_interface.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"

typedef enum {
	EEPROM_ERROR,
	EEPROM_SUCCESS
}EN_eepromError_t;

#define EEPROM_24C256B
#define MANDATORY_SEQUENCE		 0xA0 
#define NEDDED_SHIFT_TIMES	     7
#ifdef EEPROM_24C16B
#define BYTE_ADDRESS			0x0311
#define MANDATORY_SEQUENCE	     0xA0
#define	PAGE_MASK			     0x0700
u8 EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData);
u8 EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData);
u8* EEPROM_readArray(u16 u16_l_byteAddress);
u8 EEPROM_writeArray(u16 u16_l_byteAddress, u8* pstr);
#else
#define BYTE_ADDRESS			 0x6D16
#define EEPROM_ADDRESS			 0xA0
#define MANDATORY_SEQUENCE		 0xA0   // 10100 
#define	PAGE_MASK_256			 0x00FF
#define NEDDED_SHIFT_TIMES_256	 7	
#define SHIFT_THE_FIRST_BYTE	 8	

u8 EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData);
u8 EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData);
u8* EEPROM_readArray(u16 u16_l_byteAddress);
u8 EEPROM_writeArray(u16 u16_l_byteAddress, u8* pstr);
#endif
void EEPROM_init(void);


#endif /* EXTERNAL_EEPROM_H_ */