/**
 * @file SSD.h
 * @brief Public header for SSD (Seven Segment Display) driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control 7-segment displays connected to AVR GPIO pins.
 *              Supports both common cathode and common anode types.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef SSD_H_
#define SSD_H_

#include "../../MCAL_/MCAL_Common/STD_TYPES.h"

/*==============================================================================
 * Ports Identification Macros
 *============================================================================*/

#define SSD_PORTA   0   /**< SSD data or enable connected to PORTA */
#define SSD_PORTB   1   /**< SSD data or enable connected to PORTB */
#define SSD_PORTC   2   /**< SSD data or enable connected to PORTC */
#define SSD_PORTD   3   /**< SSD data or enable connected to PORTD */

/*==============================================================================
 * Pins Identification Macros (PIN0 to PIN7)
 *============================================================================*/

#define SSD_PIN0    0   /**< SSD enable pin 0 */
#define SSD_PIN1    1   /**< SSD enable pin 1 */
#define SSD_PIN2    2   /**< SSD enable pin 2 */
#define SSD_PIN3    3   /**< SSD enable pin 3 */
#define SSD_PIN4    4   /**< SSD enable pin 4 */
#define SSD_PIN5    5   /**< SSD enable pin 5 */
#define SSD_PIN6    6   /**< SSD enable pin 6 */
#define SSD_PIN7    7   /**< SSD enable pin 7 */

/*==============================================================================
 * SSD Type Configuration
 *============================================================================*/

#define SSD_COMMON_CATHODE 0    /**< SSD turns ON segments with HIGH signal */
#define SSD_COMMON_ANODE   1    /**< SSD turns ON segments with LOW signal */

/*==============================================================================
 * SSD Configuration Structure
 *============================================================================*/

/**
 * @brief SSD configuration structure
 * @note This structure defines the hardware connection of a 7-segment display
 *       including its type (common cathode/anode), data port, and enable pin
 */
typedef struct 
{
    u8 Type;           /**< SSD type: SSD_COMMON_CATHODE or SSD_COMMON_ANODE */
    u8 DataPort;       /**< Port where data lines (a-g) are connected */
    u8 EnablePort;     /**< Port where the enable/control pin is connected */
    u8 EnablePin;      /**< Pin number for the enable/control signal */
} SSD_Type;

/*==============================================================================
 * SSD Control APIs
 *============================================================================*/

/**
 * @brief Initialize the data port of the SSD as output
 * @param Data: SSD configuration structure
 * @note This function configures the entire data port (8 pins) as output
 * @warning Must be called before sending any numbers to the SSD
 */
void SSD_InitDataPort(SSD_Type Data);

/**
 * @brief Display a number on the SSD
 * @param Data: SSD configuration structure
 * @param Value: Number to display (0-9)
 * @note For common cathode: sends positive logic (1=segment ON)
 *       For common anode: sends negative logic (0=segment ON)
 * @warning Value must be between 0 and 9, otherwise behavior is undefined
 */
void SSD_SendNumber(SSD_Type Data, u8 Value);

/**
 * @brief Enable the SSD (turn the display ON)
 * @param Data: SSD configuration structure
 * @note Typically used to activate the SSD by controlling the common pin
 *       or transistor driving the display
 */
void SSD_Enable(SSD_Type Data);

/**
 * @brief Disable the SSD (turn the display OFF)
 * @param Data: SSD configuration structure
 * @note Used to deactivate the SSD, useful for multiplexing
 *       or power saving when display is not needed
 */
void SSD_Desable(SSD_Type Data);

#endif /* SSD_H_ */