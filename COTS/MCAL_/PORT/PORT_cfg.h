/**
 * @file PORT_CFG.h
 * @brief Public configuration header for DIO port/pin initialization
 * @description This file defines the initial direction and default values
 *              for all pins across PORTA, PORTB, PORTC, and PORTD.
 *              These settings are used during system startup.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

/*==============================================================================
 * Pin Direction Definitions
 *============================================================================*/

/**
 * @def DIO_INPUT
 * @brief Configure pin as input (high impedance)
 */
#define DIO_INPUT  0

/**
 * @def DIO_OUTPUT
 * @brief Configure pin as output (can drive HIGH/LOW)
 */
#define DIO_OUTPUT 1

/**
 * @defgroup PinDirectionOptions Pin Direction Options
 * @brief Available direction settings for each pin
 * @{
 *   DIO_INPUT  - Set pin as digital input
 *   DIO_OUTPUT - Set pin as digital output
 * @}
 */

/*==============================================================================
 * PORTA Pin Directions (8 pins)
 *============================================================================*/

#define PORTA_PIN0_DIR				DIO_INPUT
#define PORTA_PIN1_DIR				DIO_INPUT
#define PORTA_PIN2_DIR				DIO_INPUT
#define PORTA_PIN3_DIR				DIO_INPUT
#define PORTA_PIN4_DIR				DIO_INPUT
#define PORTA_PIN5_DIR				DIO_INPUT
#define PORTA_PIN6_DIR				DIO_INPUT
#define PORTA_PIN7_DIR				DIO_INPUT

/*==============================================================================
 * PORTB Pin Directions (8 pins)
 *============================================================================*/

#define PORTB_PIN0_DIR				DIO_INPUT			
#define PORTB_PIN1_DIR				DIO_INPUT			
#define PORTB_PIN2_DIR				DIO_INPUT			
#define PORTB_PIN3_DIR				DIO_INPUT			
#define PORTB_PIN4_DIR				DIO_INPUT			
#define PORTB_PIN5_DIR				DIO_INPUT			
#define PORTB_PIN6_DIR				DIO_INPUT			
#define PORTB_PIN7_DIR				DIO_INPUT

/*==============================================================================
 * PORTC Pin Directions (8 pins)
 *============================================================================*/

#define PORTC_PIN0_DIR				DIO_INPUT
#define PORTC_PIN1_DIR				DIO_INPUT
#define PORTC_PIN2_DIR				DIO_INPUT
#define PORTC_PIN3_DIR				DIO_INPUT			
#define PORTC_PIN4_DIR				DIO_INPUT			
#define PORTC_PIN5_DIR				DIO_INPUT			
#define PORTC_PIN6_DIR				DIO_INPUT			
#define PORTC_PIN7_DIR				DIO_INPUT

/*==============================================================================
 * PORTD Pin Directions (8 pins)
 *============================================================================*/

#define PORTD_PIN0_DIR				DIO_INPUT			
#define PORTD_PIN1_DIR				DIO_INPUT			
#define PORTD_PIN2_DIR				DIO_INPUT			
#define PORTD_PIN3_DIR				DIO_INPUT			
#define PORTD_PIN4_DIR				DIO_INPUT			
#define PORTD_PIN5_DIR				DIO_INPUT			
#define PORTD_PIN6_DIR				DIO_INPUT			
#define PORTD_PIN7_DIR				DIO_INPUT

/*==============================================================================
 * Pin Initial Value Definitions
 *============================================================================*/

/* Input pin configuration options */
/**
 * @def INPUT_FLOATING
 * @brief Configure input pin with no internal pull-up resistor (high impedance)
 * @note Pin state is determined by external circuitry
 */
#define INPUT_FLOATING 0

/**
 * @def INPUT_PULLUP
 * @brief Configure input pin with internal pull-up resistor enabled
 * @note Pin reads HIGH when externally unconnected
 */
#define INPUT_PULLUP   1

/* Output pin configuration options */
/**
 * @def OUTPUT_LOW
 * @brief Set output pin to 0V (logic LOW)
 */
#define OUTPUT_LOW     0

/**
 * @def OUTPUT_HIGH
 * @brief Set output pin to VCC (logic HIGH, typically 5V or 3.3V)
 */
#define OUTPUT_HIGH    1

/**
 * @defgroup PinInitialValueOptions Pin Initial Value Options
 * @brief Available initial value settings for each pin
 * @{
 *   INPUT_FLOATING - Input pin, pull-up disabled
 *   INPUT_PULLUP   - Input pin, pull-up enabled
 *   OUTPUT_LOW     - Output pin, driven LOW
 *   OUTPUT_HIGH    - Output pin, driven HIGH
 * @}
 */

/**
 * @note These are the initial values applied during system startup.
 *       Values can be changed at runtime using the DIO driver APIs.
 */

/*==============================================================================
 * PORTA Pin Initial Values (8 pins)
 *============================================================================*/

#define PORTA_PIN0_INITIAL_VALUE	INPUT_FLOATING
#define PORTA_PIN1_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN2_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN3_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN4_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN5_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN6_INITIAL_VALUE    INPUT_FLOATING
#define PORTA_PIN7_INITIAL_VALUE	INPUT_FLOATING

/*==============================================================================
 * PORTB Pin Initial Values (8 pins)
 *============================================================================*/

#define PORTB_PIN0_INITIAL_VALUE	INPUT_FLOATING
#define PORTB_PIN1_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN2_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN3_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN4_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN5_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN6_INITIAL_VALUE    INPUT_FLOATING
#define PORTB_PIN7_INITIAL_VALUE	INPUT_FLOATING

/*==============================================================================
 * PORTC Pin Initial Values (8 pins)
 *============================================================================*/

#define PORTC_PIN0_INITIAL_VALUE	INPUT_FLOATING
#define PORTC_PIN1_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN2_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN3_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN4_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN5_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN6_INITIAL_VALUE    INPUT_FLOATING
#define PORTC_PIN7_INITIAL_VALUE	INPUT_FLOATING

/*==============================================================================
 * PORTD Pin Initial Values (8 pins)
 *============================================================================*/

#define PORTD_PIN0_INITIAL_VALUE	INPUT_FLOATING
#define PORTD_PIN1_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN2_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN3_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN4_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN5_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN6_INITIAL_VALUE    INPUT_FLOATING
#define PORTD_PIN7_INITIAL_VALUE	INPUT_FLOATING

/*============================================================================*/
#endif /* PORT_CONFIG_H_ */