/*
 * TMR1_interface.c
 *
 * Created: 2023-05-19 5:10:16 PM
 *  Author: HAZEM-PC
 */ 
/*============= FILE INCLUSION =============*/
#include "tmr1_interface.h"

/*============= MACRO DEFINITION =============*/
#define CLK_MASKING_BITS	0xF8
#define CAPT_MASKING_BITS	0xBF
#define NOISE_MASKING_BITS	0x7F
#define WGMA_MASKING_BITS	0xFC
#define WGMB_MASKING_BITS	0xE7
#define WGM_LOW_MASKING		0x03
#define WGM_HIGH_MASKING	0x0C
#define INT_MASKING_BITS	0xC3
#define ZERO_VALUE			0
/*============= FUNCTION DEFINITION =============*/

void TMR1_init (ST_TME1_ConfigType* TMR_config)
{
	//set timer initial value
	TCNT1 = ZERO_VALUE;
	//set compare initial value
	OCR1A = ZERO_VALUE;
	OCR1B = ZERO_VALUE;
	//set input capture initial value
	ICR1 = ZERO_VALUE;
	//set clock option
	TCCR1B = (TCCR1B & CLK_MASKING_BITS) | (TMR_config->CLK_source);
	//set  Input Capture Edge Select
	TCCR1B = (TCCR1B & CAPT_MASKING_BITS) | ((TMR_config->Edge_type) << ICES1);
	//set Input Capture Noise Canceler 
	TCCR1B = (TCCR1B & NOISE_MASKING_BITS) | ((TMR_config->NO_Noise) << ICNC1);
	//set wave generation mode
	TCCR1A = (TCCR1A & WGMA_MASKING_BITS) | (TMR_config->TMR_mode & WGM_LOW_MASKING);
	TCCR1B = (TCCR1B & WGMB_MASKING_BITS) | ((TMR_config->TMR_mode & WGM_HIGH_MASKING) << WGM12);
	//interrupt source
	TIMSK = ((TIMSK & INT_MASKING_BITS) | (TMR_config->INT_source)) && (TMR_config->INT_state);
	//he FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode
	if(TMR_config->TMR_mode == Normal || TMR_config->TMR_mode == CTC)
	{
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	}
}
u16 TMR1_readTime(void)
{
	//return timer/counter register
	return TCNT1 ;
}
void TMR1_clear(void)
{
	//reset timer/counter register
	TCNT1 = ZERO_VALUE;
}

void TMR1_stop(void)
{
	//stop timer clock
	TCCR1B=ZERO_VALUE;
	//clear timer interrupt 
	TIMSK=ZERO_VALUE;
}