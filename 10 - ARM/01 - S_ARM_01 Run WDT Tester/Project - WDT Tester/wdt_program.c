/*
 * wdt_program.c
 *
 *     Created on: Jun 1, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Watchdog Timer (WDT) functions' implementation, and IRQ handlers implementation.
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
#include "wdt_interface.h"
#include "wdt_private.h"

/*******************************************************************************************************************************************************************/
/* WDT Global Variables */

/* Global Pointer to Function, this function ( in an Upper Layer ) which this Pointer will hold its address; is having void input argument and void return type. */
static void ( *vpf_gs_interruptAction ) ( void ) = STD_TYPES_NULL;

/* Global Array of TimeCounters, to store TimeoutTicks for both WDTs */
static u32 au32_gs_timeoutCounters[2] = { 0, 0 };

WDT_enId_t en_g_currentWDTId = WDT_EN_INVALID_ID;

extern unsigned int SystemCoreClock;

/*******************************************************************************************************************************************************************/
/* WDT Static Functions' Prototypes */

static vd WDT_waitUntilWriteCompletes( void );
static WDT_enErrorState_t WDT_setTimeoutCounter( WDT_enId_t en_a_wdtId, u32 u32_a_timeoutMS );

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_initalization
 Input: Pointer to st LinkConfig
 Output: en Error or No Error
 Description: Function to initialize WDT peripheral using Linking Configurations.
*/
WDT_enErrorState_t WDT_initalization( const WDT_stLinkConfig_t *pst_a_linkConfig )
{
	/* Define local variable to set the error state = OK. */
	WDT_enErrorState_t en_l_errorState = WDT_EN_OK;
	
	/* Check 1: Pointer is not equal to NULL. */
	if ( pst_a_linkConfig != STD_TYPES_NULL )
	{
		/* Check 1.1: Id, ResetMode, InterruptMode, InterruptType, and StallMode are in the valid range. */
		if ( ( pst_a_linkConfig->en_a_id < WDT_EN_INVALID_ID )				 					&& 
				 ( pst_a_linkConfig->en_a_resetMode < WDT_EN_INVALID_RST_MODE )			&&
				 ( pst_a_linkConfig->en_a_interruptMode < WDT_EN_INVALID_INT_MODE )	&&
				 ( pst_a_linkConfig->en_a_interruptType < WDT_EN_INVALID_INT_TYPE ) &&
				 ( pst_a_linkConfig->en_a_stallMode < WDT_EN_INVALID_STALL_MODE ) )
		{
			/* Step 1: Enable peripheral clock, by setting the Rn bit in the RCGCWD register. */
			switch ( pst_a_linkConfig->en_a_id )
			{
				case WDT_EN_ID_0: SET_BIT( WDT_U32_RCGCWD_REG, WDT_U8_R0_BIT ); break;
				case WDT_EN_ID_1: SET_BIT( WDT_U32_RCGCWD_REG, WDT_U8_R1_BIT ); break;
				default:									/* Do Nothing. */											break;
			}
			
			/* Step 2: Load the WDTLOAD register with the desired timer load value. */
			WDT_setTimeoutCounter( pst_a_linkConfig->en_a_id, pst_a_linkConfig->u32_a_timeoutMS );
			
			/* Step 3: Wait for the WRC bit in the WDTCTL register to be set, incase using WDT1.*/
			if ( pst_a_linkConfig->en_a_id == WDT_EN_ID_1 )
			{
				WDT_waitUntilWriteCompletes();
			}
			
			/* Step 4: Configure ResetMode, by configuring the RESEN bit in the WDTCTL register. */
			switch ( pst_a_linkConfig->en_a_resetMode )
			{
				case WDT_EN_DISABLE_RST: CLR_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_RESEN_BIT ); break;
				case WDT_EN_ENABLE_RST : SET_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_RESEN_BIT ); break;
				default:																			/* Do Nothing. */											 									 break;
			}
			
			/* Step 5: Wait for the WRC bit in the WDTCTL register to be set, incase using WDT1. */
			if ( pst_a_linkConfig->en_a_id == WDT_EN_ID_1 )
			{
				WDT_waitUntilWriteCompletes();
			}
			
			/* Step 6: Configure InterruptMode, by configuring the INTEN bit in the WDTCTL register. */
			switch ( pst_a_linkConfig->en_a_interruptMode )
			{
				case WDT_EN_DISABLE_INT: 
				{
					CLR_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_INTEN_BIT );					
					break;
				}
								
				case WDT_EN_ENABLE_INT : 
				{
					/* Step 6.1: Store the passed address of function through pointer to function ( InterruptAction ) into the Global Pointer to Function ( InterruptAction ). */
					/* Check 1.1.1: Pointer is not equal to NULL. */
					if ( pst_a_linkConfig->vpf_a_interruptAction != STD_TYPES_NULL )
					{
						vpf_gs_interruptAction = pst_a_linkConfig->vpf_a_interruptAction;
					}
					/* Check 1.1.1: Pointer is equal to NULL. */
					else
					{
						/* Update error state = NOK, Pointer is NULL! */
						en_l_errorState = WDT_EN_NOK;
					}
					
					/* Step 6.2: Configure InterruptType, by configuring the INTTYPE bit in the WDTCTL register. */
					switch ( pst_a_linkConfig->en_a_interruptType )
					{
						case WDT_EN_NORMAL_INT: CLR_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_INTTYPE_BIT ); break;
						case WDT_EN_NMI_INT   : SET_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_INTTYPE_BIT ); break;
						default:																						/* Do Nothing. */															 			break;
					}
					
					/* Step 6.3: Wait for the WRC bit in the WDTCTL register to be set, incase using WDT1. */
					if ( pst_a_linkConfig->en_a_id == WDT_EN_ID_1 )
					{
						WDT_waitUntilWriteCompletes();
					}
					
					SET_BIT( WDT_U32_WDTCTL_REG( pst_a_linkConfig->en_a_id ), WDT_U8_INTEN_BIT );
					
					/* Step 6.4: Wait for the WRC bit in the WDTCTL register to be set, incase using WDT1. */
					if ( pst_a_linkConfig->en_a_id == WDT_EN_ID_1 )
					{
						WDT_waitUntilWriteCompletes();
					}
					
					/* Step 6.5: Enable Interrupt in the NVIC peripheral. */
					NVIC_EnableIRQ( WATCHDOG0_IRQn );
					
					/* Step 6.6: Enable Interrupts. */
					__enable_irq();
					
					break;
				}

				default:
				{
					/* Do Nothing. */
					break;
				}
			}
			
			/* Step 7: Configure StallMode, by configuring the STALL bit in the WDTTEST register. */
			switch ( pst_a_linkConfig->en_a_stallMode )
			{
				case WDT_EN_DISABLE_STALL: CLR_BIT( WDT_U32_WDTTEST_REG( pst_a_linkConfig->en_a_id ), WDT_U8_STALL_BIT ); break;
				case WDT_EN_ENABLE_STALL : SET_BIT( WDT_U32_WDTTEST_REG( pst_a_linkConfig->en_a_id ), WDT_U8_STALL_BIT ); break;
				default:																			/* Do Nothing. */											 									 	  break;
			}
		}
		/* Check 1.2: Id, ResetMode, InterruptMode, InterruptType, or StallMode is not in the valid range. */
		else
		{
			/* Update error state = NOK, Wrong Id, ResetMode, InterruptMode, InterruptType, or StallMode! */
			en_l_errorState = WDT_EN_NOK;
		}
	}
	/* Check 2: Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Pointer is NULL! */
		en_l_errorState = WDT_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_waitUntilWriteCompletes
 Input: void
 Output: void
 Description: Function to Wait until write completes when using WDT1.
*/
static vd WDT_waitUntilWriteCompletes( void )
{
	/* Important: Because the Watchdog Timer 1 module has an independent clocking domain, its
	 * registers must be written with a timing gap between accesses. Software must guarantee
	 * that this delay is inserted between back-to-back writes to WDT1 registers or between
	 * a write followed by a read to the registers. The timing for back-to-back reads from the
	 * WDT1 module has no restrictions. The WRC bit in the Watchdog Control (WDTCTL)
	 * register for WDT1 indicates that the required timing gap has elapsed. This bit is cleared
	 * on a write operation and set once the write completes, indicating to software that another
	 * write or read may be started safely. Software should poll WDTCTL for WRC=1 prior to
	 * accessing another register. 
	 * Note that WDT0 does not have this restriction as it runs off the system clock and therefore 
	 * does not have a WRC bit. 
	 */
	/* Loop: Wait ( Poll ) until write completes ( i.e. until Flag ( WRC ) = 1 ). */
	while ( !( GET_BIT( WDT_U32_WDTCTL_REG( WDT_EN_ID_1 ), WDT_U8_WRC_BIT ) ) );
}

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_setTimeoutCounter
 Input: en Id and u32 TimeoutMS
 Output: en Error or No Error
 Description: Function to Set the Timeout Counter.
*/
static WDT_enErrorState_t WDT_setTimeoutCounter( WDT_enId_t en_a_wdtId, u32 u32_a_timeoutMS )
{
	/* Define local variable to set the error state = OK. */
	WDT_enErrorState_t en_l_errorState = WDT_EN_OK;
	
	/* Define local variable to store the timeout ticks = 0. */
	u64 u64_l_timeoutTicks = 0;
	
	/* Check 1: Id and TimeoutMS are in the valid range. */
	if ( ( en_a_wdtId < WDT_EN_INVALID_ID ) && ( u32_a_timeoutMS != 0 ) )
	{
		/* Step 1: Convert TimeoutMS into TimeoutTicks. */
		u64_l_timeoutTicks = ( u64 ) ( u32_a_timeoutMS * ( SystemCoreClock / 1000 ) );
		
		/* Step 2: Store TimeoutTicks in the Global TimeoutCounters Array. */
		au32_gs_timeoutCounters[en_a_wdtId] = ( u32 ) u64_l_timeoutTicks;
		
		/* Step 3: Load the WDTLOAD register with the desired TimeoutTicks. */
		WDT_U32_WDTLOAD_REG( en_a_wdtId ) = au32_gs_timeoutCounters[en_a_wdtId];		
	}
	/* Check 2: Id or TimeoutMS is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong Id or TimeoutMS! */
		en_l_errorState = WDT_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_resetTimeoutCounter
 Input: en Id
 Output: en Error or No Error
 Description: Function to Reset the Timeout Counter.
*/
WDT_enErrorState_t WDT_resetTimeoutCounter( WDT_enId_t en_a_wdtId )
{
	/* Define local variable to set the error state = OK. */
	WDT_enErrorState_t en_l_errorState = WDT_EN_OK;
	
	/* Check 1: Id is in the valid range. */
	if ( en_a_wdtId < WDT_EN_INVALID_ID )
	{
		/* Check 1.1: Global TimeoutCounters Array Value of the the passed Id is not equal to 0. */
		if ( au32_gs_timeoutCounters[en_a_wdtId] != 0 )
		{
			/* Step 2: Reload the WDTLOAD register with the desired TimeoutTicks. */
			WDT_U32_WDTLOAD_REG( en_a_wdtId ) = au32_gs_timeoutCounters[en_a_wdtId];	
		}
		/* Check 1.1: Global TimeoutCounters Array Value of the the passed Id is equal to 0. */
		else
		{
			/* Do Nothing. */
		}
	}		
	/* Check 2: Id is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong Id! */
		en_l_errorState = WDT_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_getInterruptStatus
 Input: en Id and Pointer to bool ReturnedInterruptStatus
 Output: en Error or No Error
 Description: Function to Get WDT Interrupt Status.
*/
WDT_enErrorState_t WDT_getInterruptStatus( WDT_enId_t en_a_wdtId, bool *pbool_a_returnedInterruptStatus )
{
	/* Define local variable to set the error state = OK. */
	WDT_enErrorState_t en_l_errorState = WDT_EN_OK;
	
	/* Check 1: Id is in the valid range, and Pointer is not equal to NULL. */
	if ( ( en_a_wdtId < WDT_EN_INVALID_ID ) && ( pbool_a_returnedInterruptStatus != STD_TYPES_NULL ) )
	{
		/* Check 1.1: Timeout event has occurred. */
		if ( GET_BIT( WDT_U32_WDTRIS_REG( en_a_wdtId ), WDT_U8_WDTRIS_BIT ) )
		{
			*pbool_a_returnedInterruptStatus = STD_TYPES_TRUE;
		}
		/* Check 1.1: Timeout event has not occurred. */
		else
		{
			*pbool_a_returnedInterruptStatus = STD_TYPES_FALSE;
		}
	}		
	/* Check 2: Id is not in the valid range, or Pointer is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong Id, or Pointer is Null! */
		en_l_errorState = WDT_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/
/*
 Name: WDT_deinitalization
 Input: en Id
 Output: en Error or No Error
 Description: Function to deinitialize WDT using the passed Id.
*/
WDT_enErrorState_t WDT_deinitalization( WDT_enId_t en_a_wdtId )
{
	/* Define local variable to set the error state = OK. */
	WDT_enErrorState_t en_l_errorState = WDT_EN_OK;
	
	/* Check 1: Id is in the valid range. */
	if ( en_a_wdtId < WDT_EN_INVALID_ID )
	{
		/* Step 1: Disable peripheral clock, by clearing the Rn bit in the RCGCWD register. */
		switch ( en_a_wdtId )
		{
			case WDT_EN_ID_0: CLR_BIT( WDT_U32_RCGCWD_REG, WDT_U8_R0_BIT ); break;
			case WDT_EN_ID_1: CLR_BIT( WDT_U32_RCGCWD_REG, WDT_U8_R1_BIT ); break;
			default:									/* Do Nothing. */											break;
		}					
	}		
	/* Check 2: Id is not in the valid range. */
	else
	{
		/* Update error state = NOK, Wrong Id! */
		en_l_errorState = WDT_EN_NOK;
	}

	return en_l_errorState;
}

/*******************************************************************************************************************************************************************/

/* IRQ handler implementation of WDT0 */
void WDT0_Handler ( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( vpf_gs_interruptAction != STD_TYPES_NULL )
	{
		/* Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Pointer to Function ( InterruptAction ). */
		vpf_gs_interruptAction();
	}
	/* Check 1: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}
}

/*******************************************************************************************************************************************************************/

/* IRQ handler implementation of NMI */
void NMI_Handler ( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( vpf_gs_interruptAction != STD_TYPES_NULL )
	{
		/* Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Pointer to Function ( InterruptAction ). */
		vpf_gs_interruptAction();
	}
	/* Check 1: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}
}

/*******************************************************************************************************************************************************************/
