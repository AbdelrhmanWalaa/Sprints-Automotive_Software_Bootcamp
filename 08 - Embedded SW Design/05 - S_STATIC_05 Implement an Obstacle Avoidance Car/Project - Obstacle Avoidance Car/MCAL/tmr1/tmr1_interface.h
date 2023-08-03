/*
 * TMR1_interface.h
 *
 * Created: 2023-05-19 5:10:30 PM
 *  Author: HAZEM-PC
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_

/*============= FILE INCLUSION =============*/
#include "../../LIB/std_types/STD_TYPES.h"
#include "../../LIB/bit_math/BIT_MATH.h"
#include "../TMR_UTILITIES/TMR_UTILITIES.h"
#include "../TMR_UTILITIES/TMR_Registers.h"
/*============= extern variables =============*/


/*============= MACRO DEFINITION =============*/


/*============= TYPE DEFINITION =============*/
typedef enum{
	OVF=4,COMP_B=8,COMP_A=16,INPUT_CAPT=32,MAX_SOURCE
	}EN_TMR_INT;
	
typedef enum{
	Disable,Enable
}EN_INT_STATE;

typedef enum{
	NO_CLK,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EXT_CLK_FALLING,EXT_CLK_RISING,MAX_CLK
	}EN_TMR_CLK;
	
typedef enum{
	TMR_FALLING,TMR_RISING
	}EN_TME_CAPT_EDGE;
	
typedef enum{
	Noise_Disable,Noise_Enable
	}EN_TMR_CAPT_FILTER;
	
typedef enum{
	Normal_mode,CMP_toggle,CMP_clear,CMP_set
	}EN_TME_CMP_MODE;
	
typedef enum{
	Normal,PWM,CTC=4,FAST_PWM,MAX_MODE=15
	}EN_TMR2_MODE;
	
typedef struct{
	EN_TMR2_MODE TMR_mode;
	EN_TMR_CLK CLK_source;
	EN_INT_STATE INT_state;
	EN_TMR_INT INT_source;
	EN_TME_CAPT_EDGE Edge_type;
	EN_TME_CMP_MODE CMP_mode;
	EN_TMR_CAPT_FILTER NO_Noise;
}ST_TME1_ConfigType;
	

/*============= FUNCTION PROTOTYPE =============*/
void TMR1_init (ST_TME1_ConfigType* TMR_config);
u16 TMR1_readTime(void);
void TMR1_clear(void);
void TMR1_stop(void);
#endif /* TMR1_INTERFACE_H_ */



