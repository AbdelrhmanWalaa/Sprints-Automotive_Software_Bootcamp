/*
* TMR_Program.c
*
*     Created on: Jul 27, 2021
*         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
*    Description: This file contains all Timers (TMR) functions' implementation, and ISR functions' prototypes and implementation.
*  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
*	   Copyright: MIT License
*	   
*	              Copyright (c) Abdelrhman Walaa
*	   
*	              Permission is hereby granted, free of charge, to any person obtaining a copy
*	              of this software and associated documentation files (the "Software"), to deal
*	              in the Software without restriction, including without limitation the rights
*	              to use, copy, modify, merge, publish, distribute, sub license, and/or sell
*	              copies of the Software, and to permit persons to whom the Software is
*	              furnished to do so, subject to the following conditions:
*	   
*	              The above copyright notice and this permission notice shall be included in all
*	              copies or substantial portions of the Software.
*	   
*	              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	              IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	              FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	              AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	              LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*		           SOFTWARE.
*/

/* MCAL */
#include "TMR_Interface.h"
#include "TMR_Config.h"
#include "TMR_Private.h"

/*******************************************************************************************************************************************************************/
/* TMR Global Variables */

/* Global Arrays of 3 Pointers to Functions ( because we have 3 Timers ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( *Glb_ApfOVFInterruptsAction[3] ) ( void ) = { STD_TYPES_NULL, STD_TYPES_NULL, STD_TYPES_NULL };
static void ( *Glb_ApfCOMPInterruptsAction[3] ) ( void ) = { STD_TYPES_NULL, STD_TYPES_NULL, STD_TYPES_NULL };

/* Global Array of OVF Counters, in case the desired time to be counted; is more than Timer counting register ( TCNTn ), i.e.: to count the number of Overflows. */
static u16 Glb_Au16OVFCounters[3] = { 0, 0, 0 };

/*******************************************************************************************************************************************************************/
/* TMR Static Functions' Prototypes */

static bool TMR_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 );
static bool TMR_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue );
static bool TMR_boolIsNullPointer ( const vd *Cpy_pvdPointer );

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_vdTMR0Initialization
 Input: void
 Output: void
 Description: Function to Initialize TMR0 peripheral.
*/
void TMR_vdTMR0Initialization( void )
{
	/* Step 1: Select Waveform Generation Mode */
	/* Check 1.1: Waveform Generation Mode is Normal Mode */
	if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_MODE_SELECT, TMR_U8_TMR_0_NORMAL_MODE ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT );
	}
	/* Check 1.2: Waveform Generation Mode is PWM, Phase Correct Mode */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_MODE_SELECT, TMR_U8_TMR_0_PWM_PHASE_CORRECT_MODE ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT );
	}
	/* Check 1.3: Waveform Generation Mode is CTC Mode */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_MODE_SELECT, TMR_U8_TMR_0_CTC_MODE ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT );
	}
	/* Check 1.4: Waveform Generation Mode is Fast PWM Mode */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_MODE_SELECT, TMR_U8_TMR_0_FAST_PWM_MODE ) )
	{
		 SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT );
		 SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT );
	}
	/* Check 1.5: Waveform Generation Mode is Invalid */
	else
	{
		/* Do Nothing */
	}

	/* Step 2: Select Compare Match Output Mode */
	/* Check 2.1: Compare Match Output Mode is Disconnect OC0 on compare match */
	if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_COMP_OUTPUT_MODE, TMR_U8_TMR_0_DISCONNECT_OC0_PIN ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT ); 
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
	}
	/* Check 2.2: Compare Match Output Mode is Toggle OC0 on compare match */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_COMP_OUTPUT_MODE, TMR_U8_TMR_0_TOG_OC0_PIN ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
	}
	/* Check 2.3: Compare Match Output Mode is Clear OC0 on compare match */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_COMP_OUTPUT_MODE, TMR_U8_TMR_0_CLR_OC0_PIN ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
	}
	/* Check 2.4: Compare Match Output Mode is Set OC0 on compare match ( PWM -> Inverting Mode ) */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_COMP_OUTPUT_MODE, TMR_U8_TMR_0_SET_OC0_PIN ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
	}
	/* Check 2.5: Compare Match Output Mode is Invalid */
	else
	{
		/* Do Nothing */
	}

	/* Step 3: Select Interrupt Source */
	/* Check 3.1: Interrupt Source is No Interrupt ( i.e.: Interrupts are disabled, as in PWM two modes ) */
	if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_INTERRUPT_SELECT, TMR_U8_TMR_0_NO_INTERRUPT ) )
	{
		CLR_BIT( TMR_U8_TIMSK_REG, TMR_U8_OCIE0_BIT );
		CLR_BIT( TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT );
	}
	/* Check 3.2: Interrupt Source is Compare Interrupt */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_INTERRUPT_SELECT, TMR_U8_TMR_0_COMP_INTERRUPT ) )
	{
		SET_BIT( TMR_U8_TIMSK_REG, TMR_U8_OCIE0_BIT );
	}
	/* Check 3.3: Interrupt Source is Overflow Interrupt */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_INTERRUPT_SELECT, TMR_U8_TMR_0_OVF_INTERRUPT ) )
	{
		SET_BIT( TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT );
	}
	/* Check 3.4: Interrupt Source is Invalid */
	else
	{
		/* Do Nothing */
	}

	/* Step 4: Set Compare Value and Preload Value */
	/* Compare Value */
	TMR_U8_OCR0_REG  = TMR_U8_TMR_0_COMPARE_VALUE;
	/* Preload value */
	TMR_U8_TCNT0_REG = TMR_U8_TMR_0_PRELOAD_VALUE;

	/* Step 5: Select Clock Source ( i.e.: Start Counting ) */
	/* Check 5.1: Clock Source is No Clock Source (Timer/Counter0 stopped) */
	if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_NO_CLOCK_SOURCE ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.2: Clock Source is No Prescaler */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_NO_PRESCALER ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.3: Clock Source is 8 Prescaler */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_8_PRESCALER ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.4: Clock Source is 64 Prescaler */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_64_PRESCALER ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.5: Clock Source is 256 Prescaler */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_256_PRESCALER ) )
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.6: Clock Source is 1024 Prescaler */
	else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_1024_PRESCALER ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.7: Clock Source is External Clock Source with Falling Edge, on Pin TO */
	else if (  TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE ) )	
	{
		CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}
	/* Check 5.8: Clock Source is External Clock Source with Rising Edge, on Pin TO */
	else if ( TMR_boolAreEqualValues ( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE ) )
	{
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
		SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
	}	
	/* Check 5.9: Interrupt Source is Invalid */
	else
	{
		/* Do Nothing */
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_enEnableTMR
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Enable TMR peripheral.
*/
TMR_enErrorState_t TMR_enEnableTMR( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	TMR_enErrorState_t Loc_enErrorState = TMR_EN_OK;

	/* Check 1: TimertId is in the valid range */
	if ( TMR_boolIsInValidRange( Cpy_u8TimerId, TMR_U8_TMR2 ) )
	{
		/* Check 1.1: Required TimerId is TMR0 */
		if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR0 ) )
		{
			/* Step 1: Set Compare Value and Preload Value */
			/* Compare Value */
			//TMR_U8_OCR0_REG  = TMR_U8_TMR_0_COMPARE_VALUE;
			/* Preload value */
			//TMR_U8_TCNT0_REG = TMR_U8_TMR_0_PRELOAD_VALUE;
			
			/* Step 2: Select Clock Source ( i.e.: Start Counting ) */
			/* Check 1.1.1: Clock Source is No Clock Source (Timer/Counter0 stopped) */
			if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_NO_CLOCK_SOURCE ) )
			{
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.2: Clock Source is No Prescaler */
			else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_NO_PRESCALER ) )
			{
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.3: Clock Source is 8 Prescaler */
			else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_8_PRESCALER ) )
			{
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.4: Clock Source is 64 Prescaler */
			else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_64_PRESCALER ) )
			{
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.5: Clock Source is 256 Prescaler */
			else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_256_PRESCALER ) )
			{
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.6: Clock Source is 1024 Prescaler */
			else if ( TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_1024_PRESCALER ) )
			{
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.7: Clock Source is External Clock Source with Falling Edge, on Pin TO */
			else if (  TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE ) )
			{
				CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.8: Clock Source is External Clock Source with Rising Edge, on Pin TO */
			else if (  TMR_boolAreEqualValues( TMR_U8_TMR_0_CLOCK_SELECT, TMR_U8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE ) )
			{
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
				SET_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );
			}
			/* Check 1.1.9: Interrupt Source is Invalid */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.2: Required TimerId is TMR1 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR1 ) )
		{
			/* Future Improvements */
		}
		/* Check 1.3: Required TimerId is TMR2 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR2 ) )
		{
			/* Future Improvements */
		}
		/* Check 1.4: Required TimerId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_enErrorState = TMR_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_enDisableTMR
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Disable TMR peripheral.
*/
TMR_enErrorState_t TMR_enDisableTMR( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	TMR_enErrorState_t Loc_enErrorState = TMR_EN_OK;

	/* Check 1: TimertId is in the valid range */
	if ( TMR_boolIsInValidRange( Cpy_u8TimerId, TMR_U8_TMR2 ) )
	{
		/* Check 1.1: Required TimerId is TMR0 */
		if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR0 ) )
		{
			/* Step 1: Disconnect COMP ( OC0 ) Pin */
			CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM00_BIT );
			CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_COM01_BIT );
				
			/* Step 2: Clock Source = No Clock Source ( Timer/Counter0 stopped ) */
			CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT );
			CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT );
			CLR_BIT( TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT );

			/* Step 3: Clear Timer/Counter0 OVF Flag */
			SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT );

			/* Step 4: Clear Compare Value and Preload Value */
			/* Compare Value */
			TMR_U8_OCR0_REG  = 0x00;
			/* Clear TMR0 */
			TMR_U8_TCNT0_REG = 0x00;

			/* Step 5: Reset the OVF Counter of Timer/Counter0 to 0 */
			Glb_Au16OVFCounters[TMR_U8_TMR0] = 0;			
		}
		/* Check 1.2: Required TimerId is TMR1 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR1 ) )
		{
			/* Future Improvements */		
		}
		/* Check 1.3: Required TimerId is TMR2 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR2 ) )
		{
			/* Future Improvements */
		}
		/* Check 1.4: Required TimerId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_enErrorState = TMR_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_enDelayMS
 Input: u8 TimerId and u32 Delay
 Output: en Error or No Error
 Description: Function to use TMR peripheral as Delay in MS.
*/
TMR_enErrorState_t TMR_enDelayMS( u8 Cpy_u8TimerId, u32 Cpy_u32Delay )
{
	/* Define local variable to set the error state = OK */
	TMR_enErrorState_t Loc_enErrorState = TMR_EN_OK;
	
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
	if ( TMR_boolIsInValidRange( Cpy_u8TimerId, TMR_U8_TMR2 ) )
	{		
		/* Step 1: Disable Timer */
		TMR_enDisableTMR( Cpy_u8TimerId );
		
		/* Check 1.1: Required TimerId is TMR0 */
		if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR0 ) )
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
			/* Check 1.1.3 */
			else
			{
				/* Do Nothing */
			}
		}
		/* Check 1.2: Required TimerId is TMR1 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR1 ) )
		{
			/* Future Improvements */
		}
		/* Check 1.3: Required TimerId is TMR2 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR2 ) )
		{
			/* Future Improvements */
		}
		/* Check 1.4: Required TimerId is Invalid */
		else
		{
			/* Do Nothing */
		}
		
		/* Step 4: Enable Timer */
		TMR_enEnableTMR( Cpy_u8TimerId );
				
		/* Loop: Until Counter = NumberOfOVFs */
		while ( Loc_u32NumberOfOVFs > Loc_u32Counter )
		{
			/* Loop: Until OVFFlagStatus is set ( i.e.: Timer overflow occurs ) */
			while ( Loc_u8OVFFlagStatus == TMR_U8_FLAG_DOWN )
			{
				/* Step 5: Get OVFFlagStatus */
				TMR_enGetOVFFlagStatus( Cpy_u8TimerId, &Loc_u8OVFFlagStatus );
			}
			
			/* Step 6: Reset OVFFlagStatus value */
			Loc_u8OVFFlagStatus = TMR_U8_FLAG_DOWN;
			/* Step 7: Increment Counter */
			Loc_u32Counter++;
			/* Step 8: Clear OVFFlag ( i.e.: TOVn bit in TIFR register ) */
			TMR_enClearOVFFlag( Cpy_u8TimerId );
		}
		
		/* Step 9: Disable Timer */
		TMR_enDisableTMR( Cpy_u8TimerId );
	}
	/* Check 2: TimertId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_enErrorState = TMR_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_enGetOVFFlagStatus
 Input: u8 TimerId and Pointer to u8 ReturnedFlagStatus
 Output: en Error or No Error
 Description: Function to Get status of the OVF Flag in TMR peripheral.
*/
TMR_enErrorState_t TMR_enGetOVFFlagStatus( u8 Cpy_u8TimerId, u8 *Cpy_pu8ReturnedFlagStatus )
{
	/* Define local variable to set the error state = OK */
	TMR_enErrorState_t Loc_enErrorState = TMR_EN_OK;

	/* Check 1: TimertId is in the valid range, and Pointer is not equal to NULL */
	if ( ( TMR_boolIsInValidRange( Cpy_u8TimerId, TMR_U8_TMR2 ) )			&&
		 ( TMR_boolIsNullPointer ( Cpy_pu8ReturnedFlagStatus ) ) )
	{
		/* Check 1.1: Required TimerId is TMR0 */
		if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR0 ) )
		{
			*Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT );
		}
		/* Check 1.2: Required TimerId is TMR1 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR1 ) )
		{
			*Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV1_BIT );
		}
		/* Check 1.3: Required TimerId is TMR2 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR2 ) )
		{
			*Cpy_pu8ReturnedFlagStatus = GET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV2_BIT );
		}
		/* Check 1.4: Required TimerId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: TimertId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong TimertId or Pointer is NULL! */
		Loc_enErrorState = TMR_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_enClearOVFFlag
 Input: u8 TimerId
 Output: en Error or No Error
 Description: Function to Clear the OVF Flag in TMR peripheral.
*/
TMR_enErrorState_t TMR_enClearOVFFlag( u8 Cpy_u8TimerId )
{
	/* Define local variable to set the error state = OK */
	TMR_enErrorState_t Loc_enErrorState = TMR_EN_OK;

	/* Check 1: TimertId is in the valid range */
	if ( TMR_boolIsInValidRange( Cpy_u8TimerId, TMR_U8_TMR2 ) )
	{
		/* Check 1.1: Required TimerId is TMR0 */
		if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR0 ) )
		{
			SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV0_BIT );
		}
		/* Check 1.2: Required TimerId is TMR1 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR1 ) )
		{
			SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV1_BIT );
		}
		/* Check 1.3: Required TimerId is TMR2 */
		else if ( TMR_boolAreEqualValues( Cpy_u8TimerId, TMR_U8_TMR2 ) )
		{
			SET_BIT( TMR_U8_TIFR_REG, TMR_U8_TOV2_BIT );
		}
		/* Check 1.4: Required TimerId is Invalid */
		else
		{
			/* Do Nothing */
		}
	}
	/* Check 2: TimertId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong TimertId! */
		Loc_enErrorState = TMR_EN_NOK;
	}

	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_boolAreEqualValues
 Input: u8 Value1 and u8 Value2
 Output: bool True or False
 Description: Function to check whether the Values passed are equal.
*/
static bool TMR_boolAreEqualValues( u8 Cpy_u8Value1, u8 Cpy_u8Value2 )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
		
	/* Check: Values passed are equal */
	if ( Cpy_u8Value1 != Cpy_u8Value2 )
	{
		/* Update error state = FALSE, Different Values! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
		
	return Loc_boolErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_boolIsInValidRange
 Input: u8 Value and u8 MaxValue
 Output: bool True or False
 Description: Function to check whether the Value passed, lies within its valid range.
*/
static bool TMR_boolIsInValidRange( u8 Cpy_u8Value, u8 Cpy_u8MaxValue )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
	
	/* Check: Value passed lies within its valid range */
	if ( Cpy_u8Value > Cpy_u8MaxValue )
	{
		/* Update error state = FALSE, Wrong Value! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
	
	return Loc_boolErrorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: TMR_boolIsNullPointer
 Input: Pointer to vd Pointer
 Output: bool True or False
 Description: Function to check whether the Pointer passed, is a Null Pointer.
*/
static bool TMR_boolIsNullPointer( const vd *Cpy_pvdPointer )
{
	/* Define Local Variable to set the error state = TRUE */
	bool Loc_boolErrorState = STD_TYPES_TRUE;
		
	/* Check: Pointer passed is a Null Pointer */
	if ( Cpy_pvdPointer == STD_TYPES_NULL )
	{
		/* Update error state = FALSE, Null Pointer! */
		Loc_boolErrorState = STD_TYPES_FALSE;
	}
		
	return Loc_boolErrorState;
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
		if ( TMR_boolIsNullPointer( Glb_ApfCOMPInterruptsAction[TMR_U8_TMR0] ) )
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
		if ( TMR_boolIsNullPointer( Glb_ApfCOMPInterruptsAction[TMR_U8_TMR0] ) )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( OVFInterruptsAction ) */
			Glb_ApfOVFInterruptsAction[TMR_U8_TMR0]();
		}
	}
}

/*******************************************************************************************************************************************************************/