/**
 * @file LED.h
 * @brief Public header for LED driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control LEDs connected to AVR GPIO pins.
 *              Supports both active high and active low configurations.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef LED_H_
#define LED_H_

#include "././LIP/STD_TYPES.h"


/*==============================================================================
 * Ports Identification Macros
 *============================================================================*/

#define LED_PORTA   0   /**< LED connected to PORTA */
#define LED_PORTB   1   /**< LED connected to PORTB */
#define LED_PORTC   2   /**< LED connected to PORTC */
#define LED_PORTD   3   /**< LED connected to PORTD */

/*==============================================================================
 * Pins Identification Macros (PIN0 to PIN7)
 *============================================================================*/

#define LED_PIN0    0   /**< LED connected to pin 0 */
#define LED_PIN1    1   /**< LED connected to pin 1 */
#define LED_PIN2    2   /**< LED connected to pin 2 */
#define LED_PIN3    3   /**< LED connected to pin 3 */
#define LED_PIN4    4   /**< LED connected to pin 4 */
#define LED_PIN5    5   /**< LED connected to pin 5 */
#define LED_PIN6    6   /**< LED connected to pin 6 */
#define LED_PIN7    7   /**< LED connected to pin 7 */

/*==============================================================================
 * LED Polarity Configuration
 *============================================================================*/

#define ACTIVE_HIGH 1   /**< LED turns ON when pin is HIGH */
#define ACTIVE_LOW  0   /**< LED turns ON when pin is LOW */

/*==============================================================================
 * LED Configuration Structure
 *============================================================================*/

/**
 * @brief LED configuration structure
 * @note This structure defines the hardware connection of an LED
 *       including its port, pin number, and active polarity
 */
typedef struct 
{
    u8 Port;           /**< Port identifier (LED_PORTA to LED_PORTD) */
    u8 Pin;            /**< Pin identifier (LED_PIN0 to LED_PIN7) */
    u8 Active_state;   /**< Active state (ACTIVE_HIGH or ACTIVE_LOW) */
} LED_Type;

/*==============================================================================
 * LED Control APIs
 *============================================================================*/

/**
 * @brief Initialize an LED pin as output
 * @param LED_cfg: Configuration structure defining the LED
 * @note This function must be called before using other LED APIs
 * @warning Invalid port or pin parameters will cause undefined behavior
 */
void LED_Int(LED_Type LED_cfg);

/**
 * @brief Turn ON the LED
 * @param LED_cfg: Configuration structure defining the LED
 * @note The actual pin state depends on Active_state:
 *       - ACTIVE_HIGH: Pin set to HIGH
 *       - ACTIVE_LOW:  Pin set to LOW
 */
void LED_ON(LED_Type LED_cfg);

/**
 * @brief Turn OFF the LED
 * @param LED_cfg: Configuration structure defining the LED
 * @note The actual pin state depends on Active_state:
 *       - ACTIVE_HIGH: Pin set to LOW
 *       - ACTIVE_LOW:  Pin set to HIGH
 */
void LED_OFF(LED_Type LED_cfg);

/**
 * @brief Toggle the LED state (ON->OFF or OFF->ON)
 * @param LED_cfg: Configuration structure defining the LED
 * @note The LED will change to the opposite state of its current condition
 * @warning LED must be initialized before toggling
 */
void LED_Toogel(LED_Type LED_cfg);

#endif /* LED_H_ */