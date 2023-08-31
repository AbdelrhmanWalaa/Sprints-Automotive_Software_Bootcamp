/*
 * gptm_program.c
 *
 *     Created on: Jun 20, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Timers (GPTM) functions' implementation, and IRQ handlers implementation.
 *  MCU Datasheet: Tiva™ TM4C123GH6PM - https://www.ti.com/lit/pdf/spms376
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
#include "gptm_interface.h"
#include "gptm_private.h"

/*******************************************************************************************************************************************************************/
/* GPTM Global Variables */

/* Global Array of Pointers to Functions, these functions ( in an Upper Layer ) which these Pointers will hold their addresses; are having void input argument and void return type. */
static void ( *avpf_gs_timersInterruptsAction[24] ) ( void ) = { STD_TYPES_NULL };

/* Global variable to store GPTM TimerTickTime. */
static f32 f32_gs_timerTickTime = 0;

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_initialization
 Input: Pointer to Array of st TimerLinkConfig and u8 NumberOfTimers
 Output: en Error or No Error
 Description: Function to initialize GPTM peripheral using Linking Configurations.
*/
GPTM_enErrorState_t GPTM_initialization( const GPTM_stTimerLinkConfig_t *past_a_timersLinkConfig, u8 u8_a_numberOfTimers )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Define local variable to set the index value = 0. */
	u8 u8_l_index = 0;
	
	/* Check 1: Pointer is not equal to NULL, and NumberOfTimers is in the valid range. */
	if ( ( past_a_timersLinkConfig != STD_TYPES_NULL ) 				  &&
			 ( u8_a_numberOfTimers < GPTM_EN_INVALID_TIMER_ID ) )
	{	
		/* Loop: Until initializing all Timers passed. */
		for ( u8_l_index = 0; u8_l_index < u8_a_numberOfTimers; u8_l_index++ )
		{
			/* Check 1.1: TimerId, TimerMode, TimerUse, TimerInterruptMode, and TimerInterruptNumber are in the valid range. */
			if ( ( past_a_timersLinkConfig[u8_l_index].en_a_timerId < GPTM_EN_INVALID_TIMER_ID )                        &&
					 ( past_a_timersLinkConfig[u8_l_index].en_a_timerMode < GPTM_EN_INVALID_TIMER_MODE )                    &&
			     ( past_a_timersLinkConfig[u8_l_index].en_a_timerUse < GPTM_EN_INVALID_TIMER_USE )                      &&
					 ( past_a_timersLinkConfig[u8_l_index].en_a_timerInterruptMode < GPTM_EN_INVALID_TIMER_INT_MODE )       &&
			     ( past_a_timersLinkConfig[u8_l_index].en_a_timerInterruptNumber < GPTM_EN_INVALID_TIMER_INT_NUMBER ) )
			{
				/* Step 1: Calculate TimerTickTime = 1000000 us / System Clock Frequency */
				/* Example: System Clock Frequency = 16 MHz */
				/* Answer : TimerTickTime = ( 1000000 us / 16000000 ) = 0.0625 us */
				f32_gs_timerTickTime = ( f32 ) ( 1000000.0 / ( u32 ) F_CPU );
				
				/* Step 2: Enable the clock for the timer module in the RCGCTIMER or RCGCWTIMER registers. */
				/* Check 1.1.1: Timer is not a Wide Timer. */
				if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
				{
					SET_BIT( GPTM_U32_RCGCTIMER_REG, past_a_timersLinkConfig[u8_l_index].en_a_timerId );
				}
				/* Check 1.1.2: Timer is a Wide Timer. */
				else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
				{
					SET_BIT( GPTM_U32_RCGCWTIMER_REG, ( past_a_timersLinkConfig[u8_l_index].en_a_timerId - GPTM_EN_TIMER_5 ) );
				}
				
				/* Step 3: Ensure the timer is disabled ( TAEN and TBEN bits in the GPTMCTL register are cleared ) before making any changes. */
				CLR_BIT( GPTM_U32_GPTMCTL_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAEN_BIT );
				CLR_BIT( GPTM_U32_GPTMCTL_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TBEN_BIT );
				
				/* Check 1.1.3: Required TimerMode. */
				switch ( past_a_timersLinkConfig[u8_l_index].en_a_timerMode )
				{
					case GPTM_EN_ONE_SHOT_MODE:
					{
						/* Check 1.1.3.1: Required TimerUse. */
						switch ( past_a_timersLinkConfig[u8_l_index].en_a_timerUse )
						{
						  case GPTM_EN_INDIVIDUAL_A:
							{
								/* Step 4.1.1: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x4 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x4;
								
								/* Step 5.1.1: Configure the TAMR bits in the GPTM Timer A Mode Register (GPTMTAMR) = 0x1 for One-Shot mode. */
								/* Debug */
								SET_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR00_BIT );
								CLR_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR01_BIT );
								
								/* Step 6.1.1: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.1.1: Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR). */
								/* Check 1.1.3.1.1: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u16 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
								/* Check 1.1.3.1.2: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
											
								break;
							}
							
							case GPTM_EN_INDIVIDUAL_B:
							{
								/* Step 4.1.2: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x4 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x4;
								
								/* Step 5.1.2: Configure the TBMR bits in the GPTM Timer B Mode Register (GPTMTBMR) = 0x1 for One-Shot mode. */
								SET_BIT( GPTM_U32_GPTMTBMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TBMR00_BIT );
								CLR_BIT( GPTM_U32_GPTMTBMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TBMR01_BIT );
								
								/* Step 6.1.2: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.1.2: Load the start value into the GPTM Timer B Interval Load Register (GPTMTBILR). */
								/* Check 1.1.3.1.3: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u16 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
								/* Check 1.1.3.1.4: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}

								break;
							}
							
							case GPTM_EN_CONCATUNATED:
							{								
								/* Step 4.1.3: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x0;
								
								/* Step 5.1.3: Configure the TAMR bits in the GPTM Timer A Mode Register (GPTMTAMR) = 0x1 for One-Shot mode. */
								SET_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR00_BIT );
								CLR_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR01_BIT );
								
								/* Step 6.1.3: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.1.3: Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR) and GPTM Timer B Interval Load Register (GPTMTBILR). */
					   		/* Check 1.1.3.1.5: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									/* Debug */
								  GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue );
								}
								/* Check 1.1.3.1.6: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue );
								  GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue >> 32 );
								}
								
								break;
							}
							
							default:
							{
								/* Do Nothing. */
								break;
							}
						}

						break;
					}
					
					case GPTM_EN_PERIODIC_MODE:
					{
						/* Check 1.1.3.2: Required TimerUse. */
						switch ( past_a_timersLinkConfig[u8_l_index].en_a_timerUse )
						{
						  case GPTM_EN_INDIVIDUAL_A:
							{
								/* Step 4.2.1: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x4 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x4;
								
								/* Step 5.2.1: Configure the TAMR bits in the GPTM Timer A Mode Register (GPTMTAMR) = 0x2 for Periodic mode. */
								CLR_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR00_BIT );
								SET_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR01_BIT );
								
								/* Step 6.2.1: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.2.1: Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR). */
								/* Check 1.1.3.2.1: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u16 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
								/* Check 1.1.3.2.2: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
			
								break;
							}
							
							case GPTM_EN_INDIVIDUAL_B:
							{
								/* Step 4.2.2: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x4 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x4;
								
								/* Step 5.2.2: Configure the TBMR bits in the GPTM Timer B Mode Register (GPTMTBMR) = 0x2 for Periodic mode. */
								CLR_BIT( GPTM_U32_GPTMTBMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TBMR00_BIT );
								SET_BIT( GPTM_U32_GPTMTBMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TBMR01_BIT );
								
								/* Step 6.2.2: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.2.2: Load the start value into the GPTM Timer B Interval Load Register (GPTMTBILR). */
								/* Check 1.1.3.2.3: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u16 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}
								/* Check 1.1.3.2.4: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue;
								}

								break;
							}
							
							case GPTM_EN_CONCATUNATED:
							{								
								/* Step 4.2.3: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0 */
								GPTM_U32_GPTMCFG_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = 0x0;
								
								/* Step 5.2.3: Configure the TAMR bits in the GPTM Timer A Mode Register (GPTMTAMR) = 0x2 for Periodic mode. */
								CLR_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR00_BIT );
								SET_BIT( GPTM_U32_GPTMTAMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TAMR01_BIT );
								
								/* Step 6.2.3: Configure the TASNAPS, TAWOT, TAMTE, and TACDIR bits in the GPTMTAMR register to 
								 * select whether to capture the value of the free-running timer at time-out, use an external 
								 * trigger to start counting, configure an additional trigger or interrupt, and count up or down.
								 */
								/* Future Improvements. */
								
								/* Step 7.2.3: Load the start value into the GPTM Timer A Interval Load Register (GPTMTAILR) and GPTM Timer B Interval Load Register (GPTMTBILR). */
					   		/* Check 1.1.3.2.5: Timer is not a Wide Timer. */
								if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue );
								}
								/* Check 1.1.3.2.6: Timer is a Wide Timer. */
								else if ( past_a_timersLinkConfig[u8_l_index].en_a_timerId <= GPTM_EN_WIDE_TIMER_5 )
								{
									GPTM_U32_GPTMTAILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue );
								  GPTM_U32_GPTMTBILR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ) = ( u32 ) ( past_a_timersLinkConfig[u8_l_index].u64_a_timerStartValue >> 32 );
								}
								
								break;
							}
							
							default:
							{
								/* Do Nothing. */
								break;
							}
						}

						break;
					}
					
					case GPTM_EN_RTC_MODE:
					{						
						/* Future Improvements. */
						break;
					}
					
					case GPTM_EN_EDGE_COUNT_MODE:
					{						
						/* Future Improvements. */
						break;
					}
					
					case GPTM_EN_EDGE_TIME_MODE:
					{						
						/* Future Improvements. */
						break;
					}
					
					case GPTM_EN_PWM_MODE:
					{						
						/* Future Improvements. */
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
				
				/* Step 8: If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR). */
				switch ( past_a_timersLinkConfig[u8_l_index].en_a_timerInterruptMode )
				{
					case GPTM_EN_DISABLED_INT:
					{
						CLR_BIT( GPTM_U32_GPTMIMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TATOIM_BIT );
						
						/* Step 8.1: Disable Interrupt in the NVIC peripheral. */
						NVIC_DisableIRQ( ( IRQn_Type ) past_a_timersLinkConfig[u8_l_index].en_a_timerInterruptNumber );
						
						break;
					}
					
					case GPTM_EN_ENABLED_INT:
					{
						SET_BIT( GPTM_U32_GPTMIMR_REG( past_a_timersLinkConfig[u8_l_index].en_a_timerId ), GPTM_U8_TATOIM_BIT );
						
						/* Step 8.2: Enable Interrupt in the NVIC peripheral. */
						NVIC_EnableIRQ( ( IRQn_Type ) past_a_timersLinkConfig[u8_l_index].en_a_timerInterruptNumber );
						
						/* Step 8.3: Enable Interrupts. */
						__enable_irq();
						
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
			}
			/* Check 1.2: TimerId, TimerMode, TimerUse, TimerInterruptMode, or TimerInterruptNumber is not in the valid range. */
			else
			{
				/* Update error state = NOK, Wrong TimerId, TimerMode, TimerUse, TimerInterruptMode, or TimerInterruptNumber! */
				en_l_errorState = GPTM_EN_NOK;
				
				break;
			}
		}
	}
	/* Check 2: Pointer is equal to NULL, or NumberOfTimers is not in the valid range. */
	else
	{
		/* Update error state = NOK, Pointer is NULL, or Wrong NumberOfTimers! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_setTimer
 Input: en TimerId, en TimerUse, u64 Time, and en TimeUnit
 Output: en Error or No Error
 Description: Function to set GPTM peripheral to count in microseconds( us ), milliseconds ( ms ), and seconds ( sec ).
*/
GPTM_enErrorState_t GPTM_setTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, u64 u64_a_time, GPTM_enTimeUnit_t en_a_timeUnit )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Define local variables to calculate TimerStartValue. */
	u64 u64_l_time = 0;
	u64 u64_l_timerStartValue = 0;
	f32 f32_l_timerMaxTime = 0;
	
	/* Check 1: TimerId, TimerUse, and TimeUnit are in the valid range. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )     &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE )   &&
	     ( en_a_timeUnit < GPTM_EN_INVALID_TIME_UNIT ) )
	{
		/* Check 1.1: Required TimeUnit. */
		switch( en_a_timeUnit )
		{
			case GPTM_EN_TIME_US : u64_l_time = u64_a_time          ; break;
			case GPTM_EN_TIME_MS : u64_l_time = u64_a_time * 1000   ; break;
			case GPTM_EN_TIME_SEC: u64_l_time = u64_a_time * 1000000; break;
			default:                /* Do Nothing. */                 break;
		}
		
		/* Check 1.2: Required TimerId. */
		switch( en_a_timerId )
		{
			case GPTM_EN_TIMER_0 ... GPTM_EN_TIMER_5:
			{
				/* Check 1.2.1: Required TimerUse. */
				switch( en_a_timerUse )
				{
					case GPTM_EN_INDIVIDUAL_A:
					case GPTM_EN_INDIVIDUAL_B:
					{
						/* Step 2: Calculate TimerMaxTime = TimerTickTime * ( 2 ^ TimerResolution ) */
						/* Example: TimerTickTime = 0.0625 us, TimerResolution = 16 */
						/* Answer : TimerMaxTime = 0.0625 * ( 2 ^ 16 ) = 4096 us */
						f32_l_timerMaxTime = f32_gs_timerTickTime * pow( 2, 16 );
						
						/* Step 2.1: Calculate TimerStartValue = ( 2 ^ TimerResolution ) - ( ( TimerMaxTime - Time ) / TimerTickTime ) */
						/* Example: TimerResolution = 16, TimerMaxTime = 4096 us, Time = 1000 us, TimerTickTime = 0.0625 us */
						/* Answer : TimerStartValue = ( 2 ^ 16 ) - ( ( 4096 - 1000 ) / 0.0625 ) = 16000 */
						u64_l_timerStartValue = ( u64 ) ( pow( 2, 16 ) - ( ( f32_l_timerMaxTime - u64_l_time ) / f32_gs_timerTickTime ) );
						
						/* Check 1.2.1.1: Required TimerUse is Individual A. */
						if ( en_a_timerUse == GPTM_EN_INDIVIDUAL_A )
						{
							GPTM_U32_GPTMTAILR_REG( en_a_timerId ) = ( u16 ) u64_l_timerStartValue;
						}
						/* Check 1.2.1.2: Required TimerUse is Individual B. */
						else if ( en_a_timerUse == GPTM_EN_INDIVIDUAL_B )
						{
							GPTM_U32_GPTMTBILR_REG( en_a_timerId ) = ( u16 ) u64_l_timerStartValue;
						}
						/* Check 1.2.1.3: Required TimerUse is Invalid. */
						else
						{
							/* Do Nothing. */
						}
						
						break;
					}
					
					case GPTM_EN_CONCATUNATED:
					{
						/* Step 2: Calculate TimerMaxTime = TimerTickTime * ( 2 ^ TimerResolution ) */
						/* Example: TimerTickTime = 0.0625 us, TimerResolution = 32 */
						/* Answer : TimerMaxTime = 0.0625 * ( 2 ^ 32 ) = 268,435,456 us */
						f32_l_timerMaxTime = f32_gs_timerTickTime * pow( 2, 32 );
						
						/* Step 2.1: Calculate TimerStartValue = ( 2 ^ TimerResolution ) - ( ( TimerMaxTime - Time ) / TimerTickTime ) */
						/* Example: TimerResolution = 32, TimerMaxTime = 268,435,456 us, Time = 200,000,000 us, TimerTickTime = 0.0625 us */
						/* Answer : TimerStartValue = ( 2 ^ 32 ) - ( ( 268,435,456 - 200,000,000 ) / 0.0625 ) = 3,200,000,000 */
						u64_l_timerStartValue = ( u64 ) ( pow( 2, 32 ) - ( ( f32_l_timerMaxTime - u64_l_time ) / f32_gs_timerTickTime ) );
						
						GPTM_U32_GPTMTAILR_REG( en_a_timerId ) = ( u32 ) ( u64_l_timerStartValue );
						
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
				
				break;
			}
			
			case GPTM_EN_WIDE_TIMER_0 ... GPTM_EN_WIDE_TIMER_5:
			{
				/* Check 1.2.2: Required TimerUse. */
				switch( en_a_timerUse )
				{
					case GPTM_EN_INDIVIDUAL_A:
					case GPTM_EN_INDIVIDUAL_B:
					{
						/* Step 2: Calculate TimerMaxTime = TimerTickTime * ( 2 ^ TimerResolution ) */
						/* Example: TimerTickTime = 0.0625 us, TimerResolution = 32 */
						/* Answer : TimerMaxTime = 0.0625 * ( 2 ^ 32 ) = 268,435,456 us */
						f32_l_timerMaxTime = f32_gs_timerTickTime * pow( 2, 32 );
						
						/* Step 2.1: Calculate TimerStartValue = ( 2 ^ TimerResolution ) - ( ( TimerMaxTime - Time ) / TimerTickTime ) */
						/* Example: TimerResolution = 32, TimerMaxTime = 268,435,456 us, Time = 200,000,000 us, TimerTickTime = 0.0625 us */
						/* Answer : TimerStartValue = ( 2 ^ 32 ) - ( ( 268,435,456 - 200,000,000 ) / 0.0625 ) = 3,200,000,000 */
						u64_l_timerStartValue = ( u64 ) ( pow( 2, 32 ) - ( ( f32_l_timerMaxTime - u64_l_time ) / f32_gs_timerTickTime ) );
						
						/* Check 1.2.2.1: Required TimerUse is Individual A. */
						if ( en_a_timerUse == GPTM_EN_INDIVIDUAL_A )
						{
							GPTM_U32_GPTMTAILR_REG( en_a_timerId ) = ( u32 ) u64_l_timerStartValue;
						}
						/* Check 1.2.2.2: Required TimerUse is Individual B. */
						else if ( en_a_timerUse == GPTM_EN_INDIVIDUAL_B )
						{
							GPTM_U32_GPTMTBILR_REG( en_a_timerId ) = ( u32 ) u64_l_timerStartValue;
						}
						/* Check 1.2.2.3: Required TimerUse is Invalid. */
						else
						{
							/* Do Nothing. */
						}
						
						break;
					}
					
					case GPTM_EN_CONCATUNATED:
					{
						/* Step 2: Calculate TimerMaxTime = TimerTickTime * ( 2 ^ TimerResolution ) */
						/* Example: TimerTickTime = 0.0625 us, TimerResolution = 64 */
						/* Answer : TimerMaxTime = 0.0625 * ( 2 ^ 64 ) = 1,152,921,504,606,846,976 us */
						f32_l_timerMaxTime = f32_gs_timerTickTime * pow( 2, 64 );
						
						/* Step 2.1: Calculate TimerStartValue = ( 2 ^ TimerResolution ) - ( ( TimerMaxTime - Time ) / TimerTickTime ) */
						/* Example: TimerResolution = 16, TimerMaxTime = 1,152,921,504,606,846,976 us, Time = 1000 us, TimerTickTime = 0.0625 us */
						/* Answer : TimerStartValue = ( 2 ^ 64 ) - ( ( 4096 - 1000 ) / 0.0625 ) = 16000 */
						u64_l_timerStartValue = ( u64 ) ( pow( 2, 64 ) - ( ( f32_l_timerMaxTime - u64_l_time ) / f32_gs_timerTickTime ) );
						
						GPTM_U32_GPTMTAILR_REG( en_a_timerId ) = ( u32 ) ( u64_l_timerStartValue );
						GPTM_U32_GPTMTBILR_REG( en_a_timerId ) = ( u32 ) ( u64_l_timerStartValue >> 32 );
						
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
				
				break;
			}
			
			default:
			{
				/* Do Nothing. */
				break;
			}			
		}
	}
  /* Check 2: TimerId, TimerUse, or TimeUnit is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerId, TimerUse, or TimeUnit! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_enableTimer
 Input: en TimerId and en TimerUse
 Output: en Error or No Error
 Description: Function to enable GPTM.
*/
GPTM_enErrorState_t GPTM_enableTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerId and TimerUse are in the valid range. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )     &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE ) )
	{
		/* Check 1.1: Required TimerUse. */
		switch( en_a_timerUse )
		{
			case GPTM_EN_INDIVIDUAL_A: SET_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TAEN_BIT ); break;
			case GPTM_EN_INDIVIDUAL_B: SET_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TBEN_BIT ); break;
			case GPTM_EN_CONCATUNATED: SET_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TAEN_BIT ); break;
			default:                                /* Do Nothing. */                                     break;
		}
	}
  /* Check 2: TimerId or TimerUse is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_disableTimer
 Input: en TimerId and en TimerUse
 Output: en Error or No Error
 Description: Function to disable GPTM.
*/
GPTM_enErrorState_t GPTM_disableTimer( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerId and TimerUse are in the valid range. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )     &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE ) )
	{
		/* Check 1.1: Required TimerUse. */
		switch( en_a_timerUse )
		{
			case GPTM_EN_INDIVIDUAL_A: CLR_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TAEN_BIT ); break;
			case GPTM_EN_INDIVIDUAL_B: CLR_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TBEN_BIT ); break;
			case GPTM_EN_CONCATUNATED: CLR_BIT( GPTM_U32_GPTMCTL_REG( en_a_timerId ), GPTM_U8_TAEN_BIT ); break;
			default:                                /* Do Nothing. */                                     break;
		}
	}
  /* Check 2: TimerId or TimerUse is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_enableInterrupt
 Input: en TimerInterruptNumber
 Output: en Error or No Error
 Description: Function to enable GPTM Interrupt.
*/
GPTM_enErrorState_t GPTM_enableInterrupt( GPTM_enTimerInterruptNumber_t en_a_timerInterruptNumber )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerInterruptNumber is in the valid range. */
	if ( en_a_timerInterruptNumber < GPTM_EN_INVALID_TIMER_INT_NUMBER ) 
	{
		/* Enable Interrupt in the NVIC peripheral. */
		NVIC_EnableIRQ( ( IRQn_Type ) en_a_timerInterruptNumber );
		
		/* Enable Interrupts. */
		__enable_irq();	
	}
  /* Check 2: TimerInterruptNumber is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerInterruptNumber! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;		
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_disableInterrupt
 Input: en TimerInterruptNumber
 Output: en Error or No Error
 Description: Function to disable GPTM Interrupt.
*/
GPTM_enErrorState_t GPTM_disableInterrupt( GPTM_enTimerInterruptNumber_t en_a_timerInterruptNumber )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerInterruptNumber is in the valid range. */
	if ( en_a_timerInterruptNumber < GPTM_EN_INVALID_TIMER_INT_NUMBER ) 
	{
		/* Disable Interrupt in the NVIC peripheral. */
		NVIC_DisableIRQ( ( IRQn_Type ) en_a_timerInterruptNumber );
	}
  /* Check 2: TimerInterruptNumber is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerInterruptNumber! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_getTimeoutStatusFlag
 Input: en TimerId, en TimerUse, and Pointer to u8 TimeoutStatusFlag
 Output: en Error or No Error
 Description: Function to get GPTM clear Timeout Status Flag.
*/
GPTM_enErrorState_t GPTM_getTimeoutStatusFlag( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, u8 *pu8_a_timeoutStatusFlag )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerId and TimerUse are in the valid range, and Pointer is not equal to NULL. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )      &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE )    &&
	     ( pu8_a_timeoutStatusFlag != STD_TYPES_NULL ) )
	{
		/* Check 1.1: Required TimerUse. */
		switch( en_a_timerUse )
		{
			case GPTM_EN_INDIVIDUAL_A: *pu8_a_timeoutStatusFlag = GET_BIT( GPTM_U32_GPTMRIS_REG( en_a_timerId ), GPTM_U8_TATORIS_BIT ); break;
			case GPTM_EN_INDIVIDUAL_B: *pu8_a_timeoutStatusFlag = GET_BIT( GPTM_U32_GPTMRIS_REG( en_a_timerId ), GPTM_U8_TBTORIS_BIT ); break;
			case GPTM_EN_CONCATUNATED: *pu8_a_timeoutStatusFlag = GET_BIT( GPTM_U32_GPTMRIS_REG( en_a_timerId ), GPTM_U8_TATORIS_BIT ); break;
			default:                                                 /* Do Nothing. */                                                  break;
		}		
	}
	/* Check 2: TimerId or TimerUse is not in the valid range, or and Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse, Pointer is NULL! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_clearTimeoutStatusFlag
 Input: en TimerId and en TimerUse,
 Output: en Error or No Error
 Description: Function to clear GPTM clear Timeout Status Flag.
*/
GPTM_enErrorState_t GPTM_clearTimeoutStatusFlag( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerId and TimerUse are in the valid range. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )      &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE ) )
	{
		/* Check 1.1: Required TimerUse. */
		switch( en_a_timerUse )
		{
			case GPTM_EN_INDIVIDUAL_A: SET_BIT( GPTM_U32_GPTMICR_REG( en_a_timerId ), GPTM_U8_TATOCINT_BIT ); break;
			case GPTM_EN_INDIVIDUAL_B: SET_BIT( GPTM_U32_GPTMICR_REG( en_a_timerId ), GPTM_U8_TBTOCINT_BIT ); break;
			case GPTM_EN_CONCATUNATED: SET_BIT( GPTM_U32_GPTMICR_REG( en_a_timerId ), GPTM_U8_TATOCINT_BIT ); break;
			default:                                    /* Do Nothing. */                                     break;
		}		
	}
	/* Check 2: TimerId or TimerUse is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPTM_setCallback
 Input: en TimerId, en TimerUse, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function of the passed Timer ( TimerId ),
							the address is passed through a pointer to function ( TimerInterruptAction ), and then pass this address to IRQ function.
*/
GPTM_enErrorState_t GPTM_setCallback( GPTM_enTimerId_t en_a_timerId, GPTM_enTimerUse_t en_a_timerUse, void ( *vpf_a_timerInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	GPTM_enErrorState_t en_l_errorState = GPTM_EN_OK;
	
	/* Check 1: TimerId and TimerUse are in the valid range, and Pointer to Function is not equal to NULL. */
	if ( ( en_a_timerId < GPTM_EN_INVALID_TIMER_ID )         &&
		   ( en_a_timerUse < GPTM_EN_INVALID_TIMER_USE )       &&
		   ( vpf_a_timerInterruptAction != STD_TYPES_NULL ) )
	{
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( en_a_timerId, en_a_timerUse )] = vpf_a_timerInterruptAction;
	}
	/* Check 2: TimerId or TimerUse is not in the valid range, or Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse, or Pointer is NULL! */
		en_l_errorState = GPTM_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER0A */
void TIMER0A_Handler( void )
 {
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_A)]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER0B */
void TIMER0B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_0, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER1A */
void TIMER1A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_A )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER1B */
void TIMER1B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_1, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER2A */
void TIMER2A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_A )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER2B */
void TIMER2B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_2, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER3A */
void TIMER3A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_A )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER3B */
void TIMER3B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_3, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER4A */
void TIMER4A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_A )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER4B */
void TIMER4B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_4, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER5A */
void TIMER5A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_A )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER5B */
void TIMER5B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_B )]();
		
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_TIMER_5, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER0A */
void WTIMER0A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER0B */
void WTIMER0B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_0, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER1A */
void WTIMER1A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER1B */
void WTIMER1B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_1, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER2A */
void WTIMER2A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of TIMER2B */
void WTIMER2B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_2, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER3A */
void WTIMER3A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER3B */
void WTIMER3B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_3, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER4A */
void WTIMER4A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER4B */
void WTIMER4B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_4, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER5A */
void WTIMER5A_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_A )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_A )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_A );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of WTIMER5B */
void WTIMER5B_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_B )] != STD_TYPES_NULL )
	{
		/* Step 1: Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_timersInterruptsAction[GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_B )]();
				
		/* Step 2: Clear Timeout Status Flag */
		GPTM_clearTimeoutStatusFlag( GPTM_EN_WIDE_TIMER_5, GPTM_EN_INDIVIDUAL_B );
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}

/*******************************************************************************************************************************************************************/
