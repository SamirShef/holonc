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
    TOK_LET,                                /**< 'let' keyword for variable definition */
    TOK_FUN,                                /**< 'fun' keyword for function definition */
    TOK_IF,                                 /**< 'if' keyword for conditionally expression operator */
    TOK_ELSE,                               /**< 'else' keyword for else branch in conditionally expression operator */
    TOK_FOR,                                /**< 'for' keyword for `for` cycle definition */
    TOK_WHILE,                              /**< 'while' keyword for `while` cycle definition */

    TOK_ID,                                 /**< Identifier */
    TOK_NUMBER_LIT,                         /**< Decimal number literal */
    TOK_STRING_LIT,                         /**< String literal */
    TOK_BOOLEAN_LIT                         /**< Boolean literal */
} TokenType;

/**
 * @brief Base token structure
 */
typedef struct {
    TokenType type;                         /**< Token's type */
    const char *value;                      /**< Token's string value */

    uint32_t line;                          /**< Token line coordinate */
    uint32_t column;                        /**< Token column coordinate */
} Token;