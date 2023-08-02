/*
 * 	File:						common_macros.h
 *	Module:					library
 *	Description: 		header file 
 * 	Author: 				HAZEM ASHRAF
 */


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1UL<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1UL<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1UL<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8UL-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8UL-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1UL<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1UL<<BIT)) )

/* get value of a certain bit in any register */
#define GET_BIT_STATUS(REGISTER,BIT_NUMBER)		(0UL != ((REGISTER) & (1UL << (BIT_NUMBER))))

#endif /* COMMON_MACROS_H_ */
