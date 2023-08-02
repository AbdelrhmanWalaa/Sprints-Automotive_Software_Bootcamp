/*
 * External_EEPROM.c
 * Created: 3/5/2023 3:40 AM
 * Author : Mahmoud Mowafey
 *
*/
#include "External_EEPROM.h"


/*
* initializing the EEPROM protocol
*
* Parameters
*       	[in] void
* Return
*   	    [out] void
*
*/
void EEPROM_init(void)
{
	TWI_init(); // just initialize the TWI module inside the MC
}

#ifdef EEPROM_24C16B

/*
* Writing one byte inside the External_EEPROM 
*
* Parameters
*       	[in] u16_l_byteAddress desired address, u8_l_byteData desired data to be saved
* Return
*   	    [out] EN_eepromError_t error_state
*
*/
EN_eepromError_t EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData)
{
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return EEPROM_ERROR;
	}
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	TWI_write((u8)((MANDATORY_SEQUENCE) | ((u16_l_byteAddress & PAGE_MASK) >> NEDDED_SHIFT_TIMES)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//send the required location address
	TWI_write((u8)(u16_l_byteAddress));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//write byte to eeprom
	TWI_write(u8_l_byteData);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	TWI_stop();

	return EEPROM_SUCCESS;
}

/*
* Reading one byte from the External_EEPROM
*
* Parameters
*       	[in] u16_l_byteAddress desired address, *u8_l_byteData pointer to save the saved data.
* Return
*   	    [out] EN_eepromError_t error_state
*
*/
EN_eepromError_t EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData)
{
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return EEPROM_ERROR;
	}
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	TWI_write((u8)((MANDATORY_SEQUENCE) | ((u16_l_byteAddress & PAGE_MASK) >> NEDDED_SHIFT_TIMES)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//send the required location address
	TWI_write((u8)(u16_l_byteAddress));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//send a repeated start
	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
	{
		return EEPROM_ERROR;
	}
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=1 (Read)
	TWI_write((u8)((MANDATORY_SEQUENCE) | ((u16_l_byteAddress & PAGE_MASK) >> NEDDED_SHIFT_TIMES) | 1));
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
	{
		return EEPROM_ERROR;
	}
	*u8_l_byteData = TWI_readWithNAck();
	if (TWI_getStatus() != TW_MR_DATA_NACK)
	{
		return EEPROM_ERROR;
	}
	TWI_stop();
	return EEPROM_SUCCESS;
}



#else
// This block of code is used when the desired memory is AT24C256KB
/*
* Writing one byte inside the External_EEPROM
*
* Parameters
*       	[in] u16_l_byteAddress desired address, u8_l_byteData desired data to be saved
* Return
*   	    [out] EN_eepromError_t error_state
*
*/
EN_eepromError_t EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData)
{
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return EEPROM_ERROR;
	}
	//Send the Device Address and R/W=0 bit
	TWI_write((u8)(MANDATORY_SEQUENCE));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the first word ( 7-MSBs) 0x0311 
	TWI_write((u8)(u16_l_byteAddress >> SHIFT_THE_FIRST_BYTE));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the Second word ( 8-LSBs)
	TWI_write((u8)((u16_l_byteAddress)&PAGE_MASK_256));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//write byte to eeprom
	TWI_write(u8_l_byteData);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	TWI_stop();
	return EEPROM_SUCCESS;
}

/*
* Reading one byte from the External_EEPROM
*
* Parameters
*       	[in] u16_l_byteAddress desired address, *u8_l_byteData pointer to save the saved data.
* Return
*   	    [out] EN_eepromError_t error_state
*
*/
EN_eepromError_t EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData)
{
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return EEPROM_ERROR;
	}
	//Send the Device Address and R/W=0 bit
	TWI_write((u8)((MANDATORY_SEQUENCE)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the first word ( 7-MSBs)--->0x0311
	TWI_write((u8)(u16_l_byteAddress >> SHIFT_THE_FIRST_BYTE));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the Second word ( 8-LSBs)
	TWI_write((u8)((u16_l_byteAddress)&PAGE_MASK_256));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//send a repeated start
	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
	{
		return EEPROM_ERROR;
	}
	//Send the Device Address and R/W=1 bit
	TWI_write((u8)(0xA1));
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
	{
		return EEPROM_ERROR;
	}
	//Read the data from the eeprom	with NACK
	*u8_l_byteData = TWI_readWithNAck();

	if (TWI_getStatus() != TW_MR_DATA_NACK)
	{
		return EEPROM_ERROR;
	}
	TWI_stop();
	return EEPROM_SUCCESS;
}


#endif

/*
* Writing Array_of_Bytes or String to be saved inside the External_EEPROM
*
* Parameters
*       	[in] u16_l_byteAddress desired address where the data will be saved in the EEPROM.
*				 u8* pstr pointer to string which contain the data to be saved.	
* Return
*   	    [out] EN_eepromError_t error_state.
*
*/

EN_eepromError_t EEPROM_writeArray(u16 u16_l_byteAddress, u8* pstr)
{
	u8 i = 0, x = 0;
	u16 j = u16_l_byteAddress;
	while (pstr[i] != '\0')
	{
		x = EEPROM_writeByte(j++, pstr[i++]);
		TIMER_delay_ms(10);
		if (0 == x)
			return EEPROM_ERROR;
	}
	EEPROM_writeByte(j, '\0');
	TIMER_delay_ms(10);
	return EEPROM_SUCCESS;
}

/*
* Reading Array_of_Bytes or String from the External_EEPROM
*
* Parameters
*       	[in] u16_l_byteAddress desired address where the data is saved in the EEPROM.
* Return
*   	    [out] u8* to array that contain the saved data inside the EEPROM.
*
*/
u8* EEPROM_readArray(u16 u16_l_byteAddress)
{
	u8 i = 0;
	static u8 arr[20];
	do {
		EEPROM_readByte(u16_l_byteAddress, &arr[i]);
		TIMER_delay_ms(10);
		u16_l_byteAddress++;
		i++;
	} while ((arr[i - 1] != '\0') && (i != 19));
	arr[i] = '\0';
	return arr;
}

/*
* Converting the decimal formate of the address to hex formate.
*
* Parameters
*       	[in] u8 decimal value.
* Return
*   	    [out] u8 hex value.
*
*/
u8 decimal_to_hex(u8 val)
{
	u8 msb, lsb, hex;
	msb = val / 10;
	lsb = val % 10;
	hex = ((msb << 4) + lsb);
	return hex;
}