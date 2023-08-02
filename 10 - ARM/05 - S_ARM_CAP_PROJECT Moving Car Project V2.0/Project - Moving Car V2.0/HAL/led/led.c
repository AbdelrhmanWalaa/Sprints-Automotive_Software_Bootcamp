/*
 * 	File:						led.c
 *	Module:					Led
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "led.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/
enu_error_state_t LED_init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_error_state_t enu_error_state = SUCCESS;
	if(enu_gpio_port_id < ENU_MAX_PORT)
	{
		if(enu_gpio_pin_id < ENU_MAX_PIN)
		{
				str_gpio_config_t str_gpio_config ;
				str_gpio_config.enu_gpio_current_level 		= ENU_PIN_CUR_8MA;
				str_gpio_config.enu_gpio_internal_attach 	= ENU_PIN_PUR;
				str_gpio_config.enu_gpio_pin_direction 		= ENU_PIN_OUTPUT;
				str_gpio_config.enu_gpio_pin_id 					= enu_gpio_pin_id;
				str_gpio_config.enu_gpio_pin_level 				= ENU_PIN_LOW;
				str_gpio_config.enu_gpio_pin_mode 				= ENU_DIGITAL_MODE;
				str_gpio_config.enu_gpio_port_id 					= enu_gpio_port_id;
				GPIO_init(&str_gpio_config);
		}
		else
		{
			enu_error_state = FAILED;
		}
	}
	else
	{
		enu_error_state = FAILED;
	}
	return enu_error_state;
}
enu_error_state_t LED_digitalWrite(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_gpio_pin_level_t enu_gpio_pin_level)
{
	enu_error_state_t enu_error_state = SUCCESS;
	if(enu_gpio_port_id < ENU_MAX_PORT)
	{
		if(enu_gpio_pin_id < ENU_MAX_PIN)
		{
			if((enu_gpio_pin_level == ENU_PIN_LOW) || (enu_gpio_pin_level == ENU_PIN_HIGH))
			{
				GPIO_digitalWrite(enu_gpio_port_id,enu_gpio_pin_id,enu_gpio_pin_level);
			}
			else
			{
				enu_error_state = FAILED;
			}
		}
		else
		{
			enu_error_state = FAILED;
		}
	}
	else
	{
		enu_error_state = FAILED;
	}
	return enu_error_state;
	
}

