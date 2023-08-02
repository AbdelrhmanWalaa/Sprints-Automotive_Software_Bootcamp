/*
 * 	File:						gpt.c
 *	Module:					General Purpose Timers(GPT)
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "gpt.h"

/*=========MACRO DEFINITIONS=========*/
#define TAEN 			0
#define TBEN 			8
#define TACDIR		4
#define TBCDIR		4
#define TASTALL		1
#define TBSTALL		9
#define TATOIM		0
#define TBTOIM		8
#define TATORIS		0
#define TATOCINT 	0
#define F_CPU			16
#define MAX_16BIT_TIME_US 	4096 
#define MAX_32BIT_TIME_US		268435456UL 
#define MAX_64BIT_TIME_US 	1152921504606850000ULL 

#define MASKING_BIT 0xFFFFFFFC

#define MSEC_CONVERT	1000
#define USEC_CONVERT	1000000UL

#define TAMR_BIT0	0
#define TAMR_BIT1	1


#define GPTMCFG_CONC	0
#define GPTMCFG_RTC		1
#define GPTMCFG_INDVI	4

/*=========TYPE DEFINITIONS=========*/

typedef enum{
	ONE_SHOT			=0x1,
	PERIODIC_MODE	=0x2,
	CAPTURE_MODE	=0x3,
	MAX_MODE
}enu_timer_mode_pin_t;

typedef enum{
	SPLIT_MODE,
	CONCT_MODE,
	MAX_REG_MODE
}enu_gpt_reg_mode_t;


/*=========EXTERN VARIABLES=========*/


/*=========GLOBAL VARIABLES=========*/
static boolean gs_bo_init_state[MAX_TIMER_ID] = {FALSE};
static enu_timer_int_state_t arr_enu_timer_int_state[MAX_TIMER_ID] = {TIMER_DISABLE_INT};
static volatile ptr_callback_t gl_arr_ptr_callback[MAX_TIMER_ID] = {NULL_PTR};
/*=========STATIC FUNCTIONS=========*/


/*=========APIs DECLERATIONS=========*/
enu_timer_error_t gpt_Init 	(str_gpt_config_t* str_gpt_config)
{
	enu_timer_error_t enu_timer_error = GPT_VALID_OPERATION;
//	uint8 u8_index = 0;
	uint8 u8_timer_id = 0;
	
	//todo..if use CCP the clock to the appropiate pin must be enabled via the RCGCGPIO register
	//todo..Configure the PMCn fields in the GPIOPCTL register to assign the CCP signals to the appropriate pins
	if(str_gpt_config != NULL_PTR)
	{
		if(gs_bo_init_state[str_gpt_config->enu_timer_id] == FALSE)
		{
			//for(u8_index = 0; u8_index < MAX_TIMER_ID; u8_index ++)
			{
				//u8_timer_id = str_gpt_config[u8_index].enu_timer_id;
				u8_timer_id = str_gpt_config->enu_timer_id;
				if(u8_timer_id < MAX_TIMER_ID)
				{
					//to use GPT enable timer module in run mode through RCGCTIMER or RCGCWTIMER registers
					if (u8_timer_id <= TIMER5_ID)
					{
						SET_BIT(RCGCTIMER_REG,u8_timer_id);
					}
					else 
					{
						SET_BIT(RCGCWTIMER_REG,((u8_timer_id)-6));
					}
					//Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes.
					CLEAR_BIT(GPTMCTL(u8_timer_id),TAEN);
					CLEAR_BIT(GPTMCTL(u8_timer_id),TBEN);
					//Write the GPTM Configuration Register (GPTMCFG) whether the GPTM is in 32- or 64-bit mode (concatenated timers) 
					//or in 16- or 32-bit mode (individual, split timers).
					//select concatenated mode
					CLEAR_BIT(GPTMCFG(u8_timer_id),GPTMCFG_CONC);
			
					//Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
					if(str_gpt_config->enu_timer_mode == ONESHOT)
					{
						//SET_BIT(GPTMTAMR(u8_timer_id),TAMR_BIT0);
						GPTMTAMR(u8_timer_id)=ONE_SHOT;
						//GPTMTAMR(u8_timer_id) = (GPTMTAMR(u8_timer_id) & MASKING_BIT ) | (ONE_SHOT);
					}
					else if(str_gpt_config->enu_timer_mode == PERIODIC)
					{
						//SET_BIT(GPTMTAMR(u8_timer_id),TAMR_BIT1);
						GPTMTAMR(u8_timer_id)=PERIODIC_MODE;
						//GPTMTAMR(u8_timer_id) = (GPTMTAMR(u8_timer_id) & MASKING_BIT ) | (PERIODIC_MODE);
					}
					else
					{
						//not support yet ..TODO
						enu_timer_error = GPT_INVALID_OPERATION;
					}		
					//set count direction to count down
					CLEAR_BIT(GPTMTAMR(u8_timer_id),TACDIR);
					//enable GPT stall mode
//					SET_BIT(GPTMCTL(u8_timer_id),TASTALL);
					//check interrupt state
					if(str_gpt_config->enu_timer_int_state == TIMER_ENABLE_INT)
					{
						// enable GPTMIMR Interrupt mask register 
						SET_BIT(GPTMIMR(u8_timer_id),TATOIM);
						//enable NVIC IRQ
						gpt_enable_notification(str_gpt_config->enu_timer_id);
						//save callback function
						gl_arr_ptr_callback[u8_timer_id] = str_gpt_config->ptr_callback;
						//save interrupt state
						arr_enu_timer_int_state[u8_timer_id] = TIMER_ENABLE_INT;
					}
				}
				else
				{
					enu_timer_error = GPT_INVALID_OPERATION;
				}		
	
			}
		}
		else
		{
			enu_timer_error = GPT_INVALID_OPERATION;
		}
		
		gs_bo_init_state[str_gpt_config->enu_timer_id] = TRUE;
	}
	else
	{
		//already initialized
		enu_timer_error = GPT_INVALID_OPERATION;
	}
	
	return enu_timer_error;
}


enu_timer_error_t gpt_startTimer (enu_timer_id_t enu_timer_id,uint32 u32_time,enu_tick_unit_t enu_tick_unit)
{
	enu_timer_error_t enu_timer_error = GPT_VALID_OPERATION;
	uint64 u64_num_of_ticks = 0;
	uint64 u64_time_us = 0;
	if(gs_bo_init_state[enu_timer_id] == TRUE)
	{
		if(enu_timer_id < MAX_TIMER_ID)
		{
			if(enu_tick_unit == USEC)
			{
				u64_time_us = u32_time;
			}
			else if(enu_tick_unit == MSEC)
			{
				u64_time_us = (uint64)u32_time * MSEC_CONVERT;
			}
			else 
			{
				u64_time_us = (uint64)u32_time * USEC_CONVERT;
			}
			
			//calculate load value
			if((u64_time_us < MAX_32BIT_TIME_US) || (u64_time_us < MAX_64BIT_TIME_US))
			{
				u64_num_of_ticks = (uint64)((float64)u64_time_us/0.0625F);				
			}
			else
			{
				enu_timer_error = GPT_INVALID_OPERATION;
			}
			
			//Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
			GPTMTAILR(enu_timer_id) = (uint32)u64_num_of_ticks;
			
			if(enu_timer_id >= TIMER6_ID)
			{
				//wide register
				GPTMTBILR(enu_timer_id) = (uint32)((u64_num_of_ticks) >> 32);
			}

			//Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
			SET_BIT(GPTMCTL(enu_timer_id),TAEN);
			//SET_BIT(GPTMCTL(enu_timer_id),TBEN);
			//check whether using polling or interrupt
			if(arr_enu_timer_int_state[enu_timer_id] == TIMER_DISABLE_INT)
			{
				//polling through GPTM Raw Interrupt Status (GPTMRIS),GPTM Timer A Time-Out Raw Interrupt
				while(BIT_IS_CLEAR(GPTMRIS(enu_timer_id),TATORIS));
				//clear the interrupt flag through GPTM Interrupt Clear (GPTMICR),
				SET_BIT(GPTMICR(enu_timer_id),TATOCINT);
				//gpt_stopTimer(enu_timer_id);
			}
			else
			{
				//interrupt wait for callback
			}
		}
		else
		{
			enu_timer_error = GPT_INVALID_OPERATION;
		}
	}
	else
	{
		enu_timer_error = GPT_INVALID_OPERATION;
	}
	return enu_timer_error;
}


enu_timer_error_t gpt_stopTimer (enu_timer_id_t enu_timer_id)
{
	enu_timer_error_t enu_timer_error = GPT_VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		//the timer is disabled (the TnEN bit in the GPTMCTL register is cleared)
			CLEAR_BIT(GPTMCTL(enu_timer_id),TAEN);
			CLEAR_BIT(GPTMCTL(enu_timer_id),TBEN);
	}
	else
	{
		enu_timer_error = GPT_INVALID_OPERATION;
	}
	return enu_timer_error;
}


enu_timer_error_t gpt_enable_notification(enu_timer_id_t enu_timer_id)
{
	enu_timer_error_t enu_timer_error = GPT_VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		if (enu_timer_id == TIMER0_ID)
		{
			NVIC_EnableIRQ(TIMER0A_IRQn);
		}
		else if (enu_timer_id == TIMER1_ID)
		{
			NVIC_EnableIRQ(TIMER1A_IRQn);
		}
		else if (enu_timer_id == TIMER2_ID)
		{
			NVIC_EnableIRQ(TIMER2A_IRQn);
		}
		else if (enu_timer_id == TIMER3_ID)
		{
			NVIC_EnableIRQ(TIMER3A_IRQn);
		}
		else if (enu_timer_id == TIMER4_ID)
		{
			NVIC_EnableIRQ(TIMER4A_IRQn);
		}
		else if (enu_timer_id == TIMER5_ID)
		{
			NVIC_EnableIRQ(TIMER5A_IRQn);
		}
		else if (enu_timer_id == TIMER6_ID)
		{
			NVIC_EnableIRQ(WTIMER0A_IRQn);
		}
		else if (enu_timer_id == TIMER7_ID)
		{
			NVIC_EnableIRQ(WTIMER1A_IRQn);
		}
		else if (enu_timer_id == TIMER8_ID)
		{
			NVIC_EnableIRQ(WTIMER2A_IRQn);
		}
		else if (enu_timer_id == TIMER9_ID)
		{
			NVIC_EnableIRQ(WTIMER3A_IRQn);
		}
		else if (enu_timer_id == TIMER10_ID)
		{
			NVIC_EnableIRQ(WTIMER4A_IRQn);
		}
		else 
		{
			NVIC_EnableIRQ(WTIMER5A_IRQn);
		}
	}
	else
	{	
		enu_timer_error = GPT_INVALID_OPERATION;
	}
	__enable_irq();
	return enu_timer_error;
}

enu_timer_error_t gpt_disable_notification (enu_timer_id_t enu_timer_id)
{
	enu_timer_error_t enu_timer_error = GPT_VALID_OPERATION;
	if(enu_timer_id < MAX_TIMER_ID)
	{
			// clear GPTMIMR Interrupt mask register 
			CLEAR_BIT(GPTMIMR(enu_timer_id),TATOIM);
	}
	else
	{
		enu_timer_error = GPT_INVALID_OPERATION;
	}
	return enu_timer_error;
}

enu_timer_error_t gpt_getElapsedTime 	(enu_timer_id_t enu_timer_id,uint32* u32_ptr_elapse_time);

enu_timer_error_t gpt_getReminingTime (enu_timer_id_t enu_timer_id,uint32* u32_ptr_remaining_time);


//TIMER ISR HANDLERS

void TIMER0A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER0_ID] != NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER0_ID]();
		 SET_BIT(GPTMICR(TIMER0_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void TIMER1A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER1_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER1_ID]();
		 SET_BIT(GPTMICR(TIMER1_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void TIMER2A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER2_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER2_ID]();
		 SET_BIT(GPTMICR(TIMER2_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

void TIMER3A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER3_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER3_ID]();
		 SET_BIT(GPTMICR(TIMER3_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void TIMER4A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER4_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER4_ID]();
		 SET_BIT(GPTMICR(TIMER4_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

void TIMER5A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER5_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER5_ID]();
		 SET_BIT(GPTMICR(TIMER5_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

void WTIMER0A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER6_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER6_ID]();
		 SET_BIT(GPTMICR(TIMER6_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void WTIMER1A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER7_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER7_ID]();
		 SET_BIT(GPTMICR(TIMER7_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void WTIMER2A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER8_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER8_ID]();
		 SET_BIT(GPTMICR(TIMER8_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

void WTIMER3A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER9_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER9_ID]();
		 SET_BIT(GPTMICR(TIMER9_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}


void WTIMER4A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER10_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER10_ID]();
		 SET_BIT(GPTMICR(TIMER10_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

void WTIMER5A_Handler(void) 
{
   if (gl_arr_ptr_callback[TIMER11_ID]!=NULL_PTR)
	 {
		 gl_arr_ptr_callback[TIMER11_ID]();
		 SET_BIT(GPTMICR(TIMER11_ID),TATOCINT);
	 }
	 else
	 {
		 //do nothing
	 }
}

