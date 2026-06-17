/**
 * @file BIT_MATH.h
 * @brief Bit manipulation macros for register operations
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/**
 * @brief Set a specific bit in a register
 * @param REG: Target register
 * @param BIT: Bit position (0-7)
 */
#define SET_BIT(REG, BIT)     ((REG) |= (1 << (BIT)))

/**
 * @brief Clear a specific bit in a register
 * @param REG: Target register
 * @param BIT: Bit position (0-7)
 */
#define CLR_BIT(REG, BIT)     ((REG) &= ~(1 << (BIT)))

/**
 * @brief Toggle a specific bit in a register
 * @param REG: Target register
 * @param BIT: Bit position (0-7)
 */
#define TOG_BIT(REG, BIT)     ((REG) ^= (1 << (BIT)))

/**
 * @brief Read a specific bit from a register
 * @param REG: Target register
 * @param BIT: Bit position (0-7)
 * @return Value of the bit (0 or 1)
 */
#define GET_BIT(REG, BIT)     (((REG) >> (BIT)) & 0x01)

/**
 * @brief Assign a value to a specific bit
 * @param REG: Target register
 * @param BIT: Bit position (0-7)
 * @param VAL: Value to assign (0 or 1)
 */
#define ASSIGN_BIT(REG, BIT, VAL)  do { \
    if (VAL) SET_BIT(REG, BIT); \
    else CLR_BIT(REG, BIT); \
} while(0)

/**
 * @brief Set multiple bits at once (bitmask)
 * @param REG: Target register
 * @param MASK: Bitmask of bits to set
 */
#define SET_MASK(REG, MASK)   ((REG) |= (MASK))

/**
 * @brief Clear multiple bits at once (bitmask)
 * @param REG: Target register
 * @param MASK: Bitmask of bits to clear
 */
#define CLR_MASK(REG, MASK)   ((REG) &= ~(MASK))

/**
 * @brief Get multiple bits (bitmask)
 * @param REG: Target register
 * @param MASK: Bitmask to extract
 * @return Extracted bits shifted to LSB
 */
#define GET_MASK(REG, MASK)   (((REG) & (MASK)) >> __builtin_ctz(MASK))

#endif /* BIT_MATH_H_ */