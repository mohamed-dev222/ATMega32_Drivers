/**
 * @file Timer.c
 * @brief Implementation of AVR Timer Driver
 * @note This is the ONLY file that includes Timer_Private.h and Timer_Internal.h
 * 
 * @defgroup TimerImplementation Timer Driver Implementation
 * @{
 */

#include "Timer.h"
#include "Timer_Internal.h"
#include "Timer_Private.h"
#include "../../LIP/MCAL_CONFIG.h"
#include "../../LIP/MCAL_CONFIG.h"
#include "../../LIP/BIT_MATH.h"

const u16 TimerPrescalerMap[] =
{
    [TIMER_PRESCALER_STOPPED]   = 0,
    [TIMER_PRESCALER_1]         = 1,
    [TIMER_PRESCALER_8]         = 8,
    [TIMER_PRESCALER_64]        = 64,
    [TIMER_PRESCALER_256]       = 256,
    [TIMER_PRESCALER_1024]      = 1024,
    [TIMER_PRESCALER_T0_FALLING]= 0,
    [TIMER_PRESCALER_T0_RISING] = 0
};

const u16 Timer2PrescalerMap[] =
{
    [TIMER2_PRESCALER_STOPPED]  = 0,
    [TIMER2_PRESCALER_1]        = 1,
    [TIMER2_PRESCALER_8]        = 8,
    [TIMER2_PRESCALER_32]       = 32,
    [TIMER2_PRESCALER_64]       = 64,
    [TIMER2_PRESCALER_128]      = 128,
    [TIMER2_PRESCALER_256]      = 256,
    [TIMER2_PRESCALER_1024]     = 1024
};

static Timer_Status_t TimerStatus[TIMER_MAX_ID] =
{
    TIMER_STATUS_STOPPED,
    TIMER_STATUS_STOPPED,
    TIMER_STATUS_STOPPED
};

static u8 TimerInitialized = 0;
static u8 WDTCurrentTimeout = WDT_PS_1_0_S;

static void Timer_ClearClock(Timer_Id_t TimerId)
{
    switch (TimerId)
    {
        case TIMER0:
            CLR_MASK(TCCR0, 0x07);
            break;
        case TIMER1:
            CLR_MASK(TCCR1B, 0x07);
            break;
        case TIMER2:
            CLR_MASK(TCCR2, 0x07);
            break;
        default:
            break;
    }
}

static void Timer_ApplyClock(Timer_Id_t TimerId, u8 ClockBits)
{
    switch (TimerId)
    {
        case TIMER0:
            CLR_MASK(TCCR0, 0x07);
            SET_MASK(TCCR0, ClockBits & 0x07);
            break;
        case TIMER1:
            CLR_MASK(TCCR1B, 0x07);
            SET_MASK(TCCR1B, ClockBits & 0x07);
            break;
        case TIMER2:
            CLR_MASK(TCCR2, 0x07);
            SET_MASK(TCCR2, ClockBits & 0x07);
            break;
        default:
            break;
    }
}

static Timer_Error_t Timer0_Init(void)
{
    u8 modeBits = 0;
    u8 comBits = 0;

    switch (TIMER0_MODE)
    {
        case TIMER_MODE_NORMAL:
            modeBits = 0;
            break;
        case TIMER_MODE_PHASE_PWM:
            modeBits = (1 << WGM00);
            break;
        case TIMER_MODE_CTC:
            modeBits = (1 << WGM01);
            break;
        case TIMER_MODE_FAST_PWM:
            modeBits = (1 << WGM00) | (1 << WGM01);
            break;
        default:
            return TIMER_E_INVALID_MODE;
    }

    switch (TIMER0_OC_MODE)
    {
        case TIMER_OC_DISCONNECTED:
            comBits = 0;
            break;
        case TIMER_OC_TOGGLE:
            comBits = (1 << COM00);
            break;
        case TIMER_OC_NON_INVERTING:
            comBits = (1 << COM01);
            break;
        case TIMER_OC_INVERTING:
            comBits = (1 << COM01) | (1 << COM00);
            break;
        default:
            return TIMER_E_INVALID_PARAM;
    }

    TCCR0 = modeBits | comBits;
    TCNT0 = (u8)TIMER0_INITIAL_VALUE;

    if (TIMER0_MODE == TIMER_MODE_CTC ||
        TIMER0_MODE == TIMER_MODE_PHASE_PWM ||
        TIMER0_MODE == TIMER_MODE_FAST_PWM)
    {
        if (!TIMER_IS_VALID_8BIT(TIMER0_COMPARE_VALUE))
        {
            return TIMER_E_OUT_OF_RANGE;
        }
        OCR0 = (u8)TIMER0_COMPARE_VALUE;
    }

    Timer_ClearClock(TIMER0);

    if (TIMER0_OVERFLOW_INTERRUPT == ENABLE)
    {
        SET_BIT(TIMSK, TOIE0);
    }
    else
    {
        CLR_BIT(TIMSK, TOIE0);
    }

    TimerStatus[TIMER0] = TIMER_STATUS_STOPPED;
    return TIMER_E_OK;
}

static u8 Timer1_ComputeWGMBits(void)
{
    u8 bits = 0;
    switch (TIMER1_MODE)
    {
        case TIMER1_NORMAL:
            bits = 0;
            break;
        case TIMER1_PWM_8_BIT:
            bits = (1 << WGM10);
            break;
        case TIMER1_PWM_9_BIT:
            bits = (1 << WGM11);
            break;
        case TIMER1_PWM_10_BIT:
            bits = (1 << WGM11) | (1 << WGM10);
            break;
        case TIMER1_CTC_OCR1A:
            bits = (1 << WGM12);
            break;
        case TIMER1_FAST_PWM_8_BIT:
            bits = (1 << WGM12) | (1 << WGM10);
            break;
        case TIMER1_FAST_PWM_9_BIT:
            bits = (1 << WGM12) | (1 << WGM11);
            break;
        case TIMER1_FAST_PWM_10_BIT:
            bits = (1 << WGM12) | (1 << WGM11) | (1 << WGM10);
            break;
        case TIMER1_PWM_PF_ICR:
            bits = (1 << WGM13);
            break;
        case TIMER1_PWM_PF_OCR1A:
            bits = (1 << WGM13) | (1 << WGM10);
            break;
        case TIMER1_PWM_PC_ICR:
            bits = (1 << WGM13) | (1 << WGM11);
            break;
        case TIMER1_PWM_PC_OCR1A:
            bits = (1 << WGM13) | (1 << WGM11) | (1 << WGM10);
            break;
        case TIMER1_CTC_ICR1:
            bits = (1 << WGM13) | (1 << WGM12);
            break;
        case TIMER1_FAST_PWM_ICR1:
            bits = (1 << WGM13) | (1 << WGM12) | (1 << WGM11);
            break;
        case TIMER1_FAST_PWM_OCR1A:
            bits = (1 << WGM13) | (1 << WGM12) | (1 << WGM11) | (1 << WGM10);
            break;
        default:
            bits = 0xFF;
            break;
    }
    return bits;
}

static Timer_Error_t Timer1_Init(void)
{
    u8 tccr1a = 0;
    u8 tccr1b = 0;
    u16 compareA = 0;
    u16 compareB = 0;

    if (!TIMER1_IS_VALID_MODE(TIMER1_MODE))
    {
        return TIMER_E_INVALID_MODE;
    }

    u8 wgmBits = Timer1_ComputeWGMBits();
    if (wgmBits == 0xFF)
    {
        return TIMER_E_INVALID_MODE;
    }

    tccr1a |= (wgmBits & ((1 << WGM11) | (1 << WGM10)));
    tccr1b |= (wgmBits & ((1 << WGM13) | (1 << WGM12)));

    switch (TIMER1_OCR1A_MODE)
    {
        case TIMER_OC_DISCONNECTED:
            break;
        case TIMER_OC_TOGGLE:
            tccr1a |= (1 << COM1A0);
            break;
        case TIMER_OC_NON_INVERTING:
            tccr1a |= (1 << COM1A1);
            break;
        case TIMER_OC_INVERTING:
            tccr1a |= (1 << COM1A1) | (1 << COM1A0);
            break;
        default:
            return TIMER_E_INVALID_PARAM;
    }

    switch (TIMER1_OCR1B_MODE)
    {
        case TIMER_OC_DISCONNECTED:
            break;
        case TIMER_OC_TOGGLE:
            tccr1a |= (1 << COM1B0);
            break;
        case TIMER_OC_NON_INVERTING:
            tccr1a |= (1 << COM1B1);
            break;
        case TIMER_OC_INVERTING:
            tccr1a |= (1 << COM1B1) | (1 << COM1B0);
            break;
        default:
            return TIMER_E_INVALID_PARAM;
    }

    if (TIMER1_INPUT_CAPTURE_NOISE == ENABLE)
    {
        SET_BIT(tccr1b, ICNC1);
    }

    if (TIMER1_INPUT_CAPTURE_EDGE == TIMER_ICP_RISING_EDGE)
    {
        SET_BIT(tccr1b, ICES1);
    }

    if (!TIMER1_IS_VALID_PRESCALER(TIMER1_PRESCALER))
    {
        return TIMER_E_INVALID_PARAM;
    }

    if (TIMER1_USE_HIGH_LEVEL_CONFIG == 1U)
    {
        if (TIMER1_MODE != TIMER1_FAST_PWM_ICR1)
        {
            return TIMER_E_INVALID_MODE;
        }

        if (TIMER1_PWM_FREQUENCY == 0UL)
        {
            return TIMER_E_INVALID_PARAM;
        }

        u32 prescalerValue = TimerPrescalerMap[TIMER1_PRESCALER];
        u32 topCalc = (F_CPU / (prescalerValue * TIMER1_PWM_FREQUENCY));
        if (topCalc == 0UL || topCalc > 65536UL)
        {
            return TIMER_E_OUT_OF_RANGE;
        }

        ICR1 = (u16)(topCalc - 1UL);
        compareA = (u16)(((u32)ICR1 * TIMER1_PWM_DUTY_A) / 100UL);
        compareB = (u16)(((u32)ICR1 * TIMER1_PWM_DUTY_B) / 100UL);
    }
    else
    {
        if (!TIMER_IS_VALID_16BIT(TIMER1_ICR_TOP) ||
            !TIMER_IS_VALID_16BIT(TIMER1_OCR1A_VALUE) ||
            !TIMER_IS_VALID_16BIT(TIMER1_OCR1B_VALUE))
        {
            return TIMER_E_OUT_OF_RANGE;
        }

        ICR1 = TIMER1_ICR_TOP;
        compareA = TIMER1_OCR1A_VALUE;
        compareB = TIMER1_OCR1B_VALUE;
    }

    OCR1A = compareA;
    OCR1B = compareB;
    TCNT1 = 0;
    TCCR1A = tccr1a;
    TCCR1B = tccr1b;
    Timer_ClearClock(TIMER1);

    if (TIMER1_OVERFLOW_INT == ENABLE)
    {
        SET_BIT(TIMSK, TOIE1);
    }
    else
    {
        CLR_BIT(TIMSK, TOIE1);
    }

    if (TIMER1_CTC_A_INT == ENABLE)
    {
        SET_BIT(TIMSK, OCIE1A);
    }
    else
    {
        CLR_BIT(TIMSK, OCIE1A);
    }

    if (TIMER1_CTC_B_INT == ENABLE)
    {
        SET_BIT(TIMSK, OCIE1B);
    }
    else
    {
        CLR_BIT(TIMSK, OCIE1B);
    }

    if (TIMER1_ICR_INT == ENABLE)
    {
        SET_BIT(TIMSK, TICIE1);
    }
    else
    {
        CLR_BIT(TIMSK, TICIE1);
    }

    TimerStatus[TIMER1] = TIMER_STATUS_STOPPED;
    return TIMER_E_OK;
}

static Timer_Error_t Timer2_Init(void)
{
    u8 modeBits = 0;
    u8 comBits = 0;

    switch (TIMER2_MODE)
    {
        case TIMER_MODE_NORMAL:
            modeBits = 0;
            break;
        case TIMER_MODE_PHASE_PWM:
            modeBits = (1 << WGM20);
            break;
        case TIMER_MODE_CTC:
            modeBits = (1 << WGM21);
            break;
        case TIMER_MODE_FAST_PWM:
            modeBits = (1 << WGM20) | (1 << WGM21);
            break;
        default:
            return TIMER_E_INVALID_MODE;
    }

    switch (TIMER2_OC_MODE)
    {
        case TIMER_OC_DISCONNECTED:
            comBits = 0;
            break;
        case TIMER_OC_TOGGLE:
            comBits = (1 << COM20);
            break;
        case TIMER_OC_NON_INVERTING:
            comBits = (1 << COM21);
            break;
        case TIMER_OC_INVERTING:
            comBits = (1 << COM21) | (1 << COM20);
            break;
        default:
            return TIMER_E_INVALID_PARAM;
    }

    TCCR2 = modeBits | comBits;
    TCNT2 = (u8)TIMER2_INITIAL_VALUE;

    if (TIMER2_MODE == TIMER_MODE_CTC ||
        TIMER2_MODE == TIMER_MODE_PHASE_PWM ||
        TIMER2_MODE == TIMER_MODE_FAST_PWM)
    {
        if (!TIMER_IS_VALID_8BIT(TIMER2_COMPARE_VALUE))
        {
            return TIMER_E_OUT_OF_RANGE;
        }
        OCR2 = (u8)TIMER2_COMPARE_VALUE;
    }

    Timer_ClearClock(TIMER2);

    if (TIMER2_OVERFLOW_INT == ENABLE)
    {
        SET_BIT(TIMSK, TOIE2);
    }
    else
    {
        CLR_BIT(TIMSK, TOIE2);
    }

    if (TIMER2_CTC_INT == ENABLE)
    {
        SET_BIT(TIMSK, OCIE2);
    }
    else
    {
        CLR_BIT(TIMSK, OCIE2);
    }

    TimerStatus[TIMER2] = TIMER_STATUS_STOPPED;
    return TIMER_E_OK;
}

static Timer_Error_t WDT_Init(void)
{
    if (!WDT_IS_VALID_PRESCALER(WDT_TIMEOUT))
    {
        return TIMER_E_INVALID_PARAM;
    }

    WDTCurrentTimeout = WDT_TIMEOUT;
    WDTCR = (1 << WDE) | (u8)WDTCurrentTimeout;
    return TIMER_E_OK;
}

Timer_Error_t Timer_Init(void)
{
    Timer_Error_t Error;

    if (TimerInitialized)
    {
        return TIMER_E_OK;
    }

    Error = Timer0_Init();
    if (Error != TIMER_E_OK)
    {
        return Error;
    }

    Error = Timer1_Init();
    if (Error != TIMER_E_OK)
    {
        return Error;
    }

    Error = Timer2_Init();
    if (Error != TIMER_E_OK)
    {
        return Error;
    }

    Error = WDT_Init();
    if (Error != TIMER_E_OK)
    {
        return Error;
    }

    TimerInitialized = 1;
    return TIMER_E_OK;
}

Timer_Error_t Timer_DeInit(void)
{
    Timer_Stop(TIMER0);
    Timer_Stop(TIMER1);
    Timer_Stop(TIMER2);

    TCCR0 = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR2 = 0;
    TCNT0 = 0;
    TCNT1 = 0;
    TCNT2 = 0;
    OCR0 = 0;
    OCR1A = 0;
    OCR1B = 0;
    OCR2 = 0;
    ICR1 = 0;
    WDT_Disable();

    TimerStatus[TIMER0] = TIMER_STATUS_STOPPED;
    TimerStatus[TIMER1] = TIMER_STATUS_STOPPED;
    TimerStatus[TIMER2] = TIMER_STATUS_STOPPED;
    TimerInitialized = 0;
    return TIMER_E_OK;
}

Timer_Error_t Timer_Start(Timer_Id_t TimerId)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            Timer_ApplyClock(TIMER0, (u8)TIMER0_PRESCALER);
            break;
        case TIMER1:
            Timer_ApplyClock(TIMER1, (u8)TIMER1_PRESCALER);
            break;
        case TIMER2:
            Timer_ApplyClock(TIMER2, (u8)TIMER2_PRESCALER);
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    TimerStatus[TimerId] = TIMER_STATUS_RUNNING;
    return TIMER_E_OK;
}

Timer_Error_t Timer_Stop(Timer_Id_t TimerId)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    Timer_ClearClock(TimerId);
    TimerStatus[TimerId] = TIMER_STATUS_STOPPED;
    return TIMER_E_OK;
}

Timer_Error_t Timer_Reset(Timer_Id_t TimerId)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            TCNT0 = 0;
            break;
        case TIMER1:
            TCNT1 = 0;
            break;
        case TIMER2:
            TCNT2 = 0;
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    return TIMER_E_OK;
}

Timer_Error_t Timer_GetCounter(Timer_Id_t TimerId, u32* pValue)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (pValue == NULL)
    {
        return TIMER_E_NULL_PTR;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            *pValue = TCNT0;
            break;
        case TIMER1:
            *pValue = TCNT1;
            break;
        case TIMER2:
            *pValue = TCNT2;
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    return TIMER_E_OK;
}

Timer_Error_t Timer_SetCounter(Timer_Id_t TimerId, u32 Value)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            if (!TIMER_IS_VALID_8BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            TCNT0 = (u8)Value;
            break;
        case TIMER1:
            if (!TIMER_IS_VALID_16BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            TCNT1 = (u16)Value;
            break;
        case TIMER2:
            if (!TIMER_IS_VALID_8BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            TCNT2 = (u8)Value;
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    return TIMER_E_OK;
}

Timer_Error_t Timer_GetCompare(Timer_Id_t TimerId, Timer_Channel_t Channel, u32* pValue)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (pValue == NULL)
    {
        return TIMER_E_NULL_PTR;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            *pValue = OCR0;
            break;
        case TIMER1:
            *pValue = (Channel == COMPARE_A) ? OCR1A : OCR1B;
            break;
        case TIMER2:
            *pValue = OCR2;
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    return TIMER_E_OK;
}

Timer_Error_t Timer_SetCompare(Timer_Id_t TimerId, Timer_Channel_t Channel, u32 Value)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    switch (TimerId)
    {
        case TIMER0:
            if (!TIMER_IS_VALID_8BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            OCR0 = (u8)Value;
            break;
        case TIMER1:
            if (!TIMER_IS_VALID_16BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            if (Channel == COMPARE_A)
            {
                OCR1A = (u16)Value;
            }
            else
            {
                OCR1B = (u16)Value;
            }
            break;
        case TIMER2:
            if (!TIMER_IS_VALID_8BIT(Value))
            {
                return TIMER_E_OUT_OF_RANGE;
            }
            OCR2 = (u8)Value;
            break;
        default:
            return TIMER_E_INVALID_ID;
    }

    return TIMER_E_OK;
}

Timer_Error_t Timer_GetStatus(Timer_Id_t TimerId, Timer_Status_t* pStatus)
{
    if (TimerId >= TIMER_MAX_ID)
    {
        return TIMER_E_INVALID_ID;
    }

    if (pStatus == NULL)
    {
        return TIMER_E_NULL_PTR;
    }

    *pStatus = TimerStatus[TimerId];
    return TIMER_E_OK;
}

Timer_Error_t Timer_GetTick(Timer_Id_t TimerId, u32* pTicks)
{
    return Timer_GetCounter(TimerId, pTicks);
}

Timer_Error_t Timer0_SetPreload(u8 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    TCNT0 = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer0_SetCompareValue(u8 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    OCR0 = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetFrequency(u16 frequency)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    if (frequency == 0U)
    {
        return TIMER_E_INVALID_PARAM;
    }

    if (TIMER1_MODE != TIMER1_FAST_PWM_ICR1)
    {
        return TIMER_E_INVALID_MODE;
    }

    u32 prescalerValue = TimerPrescalerMap[TIMER1_PRESCALER];
    if (prescalerValue == 0U)
    {
        return TIMER_E_INVALID_PARAM;
    }

    u32 topCalc = (F_CPU / (prescalerValue * (u32)frequency));
    if (topCalc == 0U || topCalc > 65536U)
    {
        return TIMER_E_OUT_OF_RANGE;
    }

    u16 topValue = (u16)(topCalc - 1U);
    ICR1 = topValue;
    OCR1A = (u16)(((u32)topValue * TIMER1_PWM_DUTY_A) / 100U);
    OCR1B = (u16)(((u32)topValue * TIMER1_PWM_DUTY_B) / 100U);
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetDutyA(u8 duty)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    if (duty > 100U)
    {
        return TIMER_E_OUT_OF_RANGE;
    }

    if (TIMER1_MODE != TIMER1_FAST_PWM_ICR1)
    {
        return TIMER_E_INVALID_MODE;
    }

    if (ICR1 == 0U)
    {
        return TIMER_E_INVALID_PARAM;
    }

    OCR1A = (u16)(((u32)ICR1 * duty) / 100U);
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetDutyB(u8 duty)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    if (duty > 100U)
    {
        return TIMER_E_OUT_OF_RANGE;
    }

    if (TIMER1_MODE != TIMER1_FAST_PWM_ICR1)
    {
        return TIMER_E_INVALID_MODE;
    }

    if (ICR1 == 0U)
    {
        return TIMER_E_INVALID_PARAM;
    }

    OCR1B = (u16)(((u32)ICR1 * duty) / 100U);
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetICR(u16 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    ICR1 = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetOCR1A(u16 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    OCR1A = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer1_SetOCR1B(u16 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    OCR1B = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer2_SetPreload(u8 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    TCNT2 = value;
    return TIMER_E_OK;
}

Timer_Error_t Timer2_SetCompareValue(u8 value)
{
    if (!TimerInitialized)
    {
        return TIMER_E_NOT_INITIALIZED;
    }

    OCR2 = value;
    return TIMER_E_OK;
}

Timer_Error_t WDT_Enable(void)
{
    WDTCurrentTimeout = WDT_TIMEOUT;
    WDTCR = (1 << WDE) | (u8)WDTCurrentTimeout;
    return TIMER_E_OK;
}

Timer_Error_t WDT_Disable(void)
{
    WDTCR = (1 << WDTOE) | (1 << WDE);
    WDTCR = 0;
    return TIMER_E_OK;
}

Timer_Error_t WDT_Refresh(void)
{
#ifdef __AVR__
    __asm__ __volatile__("wdr");
#endif
    return TIMER_E_OK;
}

Timer_Error_t WDT_SetTimeout(u8 timeout)
{
    if (!WDT_IS_VALID_PRESCALER(timeout))
    {
        return TIMER_E_INVALID_PARAM;
    }

    WDTCurrentTimeout = timeout;
    WDTCR = (1 << WDE) | (u8)WDTCurrentTimeout;
    return TIMER_E_OK;
}

/** @} */
