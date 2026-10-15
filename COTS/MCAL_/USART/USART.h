/**
 * @file USART_INTERFACE_H_
 * @brief Interface header for USART driver Contains all function prototypes
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/*==============================================================================
 * Initialization Function
 *============================================================================*/

/*
 * Brief : This Function initialize USART depend on config.h
 * Parameters : Nothing
 * Return : Nothing
 */
void USART_voidInit (void);

/*==============================================================================
 * Send Data Functions
 *============================================================================*/

/*
 * Brief : This Function sends a single byte of data
 * Parameters : Copy_u8Data (the data to be sent)
 * Return : Error State
 */
u8 USART_u8SendData (u8 Copy_u8Data);

/*
 * Brief : This Function sends a string of data synchronously
 * Parameters : Copy_pchString (pointer to the string to be sent)
 * Return : Error State
 */
u8 USART_u8SendStringSynch (const u8 * Copy_pchString);

/*
 * Brief : This Function sends a string of data asynchronously
 * Parameters : Copy_pchString (pointer to the string to be sent)
 *              NotificationFunc (pointer to the notification function)
 * Return : Error State
 */
u8 USART_u8SendStringAsynch (const u8 * Copy_pchString , void (* NotificationFunc)(void));

/*==============================================================================
 * Receive Data Functions
 *============================================================================*/

/*
 * Brief : This Function receives a single byte of data
 * Parameters : Copy_u8ReceviedData (pointer to store the received data)
 * Return : Error State
 */
u8 USART_u8RecevieData (u8 * Copy_u8ReceviedData);

/*
 * Brief : This Function receives a buffer of data synchronously
 * Parameters : Copy_pchString (pointer to the buffer to store the received data)
 *              Copy_uint32BufferSize (size of the buffer)
 * Return : Error State
 */
u8 USART_u8ReceiveBufferSynch (u8 * Copy_pchString , u32 Copy_uint32BufferSize);

/*
 * Brief : This Function receives a buffer of data asynchronously
 * Parameters : Copy_pchString (pointer to the buffer to store the received data)
 *              Copy_uint32BufferSize (size of the buffer)
 *              NotificationFunc (pointer to the notification function)
 * Return : Error State
 */
u8 USART_u8ReceiveBufferAsynch (u8 * Copy_pchString , u32 Copy_uint32BufferSize , void (* NotificationFunc)(void));

#endif /* USART_INTERFACE_H_ */