/**
 * @file BUZ.h
 * @brief Public header for Buzzer driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control a buzzer connected to AVR GPIO pins.
 *              Supports both active high and active low configurations.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef BUZ_H_
#define BUZ_H_

#include "././LIP/STD_TYPES.h"

#include "../../MCAL_/DIO/DIO.h"

/*==============================================================================
 * Ports Identification Macros
 *============================================================================*/

#define BUZ_PORTA   0   /**< Buzzer connected to PORTA */
#define BUZ_PORTB   1   /**< Buzzer connected to PORTB */
#define BUZ_PORTC   2   /**< Buzzer connected to PORTC */
#define BUZ_PORTD   3   /**< Buzzer connected to PORTD */

/*==============================================================================
 * Pins Identification Macros (PIN0 to PIN7)
 *============================================================================*/

#define BUZ_PIN0    0   /**< Buzzer connected to pin 0 */
#define BUZ_PIN1    1   /**< Buzzer connected to pin 1 */
#define BUZ_PIN2    2   /**< Buzzer connected to pin 2 */
#define BUZ_PIN3    3   /**< Buzzer connected to pin 3 */
#define BUZ_PIN4    4   /**< Buzzer connected to pin 4 */
#define BUZ_PIN5    5   /**< Buzzer connected to pin 5 */
#define BUZ_PIN6    6   /**< Buzzer connected to pin 6 */
#define BUZ_PIN7    7   /**< Buzzer connected to pin 7 */

/*==============================================================================
 * Buzzer Polarity Configuration
 *============================================================================*/

#define ACTIVE_HIGH 1   /**< Buzzer sounds when pin is HIGH */
#define ACTIVE_LOW  0   /**< Buzzer sounds when pin is LOW */

/*==============================================================================
 * Buzzer Configuration Structure
 *============================================================================*/

/**
 * @brief Buzzer configuration structure
 * @note This structure defines the hardware connection of a buzzer
 *       including its port, pin number, and active polarity
 */
typedef struct 
{
    u8 Port;           /**< Port identifier (BUZ_PORTA to BUZ_PORTD) */
    u8 Pin;            /**< Pin identifier (BUZ_PIN0 to BUZ_PIN7) */
    u8 Active_state;   /**< Active state (ACTIVE_HIGH or ACTIVE_LOW) */
} BUZ_Type;

/*==============================================================================
 * Buzzer Control APIs
 *============================================================================*/

/**
 * @brief Initialize a buzzer pin as output
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @note This function must be called before using other BUZ APIs
 * @warning Invalid port or pin parameters will cause undefined behavior
 */
void BUZ_Init(BUZ_Type BUZ_cfg);

/**
 * @brief Turn ON the buzzer (start sound)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @note The actual pin state depends on Active_state:
 *       - ACTIVE_HIGH: Pin set to HIGH
 *       - ACTIVE_LOW:  Pin set to LOW
 */
void BUZ_ON(BUZ_Type BUZ_cfg);

/**
 * @brief Turn OFF the buzzer (stop sound)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @note The actual pin state depends on Active_state:
 *       - ACTIVE_HIGH: Pin set to LOW
 *       - ACTIVE_LOW:  Pin set to HIGH
 */
void BUZ_OFF(BUZ_Type BUZ_cfg);

/**
 * @brief Toggle the buzzer state (ON->OFF or OFF->ON)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @note The buzzer will change to the opposite state of its current condition
 * @warning Buzzer must be initialized before toggling
 */
void BUZ_Toggle(BUZ_Type BUZ_cfg);

/**
 * @brief Produce a beep sound for a specified duration
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @param duration_ms: Duration of the beep in milliseconds
 * @note This function turns the buzzer ON, waits, then turns it OFF
 * @warning This is a blocking function
 */
void BUZ_Beep(BUZ_Type BUZ_cfg, u16 duration_ms);

#endif /* BUZ_H_ */