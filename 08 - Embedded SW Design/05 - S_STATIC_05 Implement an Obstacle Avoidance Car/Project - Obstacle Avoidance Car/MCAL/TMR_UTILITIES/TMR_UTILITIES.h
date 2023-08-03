/*
 * TMR_UTILITIES.h
 *
 * Created: 2023-05-16 6:57:41 PM
 *  Author: HAZEM-PC
 */ 


#ifndef TMR_UTILITIES_H_
#define TMR_UTILITIES_H_

/*============= FILE INCLUSION =============*/
//#include "../../LIB/mcu_config/mcu_config.h"

#define F_CPU	8000000UL

/*============= MACRO DEFINITION =============*/
//timer common macros

#define MAX_COUNT 256
#define MIN_COUNT 1
#define INIT_VALUE(T_max,T_delay,tick)  (((f32)T_max-T_delay)/tick)
#define MAX_DELAY_MS(prescaler) ((((f32)prescaler/F_CPU)*MAX_COUNT)*1000UL)
#define MIN_DELAY_MS(prescaler) ((((f32)prescaler/F_CPU)*MIN_COUNT)*1000UL)
#define MAX_DELAY_US(prescaler) ((((f32)prescaler/F_CPU)*MAX_COUNT)*1000000UL)
#define MIN_DELAY_US(prescaler) ((((f32)prescaler/F_CPU)*MIN_COUNT)*1000000UL)

#define TRUE	1
#define FALSE	0

//pre_scaler values for TIMER0
#define P_0    0
#define P_1    1
#define P_8    8
#define P_32   32
#define P_64   64
#define P_128  128
#define P_256  256
#define P_1024 1024


#endif /* TMR_PRIVATE_H_ */