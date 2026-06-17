/**
 * @file DIO.h
 * @brief Public header for DIO (Digital Input/Output) driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control AVR GPIO pins
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef DIO_H_
#define DIO_H_

#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"
#include "DIO_cfg.h"

/*==============================================================================
 * Pin Control APIs
 *============================================================================*/

/**
 * @brief Set the direction (input/output) of a specific pin
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8PIN:  DIO_PIN0 to DIO_PIN7
 * @param Copy_u8Direction: DIO_PIN_INPUT or DIO_PIN_OUTPUT
 * @return OK if successful, NOK if invalid parameters
 */
status_t DIO_setPinDirection(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Direction);

/**
 * @brief Set the value (high/low) of a specific pin
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8PIN:  DIO_PIN0 to DIO_PIN7
 * @param Copy_u8Value: DIO_PIN_HIGH or DIO_PIN_LOW
 * @return OK if successful, NOK if invalid parameters
 * @note For input pins: HIGH enables pull-up resistor, LOW disables pull-up
 */
status_t DIO_setPinValue(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Value);

/**
 * @brief Read the current value of a specific pin
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8PIN:  DIO_PIN0 to DIO_PIN7
 * @param Copy_ptrData: Pointer to store the read value (0 or 1)
 * @return OK if successful, NOK if invalid parameters
 */
status_t DIO_getPinValue(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 *Copy_ptrData);

/**
 * @brief Toggle the value of a specific pin (HIGH->LOW or LOW->HIGH)
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8PIN:  DIO_PIN0 to DIO_PIN7
 * @return OK if successful, NOK if invalid parameters
 * @warning Only works correctly if the pin is configured as output
 */
status_t DIO_togglePinValue(u8 Copy_u8PORT, u8 Copy_u8PIN);

/*==============================================================================
 * Port Control APIs (Bulk operations on all 8 pins)
 *============================================================================*/

/**
 * @brief Set the direction for the entire port (all 8 pins at once)
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8Direction: 8-bit value (1=output, 0=input for each bit position)
 *                          Example: 0xFF = all output, 0x00 = all input
 * @return OK if successful, NOK if invalid port
 * @note Use DIO_PORT_OUTPUT (0xFF) or DIO_PORT_INPUT (0x00) macros
 */
status_t DIO_setPortDirection(u8 Copy_u8PORT, u8 Copy_u8Direction);

/**
 * @brief Set the value for the entire port (all 8 pins at once)
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8Value: 8-bit value to write to the port
 * @return OK if successful, NOK if invalid port
 */
status_t DIO_setPortValue(u8 Copy_u8PORT, u8 Copy_u8Value);

/**
 * @brief Read the current value of the entire port
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_ptrData: Pointer to store the 8-bit port value
 * @return OK if successful, NOK if invalid port
 * @note Reads from PIN register (actual pin states, not output latch)
 */
status_t DIO_getPortValue(u8 Copy_u8PORT, u8 *Copy_ptrData);

/**
 * @brief Toggle all pins of a port simultaneously
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @return OK if successful, NOK if invalid port
 * @warning Use only if all pins on the port are configured as outputs
 */
status_t DIO_togglePortValue(u8 Copy_u8PORT);

/**
 * @brief Write value to the lower 4 bits (pins 0:3) of a specific port
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8value: 4-bit value (0x00 to 0x0F) to be written to low nibble
 * @return OK if successful, NOK if invalid port
 * @note This function affects only the lower nibble (bits 0 to 3)
 *       while preserving the upper nibble (bits 4 to 7)
 * @warning Ensure the target pins are configured as outputs
 */
status_t DIO_WriteLowNibbles(u8 Copy_u8PORT, u8 Copy_u8value);

/**
 * @brief Write value to the upper 4 bits (pins 4:7) of a specific port
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8value: 4-bit value (0x00 to 0x0F) to be written to high nibble
 * @return OK if successful, NOK if invalid port
 * @note This function affects only the upper nibble (bits 4 to 7)
 *       while preserving the lower nibble (bits 0 to 3)
 * @warning Ensure the target pins are configured as outputs
 */
status_t DIO_WriteHighNibbles(u8 Copy_u8PORT, u8 Copy_u8value);

/**
 * @brief Enable internal pull-up resistor for a specific input pin
 * @param Copy_u8PORT: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 * @param Copy_u8PIN:  DIO_PIN0 to DIO_PIN7
 * @return OK if successful, NOK if invalid parameters
 * @details This function configures the pin as input and sets its value to HIGH,
 *          which activates the internal pull-up resistor on AVR microcontrollers.
 * @note Equivalent to: DIO_setPinDirection(PORT, PIN, DIO_PIN_INPUT) followed by
 *                     DIO_setPinValue(PORT, PIN, DIO_PIN_HIGH)
 * @warning Only works for pins configured as input. Pull-up has no effect on output pins.
 */
status_t DIO_ConnectPullup(u8 Copy_u8PORT ,u8 Copy_u8PIN);
#endif /* DIO_H_ */