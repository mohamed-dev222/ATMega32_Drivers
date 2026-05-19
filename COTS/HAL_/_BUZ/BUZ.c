/**
 * @file BUZ.c
 * @brief Source file for Buzzer driver
 * @description Implementation of buzzer control APIs using DIO driver
 * @author mohamed-dev222
 * @date 2026
 */

#include "BUZ.h"
#include "../../MCAL_/DIO/DIO.h"
//#include <util/delay.h>

/*==============================================================================
 * Buzzer Control APIs Implementation
 *============================================================================*/

/**
 * @brief Initialize a buzzer pin as output
 * @param BUZ_cfg: Configuration structure defining the buzzer
 */
void BUZ_Init(BUZ_Type BUZ_cfg)
{
    /* Set the buzzer pin as output */
    DIO_setPinDirection(BUZ_cfg.Port, BUZ_cfg.Pin, DIO_PIN_OUTPUT);
    
    /* Ensure buzzer is initially OFF */
    BUZ_OFF(BUZ_cfg);
}

/**
 * @brief Turn ON the buzzer (start sound)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 */
void BUZ_ON(BUZ_Type BUZ_cfg)
{
    if (BUZ_cfg.Active_state == ACTIVE_HIGH)
    {
        DIO_setPinValue(BUZ_cfg.Port, BUZ_cfg.Pin, DIO_PIN_HIGH);
    }
    else
    {
        DIO_setPinValue(BUZ_cfg.Port, BUZ_cfg.Pin, DIO_PIN_LOW);
    }
}

/**
 * @brief Turn OFF the buzzer (stop sound)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 */
void BUZ_OFF(BUZ_Type BUZ_cfg)
{
    if (BUZ_cfg.Active_state == ACTIVE_HIGH)
    {
        DIO_setPinValue(BUZ_cfg.Port, BUZ_cfg.Pin, DIO_PIN_LOW);
    }
    else
    {
        DIO_setPinValue(BUZ_cfg.Port, BUZ_cfg.Pin, DIO_PIN_HIGH);
    }
}

/**
 * @brief Toggle the buzzer state (ON->OFF or OFF->ON)
 * @param BUZ_cfg: Configuration structure defining the buzzer
 */
void BUZ_Toggle(BUZ_Type BUZ_cfg)
{
    DIO_togglePinValue(BUZ_cfg.Port, BUZ_cfg.Pin);
}

/**
 * @brief Produce a beep sound for a specified duration
 * @param BUZ_cfg: Configuration structure defining the buzzer
 * @param duration_ms: Duration of the beep in milliseconds
 */
/*void BUZ_Beep(BUZ_Type BUZ_cfg, u16 duration_ms)
{
    BUZ_ON(BUZ_cfg);
    _delay_ms(duration_ms);
    BUZ_OFF(BUZ_cfg);
}*/