/**
 * @file LM35_program.c
 * @brief Implementation file for LM35 temperature sensor driver
 */

#include "../../LIP/STD_TYPES.h"
#include "../../LIP/BIT_MATH.h"

#include "../../MCAL_/ADC/ADC.h"

#include "LM35.h"
#include "LM35_private.h"

u8 LM35_u8GetTemp(LM35_CONFIG *lm35, u8 *Copy_u8TempValue)
{
    u8 Local_u8ErrorState = OK;

    u16 Local_u16ADCResult = 0;
    u16 Local_u16AnalogValue = 0;
    u16 Local_u16ADCReference;

    if((lm35 == NULL) || (Copy_u8TempValue == NULL))
    {
        return NULL_POINTER;
    }

    /* Convert Volt to mV */
    Local_u16ADCReference = ((u16)lm35->Copy_u8ADCVoltageReference) * 1000U;

    /* Read ADC */
    Local_u8ErrorState = ADC_u8GetResultSync(lm35->Copy_u8LM35Channel,
                                            &Local_u16ADCResult);

    if(Local_u8ErrorState != OK)
    {
        return Local_u8ErrorState;
    }

    if(lm35->Copy_u8ADCResolution == ADC_RESOLUTION_10_BIT)
    {
        Local_u16AnalogValue =
            ((u32)Local_u16ADCResult * Local_u16ADCReference) / 1024UL;
    }
    else
    {
        Local_u16AnalogValue =
            ((u32)Local_u16ADCResult * Local_u16ADCReference) / 256UL;
    }

    /* LM35 : 10mV = 1°C */
    *Copy_u8TempValue = (u8)(Local_u16AnalogValue / 10U);

    return OK;
}