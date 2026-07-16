/**
 * @file LM35.h
 * @brief Interface file for LM35 temperature sensor driver
 * @description Contains LM35 configuration structure, macros,
 *              and function prototypes
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef LM35_H_
#define LM35_H_

/*==============================================================================
 * Includes
 *============================================================================*/

/* Add required includes here if needed */
/* #include "STD_TYPES.h" */


/*==============================================================================
 * Macros
 *============================================================================*/

/**
 * @brief ADC 10-bit resolution
 */
#define ADC_RESOLUTION_10_BIT    0

/**
 * @brief ADC 8-bit resolution
 */
#define ADC_RESOLUTION_8_BIT     1


/*==============================================================================
 * Data Types
 *============================================================================*/

/**
 * @brief LM35 configuration structure
 * @note Used to configure ADC channel, voltage reference,
 *       and ADC resolution for LM35 sensor
 */
typedef struct
{
    u8 Copy_u8LM35Channel;

    /**
     * @brief ADC voltage reference
     * @note Examples: 5V, 2.56V, External Reference
     */
    u8 Copy_u8ADCVoltageReference;

    /**
     * @brief ADC resolution selection
     * @note ADC_RESOLUTION_10_BIT or ADC_RESOLUTION_8_BIT
     */
    u8 Copy_u8ADCResolution;

} LM35_CONFIG;


/*==============================================================================
 * Function Prototypes
 *============================================================================*/

/**
 * @brief Read temperature from LM35 sensor
 *
 * @param[in]  lm35 Pointer to LM35 configuration structure
 * @param[out] Copy_u8TempValue Pointer to store temperature value
 *
 * @return Status of operation
 * @retval 0 Failed
 * @retval 1 Success
 */
u8 LM35_u8GetTemp(LM35_CONFIG * lm35, u8 * Copy_u8TempValue);

#endif /* LM35_H_ */