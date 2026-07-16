/**
 * @file STD_TYPES.h
 * @brief Standard data types for MCAL layer
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Unsigned integer types */
typedef unsigned char      u8;      /**< 8-bit unsigned integer (0 to 255) */
typedef unsigned short     u16;     /**< 16-bit unsigned integer (0 to 65535) */
typedef unsigned long      u32;     /**< 32-bit unsigned integer (0 to 4294967295) */
typedef unsigned long long u64;     /**< 32-bit unsigned integer (0 to 4294967295) */

/* Signed integer types */
typedef signed char        s8;      /**< 8-bit signed integer (-128 to 127) */
typedef signed short       s16;     /**< 16-bit signed integer (-32768 to 32767) */
typedef signed long        s32;     /**< 32-bit signed integer (-2147483648 to 2147483647) */

/* Floating point types */
typedef float              f32;     /**< 32-bit floating point */
typedef double             f64;     /**< 64-bit floating point */

/* Boolean type */
typedef enum {
    FALSE = 0,                       /**< Boolean false value */
    TRUE  = 1                        /**< Boolean true value */
} bool_t;

/* Function return status */
typedef enum {
    OK            = 0,                    /**< Operation completed successfully */
    NOK           = 1,                    /**< Operation failed */
    TIMEOUT       = 2,                    /**< Operation timeout */
    INVALID       = 3,                    /**< Invalid parameter */
    BUSY          = 4,                    /**< Resource is busy */
    NULL_POINTER  = 5,                    /**< Null pointer passed as argument */
    OUT_OF_RANGE  = 6,                    /**< Value out of valid range */
    NOT_INITIALIZED = 7,                  /**< Module not initialized */
    NOT_SUPPORTED = 8                     /**< Operation not supported */
} status_t;

/* Null pointer definition */
#define NULL ((void*)0)

/* ============================================================================
 * Timer Driver Types and Constants
 * ============================================================================ */
typedef enum
{
    TIMER_E_OK                  = 0,
    TIMER_E_NOT_OK              = 1,
    TIMER_E_INVALID_ID          = 2,
    TIMER_E_INVALID_PARAM       = 3,
    TIMER_E_NULL_PTR            = 4,
    TIMER_E_BUSY                = 5,
    TIMER_E_INVALID_MODE        = 6,
    TIMER_E_OUT_OF_RANGE        = 7,
    TIMER_E_TIMER_STOPPED       = 8,
    TIMER_E_NOT_INITIALIZED     = 9
} Timer_Error_t;

#define E_OK    TIMER_E_OK
#define E_NOT_OK TIMER_E_NOT_OK

typedef enum
{
    TIMER0 = 0,
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER_MAX_ID = 3
} Timer_Id_t;

typedef enum
{
    COMPARE_A = 0,
    COMPARE_B = 1
} Timer_Channel_t;

typedef enum
{
    TIMER_STATUS_STOPPED = 0,
    TIMER_STATUS_RUNNING = 1,
    TIMER_STATUS_OVERFLOW = 2,
    TIMER_STATUS_COMPARE = 3,
    TIMER_STATUS_ERROR = 4
} Timer_Status_t;

typedef enum
{
    TIMER_MODE_NORMAL           = 0,
    TIMER_MODE_PHASE_PWM        = 1,
    TIMER_MODE_CTC              = 2,
    TIMER_MODE_FAST_PWM         = 3
} Timer0_Mode_t;

#define TIMER_NORMAL_MODE       TIMER_MODE_NORMAL
#define TIMER_PHASE_PWM_MODE    TIMER_MODE_PHASE_PWM
#define TIMER_CTC_MODE          TIMER_MODE_CTC
#define TIMER_FAST_PWM_MODE     TIMER_MODE_FAST_PWM
#define TIMER_PWM_MODE          TIMER_MODE_PHASE_PWM

typedef enum
{
    TIMER1_NORMAL           = 0,
    TIMER1_PWM_8_BIT        = 1,
    TIMER1_PWM_9_BIT        = 2,
    TIMER1_PWM_10_BIT       = 3,
    TIMER1_CTC_OCR1A        = 4,
    TIMER1_FAST_PWM_8_BIT   = 5,
    TIMER1_FAST_PWM_9_BIT   = 6,
    TIMER1_FAST_PWM_10_BIT  = 7,
    TIMER1_PWM_PF_ICR       = 8,
    TIMER1_PWM_PF_OCR1A     = 9,
    TIMER1_PWM_PC_ICR       = 10,
    TIMER1_PWM_PC_OCR1A     = 11,
    TIMER1_CTC_ICR1         = 12,
    TIMER1_FAST_PWM_ICR1    = 14,
    TIMER1_FAST_PWM_OCR1A   = 15
} Timer1_Mode_t;

#define TIMER1_NORMAL_MODE                      TIMER1_NORMAL
#define TIMER1_PWM_8_BIT_MODE                   TIMER1_PWM_8_BIT
#define TIMER1_PWM_9_BIT_MODE                   TIMER1_PWM_9_BIT
#define TIMER1_PWM_10_BIT_MODE                  TIMER1_PWM_10_BIT
#define TIMER1_CTC_OCR1A_MODE                   TIMER1_CTC_OCR1A
#define TIMER1_FAST_PWM_8_BIT_MODE              TIMER1_FAST_PWM_8_BIT
#define TIMER1_FAST_PWM_9_BIT_MODE              TIMER1_FAST_PWM_9_BIT
#define TIMER1_FAST_PWM_10_BIT_MODE             TIMER1_FAST_PWM_10_BIT
#define TIMER1_FAST_PWM_ICR1_MODE               TIMER1_FAST_PWM_ICR1
#define TIMER1_FAST_PWM_OCR1A_MODE              TIMER1_FAST_PWM_OCR1A
#define TIMER1_CTC_ICR1_MODE                    TIMER1_CTC_ICR1
#define TIMER1_PWM_PF_ICR_MODE                  TIMER1_PWM_PF_ICR
#define TIMER1_PWM_PF_OCR1A_MODE                TIMER1_PWM_PF_OCR1A
#define TIMER1_PWM_PC_ICR_MODE                  TIMER1_PWM_PC_ICR
#define TIMER1_PWM_PC_OCR1A_MODE                TIMER1_PWM_PC_OCR1A

typedef enum
{
    TIMER_OC_DISCONNECTED   = 0,
    TIMER_OC_TOGGLE         = 1,
    TIMER_OC_NON_INVERTING  = 2,
    TIMER_OC_INVERTING      = 3
} Timer_OC_Mode_t;

#define TIMER_OC_CLEAR      TIMER_OC_NON_INVERTING
#define TIMER_OC_SET        TIMER_OC_INVERTING

typedef enum
{
    TIMER_PRESCALER_STOPPED     = 0,
    TIMER_PRESCALER_1           = 1,
    TIMER_PRESCALER_8           = 2,
    TIMER_PRESCALER_64          = 3,
    TIMER_PRESCALER_256         = 4,
    TIMER_PRESCALER_1024        = 5,
    TIMER_PRESCALER_T0_FALLING  = 6,
    TIMER_PRESCALER_T0_RISING   = 7
} Timer_Prescaler_t;

typedef enum
{
    TIMER2_PRESCALER_STOPPED    = 0,
    TIMER2_PRESCALER_1          = 1,
    TIMER2_PRESCALER_8          = 2,
    TIMER2_PRESCALER_32         = 3,
    TIMER2_PRESCALER_64         = 4,
    TIMER2_PRESCALER_128        = 5,
    TIMER2_PRESCALER_256        = 6,
    TIMER2_PRESCALER_1024       = 7
} Timer2_Prescaler_t;

#define TIMER_NO_CLOCK_SOURCE              TIMER_PRESCALER_STOPPED
#define TIMER_NO_PRESCALER_FACTOR          TIMER_PRESCALER_1
#define TIMER_DIVISION_FACTOR_8            TIMER_PRESCALER_8
#define TIMER_DIVISION_FACTOR_64           TIMER_PRESCALER_64
#define TIMER_DIVISION_FACTOR_256          TIMER_PRESCALER_256
#define TIMER_DIVISION_FACTOR_1024         TIMER_PRESCALER_1024
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING  TIMER_PRESCALER_T0_FALLING
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING   TIMER_PRESCALER_T0_RISING

#define TIMER2_NO_CLOCK_SOURCE             TIMER2_PRESCALER_STOPPED
#define TIMER2_NO_PRESCALER_FACTOR         TIMER2_PRESCALER_1
#define TIMER2_DIVISION_FACTOR_8           TIMER2_PRESCALER_8
#define TIMER2_DIVISION_FACTOR_32          TIMER2_PRESCALER_32
#define TIMER2_DIVISION_FACTOR_64          TIMER2_PRESCALER_64
#define TIMER2_DIVISION_FACTOR_128         TIMER2_PRESCALER_128
#define TIMER2_DIVISION_FACTOR_256         TIMER2_PRESCALER_256
#define TIMER2_DIVISION_FACTOR_1024        TIMER2_PRESCALER_1024

typedef enum
{
    TIMER_ICP_FALLING_EDGE = 0,
    TIMER_ICP_RISING_EDGE  = 1
} Timer_ICP_Edge_t;

typedef enum
{
    WDT_PS_16_3_MS  = 0,
    WDT_PS_32_5_MS  = 1,
    WDT_PS_65_MS    = 2,
    WDT_PS_0_13_S   = 3,
    WDT_PS_0_26_S   = 4,
    WDT_PS_0_52_S   = 5,
    WDT_PS_1_0_S    = 6,
    WDT_PS_2_1_S    = 7
} WDT_Prescaler_t;

#endif /* STD_TYPES_H_ */
