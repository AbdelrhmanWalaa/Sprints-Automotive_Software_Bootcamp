/*
 * bit_math.h
 *
 *  Created on: Mar 31, 2021
 *      Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER | ( 1 << BIT_NUMBER ) )
#define CLR_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER & ~( 1 << BIT_NUMBER ) )
#define TOG_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER ^ ( 1 << BIT_NUMBER ) )
#define GET_BIT( REGISTER, BIT_NUMBER )		( ( REGISTER & ( 1 << BIT_NUMBER ) ) >> BIT_NUMBER ) // ( ( REGISTER >> BIT_NUMBER ) & 1 )
#define UPPER_NIBBLE( REGISTER, DATA )		( REGISTER = ( REGISTER & 0x0F)  | ( DATA & 0xF0 ) )
#define LOWER_NIBBLE( REGISTER, DATA )		( REGISTER = ( REGISTER & 0x0F ) | ( DATA << 4 ) )

#endif /* BIT_MATH_H_ */
