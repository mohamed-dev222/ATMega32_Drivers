/**
 * @file EXTI_private.h
 * @brief Private header for EXTI (External Interrupt) driver
 * @description Contains register addresses, bit definitions, and internal macros.
 *              This file should NOT be included by user application code.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/*==============================================================================
 * Memory-Mapped Register Addresses
 *============================================================================*/

/**
 * @def MCUCR_REG
 * @brief MCU Control Register
 * @address 0x55
 * @details Controls interrupt sense control for INT0 and INT1:
 *          - Bit 0: ISC00 (INT0 sense control bit 0)
 *          - Bit 1: ISC01 (INT0 sense control bit 1)
 *          - Bit 2: ISC10 (INT1 sense control bit 0)
 *          - Bit 3: ISC11 (INT1 sense control bit 1)
 * @note Refer to ATmega32 datasheet for detailed bit descriptions
 */
#define MCUCR_REG   *((volatile u8 *)0x55)

/**
 * @def MCUCSR_REG
 * @brief MCU Control and Status Register
 * @address 0x54
 * @details Controls interrupt sense control for INT2:
 *          - Bit 6: ISC2 (INT2 sense control)
 * @note Refer to ATmega32 datasheet for detailed bit descriptions
 */
#define MCUCSR_REG  *((volatile u8 *)0x54)

/**
 * @def GICR_REG
 * @brief General Interrupt Control Register
 * @address 0x5B
 * @details Enables/disables external interrupts:
 *          - Bit 5: INT2 (Enable/disable INT2)
 *          - Bit 6: INT0 (Enable/disable INT0)
 *          - Bit 7: INT1 (Enable/disable INT1)
 * @note Refer to ATmega32 datasheet for detailed bit descriptions
 */
#define GICR_REG    *((volatile u8 *)0x5B)

/**
 * @def GIFR_REG
 * @brief General Interrupt Flag Register
 * @address 0x5A
 * @details Contains interrupt flags for external interrupts:
 *          - Bit 5: INTF2 (INT2 interrupt flag)
 *          - Bit 6: INTF0 (INT0 interrupt flag)
 *          - Bit 7: INTF1 (INT1 interrupt flag)
 * @note Writing logic 1 to a flag bit clears it
 */
#define GIFR_REG    *((volatile u8 *)0x5A)

/*==============================================================================
 * Bit Position Definitions (for readability)
 *============================================================================*/

/**
 * @def ISC00
 * @brief INT0 sense control bit 0 (position 0 in MCUCR)
 */
#define ISC00   0

/**
 * @def ISC01
 * @brief INT0 sense control bit 1 (position 1 in MCUCR)
 */
#define ISC01   1

/**
 * @def ISC10
 * @brief INT1 sense control bit 0 (position 2 in MCUCR)
 */
#define ISC10   2

/**
 * @def ISC11
 * @brief INT1 sense control bit 1 (position 3 in MCUCR)
 */
#define ISC11   3

/**
 * @def ISC2
 * @brief INT2 sense control bit (position 6 in MCUCSR)
 */
#define ISC2    6

/**
 * @def INT2_BIT
 * @brief INT2 enable/flag bit position (5 in GICR/GIFR)
 */
#define INT2_BIT    5

/**
 * @def INT0_BIT
 * @brief INT0 enable/flag bit position (6 in GICR/GIFR)
 */
#define INT0_BIT    6

/**
 * @def INT1_BIT
 * @brief INT1 enable/flag bit position (7 in GICR/GIFR)
 */
#define INT1_BIT    7

#endif /* EXTI_PRIVATE_H_ */