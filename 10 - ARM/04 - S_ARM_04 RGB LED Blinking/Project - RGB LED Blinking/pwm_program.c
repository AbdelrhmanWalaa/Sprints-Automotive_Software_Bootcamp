/*
 * pwm_program.c
 *
 *     Created on: Jun 25, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Pulse Width Modulation (PWM) functions' implementation.
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

/* HAL */
#include "pwm_interface.h"
#include "pwm_config.h"

/*******************************************************************************************************************************************************************/
/* PWM External Variables */

extern GPIO_stPortLinkConfig_t ast_g_gpioPortsLinkConfig[1];
extern GPIO_stPinLinkConfig_t  ast_g_gpioPinsLinkConfig[4];

extern GPTM_stTimerLinkConfig_t ast_gs_timersLinkConfig[1];

/*******************************************************************************************************************************************************************/
/* PWM Global Variables */

/* Global variables to store PWM On and Off Periods. */
static u64 u64_gs_onPeriod = 0;
static u64 u64_gs_offPeriod = 0;

/* Global variable to store PWM TimeUnit. */
static PWM_enTimeUnit_t en_gs_timeUnit;

/* Global variables to store PWM PeriodFlag state. */
static u8 u8_gs_periodFlag = PWM_OFF_PERIOD_FLAG;

/*******************************************************************************************************************************************************************/
/* PWM Static Functions' Prototypes */

/*
 Name: PWM_switchOnOffPeriods
 Input: void
 Output: void
 Description: Function to be called after a Timer Overflow, to switch between On and Off Periods.
*/
static void PWM_switchOnOffPeriods( void );

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_initialization
 Input: u8 PWMId
 Output: en Error or No Error
 Description: Function to initialize PWM peripheral, by initializing GPIO and GPTM peripherals.
*/
PWM_enErrorState_t PWM_initialization( u8 u8_a_pwmId )
{
	/* Define local variable to set the error state = OK. */
	PWM_enErrorState_t Loc_enErrorState = PWM_EN_OK;
	
	/* Check 1: PWMId is in the valid range. */
	if ( u8_a_pwmId <= PWM_U8_7 )
	{
		/* Step 1: Initialize Port. */
		GPIO_initalization( ast_g_gpioPortsLinkConfig, 1 );
		
		/* Step 2: Configure Pin. */
		GPIO_configurePin( &ast_g_gpioPinsLinkConfig[u8_a_pwmId], 1 );
		
		/* Step 3: Initialize Timer. */
		GPTM_initialization( ast_gs_timersLinkConfig, 1 );
		
		/* Step 4: Set Timer Overflow Callback function. */
		GPTM_setCallback( GPTM_EN_TIMER_0, GPTM_EN_CONCATUNATED, &PWM_switchOnOffPeriods );		
	}
	/* Check 2: PWMId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong BTNPinId! */
		Loc_enErrorState = PWM_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************//*******************************************************************************************************************************************************************/
/*
 Name: PWM_enable
 Input: u8 DutyCycle
 Output: en Error or No Error
 Description: Function to enable PWM.
*/
PWM_enErrorState_t PWM_enable( u64 u64_a_totalPeriod, PWM_enTimeUnit_t en_a_timeUnit, u8 u8_a_dutyCycle )
{
	/* Define local variable to set the error state = OK. */
	PWM_enErrorState_t Loc_enErrorState = PWM_EN_OK;
	
	/* Check 1: TimeUnit and DutyCycle are in the valid range. */
	if ( ( en_a_timeUnit < PWM_EN_INVALID_TIME_UNIT )  &&
		   ( u8_a_dutyCycle <= PWM_U8_MAX_DUTY_CYCLE ) )
	{
		/* Step 1: Calculate OnPeriod = ( TotalPeriod * DutyCycle ) / 100 */
    /* Example: TotalPeriod = 500 ms, DutyCycle = 50 */
		/* Answer : OnPeriod = ( 500 * 50 ) / 100 = 250 ms */		
		u64_gs_onPeriod = ( u64_a_totalPeriod * u8_a_dutyCycle ) / 100;
		
		/* Step 2: Calculate OffPeriod = TotalPeriod - OnPeriod */
    /* Example: TotalPeriod = 500 ms, OnPeriod = 250 ms */
		/* Answer : OffPeriod = 500 - 250 = 250 ms */	
		u64_gs_offPeriod = u64_a_totalPeriod - u64_gs_onPeriod;
		
		/* Step 3: Store TimeUnit. */
		en_gs_timeUnit = en_a_timeUnit;
		
		/* Step 4: Enable Timer. */
		GPTM_enableTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT );
	}
  /* Check 2: TimerUnit or DutyCycle is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong TimeUnit or DutyCycle! */
		Loc_enErrorState = PWM_EN_NOK;
	}
	
	return Loc_enErrorState;
}

/*******************************************************************************************************************************************************************//*******************************************************************************************************************************************************************/
/*
 Name: PWM_disable
 Input: void
 Output: void
 Description: Function to disable PWM.
*/
void PWM_disable( void )
{
	/* Step 1: Disable Timer. */
	GPTM_disableTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT );
}

/*******************************************************************************************************************************************************************//*******************************************************************************************************************************************************************/
/*
 Name: PWM_switchOnOffPeriods
 Input: void
 Output: void
 Description: Function to be called after a Timer Overflow, to switch between On and Off Periods.
*/
static void PWM_switchOnOffPeriods( void )
{
	/* Step 1: Disable Timer. */
	GPTM_disableTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT );
	
	/* Check 1: Required PeriodFlag is OnPeriodFlag ( i.e.: OnPeriod is finished, and OffPeriod will start ). */
	if ( u8_gs_periodFlag == PWM_ON_PERIOD_FLAG )
	{
		/* Step 2.1: Update PeriodFlag to OffPeriodFlag. */
		u8_gs_periodFlag = PWM_OFF_PERIOD_FLAG;
		
		/* Step 2.2: Clear GPIO Pin. */
		GPIO_clearPinValue( PWM_U8_PORT_ID_SELECT, PWM_U8_PORT_BUS_ID_SELECT, PWM_U8_PIN_ID_SELECT );
		
		/* Step 2.3: Update Timer Counter with the OffPeriod. */
		GPTM_setTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT, u64_gs_offPeriod, ( GPTM_enTimeUnit_t ) en_gs_timeUnit );
	}
	/* Check 2: Required PeriodFlag is OffPeriodFlag ( i.e.: OffPeriod is finished, and OnPeriod will start ). */
	else if ( u8_gs_periodFlag == PWM_OFF_PERIOD_FLAG )
	{
		/* Step 2.1: Update PeriodFlag to OnPeriodFlag. */
		u8_gs_periodFlag = PWM_ON_PERIOD_FLAG;
		
		/* Step 2.2: Set GPIO Pin. */
		GPIO_setPinValue( PWM_U8_PORT_ID_SELECT, PWM_U8_PORT_BUS_ID_SELECT, PWM_U8_PIN_ID_SELECT );
		
		/* Step 2.3: Update Timer Counter with the OnPeriod. */
		GPTM_setTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT, u64_gs_onPeriod, ( GPTM_enTimeUnit_t ) en_gs_timeUnit );
	}
	
	/* Step 3: Enable Timer. */
	GPTM_enableTimer( PWM_U8_TIMER_ID_SELECT, PWM_U8_TIMER_USE_SELECT );
}

/*******************************************************************************************************************************************************************//*******************************************************************************************************************************************************************/
