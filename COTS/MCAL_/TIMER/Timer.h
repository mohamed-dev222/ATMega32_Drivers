/**
 * @file Timer.h
 * @brief Main header file for AVR Timer Driver
 * @version 2.1.0
 * @copyright Copyright (c) 2026
 * @license MIT License
 * 
 * @defgroup TimerDriver AVR Timer Driver
 * @brief MCAL Timer Driver for AVR ATmega32
 * @{
 */

#ifndef TIMER_H
#define TIMER_H

#include "../../LIP/STD_TYPES.h"
#include "Timer_Cfg.h"

extern Timer_Error_t Timer_Init(void);
extern Timer_Error_t Timer_DeInit(void);
extern Timer_Error_t Timer_Start(Timer_Id_t TimerId);
extern Timer_Error_t Timer_Stop(Timer_Id_t TimerId);
extern Timer_Error_t Timer_Reset(Timer_Id_t TimerId);
extern Timer_Error_t Timer_GetCounter(Timer_Id_t TimerId, u32* pValue);
extern Timer_Error_t Timer_SetCounter(Timer_Id_t TimerId, u32 Value);
extern Timer_Error_t Timer_GetCompare(Timer_Id_t TimerId, Timer_Channel_t Channel, u32* pValue);
extern Timer_Error_t Timer_SetCompare(Timer_Id_t TimerId, Timer_Channel_t Channel, u32 Value);
extern Timer_Error_t Timer_GetStatus(Timer_Id_t TimerId, Timer_Status_t* pStatus);
extern Timer_Error_t Timer_GetTick(Timer_Id_t TimerId, u32* pTicks);

extern Timer_Error_t Timer0_SetPreload(u8 value);
extern Timer_Error_t Timer0_SetCompareValue(u8 value);
extern Timer_Error_t Timer1_SetFrequency(u16 frequency);
extern Timer_Error_t Timer1_SetDutyA(u8 duty);
extern Timer_Error_t Timer1_SetDutyB(u8 duty);
extern Timer_Error_t Timer1_SetICR(u16 value);
extern Timer_Error_t Timer1_SetOCR1A(u16 value);
extern Timer_Error_t Timer1_SetOCR1B(u16 value);
extern Timer_Error_t Timer2_SetPreload(u8 value);
extern Timer_Error_t Timer2_SetCompareValue(u8 value);
extern Timer_Error_t WDT_Enable(void);
extern Timer_Error_t WDT_Disable(void);
extern Timer_Error_t WDT_Refresh(void);
extern Timer_Error_t WDT_SetTimeout(u8 timeout);

extern void TIMER0_OVF_ISR(void) __attribute__((weak));
extern void TIMER0_COMP_ISR(void) __attribute__((weak));
extern void TIMER1_OVF_ISR(void) __attribute__((weak));
extern void TIMER1_COMPA_ISR(void) __attribute__((weak));
extern void TIMER1_COMPB_ISR(void) __attribute__((weak));
extern void TIMER1_CAPT_ISR(void) __attribute__((weak));
extern void TIMER2_OVF_ISR(void) __attribute__((weak));
extern void TIMER2_COMP_ISR(void) __attribute__((weak));

#endif /* TIMER_H */

/** @} */
