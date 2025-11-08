/**
 * @file lexer.h
 * @brief Header file for lexing analyze of source code on Holon
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "token.h"
#include <stddef.h>

/**
 * @brief Array of tokens structure
 */
typedef struct {
    Token **tokens;                     /**< Dynamic array of tokens */
    size_t count;                       /**< Count of exist tokens */
} TokenArray;

/**
 * @brief Structure of the base element of the hash-table
 */
typedef struct {
    const char *key;                    /**< String-type hash-table key */
    TokenType value;                    /**< TokenType-type hash-table value */
} Entry;

/**
 * @brief Hash-table of keywords
 */
typedef struct {
    Entry *entries;                     /**< Dynamic array of elements */
    size_t count;                       /**< Count of elements */
} Keywords;

/**
 * @brief Function for initializing all Holon's keywords
 *
 * This function adds all Holon keywords to the global variable 'keywords'
 *
 * @param keywords Pointer to global variable 'keywords'
 */
void lex_init_keywords(Keywords *keywords);

/**
 * @brief Function for add new keyword into global variable 'keywords'
 *
 * This function adds a new keyword based on the passed values to the global variable 'keywords'
 *
 * @param keywords Pointer to global variable 'keywords'
 * @param key String-type key (keyword)
 * @param value TokenType-type value
 */
void lex_add_keyword(Keywords *keywords, const char *key, TokenType value);

/**
 * @brief Function for initialization of lexer
 *
 * @param src Source code on Holon
 */
void lex_init(const char *src);

/**
 * @brief Function for create new token
 *
 * This function create a new token based on the passed values and returns it
 *
 * @param type Token type
 * @param value Token string-type value
 * @param line Token line coordinate
 * @param column Token column coordinate
 *
 * @return Created token
 */
Token *lex_create_token(TokenType type, const char *value, uint32_t line, uint32_t column);

/**
 * @brief Function for tokenizing string
 *
 * @return List of the tokens
 */
TokenArray *lex_tokenize();

/**
 * @brief Function for add new token into array of tokens
 *
 * This function adds a new token to the array of tokens
 *
 * @param tokens Pointer to array of tokens
 * @param token Pointer to new token
 */
void lex_add_token(TokenArray *tokens, Token *token);

/**
 * @brief Funtion for tokenizing number literal
 *
 * This function tokenizing number literal and returns new token with TokenType: TOK_NUMBER_LIT
 *
 * @return Pointer to token as number literal
 */
Token *lex_tokenize_number();

/**
 * @brief Funtion for tokenizing identifier
 *
 * This function tokenizing identifier and returns new token with TokenType: TOK_ID
 *
 * @return Pointer to token as identifier
 */
Token *lex_tokenize_id();

/**
 * @brief Funtion for tokenizing string literal
 *
 * This function tokenizing string literal and returns new token with TokenType: TOK_STRING_LIT
 *
 * @return Pointer to token as string literal
 */
Token *lex_tokenize_string_lit();

/**
 * @brief Funtion for tokenizing character literal
 *
 * This function tokenizing character literal and returns new token with TokenType: TOK_CHARACTER_LIT
 *
 * @return Pointer to token as character literal
 */
Token *lex_tokenize_character_lit();

/**
 * @brief Funtion for tokenizing opeartor
 *
 * This function tokenizing opeartor and returns new token with TokenType: TOK_OP_*
 *
 * @return Pointer to token as opeartor
 */
Token *lex_tokenize_op();

/**
 * @brief Function for getting escape-secuence character
 *
 * This function determines the escape-sequence based on the current character and returns it
 *
 * @return Escape-secuence character
 */
const char lex_get_escape_sequence();

/**
 * @brief Function for skip comments in code
 *
 * This function skipping '//' comments in Holon source code
 */
void skip_comment();