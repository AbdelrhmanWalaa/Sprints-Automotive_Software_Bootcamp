/*
 * kpd_program.c
 *
 *   Created on: Apr 3, 2021
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	Description: This file contains all Keypad (KPD) functions' implementation.
 */

/* HAL */
#include "kpd_config.h"
#include "kpd_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Array of KPD Keys */
static const u8 Au8_gs_keys[1][2] = KPD_AU8_KEYS;

/* Global Arrays of Rows an Columns Pins */
static const u8 Au8_gs_rowsPins[1] = { KPD_U8_R1_PIN };
static const u8 Au8_gs_colsPins[2] = { KPD_U8_C1_PIN, KPD_U8_C2_PIN };

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_initialization
 Input: void
 Output: void
 Description: Function to initialize Keypad.
*/
void KPD_initialization( void )
{
	/* Set the One Row Pin to Output, therefore One Pin is Output */
	DIO_init( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, OUT );
	
	/* Set the two Col Pins to Input, therefore two Pins are Input */
	DIO_init( KPD_U8_INPUT_PORT, KPD_U8_INPUT_PIN1,IN );
	DIO_init( KPD_U8_INPUT_PORT, KPD_U8_INPUT_PIN2,IN );
	
	/* Write High on one output pins */
	DIO_write( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, HIGH );
	
	/* Enable internal Pull-up resistor on two input pins */
	DIO_write( KPD_U8_INPUT_PORT, KPD_U8_INPUT_PIN1, HIGH );
	DIO_write( KPD_U8_INPUT_PORT, KPD_U8_INPUT_PIN2, HIGH );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_enableKPD
 Input: void
 Output: void
 Description: Function to enable Keypad.
*/
void KPD_enableKPD     ( void )
{
	/* Set the one Pin configured Output to Output, in order to enable or re-enable the KPD, therefore one Pin is Output, and the other two are Input */
	DIO_init( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, OUT );
	
	DIO_write( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, HIGH );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_disableKPD
 Input: void
 Output: void
 Description: Function to disable Keypad.
*/
void KPD_disableKPD    ( void )
{
	/* Set the one Pin configured Output to Input, in order to disable the KPD, therefore all KPD pins are Input */
	DIO_init( KPD_U8_OUTPUT_PORT, KPD_U8_OUTPUT_PIN1, IN );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_getPressedKey
 Input: Pointer to u8 ReturnedKeyValue
 Output: u8 Error or No Error
 Description: Function to check for the pressed key.
*/
u8 KPD_getPressedKey   ( u8 *pu8_a_returnedKeyValue )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
	
	/* Check 1: Pointer is not equal to NULL */
	if ( pu8_a_returnedKeyValue != NULL )
	{
		u8 u8_l_pinValue;
		u8 u8_l_keyFlag = KPD_U8_KEY_NOT_FOUND;
		
		/* Step 1: Update ReturnedKeyValue with the Not Pressed Key value */
		*pu8_a_returnedKeyValue = KPD_U8_KEY_NOT_PRESSED;

		/* Loop: On Rows -> Output ( i.e.: Set Pin ) */
		for ( u8 Loc_u8RowsCounter = 0; Loc_u8RowsCounter < 1; Loc_u8RowsCounter++ )
		{
			/* Step 2: Activate Row ( i.e. Set Pin Low ) */
            DIO_write( KPD_U8_OUTPUT_PORT, Au8_gs_rowsPins[Loc_u8RowsCounter], LOW );

			/* Loop: On Columns -> Input ( i.e. Get Pin ) */
			for ( u8 Loc_u8ColsCounter = 0; Loc_u8ColsCounter <= 1; Loc_u8ColsCounter++ )
			{
				/* Step 3: Get the value of each Key */
				DIO_read( KPD_U8_INPUT_PORT, Au8_gs_colsPins[Loc_u8ColsCounter], &u8_l_pinValue );

				/* Check 1.1.1: Key is Pressed */
				if ( u8_l_pinValue == LOW )
				{
					/* Push buttons often generate spurious open/close transitions when pressed, due to mechanical and physical issues: these transitions may be read as multiple presses in a very short time fooling the program. This example demonstrates how to debounce an input, which means checking twice in a short period of time to make sure the pushbutton is definitely pressed. Without debouncing, pressing the button once may cause unpredictable results. */
					/* Delay debouncing time of the Key */
					//_delay_ms( 20 );
					TMR0_delayMS( 20 );
					
					/* Step 4: Recheck if the Key is still Pressed */
					DIO_read( KPD_U8_INPUT_PORT, Au8_gs_colsPins[Loc_u8ColsCounter], &u8_l_pinValue );

					/* This step assures releasing Key before returning the key value, to avoid returning multiple values for the same Press! */
					/* Loop: Until releasing Key ( i.e. Pin value is High ) */
					while ( u8_l_pinValue == LOW )
					{
						DIO_read( KPD_U8_INPUT_PORT, Au8_gs_colsPins[Loc_u8ColsCounter], &u8_l_pinValue );
					}
					
					/* Step 5: Update ReturnedKeyValue with the Pressed Key value */
					*pu8_a_returnedKeyValue = Au8_gs_keys[Loc_u8RowsCounter][Loc_u8ColsCounter];
					
					/* Step 6: Update Flag to Found */
					u8_l_keyFlag = KPD_U8_KEY_FOUND;
					
					/* Step 7: Break Columns loop */
					break;
				}
			}

			/* Step 8: Deactivate Row ( i.e. Set Pin High ) */
			DIO_write( KPD_U8_OUTPUT_PORT, Au8_gs_rowsPins[Loc_u8RowsCounter], HIGH );

			/* Check 1.1: Flag is Found */
			if ( u8_l_keyFlag == KPD_U8_KEY_FOUND )
			{
				/* Step 9: Break Rows loop */
				break;
			}			
		}
	}
	/* Check 2: Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		u8_l_errorState = STD_TYPES_NOK;
	}
	
	return u8_l_errorState;	
}

/*******************************************************************************************************************************************************************/