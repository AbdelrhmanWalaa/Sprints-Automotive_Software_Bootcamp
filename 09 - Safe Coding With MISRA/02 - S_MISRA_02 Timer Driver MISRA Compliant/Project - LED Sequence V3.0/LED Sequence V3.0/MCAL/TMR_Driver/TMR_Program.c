/*
 * TMR_Program.c
 *
 *     Created on: Jul 27, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TMR) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "TMR_Private.h"
#include "TMR_Config.h"
#include "TMR_Interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Arrays of 3 Pointers to Functions ( because we have 3 Timers ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *Glb_ApfOVFInterruptsAction[3] ) ( void ) = { NULL, NULL, NULL };
static void ( *Glb_ApfCOMPInterruptsAction[3] ) ( void ) = { NULL, NULL, NULL };

/* Global Array of OVF Counters, in case the desired time to be counted; is more than Timer counting register ( TCNTn ), i.e.: to count the number of Overflows. */
static u16 Glb_Au16OVFCounters[3] = { 0, 0, 0 };

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_vdTMR0Initialization
 Input: void
 Output: void
 Description: Function to Initialize TMR0 peripheral.
*/
vd TMR_vdTMR0Initialization ( void )
{
	/* Step 1: Select Waveform Generation Mode */
	switch ( TMR_U8_TMR_0_MODE_SELECT )
	{
		/* Case 1: Waveform Generation Mode = Normal Mode */
		case TMR_U8_TMR_0_NORMAL_MODE			: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT ); break;
		/* Case 2: Waveform Generation Mode = PWM, Phase Correct Mode */
		case TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT ); break;
		/* Case 3: Waveform Generation Mode = CTC Mode */
		case TMR_U8_TMR_0_CTC_MODE				: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT ); break;
		/* Case 4: Waveform Generation Mode = Fast PWM Mode */
		case TMR_U8_TMR_0_FAST_PWM_MODE			: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT ); break;
		
		default:														/* Do Nothing */														break;
	}

	/* Step 2: Select Compare Match Output Mode */
	switch ( TMR_U8_TMR_0_COMP_OUTPUT_MODE )
	{
		/* Case 1: Waveform Generation Mode = Normal Mode */
		case TMR_U8_TMR_0_DISCONNECT_OC0_PIN: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT ); break;
		/* Case 2: Waveform Generation Mode = PWM, Phase Correct Mode */
		case TMR_U8_TMR_0_TOG_OC0_PIN		: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT ); break;
		/* Case 3: Waveform Generation Mode = CTC Mode */
		case TMR_U8_TMR_0_CLR_OC0_PIN		: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT ); break;
		/* Case 4: Set OC0 on compare match ( PWM -> Inverting Mode ) */
		case TMR_U8_TMR_0_SET_OC0_PIN		: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT ); break;
		
		default:													/* Do Nothing */														break;
	}

	/* Step 3: Select Interrupt Source */
	switch ( TMR_U8_TMR_0_INTERRUPT_SELECT )
	{
		/* Case 1: Interrupt Source = No Interrupt ( i.e.: Interrupts are disabled, as in PWM two modes ) */
		case TMR_U8_TMR_0_NO_INTERRUPT  : CLR_BIT( TMR_U8_TIMSK_REG, TMR_U8_OCIE0_BIT ); CLR_BIT( TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT );	break;
		/* Case 2: Interrupt Source = Compare Interrupt */
		case TMR_U8_TMR_0_COMP_INTERRUPT: SET_BIT( TMR_U8_TIMSK_REG, TMR_U8_OCIE0_BIT ); break;
		/* Case 3: Interrupt Source = Overflow Interrupt */
		case TMR_U8_TMR_0_OVF_INTERRUPT : SET_BIT( TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT ); break;
		
		default:						/* Do Nothing */								 break;
	}

	/* Step 4: Set Compare Value and Preload Value */
	/* Compare Value */
	TMR_U8_OCR0_REG  = TMR_U8_TMR_0_COMPARE_VALUE;
	/* Preload value */
	TMR_U8_TCNT0_REG = TMR_U8_TMR_0_PRELOAD_VALUE;

	/* Step 5: Select Clock Source ( i.e.: Start Counting ) */
	switch ( TMR_U8_TMR_0_CLOCK_SELECT )
	{
		/* Case 1: Clock Source = No Clock Source (Timer/Counter0 stopped) */
		case TMR_U8_TMR_0_NO_CLOCK_SOURCE				 : CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 2: Clock Source =  No Prescaler */
		case TMR_U8_TMR_0_NO_PRESCALER					 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 3: Clock Source = 8 Prescaler */
		case TMR_U8_TMR_0_8_PRESCALER					 : CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 4: Clock Source = 64 Prescaler */
		case TMR_U8_TMR_0_64_PRESCALER					 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 5: Clock Source = 256 Prescaler */
		case TMR_U8_TMR_0_256_PRESCALER					 : CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 6: Clock Source = 1024 Prescaler */
		case TMR_U8_TMR_0_1024_PRESCALER				 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 7: Clock Source = External Clock Source with Falling Edge, on Pin TO */
		case TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		/* Case 8: Clock Source = External Clock Source with Rising Edge, on Pin TO */
		case TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
														   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
		
		default:								 /* Do Nothing */										 break;
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8EnableTMR
 Input: u8 TimerId
 Output: u8 Error or No Error
 Description: Function to Enable TMR peripheral.
*/
u8 TMR_u8EnableTMR		     ( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: TimertId is in the valid range */
	if ( Cpy_u8TimerId <= TMR_U8_TMR2 )
	{
		/* Check 1.1: Required TimerId */
		switch ( Cpy_u8TimerId )
		{
			case TMR_U8_TMR0:
			{
				/* Step 1: Set Compare Value and Preload Value */
				/* Compare Value */
				//TMR_U8_OCR0_REG  = TMR_U8_TMR_0_COMPARE_VALUE;
				/* Preload value */
				//TMR_U8_TCNT0_REG = TMR_U8_TMR_0_PRELOAD_VALUE;

				/* Step 2: Select Clock Source ( i.e.: Start Counting ) */
				switch ( TMR_U8_TMR_0_CLOCK_SELECT )
				{
					/* Case 1: Clock Source = No Prescaler */
					case TMR_U8_TMR_0_NO_PRESCALER					 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 2: Clock Source = 8 Prescaler */
					case TMR_U8_TMR_0_8_PRESCALER					 : CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 3: Clock Source = 64 Prescaler */
					case TMR_U8_TMR_0_64_PRESCALER					 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 4: Clock Source = 256 Prescaler */
					case TMR_U8_TMR_0_256_PRESCALER					 : CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 5: Clock Source = 1024 Prescaler */
					case TMR_U8_TMR_0_1024_PRESCALER				 : SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 6: Clock Source = External Clock Source with Falling Edge, on Pin TO */
					case TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE: CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
					/* Case 7: Clock Source = External Clock Source with Rising Edge, on Pin TO */
					case TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE: SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
																	   SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT ); break;
																	   
					default:									/* Do Nothing */								     break;
				}
				break;
			}

			case TMR_U8_TMR1:
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
			
			case TMR_U8_TMR2:
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
						
			default:
			{
				/* Do Nothing */
				break;
			}
		}
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8DisableTMR
 Input: u8 TimerId
 Output: u8 Error or No Error
 Description: Function to Disable TMR peripheral.
*/
u8 TMR_u8DisableTMR		     ( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: TimertId is in the valid range */
	if ( Cpy_u8TimerId <= TMR_U8_TMR2 )
	{
		/* Check 1.1: Required TimerId */
		switch ( Cpy_u8TimerId )
		{
			case TMR_U8_TMR0:
			{
				/* Step 1: Disconnect COMP ( OC0 ) Pin */
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
							
				/* Step 2: Clock Source = No Clock Source ( Timer/Counter0 stopped ) */
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT ); CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );	CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );

				/* Step 3: Clear Timer/Counter0 OVF Flag */
				SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT );

				/* Step 4: Clear Compare Value and Preload Value */
				/* Compare Value */
				TMR_U8_OCR0_REG  = 0x00;
				/* Clear TMR0 */
				TMR_U8_TCNT0_REG = 0x00;

				/* Step 5: Reset the OVF Counter of Timer/Counter0 to 0 */
				Glb_Au16OVFCounters[TMR_U8_TMR0] = 0;

				break;
			}

			case TMR_U8_TMR1:
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
			
			case TMR_U8_TMR2:
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
			
			default:
			{
				/* Do Nothing */				
				break;
			}
		}
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8DelayMS
 Input: u8 TimerId and u32 Delay
 Output: u8 Error or No Error
 Description: Function to use TMR peripheral as Delay in MS.
*/
u8 TMR_u8DelayMS			 ( u8 Cpy_u8TimerId, u32 Cpy_u32Delay )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;
	
	/* Define local variables to store number of overflows ( initially set to 1 ), and store counter ( initially set to 0 ) value */
	u32 Loc_u32NumberOfOVFs = 1;
	u32 Loc_u32Counter = 0;
	
	/* Define local variables to store timer tick time and timer max delay */
	f32 Loc_f32TickTime = 0;
	f32 Loc_f32TimerMaxDelay = 0;
	
	/* Define local variables to be used when adjusting the number of overflows to u32 type */
	f32 Loc_f32Result = 0;
	f32 Loc_f32Number = 0;
	f32 Loc_f32Fraction = 0;
	
	/* Define local variable to set the overflow flag state = DOWN */
	u8 Loc_u8OVFFlagStatus = TMR_U8_FLAG_DOWN;

	/* Check 1: TimertId is in the valid range */
	if ( Cpy_u8TimerId <= TMR_U8_TMR2 )
	{		
		/* Step 1: Disable Timer */
		TMR_u8DisableTMR( Cpy_u8TimerId );
		
		/* Check 1.1: Required TimerId */
		switch ( Cpy_u8TimerId )
		{
			case TMR_U8_TMR0:
			{
				/* Step 2: Calculate TickTime = ( Prescaler / F_CPU ) * 1000 */
				/* Example: Prescaler = 1, F_CPU = 1MHz */
				/* Answer : TickTime = ( 1 / 1000000 ) = 0.000001 sec * 1000 = 0.001 msec */
				Loc_f32TickTime = ( 1.0 / F_CPU ) * 1000;

				/* Step 3: Calculate TimerMaxDelay = TickTime * ( 2 ^ TimerResolution ) */
				/* Example: TickTime = 0.001 msec, TimerResolution = 8 */
				/* Answer : TimerMaxDelay = 0.001 * 256 = 0.256 msec */
				Loc_f32TimerMaxDelay = Loc_f32TickTime * pow( 2, TMR_U8_TMR0_RESOLUTION );
				
				/* Check 1.1.1: TimerMaxDelay > Delay */
				if ( Loc_f32TimerMaxDelay > Cpy_u32Delay )
				{
					/* Step 3.1: Calculate TimerPreloadValue = ( TimerMaxDelay - Delay ) / TickTime */
					/* Example: TimerMaxDelay = 0.256 msec => 256 usec, Delay = 0.200 msec => 200 usec, TickTime = 0.001 msec */
					/* Answer : TimerPreloadValue = ( 0.256 - 0.200 ) / 0.001 = 56 */
					TMR_U8_TCNT0_REG = ( u8 ) ( ( Loc_f32TimerMaxDelay - Cpy_u32Delay ) / Loc_f32TickTime );
				}
				/* Check 1.1.2: TimerMaxDelay <= Delay */
				else if ( Loc_f32TimerMaxDelay <= Cpy_u32Delay )
				{
					/* Step 3.1: Calculate NumberOfOVFs and TimerPreloadValue */
					/*           1. Delay / TimerMaxDelay = Number.Fraction
					 *			 2. NumberOfOVFs = Number + 1
					 *			 3. TimerPreloadValue = ( 2 ^ TimerResolution ) - ( Fraction * ( 2 ^ TimerResolution ) )
					 */
					/* Example: TimerMaxDelay = 0.256 msec, Delay = 100 msec */
					/* Answer : 100 / 0.256 = 390.625
					 *			NumberOfOVFs = 390 + 1 = 391
					 *			TimerPreloadValue = ( 2 ^ 8 ) - ( 0.625 * ( 2 ^ 8 ) ) = 96
					 */
					Loc_f32Result = ( f32 ) ( Cpy_u32Delay / Loc_f32TimerMaxDelay );
					Loc_f32Fraction = modff( Loc_f32Result, &Loc_f32Number );
					Loc_u32NumberOfOVFs = ( u32 ) ( Loc_f32Number + 1 );
					
					TMR_U8_TCNT0_REG = ( u8 ) ( pow( 2, TMR_U8_TMR0_RESOLUTION ) - ( Loc_f32Fraction * pow( 2, TMR_U8_TMR0_RESOLUTION ) ) );
				}
								
				break;
			}
			
			case TMR_U8_TMR1: 
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
			
			case TMR_U8_TMR2:
			{
				/* Future Improvements ?? ??? ???? */
				break;
			}
			
			default:
			{
				/* Do Nothing */
				break;
			}
		}

		/* Step 4: Enable Timer */
		TMR_u8EnableTMR( Cpy_u8TimerId );
				
		/* Loop: Until Counter = NumberOfOVFs */
		while ( Loc_u32NumberOfOVFs > Loc_u32Counter )
		{
			/* Loop: Until OVFFlagStatus is set ( i.e.: Timer overflow occurs ) */
			while ( Loc_u8OVFFlagStatus == TMR_U8_FLAG_DOWN )
			{
				/* Step 5: Get OVFFlagStatus */
				TMR_u8GetOVFFlagStatus( Cpy_u8TimerId, &Loc_u8OVFFlagStatus );
			}
			
			/* Step 6: Reset OVFFlagStatus value */
			Loc_u8OVFFlagStatus = TMR_U8_FLAG_DOWN;
			/* Step 7: Increment Counter */
			Loc_u32Counter++;
			/* Step 8: Clear OVFFlag ( i.e.: TOVn bit in TIFR register ) */
			TMR_u8ClearOVFFlag( Cpy_u8TimerId );
		}
		
		/* Step 9: Disable Timer */
		TMR_u8DisableTMR( Cpy_u8TimerId );
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8GetOVFFlagStatus
 Input: u8 TimerId and Pointer to u8 ReturnedFlagStatus
 Output: u8 Error or No Error
 Description: Function to Get status of the OVF Flag in TMR peripheral.
*/
u8 TMR_u8GetOVFFlagStatus    ( u8 Cpy_u8TimerId, u8 *Cpy_pu8ReturnedFlagStatus )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: TimertId is in the valid range, and Pointer is not equal to NULL */
	if ( ( Cpy_u8TimerId <= TMR_U8_TMR2 ) && ( Cpy_pu8ReturnedFlagStatus != NULL ) )
	{
		/* Check 1.1: Required TimerId */
		switch ( Cpy_u8TimerId )
		{
			case TMR_U8_TMR0: *Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT ); break;
			case TMR_U8_TMR1: *Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV1_BIT ); break;
			case TMR_U8_TMR2: *Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV2_BIT ); break;
			default:								/* Do Nothing */								    break;
		}
	}
	/* Check 2: TimertId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong TimertId or Pointer is NULL! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8ClearOVFFlag
 Input: u8 TimerId
 Output: u8 Error or No Error
 Description: Function to Clear the OVF Flag in TMR peripheral.
*/
u8 TMR_u8ClearOVFFlag	     ( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_TYPES_OK;

	/* Check 1: TimertId is in the valid range */
	if ( Cpy_u8TimerId <= TMR_U8_TMR2 )
	{
		/* Check 1.1: Required TimerId */
		switch ( Cpy_u8TimerId )
		{
			case TMR_U8_TMR0: SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT ); break;
			case TMR_U8_TMR1: SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV1_BIT ); break;
			case TMR_U8_TMR2: SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV2_BIT ); break;
			default:				 /* Do Nothing */					   break;
		}
	}
	/* Check 2: TimertId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_u8ErrorState = STD_TYPES_NOK;
	}

	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/

/*
 *  8-bit Timer/Counter0 ISR
 */
/* ISR functions' prototypes of TMR0 Compare Match ( COMP ), and TMR0 Overflow ( OVF ) respectively */
void __vector_10( void )	__attribute__((signal));
void __vector_11( void )	__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TMR0 COMP */
void __vector_10( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer0 counting register ( TCNT0 = 8 bits ), i.e.: to count the number of Overflows */
	static u16 Loc_u16CounterCOMP = 0;

	/* Increment the COMP Counter after every Overflow in Timer0 counting register */
	Loc_u16CounterCOMP++;

	/* Check 1: The COMP Counter reached the desired number of Overflows */
	if ( Loc_u16CounterCOMP >= TMR_U16_TMR_0_NUM_OF_OVERFLOWS )
	{
		/* Reset the COMP Counter to 0 */
		Loc_u16CounterCOMP = 0;

		/* Check 1.1: TMR0 index of the Global Array is not equal to NULL */
		if ( Glb_ApfCOMPInterruptsAction[TMR_U8_TMR0] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( COMPInterruptsAction ) */
			Glb_ApfCOMPInterruptsAction[TMR_U8_TMR0]();
		}
	}
}

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TMR0 OVF */
void __vector_11( void )
{
	/* Increment the OVF Counter after every Overflow in Timer0 counting register */
	Glb_Au16OVFCounters[TMR_U8_TMR0]++;

	/* Check 1: The OVF Counter reached the desired number of Overflows */
	if ( Glb_Au16OVFCounters[TMR_U8_TMR0] >= TMR_U16_TMR_0_NUM_OF_OVERFLOWS )
	{
		/* Reset Preload Value */
		TMR_U8_TCNT0_REG = TMR_U8_TMR_0_PRELOAD_VALUE;

		/* Reset the OVF Counter to 0 */
		Glb_Au16OVFCounters[TMR_U8_TMR0] = 0;

		/* Check 1.1: TMR0 index of the Global Array is not equal to NULL */
		if ( Glb_ApfOVFInterruptsAction[TMR_U8_TMR0] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( OVFInterruptsAction ) */
			Glb_ApfOVFInterruptsAction[TMR_U8_TMR0]();
		}
	}
}

/*******************************************************************************************************************************************************************/