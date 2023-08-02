#ifndef GPT_H_
#define GPT_H_

/*=========FILE INCLUSION=========*/
#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"
#include "../../LIB/registers.h"
#include "TM4C123.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	TIMER0_ID 	= 0,
	TIMER1_ID 	= 1,
	TIMER2_ID		=	2,
	TIMER3_ID		=	3,
	TIMER4_ID		=	4,
	TIMER5_ID		=	5,
	TIMER6_ID		=	6,
	TIMER7_ID		=	7,
	TIMER8_ID		=	8,
	TIMER9_ID		=	9,
	TIMER10_ID	=	10,
	TIMER11_ID	=	11,
	MAX_TIMER_ID	
}enu_timer_id_t;

typedef enum{
	ONESHOT		=	0,
	PERIODIC	=	1,
	RTC				=	2,
	ICU				=	3,
	PWM				=	4,
	MAX_TIMER_MODE	
}enu_timer_mode_t;

typedef enum{
	USEC	=	0,
	MSEC	=	1,
	SEC		=	2,
	MAX_TICK_UNIT
}enu_tick_unit_t;

typedef enum{
	TIMER_DISABLE_INT,
	TIMER_ENABLE_INT,
	MAX_TIMER_INT_STATE
}enu_timer_int_state_t;

typedef void (*ptr_callback_t) (void);

typedef struct{
	enu_timer_id_t 				enu_timer_id;
	enu_timer_mode_t 			enu_timer_mode;
	ptr_callback_t 				ptr_callback;
	enu_timer_int_state_t enu_timer_int_state;
}str_gpt_config_t;

typedef enum{
	GPT_VALID_OPERATION,
	GPT_INVALID_OPERATION,
	MAX_GPT_ERROR
}enu_timer_error_t;


/*=========APIs DECLERATIONS=========*/
enu_timer_error_t gpt_Init 								(str_gpt_config_t* str_gpt_config);
enu_timer_error_t gpt_startTimer 					(enu_timer_id_t enu_timer_id,uint32 u32_time,enu_tick_unit_t enu_tick_unit);
enu_timer_error_t gpt_stopTimer 					(enu_timer_id_t enu_timer_id);
enu_timer_error_t gpt_enable_notification	(enu_timer_id_t enu_timer_id);
enu_timer_error_t gpt_disable_notification(enu_timer_id_t enu_timer_id);
enu_timer_error_t gpt_getElapsedTime 	(enu_timer_id_t enu_timer_id,uint32* u32_ptr_elapse_time);
enu_timer_error_t gpt_getReminingTime (enu_timer_id_t enu_timer_id,uint32* u32_ptr_remaining_time);

#endif	/* GPT_H_ */

