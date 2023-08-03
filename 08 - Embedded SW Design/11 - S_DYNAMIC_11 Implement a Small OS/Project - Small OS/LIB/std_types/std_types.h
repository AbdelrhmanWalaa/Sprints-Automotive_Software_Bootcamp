/*
 * std_types.h
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

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;				/* 1 byte , 0 -> 255 */
typedef unsigned short int u16;			/* 2 bytes, 0 -> 65,535 */
typedef unsigned long  int u32;			/* 4 bytes, 0 -> 4,294,967,295 */
typedef unsigned long long int u64;		/* 8 bytes, 0 -> 18,446,744,073,709,551,615 */

typedef signed char s8;					/* 1 byte , -128 -> 127 */
typedef signed short int s16;			/* 2 bytes, -32,768 -> 32,767 */
typedef signed long  int s32;			/* 4 bytes, -2,147,483,648 -> 2,147,483,647 */
typedef signed long long int s64;		/* 8 bytes, -9,223,372,036,854,775,807 -> 9,223,372,036,854,775,807 */

typedef float  f32;						/* 4 bytes, 3.4e-38 -> 3.4e+38 */
typedef double f64;						/* 8 bytes, 1.7e-308 -> 1.7e+308 */

typedef void vd;

#define STD_TYPES_OK	1
#define STD_TYPES_NOK	0

#define NULL	        ( ( void * ) 0 )

#endif /* STD_TYPES_H_ */