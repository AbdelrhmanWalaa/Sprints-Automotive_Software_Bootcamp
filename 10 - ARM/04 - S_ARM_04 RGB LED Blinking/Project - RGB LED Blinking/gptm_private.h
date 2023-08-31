/*
 * gptm_private.h
 *
 *     Created on: Jun 20, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all General Purpose Timers (GPTM) registers' locations and description.
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

#ifndef GPTM_PRIVATE_H_
#define GPTM_PRIVATE_H_

/*******************************************************************************************************************************************************************/
/* GPTM Base Address Macro */

/* 
 * The offset listed is a hexadecimal increment to the register's address,
 * relative to that timer's base address:
 */
/* 16/32-bit Timer 0:      0x4003.0000
 * 16/32-bit Timer 1:      0x4003.1000
 * 16/32-bit Timer 2:      0x4003.2000
 * 16/32-bit Timer 3:      0x4003.3000
 * 16/32-bit Timer 4:      0x4003.4000
 * 16/32-bit Timer 5:      0x4003.5000
 * 32/64-bit Wide Timer 0: 0x4003.6000
 * 32/64-bit Wide Timer 1: 0x4003.7000
 * 32/64-bit Wide Timer 2: 0x4004.C000
 * 32/64-bit Wide Timer 3: 0x4004.D000
 * 32/64-bit Wide Timer 4: 0x4004.E000
 * 32/64-bit Wide Timer 5: 0x4004.F000
 */
#define GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID )     	( GPTM_U8_TIMER_ID < GPTM_EN_WIDE_TIMER_2 ? ( ( 0x40030000 ) + ( ( GPTM_U8_TIMER_ID ) * ( 0x1000 ) ) ) : ( ( 0x4004C000 ) + ( ( GPTM_U8_TIMER_ID - GPTM_EN_WIDE_TIMER_2 ) * ( 0x1000 ) ) ) )

/*******************************************************************************************************************************************************************/
/* GPTM Registers' Locations */

#define GPTM_U32_GPTMCFG_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x000 ) ) // GPTM Configuration                                                 - page 727

#define GPTM_U32_GPTMTAMR_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x004 ) ) // GPTM Timer A Mode                                                  - page 729
#define GPTM_U32_GPTMTBMR_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x008 ) ) // GPTM Timer B Mode                                                  - page 733

#define GPTM_U32_GPTMCTL_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x00C ) ) // GPTM Control                                                       - page 737

#define GPTM_U32_GPTMSYNC_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x010 ) ) // GPTM Synchronize                                                   - page 741

#define GPTM_U32_GPTMIMR_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x018 ) ) // GPTM Interrupt Mask                                                - page 745
#define GPTM_U32_GPTMRIS_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x01C ) ) // GPTM Raw Interrupt Status                                          - page 748
#define GPTM_U32_GPTMMIS_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x020 ) ) // GPTM Masked Interrupt Status                                       - page 751
#define GPTM_U32_GPTMICR_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x024 ) ) // GPTM Interrupt Clear                                               - page 754

#define GPTM_U32_GPTMTAILR_REG( GPTM_U8_TIMER_ID )      *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x028 ) ) // GPTM Timer A Interval Load                                         - page 756
#define GPTM_U32_GPTMTBILR_REG( GPTM_U8_TIMER_ID )      *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x02C ) ) // GPTM Timer B Interval Load                                         - page 757

#define GPTM_U32_GPTMTAMATCHR_REG( GPTM_U8_TIMER_ID )   *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x030 ) ) // GPTM Timer A Match                                                 - page 758
#define GPTM_U32_GPTMTBMATCHR_REG( GPTM_U8_TIMER_ID )   *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x034 ) ) // GPTM Timer B Match                                                 - page 759

#define GPTM_U32_GPTMTAPR_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x038 ) ) // GPTM Timer A Prescale                                              - page 760
#define GPTM_U32_GPTMTBPR_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x03C ) ) // GPTM Timer B Prescale                                              - page 761

#define GPTM_U32_GPTMTAPMR_REG( GPTM_U8_TIMER_ID )      *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x040 ) ) // GPTM TimerA Prescale Match                                         - page 762
#define GPTM_U32_GPTMTBPMR_REG( GPTM_U8_TIMER_ID )      *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x044 ) ) // GPTM TimerB Prescale Match                                         - page 763

#define GPTM_U32_GPTMTAR_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x048 ) ) // GPTM Timer A                                                       - page 764
#define GPTM_U32_GPTMTBR_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x04C ) ) // GPTM Timer B                                                       - page 765

#define GPTM_U32_GPTMTAV_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x050 ) ) // GPTM Timer A Value                                                 - page 766
#define GPTM_U32_GPTMTBV_REG( GPTM_U8_TIMER_ID )        *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x054 ) ) // GPTM Timer B Value                                                 - page 767

#define GPTM_U32_GPTMRTCPD_REG( GPTM_U8_TIMER_ID )      *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x058 ) ) // GPTM RTC Predivide                                                 - page 768

#define GPTM_U32_GPTMTAPS_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x05C ) ) // GPTM Timer A Prescale Snapshot                                     - page 769
#define GPTM_U32_GPTMTBPS_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x060 ) ) // GPTM Timer B Prescale Snapshot                                     - page 770

#define GPTM_U32_GPTMTAPV_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x064 ) ) // GPTM Timer A Prescale Value                                        - page 771
#define GPTM_U32_GPTMTBPV_REG( GPTM_U8_TIMER_ID )       *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0x068 ) ) // GPTM Timer B Prescale Value                                        - page 772

#define GPTM_U32_GPTMPP_REG( GPTM_U8_TIMER_ID )         *( ( volatile  u32 * ) ( GPTM_U32_BASE_ADDRESS( GPTM_U8_TIMER_ID ) + 0xFC0 ) ) // GPTM Peripheral Properties                                         - page 773

#define GPTM_U32_RCGCTIMER_REG                          *( ( volatile  u32 * ) 0x400FE604 )                                            // 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control      - page 338
#define GPTM_U32_RCGCWTIMER_REG                         *( ( volatile  u32 * ) 0x400FE65C )                                            // 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control - page 357

/*******************************************************************************************************************************************************************/
/* GPTM Registers' Description */

/* GPTM Timer A Mode - GPTMTAMR */
/* Bit 11 - TAPLO: GPTM Timer A PWM Legacy Operation */
/* Value Description:
 * 	 0 	 Legacy operation with CCP pin driven Low when the
 *       GPTMTAILR is reloaded after the timer reaches 0.
 * 	 1 	 CCP is driven High when the GPTMTAILR is reloaded after the
 *       timer reaches 0.
 */
#define GPTM_U8_TAPLO_BIT           11

/* Bit 10 - TAMRSU: GPTM Timer A Match Register Update */
/* Value Description:
 * 	 0 	 Update the GPTMTAMATCHR register and the GPTMTAPR
 *       register, if used, on the next cycle.
 * 	 1 	 Update the GPTMTAMATCHR register and the GPTMTAPR
 *       register, if used, on the next timeout.
 */
#define GPTM_U8_TAMRSU_BIT          10

/* Bit 9 - TAPWMIE: GPTM Timer A PWM Interrupt Enable */
/* Value Description:
 * 	 0 	 Capture event interrupt is disabled.
 * 	 1 	 Capture event interrupt is enabled.
 */
#define GPTM_U8_TAPWMIE_BIT         9

/* Bit 8 - TAILD: GPTM Timer A Interval Load Write */
/* Value Description:
 * 	 0 	 Update the GPTMTAR and GPTMTAV registers with the value
 *       in the GPTMTAILR register on the next cycle. Also update the
 *       GPTMTAPS and GPTMTAPV registers with the value in the
 *       GPTMTAPR register on the next cycle.
 * 	 1 	 Update the GPTMTAR and GPTMTAV registers with the value
 *       in the GPTMTAILR register on the next timeout. Also update
 *       the GPTMTAPS and GPTMTAPV registers with the value in
 *       the GPTMTAPR register on the next timeout.
 */
#define GPTM_U8_TAILD_BIT           8

/* Bit 7 - TASNAPS: GPTM Timer A Snap-Shot Mode */
/* Value Description:
 * 	 0 	 Snap-shot mode is disabled.
 * 	 1 	 If Timer A is configured in the periodic mode, the actual
 *       free-running, capture or snapshot value of Timer A is loaded at
 *       the time-out event/capture or snapshot event into the GPTM
 *       Timer A (GPTMTAR) register. If the timer prescaler is used,
 *       the prescaler snapshot is loaded into the GPTM Timer A
 *       (GPTMTAPR).
 */
#define GPTM_U8_TASNAPS_BIT         7

/* Bit 6 - TAWOT: GPTM Timer A Wait-on-Trigger */
/* Value Description:
 * 	 0 	 Timer A begins counting as soon as it is enabled.
 * 	 1 	 If Timer A is enabled (TAEN is set in the GPTMCTL register),
 *       Timer A does not begin counting until it receives a trigger from
 *       the timer in the previous position in the daisy chain, see Figure
 *       11-9 on page 719. This function is valid for one-shot, periodic,
 *       and PWM modes.
 */
#define GPTM_U8_TAWOT_BIT           6

/* Bit 5 - TAMIE: GPTM Timer A Match Interrupt Enable */
/* Value Description:
 * 	 0 	 The match interrupt is disabled for match events.
 * 	 1 	 An interrupt is generated when the match value in the
 *       GPTMTAMATCHR register is reached in the one-shot and
 *       periodic modes.
 */
#define GPTM_U8_TAMIE_BIT           5

/* Bit 4 - TACDIR: GPTM Timer A Count Direction */
/* Value Description:
 * 	 0 	 The timer counts down.
 * 	 1 	 The timer counts up. When counting up, the timer starts from a
 *       value of 0x0.
 */
#define GPTM_U8_TACDIR_BIT          4

/* Bit 3 - TAAMS: GPTM Timer A Alternate Mode Select */
/* Value Description:
 * 	 0 	 Capture or compare mode is enabled.
 * 	 1 	 PWM mode is enabled.
 */
#define GPTM_U8_TAAMS_BIT           3

/* Bit 2 - TACMR: GPTM Timer A Capture Mode */
/* Value Description:
 * 	 0 	 Edge-Count mode
 * 	 1 	 Edge-Time mode
 */
#define GPTM_U8_TACMR_BIT           2

/* Bit 1:0 - TAMR: GPTM Timer A Mode */
/* Value Description:
 * 	0x0  Reserved
 * 	0x1  One-Shot Timer mode
 * 	0x2  Periodic Timer mode
 * 	0x3  Capture mode 
 */
#define GPTM_U8_TAMR01_BIT          1
#define GPTM_U8_TAMR00_BIT          0
/* End of GPTMTAMR Register */

/*************************************************************************/

/* GPTM Timer B Mode - GPTMTBMR */
/* Bit 11 - TBPLO: GPTM Timer B PWM Legacy Operation */
/* Value Description:
 * 	 0 	 Legacy operation with CCP pin driven Low when the
 *       GPTMTAILR is reloaded after the timer reaches 0.
 * 	 1 	 CCP is driven High when the GPTMTAILR is reloaded after the
 *       timer reaches 0.
 */
#define GPTM_U8_TBPLO_BIT           11

/* Bit 10 - TBMRSU: GPTM Timer B Match Register Update */
/* Value Description:
 * 	 0 	 Update the GPTMTBMATCHR register and the GPTMTBPR
 *       register, if used, on the next cycle.
 * 	 1 	 Update the GPTMTBMATCHR register and the GPTMTBPR
 *       register, if used, on the next timeout.
 */
#define GPTM_U8_TBMRSU_BIT          10

/* Bit 9 - TBPWMIE: GPTM Timer B PWM Interrupt Enable */
/* Value Description:
 * 	 0 	 Capture event interrupt is disabled.
 * 	 1 	 Capture event interrupt is enabled.
 */
#define GPTM_U8_TBPWMIE_BIT         9

/* Bit 8 - TBILD: GPTM Timer B Interval Load Write */
/* Value Description:
 * 	 0 	 Update the GPTMTBR and GPTMTBV registers with the value
 *       in the GPTMTBILR register on the next cycle. Also update the
 *       GPTMTBPS and GPTMTBPV registers with the value in the
 *       GPTMTBPR register on the next cycle.
 * 	 1 	 Update the GPTMTBR and GPTMTBV registers with the value
 *       in the GPTMTBILR register on the next timeout. Also update
 *       the GPTMTBPS and GPTMTBPV registers with the value in
 *       the GPTMTBPR register on the next timeout.
 */
#define GPTM_U8_TBILD_BIT           8

/* Bit 7 - TBSNAPS: GPTM Timer B Snap-Shot Mode */
/* Value Description:
 * 	 0 	 Snap-shot mode is disabled.
 * 	 1 	 If Timer B is configured in the periodic mode, the actual
 *       free-running, capture or snapshot value of Timer B is loaded at
 *       the time-out event/capture or snapshot event into the GPTM
 *       Timer B (GPTMTBR) register. If the timer prescaler is used,
 *       the prescaler snapshot is loaded into the GPTM Timer B
 *       (GPTMTBPR).
 */
#define GPTM_U8_TBSNAPS_BIT         7

/* Bit 6 - TBWOT: GPTM Timer B Wait-on-Trigger */
/* Value Description:
 * 	 0 	 Timer B begins counting as soon as it is enabled.
 * 	 1 	 If Timer B is enabled (TBEN is set in the GPTMCTL register),
 *       Timer B does not begin counting until it receives a trigger from
 *       the timer in the previous position in the daisy chain, see Figure
 *       11-9 on page 719. This function is valid for one-shot, periodic,
 *       and PWM modes.
 */
#define GPTM_U8_TBWOT_BIT           6

/* Bit 5 - TBMIE: GPTM Timer B Match Interrupt Enable */
/* Value Description:
 * 	 0 	 The match interrupt is disabled for match events.
 * 	 1 	 An interrupt is generated when the match value in the
 *       GPTMTBMATCHR register is reached in the one-shot and
 *       periodic modes.
 */
#define GPTM_U8_TBMIE_BIT           5

/* Bit 4 - TBCDIR: GPTM Timer B Count Direction */
/* Value Description:
 * 	 0 	 The timer counts down.
 * 	 1 	 The timer counts up. When counting up, the timer starts from a
 *       value of 0x0.
 */
#define GPTM_U8_TBCDIR_BIT          4

/* Bit 3 - TBAMS: GPTM Timer B Alternate Mode Select */
/* Value Description:
 * 	 0 	 Capture or compare mode is enabled.
 * 	 1 	 PWM mode is enabled.
 */
#define GPTM_U8_TBAMS_BIT           3

/* Bit 2 - TBCMR: GPTM Timer B Capture Mode */
/* Value Description:
 * 	 0 	 Edge-Count mode
 * 	 1 	 Edge-Time mode
 */
#define GPTM_U8_TBCMR_BIT           2

/* Bit 1:0 - TBMR: GPTM Timer B Mode */
/* Value Description:
 * 	0x0  Reserved
 * 	0x1  One-Shot Timer mode
 * 	0x2  Periodic Timer mode
 * 	0x3  Capture mode 
 */
#define GPTM_U8_TBMR01_BIT          1
#define GPTM_U8_TBMR00_BIT          0
/* End of GPTMTBMR Register */

/*************************************************************************/

/* GPTM Control - GPTMCTL */
/* Bit 14 - TBPWML: GPTM Timer B PWM Output Level */
/* Value Description:
 * 	 0 	 Output is unaffected.
 * 	 1 	 Output is inverted.
 */
#define GPTM_U8_TBPWML_BIT          14

/* Bit 13 - TBOTE: GPTM Timer B Output Trigger Enable */
/* Value Description:
 * 	 0 	 The output Timer B ADC trigger is disabled.
 * 	 1 	 The output Timer B ADC trigger is enabled.
 */
#define GPTM_U8_TBOTE_BIT           13

/* Bit 11:10 - TBEVENT: GPTM Timer B Event Mode */
/* Value Description:
 * 	0x0  Positive edge
 * 	0x1  Negative edge
 * 	0x2  Reserved
 * 	0x3  Both edges
 */
#define GPTM_U8_TBEVENT01_BIT       11
#define GPTM_U8_TBEVENT00_BIT       10

/* Bit 9 - TBSTALL: GPTM Timer B Stall Enable */
/* Value Description:
 * 	 0 	 Timer B continues counting while the processor is halted by the
 *       debugger.
 * 	 1 	 Timer B freezes counting while the processor is halted by the
 *       debugger.
 */
#define GPTM_U8_TBSTALL_BIT         9

/* Bit 8 - TBEN: GPTM Timer B Enable */
/* Value Description:
 * 	 0 	 Timer B is disabled.
 * 	 1 	 Timer B is enabled and begins counting or the capture logic is
 *       enabled based on the GPTMCFG register.
 */
#define GPTM_U8_TBEN_BIT            8

/* Bit 6 - TAPWML: GPTM Timer A PWM Output Level */
/* Value Description:
 * 	 0 	 Output is unaffected.
 * 	 1 	 Output is inverted.
 */
#define GPTM_U8_TAPWML_BIT          6

/* Bit 5 - TAOTE: GPTM Timer A Output Trigger Enable */
/* Value Description:
 * 	 0 	 The output Timer A ADC trigger is disabled.
 * 	 1 	 The output Timer A ADC trigger is enabled.
 */
#define GPTM_U8_TAOTE_BIT           5

/* Bit 4 - RTCEN: GPTM RTC Stall Enable */
/* Value Description:
 * 	 0 	 RTC counting freezes while the processor is halted by the
 *       debugger.
 * 	 1 	 RTC counting continues while the processor is halted by the
 *       debugger.
 */
#define GPTM_U8_RTCEN_BIT           4

/* Bit 3:2 - TAEVENT: GPTM Timer A Event Mode */
/* Value Description:
 * 	0x0  Positive edge
 * 	0x1  Negative edge
 * 	0x2  Reserved
 * 	0x3  Both edges
 */
#define GPTM_U8_TAEVENT01_BIT       3
#define GPTM_U8_TAEVENT00_BIT       2

/* Bit 1 - TASTALL: GPTM Timer A Stall Enable */
/* Value Description:
 * 	 0 	 Timer A continues counting while the processor is halted by the
 *       debugger.
 * 	 1 	 Timer A freezes counting while the processor is halted by the
 *       debugger.
 */
#define GPTM_U8_TASTALL_BIT         1

/* Bit 0 - TAEN: GPTM Timer A Enable */
/* Value Description:
 * 	 0 	 Timer A is disabled.
 * 	 1 	 Timer A is enabled and begins counting or the capture logic is
 *       enabled based on the GPTMCFG register.
 */
#define GPTM_U8_TAEN_BIT            0
/* End of GPTMCTL Register */

/*************************************************************************/

/* GPTM Interrupt Mask - GPTMIMR */
/* Bit 16 - WUEIM: 32/64-Bit Wide GPTM Write Update Error Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_WUEIM_BIT           16

/* Bit 11 - TBMIM: GPTM Timer B Match Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_TBMIM_BIT           11

/* Bit 10 - CBEIM: GPTM Timer B Capture Mode Event Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_CBEIM_BIT           10

/* Bit 9 - CBMIM: GPTM Timer B Capture Mode Match Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_CBMIM_BIT           9

/* Bit 8 - TBTOIM: GPTM Timer B Time-Out Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_TBTOIM_BIT          8

/* Bit 4 - TAMIM: GPTM Timer A Match Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_TAMIM_BIT           4

/* Bit 3 - RTCIM: GPTM RTC Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_RTCIM_BIT           3

/* Bit 2 - CAEIM: GPTM Timer A Capture Mode Event Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_CAEIM_BIT           2

/* Bit 1 - CAMIM: GPTM Timer A Capture Mode Match Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_CAMIM_BIT           1

/* Bit 0 - TATOIM: GPTM Timer A Time-Out Interrupt Mask */
/* Value Description:
 * 	 0 	 Interrupt is disabled.
 * 	 1 	 Interrupt is enabled.
 */
#define GPTM_U8_TATOIM_BIT          0
/* End of GPTMIMR Register */

/*************************************************************************/

/* GPTM Raw Interrupt Status - GPTMRIS */
/* Bit 16 - WUERIS: 32/64-Bit Wide GPTM Write Update Error Raw Interrupt Status */
/* Value Description:
 * 	 0 	 No error.
 * 	 1 	 Either a Timer A register or a Timer B register was written twice
 *       in a row or a Timer A register was written before the
 *       corresponding Timer B register was written.
 */
#define GPTM_U8_WUERIS_BIT          16

/* Bit 11 - TBMRIS: GPTM Timer B Match Raw Interrupt */
/* Value Description:
 * 	 0 	 The match value has not been reached.
 * 	 1 	 The TBMIE bit is set in the GPTMTBMR register, and the match
 *       values in the GPTMTBMATCHR and (optionally) GPTMTBPMR
 *       registers have been reached when configured in one-shot or
 *       periodic mode.
 */
#define GPTM_U8_TBMRIS_BIT          11

/* Bit 10 - CBERIS: GPTM Timer B Capture Mode Event Raw Interrupt */
/* Value Description:
 * 	 0 	 The capture mode event for Timer B has not occurred.
 * 	 1 	 A capture mode event has occurred for Timer B. This interrupt
 *       asserts when the subtimer is configured in Input Edge-Time
 *       mode or when configured in PWM mode with the PWM interrupt
 *       enabled by setting the TBPWMIE bit in the GPTMTBMR.
 */
#define GPTM_U8_CBERIS_BIT          10

/* Bit 9 - CBMRIS: GPTM Timer B Capture Mode Match Raw Interrupt */
/* Value Description:
 * 	 0 	 The capture mode match for Timer B has not occurred.
 * 	 1 	 The capture mode match has occurred for Timer B. This interrupt
 *       asserts when the values in the GPTMTBR and GPTMTBPR
 *       match the values in the GPTMTBMATCHR and GPTMTBPMR
 *       when configured in Input Edge-Time mode.
 */
#define GPTM_U8_CBMRIS_BIT          9

/* Bit 8 - TBTORIS: GPTM Timer B Time-Out Raw Interrupt */
/* Value Description:
 * 	 0 	 Timer B has not timed out.
 * 	 1 	 Timer B has timed out. This interrupt is asserted when a
 *       one-shot or periodic mode timer reaches it's count limit (0 or
 *       the value loaded into GPTMTBILR, depending on the count
 *       direction).
 */
#define GPTM_U8_TBTORIS_BIT         8

/* Bit 4 - TAMRIS: GPTM Timer A Match Raw Interrupt */
/* Value Description:
 * 	 0 	 The match value has not been reached.
 * 	 1 	 The TAMIE bit is set in the GPTMTAMR register, and the match
 *       values in the GPTMTAMATCHR and (optionally) GPTMTAPMR
 *       registers have been reached when configured in one-shot or
 *       periodic mode.
 */
#define GPTM_U8_TAMRIS_BIT          4

/* Bit 3 - RTCRIS: GPTM RTC Raw Interrupt */
/* Value Description:
 * 	 0 	 The RTC event has not occurred.
 * 	 1 	 The RTC event has occurred.
 */
#define GPTM_U8_RTCRIS_BIT          3

/* Bit 2 - CAERIS: GPTM Timer A Capture Mode Event Raw Interrupt */
/* Value Description:
 * 	 0 	 The capture mode event for Timer A has not occurred.
 * 	 1 	 A capture mode event has occurred for Timer A. This interrupt
 *       asserts when the subtimer is configured in Input Edge-Time
 *       mode or when configured in PWM mode with the PWM interrupt
 *       enabled by setting the TAPWMIE bit in the GPTMTAMR.
 */
#define GPTM_U8_CAERIS_BIT          2

/* Bit 1 - CAMRIS: GPTM Timer A Capture Mode Match Raw Interrupt */
/* Value Description:
 * 	 0 	 The capture mode match for Timer A has not occurred.
 * 	 1 	 The capture mode match has occurred for Timer A. This interrupt
 *       asserts when the values in the GPTMTAR and GPTMTAPR
 *       match the values in the GPTMTAMATCHR and GPTMTAPMR
 *       when configured in Input Edge-Time mode.
 */
#define GPTM_U8_CAMRIS_BIT          1

/* Bit 0 - TATORIS: GPTM Timer A Time-Out Raw Interrupt */
/* Value Description:
 * 	 0 	 Timer A has not timed out.
 * 	 1 	 Timer A has timed out. This interrupt is asserted when a
 *       one-shot or periodic mode timer reaches it's count limit (0 or
 *       the value loaded into GPTMTAILR, depending on the count
 *       direction).
 */
#define GPTM_U8_TATORIS_BIT         0
/* End of GPTMRIS Register */

/*************************************************************************/

/* GPTM Masked Interrupt Status - GPTMMIS */
/* Bit 16 - WUEMIS: 32/64-Bit Wide GPTM Write Update Error Masked Interrupt Status */
/* Value Description:
 * 	 0 	 An unmasked Write Update Error has not occurred.
 * 	 1 	 An unmasked Write Update Error has occurred.
 */
#define GPTM_U8_WUEMIS_BIT          16

/* Bit 11 - TBMMIS: GPTM Timer B Match Masked Interrupt */
/* Value Description:
 * 	 0 	 A Timer B Mode Match interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Timer B Mode Match interrupt
 *       has occurred.
 */
#define GPTM_U8_TBMMIS_BIT          11

/* Bit 10 - CBEMIS: GPTM Timer B Capture Mode Event Masked Interrupt */
/* Value Description:
 * 	 0 	 A Capture B event interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Capture B event interrupt
 *       has occurred.
 */
#define GPTM_U8_CBEMIS_BIT          10

/* Bit 9 - CBMMIS: GPTM Timer B Capture Mode Match Masked Interrupt */
/* Value Description:
 * 	 0 	 A Capture B Mode Match interrupt has not occurred or is
 *       masked.
 * 	 1 	 An unmasked Capture B Match interrupt
 *       has occurred.
 */
#define GPTM_U8_CBMMIS_BIT          9

/* Bit 8 - TBTOMIS: GPTM Timer B Time-Out Masked Interrupt */
/* Value Description:
 * 	 0 	 A Timer B Time-Out interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Timer B Time-Out interrupt
 *       has occurred.
 */
#define GPTM_U8_TBTOMIS_BIT         8

/* Bit 4 - TAMMIS: GPTM Timer A Match Masked Interrupt */
/* Value Description:
 * 	 0 	 A Timer A Mode Match interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Timer A Mode Match interrupt
 *       has occurred.
 */
#define GPTM_U8_TAMMIS_BIT          4

/* Bit 3 - RTCMIS: GPTM RTC Masked Interrupt */
/* Value Description:
 * 	 0 	 An RTC event interrupt has not occurred or is masked.
 * 	 1 	 An unmasked RTC event interrupt
 *       has occurred.
 */
#define GPTM_U8_RTCMIS_BIT          3

/* Bit 2 - CAEMIS: GPTM Timer A Capture Mode Event Masked Interrupt */
/* Value Description:
 * 	 0 	 A Capture A event interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Capture A event interrupt
 *       has occurred.
 */
#define GPTM_U8_CAEMIS_BIT          2

/* Bit 1 - CAMMIS: GPTM Timer A Capture Mode Match Masked Interrupt */
/* Value Description:
 * 	 0 	 A Capture A Mode Match interrupt has not occurred or is
 *       masked.
 * 	 1 	 An unmasked Capture A Match interrupt
 *       has occurred.
 */
#define GPTM_U8_CAMMIS_BIT          1

/* Bit 0 - TATOMIS: GPTM Timer A Time-Out Masked Interrupt */
/* Value Description:
 * 	 0 	 A Timer A Time-Out interrupt has not occurred or is masked.
 * 	 1 	 An unmasked Timer A Time-Out interrupt
 *       has occurred.
 */
#define GPTM_U8_TATOMIS_BIT         0
/* End of GPTMMIS Register */

/*************************************************************************/

/* GPTM Interrupt Clear - GPTMICR */
/* Bit 16 - WUECINT: 32/64-Bit Wide GPTM Write Update Error Interrupt Clear */
/* 
 * Writing a 1 to this bit clears the WUERIS bit in the GPTMRIS register
 * and the WUEMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_WUECINT_BIT         16

/* Bit 11 - TBMCINT: GPTM Timer B Match Interrupt Clear */
/* 
 * Writing a 1 to this bit clears the CBERIS bit in the GPTMRIS register
 * and the CBEMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_TBMCINT_BIT         11

/* Bit 10 - CBECINT: GPTM Timer B Capture Mode Event Interrupt Clear */
/* 
 * Writing a 1 to this bit clears the TBMRIS bit in the GPTMRIS register
 * and the TBMMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_CBECINT_BIT         10

/* Bit 9 - CBMCINT: GPTM Timer B Capture Mode Match Interrupt Clear */
/*
 * Writing a 1 to this bit clears the CBMRIS bit in the GPTMRIS register
 * and the CBMMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_CBMCINT_BIT         9

/* Bit 8 - TBTOCINT: GPTM Timer B Time-Out Interrupt Clear */
/*
 * Writing a 1 to this bit clears the TBTORIS bit in the GPTMRIS register
 * and the TBTOMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_TBTOCINT_BIT        8

/* Bit 4 - TAMCINT: GPTM Timer A Match Interrupt Clear */
/*
 * Writing a 1 to this bit clears the TAMRIS bit in the GPTMRIS register
 * and the TAMMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_TAMCINT_BIT         4

/* Bit 3 - RTCCINT: GPTM RTC Interrupt Clear */
/*
 * Writing a 1 to this bit clears the RTCRIS bit in the GPTMRIS register
 * and the RTCMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_RTCCINT_BIT         3

/* Bit 2 - CAECINT: GPTM Timer A Capture Mode Event Interrupt Clear */
/* 
 * Writing a 1 to this bit clears the CAERIS bit in the GPTMRIS register
 * and the CAEMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_CAECINT_BIT         2

/* Bit 1 - CAMCINT: GPTM Timer A Capture Mode Match Interrupt Clear */
/*
 * Writing a 1 to this bit clears the CAMRIS bit in the GPTMRIS register
 * and the CAMMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_CAMCINT_BIT         1

/* Bit 0 - TATOCINT: GPTM Timer A Time-Out Raw Interrupt */
/* 
 * Writing a 1 to this bit clears the TATORIS bit in the GPTMRIS register
 * and the TATOMIS bit in the GPTMMIS register.
 */
#define GPTM_U8_TATOCINT_BIT        0
/* End of GPTMICR Register */

/*************************************************************************/

/* 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control - RCGCTIMER */
/* Bit 5 - R5: 16/32-Bit General-Purpose Timer 5 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 5 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 5 in Run mode.
 */
#define GPTM_U8_R5_BIT              5

/* Bit 4 - R4: 16/32-Bit General-Purpose Timer 4 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 4 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 4 in Run mode.
 */
#define GPTM_U8_R4_BIT              4

/* Bit 3 - R3: 16/32-Bit General-Purpose Timer 3 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 3 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 3 in Run mode.
 */
#define GPTM_U8_R3_BIT              3

/* Bit 2 - R2: 16/32-Bit General-Purpose Timer 2 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 2 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 2 in Run mode.
 */
#define GPTM_U8_R2_BIT              2

/* Bit 1 - R1: 16/32-Bit General-Purpose Timer 1 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 1 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 1 in Run mode.
 */
#define GPTM_U8_R1_BIT              1

/* Bit 0 - R0: 16/32-Bit General-Purpose Timer 0 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 16/32-bit general-purpose timer module 0 is disabled.
 * 	 1 	 Enable and provide a clock to 16/32-bit general-purpose timer
 *       module 0 in Run mode.
 */
#define GPTM_U8_R0_BIT              0
/* End of RCGCTIMER Register */

/*************************************************************************/

/* 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control - RCGCWTIMER */
/* Bit 5 - WR5: 32/64-Bit Wide General-Purpose Timer 5 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 5 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 5 in Run mode.
 */
#define GPTM_U8_WR5_BIT             5

/* Bit 4 - WR4: 32/64-Bit Wide General-Purpose Timer 4 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 4 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 4 in Run mode.
 */
#define GPTM_U8_WR4_BIT             4

/* Bit 3 - WR3: 32/64-Bit Wide General-Purpose Timer 3 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 3 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 3 in Run mode.
 */
#define GPTM_U8_WR3_BIT             3

/* Bit 2 - WR2: 32/64-Bit Wide General-Purpose Timer 2 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 2 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 2 in Run mode.
 */
#define GPTM_U8_WR2_BIT             2

/* Bit 1 - WR1: 32/64-Bit Wide General-Purpose Timer 1 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 1 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 1 in Run mode.
 */
#define GPTM_U8_WR1_BIT             1

/* Bit 0 - WR0: 32/64-Bit Wide General-Purpose Timer 0 Run Mode Clock Gating Control */
/* Value Description:
 * 	 0 	 32/64-Bit wide general-purpose timer module 0 is disabled.
 * 	 1 	 Enable and provide a clock to 32/64-Bit wide general-purpose 
 *       timer module 0 in Run mode.
 */
#define GPTM_U8_WR0_BIT             0
/* End of RCGCTIMER Register */

/*******************************************************************************************************************************************************************/
/* GPTM Private Macros */

#define GPTM_U8_INTERRUPTS_ACTION_INDEX( GPTM_EN_TIMER_ID, GPTM_EN_TIMER_USE )    ( GPTM_EN_TIMER_USE < GPTM_EN_CONCATUNATED ? ( ( 2 * GPTM_EN_TIMER_ID ) + GPTM_EN_TIMER_USE ) : ( 2 * GPTM_EN_TIMER_ID ) )

/*******************************************************************************************************************************************************************/

#endif /* GPTM_PRIVATE_H_ */
