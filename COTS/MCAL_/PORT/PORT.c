/**
 * @file PORT.c
 * @brief Implementation file for PORT initialization driver
 * @description Contains the function definitions for initializing all AVR ports
 *              based on configuration from PORT_cfg.h. Sets up both direction
 *              (DDRx) and initial values (PORTx) registers.
 * @author mohamed-dev222
 * @date 2026
 */

/*==============================================================================
 * Includes
 *============================================================================*/

#include "././LIP/STD_TYPES.h" /* Standard data types (u8, u16, etc.) */
#include "PORT_cfg.h"                    /* Pin configuration settings */
#include "PORT_private.h"                /* Register addresses and concatenation macros */
#include "PORT.h"                        /* Public function prototypes */

/*==============================================================================
 * Public Functions Implementation
 *============================================================================*/

/**
 * @brief Initialize all DIO ports (PORTA, PORTB, PORTC, PORTD)
 * @description Applies direction and initial value settings from configuration:
 *              1. Sets Data Direction Registers (DDRx) for input/output
 *              2. Sets Port Data Registers (PORTx) for initial values
 *              For input pins: writing 1 enables pull-up resistor
 *              For output pins: writing 1 sets HIGH, 0 sets LOW
 * @return void
 * @note Must be called once before any DIO operations
 * @note The order of operations matters: DDR set first, then PORT values
 */
void PORT_voidInit(void)
{
    /*----------------------------------------------------------------------
     * Step 1: Configure Pin Directions (Input/Output)
     *--------------------------------------------------------------------*/
    DDRA_Register = PORTA_DIR;   /* PORTA direction: 1=output, 0=input */
    DDRB_Register = PORTB_DIR;   /* PORTB direction */
    DDRC_Register = PORTC_DIR;   /* PORTC direction */
    DDRD_Register = PORTD_DIR;   /* PORTD direction */
    
    /*----------------------------------------------------------------------
     * Step 2: Configure Initial Values
     *--------------------------------------------------------------------*/
    /* Hint: Setting PORTx register to 1 for input pins enables pull-up resistor
     *       Setting PORTx register for output pins sets the initial output state
     */
    PORTA_Register = PORTA_INITIAL_VALUE;
    PORTB_Register = PORTB_INITIAL_VALUE;
    PORTC_Register = PORTC_INITIAL_VALUE;
    PORTD_Register = PORTD_INITIAL_VALUE;
}