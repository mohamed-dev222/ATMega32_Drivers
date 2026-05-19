/**
 * @file STD_TYPES.h
 * @brief Standard data types for MCAL layer
 * @author mohamed-dev222
 * @date 2026
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Unsigned integer types */
typedef unsigned char      u8;      /**< 8-bit unsigned integer (0 to 255) */
typedef unsigned short     u16;     /**< 16-bit unsigned integer (0 to 65535) */
typedef unsigned long      u32;     /**< 32-bit unsigned integer (0 to 4294967295) */
typedef unsigned long long u64;     /**< 32-bit unsigned integer (0 to 4294967295) */

/* Signed integer types */
typedef signed char        s8;      /**< 8-bit signed integer (-128 to 127) */
typedef signed short       s16;     /**< 16-bit signed integer (-32768 to 32767) */
typedef signed long        s32;     /**< 32-bit signed integer (-2147483648 to 2147483647) */

/* Floating point types */
typedef float              f32;     /**< 32-bit floating point */
typedef double             f64;     /**< 64-bit floating point */

/* Boolean type */
typedef enum {
    FALSE = 0,                       /**< Boolean false value */
    TRUE  = 1                        /**< Boolean true value */
} bool_t;

/* Function return status */
typedef enum {
    OK       = 0,                    /**< Operation completed successfully */
    NOK      = 1,                    /**< Operation failed */
    TIMEOUT  = 2,                    /**< Operation timeout */
    INVALID  = 3                     /**< Invalid parameter */
} status_t;

/* Null pointer definition */
#define NULL ((void*)0)

#endif /* STD_TYPES_H_ */
