/*
 * pwm_program.c
 *
 *     Created on: May 17, 2023
 *         Author: Hazem Ashraf - https://github.com/hazemashrafali
 *    Description: This file contains all Pulse Width Modulation (PWM) functions' implementation, and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "pwm_private.h"
#include "pwm_config.h"
#include "pwm_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global Variables to store Port and Pin values. */
static u8 u8_gs_portId, u8_gs_pinId;

/* Global Variables to store different values. */
static u8 u8_gs_TonInitialValue, u8_gs_ToffInitialValue;
static u16 u16_gs_TonPrescale, u16_gs_ToffPrescale;
static f32 f32_gs_periodTime;

/* Global Variable ( Flag ) to be altered when entering OVF interrupt in TMR2. */
static volatile u8 u8_gs_PWMFlag = PWM_U8_FLAG_DOWN;

/*******************************************************************************************************************************************************************/
/* PWM Private Functions' prototypes */

static u8 PWM_calculatePrescaler   ( f32 f32_a_delay, u16 *pu16_a_returnedPrescaler );
static u8 PWM_calculateInitialValue( u16 u16_a_prescaler, f32 f32_a_delay, u8 *pu16_a_returnedInitialValue );
static u8 PWM_setPrescaler         ( u16 u16_a_prescaler );

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_initialization
 Input: u8 PortId, u8 PinId, and f32 PWMFrequency
 Output: u8 Error or No Error
 Description: Function to Initialize PWM peripheral.
*/
u8 PWM_initialization( u8 u8_a_portId, u8 u8_a_pinId, f32 f32_a_pwmFrequency )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;

	/* Check 1: PortId and PinlId are in the valid range */
	if ( ( u8_a_portId <= DIO_U8_PORTD ) && ( u8_a_pinId <= DIO_U8_PIN7 ) )
	{
		/* Step 1: Store Port and Pin ( through which PWM will be generated ) in Global Variables */
		u8_gs_portId = u8_a_portId;
		u8_gs_pinId = u8_a_pinId;
		
		/* Step 2: Set the PWM Pin Direction to Out */
		switch ( u8_a_portId )
		{
			case DIO_U8_PORTA: SET_BIT( DIO_U8_DDRA_REG, u8_a_pinId ); break;
			case DIO_U8_PORTB: SET_BIT( DIO_U8_DDRB_REG, u8_a_pinId ); break;
			case DIO_U8_PORTC: SET_BIT( DIO_U8_DDRC_REG, u8_a_pinId ); break;
			case DIO_U8_PORTD: SET_BIT( DIO_U8_DDRD_REG, u8_a_pinId ); break;
		}
				
		/* Step 3: Set the PWM Pin Value to Low */
		switch ( u8_a_portId )
		{
			case DIO_U8_PORTA: CLR_BIT( DIO_U8_PORTA_REG, u8_a_pinId ); break;
			case DIO_U8_PORTB: CLR_BIT( DIO_U8_PORTB_REG, u8_a_pinId ); break;
			case DIO_U8_PORTC: CLR_BIT( DIO_U8_PORTC_REG, u8_a_pinId ); break;
			case DIO_U8_PORTD: CLR_BIT( DIO_U8_PORTD_REG, u8_a_pinId ); break;
		}		
		
		/* Step 4: Calculate Period ( Note: PWM Periodic Time is in milli seconds ) */
		f32_gs_periodTime = 1.0F / f32_a_pwmFrequency;
		
		/* Step 5: Enable TMR2 Overflow Interrupt */
		SET_BIT( TMR_U8_TIMSK_REG, TMR_U8_TOIE2_BIT );	
	}
	/* Check 2:PortId and PinlId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong PortId and PinlId! */
		u8_l_errorState = STD_TYPES_NOK;
	}
		
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_generatePWM
 Input: u8 DutyCycle
 Output: u8 Error or No Error
 Description: Function to Generate PWM.
*/
u8 PWM_generatePWM   ( u8 u8_a_dutyCycle )
{	 
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
	
	/* Check 1: DutyCycle is in the valid range */
	if ( u8_a_dutyCycle <= PWM_U8_MAX_DUTY_CYCLE )
	{
		f32 f32_l_timeOn, f32_l_timeOff;
		
		/* Step 1: Calculate Time Delay for both On & Off Time */
		f32_l_timeOff = ( ( f32 ) f32_gs_periodTime * u8_a_dutyCycle ) / 100.0F;
		f32_l_timeOn = f32_gs_periodTime - f32_l_timeOff;
		
		/* Step 2: Calculate Prescaler Value for both On & Off Time */
		PWM_calculatePrescaler( f32_l_timeOn, &u16_gs_TonPrescale );
		PWM_calculatePrescaler( f32_l_timeOff, &u16_gs_ToffPrescale );
		
		/* Step 3: Calculate Initial Value for both On & Off Time */
		PWM_calculateInitialValue( u16_gs_TonPrescale, f32_l_timeOn, &u8_gs_TonInitialValue );
		PWM_calculateInitialValue( u16_gs_ToffPrescale, f32_l_timeOff, &u8_gs_ToffInitialValue );
		
		/* Step 4: Set TMR2 Initial Value */
		TMR_U8_TCNT2_REG = u8_gs_TonInitialValue;
		
		/* Step 4: Set TMR2 Prescaler Value */
		PWM_setPrescaler( u16_gs_TonPrescale );
	}
	/* Check 2: DutyCycle is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong DutyCycle! */
		u8_l_errorState = STD_TYPES_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_calculatePrescaler
 Input: f32 Delay and Pointer to u16 ReturnedPrescaler
 Output: u8 Error or No Error
 Description: Function to calculate Prescaler value.
*/
static u8 PWM_calculatePrescaler   ( f32 f32_a_delay, u16 *pu16_a_returnedPrescaler )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
	
	/* Check 1: Delay is in the valid range, and Pointer is not equal to NULL */
	if( ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_1024_PRESCALER ) ) && ( pu16_a_returnedPrescaler != NULL ) )
	{
		/* Case 1: Delay <= MaxDelay of No Prescaler */
		if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_NO_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_NO_PRESCALER;
		}
		/* Case 2: Delay <= MaxDelay of 8 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_8_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_8_PRESCALER;
		}
		/* Case 3: Delay <= MaxDelay of 32 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_32_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_32_PRESCALER;
		}
		/* Case 4: Delay <= MaxDelay of 64 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_64_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_64_PRESCALER;
		}
		/* Case 5: Delay <= MaxDelay of 128 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_128_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_128_PRESCALER;
		}
		/* Case 6: Delay <= MaxDelay of 256 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_256_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_256_PRESCALER;
		}
		/* Case 7: Delay <= MaxDelay of 1024 Prescaler */
		else if ( f32_a_delay <= MAX_DELAY_MS( TMR_U16_TMR_2_1024_PRESCALER ) )
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_1024_PRESCALER;
		}
		/* Case 8: No Clock Source */
		else
		{
			*pu16_a_returnedPrescaler = TMR_U16_TMR_2_NO_CLOCK_SOURCE;
		}
	}
	/* Check 2: Delay is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong Delay or Pointer is NULL! */
		u8_l_errorState = STD_TYPES_NOK;
	}
	
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_calculateInitialValue
 Input: u16 Prescaler, f32 Delay, and Pointer to u16 ReturnedPrescaler
 Output: u8 Error or No Error
 Description: Function to calculate Initial value.
*/
static u8 PWM_calculateInitialValue( u16 u16_a_prescaler, f32 f32_a_delay, u8 *pu16_a_returnedInitialValue )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
		
	/* Check 1: Prescaler is in the valid range, and Pointer is not equal to NULL */
	if( ( u16_a_prescaler <= TMR_U16_TMR_2_1024_PRESCALER ) && ( pu16_a_returnedInitialValue != NULL ) )
	{
		/* Check 1.1: Required Prescaler */
		switch( u16_a_prescaler )
		{
			/* Case 1: No Prescaler */
			case TMR_U16_TMR_2_NO_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_NO_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_NO_PRESCALER ) );
			break;
			/* Case 2: Prescaler is 8 */
			case TMR_U16_TMR_2_8_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_8_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_8_PRESCALER ) );
			break;
			/* Case 3: Prescaler is 32 */
			case TMR_U16_TMR_2_32_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_32_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_32_PRESCALER ) );
			break;
			/* Case 4: Prescaler is 64 */
			case TMR_U16_TMR_2_64_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_64_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_64_PRESCALER ) );
			break;
			/* Case 5: Prescaler is 128 */
			case TMR_U16_TMR_2_128_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_128_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_128_PRESCALER ) );
			break;
			/* Case 6: Prescaler is 256 */
			case TMR_U16_TMR_2_256_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE( MAX_DELAY_MS( TMR_U16_TMR_2_256_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_256_PRESCALER ) );
			break;
			/* Case 7: Prescaler is 1024 */
			case TMR_U16_TMR_2_1024_PRESCALER:
				*pu16_a_returnedInitialValue = INITITAL_VALUE ( MAX_DELAY_MS( TMR_U16_TMR_2_1024_PRESCALER ), f32_a_delay, MIN_DELAY_MS( TMR_U16_TMR_2_1024_PRESCALER ) );
			break;
		}
	}
	/* Check 2: Prescaler is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong Prescaler or Pointer is NULL! */
		u8_l_errorState = STD_TYPES_NOK;
	}
		
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: PWM_setPrescaler
 Input: u16 Prescaler
 Output: u8 Error or No Error
 Description: Function to Set Prescaler value.
*/
static u8 PWM_setPrescaler         ( u16 u16_a_prescaler )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_TYPES_OK;
		
	/* Check 1: Prescaler is in the valid range */
	if ( u16_a_prescaler <= TMR_U16_TMR_2_1024_PRESCALER )
	{
		/* Check 1.1: Required Prescaler */
		switch ( u16_a_prescaler )
		{
			/* Case 1: Clock Source =  No Prescaler */
			case TMR_U16_TMR_2_NO_PRESCALER	  : SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
											    CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 2: Clock Source = 8 Prescaler */
			case TMR_U16_TMR_2_8_PRESCALER	  : CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
											    CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 3: Clock = 32 Prescaler */
			case TMR_U16_TMR_2_32_PRESCALER	  : SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
												CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 4: Clock Source = 64 Prescaler */
			case TMR_U16_TMR_2_64_PRESCALER	  : CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
												SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 5: Clock Source = 128 Prescaler */
			case TMR_U16_TMR_2_128_PRESCALER  : SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
												SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 6: Clock Source = 256 Prescaler */
			case TMR_U16_TMR_2_256_PRESCALER  : CLR_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
												SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
			/* Case 7: Clock Source = 1024 Prescaler */
			case TMR_U16_TMR_2_1024_PRESCALER : SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT ); SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT );
												SET_BIT( TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT ); break;
		}
	}
	/* Check 2: Prescaler is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong Prescaler! */
		u8_l_errorState = STD_TYPES_NOK;
	}
		
	return u8_l_errorState;
}

/*******************************************************************************************************************************************************************/

/*
 *  8-bit Timer/Counter2 ISR
 */
/* ISR functions' prototypes of TMR2 Overflow ( OVF ) */
void __vector_5( void )		__attribute__((signal));

/*******************************************************************************************************************************************************************/

/* ISR function implementation of TMR2 OVF */
void __vector_5( void )
{
	/* Check 1: PWMFlag is not set */
	if( u8_gs_PWMFlag == PWM_U8_FLAG_DOWN )
	{
		PWM_setPrescaler( u16_gs_ToffPrescale );		
		TMR_U8_TCNT2_REG = u8_gs_ToffInitialValue;
		
		u8_gs_PWMFlag = PWM_U8_FLAG_UP;
	}
	/* Check 2: PWMFlag is set */
	else
	{
		PWM_setPrescaler( u16_gs_TonPrescale );		
		TMR_U8_TCNT2_REG = u8_gs_TonInitialValue;
		
		u8_gs_PWMFlag = PWM_U8_FLAG_DOWN;
	}

	/* Step 2: Toggle the PWM Pin */
	switch ( u8_gs_portId )
	{
		case DIO_U8_PORTA: TOG_BIT( DIO_U8_PORTA_REG, u8_gs_pinId ); break;
		case DIO_U8_PORTB: TOG_BIT( DIO_U8_PORTB_REG, u8_gs_pinId ); break;
		case DIO_U8_PORTC: TOG_BIT( DIO_U8_PORTC_REG, u8_gs_pinId ); break;
		case DIO_U8_PORTD: TOG_BIT( DIO_U8_PORTD_REG, u8_gs_pinId ); break;
	}
}

/*******************************************************************************************************************************************************************/