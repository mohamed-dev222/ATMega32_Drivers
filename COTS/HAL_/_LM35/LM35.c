/**
 * @file LM35_program.c
 * @brief Implementation file for LM35 temperature sensor driver
 * @description Contains all function definitions for LM35 sensor
 * @author mohamed-dev222
 * @date 2026
 */

/*==============================================================================
 * Includes
 *============================================================================*/

#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"

#include "../../MCAL_/DIO/DIO.h"
#include "../../MCAL_/ADC/ADC.h"

#include "LM35.h"
#include "LM35_private.h"


/*==============================================================================
 * Function Definitions
 *============================================================================*/

/**
 * @brief Read temperature from LM35 sensor
 *
 * @param[in]  lm35 Pointer to LM35 configuration structure
 * @param[out] Copy_u8TempValue Pointer to store temperature value
 *
 * @return Error state
 * @retval OK     Operation completed successfully
 * @retval NOK    Operation failed
 *
 * @note Temperature is calculated based on:
 *       LM35 Output = 10mV / °C
 */
u8 LM35_u8GetTemp(LM35_CONFIG * lm35, u8 * Copy_u8TempValue)
{
    u8 Local_u8ErrorState = OK;

    u16 Local_u16ADCResult;
    u16 Local_u16AnalogValue;

    /**
     * Convert voltage reference from Volt to milliVolt
     * Example:
     * 5V -> 5000mV
     */
    u16 Local_u16ADCReference =
        (lm35->Copy_u8ADCVoltageReference) * 1000;

    /*======================================================================
     * ADC Digital Reading
     *====================================================================*/

    ADC_u8GetResultSync(
        lm35->Copy_u8LM35Channel,
        &Local_u16ADCResult
    );

    /*======================================================================
     * Convert ADC Reading to Analog Voltage
     *====================================================================*/

    if (lm35->Copy_u8ADCResolution == ADC_RESOLUTION_10_BIT)
    {
        Local_u16AnalogValue =
            (u16)(((u32)Local_u16ADCResult *
            (u32)Local_u16ADCReference) / 1024UL);
    }
    else if (lm35->Copy_u8ADCResolution == ADC_RESOLUTION_8_BIT)
    {
        Local_u16AnalogValue =
            (u16)(((u32)Local_u16ADCResult *
            (u32)Local_u16ADCReference) / 256UL);
    }

    /*======================================================================
     * Convert Analog Voltage (mV) to Temperature (°C)
     * LM35: 10mV = 1°C
     *====================================================================*/

    *Copy_u8TempValue = Local_u16AnalogValue / 10;

    return Local_u8ErrorState;
}