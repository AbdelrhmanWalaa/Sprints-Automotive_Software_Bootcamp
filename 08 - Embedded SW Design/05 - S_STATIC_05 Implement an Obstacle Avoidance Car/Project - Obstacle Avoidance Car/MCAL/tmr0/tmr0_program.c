/*
 * TMR0_interface.c
 *
 * Created: 2023-05-16 6:54:02 PM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "tmr0_interface.h"

/*============= global variables =============*/
static void (*g_callBackPtr_0)(void) = NULL;
static volatile u8 NO_OF_OVERFLOWS=0;
static volatile u8 g_tick=0;
static u8 g_initial_value=0;
volatile u8 g_timeout_flag=0;

/*============= TYPE DEFINITION =============*/
typedef struct{
	u16 prescaler;
	u8 initial_value;
	f32 NO_OF_OV;
}ST_timer0_config;

/*============= PRIVATE FUNCTIONS =============*/
static inline u8 TMR0_calculatePrescaler(f32 delay,u16* prescale);
static inline void TMR0_calculateInitialValue(u16 prescaler,u8* initial_value,f32 delay);
static inline void TMR0_setPrescale(u16 prescaler);

/*============= FUNCTION DEFINITIONS =============*/
/*
 * Description:used to calculate timer settings
 * calculate pre_scale value
 * calculate number of overflows
 * calculate timer initial value
 */

void TMR0_delayMS(f32 delay)
{
	//delay-=5;
	ST_timer0_config Time;
	u8 real_part,reminder,count;
	if(TMR0_calculatePrescaler(delay, &Time.prescaler))
	{
		TMR0_calculateInitialValue(Time.prescaler, &Time.initial_value,delay);
		Time.NO_OF_OV=0;
	}
	else
	{
		Time.prescaler=P_1024;
		Time.NO_OF_OV=(delay/MAX_DELAY_MS(P_1024));
		Time.initial_value=0;
	}
	real_part=Time.NO_OF_OV;
	reminder=(Time.NO_OF_OV-real_part)*(MAX_DELAY_MS(P_1024)); //reminder delay to complete required delay period
	count=real_part;
	TCNT0=Time.initial_value;
	if(count==0)
	{
		TMR0_setPrescale(Time.prescaler);
		while(!(TIFR & (1<<TOV0)));
	}
	else
	{
		TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);		//use clock pre_scale 1024
		while(count != 0)								//run delay of real part
		{
			while(!(TIFR & (1<<TOV0)));
			count--;
			TIFR |= (1<<TOV0);
		}
		if(reminder > 0)								//run remaining delay period
		{
			if(reminder <= MAX_DELAY_MS(P_1))						//find best range that contain the required remaining delay
				Time.prescaler=P_1;
			else if(reminder <= MAX_DELAY_MS(P_8))
				Time.prescaler=P_8;
			else if(reminder <= MAX_DELAY_MS(P_64))
				Time.prescaler=P_64;
			else if(reminder <= MAX_DELAY_MS(P_256))
				Time.prescaler=P_256;
			else if(reminder <= MAX_DELAY_MS(P_1024))
				Time.prescaler=P_1024;
			else
				Time.prescaler = P_0;
		}
		switch(Time.prescaler)												//according to selected pre_scaler value
		{
		case P_1:
			TCNT0=INIT_VALUE(MAX_DELAY_MS(P_1),reminder,MIN_DELAY_MS(P_1));	//set TCNT0 register with the initial value
			TCCR0 = (1<<FOC0) | (1<<CS00);									//set TCCR0 register with clock source
			break;
		case P_8:
			TCNT0=INIT_VALUE(MAX_DELAY_MS(P_8),reminder,MIN_DELAY_MS(P_8));
			TCCR0 = (1<<FOC0) | (1<<CS01);
			break;
		case P_64:
			TCNT0=INIT_VALUE(MAX_DELAY_MS(P_64),reminder,MIN_DELAY_MS(P_64));
			TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
			break;
		case P_256:
			TCNT0=INIT_VALUE(MAX_DELAY_MS(P_256),reminder,MIN_DELAY_MS(P_256));
			TCCR0 = (1<<FOC0) | (1<<CS02);
			break;
		case P_1024:
			TCNT0=INIT_VALUE(MAX_DELAY_MS(P_1024),reminder,MIN_DELAY_MS(P_1024));
			TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
			break;
		default:
			TCNT0=0;
			TCCR0 = 0;
			break;
		}
		while(!(TIFR & (1<<TOV0)));			//Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)
	}
	TIFR |= (1<<TOV0);						//Clear TOV0 bit by set its value
	TCCR0 = FALSE;
}

void TMR0_stop(void)
{
	TIMSK &= ~(1<<TOIE0);
}

void TMR0_callEvent(f32 delay,void(*g_ptr)(void))
{	
	TIMSK |= (1<<TOIE0);
	if(delay < MAX_DELAY_MS(P_1024))
	{
		g_initial_value=ceil(((f32)(MAX_DELAY_MS(P_1024)-delay)/MIN_DELAY_MS(P_1024)));
		NO_OF_OVERFLOWS=0;
	}
	else
	{
		NO_OF_OVERFLOWS=delay/MAX_DELAY_MS(P_1024);
		g_initial_value=0;
	}
	TCNT0=g_initial_value;
	
	g_callBackPtr_0=g_ptr;
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

void TMR0_timeoutMS(f32 delay)
{
	/*code to count time in milliseconds*/
	if(delay < MAX_DELAY_MS(P_1024))
	{
		g_initial_value=delay;
		NO_OF_OVERFLOWS=0;
	}
	else
	{
		NO_OF_OVERFLOWS = ((f32)delay/MAX_DELAY_MS(P_1024));
		g_initial_value = MAX_COUNT - 1;
	}
	TCNT0=0;
	OCR0=g_initial_value;
	TIMSK |= (1<<OCIE0);			//enable timer compare match interrupt
	g_timeout_flag=0;				//set flag to default
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}

ISR_HANDLER(TMR0_CMP)
{
	if(NO_OF_OVERFLOWS > 0)
	{
		g_tick++;
		if(g_tick==NO_OF_OVERFLOWS)
		{
			g_timeout_flag++;
			g_tick = 0;			//clear the tick counter again to start new count				
		}
	}
	else
	{
		g_timeout_flag++;
		TCNT0=0;
		OCR0=g_initial_value;
	}
}

ISR_HANDLER(TMR0_OVF)
{
	if(g_callBackPtr_0 != NULL)
	{
		if(NO_OF_OVERFLOWS > 0)
		{
			g_tick++;
			if(g_tick == NO_OF_OVERFLOWS)
			{
				g_callBackPtr_0();
				g_tick = 0; //clear the tick counter again to start new count
			}
		}
		else
		{
			g_callBackPtr_0();
			TCNT0=g_initial_value;
		}
	}
}

static inline u8 TMR0_calculatePrescaler(f32 delay,u16* prescale)
{
	if(delay <= MAX_DELAY_MS(P_1024))
	{
		if(delay <= MAX_DELAY_MS(P_1))
			*prescale=P_1;
		else if(delay <= MAX_DELAY_MS(P_8))
			*prescale=P_8;
		else if(delay <= MAX_DELAY_MS(P_64))
			*prescale=P_64;
		else if(delay <= MAX_DELAY_MS(P_256))
			*prescale=P_256;
		else if(delay <= MAX_DELAY_MS(P_1024))
			*prescale=P_1024;
		else
			*prescale = P_0;
		return TRUE;
	}
	else
		return FALSE;
}

static inline void TMR0_calculateInitialValue(u16 prescaler,u8* init_value,f32 delay)
{
	switch(prescaler)
	{
	case P_1:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_1),delay,MIN_DELAY_MS(P_1));
		break;
	case P_8:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_8),delay,MIN_DELAY_MS(P_8));
		break;
	case P_64:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_64),delay,MIN_DELAY_MS(P_64));
		break;
	case P_256:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_256),delay,MIN_DELAY_MS(P_256));
		break;
	case P_1024:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_1024),delay,MIN_DELAY_MS(P_1024));
		break;
	default:
		*init_value=FALSE;
		break;
	}
}

static inline void TMR0_setPrescale(u16 prescaler)
{
	switch(prescaler)
	{
	case P_1:
		TCCR0 = (1<<FOC0) | (1<<CS00);
		break;
	case P_8:
		TCCR0 = (1<<FOC0) | (1<<CS01);
		break;
	case P_64:
		TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
		break;
	case P_256:
		TCCR0 = (1<<FOC0) | (1<<CS02);
		break;
	case P_1024:
		TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
		break;
	default:
		TCCR0 = FALSE;
		break;
	}
}

