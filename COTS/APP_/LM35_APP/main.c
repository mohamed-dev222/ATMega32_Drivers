#include "../HAL_/_LED/LED.h"
#include "../HAL_/_LM35/LM35.h"

#include "../MCAL_/ADC/ADC.h"

int main(void)
{
    ADC_voidInit();

    LED_Type LED1 =
    {
        LED_PORTB,
        LED_PIN0,
        ACTIVE_HIGH
    };

    LED_Int(LED1);

    u8 Temp = 0;

    LM35_CONFIG LM35_1 =
    {
        ADC_CHANNEL0,
        5,                      // Voltage Reference = 5V
        ADC_RESOLUTION_10_BIT
    };

    while(1)
    {
        LM35_u8GetTemp(&LM35_1, &Temp);

        if(Temp > 30)
        {
            LED_ON(LED1);
        }
        else
        {
            LED_OFF(LED1);
        }
    }
}