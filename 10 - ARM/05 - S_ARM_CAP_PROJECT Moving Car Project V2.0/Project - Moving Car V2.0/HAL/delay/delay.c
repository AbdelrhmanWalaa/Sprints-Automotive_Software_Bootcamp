/*
 * 	File:						delay.c
 *	Module:					delay
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "delay.h"

/*=========MACRO DEFINITIONS=========*/


/*=========EXTERN VARIABLES=========*/


/*=========STATIC GLOBAL VARIABLES=========*/


/*=========TYPE DEFINITIONS=========*/


/*=========PRIVATE FUNCTIONS=========*/


/*=========APIs DEFINITIONS=========*/
enu_delay_error_t delay_us (enu_timer_id_t enu_timer_id,uint32 u32_time)
{
	enu_delay_error_t enu_delay_error = VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		str_gpt_config_t str_gpt_config = 
		{
			.enu_timer_id 				= enu_timer_id,
			.enu_timer_mode 			= ONESHOT,
			.ptr_callback					=	NULL_PTR,
			.enu_timer_int_state 	= TIMER_DISABLE_INT,
		};
		gpt_Init(&str_gpt_config);
		gpt_startTimer(enu_timer_id,u32_time,USEC);
	}
	else
	{
		enu_delay_error = INVALID_OPERATION;
	}
	return enu_delay_error;
}



enu_delay_error_t delay_ms (enu_timer_id_t enu_timer_id,uint32 u32_time)
{
	enu_delay_error_t enu_delay_error = VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		str_gpt_config_t str_gpt_config = 
		{
			.enu_timer_id 				= enu_timer_id,
			.enu_timer_mode 			= ONESHOT,
			.ptr_callback					=	NULL_PTR,
			.enu_timer_int_state 	= TIMER_DISABLE_INT,
		};
		gpt_Init(&str_gpt_config);
		gpt_startTimer(enu_timer_id,u32_time,MSEC);
	}
	else
	{
		enu_delay_error = INVALID_OPERATION;
	}
	return enu_delay_error;
}


enu_delay_error_t delay_sec (enu_timer_id_t enu_timer_id,uint32 u32_time)
{
	enu_delay_error_t enu_delay_error = VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		str_gpt_config_t str_gpt_config = 
		{
			.enu_timer_id 				= enu_timer_id,
			.enu_timer_mode 			= ONESHOT,
			.ptr_callback					=	NULL_PTR,
			.enu_timer_int_state 	= TIMER_DISABLE_INT,
		};
		gpt_Init(&str_gpt_config);
		gpt_startTimer(enu_timer_id,u32_time,SEC);
	}
	else
	{
		enu_delay_error = INVALID_OPERATION;
	}
	return enu_delay_error;
}
