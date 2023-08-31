/*
 * gpio_linkConfig.c
 *
 *     Created on: Jun 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Input Output (GPIO) linking configurations implementation.
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
#include "gpio_linkConfig.h"

/*******************************************************************************************************************************************************************/
/* Tiva™ TM4C123GH6PM Pinouts: */
/*    
                                                                                                          S    S
                                                                                                          W	   W
                                                                                                          C	   D
                                                                                                          L    I
                                                                                                          K	   O	 	 SWO
                                                                                          V  			 				/    /      /
                                                                                          D  						 TCK TMS TDI TDO 
                                                                                          C  			  			/   /   /   /
                                                         PD3 PD2 PD1 PD0 PE5 PE4 PB4 PB5  C  GND VDD PD6 PC0 PC1 PC2 PC3
                                                      ----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|----
                                                     |   64  63  62  61  60  59  58  57  56  55  54  53  52  51  50  49    |
                                                PB6 -| 1		                                    												48 |- PB3 / I2C0SDA
                                               VDDA -| 2		                                    												47 |- PB2 / I2C0SCL
                                               GNDA -| 3		                                    												46 |- PB1 / USB0VBUS
                                                PB7	-| 4		                                    												45 |- PB0 / USB0ID
                                                PF4	-| 5		                                    												44 |- PD5
                                                PE3	-| 6		                                    												43 |- PD4
                                                PE2	-| 7		                                    												42 |- VDD
                                                PE1	-| 8		               			 Tiva™ TM4C123GH6PM     								41 |- OSC1
                                                PE0 -| 9		                                    												40 |- OSC0
                                                PD7	-| 10		                                    												39 |- GND
                                                VDD	-| 11		                                    												38 |- RST
                                                GND -| 12		                                    												37 |- VBAT
                                                PC7 -| 13		                                    												36 |- XOSC1
                                                PC6 -| 14		                                    												35 |- GNDX
                                                PC5 -| 15		                                    												34 |- XOSC0
                                                PC4 -| 16 		                                    											33 |- HIB
                                                     |   17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32    |
                                                      ----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|----
                                                         PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7  V  VDD GND PF0 PF1 PF2 PF3 WAKE
                                                          /   /   /   /					 					D
                                                          U   U   S   S					 					C
                                                          0   0   S	  S					 					C
                                                          R   T   I	  I
                                                          x   x   0	  0
                                                                  C   F
                                                                  l   s
                                                                  k   s


                                            Note: For more information about GPIO pins and their alternate functions, see pages 650 & 651.
*/

/*******************************************************************************************************************************************************************/
/* GPIO Global Variables */

/* GPIO Ports Linking Configurations Structure Implementation */
GPIO_stPortLinkConfig_t ast_g_gpioPortsLinkConfig[1] = { { GPIO_EN_PORTF,           // ast_g_gpioPortsLinkConfig[0].en_a_portId
																													 GPIO_EN_APB,             // ast_g_gpioPortsLinkConfig[0].en_a_portBusId
																													 GPIO_EN_RUN_MODE } };    // ast_g_gpioPortsLinkConfig[0].en_a_portMode

/* GPIO Pins Linking Configurations Structure Implementation */
GPIO_stPinLinkConfig_t ast_g_gpioPinsLinkConfig[4] = { { /* Red LED */
																												 GPIO_EN_PORTF,             // ast_g_gpioPinsLinkConfig[0].en_a_portId
																												 GPIO_EN_APB,               // ast_g_gpioPinsLinkConfig[0].en_a_portBusId
																												 GPIO_EN_PIN1,              // ast_g_gpioPinsLinkConfig[0].en_a_pinId
																												 GPIO_EN_ENABLE_PIN,        // ast_g_gpioPinsLinkConfig[0].en_a_pinMode
																												 GPIO_EN_OUTPUT_DIR,        // ast_g_gpioPinsLinkConfig[0].en_a_pinDirection
																												 GPIO_EN_PIN_HIGH,          // ast_g_gpioPinsLinkConfig[0].en_a_pinValue
																												 GPIO_EN_PIN_GPIO_MODE,     // ast_g_gpioPinsLinkConfig[0].en_a_pinAlternateMode
																												 GPIO_EN_8_MA_DRIVE,        // ast_g_gpioPinsLinkConfig[0].en_a_pinDrive
                                                         GPIO_EN_DISABLE_PIN_PAD,   // ast_g_gpioPinsLinkConfig[0].en_a_pinPad
																												 GPIO_EN_DISABLE_INT,       // ast_g_gpioPinsLinkConfig[0].en_a_pinInterruptMode
																												 STD_TYPES_NULL	},          // ast_g_gpioPinsLinkConfig[0].en_a_pinInterruptAcrion
																												 /* Blue LED */
																											 { GPIO_EN_PORTF,             // ast_g_gpioPinsLinkConfig[1].en_a_portId
																											   GPIO_EN_APB,               // ast_g_gpioPinsLinkConfig[1].en_a_portBusId																												 
																											   GPIO_EN_PIN2,              // ast_g_gpioPinsLinkConfig[1].en_a_pinId
																											   GPIO_EN_ENABLE_PIN,        // ast_g_gpioPinsLinkConfig[1].en_a_pinMode
																											   GPIO_EN_OUTPUT_DIR,        // ast_g_gpioPinsLinkConfig[1].en_a_pinDirection
																											   GPIO_EN_PIN_LOW,           // ast_g_gpioPinsLinkConfig[1].en_a_pinValue
																											   GPIO_EN_PIN_GPIO_MODE,     // ast_g_gpioPinsLinkConfig[1].en_a_pinAlternateMode
																											   GPIO_EN_8_MA_DRIVE,        // ast_g_gpioPinsLinkConfig[1].en_a_pinDrive
																												 GPIO_EN_DISABLE_PIN_PAD,   // ast_g_gpioPinsLinkConfig[1].en_a_pinPad
																											   GPIO_EN_DISABLE_INT,       // ast_g_gpioPinsLinkConfig[1].en_a_pinInterruptMode
																											   STD_TYPES_NULL	},          // ast_g_gpioPinsLinkConfig[1].en_a_pinInterruptAcrion
																											   /* Green LED */
																											 { GPIO_EN_PORTF,             // ast_g_gpioPinsLinkConfig[2].en_a_portId
																											   GPIO_EN_APB,               // ast_g_gpioPinsLinkConfig[2].en_a_portBusId																												 
																											   GPIO_EN_PIN3,              // ast_g_gpioPinsLinkConfig[2].en_a_pintId
																											   GPIO_EN_ENABLE_PIN,        // ast_g_gpioPinsLinkConfig[2].en_a_pinode
																											   GPIO_EN_OUTPUT_DIR,        // ast_g_gpioPinsLinkConfig[2].en_a_pinDirection
																											   GPIO_EN_PIN_LOW,           // ast_g_gpioPinsLinkConfig[2].en_a_pinValue
																											   GPIO_EN_PIN_GPIO_MODE,     // ast_g_gpioPinsLinkConfig[2].en_a_pinAlternateMode
																											   GPIO_EN_8_MA_DRIVE,        // ast_g_gpioPinsLinkConfig[2].en_a_pinDrive
																												 GPIO_EN_DISABLE_PIN_PAD,   // ast_g_gpioPinsLinkConfig[2].en_a_pinPad
																											   GPIO_EN_DISABLE_INT,       // ast_g_gpioPinsLinkConfig[2].en_a_pinInterruptMode
																											   STD_TYPES_NULL	},          // ast_g_gpioPinsLinkConfig[2].en_a_pinInterruptAcrion
																											   /* SW1 */
																											 { GPIO_EN_PORTF,             // ast_g_gpioPinsLinkConfig[3].en_a_portId
																											   GPIO_EN_APB,               // ast_g_gpioPinsLinkConfig[3].en_a_portBusId																												 
																											   GPIO_EN_PIN4,              // ast_g_gpioPinsLinkConfig[3].en_a_pintId
																											   GPIO_EN_ENABLE_PIN,        // ast_g_gpioPinsLinkConfig[3].en_a_pinode
																											   GPIO_EN_INPUT_DIR,         // ast_g_gpioPinsLinkConfig[3].en_a_pinDirection
																											   GPIO_EN_PIN_LOW,           // ast_g_gpioPinsLinkConfig[3].en_a_pinValue
																											   GPIO_EN_PIN_GPIO_MODE,     // ast_g_gpioPinsLinkConfig[3].en_a_pinAlternateMode
																											   GPIO_EN_DISABLE_PIN_DRIVE, // ast_g_gpioPinsLinkConfig[3].en_a_pinDrive
																												 GPIO_EN_ENABLE_PULL_UP,    // ast_g_gpioPinsLinkConfig[3].en_a_pinPad
																											   GPIO_EN_DISABLE_INT,       // ast_g_gpioPinsLinkConfig[3].en_a_pinInterruptMode
																											   STD_TYPES_NULL	} };        // ast_g_gpioPinsLinkConfig[3].en_a_pinInterruptAcrion
																							
/*******************************************************************************************************************************************************************/
