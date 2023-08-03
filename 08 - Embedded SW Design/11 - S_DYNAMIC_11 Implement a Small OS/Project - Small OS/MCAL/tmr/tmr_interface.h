/*
 * tmr_interface.h
 *
 * Created: 2023-06-01 2:33:29 AM
 *  Author: HAZEM-PC
 */ 

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/*============= FILE INCLUSION =============*/
#include "tmr_utilities.h"

#include "../../LIB/mcu_config/mcu_config.h"
#include "../../LIB/std_types/std_types.h"
#include "../../LIB/bit_math/bit_math.h"

/*============= extern variables =============*/


/*============= MACRO DEFINITION =============*/


/*============= TYPE DEFINITION =============*/

typedef enum{
	NORMAL,
	PWM,
	CTC			=0x08,
	FAST_PWM	=0x09,
	MAX_MODE	=0x0F
	}enu_tmr_mode_t;

typedef enum{
	CLK_STOP,
	CLK_1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024,
	CLK_EXT_FALLING,
	CLK_EXT_RISING,
	MAX_CLK
	}enu_tmr_clk_t;

typedef enum{
	DISABLE,
	EN_OVF		=4,
	EN_COM_B	=8,
	EN_COM_A	=16,
	EN_ICU		=32,
	MAX_SOURCE
	}enu_tmr_intState_t;

typedef struct{
	enu_tmr_mode_t		enu_tmr_mode;
	enu_tmr_clk_t		enu_tmr_clk;
	enu_tmr_intState_t	enu_tmr_intState;
}str_tmr_configType;

typedef enum{
	TMR_STATE_FAILED,
	TMR_STATE_SUCCESS
	}enu_tmr_state_t;

/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief                                           :   used to initialize timer with required the configuration
 * 
 * @param[in]   str_tmr_config						:   pointer to configuration structure 
 * 
 * @return      TMR_STATE_SUCCESS					:   in case of successful operation     
 *              TMR_STATE_FAILED 					:   in case of the pointer is not valid     
 */	
enu_tmr_state_t tmr_Init	(str_tmr_configType* str_tmr_config);

/**
 * @brief                                           :   Function used to set the timer value
 * 
 * @param[in]   time								:	the required periodic value from the timer  
 * 
 * @return      void								:       
 *                  
 */
void tmr_setTimer			(u16 time);

/**
 * @brief                                           :   Function used to clear the timer value
 * 
 * @param[in]   void								:   
 * 
 * @return      void								:       
 *                  
 */
void tmr_Clear				(void);

/**
 * @brief                                           :   Function used to stop the timer clock
 * 
 * @param[in]   void								:   
 * 
 * @return      void								:       
 *                  
 */
void tmr_Stop				(void);

/**
 * @brief                                           :   Function used to resume the timer clock
 * 
 * @param[in]   void								:   
 * 
 * @return      void								:       
 *                  
 */
void tmr_resume				(void);

/**
 * @brief                                           :   Function used to set timer overflow callback function
 * 
 * @param[in]   g_ptr								:	pointer to the callback function   
 * 
 * @return      void								:       
 *                  
 */
void tmr_ovf_setCallback	(void(*g_ptr)(void));

/**
 * @brief                                           :   Function used to set timer compare_a callback function
 * 
 * @param[in]   g_ptr								:	pointer to the callback function   
 * 
 * @return      void								:       
 *                  
 */
void tmr_cmpa_setCallback	(void(*g_ptr)(void));

/**
 * @brief                                           :   Function used to set timer compare_b callback function
 * 
 * @param[in]   g_ptr								:	pointer to the callback function   
 * 
 * @return      void								:       
 *                  
 */
void tmr_cmpb_setCallback	(void(*g_ptr)(void));

/**
 * @brief                                           :   Function used to set timer ICU callback function
 * 
 * @param[in]   g_ptr								:	pointer to the callback function   
 * 
 * @return      void								:       
 *                  
 */
void tmr_icu_setCallback	(void(*g_ptr)(void));


#endif /* TMR_INTERFACE_H_ */