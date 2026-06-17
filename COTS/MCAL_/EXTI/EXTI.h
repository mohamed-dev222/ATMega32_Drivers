/**
 * @file EXTI_.h
 * @brief Public interface header for EXTI (External Interrupt) driver
 * @description Provides APIs to configure and control external interrupts 
 *              (INT0, INT1, INT2) on AVR microcontrollers (ATmega32)
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include "././LIP/STD_TYPES.h"

/*==============================================================================
 * EXTI Line Definitions
 *============================================================================*/

/**
 * @def EXTI_LINE0
 * @brief External interrupt line 0 (INT0)
 * @details Bit position 6 in GICR/GIFR registers
 */
#define EXTI_LINE0   6

/**
 * @def EXTI_LINE1
 * @brief External interrupt line 1 (INT1)
 * @details Bit position 7 in GICR/GIFR registers
 */
#define EXTI_LINE1   7

/**
 * @def EXTI_LINE2
 * @brief External interrupt line 2 (INT2)
 * @details Bit position 5 in GICR/GIFR registers
 */
#define EXTI_LINE2   5

/*==============================================================================
 * Trigger Sense Modes
 *============================================================================*/

/**
 * @def EXTI_FALLING_EDGE
 * @brief Trigger interrupt on falling edge (HIGH to LOW transition)
 */
#define EXTI_FALLING_EDGE  0

/**
 * @def EXTI_RISING_EDGE
 * @brief Trigger interrupt on rising edge (LOW to HIGH transition)
 */
#define EXTI_RISING_EDGE   1

/**
 * @def EXTI_LOW_LEVEL
 * @brief Trigger interrupt when pin is LOW (level triggered)
 * @note Only available for INT0 and INT1, not for INT2
 */
#define EXTI_LOW_LEVEL     2

/**
 * @def EXTI_ON_CHANGE
 * @brief Trigger interrupt on any logical change (both rising and falling)
 * @note Only available for INT0 and INT1, not for INT2
 */
#define EXTI_ON_CHANGE     3

/*==============================================================================
 * Public Functions Prototypes
 *============================================================================*/

/**
 * @brief Initialize the External Interrupt based on pre-build configuration
 * @return void
 * @details Reads configuration macros (EXTI_LINE, EXTI_SENSE_MODE) from EXTI_cfg.h
 *          and configures the corresponding registers (MCUCR, MCUCSR)
 * @note Must call this function before using any other EXTI APIs
 * @warning Pre-build configuration must be defined in EXTI_cfg.h
 */
void EXTI_voidInit(void);

/**
 * @brief Set the trigger sense mode for a specific external interrupt line (runtime)
 * @param Copy_u8SenseMode: Trigger mode selection
 *                          Options:
 *                          - EXTI_LOW_LEVEL
 *                          - EXTI_ON_CHANGE
 *                          - EXTI_FALLING_EDGE
 *                          - EXTI_RISING_EDGE
 * @param Copy_u8Line: External interrupt line
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return void
 * @note Allows runtime configuration (post-build) without recompilation
 * @warning EXTI_LINE2 supports only FALLING_EDGE and RISING_EDGE modes
 */
void EXTI_voidSetSignalLatch(u8 Copy_u8SenseMode, u8 Copy_u8Line);

/**
 * @brief Enable a specific external interrupt line
 * @param Copy_u8Line: External interrupt line to enable
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return u8: OK (1) if successful, NOK (0) if invalid line parameter
 * @note Enables the interrupt in the GICR (General Interrupt Control Register)
 * @warning Global interrupts (I-bit in SREG) must also be enabled using sei()
 */
status_t EXTI_EnableInterrupt(u8 Copy_u8Line);

/**
 * @brief Disable a specific external interrupt line
 * @param Copy_u8Line: External interrupt line to disable
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return u8: OK (1) if successful, NOK (0) if invalid line parameter
 * @note Disables the interrupt in the GICR (General Interrupt Control Register)
 */
status_t  EXTI_DisableInterrupt(u8 Copy_u8Line);

/**
 * @brief Clear the interrupt flag for a specific EXTI line
 * @param Copy_u8Line: External interrupt line
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return void
 * @note Writing logic 1 to GIFR register clears the pending interrupt flag
 * @note Useful for acknowledging interrupts in polling mode
 */
void EXTI_voidClearFlag(u8 Copy_u8Line);

/**
 * @brief Register a callback function to execute when the interrupt occurs
 * @param Copy_pvoidCallBack: Pointer to the callback function (user ISR)
 * @param Copy_u8EXTILine: External interrupt line
 *                         Options:
 *                         - EXTI_LINE0 (INT0)
 *                         - EXTI_LINE1 (INT1)
 *                         - EXTI_LINE2 (INT2)
 * @return void
 * @details The callback is stored in an array and invoked from the corresponding ISR
 * @note Must be called before the interrupt occurs
 * @warning Keep callback functions short, fast, and avoid blocking operations
 * @warning Callback executes in interrupt context (ISR)
 */
void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void), u8 Copy_u8EXTILine);

#endif /* EXTI_INTERFACE_H_ */