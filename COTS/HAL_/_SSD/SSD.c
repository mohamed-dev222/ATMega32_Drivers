#include "SSD.h"
#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"
#include "../../MCAL_/DIO/DIO.h"
#include "SSD_private.h"

static u8 Local_u8SSDNumbers[10] = SSD_NUMBERS_ARR;

void SSD_InitDataPort(SSD_Type Data)
{
    DIO_setPortDirection(Data.DataPort, DIO_PORT_OUTPUT);

    DIO_setPinDirection(Data.EnablePort, Data.EnablePin, DIO_PIN_OUTPUT);
}

void SSD_SendNumber(SSD_Type Data, u8 Value)
{
    if(Value <= 9)
    {
        if (Data.Type == SSD_COMMON_CATHODE)
        {
            DIO_setPortValue(Data.DataPort, Local_u8SSDNumbers[Value]);
        }

        else if (Data.Type == SSD_COMMON_ANODE)
        {
            DIO_setPortValue(Data.DataPort, ~Local_u8SSDNumbers[Value]);
        }
    }
}

void SSD_Enable(SSD_Type Data)
{
    if (Data.Type == SSD_COMMON_CATHODE)
    {
        DIO_setPinValue(Data.EnablePort, Data.EnablePin, DIO_PIN_HIGH);
    }

    else if (Data.Type == SSD_COMMON_ANODE)
    {
        DIO_setPinValue(Data.EnablePort, Data.EnablePin, DIO_PIN_LOW);
    }
}
void SSD_Desable(SSD_Type Data)
{
    if (Data.Type == SSD_COMMON_CATHODE)
    {
        DIO_setPinValue(Data.EnablePort, Data.EnablePin, DIO_PIN_LOW);
    }

    else if (Data.Type == SSD_COMMON_ANODE)
    {
        DIO_setPinValue(Data.EnablePort, Data.EnablePin, DIO_PIN_HIGH);
    }
}