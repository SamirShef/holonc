/**
 * @file token.h
 * @brief Header file for define token structure
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>

/**
 * @brief All tokens types
 */
typedef enum : uint8_t {
    LET,                        /**< 'let' keyword for variable definition */

    INT_LIT,                    /**< Integer (32-bits) number literal */
    DOUBLE_LIT,                 /**< Floating poin (64-bits) number literal */
} TokenType;

/**
 * @brief Base token structure
 */
typedef struct {
    TokenType type;             /**< Token's type */
    const char *value;          /**< Token's string value */

    uint32_t line;              /**< Token line coordinate */
    uint32_t column;            /**< Token column coordinate */
} Token;