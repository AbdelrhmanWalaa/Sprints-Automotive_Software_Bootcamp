/*
 * gpio_interface.h
 *
 *     Created on: Jun 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Input Output (GPIO) functions' prototypes, link configurations, and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: Tiva™ TM4C123GH6PM - https://www.ti.com/lit/pdf/spms376
 *	    Copyright: MIT License
 *
 *	               Copyright (c) Abdelrhman Walaa
 *
 *	               Permission is hereby granted, free of charge, to any person obtaining a copy
 *	               of this software and associated documentation files (the "Software"), to deal
 *	               in the Software without restriction, including without limitation the rights
 *	               to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	               copies of the Software, and to permit persons to whom the Software is
 *	               furnished to do so, subject to the following conditions:
 *
 *	               The above copyright notice and this permission notice shall be included in all
 *	               copies or substantial portions of the Software.
 *
 *	               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	               IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	               FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	               AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	               LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	               SOFTWARE.
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* GPIO Includes */

/* STD LIB */
#include "TM4C123.h"

/* LIB */
#include "std_types.h"
#include "bit_math.h"

/* MCAL */
#include "gpio_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* GPIO Error States */

typedef enum
{
	GPIO_EN_NOK = 0, 
	GPIO_EN_OK
	
} GPIO_enErrorState_t;

/*******************************************************************************************************************************************************************/
/* GPIO Functions' Prototypes */

/*
 Name: GPIO_initalization
 Input: Pointer to Array of st PortLinkConfig and u8 NumberOfPorts
 Output: en Error or No Error
 Description: Function to initialize GPIO Port peripheral using Linking Configurations.
*/
extern GPIO_enErrorState_t GPIO_initalization( const GPIO_stPortLinkConfig_t *past_a_portsLinkConfig, u8 u8_a_numberOfPorts );

/*
 Name: GPIO_configurePin
 Input: Pointer to Array of st PinLinkConfig and u8 NumberOfPins
 Output: en Error or No Error
 Description: Function to configure GPIO Pin peripheral using Linking Configurations.
*/
extern GPIO_enErrorState_t GPIO_configurePin( const GPIO_stPinLinkConfig_t *past_a_pinsLinkConfig, u8 u8_a_numberOfPins );

/*
 Name: GPIO_setPinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to set Pin value.
*/
extern GPIO_enErrorState_t GPIO_setPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId );

/*
 Name: GPIO_getPinValue
 Input: en PortId, en BusId, en PinId, and Pointer to en ReturnedPinValue
 Output: en Error or No Error
 Description: Function to get Pin value.
*/
extern GPIO_enErrorState_t GPIO_getPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, GPIO_enPinValue_t *pen_a_returnedPinValue );

/*
 Name: GPIO_clearPinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to clear Pin value.
*/
extern GPIO_enErrorState_t GPIO_clearPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId );
	
/*
 Name: GPIO_togglePinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to toggle Pin value.
*/
extern GPIO_enErrorState_t GPIO_togglePinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId );

/*
 Name: GPIO_enableInterrupt
 Input: en PortId, en BusId, en PinId, and u8 SenseControl
 Output: en Error or No Error
 Description: Function to enable Interrupt.
*/
extern GPIO_enErrorState_t GPIO_enableInterrupt( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, u8 u8_a_senseControl );

/*
 Name: GPIO_disableInterrupt
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to disable Interrupt.
*/
extern GPIO_enErrorState_t GPIO_disableInterrupt( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId );

/*
 Name: GPIO_setCallback
 Input: en PortId, en BusId, en PinId, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in IRQ function of the passed Pin ( PinId ),
							the address is passed through a pointer to function ( InterruptAction ), and then pass this address to IRQ function.
*/
extern GPIO_enErrorState_t GPIO_setCallback( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, void ( *vpf_a_interruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* GPIO_INTERFACE_H_ */
