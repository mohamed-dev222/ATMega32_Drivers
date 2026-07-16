/**
 * @file Timer_Cfg.h
 * @brief Configuration header for AVR Timer Driver
 * @note Defines timer modes, prescalers, compare values, and WDT timeout
 */

#ifndef TIMER_CFG_H
#define TIMER_CFG_H

/* ======== Enable / Disable ======== */
#define ENABLE  1U
#define DISABLE 0U

/* ======== Timer0 Configuration ======== */
#define TIMER0_MODE               TIMER_MODE_NORMAL
#define TIMER0_OC_MODE            TIMER_OC_DISCONNECTED
#define TIMER0_INITIAL_VALUE      0U
#define TIMER0_COMPARE_VALUE      0U
#define TIMER0_PRESCALER          TIMER_PRESCALER_64
#define TIMER0_OVERFLOW_INTERRUPT DISABLE

/* ======== Timer1 Configuration ======== */
#define TIMER1_MODE               TIMER1_NORMAL
#define TIMER1_OCR1A_MODE         TIMER_OC_DISCONNECTED
#define TIMER1_OCR1B_MODE         TIMER_OC_DISCONNECTED
#define TIMER1_INPUT_CAPTURE_NOISE DISABLE
#define TIMER1_INPUT_CAPTURE_EDGE TIMER_ICP_FALLING_EDGE
#define TIMER1_PRESCALER          TIMER_PRESCALER_64
#define TIMER1_USE_HIGH_LEVEL_CONFIG 0U
#define TIMER1_PWM_FREQUENCY      1000UL
#define TIMER1_PWM_DUTY_A         50U
#define TIMER1_PWM_DUTY_B         50U
#define TIMER1_ICR_TOP            0x0000U
#define TIMER1_OCR1A_VALUE        0x0000U
#define TIMER1_OCR1B_VALUE        0x0000U
#define TIMER1_OVERFLOW_INT       DISABLE
#define TIMER1_CTC_A_INT          DISABLE
#define TIMER1_CTC_B_INT          DISABLE
#define TIMER1_ICR_INT            DISABLE

/* ======== Timer2 Configuration ======== */
#define TIMER2_MODE               TIMER_MODE_NORMAL
#define TIMER2_OC_MODE            TIMER_OC_DISCONNECTED
#define TIMER2_INITIAL_VALUE      0U
#define TIMER2_COMPARE_VALUE      0U
#define TIMER2_PRESCALER          TIMER2_PRESCALER_64
#define TIMER2_OVERFLOW_INT       DISABLE
#define TIMER2_CTC_INT            DISABLE

/* ======== Watchdog Timer Configuration ======== */
#define WDT_TIMEOUT               WDT_PS_1_0_S

#endif /* TIMER_CFG_H */
