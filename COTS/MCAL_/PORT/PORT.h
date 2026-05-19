/**
 * @file PORT.h
 * @brief Public interface header for PORT initialization driver
 * @description Provides the initialization function for setting up all AVR ports
 *              based on the configuration defined in PORT_CONFIG.h.
 *              This driver handles DDR (direction) and PORT (initial value) registers.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef PORT_INTERFACE_H_
#define PORT_INTERFACE_H_

/*==============================================================================
 * Public Functions Prototypes
 *============================================================================*/

/**
 * @brief Initialize all DIO ports (PORTA, PORTB, PORTC, PORTD) based on configuration
 * @description This function reads the direction and initial value settings from
 *              PORT_CONFIG.h and applies them to the appropriate AVR registers:
 *              - Sets DDRx register for pin directions
 *              - Sets PORTx register for initial values (pull-ups for inputs, 
 *                HIGH/LOW for outputs)
 * @return void
 * @note This function MUST be called once during system startup before using any DIO APIs
 * @note After initialization, pin states can be changed using the DIO driver functions
 * @warning Do not call this function again after runtime as it will override any
 *          changes made by the application using DIO APIs
 */
void PORT_voidInit(void);

#endif /* PORT_INTERFACE_H_ */