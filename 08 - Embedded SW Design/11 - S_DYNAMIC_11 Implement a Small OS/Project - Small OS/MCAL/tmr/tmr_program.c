/*
 * tmr_program.c
 *
 * Created: 2023-06-01 2:33:12 AM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "tmr_interface.h"

/*============= MACRO DEFINITION =============*/
#define CLK_MASKING_BITS	0xF8
#define CAPT_MASKING_BITS	0xBF
#define NOISE_MASKING_BITS	0x7F
#define WGMA_MASKING_BITS	0xFC
#define WGMB_MASKING_BITS	0xC7
#define WGM_LOW_MASKING		0x03
#define WGM_HIGH_MASKING	0x18
#define INT_MASKING_BITS	0xC3
#define FOC_MASKING_BITS	0xF3

/*============= global variables =============*/
static  void (*gl_ov_callBackPtr)	(void) = NULL;
static  void (*gl_cmpa_callBackPtr)	(void) = NULL;
static  void (*gl_cmpb_callBackPtr)	(void) = NULL;
static  void (*gl_icu_callBackPtr)	(void) = NULL;
static u16 u16_gl_initial_value	=0;
static u16 u16_gl_no_overflow	=0;
static volatile u16 u16_gl_tick	=0;
/*============= FUNCTION DEFINITIONS =============*/
enu_tmr_state_t tmr_Init	(str_tmr_configType* str_tmr_config)
{
	enu_tmr_state_t enu_tmr_state = TMR_STATE_SUCCESS;
	if(str_tmr_config != NULL)
	{
		//set timer initial value
		TCNT1 = 0;
		//set compare initial value
		OCR1A = 0;
		OCR1B = 0;
		//set input capture initial value
		ICR1 = 0;
		//set clock option
		TCCR1B = (TCCR1B & CLK_MASKING_BITS) | (str_tmr_config->enu_tmr_clk);
		//set timer mode
		TCCR1A = (TCCR1A & WGMA_MASKING_BITS) | (str_tmr_config->enu_tmr_mode & WGM_LOW_MASKING);
		TCCR1B = (TCCR1B & WGMB_MASKING_BITS) | ((str_tmr_config->enu_tmr_mode & WGM_HIGH_MASKING));
		//FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode
		if((str_tmr_config->enu_tmr_mode == NORMAL) || (str_tmr_config->enu_tmr_mode == CTC))
		{
			TCCR1A = (TCCR1A & FOC_MASKING_BITS) | (1<<FOC1A) | (1<<FOC1B);		
		}
		//set interrupt source
		TIMSK = ((TIMSK & INT_MASKING_BITS) | (str_tmr_config->enu_tmr_intState));
	}
	else
	{
		enu_tmr_state = TMR_STATE_FAILED;
	}
	return enu_tmr_state;
}

void tmr_setTimer(u16 delay)
{
	TIMSK |= (1<<TOIE1);
	if(delay < MAX_DELAY_MS(P_1))
	{
		u16_gl_initial_value=ceil(((f64)(MAX_DELAY_MS(P_1)-delay)/MIN_DELAY_MS(P_1)));
		u16_gl_no_overflow=0;
	}
	else
	{
		u16_gl_no_overflow=delay/MAX_DELAY_MS(P_1);
		u16_gl_initial_value=0;
	}
	TCNT1=u16_gl_initial_value;	
	TCCR1B = (TCCR1B & CLK_MASKING_BITS)|(1<<CS10);
}
void tmr_Clear(void)
{
	TCNT1=0;
}
void tmr_Stop(void)
{
	//stop timer clock
	TCCR1B=CLK_STOP;
}

void tmr_resume(void)
{
	TCCR1B = (TCCR1B & CLK_MASKING_BITS)|(1<<CS10);
}

void tmr_ovf_setCallback(void(*g_ptr)(void))
{
	gl_ov_callBackPtr = g_ptr;
}

void tmr_cmpa_setCallback(void(*g_ptr)(void))
{
	gl_cmpa_callBackPtr = g_ptr;
}

void tmr_cmpb_setCallback(void(*g_ptr)(void))
{
	gl_cmpb_callBackPtr = g_ptr;
}

void tmr_icu_setCallback(void(*g_ptr)(void))
{
	gl_icu_callBackPtr = g_ptr;
}

ISR_HANDLER(TMR1_OVF)
{
	if(gl_ov_callBackPtr != NULL)
	{
		if(u16_gl_no_overflow > 0)
		{
			u16_gl_tick++;
			if(u16_gl_tick == u16_gl_no_overflow)
			{
				gl_ov_callBackPtr();
				u16_gl_tick = 0; //clear the tick counter again to start new count
			}
		}
		else
		{
			gl_ov_callBackPtr();
			TCNT1=u16_gl_initial_value;
		}
	}
}

ISR_HANDLER(TMR1_CMP_B)
{
	if(gl_cmpb_callBackPtr != NULL)
	{
		gl_cmpb_callBackPtr();
	}
}

ISR_HANDLER(TMR1_CMP_A)
{
	if(gl_cmpa_callBackPtr != NULL)
	{
		gl_cmpa_callBackPtr();
	}
}

ISR_HANDLER(TMR1_CPT)
{
	if(gl_icu_callBackPtr != NULL)
	{
		gl_icu_callBackPtr();
	}
}