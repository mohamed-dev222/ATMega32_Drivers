/**
 * @file USART_CFG_H_
 * @brief Configuration header for USART driver Contains all user-configurable definitions and macros
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/*==============================================================================
 * System Frequency Configuration
 *============================================================================*/
/*
 Options:-
 	 1-SYSTEM_FREQUENCY (in Hz)
 */

#define SYSTEM_FREQUENCY                8000000UL

/*==============================================================================
 * USART Baud Rate Configuration
 *============================================================================*/
/*
 Options:-
 	 1-USART_BAUD_RATE (in bps)
 */

#define USART_BAUD_RATE                 9600UL

/*==============================================================================
 * USART System Speed Options
 *============================================================================*/
/*
 Options:-
 	 1-USART_X1
 	 2-USART_X2  (Double Speed Mode)
 */

#define USART_SYSTEM_SPEED              USART_X1

/*==============================================================================
 * USART Timeout Configuration
 *============================================================================*/
/*
 Options:-
 	 1-USART_u32TIMEOUT (in ticks)
 */

#define USART_u32TIMEOUT                10000UL

/*==============================================================================
 * USART Multi-Processor Communication Mode Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_MPCM                      DISABLE

/*==============================================================================
 * USART RX Complete Interrupt Enable Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_RX_COMPLETE_INTERRUPT     DISABLE

/*==============================================================================
 * USART TX Complete Interrupt Enable Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_TX_COMPLETE_INTERRUPT     DISABLE

/*==============================================================================
 * USART UDR Empty Interrupt Enable Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_UDR_EMPTY_INTERRUPT       DISABLE

/*==============================================================================
 * USART Receiver Enable Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_RECEIVER_ENABLE           ENABLE

/*==============================================================================
 * USART Transmitter Enable Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-ENABLE
 */

#define USART_TRANSMITTER_ENABLE        ENABLE

/*==============================================================================
 * USART Mode Select Options
 *============================================================================*/
/*
 Options:-
 	 1-ASYNCHRONOUS
 	 2-SYNCHRONOUS
 */

#define USART_MODE                      ASYNCHRONOUS

/*==============================================================================
 * USART Parity Mode Options
 *============================================================================*/
/*
 Options:-
 	 1-DISABLE
 	 2-EVEN_PARITY
 	 3-ODD_PARITY
 */

#define USART_PARITY_MODE               DISABLE

/*==============================================================================
 * USART Stop Bit Options
 *============================================================================*/
/*
 Options:-
 	 1-STOP_BIT_1
 	 2-STOP_BIT_2
 */

#define USART_STOP_BIT                  STOP_BIT_1

/*==============================================================================
 * USART Data Size Options
 *============================================================================*/
/*
 Options:-
 	 1-DATA_SIZE_5_BIT
 	 2-DATA_SIZE_6_BIT
 	 3-DATA_SIZE_7_BIT
 	 4-DATA_SIZE_8_BIT
 	 5-DATA_SIZE_9_BIT
 */

#define USART_DATA_SIZE                 DATA_SIZE_8_BIT

/*==============================================================================
 * USART Clock Polarity Options (for SYNCHRONOUS mode only)
 *============================================================================*/
/*
 Options:-
 	 1-XCK_RISING_TX_XCH_FALLING_RX
 	 2-XCK_RISING_RX_XCH_FALLING_TX
 */

#define USART_CLOCK_POLARITY            XCK_RISING_TX_XCH_FALLING_RX

#endif /* USART_CONFIG_H_ */