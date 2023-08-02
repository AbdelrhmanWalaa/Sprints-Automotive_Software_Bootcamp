/*
 * 	File:						gpio.c
 *	Module:					gpio
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "gpio.h"

/*=========MACRO DEFINITIONS=========*/
#define PORT_LOCK_VALUE		(uint32)(0x4C4F434B)


/*=========EXTERN VARIABLES=========*/


/*=========GLOBAL VARIABLES=========*/
static  void(*fptr_A0)(void);
static  void(*fptr_A1)(void);
static  void(*fptr_A2)(void);
static  void(*fptr_A3)(void);
static  void(*fptr_A4)(void);
static  void(*fptr_A5)(void);
static  void(*fptr_A6)(void);
static  void(*fptr_A7)(void);

static  void(*fptr_B0)(void);
static  void(*fptr_B1)(void);
static  void(*fptr_B2)(void);
static  void(*fptr_B3)(void);
static  void(*fptr_B4)(void);
static  void(*fptr_B5)(void);
static  void(*fptr_B6)(void);
static  void(*fptr_B7)(void);

static  void(*fptr_C0)(void);
static  void(*fptr_C1)(void);
static  void(*fptr_C2)(void);
static  void(*fptr_C3)(void);
static  void(*fptr_C4)(void);
static  void(*fptr_C5)(void);
static  void(*fptr_C6)(void);
static  void(*fptr_C7)(void);

static  void(*fptr_D0)(void);
static  void(*fptr_D1)(void);
static  void(*fptr_D2)(void);
static  void(*fptr_D3)(void);
static  void(*fptr_D4)(void);
static  void(*fptr_D5)(void);
static  void(*fptr_D6)(void);
static  void(*fptr_D7)(void);

static  void(*fptr_E0)(void);
static  void(*fptr_E1)(void);
static  void(*fptr_E2)(void);
static  void(*fptr_E3)(void);
static  void(*fptr_E4)(void);
static  void(*fptr_E5)(void);
static  void(*fptr_E6)(void);
static  void(*fptr_E7)(void);

static  void(*fptr_F0)(void);
static  void(*fptr_F1)(void);
static  void(*fptr_F2)(void);
static  void(*fptr_F3)(void);
static  void(*fptr_F4)(void);
static  void(*fptr_F5)(void);
static  void(*fptr_F6)(void);
static  void(*fptr_F7)(void);

/*=========TYPE DEFINITIONS=========*/


/*=========APIs DEFINITIONS=========*/
enu_gpio_error_state_t GPIO_init 	(const str_gpio_config_t* str_gpio_config)
{
	enu_gpio_port_id_t 			enu_gpio_port_id;
	enu_gpio_pin_id_t				enu_gpio_pin_id;
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	
	if(str_gpio_config != NULL_PTR)
	{
			enu_gpio_port_id 	= str_gpio_config->enu_gpio_port_id;
			enu_gpio_pin_id 	= str_gpio_config->enu_gpio_pin_id;

			if(enu_gpio_port_id == ENU_PORT_A)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_0);
			}
			else if (enu_gpio_port_id == ENU_PORT_B)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_1);
			}
			else if (enu_gpio_port_id == ENU_PORT_C)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_2);
			}
			else if (enu_gpio_port_id == ENU_PORT_D)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_3);
			}
			else if (enu_gpio_port_id == ENU_PORT_E)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_4);
			}
			else if (enu_gpio_port_id == ENU_PORT_F)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_5);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//unlock the GPIO 
			GPIOLOCK(enu_gpio_port_id) = PORT_LOCK_VALUE;
			//enable changes to pin
			SET_BIT(GPIOCR(enu_gpio_port_id),enu_gpio_pin_id);
			//step 1:initialize the clock
			//step 2:setup the direction
			if(str_gpio_config->enu_gpio_pin_direction == ENU_PIN_OUTPUT)
			{
				SET_BIT(GPIODIR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				CLEAR_BIT(GPIODIR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			//step 4:setup the internal attach
			if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_PUR)
			{
				SET_BIT(GPIOPUR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_PDR)
			{
				SET_BIT(GPIOPDR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_ODR)
			{
				SET_BIT(GPIOODR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 5:setup the current level
			if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_2MA)
			{
				SET_BIT(GPIODR2R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_4MA)
			{
				SET_BIT(GPIODR4R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_8MA)
			{
				SET_BIT(GPIODR8R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 6:setup digital mode
			if(str_gpio_config->enu_gpio_pin_mode == ENU_DIGITAL_MODE)
			{
				//disable the alternative functionality on this pin by clear the corresponding bit on GPIOAFSEL
				CLEAR_BIT(GPIOAFSEL(enu_gpio_port_id),enu_gpio_pin_id);
				//enable the digital functionality on this pin by set the corresponding bit on GPIODEN
				SET_BIT(GPIODEN(enu_gpio_port_id),enu_gpio_pin_id);
				//disable the analog functionality on this pin by clear the corresponding bit on GPIOAMSEL
				CLEAR_BIT(GPIOAMSEL(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_mode == ENU_ANALOG_MODE)
			{
				//disable the alternative functionality on this pin by clear the corresponding bit on GPIOAFSEL
				CLEAR_BIT(GPIOAFSEL(enu_gpio_port_id),enu_gpio_pin_id);
				//disable the digital functionality on this pin by set the corresponding bit on GPIODEN
				CLEAR_BIT(GPIODEN(enu_gpio_port_id),enu_gpio_pin_id);
				//enable the analog functionality on this pin by clear the corresponding bit on GPIOAMSEL
				SET_BIT(GPIOAMSEL(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_mode == ENU_ALTERNATE)
			{
				//TODO implmented in the future version
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 3:setup the output level
			if(str_gpio_config->enu_gpio_pin_level == ENU_PIN_LOW)
			{
				CLEAR_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_level == ENU_PIN_HIGH)
			{
				SET_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}



enu_gpio_error_state_t GPIO_digitalWrite(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_gpio_pin_level_t enu_gpio_pin_level)
{
	
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if(enu_gpio_port_id < ENU_MAX_PORT)
	{
		if(enu_gpio_pin_id < ENU_MAX_PIN)
		{
			if(enu_gpio_pin_level == ENU_PIN_LOW)
			{
				CLEAR_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(enu_gpio_pin_level == ENU_PIN_HIGH)
			{
				SET_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
	
}


enu_gpio_error_state_t GPIO_digitalRead	(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,uint8* P_value)
{
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if(P_value != NULL_PTR)
	{
		if(enu_gpio_port_id < ENU_MAX_PORT)
		{
			if(enu_gpio_pin_id < ENU_MAX_PIN)
			{
				if(BIT_IS_CLEAR(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id))
				{
					*P_value = LOGIC_HIGH;
				}
				else 
				{
					*P_value = LOGIC_LOW;
				}
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


enu_gpio_error_state_t GPIO_togglePin		(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if(enu_gpio_port_id < ENU_MAX_PORT)
	{
		if(enu_gpio_pin_id < ENU_MAX_PIN)
		{
				TOGGLE_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


enu_gpio_error_state_t GPIO_interruptEnable(enu_interrupt_edge_t enu_interrupt_edge,enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
				enu_gpio_error_state_t enu_gpio_error_state = ENU_VALID;
	      switch(enu_interrupt_edge)
				{
						case ENU_LEVEL:
						SET_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						break;
						case ENU_FALLING:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						case ENU_RISING:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						case ENU_ANY_EDGE_CHANGE:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;	
					}
					SET_BIT(GPIOIM(enu_gpio_port_id),enu_gpio_pin_id);
					switch (enu_gpio_port_id)
					{
						case ENU_PORT_A:
						NVIC_EnableIRQ(GPIOA_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_B:
						NVIC_EnableIRQ(GPIOB_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_C:
						NVIC_EnableIRQ(GPIOC_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_D:
						NVIC_EnableIRQ(GPIOD_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_E:
						NVIC_EnableIRQ(GPIOE_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_F:
						NVIC_EnableIRQ(GPIOF_IRQn);
            __enable_irq();
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;	
					}
	return enu_gpio_error_state;
}


void GPIO_interruptDisable(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	  CLEAR_BIT(GPIOIM(enu_gpio_port_id),enu_gpio_pin_id);
		CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
		CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
		CLEAR_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
}

enu_gpio_error_state_t GPIO_Setcallback(void (*Fptr)(void),enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_gpio_error_state_t enu_gpio_error_state = ENU_VALID;
	if (Fptr != NULL_PTR)
	{
	switch (enu_gpio_port_id)
					{
						case ENU_PORT_A:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_A0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_A1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_A2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_A3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_A4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_A5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_A6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_A7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
						}
						break;
						case ENU_PORT_B:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_B0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_B1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_B2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_B3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_B4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_B5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_B6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_B7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
						}
						break;
						case ENU_PORT_C:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_C0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_C1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_C2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_C3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_C4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_C5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_C6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_C7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
							
						}
						break;
						case ENU_PORT_D:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_D0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_D1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_D2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_D3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_D4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_D5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_D6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_D7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
						}
						break;
						case ENU_PORT_E:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_E0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_E1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_E2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_E3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_E4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_E5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_E6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_E7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
						}
						break;
						case ENU_PORT_F:
						{
							if(enu_gpio_pin_id == ENU_PIN_0)
							{
								fptr_F0=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_1)
							{
								fptr_F1=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_2)
							{
								fptr_F2=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_3)
							{
								fptr_F3=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_4)
							{
								fptr_F4=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_5)
							{
								fptr_F5=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_6)
							{
								fptr_F6=Fptr;
							}
							else if(enu_gpio_pin_id == ENU_PIN_7)
							{
								fptr_F7=Fptr;
							}
							else
							{
								enu_gpio_error_state = ENU_INVALID;
								//do nothing
							}
						}
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;
					}
	 }
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


/*================interrupt handler================*/
void GPIOA_Handler(void) 
{
   if ((fptr_A0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_0)))
	 {
		 fptr_A0();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_0);
	 }
	 if ((fptr_A1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_1)))
	 {
		 fptr_A1();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_1);
	 }
	 if ((fptr_A2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_2)))
	 {
		 fptr_A2();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_2);
	 }
	 if ((fptr_A3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_3)))
	 {
		 fptr_A3();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_3);
	 }
	 if ((fptr_A4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_4)))
	 {
		 	fptr_A4();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_4);
	 }
	 if ((fptr_A5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_5)))
	 {
		 	fptr_A5();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_5);
	 }
	 if ((fptr_A6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_6)))
	 {
		 	fptr_A6();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_6);
	 }
	 if ((fptr_A7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_A),ENU_PIN_7)))
	 {
		 	fptr_A7();
		 SET_BIT(GPIOICR(ENU_PORT_A),ENU_PIN_7);
	 }
}


void GPIOB_Handler(void) 
{
   if ((fptr_B0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_0)))
	 {
		 fptr_B0();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_0);
	 }
	 if ((fptr_B1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_1)))
	 {
		 fptr_B1();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_1);
	 }
	 if ((fptr_B2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_2)))
	 {
		 fptr_B2();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_2);
	 }
	 if ((fptr_B3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_3)))
	 {
		 fptr_B3();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_3);
	 }
	 if ((fptr_B4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_4)))
	 {
		 	fptr_B4();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_4);
	 }
	 if ((fptr_B5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_5)))
	 {
		 	fptr_B5();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_5);
	 }
	 if ((fptr_B6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_6)))
	 {
		 	fptr_B6();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_6);
	 }
	 if ((fptr_B7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_B),ENU_PIN_7)))
	 {
		 	fptr_B7();
		 SET_BIT(GPIOICR(ENU_PORT_B),ENU_PIN_7);
	 }
}


void GPIOC_Handler(void)
{
   if ((fptr_C0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_0)))
	 {
		 fptr_C0();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_0);
	 }
	 if ((fptr_C1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_1)))
	 {
		 fptr_C1();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_1);
	 }
	 if ((fptr_C2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_2)))
	 {
		 fptr_C2();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_2);
	 }
	 if ((fptr_C3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_3)))
	 {
		 fptr_C3();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_3);
	 }
	 if ((fptr_C4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_4)))
	 {
		 	fptr_C4();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_4);
	 }
	 if ((fptr_C5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_5)))
	 {
		 	fptr_C5();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_5);
	 }
	 if ((fptr_C6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_6)))
	 {
		 	fptr_C6();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_6);
	 }
	 if ((fptr_C7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_C),ENU_PIN_7)))
	 {
		 	fptr_C7();
		 SET_BIT(GPIOICR(ENU_PORT_C),ENU_PIN_7);
	 }
}


void GPIOD_Handler(void) 
{
  if ((fptr_D0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_0)))
	 {
		 fptr_D0();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_0);
	 }
	 if ((fptr_D1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_1)))
	 {
		 fptr_D1();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_1);
	 }
	 if ((fptr_D2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_2)))
	 {
		 fptr_D2();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_2);
	 }
	 if ((fptr_D3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_3)))
	 {
		 fptr_D3();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_3);
	 }
	 if ((fptr_D4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_4)))
	 {
		 	fptr_D4();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_4);
	 }
	 if ((fptr_D5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_5)))
	 {
		 	fptr_D5();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_5);
	 }
	 if ((fptr_D6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_6)))
	 {
		 	fptr_D6();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_6);
	 }
	 if ((fptr_D7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_D),ENU_PIN_7)))
	 {
		 	fptr_D7();
		 SET_BIT(GPIOICR(ENU_PORT_D),ENU_PIN_7);
	 }
}


void GPIOE_Handler(void)
{
   if ((fptr_E0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_0)))
	 {
		 fptr_E0();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_0);
	 }
	 if ((fptr_E1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_1)))
	 {
		 fptr_E1();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_1);
	 }
	 if ((fptr_E2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_2)))
	 {
		 fptr_E2();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_2);
	 }
	 if ((fptr_E3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_3)))
	 {
		 fptr_E3();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_3);
	 }
	 if ((fptr_E4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_4)))
	 {
		 	fptr_E4();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_4);
	 }
	 if ((fptr_E5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_5)))
	 {
		 	fptr_E5();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_5);
	 }
	 if ((fptr_F6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_6)))
	 {
		 	fptr_E6();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_6);
	 }
	 if ((fptr_E7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_E),ENU_PIN_7)))
	 {
		 	fptr_E7();
		 SET_BIT(GPIOICR(ENU_PORT_E),ENU_PIN_7);
	 }
}


void GPIOF_Handler(void) 
{
   if ((fptr_F0!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_0)))
	 {
		 fptr_F0();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_0);
	 }
	 if ((fptr_F1!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_1)))
	 {
		 fptr_F1();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_1);
	 }
	 if ((fptr_F2!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_2)))
	 {
		 fptr_F2();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_2);
	 }
	 if ((fptr_F3!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_3)))
	 {
		 fptr_F3();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_3);
	 }
	 if ((fptr_F4!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_4)))
	 {
		 	fptr_F4();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_4);
	 }
	 if ((fptr_F5!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_5)))
	 {
		 	fptr_F5();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_5);
	 }
	 if ((fptr_F6!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_6)))
	 {
		 	fptr_F6();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_6);
	 }
	 if ((fptr_F7!=NULL_PTR) && (BIT_IS_SET(GPIORIS(ENU_PORT_F),ENU_PIN_7)))
	 {
		 	fptr_F7();
		 SET_BIT(GPIOICR(ENU_PORT_F),ENU_PIN_7);
	 }

}

