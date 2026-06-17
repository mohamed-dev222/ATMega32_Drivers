/**
 * @file CLCD.c
 * @brief Source file for Character LCD driver
 * @description Implementation of LCD control APIs supporting both 4-bit and 8-bit modes
 * @author mohamed-dev222
 * @date 2026
 */

#include "././LIP/STD_TYPES.h"
#include "././LIP/BIT_MATH.h"
#include "../../MCAL_/DIO/DIO.h"
#include "CLCD_cfg.h"
#include "CLCD.h"
#include "CLCD_extrachar.h"
#include "CLCD_private.h"

// #include <util/delay.h>
#include <stdlib.h>

/***************************************************************************************/

/*
 * LCD 8-Bit Mode Connection Diagram
 * -----------                   ----------
 * | ATmega32  |                 |   LCD    |
 * |           |                 |          |
 * |        PA7|---------------->|D7        |
 * |        PA6|---------------->|D6        |
 * |        PA5|---------------->|D5        |
 * |        PA4|---------------->|D4        |
 * |        PA3|---------------->|D3        |
 * |        PA2|---------------->|D2        |
 * |        PA1|---------------->|D1        |
 * |        PA0|---------------->|D0        |
 * |           |                 |          |
 * |        PC2|---------------->|E         |
 * |        PC1|---------------->|RW        |
 * |        PC0|---------------->|RS        |
 * -----------                   ----------
 */
/***************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Initializes the LCD module with proper initialization sequence
 * @param void
 * @return void
 */
void CLCD_voidInit(void)
{
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if CLCD_MODE == 8

    /* Wait more than 30 ms for VDD to rise to 4.5V */
    _delay_ms(50);

    /* Configure all LCD pins as output */
    DIO_setPortDirection(CLCD_DATA_PORT, DIO_PORT_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_OUTPUT);

    /* Return cursor to home position (first line, first column) */
    CLCD_voidSendCommand(lcd_Home);
    _delay_ms(1);

    /* Function Set Command: 2 lines, 5x8 font size, 8-bit mode */
    CLCD_voidSendCommand(EIGHT_BITS); // 0x38 for 8-bit mode
    _delay_ms(1);                     /* Wait more than 39 ms */

    /* Display ON, Cursor OFF control */
    CLCD_voidSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /* Clear display screen */
    CLCD_voidClearScreen();

    /* Entry mode set (increment cursor, no shift) */
    CLCD_voidSendCommand(lcd_EntryMode);
    _delay_ms(1);

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif CLCD_MODE == 4

    /* Wait more than 30 ms for VDD to rise to 4.5V */
    _delay_ms(50);

    /* Configure data pins (P4-P7) and control pins as output */
    DIO_setPinDirection(CLCD_DATA_PORT, DIO_PIN4, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_DATA_PORT, DIO_PIN5, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_DATA_PORT, DIO_PIN6, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_DATA_PORT, DIO_PIN7, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_OUTPUT);
    DIO_setPinDirection(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_OUTPUT);

    /* Return cursor to home position */
    CLCD_voidSendCommand(lcd_Home);
    _delay_ms(30);

    /* Function Set Command for 4-bit mode */
    CLCD_voidSendCommand(FOUR_BITS);
    _delay_ms(1);

    /* Display ON, Cursor OFF control */
    CLCD_voidSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /* Clear display screen */
    CLCD_voidClearScreen();

    /* Entry mode set (increment cursor, no shift) */
    CLCD_voidSendCommand(lcd_EntryMode);
    _delay_ms(1);

#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Sends data byte to be displayed on LCD
 * @param Copy_u8Data - Data byte to display (character code)
 * @return void
 */
void CLCD_voidSendData(u8 Copy_u8Data)
{
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if CLCD_MODE == 8

    /* Output data to data port */
    DIO_setPortValue(CLCD_DATA_PORT, Copy_u8Data);
    /* Set RS high for data mode */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_HIGH);
    /* Set RW low for write operation */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);
    /* Generate enable pulse */
    CLCD_voidSendFallingEdge();

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif CLCD_MODE == 4

    /* Set RS high for data mode */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_HIGH);
    /* Set RW low for write operation */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);

    /* Send high nibble (bits 7-4) first */
    DIO_WriteHighNibbles(CLCD_DATA_PORT, (Copy_u8Data >> 4));
    CLCD_voidSendFallingEdge();

    /* Send low nibble (bits 3-0) */
    DIO_WriteHighNibbles(CLCD_DATA_PORT, Copy_u8Data);
    CLCD_voidSendFallingEdge();

#endif

    /* Short delay for LCD to process data */
    _delay_ms(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Sends command byte to LCD controller
 * @param Copy_u8Command - Command byte to send
 * @return void
 * @note RS pin is set low for command mode (vs high for data mode)
 */
void CLCD_voidSendCommand(u8 Copy_u8Command)
{
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if CLCD_MODE == 8

    /* Output command to data port */
    DIO_setPortValue(CLCD_DATA_PORT, Copy_u8Command);
    /* Set RS low for command mode */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_LOW);
    /* Set RW low for write operation (RW connected to GND for write-only) */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);
    /* Generate enable pulse */
    CLCD_voidSendFallingEdge();

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif CLCD_MODE == 4

    /* Set RS low for command mode */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RS, DIO_PIN_LOW);
    /* Set RW low for write operation */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_RW, DIO_PIN_LOW);

    /* Send high nibble (bits 7-4) first */
    DIO_WriteHighNibbles(CLCD_DATA_PORT, (Copy_u8Command >> 4));
    CLCD_voidSendFallingEdge();

    /* Send low nibble (bits 3-0) */
    DIO_WriteHighNibbles(CLCD_DATA_PORT, Copy_u8Command);
    CLCD_voidSendFallingEdge();

#endif

    /* Short delay for LCD to process command */
    _delay_ms(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Sends a string to be displayed on LCD
 * @param Copy_u8ptrString - Pointer to null-terminated string
 * @return void
 */
void CLCD_voidSendString(const u8 *Copy_u8ptrString)
{
    u8 LOC_u8Iterator = 0;

    /* Iterate through string until null terminator */
    while (Copy_u8ptrString[LOC_u8Iterator] != '\0')
    {
        /* Send each character to LCD */
        CLCD_voidSendData(Copy_u8ptrString[LOC_u8Iterator]);
        LOC_u8Iterator++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Converts and sends a number to be displayed on LCD
 * @param Copy_u64Number - Number to display
 * @return void
 */
void CLCD_voidSendNumber(u64 Copy_u64Number)
{
    u64 LOC_u64Reversed = 1;

    /* Handle zero case */
    if (Copy_u64Number == 0)
    {
        CLCD_voidSendData('0');
    }
    else
    {
        /* Reverse the number digits */
        while (Copy_u64Number != 0)
        {
            LOC_u64Reversed = (LOC_u64Reversed * 10) + (Copy_u64Number % 10);
            Copy_u64Number /= 10;
        }

        /* Send each digit by extracting from reversed number */
        while (LOC_u64Reversed != 1)
        {
            /* Convert digit to ASCII by adding 48 ('0') */
            CLCD_voidSendData((LOC_u64Reversed % 10) + 48);
            LOC_u64Reversed /= 10;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Sets cursor position on LCD screen
 * @param Copy_u8Row - Row number (CLCD_ROW_1 or CLCD_ROW_2)
 * @param Copy_u8Col - Column number (CLCD_COL_1 to CLCD_COL_16)
 * @return void
 * @note Command format: 0b1xxxxxxx where MSB=1 indicates set cursor command
 *       and remaining 7 bits are address counter for DDRAM (128 locations)
 */
void CLCD_voidSetPosition(u8 Copy_u8Row, u8 Copy_u8Col)
{
    u8 LOC_u8data;

    /* Validate input parameters, default to (0,0) if invalid */
    if (Copy_u8Row > 2 || Copy_u8Row < 1 || Copy_u8Col > 16 || Copy_u8Col < 1)
    {
        LOC_u8data = lcd_SetCursor; /* First location (row 1, column 0) */
    }
    else if (Copy_u8Row == CLCD_ROW_1)
    {
        /* Row 1: DDRAM address starts at 0x80 */
        LOC_u8data = (lcd_SetCursor + (Copy_u8Col - 1));
    }
    else if (Copy_u8Row == CLCD_ROW_2)
    {
        /* Row 2: DDRAM address starts at 0xC0 (0x80 + 64) */
        LOC_u8data = (lcd_SetCursor + 64 + (Copy_u8Col - 1));
    }

    /* Send command to set cursor position */
    CLCD_voidSendCommand(LOC_u8data);
    _delay_ms(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Displays a custom character from CGRAM
 * @param Copy_u8Row - Row number (CLCD_ROW_1 or CLCD_ROW_2)
 * @param Copy_u8Col - Column number (CLCD_COL_1 to CLCD_COL_16)
 * @return void
 * @note Address counter can reference both CGRAM and DDRAM
 */
void CLCD_voidSendExtraChar(u8 Copy_u8Row, u8 Copy_u8Col)
{
    u8 LOC_u8Iterator = 0;

    /* Step 1: Move to CGRAM start address */
    CLCD_voidSendCommand(lcd_CGRAM);

    /* Step 2: Write custom character pattern to CGRAM */
    for (LOC_u8Iterator = 0; LOC_u8Iterator < (sizeof(CLCD_u8ExtraChar) / sizeof(CLCD_u8ExtraChar[0])); LOC_u8Iterator++)
    {
        CLCD_voidSendData(CLCD_u8ExtraChar[LOC_u8Iterator]);
    }

    /* Step 3: Return address counter to DDRAM */
    CLCD_voidSetPosition(Copy_u8Row, Copy_u8Col);

    /* Step 4: Display the custom character by sending its CGRAM address (0-7) */
    for (LOC_u8Iterator = 0; LOC_u8Iterator < 8; LOC_u8Iterator++)
    {
        CLCD_voidSendData(LOC_u8Iterator);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Clears the LCD display and returns cursor to home
 * @param void
 * @return void
 */
void CLCD_voidClearScreen(void)
{
    CLCD_voidSendCommand(lcd_Clear);
    _delay_ms(10); /* Wait more than 1.53 ms for clear operation */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Generates a falling edge pulse on the Enable pin
 * @param void
 * @return void
 * @note Static function - only callable within this file
 */
static void CLCD_voidSendFallingEdge(void)
{
    /* Set Enable pin high */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_HIGH);
    _delay_ms(1);

    /* Set Enable pin low (creates falling edge) */
    DIO_setPinValue(CLCD_CONTROL_PORT, CLCD_EN, DIO_PIN_LOW);
    _delay_ms(1);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>