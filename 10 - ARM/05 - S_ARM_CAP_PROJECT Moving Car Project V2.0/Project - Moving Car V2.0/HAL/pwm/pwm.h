#ifndef PWM_H_
#define PWM_H_

/*=========FILE INCLUSION=========*/
#include "../../MCAL/gpt/gpt.h"
#include "../../MCAL/gpio/gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	INVALID		=0,
	VALID			=1,
	MAX_ERROR	=2
}enu_pwm_error_t;


/*=========APIs DECLERATIONS=========*/

enu_pwm_error_t PWM_Init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_timer_id_t enu_timer_id);

enu_pwm_error_t PWM_start(enu_timer_id_t enu_timer_id,uint32 u32_periodic_time,enu_tick_unit_t enu_tick_unit,uint8 u8_duty_cycle);

enu_pwm_error_t PWM_stop(enu_timer_id_t enu_timer_id);

#endif	/* PWM_H_ */

