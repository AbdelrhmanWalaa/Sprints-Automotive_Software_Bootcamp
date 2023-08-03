/*
 * US_Interface.h
 *
 * Created: 2023-05-20 3:39:57 AM
 *  Author: HAZEM-PC
 */ 


#ifndef US_INTERFACE_H_
#define US_INTERFACE_H_

/*============= FILE INCLUSION =============*/
#include "../icu/icu_interface.h"
#include "../../MCAL/dio/dio_interface.h"
#include <math.h>


/*============= MACRO DEFINITION =============*/
#define HIGH 1
#define LOW 0

/*============= FUNCTION PROTOTYPE =============*/

/*
  Description : Function to initialize the ultrasonic driver
  1-initialize ICU driver
  2-set callback function
  3-setup trigger pin direction as output
  4-setup External interrupt source
 <Inputs>
  u8 a_triggerPort:trigger port 
  a_triggerPin:trigger pin
  en_a_echoPin: interrupt source pin [EN_INT0,EN_INT1,EN_INT2]
 */
EN_state US_init(u8 a_triggerPort,u8 a_triggerPin,EN_ICU_Source en_a_echoPin);

// Description :function to read distance of from the sensor
u16 US_readDistance(void);




#endif /* US_INTERFACE_H_ */