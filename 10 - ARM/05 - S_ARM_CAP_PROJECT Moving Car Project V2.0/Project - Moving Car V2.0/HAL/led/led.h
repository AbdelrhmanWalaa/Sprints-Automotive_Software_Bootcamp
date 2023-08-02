#ifndef LED_H_
#define LED_H_

/*=========FILE INCLUSION=========*/
#include "../../MCAL/gpio/gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/

enu_error_state_t LED_init(enu_gpio_port_id_t enu_gpio_port_id, enu_gpio_pin_id_t enu_gpio_pin_id);
enu_error_state_t LED_digitalWrite(enu_gpio_port_id_t enu_gpio_port_id, enu_gpio_pin_id_t enu_gpio_pin_id, enu_gpio_pin_level_t enu_gpio_pin_level);

#endif	/* LED_H_ */

