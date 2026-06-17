/**
 * @file EXTI.c
 * @brief Implementation of External Interrupt (EXTI) driver for AVR
 * @description Provides APIs to configure, enable, disable, and manage 
 *              external interrupts (INT0, INT1, INT2) on ATmega32
 * @author mohamed-dev222
 * @date 2026
 */

#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"

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
    /* Configure EXTI line based on pre-build settings */
    #if EXTI_LINE == EXTI_LINE0

        /* Configure sense mode for INT0 (ISC00, ISC01 bits in MCUCR register) */
        #if     EXTI_SENSE_MODE == EXTI_LOW_LEVEL
            CLR_BIT(MCUCR_REG, ISC00); CLR_BIT(MCUCR_REG, ISC01);
        #elif   EXTI_SENSE_MODE == EXTI_ON_CHANGE
            SET_BIT(MCUCR_REG, ISC00); CLR_BIT(MCUCR_REG, ISC01);
        #elif   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
            CLR_BIT(MCUCR_REG, ISC00); SET_BIT(MCUCR_REG, ISC01);

        #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
            SET_BIT(MCUCR_REG, ISC00); SET_BIT(MCUCR_REG, ISC01);
        #else
            #error "Wrong EXTI_SENSE_MODE option for INT0"
        #endif


    #elif EXTI_LINE == EXTI_LINE1

        /* Configure sense mode for INT1 (ISC10, ISC11 bits in MCUCR register) */
        #if     EXTI_SENSE_MODE == EXTI_LOW_LEVEL
            CLR_BIT(MCUCR_REG, ISC10); CLR_BIT(MCUCR_REG, ISC11);
        #elif   EXTI_SENSE_MODE == EXTI_ON_CHANGE
            SET_BIT(MCUCR_REG, ISC10); CLR_BIT(MCUCR_REG, ISC11);
        #elif   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
            CLR_BIT(MCUCR_REG, ISC10); SET_BIT(MCUCR_REG, ISC11);
        #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
            SET_BIT(MCUCR_REG, ISC10); SET_BIT(MCUCR_REG, ISC11);
        #else
            #error "Wrong EXTI_SENSE_MODE option for INT1"
        #endif


    #elif EXTI_LINE == EXTI_LINE2

        /* Configure sense mode for INT2 (ISC2 bit in MCUCSR register) */
        #if     EXTI_SENSE_MODE == EXTI_FALLING_EDGE
            CLR_BIT(MCUCSR_REG, ISC2);
        #elif   EXTI_SENSE_MODE == EXTI_RISING_EDGE
            SET_BIT(MCUCSR_REG, ISC2);
        #else
            #error "INT2 only supports FALLING_EDGE or RISING_EDGE"
        #endif
    #else
        #error "Wrong EXTI_LINE configuration option"
    #endif
}

/**
 * @brief Set the trigger sense mode for a specific external interrupt line (runtime)
 * @param Copy_u8SenseMode: Trigger mode (EXTI_LOW_LEVEL, EXTI_ON_CHANGE, EXTI_FALLING_EDGE, EXTI_RISING_EDGE)
 * @param Copy_u8Line: EXTI_LINE0, EXTI_LINE1, or EXTI_LINE2
 * @return void
 */
void EXTI_voidSetSignalLatch(u8 Copy_u8SenseMode, u8 Copy_u8Line)
{
    /* For EXTI0 & EXTI1 (INT0 and INT1) */
    if (Copy_u8Line == EXTI_LINE0 || Copy_u8Line == EXTI_LINE1)
    {
        /* Convert EXTI_LINE (6 or 7) to bit position (0 or 2) */
        u8 u8BitPos = (Copy_u8Line == EXTI_LINE0) ? 0 : 2;
        
        switch (Copy_u8SenseMode)
        {
            case EXTI_LOW_LEVEL:
                CLR_BIT(MCUCR_REG, u8BitPos);
                CLR_BIT(MCUCR_REG, u8BitPos + 1);
                break;
            case EXTI_ON_CHANGE:
                SET_BIT(MCUCR_REG, u8BitPos);
                CLR_BIT(MCUCR_REG, u8BitPos + 1);
                break;
            case EXTI_FALLING_EDGE:
                CLR_BIT(MCUCR_REG, u8BitPos);
                SET_BIT(MCUCR_REG, u8BitPos + 1);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCR_REG, u8BitPos);
                SET_BIT(MCUCR_REG, u8BitPos + 1);
                break;
            default:
                /* Invalid sense mode - do nothing */
                break;
        }
    }
    /* For EXTI2 (INT2) */
    else if (Copy_u8Line == EXTI_LINE2)
    {
        switch (Copy_u8SenseMode)
        {
            case EXTI_FALLING_EDGE:
                CLR_BIT(MCUCSR_REG, ISC2);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCSR_REG, ISC2);
                break;
            default:
                /* INT2 only supports falling/rising edge */
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
status_t EXTI_DisableInterrupt(u8 Copy_u8Line)
{
    /* Valid lines are bits 5-7 in GICR (INT0=6, INT1=7, INT2=5) */
    if ((Copy_u8Line >= EXTI_LINE2) && (Copy_u8Line <= EXTI_LINE1))
    {
        CLR_BIT(GICR_REG, Copy_u8Line);
        return OK;
    }
    else
    {
        return NOK;
    }

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
status_t EXTI_EnableInterrupt(u8 Copy_u8Line)
{
    /* Valid lines are bits 5-7 in GICR (INT0=6, INT1=7, INT2=5) */
    if ((Copy_u8Line >= EXTI_LINE2) && (Copy_u8Line <= EXTI_LINE1))
    {
        SET_BIT(GICR_REG, Copy_u8Line);
        return OK;
    }
    else
    {
        return NOK;
    }
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
        EXTI_CallBack[Copy_u8EXTILine] = Copy_pvoidCallBack;
}

/*==============================================================================
 * ISR (Interrupt Service Routine) Implementations
 *============================================================================*/

/**
 * @brief ISR for External Interrupt 0 (INT0)
 * @details Vector number: 1 (__vector_1)
 *          Corresponds to INT0 in AVR
 */
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
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
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
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
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
    if (EXTI_CallBack[2] != NULL)
    {
        EXTI_CallBack[2]();           /* Execute user callback */
        EXTI_voidClearFlag(EXTI_LINE2); /* Clear interrupt flag */
    }
}