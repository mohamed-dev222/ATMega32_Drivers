/**
 * @file DIO.c
 * @brief Implementation of Digital Input/Output driver
 * @author mohamed-dev222
 * @date 2026
 */

#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"
#include "DIO_cfg.h"
#include "DIO.h"
#include "DIO_private.h"

/*==============================================================================
 * Helper Macros for Range Validation
 *============================================================================*/
#define IS_VALID_PORT(PORT)     ((PORT) <= DIO_PORTD)
#define IS_VALID_PIN(PIN)       ((PIN) <= DIO_PIN7)

/*==============================================================================
 * Pin Control Functions Implementation
 *============================================================================*/

status_t DIO_setPinDirection(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Direction)
{
    /* Validate input parameters */
    if (!IS_VALID_PORT(Copy_u8PORT) || !IS_VALID_PIN(Copy_u8PIN))
    {
        return NOK;
    }
    
    /* Set or clear the direction bit based on requested direction */
    if (Copy_u8Direction == DIO_PIN_OUTPUT)
    {
        SET_BIT(*DDR_REG[Copy_u8PORT], Copy_u8PIN);
    }
    else if (Copy_u8Direction == DIO_PIN_INPUT)
    {
        CLR_BIT(*DDR_REG[Copy_u8PORT], Copy_u8PIN);
    }
    else
    {
        return NOK;  /* Invalid direction value */
    }
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_setPinValue(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Value)
{
    /* Validate input parameters */
    if (!IS_VALID_PORT(Copy_u8PORT) || !IS_VALID_PIN(Copy_u8PIN))
    {
        return NOK;
    }
    
    /* Set or clear the pin based on requested value */
    if (Copy_u8Value == DIO_PIN_HIGH)
    {
        SET_BIT(*PORT_REG[Copy_u8PORT], Copy_u8PIN);
    }
    else if (Copy_u8Value == DIO_PIN_LOW)
    {
        CLR_BIT(*PORT_REG[Copy_u8PORT], Copy_u8PIN);
    }
    else
    {
        return NOK;  /* Invalid value */
    }
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_getPinValue(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 *Copy_ptrData)
{
    /* Validate input parameters and ensure pointer is not NULL */
    if (!IS_VALID_PORT(Copy_u8PORT) || !IS_VALID_PIN(Copy_u8PIN) || (Copy_ptrData == NULL))
    {
        return NOK;
    }
    
    /* Read pin state from PIN register (actual hardware state) */
    *Copy_ptrData = GET_BIT(*PIN_REG[Copy_u8PORT], Copy_u8PIN);
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_togglePinValue(u8 Copy_u8PORT, u8 Copy_u8PIN)
{
    /* Validate input parameters */
    if (!IS_VALID_PORT(Copy_u8PORT) || !IS_VALID_PIN(Copy_u8PIN))
    {
        return NOK;
    }
    
    /* Toggle the pin value using XOR operation */
    TOG_BIT(*PORT_REG[Copy_u8PORT], Copy_u8PIN);
    
    return OK;
}

/*==============================================================================
 * Port Control Functions Implementation
 *============================================================================*/

status_t DIO_setPortDirection(u8 Copy_u8PORT, u8 Copy_u8Direction)
{
    /* Validate port number */
    if (!IS_VALID_PORT(Copy_u8PORT))
    {
        return NOK;
    }
    
    /* Write entire direction byte to DDR register */
    *DDR_REG[Copy_u8PORT] = Copy_u8Direction;
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_setPortValue(u8 Copy_u8PORT, u8 Copy_u8Value)
{
    /* Validate port number */
    if (!IS_VALID_PORT(Copy_u8PORT))
    {
        return NOK;
    }
    
    /* Write entire value byte to PORT register */
    *PORT_REG[Copy_u8PORT] = Copy_u8Value;
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_getPortValue(u8 Copy_u8PORT, u8 *Copy_ptrData)
{
    /* Validate port number and ensure pointer is not NULL */
    if (!IS_VALID_PORT(Copy_u8PORT) || (Copy_ptrData == NULL))
    {
        return NOK;
    }
    
    /* Read entire port state from PIN register (actual hardware states) */
    *Copy_ptrData = *PIN_REG[Copy_u8PORT];
    
    return OK;
}

/*----------------------------------------------------------------------------*/

status_t DIO_togglePortValue(u8 Copy_u8PORT)
{
    /* Validate port number */
    if (!IS_VALID_PORT(Copy_u8PORT))
    {
        return NOK;
    }
    
    /* Toggle all pins by writing the bitwise complement */
    *PORT_REG[Copy_u8PORT] = ~(*PORT_REG[Copy_u8PORT]);
    
    return OK;
}

/*----------------------------------------------------------------------------*/
status_t DIO_WriteLowNibbles(u8 Copy_u8PORT, u8 Copy_u8value)
{
    if (Copy_u8PORT <= DIO_PORTD)
    {
        Copy_u8value &= 0x0F;

        /* ensure low nibble is output */
        *DDR_REG[Copy_u8PORT] |= 0x0F;

        /* safe read-modify-write */
        *PORT_REG[Copy_u8PORT] = (*PORT_REG[Copy_u8PORT] & 0xF0) | Copy_u8value;
        return OK;
    }
    else
    {
        return NOK;
    }
}

status_t DIO_WriteHighNibbles(u8 Copy_u8PORT, u8 Copy_u8value)
{
    if (Copy_u8PORT <= DIO_PORTD)
    {
        Copy_u8value = (Copy_u8value << 4) & 0xF0;

        /* ensure high nibble is output */
        *DDR_REG[Copy_u8PORT] |= 0xF0;

        /* safe read-modify-write */
        *PORT_REG[Copy_u8PORT] = (*PORT_REG[Copy_u8PORT] & 0x0F) | Copy_u8value;

        return OK;
    }
    else
    {
        return NOK;
    }
}

status_t DIO_ConnectPullup(u8 Copy_u8PORT ,u8 Copy_u8PIN)
{
    status_t ReturnStatus = OK;
    status_t LocalStatus = OK;
    
    /* Parameter validation */
    if (Copy_u8PORT > DIO_PORTD || Copy_u8PIN > DIO_PIN7)
    {
        return NOK;
    }
    else
    {
        /* Set pin as input */
        LocalStatus = DIO_setPinDirection(Copy_u8PORT, Copy_u8PIN, DIO_PIN_INPUT);
        if (LocalStatus != OK)
        {
            ReturnStatus = NOK;
        }
        
        /* Enable pull-up resistor by setting pin HIGH */
        LocalStatus = DIO_setPinValue(Copy_u8PORT, Copy_u8PIN, DIO_PIN_HIGH);
        if (LocalStatus != OK)
        {
            ReturnStatus = NOK;
        }
    }
    
    return ReturnStatus;
}

/*==============================================================================
 * End of File
 *============================================================================*/