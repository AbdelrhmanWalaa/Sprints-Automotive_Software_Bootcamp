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
static const u8 Au8_gs_keys[2][3] = KPD_AU8_KEYS;
//u8 u8_g_pressFlag = 0;

/* Global Arrays of Rows an Columns Pins */
//static const u8 Au8_gs_rowsPins[2] = { KPD_U8_R1_PIN, KPD_U8_R2_PIN };
static const u8 Au8_gs_rowsPins[2] = { 2, 3 };
static const u8 Au8_gs_colsPins[3] = { KPD_U8_C1_PIN, KPD_U8_C2_PIN, KPD_U8_C3_PIN };

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_initKPD
 Input: void
 Output: void
 Description: Function to initialize Keypad.
*/
void KPD_initKPD    ( void )
{
	/* Set the two Row Pins to Output, therefore two Pins are Output */
	DIO_init( KPD_U8_OUTPUT_PIN1, KPD_U8_OUTPUT_PORT, DIO_OUT );
	DIO_init( KPD_U8_OUTPUT_PIN2, KPD_U8_OUTPUT_PORT, DIO_OUT );
	
	/* Set the three Col Pins to Input, therefore three Pins are Input */
	DIO_init( KPD_U8_INPUT_PIN1, KPD_U8_INPUT_PORT, DIO_IN );
	DIO_init( KPD_U8_INPUT_PIN2, KPD_U8_INPUT_PORT, DIO_IN );
	DIO_init( KPD_U8_INPUT_PIN3, KPD_U8_INPUT_PORT, DIO_IN );

	/* Enable internal Pull-up resistor on three input pins */
	DIO_write( KPD_U8_INPUT_PIN1, KPD_U8_INPUT_PORT, DIO_U8_PIN_HIGH );
	DIO_write( KPD_U8_INPUT_PIN2, KPD_U8_INPUT_PORT, DIO_U8_PIN_HIGH );
	DIO_write( KPD_U8_INPUT_PIN3, KPD_U8_INPUT_PORT, DIO_U8_PIN_HIGH );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_enableKPD
 Input: void
 Output: void
 Description: Function to enable Keypad.
*/
void KPD_enableKPD  ( void )
{
	/* Set the two Pins configured Output to Output, in order to enable or re-enable the KPD, therefore two Pins are Output, and the other three are Input */
	DIO_init( 2, PORT_C, DIO_OUT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_disableKPD
 Input: void
 Output: void
 Description: Function to disable Keypad.
*/
void KPD_disableKPD ( void )
{
	/* Set the two Pins configured Output to Input, in order to disable the KPD, therefore all KPD pins are Input */
	DIO_init( 2, PORT_C, DIO_IN );
}

/*******************************************************************************************************************************************************************/
/*
 Name: KPD_getPressedKey
 Input: Pointer to u8 ReturnedKeyValue
 Output: u8 Error or No Error
 Description: Function to check for the pressed key.
*/
u8 KPD_getPressedKey( u8 *pu8_a_returnedKeyValue )
{
	//u8_g_pressFlag = 0;
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
//    *pu8_a_returnedKeyValue = '2';
//    return u8_l_errorState;
	/* Check 1: Pointer is not equal to NULL */
	if ( pu8_a_returnedKeyValue != NULL )
	{
		u8 u8_l_pinValue = DIO_U8_PIN_HIGH;
		u8 u8_l_keyFlag = KPD_U8_KEY_NOT_FOUND;
		
		/* Step 1: Update ReturnedKeyValue with the Not Pressed Key value */
		*pu8_a_returnedKeyValue = KPD_U8_KEY_NOT_PRESSED;

		/* Loop: On Rows -> Output ( i.e.: Set Pin ) */
		for ( u8 Loc_u8RowsCounter = 0; Loc_u8RowsCounter <= 1; Loc_u8RowsCounter++ )
		{

			/* Step 2: Activate Row ( i.e. Set Pin Low ) */
//            DIO_write( 2, PORT_C, DIO_U8_PIN_LOW );
//            DIO_write( 2, KPD_U8_OUTPUT_PORT, DIO_U8_PIN_LOW );

            DIO_write( KPD_U8_R1_PIN + Loc_u8RowsCounter, KPD_U8_OUTPUT_PORT, DIO_U8_PIN_LOW );
//            DIO_write( KPD_U8_R1_PIN + Loc_u8RowsCounter, KPD_U8_OUTPUT_PORT, DIO_U8_PIN_LOW );
//            continue;

			/* Loop: On Columns -> Input ( i.e. Get Pin ) */
			for ( u8 Loc_u8ColsCounter = 0; Loc_u8ColsCounter <= 2; Loc_u8ColsCounter++ )
			{
                u8_l_pinValue = DIO_U8_PIN_HIGH;

				/* Step 3: Get the value of each Key */
//				DIO_read( Au8_gs_colsPins[Loc_u8ColsCounter], KPD_U8_INPUT_PORT, &u8_l_pinValue );
				DIO_read( KPD_U8_C1_PIN + Loc_u8ColsCounter, KPD_U8_INPUT_PORT, &u8_l_pinValue );

				/* Check 1.1.1: Key is Pressed */
				if ( u8_l_pinValue == DIO_U8_PIN_LOW )
				{
					/* Push buttons often generate spurious open/close transitions when pressed, due to mechanical and physical issues: these transitions may be read as multiple presses in a very short time fooling the program. This example demonstrates how to debounce an input, which means checking twice in a short period of time to make sure the pushbutton is definitely pressed. Without debouncing, pressing the button once may cause unpredictable results. */
					/* Delay debouncing time of the Key */
					TIMER_delay_ms( 20 );
					
					/* Step 4: Recheck if the Key is still Pressed */
//					DIO_read( Au8_gs_colsPins[Loc_u8ColsCounter], KPD_U8_INPUT_PORT, &u8_l_pinValue );
					DIO_read( KPD_U8_C1_PIN + Loc_u8ColsCounter, KPD_U8_INPUT_PORT, &u8_l_pinValue );

					/* This step assures releasing Key before returning the key value, to avoid returning multiple values for the same Press! */
					/* Loop: Until releasing Key ( i.e. Pin value is High ) */
					while ( u8_l_pinValue == DIO_U8_PIN_LOW )
					{
						DIO_read( KPD_U8_C1_PIN + Loc_u8ColsCounter, KPD_U8_INPUT_PORT, &u8_l_pinValue );
					}
					
					/* Step 5: Update ReturnedKeyValue with the Pressed Key value */

//					*pu8_a_returnedKeyValue = Au8_gs_keys[Loc_u8RowsCounter][Loc_u8ColsCounter];
					*pu8_a_returnedKeyValue = ((u8 [2][3]){ {'1', '2',  '3'}, {'4', '5',  '0'}  })[Loc_u8RowsCounter][Loc_u8ColsCounter];
					//u8_g_pressFlag = 1;
					/* Step 6: Update Flag to Found */
					u8_l_keyFlag = KPD_U8_KEY_FOUND;
					
					/* Step 7: Break Columns loop */
					break;
				}
			}


			/* Step 8: Deactivate Row ( i.e. Set Pin High ) */
//			DIO_write( Au8_gs_rowsPins[Loc_u8RowsCounter], KPD_U8_OUTPUT_PORT, DIO_U8_PIN_HIGH );
			DIO_write( KPD_U8_R1_PIN + Loc_u8RowsCounter, KPD_U8_OUTPUT_PORT, DIO_U8_PIN_HIGH );

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
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;	
}

/*******************************************************************************************************************************************************************/