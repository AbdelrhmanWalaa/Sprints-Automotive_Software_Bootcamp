/*
 * bit_math.h
 *
 *  Created on: Mar 31, 2021
 *      Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *	 Copyright: MIT License
 *
 *	            Copyright (c) Abdelrhman Walaa
 *
 *	            Permission is hereby granted, free of charge, to any person obtaining a copy
 *	            of this software and associated documentation files (the "Software"), to deal
 *	            in the Software without restriction, including without limitation the rights
 *	            to use, copy, modify, merge, publish, distribute, sub license, and/or sell
 *	            copies of the Software, and to permit persons to whom the Software is
 *	            furnished to do so, subject to the following conditions:
 *
 *	            The above copyright notice and this permission notice shall be included in all
 *	            copies or substantial portions of the Software.
 *
 *	            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	            IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	            FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	            AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	            LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	            OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	            SOFTWARE.
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
