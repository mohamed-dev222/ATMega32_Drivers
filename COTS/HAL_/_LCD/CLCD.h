/**
 * @file CLCD.h
 * @brief Public header for Character LCD (16x2) driver
 * @description This is the only file the user application should include.
 *              Provides APIs to control a 16x2 character LCD connected to AVR GPIO pins.
 *              Supports both 4-bit and 8-bit modes, cursor positioning and basic LCD commands.
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#include "././LIP/STD_TYPES.h"
#include "CLCD_cfg.h"

#if CLCD_MODE == 4
#define FOUR_BITS 0x28 // 4 bits mode initialization
#elif CLCD_MODE == 8
#define EIGHT_BITS 0x38 // 8 bits mode initialization (8-bit data, 2-line display, 5 x 7 font )
#endif
/********/
/*==============================================================================
 * LCD Commands Macros
 *============================================================================*/

#define lcd_DisplayOn_CursorOff 0x0c  // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn 0x0e   // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff 0x08 // turn display off
#define lcd_Clear 0x01                // replace all characters with ASCII 'space'
#define lcd_EntryMode 0x06            // shift cursor from left to right on read/write
#define lcd_Home 0x02                 // return cursor to first position on first line
#define lcd_CGRAM 0x40                // the first Place/Address at CGRAM
#define lcd_SetCursor 0x80            // set cursor position
#define lcd_FunctionReset 0x30        // reset the LCD
/*==============================================================================
 * LCD Rows Identification Macros (1-based indexing)
 *============================================================================*/

#define CLCD_ROW_1 1 /**< First row of the LCD */
#define CLCD_ROW_2 2 /**< Second row of the LCD */

/*==============================================================================
 * LCD Columns Identification Macros (1 to 16)
 *============================================================================*/

#define CLCD_COL_1 1
#define CLCD_COL_2 2
#define CLCD_COL_3 3
#define CLCD_COL_4 4
#define CLCD_COL_5 5
#define CLCD_COL_6 6
#define CLCD_COL_7 7
#define CLCD_COL_8 8
#define CLCD_COL_9 9
#define CLCD_COL_10 10
#define CLCD_COL_11 11
#define CLCD_COL_12 12
#define CLCD_COL_13 13
#define CLCD_COL_14 14
#define CLCD_COL_15 15
#define CLCD_COL_16 16

/*==============================================================================
 * Helper Macro for Cursor Positioning
 *============================================================================*/

/**
 * @brief Calculate DDRAM address for given row and column
 * @param row: Row number (1-2)
 * @param col: Column number (1-16)
 * @note First row addresses: 0x00 to 0x0F
 *       Second row addresses: 0x40 to 0x4F
 */
#define LCD_GET_DDRAM_ADDRESS(row, col) (LCD_DDRAM_ADDRESS | ((row == 1) ? ((col) - 1) : (0x40 + (col) - 1)))

/*==============================================================================
 * LCD Control APIs
 *============================================================================*/

/**
 * @brief Initialize the LCD in 4-bit or 8-bit mode
 * @note This function must be called before any other LCD functions
 * @warning Required delay after power-up is handled inside this function
 */
void CLCD_voidInit(void);

/**
 * @brief Send a character to be displayed on the LCD
 * @param Copy_u8Data: The ASCII character to display (0-255)
 * @note The cursor automatically increments after each character
 */
void CLCD_voidSendData(u8 Copy_u8Data);

/**
 * @brief Send a command to the LCD
 * @param Copy_u8Command: The command byte to execute
 * @note Refer to LCD datasheet for available commands
 */
void CLCD_voidSendCommand(u8 Copy_u8Commend);

/**
 * @brief Clear the LCD screen and return cursor to home position
 * @note This operation takes approximately 2ms
 */
void CLCD_voidClearScreen(void);

/**
 * @brief Display a string on the LCD
 * @param Copy_pcString: Pointer to the string to display
 * @note The string must be null-terminated
 */
void CLCD_voidSendString(const u8 *Copy_u8ptrString);

/**
 * @brief Display a number on the LCD
 * @param Copy_u32Number: Number to display (0 to 4294967295)
 */
void CLCD_voidSendNumber(u64 Copy_u64Number);

/**
 * @brief Store a custom character in CGRAM
 * @param Copy_u8Location: CGRAM location (0 to 7)
 * @param Copy_pu8Pattern: Pointer to 8-byte pattern array
 * @note Each pattern is 8 bytes representing 5x8 pixel character
 */
// void CLCD_voidStoreCustomChar(u8 Copy_u8Location, const u8* Copy_pu8Pattern);
/**
 * @brief Set cursor position on the LCD
 * @param Copy_u8Row: Row number (CLCD_ROW_1 or CLCD_ROW_2)
 * @param Copy_u8Col: Column number (CLCD_COL_1 to CLCD_COL_16)
 * @example CLCD_voidSetCursor(CLCD_ROW_1, CLCD_COL_5);
 */
// void CLCD_voidSetCursor(u8 Copy_u8Row, u8 Copy_u8Col);

#endif /* CLCD_INTERFACE_H_ */