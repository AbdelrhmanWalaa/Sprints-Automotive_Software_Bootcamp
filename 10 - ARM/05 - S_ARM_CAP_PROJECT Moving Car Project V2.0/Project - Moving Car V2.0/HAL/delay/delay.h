#ifndef DELAY_H_
#define DELAY_H_

/*=========FILE INCLUSION=========*/
#include "../../MCAL/gpt/gpt.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	INVALID_OPERATION,
	VALID_OPERATION,
	MAX_DELAY_ERROR
}enu_delay_error_t;


/*=========APIs DECLERATIONS=========*/
enu_delay_error_t delay_us (enu_timer_id_t enu_timer_id,uint32 u32_time);
enu_delay_error_t delay_ms (enu_timer_id_t enu_timer_id,uint32 u32_time);
enu_delay_error_t delay_sec (enu_timer_id_t enu_timer_id,uint32 u32_time);
#endif	/* DELAY_H_ */

