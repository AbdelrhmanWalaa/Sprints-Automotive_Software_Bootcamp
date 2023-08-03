/*
 * uart_program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "uart_private.h"
#include "uart_config.h"
#include "uart_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Pointers to Functions, these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *vpf_gs_RXCInterruptAction  ) ( void ) = NULL;
static void ( *vpf_gs_UDREInterruptAction ) ( void ) = NULL;
static void ( *vpf_gs_TXCInterruptAction  ) ( void ) = NULL;

/* Global Array of UBRR ( Normal Speed ) Values for Commonly Used Oscillator Frequencies */
/*                    Baud Rate:                  */    /*  2.4k |  4.8k |  9.6k | 14.4k | 19.2k | 28.8k | 38.4k | 57.8k */   /*  FCPU  */
static const u16 Au16_gs_UBRRValuesNormalSpeed[6][8] = { {  25   ,  12   ,  6    ,   3   ,   2   ,   1   ,   1   ,   0   },   /*  1 MHz */
                                                         {  51   ,  25   ,  12   ,   8   ,   6   ,   3   ,   2   ,   1   },   /*  2 MHz */
                                                         {  103  ,  51   ,  25   ,   16  ,   12  ,   8   ,   6   ,   3   },   /*  4 MHz */
                                                         {  207  ,  103  ,  51   ,   34  ,   25  ,   16  ,   12  ,   8   },   /*  8 MHz */
                                                         {  416  ,  207  ,  103  ,   68  ,   51  ,   34  ,   25  ,   16  },   /* 16 MHz */
                                                         {  520  ,  259  ,  129  ,   86  ,   64  ,   42  ,   32  ,   21  } }; /* 20 MHz */

/* Global Array of UBRR ( Double Speed ) Values for Commonly Used Oscillator Frequencies */
/*                    Baud Rate:                  */    /*  2.4k |  4.8k |  9.6k | 14.4k | 19.2k | 28.8k | 38.4k | 57.8k */   /*  FCPU  */
static const u16 Au16_gs_UBRRValuesDoubleSpeed[6][8] = { {  51   ,  25   ,  12   ,   8   ,   6   ,   3   ,   2   ,   1   },   /*  1 MHz */
                                                         {  103  ,  51   ,  25   ,   16  ,   12  ,   8   ,   6   ,   3   },   /*  2 MHz */
                                                         {  207  ,  103  ,  51   ,   34  ,   25  ,   16  ,   12  ,   8   },   /*  4 MHz */
                                                         {  416  ,  207  ,  103  ,   68  ,   51  ,   34  ,   25  ,   16  },   /*  8 MHz */
                                                         {  832  ,  416  ,  207  ,   138 ,   103 ,   68  ,   51  ,   34  },   /* 16 MHz */
                                                         {  1041 ,  520  ,  259  ,   173 ,   129 ,   86  ,   64  ,   42  } }; /* 20 MHz */

/*******************************************************************************************************************************************************************/
/*
 Name: UART_initialization
 Input: void
 Output: void
 Description: Function to initialize UART peripheral.
*/
vd UART_initialization  ( void )
{
    /* The UBRRH Register shares the same I/O location as the UCSRC Register. Therefore some special consideration must be taken when accessing this I/O location. */
    /* When doing a write access of this I/O location, the high bit of the value written, the USART Register Select ( URSEL -> 8th ) bit, controls which one of the two registers that will be written. 
       If URSEL is zero during a write operation, the UBRRH value will be updated. If URSEL is one, the UCSRC setting will be updated. */
    u8 u8_l_UCSRCRegValue = 0b10000000;

    /* Step 1: Select UART Mode */
	switch ( UART_U8_MODE_SELECT )
	{
        /* Case 1: UART Mode = Asynchronous Mode */
		case UART_U8_ASYNC_MODE: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
        /* Case 2: UART Mode = Synchronous Mode */
        case UART_U8_SYNC_MODE : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UMSEL_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCPOL_BIT ); break;
    }

    /* Step 2: Select Speed and Baud Rate */
    switch ( UART_U8_SPEED_SELECT )
	{
        /* Case 1: Speed = Normal Speed */
		case UART_U8_NORMAL_SPEED:

            CLR_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
            /* Baud Rate in Normal Speed Mode */
            UART_U8_UBRRL_REG = ( u8 )   Au16_gs_UBRRValuesNormalSpeed[0][UART_U8_BAUD_RATE_SELECT];
            UART_U8_UBRRH_REG = ( u8 ) ( Au16_gs_UBRRValuesNormalSpeed[0][UART_U8_BAUD_RATE_SELECT] >> 8 );
        break;

        /* Case 2: Speed = Double Speed */
        case UART_U8_DOUBLE_SPEED:

            SET_BIT( UART_U8_UCSRA_REG, UART_U8_U2X_BIT );
            /* Baud Rate in Double Speed Mode */
            UART_U8_UBRRL_REG = ( u8 )   Au16_gs_UBRRValuesDoubleSpeed[0][UART_U8_BAUD_RATE_SELECT];
            UART_U8_UBRRH_REG = ( u8 ) ( Au16_gs_UBRRValuesDoubleSpeed[0][UART_U8_BAUD_RATE_SELECT] >> 8 ); 
        break;
    }

    /* Step 3: Select Multi-processor Communication Mode */
    switch ( UART_U8_MPCM_ENABLE )
	{
        /* Case 1: Multi-processor Communication Mode = Disabled */
		case UART_U8_MPCM_DISABLED: CLR_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
        /* Case 2: Multi-processor Communication Mode = Enabled */
        case UART_U8_MPCM_ENABLED : SET_BIT( UART_U8_UCSRA_REG, UART_U8_MPCM_BIT ); break;
    }

    /* Step 4: Receiver Complete Interrupt Enable */
    switch ( UART_U8_RX_INT_ENABLE )
	{
        /* Case 1: Receiver Complete Interrupt = Disabled */
		case UART_U8_RX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
        /* Case 2: Receiver Complete Interrupt = Enabled */
        case UART_U8_RX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXCIE_BIT ); break;
    }

    /* Step 5: Transmitter Complete Interrupt Enable */
    switch ( UART_U8_TX_INT_ENABLE )
	{
        /* Case 1: Transmitter Complete Interrupt = Disabled */
		case UART_U8_TX_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
        /* Case 2: Transmitter Complete Interrupt = Enabled */
        case UART_U8_TX_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXCIE_BIT ); break;
    }

    /* Step 6: Data Register Empty Interrupt Enable */
    switch ( UART_U8_DATA_REG_EMPTY_INT_ENABLE )
	{
        /* Case 1: Data Register Empty Interrupt = Disabled */
		case UART_U8_UDRE_INT_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
        /* Case 2: Data Register Empty Interrupt = Enabled */
        case UART_U8_UDRE_INT_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_UDRIE_BIT ); break;
    }

    /* Step 7: Select Parity Mode */
    switch ( UART_U8_PARITY_MODE_SELECT )
	{
        /* Case 1: Parity Mode = Disabled */
		case UART_U8_PARITY_MODE_DISABLED: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
        /* Case 2: Parity Mode = Even */
        case UART_U8_EVEN_PARITY_MODE    : CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
        /* Case 3: Parity Mode = Odd */        
        case UART_U8_ODD_PARITY_MODE     : SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UPM1_BIT ); break;
    }

    /* Step 8: Select Stop Bit(s) */
    switch ( UART_U8_STOP_BIT_SELECT )
	{
        /* Case 1: Stop Bit(s) = 1 */
		case UART_U8_ONE_STOP_BIT: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
        /* Case 2: Stop Bit(s) = 2 */
        case UART_U8_TWO_STOP_BIT: SET_BIT( u8_l_UCSRCRegValue, UART_U8_USBS_BIT ); break;
    }

    /* Step 9: Select Data Size */
    switch ( UART_U8_DATA_BITS_SELECT )
	{
        /* Case 1: Data Size = 5 Bits */
		case UART_U8_5_BITS_DATA: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 2: Data Size = 6 Bits */
        case UART_U8_6_BITS_DATA: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 3: Data Size = 7 Bits */
        case UART_U8_7_BITS_DATA: CLR_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 4: Data Size = 8 Bits */
        case UART_U8_8_BITS_DATA: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  CLR_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
        /* Case 5: Data Size = 9 Bits */
        case UART_U8_9_BITS_DATA: SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ0_BIT ); SET_BIT( u8_l_UCSRCRegValue, UART_U8_UCSZ1_BIT );
                                  SET_BIT( UART_U8_UCSRB_REG, UART_U8_UCSZ2_BIT ); break;
    }

    /* Step 10: Update UCSRC Register, after configuring modes and selecting UCSRC Register */
    UART_U8_UCSRC_REG = u8_l_UCSRCRegValue;

    /* Step 11: Receiver Enable */
    switch ( UART_U8_RX_ENABLE )
	{
        /* Case 1: Receiver ( RX ) = Disabled */
		case UART_U8_RX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
        /* Case 2: Receiver ( RX ) = Enabled */
        case UART_U8_RX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_RXEN_BIT ); break;
    }

    /* Step 11: Transmitter Enable */
    switch ( UART_U8_TX_ENABLE )
	{
        /* Case 1: Transmitter ( TX ) = Disabled */
		case UART_U8_TX_DISABLED: CLR_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
        /* Case 2: Transmitter ( TX ) = Enabled */
        case UART_U8_TX_ENABLED : SET_BIT( UART_U8_UCSRB_REG, UART_U8_TXEN_BIT ); break;
    }
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_receiveByte
 Input: u8 InterruptionMode and Pointer to u8 ReturnedReceiveByte
 Output: u8 Error or No Error
 Description: Function to Receive Byte using both Polling and Interrupt Modes, with Timeout mechanism.
*/
u8 UART_receiveByte     ( u8 u8_a_interruptionMode, u8 *pu8_a_returnedReceiveByte )
{
    /* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
    
    /* Check 1: InterruptionMode is in the valid range, and Pointer is not equal to NULL */
    if ( ( u8_a_interruptionMode <= UART_U8_RXC_INT_MODE ) && ( pu8_a_returnedReceiveByte != NULL ) )
    {
        /* Check 1.1: Required InterruptionMode */
        switch ( u8_a_interruptionMode )
        {
            case UART_U8_POLLING_MODE:
			{
				u16 u16_l_TimeOutCounter = 0;

                /* Step 1: Wait ( Poll ) until Byte is Received ( i.e. until Flag ( RXC ) = 1 ), taking into consideration TimeOutCounter */
                while ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT ) == 0 ) && ( u16_l_TimeOutCounter < UART_U16_TIME_OUT_MAX_VALUE ) )
                {
                    u16_l_TimeOutCounter++;
                }
                
                /* Check 1.1.1: Data is Received ( i.e. Flag ( RXC ) = 1 ) */
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
                    u8_l_errorState = STD_NOK;
                }
			}
            break;

            case UART_U8_RXC_INT_MODE:

                /* Get the Received Byte from the UART register -> ( UDR register ). */
                *pu8_a_returnedReceiveByte = UART_U8_UDR_REG;

            break;
        }                
    }
    /* Check 2: InterruptionMode is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptionMode or Pointer is NULL! */
		u8_l_errorState = STD_NOK;
	}

	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_receiveByteBlock
 Input: u8 Pointer to u8 ReturnedReceiveByte
 Output: u8 Error or No Error
 Description: Function to Receive Byte using Polling Mode, without Timeout mechanism.
*/
u8 UART_receiveByteBlock( u8 *pu8_a_returnedReceiveByte )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;

	/* Check 1: Pointer is not equal to NULL */
	if ( pu8_a_returnedReceiveByte != NULL ) 
	{
		/* Step 1: Wait ( Poll ) until Byte is Received ( i.e. until Flag ( RXC ) = 1 ), taking into consideration TimeOutCounter */
		while ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT ) == 0 );
		/* Step 2: Clear the flag ( RXC ) by writing logical one, because this is Polling Mode. */
		SET_BIT( UART_U8_UCSRA_REG, UART_U8_RXC_BIT );

		/* Step 3: Get the Received Byte from the UART register -> ( UDR register ). */
		*pu8_a_returnedReceiveByte = UART_U8_UDR_REG;
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		u8_l_errorState = STD_NOK;
	}

	return u8_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_transmitByte
 Input: u8 InterruptionMode and u8 TransmitByte
 Output: u8 Error or No Error
 Description: Function to Transmit Byte using both Polling and Interrupt Modes, with Timeout mechanism.
*/
u8 UART_transmitByte    ( u8 u8_a_interruptionMode, u8 u8_a_transmitByte )
{
    /* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
    
    /* Check 1: InterruptionMode is in the valid range */
    if ( u8_a_interruptionMode <= UART_U8_UDRE_INT_MODE )
    {
        /* Check 1.1: Required InterruptionMode */
        switch ( u8_a_interruptionMode )
        {
            case UART_U8_POLLING_MODE:
			{
                u16 u16_l_TimeOutCounter = 0;

                /* Step 1: Wait ( Poll ) until Transmit Register is Empty ( i.e. until Flag ( UDRE ) = 1 ), taking into consideration TimeOutCounter */
                while ( ( GET_BIT( UART_U8_UCSRA_REG, UART_U8_UDRE_BIT ) == 0 ) && ( u16_l_TimeOutCounter < UART_U16_TIME_OUT_MAX_VALUE ) )
                {
                    u16_l_TimeOutCounter++;
                }

                /* Check 1.1.1: Transmit Register is Empty ( i.e. Flag ( UDRE ) = 1 ) */
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
                    u8_l_errorState = STD_NOK;
                }
			}
            break;

            case UART_U8_UDRE_INT_MODE:

                /* Set the Transmitted Byte to the UART register -> ( UDR register ). */
                UART_U8_UDR_REG = u8_a_transmitByte;

            break;
        }
    }
    /* Check 2: InterruptionMode is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptionMode! */
		u8_l_errorState = STD_NOK;
	}

	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_transmitString
 Input: Pointer to u8 String
 Output: u8 Error or No Error
 Description: Function to Transmit String.
*/
u8 UART_transmitString  ( u8 *pu8_a_string )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
	    
	/* Check 1: Pointer is not equal to NULL */
	if ( pu8_a_string != NULL )
	{
		while ( *pu8_a_string != '\0' )
		{
			UART_transmitByte( UART_U8_POLLING_MODE, *pu8_a_string );
			/* Increment String */
			pu8_a_string++;
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		u8_l_errorState = STD_NOK;
	}

	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_RXCSetCallBack
 Input: Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( RXCInterruptAction ), and then pass this address to ISR function.
*/
u8 UART_RXCSetCallBack  ( void ( *vpf_a_RXCInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;

	/* Check 1: Pointer to Function is not equal to NULL */
	if( vpf_a_RXCInterruptAction != NULL )
	{
        /* Store the passed address of function ( in APP Layer ) through pointer to function ( RXCInterruptAction ) into Global Pointer to Function ( RXCInterruptAction ). */
		vpf_gs_RXCInterruptAction = vpf_a_RXCInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_UDRESetCallBack
 Input: Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( UDREInterruptAction ), and then pass this address to ISR function.
*/
u8 UART_UDRESetCallBack ( void ( *vpf_a_UDREInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;

	/* Check 1: Pointer to Function is not equal to NULL */
	if( vpf_a_UDREInterruptAction != NULL )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( UDREInterruptAction ) into Global Pointer to Function ( UDREInterruptAction ). */
		vpf_gs_UDREInterruptAction = vpf_a_UDREInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: UART_TXCSetCallBack
 Input: Pointer to Function that takes void and returns void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function,
  	  	  	  the address is passed through a pointer to function ( TXCInterruptAction ), and then pass this address to ISR function.
*/
u8 UART_TXCSetCallBack  ( void ( *vpf_a_TXCInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;

	/* Check 1: Pointer to Function is not equal to NULL */
	if( vpf_a_TXCInterruptAction != NULL )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( TXCInterruptAction ) into Global Pointer to Function ( TXCInterruptAction ). */
		vpf_gs_TXCInterruptAction = vpf_a_TXCInterruptAction;
	}
	/* Check 2: Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer to Function is NULL! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/

/* ISR functions' prototypes of Receive Complete ( RXC ), Data Register Empty ( UDRE ), and Transmit Complete ( TXC ) respectively */
void __vector_13( void )	__attribute__((signal));
void __vector_14( void )	__attribute__((signal));
void __vector_15( void )	__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of RXC */
void __vector_13( void )
{
	/* Check: Global Pointer to Function is not equal to NULL */
	if ( vpf_gs_RXCInterruptAction != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Pointer to Function ( RXCInterruptAction ) */
		vpf_gs_RXCInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of UDRE */
void __vector_14( void )
{
	/* Check: Global Pointer to Function is not equal to NULL */
	if ( vpf_gs_UDREInterruptAction != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Pointer to Function ( UDREInterruptAction ) */
		vpf_gs_UDREInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TXC */
void __vector_15( void )
{
	/* Check: Global Pointer to Function is not equal to NULL */
	if ( vpf_gs_TXCInterruptAction != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Pointer to Function ( TXCInterruptAction ) */
		vpf_gs_TXCInterruptAction();
	}
}

/*******************************************************************************************************************************************************************/