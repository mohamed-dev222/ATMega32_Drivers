/**
 * @file EXTI.c
 * @brief Implementation of External Interrupt (EXTI) driver for AVR
 * @description Provides APIs to configure, enable, disable, and manage 
 *              external interrupts (INT0, INT1, INT2) on ATmega32
 * @author mohamed-dev222
 * @date 2026
 */

#include "../MCAL_Common/STD_TYPES.h"
#include "../MCAL_Common/BIT_MATH.h"

#include "EXTI.h"
#include "EXTI_private.h"
#include "EXTI_cfg.h"

/*==============================================================================
 * Global Variables
 *============================================================================*/

/**
 * @brief Array of function pointers to store callback functions for each EXTI line
 * @details Index mapping:
 *          - Index 0: EXTI_LINE0 (INT0)
 *          - Index 1: EXTI_LINE1 (INT1)
 *          - Index 2: EXTI_LINE2 (INT2)
 * @note Initialized to NULL by default
 */
void (*EXTI_CallBack[3])(void) = { NULL };

/*==============================================================================
 * Public Functions Implementation
 *============================================================================*/

/**
 * @brief Initialize the External Interrupt based on pre-build configuration
 * @return void
 * @details This function uses compile-time configuration from EXTI_cfg.h:
 *          - EXTI_LINE: Selects which interrupt line to configure (LINE0, LINE1, LINE2)
 *          - EXTI_SENSE_MODE: Selects trigger condition (LOW_LEVEL, ON_CHANGE, 
 *            FALLING_EDGE, RISING_EDGE)
 * @note This is a pre-build configuration approach (using #if directives)
 * @warning Must define EXTI_LINE and EXTI_SENSE_MODE in EXTI_cfg.h before compilation
 */
void EXTI_voidInit(void)
{
    #ifdef EXTI_LINE

        /* Configure EXTI line based on pre-build settings */
        #if EXTI_LINE == EXTI_LINE1

            /* Configure sense mode for INT1 (pins ISC11, ISC10 in MCUCR register) */
            #if     EXTI_SENSE_MODE == EXTI_LOW_LEVEL
                CLR_BIT(MCUCR_REG, 2); CLR_BIT(MCUCR_REG, 3);
            #elif   EXTI_SENSE_MODE == EXTI_ON_CHANGE
                SET_BIT(MCUCR_REG, 2); CLR_BIT(MCUCR_REG, 3);
            #elif   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
                CLR_BIT(MCUCR_REG, 2); SET_BIT(MCUCR_REG, 3);
            #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
                SET_BIT(MCUCR_REG, 2); SET_BIT(MCUCR_REG, 3);
            #endif

        #elif EXTI_LINE == EXTI_LINE0

            /* Configure sense mode for INT0 (pins ISC00, ISC01 in MCUCR register) */
            #if     EXTI_SENSE_MODE == EXTI_LOW_LEVEL
                CLR_BIT(MCUCR_REG, 0); CLR_BIT(MCUCR_REG, 1);
            #elif   EXTI_SENSE_MODE == EXTI_ON_CHANGE
                SET_BIT(MCUCR_REG, 0); CLR_BIT(MCUCR_REG, 1);
            #elif   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
                CLR_BIT(MCUCR_REG, 0); SET_BIT(MCUCR_REG, 1);
            #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
                SET_BIT(MCUCR_REG, 0); SET_BIT(MCUCR_REG, 1);
            #endif

        #elif EXTI_LINE == EXTI_LINE2

            /* Configure sense mode for INT2 (pin ISC2 in MCUCSR register) */
            #if     EXTI_SENSE_MODE == EXTI_FALLING_EDGE
                CLR_BIT(MCUCSR_REG, 6);
            #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
                SET_BIT(MCUCSR_REG, 6);
            #endif

        #else
            #error "Wrong EXTI_LINE configuration option"
        #endif

    #endif
}

/**
 * @brief Set the trigger sense mode for a specific external interrupt line
 * @param Copy_u8SenseMode: Trigger mode selection
 *                          Options:
 *                          - EXTI_LOW_LEVEL
 *                          - EXTI_ON_CHANGE
 *                          - EXTI_FALLING_EDGE
 *                          - EXTI_RISING_EDGE
 * @param Copy_u8Line: External interrupt line
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return void
 * @note This is a post-build configuration approach (runtime configurable)
 * @warning For EXTI_LINE2, only FALLING_EDGE and RISING_EDGE modes are supported
 */
void EXTI_voidSetSignalLatch(u8 Copy_u8SenseMode, u8 Copy_u8Line)
{
    /* Configure sense mode for INT0 or INT1 */
    if (Copy_u8Line >= EXTI_LINE0 && Copy_u8Line <= EXTI_LINE1)
    {
        /* Calculate bit position: INT0 uses bits 0-1, INT1 uses bits 2-3 */
        Copy_u8Line = (6 - Copy_u8Line) * -2;

        switch (Copy_u8SenseMode)
        {
            case EXTI_LOW_LEVEL:
                CLR_BIT(MCUCR_REG, Copy_u8Line);
                CLR_BIT(MCUCR_REG, Copy_u8Line + 1);
                break;
            case EXTI_ON_CHANGE:
                SET_BIT(MCUCR_REG, Copy_u8Line);
                CLR_BIT(MCUCR_REG, Copy_u8Line + 1);
                break;
            case EXTI_FALLING_EDGE:
                CLR_BIT(MCUCR_REG, Copy_u8Line);
                SET_BIT(MCUCR_REG, Copy_u8Line + 1);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCR_REG, Copy_u8Line);
                SET_BIT(MCUCR_REG, Copy_u8Line + 1);
                break;
            default:
                /* Invalid sense mode - do nothing */
                break;
        }
    }
    /* Configure sense mode for INT2 */
    else
    {
        switch (Copy_u8SenseMode)
        {
            case EXTI_FALLING_EDGE:
                CLR_BIT(MCUCSR_REG, 6);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCSR_REG, 6);
                break;
            default:
                /* INT2 only supports edge triggering */
                break;
        }
    }
}

/**
 * @brief Disable a specific external interrupt line
 * @param Copy_u8Line: External interrupt line to disable
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return status_t: OK if successful, NOK if invalid line parameter
 * @note Uses GICR register (General Interrupt Control Register)
 */
u8 EXTI_voidDisableInterrupt(u8 Copy_u8Line)
{
    u8 Local_u8ErrorState = OK;
    
    /* Valid lines are bits 5-7 in GICR (INT0=6, INT1=7, INT2=5) */
    if ((Copy_u8Line >= EXTI_LINE2) && (Copy_u8Line <= EXTI_LINE1))
    {
        CLR_BIT(GICR_REG, Copy_u8Line);
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    
    return Local_u8ErrorState;
}

/**
 * @brief Enable a specific external interrupt line
 * @param Copy_u8Line: External interrupt line to enable
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return status_t: OK if successful, NOK if invalid line parameter
 * @note Uses GICR register (General Interrupt Control Register)
 */
u8 EXTI_voidEnableInterrupt(u8 Copy_u8Line)
{
    u8 Local_u8ErrorState = OK;
    
    /* Valid lines are bits 5-7 in GICR (INT0=6, INT1=7, INT2=5) */
    if ((Copy_u8Line >= EXTI_LINE2) && (Copy_u8Line <= EXTI_LINE1))
    {
        SET_BIT(GICR_REG, Copy_u8Line);
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    
    return Local_u8ErrorState;
}

/**
 * @brief Clear the interrupt flag for a specific EXTI line
 * @param Copy_u8Line: External interrupt line
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return void
 * @note Writing logic 1 to GIFR register clears the flag
 */
void EXTI_voidClearFlag(u8 Copy_u8Line)
{
    SET_BIT(GIFR_REG, Copy_u8Line);
}

/**
 * @brief Get the current status of the interrupt flag for a specific EXTI line
 * @param Copy_u8Line: External interrupt line
 *                     Options:
 *                     - EXTI_LINE0 (INT0)
 *                     - EXTI_LINE1 (INT1)
 *                     - EXTI_LINE2 (INT2)
 * @return u8: 1 if flag is set (interrupt pending), 0 if clear
 */
u8 EXTI_u8GetFlag(u8 Copy_u8Line)
{
    return GET_BIT(GIFR_REG, Copy_u8Line);
}

/**
 * @brief Register a callback function to be executed when the interrupt occurs
 * @param Copy_pvoidCallBack: Pointer to the callback function (ISR in application)
 * @param Copy_u8EXTILine: External interrupt line
 *                         Options:
 *                         - EXTI_LINE0 (INT0)
 *                         - EXTI_LINE1 (INT1)
 *                         - EXTI_LINE2 (INT2)
 * @return void
 * @note The callback function will be called from the ISR context
 * @warning Keep callback functions short and avoid blocking operations
 */
void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void), u8 Copy_u8EXTILine)
{
    if (Copy_pvoidCallBack != NULL)
    {
        EXTI_CallBack[Copy_u8EXTILine] = Copy_pvoidCallBack;
    }
}

/*==============================================================================
 * ISR (Interrupt Service Routine) Implementations
 *============================================================================*/

/**
 * @brief ISR for External Interrupt 0 (INT0)
 * @details Vector number: 1 (__vector_1)
 *          Corresponds to INT0 in AVR
 */
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if (EXTI_CallBack[0] != NULL)
    {
        EXTI_CallBack[0]();           /* Execute user callback */
        EXTI_voidClearFlag(EXTI_LINE0); /* Clear interrupt flag */
    }
}

/**
 * @brief ISR for External Interrupt 1 (INT1)
 * @details Vector number: 2 (__vector_2)
 *          Corresponds to INT1 in AVR
 */
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if (EXTI_CallBack[1] != NULL)
    {
        EXTI_CallBack[1]();           /* Execute user callback */
        EXTI_voidClearFlag(EXTI_LINE1); /* Clear interrupt flag */
    }
}

/**
 * @brief ISR for External Interrupt 2 (INT2)
 * @details Vector number: 3 (__vector_3)
 *          Corresponds to INT2 in AVR
 */
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    if (EXTI_CallBack[2] != NULL)
    {
        EXTI_CallBack[2]();           /* Execute user callback */
        EXTI_voidClearFlag(EXTI_LINE2); /* Clear interrupt flag */
    }
}