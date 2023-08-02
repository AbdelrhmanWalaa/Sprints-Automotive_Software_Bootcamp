/*
 * 	File:						pwm.c
 *	Module:					PWM
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "pwm.h"

/*=========MACRO DEFINITIONS=========*/
#define MAX_DUTY_CYCLE 100.0F

/*=========EXTERN VARIABLES=========*/


/*=========STATIC GLOBAL VARIABLES=========*/
static enu_gpio_port_id_t gs_enu_gpio_port_id = ENU_MAX_PORT;
static enu_gpio_pin_id_t gs_enu_gpio_pin_id 	= ENU_MAX_PIN;
static boolean gs_bo_pwm_flag	= FALSE;
static uint32 gs_u32_pwm_time	=	0;
static enu_timer_id_t gs_enu_timer_id ;
static float32 gs_f32_on_time;
static float32 gs_f32_off_time;
static uint32 gs_u32_periodic_time;
static enu_tick_unit_t gs_enu_tick_unit;

/*=========TYPE DEFINITIONS=========*/


/*=========PRIVATE FUNCTIONS=========*/
static void PWM_callback	(void);

/*=========APIs DEFINITIONS=========*/

enu_pwm_error_t PWM_Init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_timer_id_t enu_timer_id)
{
	enu_pwm_error_t enu_pwm_error = VALID;
	//check the passing parameters
	if((enu_gpio_port_id < ENU_MAX_PORT) && (enu_gpio_pin_id < ENU_MAX_PIN) && (enu_timer_id < MAX_TIMER_ID))
	{
		
		gs_enu_gpio_port_id = enu_gpio_port_id;
		gs_enu_gpio_pin_id 	= enu_gpio_pin_id;
		gs_enu_timer_id			= enu_timer_id;
		//init GPT
		str_gpt_config_t str_gpt_config = 
		{
			.enu_timer_id 				= enu_timer_id,
			.enu_timer_mode 			= PERIODIC,
			.ptr_callback					=	PWM_callback,
			.enu_timer_int_state 	= TIMER_ENABLE_INT,
		};
		//init GPIO
		str_gpio_config_t str_gpio_config =
		{
			.enu_gpio_current_level 		= ENU_PIN_CUR_8MA,
			.enu_gpio_internal_attach 	= ENU_PIN_PUR,
			.enu_gpio_pin_direction 		= ENU_PIN_OUTPUT,
			.enu_gpio_pin_id 						= enu_gpio_pin_id,
			.enu_gpio_pin_level 				= ENU_PIN_LOW,
			.enu_gpio_pin_mode 					= ENU_DIGITAL_MODE,
			.enu_gpio_port_id 					= enu_gpio_port_id,
		};
		GPIO_init(&str_gpio_config);
		gpt_Init(&str_gpt_config);
		
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
}


enu_pwm_error_t PWM_start(enu_timer_id_t enu_timer_id,uint32 u32_periodic_time,enu_tick_unit_t enu_tick_unit,uint8 u8_duty_cycle)
{
	enu_pwm_error_t enu_pwm_error = VALID;
	float32 f32_on_time	=	0;
	float32 f32_off_time	=	0;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		if(u32_periodic_time > 0)
		{
			gs_u32_periodic_time = u32_periodic_time;
			if((u8_duty_cycle < MAX_DUTY_CYCLE) && ((u8_duty_cycle > 0)))
			{
				f32_off_time=((float32)u32_periodic_time*u8_duty_cycle)/MAX_DUTY_CYCLE;	//calculate on time delay
				f32_on_time=u32_periodic_time-f32_off_time;
				gs_f32_on_time = f32_on_time;
				gs_f32_off_time = f32_off_time;
				gs_enu_tick_unit = enu_tick_unit;
				gpt_startTimer(enu_timer_id,f32_on_time,enu_tick_unit);
			}
			else if(u8_duty_cycle == MAX_DUTY_CYCLE)
			{
				gs_f32_on_time = u32_periodic_time;
				gs_enu_tick_unit = enu_tick_unit;
			}
			else if(u8_duty_cycle == 0)
			{
				gs_f32_on_time = 0;
				gs_enu_tick_unit = enu_tick_unit;
			}
			else
			{
				enu_pwm_error = INVALID;
			}
			//gpt_startTimer(enu_timer_id,f32_on_time,enu_tick_unit);
			//gpt_enable_notification(enu_timer_id);
		}
		else
		{
			enu_pwm_error = INVALID;
		}
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
	
}


enu_pwm_error_t PWM_stop(enu_timer_id_t enu_timer_id)
{	
	enu_pwm_error_t enu_pwm_error = VALID;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		gpt_stopTimer(enu_timer_id);
		gpt_disable_notification(enu_timer_id);
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
}



void PWM_callback	(void)
{
	if (gs_f32_on_time == 0)
	{
		GPIO_digitalWrite(gs_enu_gpio_port_id,gs_enu_gpio_pin_id,ENU_PIN_LOW);	
		gpt_stopTimer(gs_enu_timer_id);
	}
	else if (gs_f32_on_time == gs_u32_periodic_time)
	{
		GPIO_digitalWrite(gs_enu_gpio_port_id,gs_enu_gpio_pin_id,ENU_PIN_HIGH);
		gpt_stopTimer(gs_enu_timer_id);
	}
	else if(gs_bo_pwm_flag == FALSE)
	{
		gpt_startTimer(gs_enu_timer_id,gs_f32_off_time,gs_enu_tick_unit);
		gs_bo_pwm_flag = TRUE;
		GPIO_togglePin(gs_enu_gpio_port_id,gs_enu_gpio_pin_id);	
	}
	else if(gs_bo_pwm_flag == TRUE)
	{
		gpt_startTimer(gs_enu_timer_id,gs_f32_on_time,gs_enu_tick_unit);
		gs_bo_pwm_flag = FALSE;
		GPIO_togglePin(gs_enu_gpio_port_id,gs_enu_gpio_pin_id);	
	}
	else 
	{
		//do nothing
	}
}


/*
enu_pwm_error_t PWM_start(enu_timer_id_t enu_timer_id,uint32 u32_periodic_time,enu_tick_unit_t enu_tick_unit,uint8 u8_duty_cycle)
{
	enu_pwm_error_t enu_pwm_error = VALID;
	float32 f32_on_time	=	0;
	float32 f32_off_time	=	0;
	if((enu_timer_id < MAX_TIMER_ID) && (u8_duty_cycle < MAX_DUTY_CYCLE))
	{
		f32_off_time=((float32)u32_periodic_time*u8_duty_cycle)/MAX_DUTY_CYCLE;	//calculate on time delay
		f32_on_time=u32_periodic_time-f32_off_time;
		gs_f32_on_time = f32_on_time;
		gs_f32_off_time = f32_off_time;
		gs_enu_tick_unit = enu_tick_unit;
		gpt_startTimer(enu_timer_id,f32_on_time,enu_tick_unit);
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
	
}


void PWM_callback	(void)
{
	if(gs_bo_pwm_flag == FALSE)
	{
		gpt_startTimer(gs_enu_timer_id,gs_f32_off_time,gs_enu_tick_unit);
		gs_bo_pwm_flag = TRUE;
	}
	else
	{
		gpt_startTimer(gs_enu_timer_id,gs_f32_on_time,gs_enu_tick_unit);
		gs_bo_pwm_flag = FALSE;
	}
	GPIO_togglePin(gs_enu_gpio_port_id,gs_enu_gpio_pin_id);	
}

*/
