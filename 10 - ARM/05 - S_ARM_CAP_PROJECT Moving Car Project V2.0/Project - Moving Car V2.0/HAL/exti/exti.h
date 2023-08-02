#ifndef EXTI_H_
#define EXTI_H_

/*=========FILE INCLUSION=========*/
#include "../../MCAL/gpio/gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

typedef enum{
	INVALID_PAR			=0,
	VALID_PAR				=1,
	MAX_ERROR_PAR		=2
}enu_int_error_t;


/*=========APIs DECLERATIONS=========*/

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
enu_int_error_t INT_init				(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_interrupt_edge_t enu_interrupt_edge,void (*Fptr_callback)(void));


/**
 * @brief       INT_Deinit        	: Function used to Deinitialize GPIO interrupt 
 * 
 * @param[in]   enu_gpio_port_id		:	port name id should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   enu_gpio_pin_id			:	pin name id should be	[ENU_PIN_0,ENU_PIN_1,ENU_PIN_2,ENU_PIN_3,ENU_PIN_4,ENU_PIN_5,ENU_PIN_6,ENU_PIN_7] 
 *
 * @return      VALID_PAR						: in case of successful operation     
 *							INVALID_PAR					:	in case of wrong value       
 */
enu_int_error_t INT_Deinit			(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);


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
enu_int_error_t INT_setCallBack	(void (*Fptr_callback)(void),enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);

#endif	/* EXTI_H_ */


