/*
 * TMR0_interface.h
 *
 * Created: 2023-05-16 6:56:32 PM
 *  Author: HAZEM-PC
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

/*============= FILE INCLUSION =============*/

#include "../../LIB/std_types/std_types.h"
#include "../TMR_UTILITIES/TMR_UTILITIES.h"
#include "../TMR_UTILITIES/TMR_Registers.h"

/*============= extern variables =============*/
extern volatile u8 g_timeout_flag;


/*============= MACRO DEFINITION =============*/
#define MAX_DELAY_COMP_MODE 40  //evaluate to 40*250ms=10 seconds

/*============= FUNCTION PROTOTYPE =============*/

/*
Description
use to apply block delay using overflow mode 
*/
void TMR0_delayMS(f32 delay);

/*
Description
use to stop timer functionality
*/
void TMR0_stop(void);


/*
Description
use to call event after elapse timeout delay using overflow mode
minimum delay is (1 ms)
*/
void TMR0_callEvent(f32 delay,void(*g_ptr)(void));

/*
Description:use to apply timeout function using compare match mode 
to check that timeout use <g_timeout_flag> which by default is zero and change to 1 after timeout
[maximum timeout] is 10.2 second
to configure maximum timeout redefine MAX_DELAY_COMP_MODE 
for example:
assume OCR register (0--255) 
max_timeout = MAX_DELAY_COMP_MODE * OCR
*/
void TMR0_timeoutMS(f32 delay); 

//void TMR0_OVFSetCallBack (void(*g_ptr)(void));
//void TMR0_CMPSetCallBack (void(*g_ptr)(void));

#endif /* TMR0_INTERFACE_H_ */