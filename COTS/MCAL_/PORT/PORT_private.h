/**
 * @file PORT_PRIVATE.h
 * @brief Private header for PORT driver - internal register mappings and macros
 * @description Contains AVR register addresses, bit concatenation utilities,
 *              and compiled direction/initial values from configuration.
 *              This file should NOT be included directly by user application.
 * @author mohamed-dev222
 * @date 2026
 */
#ifndef PORT_PRIVATE_H_
#define PORT_PRIVATE_H_

/*==============================================================================
 * AVR Port Registers Memory Mapping
 *============================================================================*/

/**
 * @brief Data Direction Registers (DDRx) - Control pin direction (input/output)
 * @note DDRx register addresses for ATmega32/16/8 family
 * @warning These register definitions might be redundant if DIO driver uses
 *          standard AVR headers. Consider removing if using <avr/io.h>
 */
/*  Hint : we could delete that from DIO Driver  */
#define DDRA_Register 		*((volatile u8*)0x3a)
#define DDRB_Register		*((volatile u8*)0x37)
#define DDRC_Register		*((volatile u8*)0x34)
#define DDRD_Register		*((volatile u8*)0x31)

/**
 * @brief Port Data Registers (PORTx) - Control output value / pull-up state
 * @note For output pins: write HIGH/LOW
 *       For input pins: write 1 to enable pull-up, 0 to disable
 */
#define PORTA_Register		*((volatile u8*)0x3b)
#define PORTB_Register		*((volatile u8*)0x38)
#define PORTC_Register		*((volatile u8*)0x35)
#define PORTD_Register		*((volatile u8*)0x32)



/*==============================================================================
 * Bit Concatenation Macros
 *============================================================================*/

/**
 * @def CONC(b7,b6,b5,b4,b3,b2,b1,b0)
 * @brief Concatenate 8 individual bits into a single byte value
 * @param b7 Most significant bit (bit 7)
 * @param b6 Bit 6
 * @param b5 Bit 5
 * @param b4 Bit 4
 * @param b3 Bit 3
 * @param b2 Bit 2
 * @param b1 Bit 1
 * @param b0 Least significant bit (bit 0)
 * @return 8-bit value formed by concatenation
 * @example CONC(1,0,1,0,1,0,1,0) -> 0b10101010 (0xAA)
 * @warning Uses compiler-specific binary literal extension (0b prefix)
 */

#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)

/**
 * @def CONC_HELPER
 * @brief Internal helper macro for CONC - performs actual concatenation
 * @hideinitializer
 */
#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0


/*==============================================================================
 * Compiled Port Direction Values
 *============================================================================*/

/**
 * @brief Pre-compiled direction byte for PORTA (0=input, 1=output)
 * @note Generated from PORTA_PIN0_DIR to PORTA_PIN7_DIR in PORT_CONFIG.h
 */
#define PORTA_DIR				CONC(PORTA_PIN7_DIR,PORTA_PIN6_DIR,PORTA_PIN5_DIR,PORTA_PIN4_DIR,PORTA_PIN3_DIR,PORTA_PIN2_DIR,PORTA_PIN1_DIR,PORTA_PIN0_DIR)

/**
 * @brief Pre-compiled direction byte for PORTB
 */
#define PORTB_DIR				CONC(PORTB_PIN7_DIR,PORTB_PIN6_DIR,PORTB_PIN5_DIR,PORTB_PIN4_DIR,PORTB_PIN3_DIR,PORTB_PIN2_DIR,PORTB_PIN1_DIR,PORTB_PIN0_DIR)

/**
 * @brief Pre-compiled direction byte for PORTC
 */
#define PORTC_DIR				CONC(PORTC_PIN7_DIR,PORTC_PIN6_DIR,PORTC_PIN5_DIR,PORTC_PIN4_DIR,PORTC_PIN3_DIR,PORTC_PIN2_DIR,PORTC_PIN1_DIR,PORTC_PIN0_DIR)

/**
 * @brief Pre-compiled direction byte for PORTD
 */
#define PORTD_DIR				CONC(PORTD_PIN7_DIR,PORTD_PIN6_DIR,PORTD_PIN5_DIR,PORTD_PIN4_DIR,PORTD_PIN3_DIR,PORTD_PIN2_DIR,PORTD_PIN1_DIR,PORTD_PIN0_DIR)


/*==============================================================================
 * Compiled Port Initial Values
 *============================================================================*/

/**
 * @brief Pre-compiled initial value byte for PORTA
 * @note These are the startup values applied during PORT_voidInit()
 * @note Values can be changed at runtime using DIO driver
 */
#define PORTA_INITIAL_VALUE		CONC(PORTA_PIN7_INITIAL_VALUE,PORTA_PIN6_INITIAL_VALUE,PORTA_PIN5_INITIAL_VALUE,PORTA_PIN4_INITIAL_VALUE,PORTA_PIN3_INITIAL_VALUE,PORTA_PIN2_INITIAL_VALUE,PORTA_PIN1_INITIAL_VALUE,PORTA_PIN0_INITIAL_VALUE)

/**
 * @brief Pre-compiled initial value byte for PORTB
 */
#define PORTB_INITIAL_VALUE		CONC(PORTB_PIN7_INITIAL_VALUE,PORTB_PIN6_INITIAL_VALUE,PORTB_PIN5_INITIAL_VALUE,PORTB_PIN4_INITIAL_VALUE,PORTB_PIN3_INITIAL_VALUE,PORTB_PIN2_INITIAL_VALUE,PORTB_PIN1_INITIAL_VALUE,PORTB_PIN0_INITIAL_VALUE)

/**
 * @brief Pre-compiled initial value byte for PORTC
 */
#define PORTC_INITIAL_VALUE		CONC(PORTC_PIN7_INITIAL_VALUE,PORTC_PIN6_INITIAL_VALUE,PORTC_PIN5_INITIAL_VALUE,PORTC_PIN4_INITIAL_VALUE,PORTC_PIN3_INITIAL_VALUE,PORTC_PIN2_INITIAL_VALUE,PORTC_PIN1_INITIAL_VALUE,PORTC_PIN0_INITIAL_VALUE)

/**
 * @brief Pre-compiled initial value byte for PORTD
 */
#define PORTD_INITIAL_VALUE		CONC(PORTD_PIN7_INITIAL_VALUE,PORTD_PIN6_INITIAL_VALUE,PORTD_PIN5_INITIAL_VALUE,PORTD_PIN4_INITIAL_VALUE,PORTD_PIN3_INITIAL_VALUE,PORTD_PIN2_INITIAL_VALUE,PORTD_PIN1_INITIAL_VALUE,PORTD_PIN0_INITIAL_VALUE)

#endif /* PORT_PRIVATE_H_ */

