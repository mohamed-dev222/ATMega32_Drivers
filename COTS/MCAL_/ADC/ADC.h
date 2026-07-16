/**
 * @file ADC.h
 * @brief Public header for ADC (Analog to Digital Converter) driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control AVR ADC module
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*==============================================================================
 * Error States / Return Values
 *============================================================================*/
/* Uses shared status_t from STD_TYPES.h: OK, NOK, TIMEOUT, INVALID,
   BUSY, NULL_POINTER, OUT_OF_RANGE, NOT_INITIALIZED, NOT_SUPPORTED */

/*==============================================================================
 * ADC Module State Flags
 *============================================================================*/
#define IDLE            0   /* ADC is idle and ready for new conversion */
#define BUSY            1   /* ADC is currently performing a conversion */

/*==============================================================================
 * ADC Module Status Options
 *============================================================================*/
#define ADC_DISABLE             0
#define ADC_ENABLE              1

/*==============================================================================
 * ADC Interrupt Status Options
 *============================================================================*/
#define INT_DISABLE             0
#define INT_ENABLE              1

/*==============================================================================
 * ADC Voltage Reference Selection Options
 *============================================================================*/
#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3

/*==============================================================================
 * ADC Result Adjustment Options
 *============================================================================*/
#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

/*==============================================================================
 * ADC Channel Selection Options (Single Ended Inputs)
 *============================================================================*/
#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7

/*==============================================================================
 * ADC Auto-Triggering Source Options
 *============================================================================*/
#define ADC_SINGLE_CONVERSION   0
#define ADC_FREE_RUNNING        1
#define ADC_ANALOG_COMPARATOR   2
#define ADC_EXTI0               3
#define ADC_TIM0_CTC            4
#define ADC_TIM0_OVF            5
#define ADC_TIM1_CTC_CHANNEL_B  6
#define ADC_TIM1_OVF            7
#define ADC_TIM1_ICU            8

/*==============================================================================
 * ADC Clock Prescaler Options
 *============================================================================*/
#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7

/*==============================================================================
 * Chain Structure for Asynchronous Chain Conversion
 *============================================================================*/
/**
 * @struct Chain_t
 * @brief Structure to configure a chain of ADC conversions
 * @param Channel: Pointer to array of channels to be converted sequentially
 * @param Result:  Pointer to array to store conversion results
 * @param Size:    Number of channels in the chain
 * @param NotificationFunc: Callback function to be called when chain completes
 */
typedef struct 
{
	u8*  Channel ;
	u16* Result  ;
	u8   Size    ;
	void (*NotificationFunc)(void);
}Chain_t ;

/*==============================================================================
 * ADC Public APIs
 *============================================================================*/

/**
 * @brief Initialize the ADC module with configuration from ADC_config.h
 * @param void
 * @return void
 * @details Configures voltage reference, result adjustment, prescaler,
 *          peripheral enable/disable, and interrupt enable/disable
 */
void ADC_voidInit               ( void                                                                             );

/**
 * @brief Get ADC conversion result in synchronous (blocking) mode
 * @param Copy_u8Channel: ADC channel to read from (ADC_CHANNEL0 to ADC_CHANNEL7)
 * @param Copy_pu16Result: Pointer to store the conversion result (10-bit or 8-bit based on adjustment)
 * @return status_t: OK if successful, BUSY if ADC is busy, TIMEOUT if conversion timed out, NULL_POINTER if result pointer is NULL
 * @details This function blocks until conversion completes or timeout occurs
 * @note Uses polling on ADIF flag with timeout mechanism
 */
status_t   ADC_u8GetResultSync        ( u8 Copy_u8Channel , u16* Copy_pu16Result                                         );

/**
 * @brief Start ADC conversion in asynchronous (non-blocking) mode for single channel
 * @param Copy_u8Channel: ADC channel to read from (ADC_CHANNEL0 to ADC_CHANNEL7)
 * @param Copy_pu16Reading: Pointer to store the conversion result when complete
 * @param Copy_pvNotificationFunc: Callback function to be called when conversion completes
 * @return status_t: OK if successful, BUSY if ADC is busy, NULL_POINTER if parameters are NULL
 * @details Conversion continues in background. The notification function is called from ISR context
 * @warning The callback function should be lightweight and avoid long operations
 */
status_t   ADC_u8StartConversionAsynch( u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void) );

/**
 * @brief Start ADC chain conversion in asynchronous (non-blocking) mode
 * @param Copy_Chain: Pointer to Chain_t structure containing channels, results array, size, and callback
 * @return status_t: OK if successful, BUSY if ADC is busy, NULL_POINTER if chain or its members are NULL
 * @details Converts multiple channels sequentially. Results are stored in the Result array.
 *          Notification function is called after all channels are converted
 * @note The Channel array and Result array must be allocated by the user
 */
status_t   ADC_u8StartChainAsynch     ( Chain_t * Copy_Chain);

/**
 * @brief Enable the ADC peripheral
 * @param void
 * @return void
 * @details Turns on the ADC module to start consuming power and be ready for conversions
 */
void ADC_voidEnable           (void);

/**
 * @brief Disable the ADC peripheral
 * @param void
 * @return void
 * @details Turns off the ADC module to save power
 */
void ADC_voidDisable          (void);

/**
 * @brief Enable ADC conversion complete interrupt
 * @param void
 * @return void
 * @details Enables the interrupt that fires when an ADC conversion completes
 * @note Must be enabled for asynchronous conversion modes
 */
void ADC_voidInterruptEnable  (void);

/**
 * @brief Disable ADC conversion complete interrupt
 * @param void
 * @return void
 * @details Disables the ADC conversion complete interrupt
 */
void ADC_voidInterruptDisable (void);

/**
 * @brief Change ADC clock prescaler at runtime
 * @param Copy_u8Prescaler: Prescaler value (ADC_PRE_2, ADC_PRE_4, ... ADC_PRE_128)
 * @return OK if successful (prescaler value < 8), error code otherwise
 * @details Modifies the ADC clock division factor. Valid values 0-7
 * @note Changing prescaler during conversion may affect result accuracy
 */
status_t ADC_u8SetPrescaler (u8 Copy_u8Prescaler);

#endif /* ADC_INTERFACE_H_ */