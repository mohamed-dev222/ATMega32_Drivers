/**
 * @file MAPPING_program.c
 * @brief Implementation file for Mapping utility
 * @description Contains function definitions for value mapping
 *              between input and output ranges
 * @author mohamed-dev222
 * @date 2026
 */

/*==============================================================================
 * Includes
 *============================================================================*/

#include "STD_TYPES.h"
#include "MAPPING.h"


/*==============================================================================
 * Function Definitions
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
u32 MAPPING_u32GetOutput(MAPPING_CONFIG * mapping_config)
{
    u32 Local_u32OutputValue;

    Local_u32OutputValue =
        (
            (
                (
                    mapping_config->Copy_u32InputValue -
                    mapping_config->Copy_u32InputMin
                )
                *
                (
                    mapping_config->Copy_u32OutputMax -
                    mapping_config->Copy_u32OutputMin
                )
            )
            /
            (
                mapping_config->Copy_u32InputMax -
                mapping_config->Copy_u32InputMin
            )
        )
        +
        mapping_config->Copy_u32OutputMin;

    return Local_u32OutputValue;
}