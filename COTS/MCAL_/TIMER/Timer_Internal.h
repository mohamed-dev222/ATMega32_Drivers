/**
 * @file Timer_Internal.h
 * @brief Internal utilities, validation macros, and helper functions
 * @note This file should ONLY be included by Timer.c
 * @warning Not part of public API
 * 
 * @defgroup TimerInternal Internal Utilities
 * @{
 */

#ifndef TIMER_INTERNAL_H
#define TIMER_INTERNAL_H

#include "../../LIP/STD_TYPES.h"
#include "Timer_Cfg.h"

#define TIMER_MAX_8BIT      255U
#define TIMER_MAX_16BIT     65535U

#define TIMER_IS_VALID_8BIT(x)      ((x) <= TIMER_MAX_8BIT)
#define TIMER_IS_VALID_16BIT(x)     ((x) <= TIMER_MAX_16BIT)
#define TIMER_IS_VALID_INTERRUPT(x) (((x) == ENABLE) || ((x) == DISABLE))

#define TIMER0_IS_VALID_MODE(x) \
    (((x) == TIMER_MODE_NORMAL) || \
     ((x) == TIMER_MODE_PHASE_PWM) || \
     ((x) == TIMER_MODE_CTC) || \
     ((x) == TIMER_MODE_FAST_PWM))

#define TIMER2_IS_VALID_MODE(x) TIMER0_IS_VALID_MODE(x)

#define TIMER1_IS_PWM_MODE(x) \
    (((x) == TIMER1_PWM_8_BIT) || \
     ((x) == TIMER1_PWM_9_BIT) || \
     ((x) == TIMER1_PWM_10_BIT) || \
     ((x) == TIMER1_FAST_PWM_8_BIT) || \
     ((x) == TIMER1_FAST_PWM_9_BIT) || \
     ((x) == TIMER1_FAST_PWM_10_BIT) || \
     ((x) == TIMER1_PWM_PF_ICR) || \
     ((x) == TIMER1_PWM_PF_OCR1A) || \
     ((x) == TIMER1_PWM_PC_ICR) || \
     ((x) == TIMER1_PWM_PC_OCR1A) || \
     ((x) == TIMER1_FAST_PWM_ICR1) || \
     ((x) == TIMER1_FAST_PWM_OCR1A))

#define TIMER1_IS_CTC_MODE(x) \
    (((x) == TIMER1_CTC_OCR1A) || ((x) == TIMER1_CTC_ICR1))

#define TIMER1_IS_NORMAL_MODE(x) \
    ((x) == TIMER1_NORMAL)

#define TIMER1_IS_VALID_MODE(x) \
    (TIMER1_IS_NORMAL_MODE(x) || \
     TIMER1_IS_PWM_MODE(x) || \
     TIMER1_IS_CTC_MODE(x))

#define TIMER0_IS_VALID_PRESCALER(x) \
    (((x) == TIMER_PRESCALER_STOPPED) || \
     ((x) == TIMER_PRESCALER_1) || \
     ((x) == TIMER_PRESCALER_8) || \
     ((x) == TIMER_PRESCALER_64) || \
     ((x) == TIMER_PRESCALER_256) || \
     ((x) == TIMER_PRESCALER_1024) || \
     ((x) == TIMER_PRESCALER_T0_FALLING) || \
     ((x) == TIMER_PRESCALER_T0_RISING))

#define TIMER1_IS_VALID_PRESCALER(x) \
    (((x) == TIMER_PRESCALER_STOPPED) || \
     ((x) == TIMER_PRESCALER_1) || \
     ((x) == TIMER_PRESCALER_8) || \
     ((x) == TIMER_PRESCALER_64) || \
     ((x) == TIMER_PRESCALER_256) || \
     ((x) == TIMER_PRESCALER_1024))

#define TIMER2_IS_VALID_PRESCALER(x) \
    (((x) == TIMER2_PRESCALER_STOPPED) || \
     ((x) == TIMER2_PRESCALER_1) || \
     ((x) == TIMER2_PRESCALER_8) || \
     ((x) == TIMER2_PRESCALER_32) || \
     ((x) == TIMER2_PRESCALER_64) || \
     ((x) == TIMER2_PRESCALER_128) || \
     ((x) == TIMER2_PRESCALER_256) || \
     ((x) == TIMER2_PRESCALER_1024))

#define TIMER_IS_VALID_PWM_MODE(x) \
    (((x) == TIMER_OC_DISCONNECTED) || \
     ((x) == TIMER_OC_NON_INVERTING) || \
     ((x) == TIMER_OC_INVERTING))

#define TIMER_IS_VALID_CTC_MODE(x) \
    (((x) == TIMER_OC_DISCONNECTED) || \
     ((x) == TIMER_OC_TOGGLE) || \
     ((x) == TIMER_OC_NON_INVERTING) || \
     ((x) == TIMER_OC_INVERTING))

#define WDT_IS_VALID_PRESCALER(x) \
    (((x) == WDT_PS_16_3_MS) || \
     ((x) == WDT_PS_32_5_MS) || \
     ((x) == WDT_PS_65_MS) || \
     ((x) == WDT_PS_0_13_S) || \
     ((x) == WDT_PS_0_26_S) || \
     ((x) == WDT_PS_0_52_S) || \
     ((x) == WDT_PS_1_0_S) || \
     ((x) == WDT_PS_2_1_S))

extern const u16 TimerPrescalerMap[];
extern const u16 Timer2PrescalerMap[];

static inline u16 Timer_GetPrescalerValue(Timer_Prescaler_t Prescaler)
{
    if (Prescaler <= TIMER_PRESCALER_1024)
    {
        return TimerPrescalerMap[Prescaler];
    }
    return 0;
}

static inline u16 Timer2_GetPrescalerValue(Timer2_Prescaler_t Prescaler)
{
    if (Prescaler <= TIMER2_PRESCALER_1024)
    {
        return Timer2PrescalerMap[Prescaler];
    }
    return 0;
}

#if !TIMER0_IS_VALID_MODE(TIMER0_MODE)
    #error "Invalid TIMER0_MODE in Timer_Cfg.h"
#endif

#if !TIMER0_IS_VALID_PRESCALER(TIMER0_PRESCALER)
    #error "Invalid TIMER0_PRESCALER in Timer_Cfg.h"
#endif

#if !TIMER_IS_VALID_8BIT(TIMER0_INITIAL_VALUE)
    #error "TIMER0_INITIAL_VALUE out of range (Max: 255)"
#endif

#if !TIMER_IS_VALID_INTERRUPT(TIMER0_OVERFLOW_INTERRUPT)
    #error "Invalid TIMER0_OVERFLOW_INTERRUPT - Use ENABLE or DISABLE"
#endif

#if !TIMER1_IS_VALID_MODE(TIMER1_MODE)
    #error "Invalid TIMER1_MODE in Timer_Cfg.h"
#endif

#if !TIMER1_IS_VALID_PRESCALER(TIMER1_PRESCALER)
    #error "Invalid TIMER1_PRESCALER in Timer_Cfg.h"
#endif

#if !TIMER2_IS_VALID_MODE(TIMER2_MODE)
    #error "Invalid TIMER2_MODE in Timer_Cfg.h"
#endif

#if !TIMER2_IS_VALID_PRESCALER(TIMER2_PRESCALER)
    #error "Invalid TIMER2_PRESCALER in Timer_Cfg.h"
#endif

#if !WDT_IS_VALID_PRESCALER(WDT_TIMEOUT)
    #error "Invalid WDT_TIMEOUT in Timer_Cfg.h"
#endif

#endif /* TIMER_INTERNAL_H */

/** @} */
