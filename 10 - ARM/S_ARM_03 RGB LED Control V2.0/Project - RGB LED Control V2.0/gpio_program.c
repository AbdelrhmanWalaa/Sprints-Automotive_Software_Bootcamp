/*
 * gpio_program.c
 *
 *     Created on: Jun 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Input Output (GPIO) functions' implementation and IRQ handlers implementation.
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

/* MCAL */
#include "gpio_interface.h"
#include "gpio_private.h"

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_initalization
 Input: Pointer to Array of st PortLinkConfig and u8 NumberOfPorts
 Output: en Error or No Error
 Description: Function to initialize GPIO Port peripheral using Linking Configurations.
*/
GPIO_enErrorState_t GPIO_initalization( const GPIO_stPortLinkConfig_t *past_a_portsLinkConfig, u8 u8_a_numberOfPorts )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Define local variable to set the index value = 0. */
	u8 u8_l_index = 0;
	
	/* Check 1: Pointer is not equal to NULL, and NumberOfPorts is in the valid range. */
	if ( ( past_a_portsLinkConfig != STD_TYPES_NULL ) 					&&
			 ( u8_a_numberOfPorts < GPIO_EN_INVALID_PORT_ID ) )
	{
		/* Loop: Until initializing all Ports passed. */
		for ( u8_l_index = 0; u8_l_index < u8_a_numberOfPorts; u8_l_index++ )
		{
			/* Check 1.1: PortId, PortBusId, and PortMode are in the valid range. */
			if ( ( past_a_portsLinkConfig[u8_l_index].en_a_portId < GPIO_EN_INVALID_PORT_ID )        &&
					 ( past_a_portsLinkConfig[u8_l_index].en_a_portBusId < GPIO_EN_INVALID_BUS_ID )      &&
					 ( past_a_portsLinkConfig[u8_l_index].en_a_portMode < GPIO_EN_INVALID_PORT_MODE ) )
			{
				/* Check 1.1: Required PortId. */
				switch ( past_a_portsLinkConfig[u8_l_index].en_a_portId )
				{
					case GPIO_EN_PORTA:
					{
						/* Check 1.1.1: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portBusId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTA_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTA_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.2: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R0_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S0_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D0_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					case GPIO_EN_PORTB:
					{
						/* Check 1.1.3: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portBusId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTB_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTB_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.4: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R1_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S1_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D1_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					case GPIO_EN_PORTC:
					{
						/* Check 1.1.5: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTC_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTC_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.6: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R2_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S2_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D2_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					case GPIO_EN_PORTD:
					{
						/* Check 1.1.7: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTD_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTD_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.8: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R3_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S3_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D3_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					case GPIO_EN_PORTE:
					{
						/* Check 1.1.9: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTE_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTE_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.10: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R4_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S4_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D4_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					case GPIO_EN_PORTF:
					{
						/* Check 1.1.11: Required PortBusId. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portId )
						{
							case GPIO_EN_APB: CLR_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTF_BIT ); break;
							case GPIO_EN_AHB: SET_BIT( GPIO_U32_GPIOHBCTL_REG, GPIO_U8_PORTF_BIT ); break;
							default:                     /* Do Nothing. */                          break;
						}
						
						/* Check 1.1.12: Required PortMode. */
						switch ( past_a_portsLinkConfig[u8_l_index].en_a_portMode )
						{
							case GPIO_EN_RUN_MODE       : SET_BIT( GPIO_U32_RCGCGPIO_REG, GPIO_U8_R5_BIT ); break;
							case GPIO_EN_SLEEP_MODE     : SET_BIT( GPIO_U32_SCGCGPIO_REG, GPIO_U8_S5_BIT ); break;
							case GPIO_EN_DEEP_SLEEP_MODE: SET_BIT( GPIO_U32_DCGCGPIO_REG, GPIO_U8_D5_BIT ); break;
							default:                             /* Do Nothing. */                          break;
						}
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
			}		
			/* Check 1.2: PortId, PortBusId, or PortMode is not in the valid range. */
			else
			{
				/* Update error state = NOK, Wrong PortId, PortBusId, or PortMode! */
				en_l_errorState = GPIO_EN_NOK;
				
				break;
			}
		}
	}
	/* Check 2: Pointer is equal to NULL, or NumberOfPorts is not in the valid range. */
	else
	{
		/* Update error state = NOK, Pointer is NULL, or Wrong NumberOfPorts! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;
}	

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_configurePin
 Input: Pointer to Array of st PinLinkConfig and u8 NumberOfPins
 Output: en Error or No Error
 Description: Function to configure GPIO Pin peripheral using Linking Configurations.
*/
GPIO_enErrorState_t GPIO_configurePin( const GPIO_stPinLinkConfig_t *past_a_pinsLinkConfig, u8 u8_a_numberOfPins )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Define local variable to set the index value = 0. */
	u8 u8_l_index = 0;
	
	/* Check 1: Pointer is not equal to NULL, and NumberOfPins is in the valid range. */
	if ( ( past_a_pinsLinkConfig != STD_TYPES_NULL ) 				&&
			 ( u8_a_numberOfPins < 43 ) )
	{
		/* Loop: Until configuring all Pins passed. */
		for ( u8_l_index = 0; u8_l_index < u8_a_numberOfPins; u8_l_index++ )
		{
			/* Check 1.1: PortId, PortBusId, PinId, PinMode, PinDirection, PinValue, PinAlternateMode, PinDrive, PinPad, and PinInterruptMode are in the valid range. */
			if ( ( past_a_pinsLinkConfig[u8_l_index].en_a_portId < GPIO_EN_INVALID_PORT_ID )                  &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId < GPIO_EN_INVALID_BUS_ID )                &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinId < GPIO_EN_INVALID_PIN_ID )                    &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinMode < GPIO_EN_INVALID_PIN_MODE )                &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinDirection < GPIO_EN_INVALID_PIN_DIR )            &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinValue < GPIO_EN_INVALID_PIN_VALUE )              &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinAlternateMode < GPIO_EN_INVALID_PIN_ALT_MODE )   &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinDrive < GPIO_EN_INVALID_PIN_DRIVE )              &&
			     ( past_a_pinsLinkConfig[u8_l_index].en_a_pinPad < GPIO_EN_INVALID_PIN_PAD )                  &&
					 ( past_a_pinsLinkConfig[u8_l_index].en_a_pinInterruptMode < GPIO_EN_INVALID_PIN_INT_MODE ) )
			{
				/* Step 1: Set the direction of the GPIO port pins by programming the GPIODIR register. */
				/* Check 1.1.1: Required PinDirection. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinDirection )
				{
					case GPIO_EN_INPUT_DIR : CLR_BIT( GPIO_U32_GPIODIR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId ); break;
					case GPIO_EN_OUTPUT_DIR: SET_BIT( GPIO_U32_GPIODIR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId ); break;
					default:                                                         						                            /* Do Nothing. */					                                                                         break;
				}
				
				/* Step 2: Set the value of the GPIO port pins by programming the GPIODATA register. */
				/* Check 1.1.2: Required PinValue. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinValue )
				{					
					case GPIO_EN_PIN_LOW : CLR_BIT( GPIO_U32_GPIODATA_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId ); break;
					case GPIO_EN_PIN_HIGH: SET_BIT( GPIO_U32_GPIODATA_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId ); break;
					default:                                                                                      /* Do Nothing. */                                                                                           break;
				}
				
				/* Step 3: Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. */
				/* Check 1.1.3: Required PinAlternateMode. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinAlternateMode )
				{
					case GPIO_EN_PIN_GPIO_MODE: CLR_BIT( GPIO_U32_GPIOAFSEL_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId); break;
					case GPIO_EN_PIN_ALT_MODE : SET_BIT( GPIO_U32_GPIOAFSEL_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId); break;
					default:                                                                                      /* Do Nothing. */                                                                                                break;
				}
				
				/* Step 4: Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8 registers. */
				/* Check 1.1.4: Required PinDrive. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinDrive )
				{
					case GPIO_EN_DISABLE_PIN_DRIVE:
					{
						CLR_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						CLR_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						CLR_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						break;
					}
					
					case GPIO_EN_2_MA_DRIVE:
					{
						SET_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId);
						break;
					}
					
					case GPIO_EN_4_MA_DRIVE:
					{
						SET_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId);
						break;
					}
					
					case GPIO_EN_8_MA_DRIVE:
					{
						SET_BIT( GPIO_U32_GPIODR2R_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId);
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
				
				/* Step 5: Program each pad in the port to have either pull-up, pull-down, or open drain functionality through the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed, through the GPIOSLR register. */
				/* Check 1.1.5: Required PinPad. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinPad )
				{
					case GPIO_EN_DISABLE_PIN_PAD:
					{
						CLR_BIT( GPIO_U32_GPIOPUR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						CLR_BIT( GPIO_U32_GPIOPDR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						CLR_BIT( GPIO_U32_GPIOODR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						break;
					}
					
					case GPIO_EN_ENABLE_PULL_UP:
					{
						SET_BIT( GPIO_U32_GPIOPUR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						break;
					}
					
					case GPIO_EN_ENABLE_PULL_DOWN:
					{
						SET_BIT( GPIO_U32_GPIOPDR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						break;
					}
					
					case GPIO_EN_ENABLE_OPEN_DRAIN:
					{
						SET_BIT( GPIO_U32_GPIOODR_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId );
						break;
					}
					
					default:
					{
						/* Do Nothing. */
						break;
					}
				}
				
				/* Step 6: Enable GPIO pins as digital I/Os, by setting the appropriate DEN bit in the GPIODEN register. */
				/* Check 1.1.6: Required PinMode. */
				switch ( past_a_pinsLinkConfig[u8_l_index].en_a_pinMode )
				{
					case GPIO_EN_DISABLE_PIN: CLR_BIT( GPIO_U32_GPIODEN_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId); break;
					case GPIO_EN_ENABLE_PIN : SET_BIT( GPIO_U32_GPIODEN_REG( past_a_pinsLinkConfig[u8_l_index].en_a_portBusId, past_a_pinsLinkConfig[u8_l_index].en_a_portId ), past_a_pinsLinkConfig[u8_l_index].en_a_pinId); break;
					default:                                                                                   /* Do Nothing. */ 																																												       break;
				}
				
				/* Step 7: Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event, and mask of the interrupts for each port. */
				/* Future Improvements */
				
			}
			/* Check 1.2: PortId, PortBusId, PinId, PinMode, PinDirection, PinValue, PinAlternateMode, PinDrive, PinPad, or PinInterruptMode is not in the valid range. */
			else
			{
				/* Update error state = NOK, Wrong PortId, PortBusId, PinId, PinMode, PinDirection, PinValue, PinAlternateMode, PinDriveSelect, PinPad, or PinInterruptMode! */
				en_l_errorState = GPIO_EN_NOK;
				
				break;
			}	
		}
	}
	/* Check 2: Pointer is equal to NULL, or NumberOfPorts is not in the valid range. */
	else
	{
		/* Update error state = NOK, Pointer is NULL, or Wrong NumberOfPorts! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;
}	

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_setPinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to set Pin value.
*/
GPIO_enErrorState_t GPIO_setPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Check 1: PortId, BusId and PinId are in the valid range. */
	if ( ( en_a_portId < GPIO_EN_INVALID_PORT_ID )       &&
			 ( en_a_busId < GPIO_EN_INVALID_BUS_ID )         &&
			 ( en_a_pinId < GPIO_EN_INVALID_PIN_ID ) )
	{
		SET_BIT( GPIO_U32_GPIODATA_REG( en_a_busId, en_a_portId ), en_a_pinId );
	}
	/* Check 2: PortId, BusId, or PinId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong PortId, BusId, or PinId! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_getPinValue
 Input: en PortId, en BusId, en PinId, and Pointer to en ReturnedPinValue
 Output: en Error or No Error
 Description: Function to get Pin value.
*/
GPIO_enErrorState_t GPIO_getPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, GPIO_enPinValue_t *pen_a_returnedPinValue )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Check 1: PortId, BusId and PinId are in the valid range, and Pointer is not equal to NULL. */
	if ( ( en_a_portId < GPIO_EN_INVALID_PORT_ID )       &&
			 ( en_a_busId < GPIO_EN_INVALID_BUS_ID )         &&
			 ( en_a_pinId < GPIO_EN_INVALID_PIN_ID )         &&
			 ( pen_a_returnedPinValue != STD_TYPES_NULL ) )
	{
		*pen_a_returnedPinValue = ( GPIO_enPinValue_t ) GET_BIT( GPIO_U32_GPIODATA_REG( en_a_busId, en_a_portId ), en_a_pinId );
	}
	/* Check 2: PortId, BusId, or PinId is not in the valid range, or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong PortId, BusId, or PinId, or Pointer is NULL! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;	
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_clearPinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to clear Pin value.
*/
GPIO_enErrorState_t GPIO_clearPinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Check 1: PortId, BusId and PinId are in the valid range. */
	if ( ( en_a_portId < GPIO_EN_INVALID_PORT_ID )       &&
			 ( en_a_busId < GPIO_EN_INVALID_BUS_ID )         &&
			 ( en_a_pinId < GPIO_EN_INVALID_PIN_ID ) )
	{
		CLR_BIT( GPIO_U32_GPIODATA_REG( en_a_busId, en_a_portId ), en_a_pinId );
	}
	/* Check 2: PortId, BusId, or PinId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong PortId, BusId, or PinId! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_togglePinValue
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to toggle Pin value.
*/
GPIO_enErrorState_t GPIO_togglePinValue( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Check 1: PortId, BusId and PinId are in the valid range. */
	if ( ( en_a_portId < GPIO_EN_INVALID_PORT_ID )       &&
			 ( en_a_busId < GPIO_EN_INVALID_BUS_ID )         &&
			 ( en_a_pinId < GPIO_EN_INVALID_PIN_ID ) )
	{
		TOG_BIT( GPIO_U32_GPIODATA_REG( en_a_busId, en_a_portId ), en_a_pinId );
	}
	/* Check 2: PortId, BusId, or PinId is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong PortId, BusId, or PinId! */
		en_l_errorState = GPIO_EN_NOK;
	}
	
	return en_l_errorState;
}	

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_enableInterrupt
 Input: en PortId, en BusId, en PinId, and u8 SenseControl
 Output: en Error or No Error
 Description: Function to enable GPIO Interrupt.
*/
GPIO_enErrorState_t GPIO_enableInterrupt( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, u8 u8_a_senseControl )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Future Improvements */
	
	return en_l_errorState;
}	

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_disableInterrupt
 Input: en PortId, en BusId, and en PinId
 Output: en Error or No Error
 Description: Function to disable GPIO Interrupt.
*/
GPIO_enErrorState_t GPIO_disableInterrupt( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Future Improvements */
	
	return en_l_errorState;
}	

/*******************************************************************************************************************************************************************/
/*
 Name: GPIO_setCallback
 Input: en PortId, en BusId, en PinId, and Pointer to Function that takes void and returns void
 Output: en Error or No Error
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function of the passed Pin ( PinId ),
							the address is passed through a pointer to function ( PinInterruptAction ), and then pass this address to IRQ function.
*/
GPIO_enErrorState_t GPIO_setCallback( GPIO_enPortId_t en_a_portId, GPIO_enPortBusId_t en_a_busId, GPIO_enPinId_t en_a_pinId, void ( *vpf_a_pinInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK. */
	GPIO_enErrorState_t en_l_errorState = GPIO_EN_OK;
	
	/* Future Improvements */
	
	return en_l_errorState;
}	
/*******************************************************************************************************************************************************************/
