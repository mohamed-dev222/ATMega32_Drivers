#include "../HAL_/_LED/LED.h"
// #include "util/delay.h"

void main(void)
{
    LED_Type LED1 = {LED_PORTA, LED_PIN0, ACTIVE_HIGH};
    LED_Type LED2 = {LED_PORTA, LED_PIN2, ACTIVE_HIGH};
    LED_Type LED3 = {LED_PORTA, LED_PIN3, ACTIVE_HIGH};

    LED_Int(LED1);
    LED_Int(LED2);
    LED_Int(LED3);

    s8 Count=1;
    while(1)
    {
        if (Count % 1 == 0)
        {
            LED_Toogel(LED1);
        }
        else if (Count % 2 == 0)
        {
            LED_Toogel(LED2);
        }
        else if (Count % 3 == 0)
        {
            LED_Toogel(LED3);
        }
        Count++;
        _delay_ms(1000);

    }
}