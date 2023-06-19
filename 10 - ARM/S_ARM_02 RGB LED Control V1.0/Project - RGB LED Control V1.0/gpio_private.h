/*
 * gpio_private.h
 *
 *     Created on: Jun 10, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Input Output (GPIO) registers' locations and description.
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

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* GPIO Bus Base Macros */

/* The GPIO modules may be accessed via two different memory apertures. The legacy aperture, the
 * Advanced Peripheral Bus (APB), is backwards-compatible with previous devices. The other aperture,
 * the Advanced High-Performance Bus (AHB), offers the same register map but provides better
 * back-to-back access performance than the APB bus. These apertures are mutually exclusive.
 */
 
/*
 * GPIO Advanced Peripheral Bus (APB) Base
 *
 * The offset listed is a hexadecimal increment to the register's address,
 * relative to that GPIO port's base address:
 */
/* GPIO Port A (APB): 0x4000.4000
 * GPIO Port B (APB): 0x4000.5000
 * GPIO Port C (APB): 0x4000.6000
 * GPIO Port D (APB): 0x4000.7000
 * GPIO Port E (APB): 0x4002.4000
 * GPIO Port F (APB): 0x4002.5000
 */
#define GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID )     ( GPIO_U8_PORT_ID < GPIO_EN_PORTD ? ( 0x40004000 + ( ( GPIO_U8_PORT_ID ) * 0x1000 ) ) : ( 0x40024000 + ( ( GPIO_U8_PORT_ID - 4 ) * 0x1000 ) ) )

/*
 * GPIO Advanced High-Performance Bus (AHB) Base
 *
 * The offset listed is a hexadecimal increment to the register's address,
 * relative to that GPIO port's base address:
 */
/* GPIO Port A (AHB): 0x4005.8000
 * GPIO Port B (AHB): 0x4005.9000
 * GPIO Port C (AHB): 0x4005.A000
 * GPIO Port D (AHB): 0x4005.B000
 * GPIO Port E (AHB): 0x4005.C000
 * GPIO Port F (AHB): 0x4005.D000
 */
#define GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID )     ( 0x40058000 + ( ( GPIO_U8_PORT_ID ) * 0x1000 ) ) 

/*******************************************************************************************************************************************************************/
/* GPIO Registers' Locations */

#define GPIO_U32_GPIODATA_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x3FC ) )   // GPIO Data
#define GPIO_U32_GPIODIR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x400 ) )   // GPIO Direction

#define GPIO_U32_GPIOIS_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )              *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x404 ) )   // GPIO Interrupt Sense
#define GPIO_U32_GPIOIBE_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x408 ) )   // GPIO Interrupt Both Edges
#define GPIO_U32_GPIOIEV_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x40C ) )   // GPIO Interrupt Event
#define GPIO_U32_GPIOIM_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )              *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x410 ) )   // GPIO Interrupt Mask
#define GPIO_U32_GPIORIS_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x414 ) )   // GPIO Raw Interrupt Status
#define GPIO_U32_GPIOMIS_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x418 ) )   // GPIO Masked Interrupt Status
#define GPIO_U32_GPIOICR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x41C ) )   // GPIO Interrupt Clear

#define GPIO_U32_GPIOAFSEL_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )           *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x420 ) )   // GPIO Alternate Function Select

#define GPIO_U32_GPIODR2R_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x500 ) )   // GPIO 2-mA Drive Select
#define GPIO_U32_GPIODR4R_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x504 ) )   // GPIO 4-mA Drive Select
#define GPIO_U32_GPIODR8R_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x508 ) )   // GPIO 8-mA Drive Select

#define GPIO_U32_GPIOODR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x50C ) )   // GPIO Open Drain Select
#define GPIO_U32_GPIOPUR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x510 ) )   // GPIO Pull-Up Select
#define GPIO_U32_GPIOPDR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x514 ) )   // GPIO Pull-Down Select
#define GPIO_U32_GPIOSLR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x518 ) )   // GPIO Slew Rate Control Select

#define GPIO_U32_GPIODEN_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )             *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x51C ) )   // GPIO Digital Enable
#define GPIO_U32_GPIOLOCK_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x520 ) )   // GPIO Lock
#define GPIO_U32_GPIOCR_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )              *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x524 ) )   // GPIO Commit
#define GPIO_U32_GPIOAMSEL_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )           *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x528 ) )   // GPIO Analog Mode Select

#define GPIO_U32_GPIOPCTL_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )            *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x52C ) )   // GPIO Port Control
#define GPIO_U32_GPIOADCCTL_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )          *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x530 ) )   // GPIO ADC Control 
#define GPIO_U32_GPIODMACTL_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )          *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0x534 ) )   // GPIO DMA Control 

#define GPIO_U32_GPIOPERIPHID4_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFD0 ) )   // GPIO Peripheral Identification 4
#define GPIO_U32_GPIOPERIPHID5_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFD4 ) )   // GPIO Peripheral Identification 5
#define GPIO_U32_GPIOPERIPHID6_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFD8 ) )   // GPIO Peripheral Identification 6
#define GPIO_U32_GPIOPERIPHID7_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFDC ) )   // GPIO Peripheral Identification 7
#define GPIO_U32_GPIOPERIPHID0_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFE0 ) )   // GPIO Peripheral Identification 0
#define GPIO_U32_GPIOPERIPHID1_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFE4 ) )   // GPIO Peripheral Identification 1
#define GPIO_U32_GPIOPERIPHID2_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFE8 ) )   // GPIO Peripheral Identification 2
#define GPIO_U32_GPIOPERIPHID3_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )       *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFEC ) )   // GPIO Peripheral Identification 3

#define GPIO_U32_GPIOPCELLID0_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )        *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFF0 ) )   // GPIO PrimeCell Identification 0
#define GPIO_U32_GPIOPCELLID1_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )        *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFF4 ) )   // GPIO PrimeCell Identification 1
#define GPIO_U32_GPIOPCELLID2_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )        *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFF8 ) )   // GPIO PrimeCell Identification 2
#define GPIO_U32_GPIOPCELLID3_REG( GPIO_U8_BUS_ID, GPIO_U8_PORT_ID )        *( ( volatile  u32 * ) ( ( GPIO_U8_BUS_ID == GPIO_EN_APB ? GPIO_U32_GPIOAPB_BASE( GPIO_U8_PORT_ID ) : GPIO_U32_GPIOAHB_BASE( GPIO_U8_PORT_ID ) ) + 0xFFC ) )   // GPIO PrimeCell Identification 3

#define GPIO_U32_GPIOHBCTL_REG                                              *( ( volatile  u32 * ) 0x400FE06C )                                                                                                                            // GPIO High-Performance Bus Control
#define GPIO_U32_RCGCGPIO_REG                                               *( ( volatile  u32 * ) 0x400FE608 )                                                                                                                            // General-Purpose Input/Output Run Mode Clock Gating Control
#define GPIO_U32_SCGCGPIO_REG                                               *( ( volatile  u32 * ) 0x400FE708 )                                                                                                                            // General-Purpose Input/Output Sleep Mode Clock Gating Control
#define GPIO_U32_DCGCGPIO_REG                                               *( ( volatile  u32 * ) 0x400FE808 )                                                                                                                            // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control

/*******************************************************************************************************************************************************************/
/* GPIO Registers' Description */

/* GPIO High-Performance Bus Control - GPIOHBCTL */
/* Bit 5 - PORTF: Port F Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTF_BIT           5

/* Bit 4 - PORTE: Port E Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTE_BIT           4

/* Bit 3 - PORTF: Port D Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTD_BIT           3

/* Bit 2 - PORTF: Port C Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTC_BIT           2

/* Bit 1 - PORTF: Port B Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTB_BIT           1

/* Bit 0 - PORTF: Port A Advanced High-Performance Bus */
/* Value Description:
 * 	 0 	 Advanced Peripheral Bus (APB). This bus is the legacy bus.
 * 	 1 	 Advanced High-Performance Bus (AHB)
 */
#define GPIO_U8_PORTA_BIT           0
/* End of GPIOHBCTL Register */

/*************************************************************************/

/* General-Purpose Input/Output Run Mode Clock Gating Control - RCGCGPIO */
/* Bit 5 - R5: GPIO Port F Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port F is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port F in Run mode.
 */
#define GPIO_U8_R5_BIT              5

/* Bit 4 - R4: GPIO Port E Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port E is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port E in Run mode.
 */
#define GPIO_U8_R4_BIT              4

/* Bit 3 - R3: GPIO Port D Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port D is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port D in Run mode.
 */
#define GPIO_U8_R3_BIT              3

/* Bit 2 - R2: GPIO Port C Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port C is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port C in Run mode.
 */
#define GPIO_U8_R2_BIT              2

/* Bit 1 - R1: GPIO Port B Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port B is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port B in Run mode.
 */
#define GPIO_U8_R1_BIT              1

/* Bit 0 - R0: GPIO Port A Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port A is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port A in Run mode.
 */
#define GPIO_U8_R0_BIT              0
/* End of RCGCGPIO Register */

/*************************************************************************/

/* General-Purpose Input/Output Sleep Mode Clock Gating Control - SCGCGPIO */
/* Bit 5 - S5: GPIO Port F Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port F is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port F in Sleep mode.
 */
#define GPIO_U8_S5_BIT              5

/* Bit 4 - S4: GPIO Port E Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port E is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port E in Sleep mode.
 */
#define GPIO_U8_S4_BIT              4

/* Bit 3 - S3: GPIO Port D Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port D is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port D in Sleep mode.
 */
#define GPIO_U8_S3_BIT              3

/* Bit 2 - S2: GPIO Port C Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port C is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port C in Sleep mode.
 */
#define GPIO_U8_S2_BIT              2

/* Bit 1 - S1: GPIO Port B Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port B is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port B in Sleep mode.
 */
#define GPIO_U8_S1_BIT              1

/* Bit 0 - S0: GPIO Port A Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port A is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port A in Sleep mode.
 */
#define GPIO_U8_S0_BIT              0
/* End of SCGCGPIO Register */

/*************************************************************************/

/* General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control - DCGCGPIO */
/* Bit 5 - D5: GPIO Port F Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port F is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port F in Deep-Sleep mode.
 */
#define GPIO_U8_D5_BIT              5

/* Bit 4 - D4: GPIO Port E Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port E is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port E in Deep-Sleep mode.
 */
#define GPIO_U8_D4_BIT              4

/* Bit 3 - D3: GPIO Port D Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port D is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port D in Deep-Sleep mode.
 */
#define GPIO_U8_D3_BIT              3

/* Bit 2 - D2: GPIO Port C Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port C is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port C in Deep-Sleep mode.
 */
#define GPIO_U8_D2_BIT              2

/* Bit 1 - D1: GPIO Port B Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port B is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port B in Deep-Sleep mode.
 */
#define GPIO_U8_D1_BIT              1

/* Bit 0 - D0: GPIO Port A Deep-Sleep Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 GPIO Port A is disabled.
 * 	 1 	 Enable and provide a clock to GPIO Port A in Deep-Sleep mode.
 */
#define GPIO_U8_D0_BIT              0
/* End of DCGCGPIO Register */

/*******************************************************************************************************************************************************************/

#endif /* GPIO_PRIVATE_H_ */
