/**
 * @file KPD.h
 * @brief Public header for KPD (Keypad) driver
 * @description Provides APIs to interface with a 4x4 matrix keypad.
 *              Handles key press detection and debouncing.
 * @author Embedded Systems Engineer
 * @date 2026
 */

#ifndef KPD_H_
#define KPD_H_

#include "./MCAL_Common/STD_TYPES.h"


#define NOTPRESSED 0xff


/*==============================================================================
 * Public Functions Prototypes
 *============================================================================*/

/**
 * @brief Initialize the keypad by configuring all row and column pins
 * @return void
 * @details This function must be called before using the keypad.
 *          - Configures row pins as input with internal pull-up resistors enabled
 *          - Configures column pins as output and sets them to HIGH
 * @note Uses DIO_ConnectPullup() for row pins to enable internal pull-up resistors
 * @warning Calling this function more than once may cause unexpected behavior
 */
void KPD_Init(void);

/**
 * @brief Get the key currently being pressed on the keypad
 * @return u8 ASCII character of the pressed key, or 0xFF if no key is pressed
 * @details This function scans the keypad matrix by driving each column LOW one at a time
 *          and reading the row pins. When a key is pressed, the corresponding row pin
 *          will read LOW, allowing detection of the exact key.
 * @note Implements software debouncing to prevent false readings
 * @note Blocking function - waits for debounce delay when key press is detected
 * @warning Returns 0xFF (not a valid ASCII character) when no key is pressed.
 *          Always check the return value against 0xFF before using it.
 */
u8 KPD_u8GetPressed(void);

#endif /* KPD_H_ */