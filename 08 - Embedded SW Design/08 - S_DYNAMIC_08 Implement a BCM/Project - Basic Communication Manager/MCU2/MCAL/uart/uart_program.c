/*
 * uart_program.c
 *
 *     Created on: May 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) functions' implementation, and ISR functions' prototypes and implementation.
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

/* MCAL */
#include "uart_interface.h"
#include "uart_private.h"
#include "uart_config.h"

/*******************************************************************************************************************************************************************/
/* UART Global Variables */

/* Global Pointers to Functions, these functions ( in Upper Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *vpf_gs_RXCInterruptAction  ) ( void ) = STD_TYPES_NULL;
static void ( *vpf_gs_UDREInterruptAction ) ( void ) = STD_TYPES_NULL;
static void ( *vpf_gs_TXCInterruptAction  ) ( void ) = STD_TYPES_NULL;

/* Global Array of UBRR ( Normal Speed ) Values for Commonly Used Oscillator Frequencies. */
static const u16 au16_gs_UBRRValuesNormalSpeed[6][8] = UART_AU16_NORMAL_SPEED_BAUD_RATES;

/* Global Array of UBRR ( Double Speed ) Values for Commonly Used Oscillator Frequencies. */
static const u16 au16_gs_UBRRValuesDoubleSpeed[6][8] = UART_AU16_DOUBLE_SPEED_BAUD_RATES;

/*******************************************************************************************************************************************************************/
/*
 Name: UART_initialization
 Input: void
 Output: void
 Description: Function to initialize UART peripheral using Pre-compile Configurations.
*/
void UART_initialization( void )
{
    /* The UBRRH Register shares the same I/O location as the UCSRC Register. Therefore some special consideration must be taken when accessing this I/O location. */
    /* When doing a write access of this I/O location, the high bit of the value written, the USART Register Select ( URSEL -> 8th ) bit, controls which one of the two registers that will be written. 
       If URSEL is zero during a write operation, the UBRRH value will be updated. If URSEL is one, the UCSRC setting will be updated. */
    u8 u8_l_UCSRCRegValue = 0b10000000;

    /* Step 1: Select UART Mode. */
	switch ( UART_U8_MODE_SELECT )
	{
        /* Case 1: UART Mode = Asynchronous Mode. */
		case UART_U8_ASYNC_MODE: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
        /* Case 2: UART Mode = Synchronous Mode. */
        case UART_U8_SYNC_MODE : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
    }

    /* Step 2: Select Speed and Baud Rate. */
    switch ( UART_U8_SPEED_SELECT )
	{
        /* Case 1: Speed = Normal Speed. */
		case UART_U8_NORMAL_SPEED:
		{
            CLR_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
            /* Baud Rate in Normal Speed Mode. */
            UART_U8_UBRRL_REG = ( u8 )   au16_gs_UBRRValuesNormalSpeed[MCU_U8_FCPU_SELECT][UART_U8_BAUD_RATE_SELECT];
            UART_U8_UBRRH_REG = ( u8 ) ( au16_gs_UBRRValuesNormalSpeed[MCU_U8_FCPU_SELECT][UART_U8_BAUD_RATE_SELECT] >> 8 );
		}
        break;

        /* Case 2: Speed = Double Speed. */
        case UART_U8_DOUBLE_SPEED:
		{
            SET_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
            /* Baud Rate in Double Speed Mode. */
            UART_U8_UBRRL_REG = ( u8 )   au16_gs_UBRRValuesDoubleSpeed[MCU_U8_FCPU_SELECT][UART_U8_BAUD_RATE_SELECT];
            UART_U8_UBRRH_REG = ( u8 ) ( au16_gs_UBRRValuesDoubleSpeed[MCU_U8_FCPU_SELECT][UART_U8_BAUD_RATE_SELECT] >> 8 );
		}
        break;
    }

    /* Step 3: Select Multi-processor Communication Mode. */
    switch ( UART_U8_MPCM_ENABLE )
	{
        /* Case 1: Multi-processor Communication Mode = Disabled. */
		case UART_U8_MPCM_DISABLED: CLR_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
        /* Case 2: Multi-processor Communication Mode = Enabled. */
        case UART_U8_MPCM_ENABLED : SET_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
    }

    /* Step 4: Receiver Complete Interrupt Enable. */
    switch ( UART_U8_RX_INT_ENABLE )
	{
        /* Case 1: Receiver Complete Interrupt = Disabled. */
		case UART_U8_RX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
        /* Case 2: Receiver Complete Interrupt = Enabled. */
        case UART_U8_RX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
    }

    /* Step 5: Transmitter Complete Interrupt Enable. */
    switch ( UART_U8_TX_INT_ENABLE )
	{
        /* Case 1: Transmitter Complete Interrupt = Disabled. */
		case UART_U8_TX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
        /* Case 2: Transmitter Complete Interrupt = Enabled. */
        case UART_U8_TX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
    }

    /* Step 6: Data Register Empty Interrupt Enable. */
    switch ( UART_U8_DATA_REG_EMPTY_INT_ENABLE )
	{
        /* Case 1: Data Register Empty Interrupt = Disabled. */
		case UART_U8_UDRE_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
        /* Case 2: Data Register Empty Interrupt = Enabled. */
        case UART_U8_UDRE_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
    }

    /* Step 7: Select Parity Mode. */
    switch ( UART_U8_PARITY_MODE_SELECT )
	{
        /* Case 1: Parity Mode = Disabled. */
		case UART_U8_PARITY_MODE_DISABLED: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
        /* Case 2: Parity Mode = Even. */
        case UART_U8_EVEN_PARITY_MODE    : CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
        /* Case 3: Parity Mode = Odd. */        
        case UART_U8_ODD_PARITY_MODE     : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
    }

    /* Step 8: Select Stop Bit(s). */
    switch ( UART_U8_STOP_BIT_SELECT )
	{
        /* Case 1: Stop Bit(s) = 1. */
		case UART_U8_ONE_STOP_BIT: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
        /* Case 2: Stop Bit(s) = 2. */
        case UART_U8_TWO_STOP_BIT: SET_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
    }

    /* Step 9: Select Data Size. */
    switch ( UART_U8_DATA_BITS_SELECT )
	{
        /* Case 1: Data Size = 5 Bits. */
		case UART_U8_5_DATA_BITS: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 2: Data Size = 6 Bits. */
        case UART_U8_6_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 3: Data Size = 7 Bits. */
        case UART_U8_7_DATA_BITS: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 4: Data Size = 8 Bits. */
        case UART_U8_8_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 5: Data Size = 9 Bits. */
        case UART_U8_9_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  SET_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
    }

    /* Step 10: Update UCSRC Register, after configuring modes and selecting UCSRC Register. */
    UART_U8_UCSRC_REG = u8_l_UCSRCRegValue;

    /* Step 11: Receiver Enable. */
    switch ( UART_U8_RX_ENABLE )
	{
        /* Case 1: Receiver ( RX ) = Disabled. */
		case UART_U8_RX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
        /* Case 2: Receiver ( RX ) = Enabled. */
        case UART_U8_RX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
    }

    /* Step 11: Transmitter Enable. */
    switch ( UART_U8_TX_ENABLE )
	{
        /* Case 1: Transmitter ( TX ) = Disabled. */
		case UART_U8_TX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
        /* Case 2: Transmitter ( TX ) = Enabled. */
        case UART_U8_TX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
    }
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_linkConfigInitialization
 Input: Pointer to stLinkConfig
 Output: en Error or No Error
 Description: Function to initialize UART peripheral using Linking Configurations.
*/
UART_enErrorState_t UART_linkConfigInitialization( const UART_stLinkConfig_t *pst_a_linkConfig )
{
	/* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;
	    
	/* Check 1: Pointer is not equal to NULL. */
	if ( pst_a_linkConfig != STD_TYPES_NULL )
	{
		/* The UBRRH Register shares the same I/O location as the UCSRC Register. Therefore some special consideration must be taken when accessing this I/O location. */
		/* When doing a write access of this I/O location, the high bit of the value written, the USART Register Select ( URSEL -> 8th ) bit, controls which one of the two registers that will be written. 
		   If URSEL is zero during a write operation, the UBRRH value will be updated. If URSEL is one, the UCSRC setting will be updated. */
		u8 u8_l_UCSRCRegValue = 0b10000000;
		
		/* Step 1: Select UART Mode. */
		switch ( pst_a_linkConfig->en_g_mode )
		{
		    /* Case 1: UART Mode = Asynchronous Mode. */
			case UART_EN_ASYNC_MODE: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
		    /* Case 2: UART Mode = Synchronous Mode. */
		    case UART_EN_SYNC_MODE : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
			/* Default Case: Wrong UART Mode Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 2: Select Speed and Baud Rate. */
		switch ( pst_a_linkConfig->en_g_speed )
		{
		    /* Case 1: Speed = Normal Speed. */
			case UART_EN_NORMAL_SPEED:
			{
		        CLR_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
		        /* Baud Rate in Normal Speed Mode. */
		        UART_U8_UBRRL_REG = ( u8 )   au16_gs_UBRRValuesNormalSpeed[MCU_U8_FCPU_SELECT][pst_a_linkConfig->en_g_baudRate];
		        UART_U8_UBRRH_REG = ( u8 ) ( au16_gs_UBRRValuesNormalSpeed[MCU_U8_FCPU_SELECT][pst_a_linkConfig->en_g_baudRate] >> 8 );
				
				break;
			}
		    		
		    /* Case 2: Speed = Double Speed. */
		    case UART_EN_DOUBLE_SPEED:
			{		
		        SET_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
		        /* Baud Rate in Double Speed Mode. */
		        UART_U8_UBRRL_REG = ( u8 )   au16_gs_UBRRValuesDoubleSpeed[MCU_U8_FCPU_SELECT][pst_a_linkConfig->en_g_baudRate];
		        UART_U8_UBRRH_REG = ( u8 ) ( au16_gs_UBRRValuesDoubleSpeed[MCU_U8_FCPU_SELECT][pst_a_linkConfig->en_g_baudRate] >> 8 );
				
				break;
			}
		    
			/* Default Case: Wrong Speed Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 3: Select Multi-processor Communication Mode. */
		switch ( pst_a_linkConfig->en_g_MPCM )
		{
		    /* Case 1: Multi-processor Communication Mode = Disabled. */
			case UART_EN_MPCM_DISABLED: CLR_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
		    /* Case 2: Multi-processor Communication Mode = Enabled. */
		    case UART_EN_MPCM_ENABLED : SET_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
			/* Default Case: Wrong Multi-processor Communication Mode Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 4: Receiver Complete Interrupt Enable. */
		switch ( pst_a_linkConfig->en_g_RXInterruptEnable )
		{
		    /* Case 1: Receiver Complete Interrupt = Disabled. */
			case UART_EN_RX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
		    /* Case 2: Receiver Complete Interrupt = Enabled. */
		    case UART_EN_RX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
			/* Default Case: Wrong Receiver Complete Interrupt Input. */
			default: en_l_errorState = UART_EN_NOK;			
		}
		
		/* Step 5: Transmitter Complete Interrupt Enable. */
		switch ( pst_a_linkConfig->en_g_TXInterruptEnable )
		{
		    /* Case 1: Transmitter Complete Interrupt = Disabled. */
			case UART_EN_TX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
		    /* Case 2: Transmitter Complete Interrupt = Enabled. */
		    case UART_EN_TX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
			/* Default Case: Wrong Transmitter Complete Interrupt Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 6: Data Register Empty Interrupt Enable. */
		switch ( pst_a_linkConfig->en_g_UDREInterruptEnable )
		{
		    /* Case 1: Data Register Empty Interrupt = Disabled. */
			case UART_EN_UDRE_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
		    /* Case 2: Data Register Empty Interrupt = Enabled. */
		    case UART_EN_UDRE_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
			/* Default Case: Wrong Data Register Empty Interrupt Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 7: Select Parity Mode. */
		switch ( pst_a_linkConfig->en_g_parityMode )
		{
		    /* Case 1: Parity Mode = Disabled. */
			case UART_EN_PARITY_MODE_DISABLED: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
		    /* Case 2: Parity Mode = Even. */
		    case UART_EN_EVEN_PARITY_MODE    : CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
		    /* Case 3: Parity Mode = Odd. */        
		    case UART_EN_ODD_PARITY_MODE     : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
			/* Default Case: Wrong Parity Mode Input. */
			default: en_l_errorState = UART_EN_NOK;			
		}
		
		/* Step 8: Select Stop Bit(s). */
		switch ( pst_a_linkConfig->en_g_stopBit )
		{
		    /* Case 1: Stop Bit(s) = 1. */
			case UART_EN_ONE_STOP_BIT: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
		    /* Case 2: Stop Bit(s) = 2. */
		    case UART_EN_TWO_STOP_BIT: SET_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
			/* Default Case: Wrong Stop Bit(s) Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 9: Select Data Size. */
		switch ( pst_a_linkConfig->en_g_dataBits )
		{
		    /* Case 1: Data Size = 5 Bits. */
			case UART_EN_5_DATA_BITS: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
		                              CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
		    /* Case 2: Data Size = 6 Bits. */
		    case UART_EN_6_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
		                              CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
		    /* Case 3: Data Size = 7 Bits. */
		    case UART_EN_7_DATA_BITS: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
		                              CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
		    /* Case 4: Data Size = 8 Bits. */
		    case UART_EN_8_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
		                              CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
		    /* Case 5: Data Size = 9 Bits. */
		    case UART_EN_9_DATA_BITS: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
		                              SET_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
			/* Default Case: Wrong Data Size Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 10: Update UCSRC Register, after configuring modes and selecting UCSRC Register. */
		UART_U8_UCSRC_REG = u8_l_UCSRCRegValue;
		
		/* Step 11: Receiver Enable. */
		switch ( pst_a_linkConfig->en_g_RXEnable )
		{
		    /* Case 1: Receiver ( RX ) = Disabled. */
			case UART_EN_RX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
		    /* Case 2: Receiver ( RX ) = Enabled. */
		    case UART_EN_RX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
			/* Default Case: Wrong Receiver Enable Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
		
		/* Step 11: Transmitter Enable. */
		switch ( pst_a_linkConfig->en_g_TXEnable )
		{
		    /* Case 1: Transmitter ( TX ) = Disabled. */
			case UART_EN_TX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
		    /* Case 2: Transmitter ( TX ) = Enabled. */
		    case UART_EN_TX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
			/* Default Case: Wrong Transmitter Enable Input. */
			default: en_l_errorState = UART_EN_NOK;
		}
	}
	/* Check 2: Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		en_l_errorState = UART_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_receiveByte
 Input: en BlockMode and Pointer to u8 ReturnedReceiveByte
 Output: en Error or No Error
 Description: Function to Receive Byte using both Blocking and Non-blocking Modes, with Timeout mechanism.
*/
UART_enErrorState_t UART_receiveByte( UART_enBlockMode_t en_a_blockMode, u8 *pu8_a_returnedReceiveByte )
{
    /* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;
    
    /* Check 1: BlockMode is in the valid range, and Pointer is not equal to NULL. */
    if ( ( en_a_blockMode < UART_EN_INVALID_BLOCK_MODE ) && ( pu8_a_returnedReceiveByte != STD_TYPES_NULL ) )
    {
        /* Check 1.1: Required BlockMode. */
        switch ( en_a_blockMode )
        {
            case UART_EN_BLOCKING_MODE:
			{
				u16 u16_l_timeOutCounter = 0;

                /* Step 1: Wait ( Poll ) until Byte is Received ( i.e. until Flag ( RXC ) = 1 ), taking into consideration TimeOutCounter. */
                while ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT ) == 0 ) && ( u16_l_timeOutCounter < UART_U16_TIME_OUT_MAX_VALUE ) )
                {
                    u16_l_timeOutCounter++;
                }
                
                /* Check 1.1.1: Data is Received ( i.e. Flag ( RXC ) = 1 ). */
                if ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT ) != 0 ) )
                {
                    /* Step 2: Clear the flag ( RXC ) by writing logical one, because this is Polling Mode. */
                    SET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT );

                    /* Step 3: Get the Received Byte from the UART register -> ( UDR register ). */
                    *pu8_a_returnedReceiveByte = UART_U8_UDR_REG;
                }
                /* Check 1.1.2: Byte is not Received ( i.e. TimeOutCounter reached Max value ). */
                else
                {
                    /* Update error state = NOK, TimeOutCounter reached Max value! */
                    en_l_errorState = UART_EN_NOK;
                }
				
				break;
			}
            
            case UART_EN_NON_BLOCKING_MODE:
			{
                /* Get the Received Byte from the UART register -> ( UDR register ). */
                *pu8_a_returnedReceiveByte = UART_U8_UDR_REG;
				
				break;
			}
			
			default:
			{
				/* Do Nothing. */				
				break;
			}
        }                
    }
    /* Check 2: BlockMode is not in the valid range, or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, wrong BlockMode or Pointer is NULL! */
		en_l_errorState = UART_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_transmitByte
 Input: en BlockMode and u8 TransmitByte
 Output: en Error or No Error
 Description: Function to Transmit Byte using both Blocking and Non-blocking Modes, with Timeout mechanism.
*/
UART_enErrorState_t UART_transmitByte( UART_enBlockMode_t u8_a_blockMode, u8 u8_a_transmitByte )
{
    /* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;
    
    /* Check 1: BlockMode is in the valid range. */
    if ( u8_a_blockMode < UART_EN_INVALID_BLOCK_MODE )
    {
        /* Check 1.1: Required BlockMode. */
        switch ( u8_a_blockMode )
        {
            case UART_EN_BLOCKING_MODE:
			{
                u16 u16_l_timeOutCounter = 0;

                /* Step 1: Wait ( Poll ) until Transmit Register is Empty ( i.e. until Flag ( UDRE ) = 1 ), taking into consideration TimeOutCounter. */
                while ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_UDRE_BIT ) == 0 ) && ( u16_l_timeOutCounter < UART_U16_TIME_OUT_MAX_VALUE ) )
                {
                    u16_l_timeOutCounter++;
                }

                /* Check 1.1.1: Transmit Register is Empty ( i.e. Flag ( UDRE ) = 1 ). */
                if ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_UDRE_BIT ) != 0 ) )
                {
                    /* Step 2: Clear the flag ( UDRE ) by writing logical one, because this is Polling Mode. */
                    SET_BIT( UART_U8_UCSRA_REG, UART_U8_UDRE_BIT );

                    /* Step 3: Set the Transmitted Byte to the UART register -> ( UDR register ). */
                    UART_U8_UDR_REG = u8_a_transmitByte;
                }
                /* Check 1.1.2: Transmit Register is not Empty ( i.e. TimeOutCounter reached Max value ). */
                else
                {
                    /* Update error state = NOK, TimeOutCounter reached Max value! */
                    en_l_errorState = UART_EN_NOK;
                }
						
				break;            
			}

            case UART_EN_NON_BLOCKING_MODE:
			{
                /* Set the Transmitted Byte to the UART register -> ( UDR register ). */
                UART_U8_UDR_REG = u8_a_transmitByte;
				
				break;
			}
            						
			default:
			{
				/* Do Nothing. */
				break;
			}
        }
    }
    /* Check 2: BlockMode is not in the valid range. */
	else
	{
		/* Update error state = NOK, wrong BlockMode! */
		en_l_errorState = UART_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_enableInterrupt
 Input: en InterruptId
 Output: en Error or No Error
 Description: Function to enable UART different interrupts.
*/
UART_enErrorState_t UART_enableInterrupt( UART_enInterruptId_t en_a_interruptId )
{
    /* Define local variable to set the error state = OK. */
    UART_enErrorState_t en_l_errorState = UART_EN_OK;
    
    /* Check 1: InterruptId is in the valid range. */
    if ( en_a_interruptId < UART_EN_INVALID_INT_ID )
    {
	    /* Check 1.1: Required InterruptId. */
	    switch ( en_a_interruptId )
	    {
		    case UART_EN_RXC_INT : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
		    case UART_EN_UDRE_INT: SET_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
		    case UART_EN_TXC_INT : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
		    default:			         /* Do Nothing. */		                    break;
	    }
    }
    /* Check 2: InterruptId is not in the valid range. */
    else
    {
	    /* Update error state = NOK, wrong InterruptId! */
	    en_l_errorState = UART_EN_NOK;
    }

    return en_l_errorState;
 }

/*******************************************************************************************************************************************************************/
/*
 Name: UART_disableInterrupt
 Input: en InterruptId
 Output: en Error or No Error
 Description: Function to disable UART different interrupts.
*/
UART_enErrorState_t UART_disableInterrupt( UART_enInterruptId_t en_a_interruptId )
{
    /* Define local variable to set the error state = OK. */
    UART_enErrorState_t en_l_errorState = UART_EN_OK;
    
    /* Check 1: InterruptId is in the valid range. */
    if ( en_a_interruptId < UART_EN_INVALID_INT_ID )
    {
	    /* Check 1.1: Required InterruptId. */
	    switch ( en_a_interruptId )
	    {
		    case UART_EN_RXC_INT : CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
		    case UART_EN_UDRE_INT: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
		    case UART_EN_TXC_INT : CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
		    default:			         /* Do Nothing. */		                    break;
	    }
    }
    /* Check 2: InterruptId is not in the valid range. */
    else
    {
	    /* Update error state = NOK, wrong InterruptId! */
	    en_l_errorState = UART_EN_NOK;
    }

    return en_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_RXCSetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( RXCInterruptAction ), and then pass this address to ISR function.
*/
UART_enErrorState_t UART_RXCSetCallback( void ( *vpf_a_RXCInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;

	/* Check 1: Pointer to Function is not equal to NULL. */
	if( vpf_a_RXCInterruptAction != STD_TYPES_NULL )
	{
        /* Store the passed address of function ( in Upper Layer ) through pointer to function ( RXCInterruptAction ) into Global Pointer to Function ( RXCInterruptAction ). */
		vpf_gs_RXCInterruptAction = vpf_a_RXCInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		en_l_errorState = UART_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_UDRESetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( UDREInterruptAction ), and then pass this address to ISR function.
*/
UART_enErrorState_t UART_UDRESetCallback( void ( *vpf_a_UDREInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;

	/* Check 1: Pointer to Function is not equal to NULL. */
	if( vpf_a_UDREInterruptAction != STD_TYPES_NULL )
	{
		/* Store the passed address of function ( in Upper Layer ) through pointer to function ( UDREInterruptAction ) into Global Pointer to Function ( UDREInterruptAction ). */
		vpf_gs_UDREInterruptAction = vpf_a_UDREInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		en_l_errorState = UART_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_TXCSetCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in Upper Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TXCInterruptAction ), and then pass this address to ISR function.
*/
UART_enErrorState_t UART_TXCSetCallback( void ( *vpf_a_TXCInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	UART_enErrorState_t en_l_errorState = UART_EN_OK;

	/* Check 1: Pointer to Function is not equal to NULL. */
	if( vpf_a_TXCInterruptAction != STD_TYPES_NULL )
	{
		/* Store the passed address of function ( in Upper Layer ) through pointer to function ( TXCInterruptAction ) into Global Pointer to Function ( TXCInterruptAction ). */
		vpf_gs_TXCInterruptAction = vpf_a_TXCInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		en_l_errorState = UART_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/

/* ISR functions' prototypes of Receive Complete ( RXC ), Data Register Empty ( UDRE ), and Transmit Complete ( TXC ) respectively. */
void __vector_13( void )	__attribute__((signal));
void __vector_14( void )	__attribute__((signal));
void __vector_15( void )	__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of RXC. */
void __vector_13( void )
{
	/* Check: Global Pointer to Function is not equal to NULL. */
	if ( vpf_gs_RXCInterruptAction != STD_TYPES_NULL )
	{
		/* Call Back the function ( in Upper Layer ), which its address is stored in the Global Pointer to Function ( RXCInterruptAction ). */
		vpf_gs_RXCInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of UDRE. */
void __vector_14( void )
{
	/* Check: Global Pointer to Function is not equal to NULL. */
	if ( vpf_gs_UDREInterruptAction != STD_TYPES_NULL )
	{
		/* Call Back the function ( in Upper Layer ), which its address is stored in the Global Pointer to Function ( UDREInterruptAction ). */
		vpf_gs_UDREInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TXC. */
void __vector_15( void )
{
	/* Check: Global Pointer to Function is not equal to NULL. */
	if ( vpf_gs_TXCInterruptAction != STD_TYPES_NULL )
	{
		/* Call Back the function ( in Upper Layer ), which its address is stored in the Global Pointer to Function ( TXCInterruptAction ). */
		vpf_gs_TXCInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/