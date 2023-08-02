/*
 * 	File:						exti.c
 *	Module:					Ext_interrupt
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "exti.h"

/*=========MACRO DEFINITIONS=========*/


/*=========EXTERN VARIABLES=========*/


/*=========STATIC GLOBAL VARIABLES=========*/


/*=========TYPE DEFINITIONS=========*/


/*=========PRIVATE FUNCTIONS=========*/


/*=========APIs DEFINITIONS=========*/

/**
 * @brief       INT_init        		: Function used to initialize GPIO interrupt 
 * 
 * @param[in]   enu_gpio_port_id		:	port name id should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   enu_gpio_pin_id			:	pin name id should be	[ENU_PIN_0,ENU_PIN_1,ENU_PIN_2,ENU_PIN_3,ENU_PIN_4,ENU_PIN_5,ENU_PIN_6,ENU_PIN_7] 
 * @param[in]		enu_interrupt_edge	:	type of interrupt sense control		[ENU_LEVEL,ENU_RISING,ENU_FALLING,ENU_ANY_EDGE_CHANGE]
 * @param[in]		Fptr_callback				:	pointer to callback function
 *
 * @return      VALID_PAR						: in case of successful operation     
 *							INVALID_PAR					:	in case of wrong value       
 */
enu_int_error_t INT_init	(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_interrupt_edge_t enu_interrupt_edge,void (*Fptr_callback)(void))
{
	enu_int_error_t enu_int_error = VALID_PAR;
	if( (enu_gpio_port_id < ENU_MAX_PORT) && (enu_gpio_pin_id < ENU_MAX_PIN) && (enu_interrupt_edge < ENU_MAX_EDGE) )
	{
		str_gpio_config_t str_gpio_config ;
		str_gpio_config.enu_gpio_current_level 		= ENU_PIN_CUR_2MA;
		str_gpio_config.enu_gpio_internal_attach 	= ENU_PIN_PUR;
		str_gpio_config.enu_gpio_pin_direction 		= ENU_PIN_INPUT;
		str_gpio_config.enu_gpio_pin_id 					= enu_gpio_pin_id;
		str_gpio_config.enu_gpio_pin_level 				= ENU_PIN_LOW;
		str_gpio_config.enu_gpio_pin_mode 				= ENU_DIGITAL_MODE;
		str_gpio_config.enu_gpio_port_id 					= enu_gpio_port_id;
		GPIO_init(&str_gpio_config);
		GPIO_interruptEnable(enu_interrupt_edge,enu_gpio_port_id,enu_gpio_pin_id);
		GPIO_Setcallback(Fptr_callback,enu_gpio_port_id,enu_gpio_pin_id);
	}
	else
	{
		enu_int_error = INVALID_PAR;
	}
	return enu_int_error;
}


/**
 * @brief       INT_Deinit        	: Function used to Deinitialize GPIO interrupt 
 * 
 * @param[in]   enu_gpio_port_id		:	port name id should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   enu_gpio_pin_id			:	pin name id should be	[ENU_PIN_0,ENU_PIN_1,ENU_PIN_2,ENU_PIN_3,ENU_PIN_4,ENU_PIN_5,ENU_PIN_6,ENU_PIN_7] 
 *
 * @return      VALID_PAR						: in case of successful operation     
 *							INVALID_PAR					:	in case of wrong value       
 */
enu_int_error_t INT_Deinit			(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_int_error_t enu_int_error = VALID_PAR;
	if( (enu_gpio_port_id < ENU_MAX_PORT) && (enu_gpio_pin_id < ENU_MAX_PIN) )
	{
		GPIO_interruptDisable(enu_gpio_port_id,enu_gpio_pin_id);
		GPIO_Setcallback(NULL_PTR,enu_gpio_port_id,enu_gpio_pin_id);
	}
	else
	{
		enu_int_error = INVALID_PAR;
	}
	return enu_int_error;

}


/**
 * @brief       INT_setCallBack     : Function used to set interrup callback function 
 * 
 * @param[in]   enu_gpio_port_id		:	port name id should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   enu_gpio_pin_id			:	pin name id should be	[ENU_PIN_0,ENU_PIN_1,ENU_PIN_2,ENU_PIN_3,ENU_PIN_4,ENU_PIN_5,ENU_PIN_6,ENU_PIN_7] 
 * @param[in]		Fptr_callback				:	pointer to callback function
 *
 * @return      VALID_PAR						: in case of successful operation     
 *							INVALID_PAR					:	in case of wrong value       
 */
enu_int_error_t INT_setCallBack	(void (*Fptr_callback)(void),enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_int_error_t enu_int_error = VALID_PAR;
	if( (enu_gpio_port_id < ENU_MAX_PORT) && (enu_gpio_pin_id < ENU_MAX_PIN) )
	{
		GPIO_Setcallback(Fptr_callback,enu_gpio_port_id,enu_gpio_pin_id);
	}
	else
	{
		enu_int_error = INVALID_PAR;
	}
	return enu_int_error;

}
