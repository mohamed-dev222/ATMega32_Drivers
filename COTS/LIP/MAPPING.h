/**
 * @file MAPPING.h
 * @brief Interface file for Mapping utility
 * @description Contains configuration structure and function
 *              prototype for value mapping operations
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef MAPPING_H_
#define MAPPING_H_
#include "STD_TYPES.h"
/*==============================================================================
 * Data Types
 *============================================================================*/

/**
 * @brief Mapping configuration structure
 * @note Used to map an input value from one range
 *       to another output range
 */
typedef struct
{
    /**
     * @brief Minimum input range value
     */
    u32 Copy_u32InputMin;

    /**
     * @brief Maximum input range value
     */
    u32 Copy_u32InputMax;

    /**
     * @brief Minimum output range value
     */
    u32 Copy_u32OutputMin;

    /**
     * @brief Maximum output range value
     */
    u32 Copy_u32OutputMax;

    /**
     * @brief Input value to be mapped
     */
    u32 Copy_u32InputValue;

} MAPPING_CONFIG;


/*==============================================================================
 * Function Prototypes
 *============================================================================*/

/**
 * @brief Map input value from one range to another
 *
 * @param[in] mapping_config Pointer to mapping configuration structure
 *
 * @return Mapped output value
 *
 * @note Formula:
 * Output =
 * ((InputValue - InputMin) * (OutputMax - OutputMin))
 * ---------------------------------------------------- + OutputMin
 *              (InputMax - InputMin)
 */
u32 MAPPING_u32GetOutput(MAPPING_CONFIG * mapping_config);

#endif /* MAPPING_H_ */