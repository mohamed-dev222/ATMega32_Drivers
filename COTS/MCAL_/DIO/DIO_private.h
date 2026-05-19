/**
 * @file DIO_private.h
 * @brief Private definitions for DIO driver (ATmega32 registers mapping)
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*==============================================================================
 * AVR ATMega32 Registers Addresses (Memory Mapped)
 *============================================================================*/

/* PORTA Registers */
#define PORTA *((volatile u8*)0x3B)   /* Data Register  - Write output value */
#define DDRA  *((volatile u8*)0x3A)   /* Direction Register - Set pin direction */
#define PINA  *((volatile u8*)0x39)   /* Input Pins Register - Read pin state */

/* PORTB Registers */
#define PORTB *((volatile u8*)0x38)
#define DDRB  *((volatile u8*)0x37)
#define PINB  *((volatile u8*)0x36)

/* PORTC Registers */
#define PORTC *((volatile u8*)0x35)
#define DDRC  *((volatile u8*)0x34)
#define PINC  *((volatile u8*)0x33)

/* PORTD Registers */
#define PORTD *((volatile u8*)0x32)
#define DDRD  *((volatile u8*)0x31)
#define PIND  *((volatile u8*)0x30)

/*==============================================================================
 * Arrays of pointers to access registers by index (PORT0..PORT3)
 * These arrays allow generic access to hardware registers
 *============================================================================*/

static volatile u8* const PORT_REG[] = {
    &PORTA,   /* Index 0 corresponds to DIO_PORTA */
    &PORTB,   /* Index 1 corresponds to DIO_PORTB */
    &PORTC,   /* Index 2 corresponds to DIO_PORTC */
    &PORTD    /* Index 3 corresponds to DIO_PORTD */
};

static volatile u8* const DDR_REG[] = {
    &DDRA,
    &DDRB,
    &DDRC,
    &DDRD
};

static volatile u8* const PIN_REG[] = {
    &PINA,
    &PINB,
    &PINC,
    &PIND
};

#endif /* DIO_PRIVATE_H_ */