/*
 * pwm_private.h
 *
 *     Created on: May 17, 2023
 *         Author: Hazem Ashraf - https://github.com/hazemashrafali
 *    Description: This file contains all Pulse Width Modulation (PWM) registers' locations and description.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* DIO Registers' Locations */

#define DIO_U8_DDRA_REG		    *( ( volatile u8 * ) 0x3A )
#define DIO_U8_DDRB_REG		    *( ( volatile u8 * ) 0x37 )
#define DIO_U8_DDRC_REG		    *( ( volatile u8 * ) 0x34 )
#define DIO_U8_DDRD_REG		    *( ( volatile u8 * ) 0x31 )

#define DIO_U8_PORTA_REG	    *( ( volatile u8 * ) 0x3B )
#define DIO_U8_PORTB_REG	    *( ( volatile u8 * ) 0x38 )
#define DIO_U8_PORTC_REG	    *( ( volatile u8 * ) 0x35 )
#define DIO_U8_PORTD_REG	    *( ( volatile u8 * ) 0x32 )

/* TMR Registers' Locations */

#define	TMR_U8_TIMSK_REG		*( ( volatile u8 * ) 0x59 )
#define	TMR_U8_TIFR_REG			*( ( volatile u8 * ) 0x58 )
#define	TMR_U8_SFIOR_REG		*( ( volatile u8 * ) 0x50 )

/*
 * 8-bit Timer/Counter2
 */

#define	TMR_U8_TCCR2_REG		*( ( volatile  u8 * ) 0x45 )
#define	TMR_U8_TCNT2_REG		*( ( volatile  u8 * ) 0x44 )
#define	TMR_U8_OCR2_REG			*( ( volatile  u8 * ) 0x43 )
#define	TMR_U8_ASSR_REG			*( ( volatile  u8 * ) 0x42 )

/*******************************************************************************************************************************************************************/
/* TMR Registers' Description */

/* Timer/Counter Interrupt Mask Register - TIMSK */
/* Bit 7 - OCIE2: Timer/Counter2 Output Compare Match Interrupt Enable */
#define TMR_U8_OCIE2_BIT		7
/* Bit 6 - TOIE2: Timer/Counter2 Overflow Interrupt Enable */
#define TMR_U8_TOIE2_BIT		6
/* End of TIMSK Register */

/* Timer/Counter Interrupt Flag Register - TIFR */
/* Bit 7 - OCF2: Output Compare Flag 2 */
#define TMR_U8_OCF2_BIT			7
/* Bit 6 - TOV2: Timer/Counter2 Overflow Flag */
#define TMR_U8_TOV2_BIT			6
/* End of TIFR Register */

/* Special Function IO Register - SFIOR */
/* Bit 1 - PSR2: Prescaler Reset Timer/Counter2 */
#define TMR_U8_PSR2_BIT			1
/* End of SFIOR Register */

/*
 * 8-bit Timer/Counter2 Registers' Description
 */

/* Timer/Counter Control Register - TCCR2 */
/* Bit 7 - FOC2: Force Output Compare */
#define TMR_U8_FOC2_BIT			7
/* Bit 6, 3 - WGM21:0: Waveform Generation Mode */
#define TMR_U8_WGM21_BIT		3
#define TMR_U8_WGM20_BIT		6
/* Bit 5:4 - COM21:0: Compare Match Output Mode */
#define TMR_U8_COM21_BIT		5
#define TMR_U8_COM20_BIT		4
/* Bit 2:0 - CS22:0: Clock Select */
#define TMR_U8_CS22_BIT			2
#define TMR_U8_CS21_BIT			1
#define TMR_U8_CS20_BIT			0
/* End of TCCR2 Register */

/* Asynchronous Status Register - ASSR */
/* Bit 3 - AS2: Asynchronous Timer/Counter2 */
#define TMR_U8_AS2_BIT			3
/* Bit 2 - TCN2UB: Timer/Counter2 Update Busy */
#define TMR_U8_TCN2UB_BIT		2
/* Bit 1 - OCR2UB: Output Compare Register2 Update Busy */
#define TMR_U8_OCR2UB_BIT		1
/* Bit 0 - TCR2UB: Timer/Counter Control Register2 Update Busy */
#define TMR_U8_TCR2UB_BIT		0
/* End of ASSR Register */

/*******************************************************************************************************************************************************************/
/* PWM Private Macros and Functions Like Macros */

#define MIN_COUNT			1
#define MAX_COUNT			256

#define INITITAL_VALUE( T_MAX, T_DELAY, TICK )  ( ( ( f32 ) T_MAX - T_DELAY ) / TICK )

#define MAX_DELAY_MS( PRESCALER ) ( ( ( ( f32 ) PRESCALER / F_CPU ) * MAX_COUNT ) * 1000UL )
#define MIN_DELAY_MS( PRESCALER ) ( ( ( ( f32 ) PRESCALER / F_CPU ) * MIN_COUNT ) * 1000UL )
#define MAX_DELAY_US( PRESCALER ) ( ( ( ( f32 ) PRESCALER / F_CPU ) * MAX_COUNT ) * 1000000UL )
#define MIN_DELAY_US( PRESCALER ) ( ( ( ( f32 ) PRESCALER / F_CPU ) * MIN_COUNT ) * 1000000UL )

/*******************************************************************************************************************************************************************/

#endif /* PWM_PRIVATE_H_ */