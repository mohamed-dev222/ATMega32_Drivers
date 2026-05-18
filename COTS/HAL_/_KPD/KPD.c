#include "KPD.h"
#include "KPD_cfg.h"
#include "../../MCAL_/DIO/DIO.h"

void KPD_Init(void)
{
    u8 i = 0;
    
    /* Initialize rows as input with pull-up resistors */
    for (i = KPD_ROW_START; i <= KPD_ROW_END; i++)
    {
        DIO_ConnectPullup(KPD_PORT, i);
    }
    
    /* Initialize columns as output and set them HIGH */
    for (i = KPD_COL_START; i <= KPD_COL_END; i++)
    {
        DIO_setPinDirection(KPD_PORT, i, DIO_PIN_OUTPUT);
        DIO_setPinValue(KPD_PORT, i, DIO_PIN_HIGH);
    }
}

u8 KPD_u8GetPressed(void)
{
    u8 LOC_u8Col;
    u8 LOC_u8Row;
    u8 LOC_u8PinState = 0;
    u8 LOC_u8ReturnData = NOTPRESSED;
    
    /* Scan each column */
    for (LOC_u8Col = KPD_COL_START; LOC_u8Col <= KPD_COL_END; LOC_u8Col++)
    {
        /* Drive current column LOW */
        DIO_setPinValue(KPD_PORT, LOC_u8Col, DIO_PIN_LOW);
        
        /* Check all rows */
        for (LOC_u8Row = KPD_ROW_START; LOC_u8Row <= KPD_ROW_END; LOC_u8Row++)
        {
            DIO_getPinValue(KPD_PORT, LOC_u8Row, &LOC_u8PinState);
            
            if (LOC_u8PinState == DIO_PIN_LOW)
            {
                _delay_ms(50);  /* Debounce delay */
                
                /* Verify key is still pressed */
                DIO_getPinValue(KPD_PORT, LOC_u8Row, &LOC_u8PinState);
                
                if (LOC_u8PinState == DIO_PIN_LOW)
                {
                    /* Get the pressed key from mapping table */
                    LOC_u8ReturnData = KPD_u8Buttons[LOC_u8Row - KPD_ROW_START]
                                                   [LOC_u8Col - KPD_COL_START];
                    
                    /* Wait for key to be released */
                    while (DIO_PIN_LOW == LOC_u8PinState)
                    {
                        DIO_getPinValue(KPD_PORT, LOC_u8Row, &LOC_u8PinState);
                    }
                }
                break;  /* Exit row loop once key is found */
            }
        }
        /* Return column to HIGH */
        DIO_setPinValue(KPD_PORT, LOC_u8Col, DIO_PIN_HIGH);
    }
    return LOC_u8ReturnData;
}