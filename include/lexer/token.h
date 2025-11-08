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

    TOK_NUMBER_LIT,                         /**< Decimal number literal */
    TOK_ID,                                 /**< Identifier */
    TOK_BOOLEAN_LIT,                        /**< Boolean literal */
    TOK_STRING_LIT,                         /**< String literal */
    TOK_CHARACTER_LIT,                      /**< String literal */

    TOK_OP_PLUS,                            /**< '+' operator */
    TOK_OP_PLUS_EQ,                         /**< '+=' operator */
    TOK_OP_MINUS,                           /**< '-' operator */
    TOK_OP_MINUS_EQ,                        /**< '-=' operator */
    TOK_OP_MULT,                            /**< '*' operator */
    TOK_OP_MULT_EQ,                         /**< '*=' operator */
    TOK_OP_DIV,                             /**< '/' operator */
    TOK_OP_DIV_EQ,                          /**< '/=' operator */
    TOK_OP_MODULO,                          /**< '%' operator */
    TOK_OP_MODULO_EQ,                       /**< '%=' operator */
    TOK_OP_EQ,                              /**< '=' operator */
    TOK_OP_EQ_EQ,                           /**< '==' operator */
    TOK_OP_NOT_EQ_EQ,                       /**< '!=' operator */
    TOK_OP_GT,                              /**< '>' operator */
    TOK_OP_GT_EQ,                           /**< '>=' operator */
    TOK_OP_LS,                              /**< '<' operator */
    TOK_OP_LS_EQ,                           /**< '<=' operator */
    TOK_OP_LAND,                            /**< '&&' (logical and) operator */
    TOK_OP_LOR,                             /**< '||' (logical or) operator */
    TOK_OP_LNOT,                            /**< '!' (logical negative) operator */
    TOK_OP_COMMA,                           /**< ',' operator */
    TOK_OP_DOT,                             /**< '.' operator */
    TOK_OP_COLON,                           /**< ':' operator */
    TOK_OP_LPAREN,                          /**< '(' operator */
    TOK_OP_RPAREN,                          /**< ')' operator */
    TOK_OP_LBRACE,                          /**< '{' operator */
    TOK_OP_RBRACE,                          /**< '}' operator */
    TOK_OP_LBRACKET,                        /**< '[' operator */
    TOK_OP_RBRACKET                         /**< ']' operator */
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