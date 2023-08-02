#ifndef BUTTON_H_
#define BUTTON_H_

/*=========FILE INCLUSION=========*/
#include "../../MCAL/gpio/gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/
enu_error_state_t BUTTON_init(enu_gpio_port_id_t enu_gpio_port_id, enu_gpio_pin_id_t enu_gpio_pin_id);
enu_error_state_t BUTTON_digitalRead(enu_gpio_port_id_t enu_gpio_port_id, enu_gpio_pin_id_t enu_gpio_pin_id, uint8* p_value);

#endif	/* BUTTON_H_ */

