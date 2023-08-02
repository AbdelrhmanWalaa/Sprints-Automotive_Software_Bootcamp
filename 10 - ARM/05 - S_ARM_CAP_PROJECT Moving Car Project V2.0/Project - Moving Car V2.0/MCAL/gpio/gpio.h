#ifndef GPIO_H_
#define GPIO_H_

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
	ENU_DIGITAL_MODE	=0,
	ENU_ANALOG_MODE		=1,
	ENU_ALTERNATE			=2,		// TODO..implement different functionalities for GPIO pin 
	ENU_MAX_MODE			=3
}enu_gpio_pin_mode_t;

typedef enum{
	ENU_PIN_INPUT		=0,
	ENU_PIN_OUTPUT	=1,
	ENU_MAX_DIR			=2
}enu_gpio_pin_direction_t;

typedef enum{
	ENU_PIN_LOW		=0,
	ENU_PIN_HIGH	=1,
	ENU_MAX_LEVEL	=2
}enu_gpio_pin_level_t;

typedef enum{
	ENU_PIN_PUR	=0,
	ENU_PIN_PDR	=1,
	ENU_PIN_ODR	=2,
	ENU_MAX_RES	=3
}enu_gpio_internal_attach_t;


typedef enum{
	ENU_PIN_CUR_2MA	=0,
	ENU_PIN_CUR_4MA	=1,
	ENU_PIN_CUR_8MA	=2,
	ENU_MAX_CUR			=3
}enu_gpio_current_level_t;

typedef enum{
	ENU_PORT_A		=0,
	ENU_PORT_B		=1,
	ENU_PORT_C		=2,
	ENU_PORT_D		=3,
	ENU_PORT_E		=4,
	ENU_PORT_F		=5,
	ENU_MAX_PORT	=6
}enu_gpio_port_id_t;


typedef enum{
	ENU_PIN_0		=0,
	ENU_PIN_1		=1,
	ENU_PIN_2		=2,
	ENU_PIN_3		=3,
	ENU_PIN_4		=4,
	ENU_PIN_5		=5,
	ENU_PIN_6		=6,
	ENU_PIN_7		=7,
	ENU_MAX_PIN	=8
}enu_gpio_pin_id_t;


typedef enum{
	ENU_INVALID		=0,
	ENU_VALID			=1,
	ENU_MAX_ERROR	=2
}enu_gpio_error_state_t;


typedef enum{
	ENU_LEVEL						=0,
	ENU_RISING					=1,
	ENU_FALLING					=2,
	ENU_ANY_EDGE_CHANGE	=3,
	ENU_MAX_EDGE				=4
}enu_interrupt_edge_t;


typedef struct{
	enu_gpio_pin_mode_t 				enu_gpio_pin_mode;
	enu_gpio_pin_direction_t 		enu_gpio_pin_direction;
	enu_gpio_pin_level_t				enu_gpio_pin_level;
	enu_gpio_internal_attach_t	enu_gpio_internal_attach;
	enu_gpio_current_level_t		enu_gpio_current_level;
	enu_gpio_port_id_t					enu_gpio_port_id;
	enu_gpio_pin_id_t						enu_gpio_pin_id;
}str_gpio_config_t;

/*=========APIs DECLERATIONS=========*/

enu_gpio_error_state_t GPIO_init 						(const str_gpio_config_t* str_gpio_config);
enu_gpio_error_state_t GPIO_digitalWrite		(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_gpio_pin_level_t enu_gpio_pin_level);
enu_gpio_error_state_t GPIO_digitalRead			(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,uint8* P_value);
enu_gpio_error_state_t GPIO_togglePin				(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);
enu_gpio_error_state_t GPIO_interruptEnable	(enu_interrupt_edge_t enu_interrupt_edge,enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);
void GPIO_interruptDisable									(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);
enu_gpio_error_state_t GPIO_Setcallback			(void (*Fptr)(void),enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);

#endif	/* GPIO_H_ */



