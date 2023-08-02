/*
 * TIMER_Program.c
 *
 *     Created on: Apr 19, 2023
 *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
 *    Description: This file contains all temperature sensor functions' implementation.
 *		MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
#include "temp_sensor.h"

/*define global variable*/

void TEMPSENSOR_init(void)
{
	ADC_initialization();
	//u8 u8_l_errorState = DIO_init( TEMPSENSOR_CHANNEL, TEMPSENSOR_PORT, DIO_IN);
}

/************************************************************************
 The output scale factor of the LM35 is 10 mV/°C and it 
provides an output voltage of 250 mV at 25°C .                          
************************************************************************/

void TEMPSENSOR_getValue(u16 *u16_g_lmTemperatureVal)
{
	 u16 u16_a_adcValue=0;
	 ADC_startConversion(TEMPSENSOR_CHANNEL);
	 ADC_getDigitalValue( ADC_U8_POLLING_MODE, &u16_a_adcValue );
	u16 u16_l_adcGetInputVoltage = 0;
		// get the output voltage from the LM35 sensor
	u16_l_adcGetInputVoltage =  ( (u16_a_adcValue * ADC_INT_REF_Voltage ) / ADC_RESOLUTION ) ;
		// mapping the output voltage into temperature degree according to the scale factor of the LM35 sensor
	*u16_g_lmTemperatureVal = (u16) ( u16_l_adcGetInputVoltage  / LM35_SCALE_FACTOR );
}