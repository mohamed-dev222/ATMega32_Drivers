/**
 * @file DIO_cfg.h
 * @brief Configuration header for DIO driver Contains all user-configurable definitions and macros
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*==============================================================================
 * Ports Identification Macros
 *============================================================================*/
#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

/*==============================================================================
 * Pins Identification Macros (PIN0 to PIN7)
 *============================================================================*/
#define DIO_PIN0    0
#define DIO_PIN1    1
#define DIO_PIN2    2
#define DIO_PIN3    3
#define DIO_PIN4    4
#define DIO_PIN5    5
#define DIO_PIN6    6
#define DIO_PIN7    7

/*==============================================================================
 * Pin Direction Options
 *============================================================================*/
#define DIO_PIN_OUTPUT  1   /* Set pin as output */
#define DIO_PIN_INPUT   0   /* Set pin as input */

/*==============================================================================
 * Pin Value Options (Output High/Low, Input Pull-up status)
 *============================================================================*/
#define DIO_PIN_HIGH    1   /* Set pin high (output) or enable pull-up (input) */
#define DIO_PIN_LOW     0   /* Set pin low (output) or disable pull-up (input) */

/*==============================================================================
 * Port Direction Options (For bulk operations)
 *============================================================================*/
#define DIO_PORT_OUTPUT 0xFF   /* Set entire port as output */
#define DIO_PORT_INPUT  0x00   /* Set entire port as input */

/*==============================================================================
 * Port Value Options
 *============================================================================*/
#define DIO_PORT_HIGH   0xFF   /* Set all pins high */
#define DIO_PORT_LOW    0x00   /* Set all pins low */

#endif /* DIO_CFG_H_ */