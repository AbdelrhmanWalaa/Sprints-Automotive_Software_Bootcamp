/*
 * stmr_program.c
 *
 *     Created on: Jun 15, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all System Timer (STMR) functions' implementation, and IRQ handlers implementation.
 *  MCU Datasheet: Tiva� TM4C123GH6PM - https://www.ti.com/lit/pdf/spms376
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
#include "stmr_interface.h"
#include "stmr_private.h"

/*******************************************************************************************************************************************************************/
/* STMR Global Variables */

/* Global Pointer to Function, this function ( in an Upper Layer ) which this Pointer will hold its address; is having void input argument and void return type. */
static void ( *vpf_gs_timerInterruptAction ) ( void ) = STD_TYPES_NULL;

/* Global variable of DesiredNumberOfOVFs, to count the number of Overflows in case the desired time to be counted; is more than STMR counting register ( STRELOAD ). */
static u32 u32_gs_desiredNumberOfOVFs = 0;
/* Global variable of CurrentNumberOfOVFs, to store the current number of Overflows. */
static u32 u32_gs_currentNumberOfOVFs = 0;

/* Global variables to store STMR TimerTickTime and TimerMaxTime. */
static f32 f32_gs_timerTickTime = 0;
static f32 f32_gs_timerMaxTime = 0;
	
/*******************************************************************************************************************************************************************/
/*
 Name: STMR_initialization
 Input: Pointer to st TimerLinkConfig
 Output: en Error or No Error
 Description: Function to initialize STMR Timer peripheral using Linking Configurations.
*/
STMR_enErrorState_t STMR_initialization( const STMR_stTimerLinkConfig_t *pst_a_timerLinkConfig )
{
	/* Define local variable to set the error state = OK. */
	STMR_enErrorState_t en_l_errorState = STMR_EN_OK;
	
	/* Check 1: Pointer is not equal to NULL. */
	if ( pst_a_timerLinkConfig != STD_TYPES_NULL )
	{
		/* Check 1.1: TimerClockSource, TimerMode, and TimerInterruptMode are in the valid range. */
		if ( ( pst_a_timerLinkConfig->en_a_timerClockSource < STMR_EN_INVALID_CLK_SRC )               &&
				 ( pst_a_timerLinkConfig->en_a_timerMode < STMR_EN_INVALID_TIMER_MODE )                   &&
				 ( pst_a_timerLinkConfig->en_a_timerInterruptMode < STMR_EN_INVALID_TIMER_INT_MODE ) )
		{
			/* Step 1: Calculate TimerTickTime = 1000 us / System Clock Frequency */
			/* Example: System Clock Frequency = 16 MHz */
			/* Answer : TimerTickTime = ( 1000 / 16000000 ) = 0.0000625 msec */
			f32_gs_timerTickTime = ( f32 ) ( 1000.0 / ( u32 ) F_CPU );
			
			/* Step 2: Calculate TimerMaxTime = TimerTickTime * ( 2 ^ TimerResolution ) */
			/* Example: TimerTickTime = 0.0000625 msec, TimerResolution = 24 */
			/* Answer : TimerMaxTime = 0.0000625 * ( 2 ^ 24 ) = 1048.576 msec */
			f32_gs_timerMaxTime = f32_gs_timerTickTime * pow( 2, STMR_U8_RESOLUTION );
			
			/* Step 3: Select Timer Clock Source. */
			switch ( pst_a_timerLinkConfig->en_a_timerClockSource )
			{
				case STMR_EN_PIOSC_DIV_BY_4: CLR_BIT( STMR_U32_STCTRL_REG, STMR_U8_CLK_SRC_BIT ); break;
				case STMR_EN_SYSTEM_CLK    : SET_BIT( STMR_U32_STCTRL_REG, STMR_U8_CLK_SRC_BIT ); break;
				default:                         /* Do Nothing. */                                break;
			}
			
			/* Step 4: Select Timer Interrupt Mode. */
			switch ( pst_a_timerLinkConfig->en_a_timerInterruptMode )
			{
				case STMR_EN_DISABLED_TIMER_INT:
				{
					CLR_BIT( STMR_U32_STCTRL_REG, STMR_U8_INTEN_BIT );
					
					/* Step 4.1: Disable Interrupt in the NVIC peripheral. */
					NVIC_DisableIRQ( SysTick_IRQn );
					
					break;
				}
				
				case STMR_EN_ENABLED_TIMER_INT : 
				{
					/* Step 4.2: Store the passed address of function through pointer to function ( TimerInterruptAction ) into the Global Pointer to Function ( TimerInterruptAction ). */
					/* Check 1.1.1: Pointer is not equal to NULL. */
					if ( pst_a_timerLinkConfig->vpf_a_timerInterruptAction != STD_TYPES_NULL )
					{
						vpf_gs_timerInterruptAction = pst_a_timerLinkConfig->vpf_a_timerInterruptAction;
					}
					/* Check 1.1.1: Pointer is equal to NULL. */
					else
					{
						/* Update error state = NOK, Pointer is NULL! */
						en_l_errorState = STMR_EN_NOK;
					}
					
					SET_BIT( STMR_U32_STCTRL_REG, STMR_U8_INTEN_BIT );
					
					/* Step 4.2: Enable Interrupt in the NVIC peripheral. */
					NVIC_EnableIRQ( SysTick_IRQn );
					
					/* Step 4.3: Enable Interrupts. */
					__enable_irq();
					
					break;			
				}
				
				default:
				{
					/* Do Nothing. */
					break;
				}
			}
				
			/* Step 5: Program the value in the STRELOAD register. */
			STMR_U32_STRELOAD_REG = STMR_U32_MAX_RELOAD_VALUE;
			
			/* Step 6: Clear the STCURRENT register by writing to it with any value. */
			STMR_U32_STCURRENT_REG = 0;
		}
		/* Check 1.2: TimerClockSource, TimerMode, or TimerInterruptMode is not in the valid range. */
		else
		{
			/* Update error state = NOK, Wrong TimerClockSource, TimerMode, or TimerInterruptMode! */
			en_l_errorState = STMR_EN_NOK;
		}
	}
	/* Check 2: Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		en_l_errorState = STMR_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_setTimerMS
 Input: u32 TimeMS
 Output: void
 Description: Function to set STMR peripheral to count MS.
*/
void STMR_setTimerMS( u32 u32_a_timeMS )
{
	/* Define local variable to be used when calculating ReloadValue. */
	u32 u32_l_timerReloadValue = 0;
	
	/* Define local variables to be used when adjusting the DesiredNumberOfOVFs to u32 type. */
	f32 f32_l_result = 0;
	f32 f32_l_number = 0;
	f32 f32_l_fraction = 0;
	
	/* Step 1: Disable Timer */
	STMR_disableTimer();
	
	/* Check 1: TimerMaxTime > TimeMS */
	if ( f32_gs_timerMaxTime > u32_a_timeMS )
	{
		/* Step 2.1: Calculate TimerReloadValue = ( 2 ^ TimerResolution ) - ( ( TimerMaxTime - TimeMS ) / TimerTickTime ) */
		/* Example: TimerResolution = 24, TimerMaxTime = 1048.576 msec, TimeMS = 1000 msec, TimerTickTime = 0.0000625 msec */
		/* Answer : TimerReloadValue = ( 2 ^ 24 ) - ( ( 1048.576 - 1000 ) / 0.0000625 ) = 16000000 */
		u32_l_timerReloadValue = ( u32 ) ( pow( 2, STMR_U8_RESOLUTION ) - ( ( f32_gs_timerMaxTime - u32_a_timeMS ) / f32_gs_timerTickTime ) );
	}
	/* Check 2: TimerMaxTime < TimeMS */
	else if ( f32_gs_timerMaxTime < u32_a_timeMS )
	{
		/* Step 2.2: Calculate NumberOfOVFs and TimerReloadValue */
		/*        1. TimeMS / TimerMaxTime = Number.Fraction
		 *        2. DesiredNumberOfOVFs = Number + 1
		 *        3. TimerReloadValue = Fraction * ( 2 ^ TimerResolution )
		 */
		/* Example: TimerMaxTime = 1048.576 msec, TimeMS = 2000 msec */
		/* Answer : 2000 / 1048.576 = ~1.90735
		 *          DesiredNumberOfOVFs = 2
		 *          TimerReloadValue = ( 0.90735 * ( 2 ^ 24 ) ) = ~15,222,807
		 */
		f32_l_result = ( f32 ) ( u32_a_timeMS / f32_gs_timerMaxTime );
		f32_l_fraction = modff( f32_l_result, &f32_l_number );
		u32_gs_desiredNumberOfOVFs = ( u32 ) ( f32_l_number + 1 );
		
		u32_l_timerReloadValue = ( u32 ) f32_l_fraction * pow( 2, STMR_U8_RESOLUTION );		 
	}
	
	/* Step 3: Set TimerReloadValue in STRELOAD register. */
	/* SysTick can be configured as a multi-shot timer, repeated over and over, firing every N+1 clock
   * pulses, where N is any value from 1 to 0x00FF.FFFF. For example, if a tick interrupt is required
   * every 100 clock pulses, 99 must be written into the RELOAD field.
	 */
	STMR_U32_STRELOAD_REG = ( u32 ) u32_l_timerReloadValue;
	
  STMR_enableTimer();
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_enableTimer
 Input: void
 Output: void
 Description: Function to enable STMR.
*/
void STMR_enableTimer( void )
{
	SET_BIT( STMR_U32_STCTRL_REG, STMR_U8_ENABLE_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_disableTimer
 Input: void
 Output: void
 Description: Function to disable STMR.
*/
void STMR_disableTimer( void )
{
	CLR_BIT( STMR_U32_STCTRL_REG, STMR_U8_ENABLE_BIT );
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_enableInterrupt
 Input: void
 Output: void
 Description: Function to enable STMR Interrupt.
*/
void STMR_enableInterrupt( void )
{
	/* Step 1: Set the INTEN bit the STCTRL register. */
	SET_BIT( STMR_U32_STCTRL_REG, STMR_U8_INTEN_BIT );

	/* Step 2: Enable Interrupt in the NVIC peripheral. */
	NVIC_EnableIRQ( SysTick_IRQn );
	
	/* Step 3: Enable Interrupts. */
	__enable_irq();	
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_disableInterrupt
 Input: void
 Output: void
 Description: Function to disable STMR Interrupt.
*/
void STMR_disableInterrupt( void )
{	
	/* Step 1: Clear the INTEN bit the STCTRL register. */
	CLR_BIT( STMR_U32_STCTRL_REG, STMR_U8_INTEN_BIT );

	/* Step 2: Disable Interrupt in the NVIC peripheral. */
	NVIC_DisableIRQ( SysTick_IRQn );
}

/*******************************************************************************************************************************************************************/
/*
 Name: STMR_setCallback
 Input: Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function, the address is 
              passed through a pointer to function ( TimerInterruptAction ), and then pass this address to IRQ function.
*/
STMR_enErrorState_t STMR_setCallback( void ( *vpf_a_timerInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	STMR_enErrorState_t en_l_errorState = STMR_EN_OK;
	
	/* Check 1: Pointer is not equal to NULL. */
	if ( vpf_a_timerInterruptAction != STD_TYPES_NULL )
	{
		vpf_gs_timerInterruptAction = vpf_a_timerInterruptAction;
	}
	/* Check 2: Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		en_l_errorState = STMR_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of STMR */
void SysTick_Handler( void )
{
	/* Increment the CurrentNumberOfOVFs after every Overflow in STMR counting register */
	u32_gs_currentNumberOfOVFs++;
	
	/* Check 1: The CurrentNumberOfOVFs did not reach the DesiredNumberOfOVFs */
	if ( u32_gs_currentNumberOfOVFs < u32_gs_desiredNumberOfOVFs )
	{
		/* Step 1: Reset Reload Value */
		STMR_U32_STRELOAD_REG = STMR_U32_MAX_RELOAD_VALUE;
	}
	/* Check 2: The CurrentNumberOfOVFs reached the DesiredNumberOfOVFs */
	else
	{
		/* Step 2: Disable STMR */
		STMR_disableTimer();
		
		STMR_U32_STCURRENT_REG = 0;
		
		/* Step 3: Reset the DesiredNumberOfOVFs and CurrentNumberOfOVFs to 0 */
		u32_gs_desiredNumberOfOVFs = 0;
		u32_gs_currentNumberOfOVFs = 0;

		/* Check 2.1: Pointer to Function is not equal to NULL. */
		if ( vpf_gs_timerInterruptAction != STD_TYPES_NULL )
		{
			/* Step 4: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Pointer to Function ( TimerInterruptAction ). */
			vpf_gs_timerInterruptAction();
		}
		/* Check 2.2: Pointer to Function is equal to NULL. */
		else
		{
			/* Do Nothing. */
		}
	}
}

/*******************************************************************************************************************************************************************/
