/**
 * @file MCAL_CONFIG.h
 * @brief Global configuration for MCAL layer
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef MCAL_CONFIG_H_
#define MCAL_CONFIG_H_

/* ==================== System Clock Configuration ==================== */
#define F_CPU                    16000000UL  /**< CPU frequency 16MHz */

/* ==================== UART Configuration ==================== */
#define UART_DEFAULT_BAUD        9600        /**< Default baud rate */

/* ==================== ADC Configuration ==================== */
#define ADC_VREF_AVCC            1           /**< AVCC as reference */
#define ADC_VREF_AREF            2           /**< AREF as reference */
#define ADC_VREF_INTERNAL        3           /**< Internal 1.1V reference */
#define ADC_DEFAULT_VREF         ADC_VREF_AVCC

/* ==================== Timer Configuration ==================== */
#define TIMER0_PRESCALER_0       1
#define TIMER0_PRESCALER_8       2
#define TIMER0_PRESCALER_64      3
#define TIMER0_PRESCALER_256     4
#define TIMER0_PRESCALER_1024    5
#define TIMER0_DEFAULT_PRESCALER TIMER0_PRESCALER_64

/* ==================== Watchdog Configuration ==================== */
#define WDT_TIMEOUT_16MS         0
#define WDT_TIMEOUT_32MS         1
#define WDT_TIMEOUT_64MS         2
#define WDT_TIMEOUT_125MS        3
#define WDT_TIMEOUT_250MS        4
#define WDT_TIMEOUT_500MS        5
#define WDT_TIMEOUT_1S           6
#define WDT_TIMEOUT_2S           7
#define WDT_DEFAULT_TIMEOUT      WDT_TIMEOUT_2S

/* ==================== Debug Configuration ==================== */
#define MCAL_DEBUG_ENABLE        1       /**< Enable debug messages */

#endif /* MCAL_CONFIG_H_ */