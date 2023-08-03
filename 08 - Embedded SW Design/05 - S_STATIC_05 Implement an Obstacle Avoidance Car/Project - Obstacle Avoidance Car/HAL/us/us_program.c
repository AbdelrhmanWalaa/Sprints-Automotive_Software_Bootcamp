/*
 * US_Interface.c
 *
 * Created: 2023-05-20 3:39:37 AM
 *  Author: HAZEM-PC
 */ 
/*============= FILE INCLUSION =============*/
#include "us_interface.h"
#include "../../MCAL/tmr0/tmr0_interface.h"
/*============= MACRO DEFINITION =============*/


/*============= GLOBAL STATIC VARIABLES =============*/
static u8 u8_g_edgeCount = 0;		//to count number of edges
static u16 u16_g_timeHigh = 0;		//to hold time of generated pulse
static u8 u8_g_triggerPort;			//to hold trigger port id
static u8 u8_g_triggerPin;			//to hold trigger pin id

/*============= FUNCTION DEFINITION =============*/

void US_edgeProcessing(void)
{
	u8_g_edgeCount++;
	if(u8_g_edgeCount==1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(u8_g_edgeCount==2)
	{
		u16_g_timeHigh=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RISING);
	}
}

/*
 * Description : Function to initialize the ultrasonic driver
 * 1-initialize ICU driver
 * 2-set callback function
 * 3-setup trigger pin direction as output
 * 4-setup External interrupt source
 Inputs:
  u8 a_triggerPort:trigger port 
  a_triggerPin:trigger pin
  en_a_echoPin: interrupt source pin [EN_INT0,EN_INT1,EN_INT2]
 */
EN_state US_init(u8 a_triggerPort,u8 a_triggerPin,EN_ICU_Source en_a_echoPin)
{
	if(a_triggerPin <= P7 && a_triggerPin >= P0 && a_triggerPort >= A && a_triggerPort <= D && en_a_echoPin < MAX_INT)
	{
		ST_ICU_ConfigType ST_L_IcuConfig={F_CPU_8,RISING,en_a_echoPin};
		u8_g_triggerPort=a_triggerPort;
		u8_g_triggerPin=a_triggerPin;
		ICU_init(&ST_L_IcuConfig);
		ICU_setCallBack(US_edgeProcessing);
		DIO_init(a_triggerPort, a_triggerPin, OUT);		 //setup trigger pin direction as output
		DIO_write(a_triggerPort, a_triggerPin, LOW);
		return valid;
	}
	return invalid;
}


void US_Trigger(void)
{
	DIO_write(u8_g_triggerPort, u8_g_triggerPin,HIGH);
	//_delay_us(10);
	TMR0_delayMS(1);
	DIO_write(u8_g_triggerPort, u8_g_triggerPin,LOW);
}

u16 US_readDistance(void)
{
	u16 u16_L_value=0;
	US_Trigger();
	while(u8_g_edgeCount != 2);   //wait until ultrasonic sound to travel towards the object and return.
	u16_L_value=((u16)u16_g_timeHigh/58);
	u8_g_edgeCount=0;            //clear edge count to be ready for new read
	return u16_L_value;
}
