#include "LED.h"
#include "../../MCAL_/MCAL_Common/STD_TYPES.h"
#include "../../MCAL_/MCAL_Common/BIT_MATH.h"
#include "../../MCAL_/DIO/DIO.h"

void LED_Int(LED_Type LED_cfg)
{
    DIO_setPinDirection(LED_cfg.Port, LED_cfg.Pin, DIO_PIN_OUTPUT);
}
void LED_ON(LED_Type LED_cfg)
{
    if (LED_cfg.Active_state == ACTIVE_HIGH)
    {
        DIO_setPinValue(LED_cfg.Port, LED_cfg.Pin, DIO_PIN_HIGH);
    }else if (LED_cfg.Active_state == ACTIVE_LOW)
    {
        DIO_setPinValue(LED_cfg.Port, LED_cfg.Pin, DIO_PIN_LOW);
    }
}
void LED_OFF(LED_Type LED_cfg)
{
    if (LED_cfg.Active_state == ACTIVE_LOW)
    {
        DIO_setPinValue(LED_cfg.Port, LED_cfg.Pin, DIO_PIN_HIGH);
    }else if (LED_cfg.Active_state == ACTIVE_HIGH)
    {
        DIO_setPinValue(LED_cfg.Port, LED_cfg.Pin, DIO_PIN_LOW);
    }
}
void LED_Toogel(LED_Type LED_cfg)
{
    DIO_togglePinValue(LED_cfg.Port,LED_cfg.Pin);
}