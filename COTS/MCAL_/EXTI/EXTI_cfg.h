/**
 * @file EXTI_cfg.h
 * @brief Configuration file for EXTI (External Interrupt) driver
 * @description Contains pre-build configuration options for external interrupts.
 *              Modify this file to configure the EXTI driver behavior before compilation.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*==============================================================================
 * External Interrupt Line Selection
 *============================================================================*/

/**
 * @def EXTI_LINE
 * @brief Select which external interrupt line to configure
 * @description This macro determines which EXTI line will be initialized
 *              when EXTI_voidInit() is called.
 * 
 * @options:
 *      - EXTI_LINE0  : Configure External Interrupt 0 (INT0) on PD2
 *      - EXTI_LINE1  : Configure External Interrupt 1 (INT1) on PD3
 *      - EXTI_LINE2  : Configure External Interrupt 2 (INT2) on PB2
 * 
 * @note Only ONE line can be selected at a time in pre-build configuration
 * @warning Changing this value requires recompilation of the project
 */
#define EXTI_LINE   EXTI_LINE0

/*==============================================================================
 * Interrupt Sense Mode (Trigger Condition)
 *============================================================================*/

/**
 * @def EXTI_SENSE_MODE
 * @brief Select the trigger condition for the external interrupt
 * @description This macro determines when the interrupt will be triggered
 *              based on the signal level or edge at the interrupt pin.
 * 
 * @options for EXTI_LINE0 and EXTI_LINE1:
 *      - EXTI_LOW_LEVEL     : Interrupt triggered when pin is LOW
 *      - EXTI_ON_CHANGE     : Interrupt triggered on any logic change (both edges)
 *      - EXTI_FALLING_EDGE  : Interrupt triggered on HIGH to LOW transition
 *      - EXTI_RISING_EDGE   : Interrupt triggered on LOW to HIGH transition
 * 
 * @options for EXTI_LINE2 (INT2 only):
 *      - EXTI_FALLING_EDGE  : Interrupt triggered on HIGH to LOW transition
 *      - EXTI_RISING_EDGE   : Interrupt triggered on LOW to HIGH transition
 *      - NOTE: LOW_LEVEL and ON_CHANGE are NOT supported for INT2
 * 
 * @warning For EXTI_LINE2, ONLY falling edge and rising edge are supported.
 *          Using LOW_LEVEL or ON_CHANGE with INT2 will cause undefined behavior.
 */
#define EXTI_SENSE_MODE  EXTI_FALLING_EDGE

/*==============================================================================
 * Additional Configuration Options (Optional)
 *============================================================================*/

/**
 * @def EXTI_INITIAL_STATE
 * @brief Choose whether the interrupt is initially enabled or disabled
 * @comment Uncomment the desired option to enable/disable interrupt at startup
 * 
 * @options:
 *      - EXTI_ENABLED   : Interrupt enabled after EXTI_voidInit()
 *      - EXTI_DISABLED  : Interrupt disabled after EXTI_voidInit() (requires manual enable)
 * 
 * @note This feature requires implementation in EXTI_voidInit()
 */
/* #define EXTI_INITIAL_STATE    EXTI_ENABLED */

#endif /* EXTI_CONFIG_H_ */