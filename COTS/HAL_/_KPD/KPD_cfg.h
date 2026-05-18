#ifndef KPD_cfg_H_
#define KPD_cfg_H_
#include "../../MCAL_/MCAL_Common/STD_TYPES.h"

#define KPD_ROW_INIT DIO_PIN0
#define KPD_ROW_END DIO_PIN3

#define KPD_COL_INIT DIO_PIN4
#define KPD_COL_END DIO_PIN7

/*==============================================================================
 * Keypad Configuration Macros
 *============================================================================*/

/* Keypad dimensions */
#define KPD_ROW_START       0   /* First row pin number */
#define KPD_ROW_END         3   /* Last row pin number (4 rows total: 0,1,2,3) */
#define KPD_COL_START       4   /* First column pin number */
#define KPD_COL_END         7   /* Last column pin number (4 columns total: 4,5,6,7) */

/* Keypad port configuration - modify KPD_PORT in KPD_cfg.h */
#define KPD_PORT            DIO_PORTD   /* Keypad connected to PORTD */

/* Debouncing delay in milliseconds */
#define KPD_DEBOUNCE_DELAY_MS   30

/* Keypad character mapping (4x4 matrix) */
u8 KPD_u8Buttons[4][4] = 
{
/*   C0   C1   C2   C3   */
    {'7','8', '9', '/'}, /* Row0 */ 
    {'4','5', '6', '*'},  /* Row1 */
    {'1','2', '3', '-'},  /* Row2 */
    {'?','0', '=', '+'}   /* Row3 */

};

#endif 