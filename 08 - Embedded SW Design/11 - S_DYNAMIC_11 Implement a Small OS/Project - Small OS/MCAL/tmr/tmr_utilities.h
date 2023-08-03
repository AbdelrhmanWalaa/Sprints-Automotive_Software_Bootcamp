/*
 * tmr_utilities.h
 *
 * Created: 2023-06-01 2:34:07 AM
 *  Author: HAZEM-PC
 */ 

#ifndef TMR_UTILITIES_H_
#define TMR_UTILITIES_H_

/*============= MACRO DEFINITION =============*/

//timer common macros
#define F_CPU 8000000UL
#define MAX_COUNT 65536
#define MIN_COUNT 1
#define INIT_VALUE	(T_max,T_delay,tick)  (((f64)T_max-T_delay)/tick)
#define MAX_DELAY_MS(prescaler) ((((f64)prescaler/F_CPU)*MAX_COUNT)*1000UL)
#define MIN_DELAY_MS(prescaler) ((((f64)prescaler/F_CPU)*MIN_COUNT)*1000UL)
#define MAX_DELAY_US(prescaler) ((((f64)prescaler/F_CPU)*MAX_COUNT)*1000000UL)
#define MIN_DELAY_US(prescaler) ((((f64)prescaler/F_CPU)*MIN_COUNT)*1000000UL)


//pre_scaler values for TIMER0
#define P_0    0
#define P_1    1
#define P_8    8
#define P_64   64
#define P_256  256
#define P_1024 1024



//timer 1 registers
#define TIMSK	(*((volatile u8*)0x59))	//Timer/Counter Interrupt Mask Register – TIMSK
#define TIFR	(*((volatile u8*)0x58))	//Timer/Counter Interrupt Flag Register – TIFR
#define TCCR1A	(*((volatile u8*)0x4F))
#define TCCR1B	(*((volatile u8*)0x4E))
#define TCNT1H	(*((volatile u8*)0x4D))
#define TCNT1L	(*((volatile u8*)0x4C))
#define TCNT1	(*((volatile u16*)0x4C))
#define OCR1AH	(*((volatile u8*)0x4B))
#define OCR1AL	(*((volatile u8*)0x4A))
#define OCR1A	(*((volatile u16*)0x4A))
#define OCR1BH	(*((volatile u8*)0x49))
#define OCR1BL	(*((volatile u8*)0x48))
#define OCR1B	(*((volatile u16*)0x48))
#define ICR1H	(*((volatile u8*)0x47))
#define ICR1L	(*((volatile u8*)0x46))
#define ICR1	(*((volatile u16*)0x46))


/*======timer1 pin names ====== */
//Timer/Counter1 Control Register A – TCCR1A
#define WGM10	0
#define WGM11	1
#define FOC1B	2
#define FOC1A	3
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7
//Timer/Counter1 Control Register B – TCCR1B
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4
#define ICES1	6
#define ICNC1	7
//TIMSK interrupt mask register
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7
//TIFR interrupt flag register
#define TOV0  0
#define OCF0  1
#define TOV1  2
#define OCF1B 3
#define OCF1A 4
#define ICF1  5
#define TOV2  6
#define OCF2  7

//timer ISR definition
#define TMR2_CMP	__vector_4
#define TMR2_OVF	__vector_5
#define TMR1_CPT	__vector_6
#define TMR1_CMP_A	__vector_7
#define TMR1_CMP_B	__vector_8
#define TMR1_OVF	__vector_9
#define TMR0_CMP	__vector_10
#define TMR0_OVF	__vector_11

//Macro defines the ISR
#define ISR_HANDLER(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)

#endif /* TMR_UTILITIES_H_ */