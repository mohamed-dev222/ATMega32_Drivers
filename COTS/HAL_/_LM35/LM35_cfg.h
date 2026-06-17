/**
 * @file LM35_cfg.h
 * @brief Configuration file for LM35 temperature sensor driver
 * @description Define LM35 driver configuration options
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef LM35_CFG_H_
#define LM35_CFG_H_

/*==============================================================================
 * LM35 Configuration Options
 *============================================================================*/

/**
 * @brief Configure default ADC resolution
 * @note Options:
 *       - ADC_RESOLUTION_10_BIT
 *       - ADC_RESOLUTION_8_BIT
 */
/* #define LM35_ADC_RESOLUTION    ADC_RESOLUTION_10_BIT */


/**
 * @brief Configure default ADC voltage reference
 * @note Examples:
 *       - AVCC_REFERENCE
 *       - INTERNAL_2_56V
 *       - EXTERNAL_REFERENCE
 */
/* #define LM35_VOLTAGE_REFERENCE    AVCC_REFERENCE */


#endif /* LM35_CFG_H_ */