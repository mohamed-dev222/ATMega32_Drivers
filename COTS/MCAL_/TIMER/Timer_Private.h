/**
 * @file Timer_Private.h
 * @brief Private register definitions for AVR Timer Driver
 * @note Uses AVR Datasheet naming convention (TCCR0, TCNT0, etc.)
 * @warning This file should ONLY be included by Timer.c
 * 
 * @defgroup TimerPrivate Private Register Definitions
 * @{
 */

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

#include "../../LIP/STD_TYPES.h"

#define SREG    (*((volatile u8 *)0x5F))
#define TIMSK   (*((volatile u8 *)0x59))
#define TIFR    (*((volatile u8 *)0x58))

#define TCCR0   (*((volatile u8 *)0x53))
#define TCNT0   (*((volatile u8 *)0x52))
#define OCR0    (*((volatile u8 *)0x5C))

#define TCCR1A  (*((volatile u8 *)0x4F))
#define TCCR1B  (*((volatile u8 *)0x4E))
#define TCNT1L  (*((volatile u8 *)0x4C))
#define TCNT1H  (*((volatile u8 *)0x4D))
#define TCNT1   (*((volatile u16 *)0x4C))
#define OCR1AL  (*((volatile u8 *)0x4A))
#define OCR1AH  (*((volatile u8 *)0x4B))
#define OCR1A   (*((volatile u16 *)0x4A))
#define OCR1BL  (*((volatile u8 *)0x48))
#define OCR1BH  (*((volatile u8 *)0x49))
#define OCR1B   (*((volatile u16 *)0x48))
#define ICR1L   (*((volatile u8 *)0x46))
#define ICR1H   (*((volatile u8 *)0x47))
#define ICR1    (*((volatile u16 *)0x46))

#define TCCR2   (*((volatile u8 *)0x45))
#define TCNT2   (*((volatile u8 *)0x44))
#define OCR2    (*((volatile u8 *)0x43))

#define WDTCR   (*((volatile u8 *)0x41))

#define SREG_I  7
#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOIE2   6
#define OCIE2   7

#define TOV0    0
#define OCF0    1
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
#define TOV2    6
#define OCF2    7

#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

#define TIMER0_TCCR   TCCR0
#define TIMER0_TCNT   TCNT0
#define TIMER0_OCR    OCR0
#define TIMER1_TCCRA  TCCR1A
#define TIMER1_TCCRB  TCCR1B
#define TIMER1_TCNTL  TCNT1L
#define TIMER1_TCNTH  TCNT1H
#define TIMER1_TCNT   TCNT1
#define TIMER1_OCR1AL OCR1AL
#define TIMER1_OCR1AH OCR1AH
#define TIMER1_OCR1A  OCR1A
#define TIMER1_OCR1BL OCR1BL
#define TIMER1_OCR1BH OCR1BH
#define TIMER1_OCR1B  OCR1B
#define TIMER1_ICR1L  ICR1L
#define TIMER1_ICR1H  ICR1H
#define TIMER1_ICR1   ICR1
#define TIMER2_TCCR   TCCR2
#define TIMER2_TCNT   TCNT2
#define TIMER2_OCR    OCR2

#endif /* TIMER_PRIVATE_H */
