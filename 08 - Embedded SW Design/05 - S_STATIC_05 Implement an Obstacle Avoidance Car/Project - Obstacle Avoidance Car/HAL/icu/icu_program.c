/*
 * ICU_interface.c
 *
 * Created: 2023-05-19 6:56:29 PM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "icu_interface.h"
/*============= GLOBAL VARIBALE =============*/
static EN_ICU_EdgeType EN_g_edge;
static EN_ICU_Source EN_g_source;

/*============= FUNCTION PROTOTYPE =============*/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the External Interrupt source.
 * 	4. Initialize Timer1 Registers
 */
EN_state ICU_init(const ST_ICU_ConfigType * Config_Ptr)
{
	if(Config_Ptr != NULL)
	{
		ST_TME1_ConfigType ST_L_Timer;
		ST_L_Timer.CLK_source=Config_Ptr->clock;
		ST_L_Timer.TMR_mode=Normal;
		ST_L_Timer.INT_state=Disable;
		TMR1_init(&ST_L_Timer);
		EXI_enablePIE(Config_Ptr->source,Config_Ptr->edge);
		EN_g_edge=Config_Ptr->edge;
		EN_g_source=Config_Ptr->source;
		return valid;
	}
	return invalid;
}

/*
 * Description: Function to set the Call Back function address.
 */
EN_state ICU_setCallBack(void(*a_ptr)(void))
{
	if(a_ptr != NULL)
	{
		EXI_intSetCallBack(EN_g_source,a_ptr);
		return valid;
	}
	return invalid;
}

/*
 * Description: Function to set the required edge detection.
 */
EN_state ICU_setEdgeDetectionType(const EN_ICU_EdgeType edgeType)
{
	EN_state en_l_state;
		if(edgeType==RISING)
		{
			EXI_enablePIE(EN_g_source,EXI_U8_SENSE_RISING_EDGE);
			en_l_state=valid;
		}
		else if(edgeType==FALLING)
		{
			EXI_enablePIE(EN_g_source,EXI_U8_SENSE_FALLING_EDGE);
			en_l_state=valid;
		}
		else
			en_l_state=invalid;
			
		return en_l_state;
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
u16 ICU_getInputCaptureValue(void)
{
	return TMR1_readTime();
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TMR1_clear();
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	EXI_disablePIE(EN_g_source);
	TMR1_stop();
}