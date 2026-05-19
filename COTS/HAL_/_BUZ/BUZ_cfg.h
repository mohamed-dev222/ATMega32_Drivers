/**
 * @file BUZ_cfg.h
 * @brief Configuration file for Buzzer driver
 * @description Define all buzzers used in the application
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef BUZ_CFG_H_
#define BUZ_CFG_H_

#include "BUZ.h"

/*==============================================================================
 * Buzzer Configuration Instances
 *============================================================================*/

/**
 * @brief System alert buzzer configuration
 * @note Connected to PORTB, PIN0, Active High
 */
#define BUZ_ALERT    {BUZ_PORTB, BUZ_PIN0, ACTIVE_HIGH}

/**
 * @brief Keypad buzzer configuration (for button feedback)
 * @note Connected to PORTB, PIN1, Active High
 */
#define BUZ_KEYPAD   {BUZ_PORTB, BUZ_PIN1, ACTIVE_HIGH}

/**
 * @brief Error buzzer configuration
 * @note Connected to PORTC, PIN2, Active Low
 */
#define BUZ_ERROR    {BUZ_PORTC, BUZ_PIN2, ACTIVE_LOW}

#endif /* BUZ_CFG_H_ */