/**
 * @file lexer.c
 * @brief Implementation of @file lexer.h
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../../include/lexer/lexer.h"
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *source;
size_t source_len;
int32_t pos;
uint32_t line;
uint32_t column;
Keywords *keywords;

const char lex_peek(int32_t rpos);
const char lex_advance();

void lex_init_keywords(Keywords *keywords) {
    lex_add_keyword(keywords, "let", TOK_LET);
    lex_add_keyword(keywords, "fun", TOK_FUN);
    lex_add_keyword(keywords, "if", TOK_IF);
    lex_add_keyword(keywords, "else", TOK_ELSE);
    lex_add_keyword(keywords, "for", TOK_FOR);
    lex_add_keyword(keywords, "while", TOK_WHILE);
}


void lex_add_keyword(Keywords *keywords, const char *key, TokenType value) {
    keywords->entries = realloc(keywords->entries, sizeof(Entry) * (keywords->count + 1));
    keywords->entries[keywords->count++] = (Entry){key, value};
}

void lex_init(const char *src) {
    source = strdup(src);
    source_len = strlen(source);
    pos = 0;
    line = 1;
    column = 1;

    keywords = malloc(sizeof(Keywords));
    keywords->entries = malloc(0);
    keywords->count = 0;
    lex_init_keywords(keywords);
}

Token *lex_create_token(TokenType type, const char *value, uint32_t line, uint32_t column) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    token->line = line;
    token->column = column;
    return token;
}

TokenArray *lex_tokenize() {
    TokenArray *tokens = malloc(sizeof(TokenArray));
    tokens->tokens = malloc(0);
    tokens->count = 0;

    while (pos < source_len) {
        const char c = lex_peek(0);
        if (c == ' ' || c == '\n') {
            lex_advance();
        }
        else if (c == '/') {
            if (lex_peek(1) == '/') {
                skip_comment();
                continue;
            }
            else {
                lex_add_token(tokens, lex_tokenize_op());
            }
        }
        else if (isdigit(c)) {
            lex_add_token(tokens, lex_tokenize_number());
        }
        else if (isalpha(c) || c == '_') {
            lex_add_token(tokens, lex_tokenize_id());
        }
        else if (c == '\"') {
            lex_add_token(tokens, lex_tokenize_string_lit());
        }
        else if (c == '\'') {
            lex_add_token(tokens, lex_tokenize_character_lit());
        }
        else {
            lex_add_token(tokens, lex_tokenize_op());
        }
    }
    
    return tokens;
}

void lex_add_token(TokenArray *tokens, Token *token) {
    Token **new_tokens = realloc(tokens->tokens, sizeof(Token) * (tokens->count + 1));
    if (new_tokens == NULL) {
        fprintf(stderr, "Error of re-allocated memory!\n");
        exit(1);
    }
    tokens->tokens = new_tokens;
    tokens->tokens[tokens->count++] = token;
}

Token *lex_tokenize_number() {
    char *value = calloc(0, sizeof(char));
    uint32_t tmp_l = line;
    uint32_t tmp_c = column;
    bool has_dot = false;

    while (pos < source_len && (isdigit(lex_peek(0)) || lex_peek(0) == '.')) {
        if (lex_peek(0) == '.') {
            if (has_dot) {
                fprintf(stderr, "Invalid number literal: twice dot\n");
                exit(1);
            }
            has_dot = true;
        }
        value = realloc(value, sizeof(char) * (strlen(value) + 1));
        value[strlen(value)] = lex_advance();
    }
    
    return lex_create_token(TOK_NUMBER_LIT, value, tmp_l, tmp_c);
}

Token *lex_tokenize_id() {
    char *value = calloc(0, sizeof(char));
    uint32_t tmp_l = line;
    uint32_t tmp_c = column;

    while (pos < source_len && (isalpha(lex_peek(0)) || isdigit(lex_peek(0)) || lex_peek(0) == '_')) {
        value = realloc(value, sizeof(char) * (strlen(value) + 1));
        value[strlen(value)] = lex_advance();
    }

    for (size_t i = 0; i < keywords->count; i++) {
        if (strcmp(keywords->entries[i].key, value) == 0) {
            return lex_create_token(keywords->entries[i].value, value, tmp_l, tmp_c);
        }
    }

    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        return lex_create_token(TOK_BOOLEAN_LIT, value, tmp_l, tmp_c);
    }

    return lex_create_token(TOK_ID, value, tmp_l, tmp_c);
}

Token *lex_tokenize_string_lit() {
    char *value = calloc(0, sizeof(char));
    uint32_t tmp_l = line;
    uint32_t tmp_c = column;

    lex_advance();
    while (pos < source_len && lex_peek(0) != '\"') {
        value = realloc(value, sizeof(char) * (strlen(value) + 1));
        char c = lex_advance();
        if (c == '\\') {
            c = lex_get_escape_sequence();
        }
        value[strlen(value)] = c;
    }
    if (pos == source_len) {
        fprintf(stderr, "Invalid string literal: does not have closing double quote\n");
        exit(1);
    }
    lex_advance();

    return lex_create_token(TOK_STRING_LIT, value, tmp_l, tmp_c);
}

Token *lex_tokenize_character_lit() {
    char *value = calloc(0, sizeof(char));
    uint32_t tmp_l = line;
    uint32_t tmp_c = column;

    lex_advance();
    while (pos < source_len && lex_peek(0) != '\'') {
        value = realloc(value, sizeof(char) * (strlen(value) + 1));
        char c = lex_advance();
        if (c == '\\') {
            c = lex_get_escape_sequence();
        }
        value[strlen(value)] = c;
    }
    if (pos == source_len) {
        fprintf(stderr, "Invalid character literal: does not have closing single quote\n");
        exit(1);
    }
    if (strlen(value) > 1 || strlen(value) == 0) {
        fprintf(stderr, "Invalid character literal: must have a length of 1\n");
        exit(1);
    }
    lex_advance();

    return lex_create_token(TOK_CHARACTER_LIT, value, tmp_l, tmp_c);
}

Token *lex_tokenize_op() {
    const char c = lex_peek(0);
    uint32_t tmp_l = line;
    uint32_t tmp_c = column;
    switch (c) {
        case '+':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_PLUS_EQ, "+=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_PLUS, "+", tmp_l, tmp_c);
        case '-':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_MINUS_EQ, "-=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_MINUS, "-", tmp_l, tmp_c);
        case '*':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_MULT_EQ, "*=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_MULT, "*", tmp_l, tmp_c);
        case '/':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_DIV_EQ, "/=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_DIV, "/", tmp_l, tmp_c);
        case '%':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_MODULO_EQ, "%=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_MODULO, "%", tmp_l, tmp_c);
        case '=':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_EQ_EQ, "==", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_EQ, "=", tmp_l, tmp_c);
        case '!':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_NOT_EQ_EQ, "!=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_LNOT, "!", tmp_l, tmp_c);
        case '>':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_GT_EQ, ">=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_GT, ">", tmp_l, tmp_c);
        case '<':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '=') {
                lex_advance();
                return lex_create_token(TOK_OP_LS_EQ, "<=", tmp_l, tmp_c);
            }
            return lex_create_token(TOK_OP_LS, "<", tmp_l, tmp_c);
        case '&':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '&') {
                lex_advance();
                return lex_create_token(TOK_OP_LAND, "&&", tmp_l, tmp_c);
            }
            fprintf(stderr, "Operator '&' (bitwise and) does not supported\n");
        case '|':
            lex_advance();
            if (pos < source_len && lex_peek(0) == '|') {
                lex_advance();
                return lex_create_token(TOK_OP_LOR, "||", tmp_l, tmp_c);
            }
            fprintf(stderr, "Operator '|' (bitwise or) does not supported\n");
        case ',':
            lex_advance();
            return lex_create_token(TOK_OP_COMMA, ",", tmp_l, tmp_c);
        case '.':
            lex_advance();
            return lex_create_token(TOK_OP_DOT, ".", tmp_l, tmp_c);
        case ':':
            lex_advance();
            return lex_create_token(TOK_OP_COLON, ":", tmp_l, tmp_c);
        case '(':
            lex_advance();
            return lex_create_token(TOK_OP_LPAREN, "(", tmp_l, tmp_c);
        case ')':
            lex_advance();
            return lex_create_token(TOK_OP_RPAREN, ")", tmp_l, tmp_c);
        case '{':
            lex_advance();
            return lex_create_token(TOK_OP_LBRACE, "{", tmp_l, tmp_c);
        case '}':
            lex_advance();
            return lex_create_token(TOK_OP_RBRACE, "}", tmp_l, tmp_c);
        case '[':
            lex_advance();
            return lex_create_token(TOK_OP_LBRACKET, "[", tmp_l, tmp_c);
        case ']':
            lex_advance();
            return lex_create_token(TOK_OP_RBRACKET, "]", tmp_l, tmp_c);
        default:
            fprintf(stderr, "Unsupported operator: '%c' %zu\n", c, source_len);
            exit(1);
    }
}

const char lex_peek(int32_t rpos) {
    if (pos + rpos >= source_len) {
        fprintf(stderr, "Index out of range (%d/%zu)\n", pos + rpos, source_len);
        exit(1);
    }
    return source[pos + rpos];
}

const char lex_advance() {
    const char c = lex_peek(0);
    pos++;
    column++;
    if (c == '\n') {
        line++;
        column = 1;
    }
    return c;
}

const char lex_get_escape_sequence() {
    const char c = lex_advance();
    switch (c) {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case 'v':
            return '\v';
        case 'b':
            return '\b';
        case 'r':
            return '\r';
        case 'f':
            return '\f';
        case 'a':
            return '\a';
        case '\\':
            return '\\';
        case '\'':
            return '\'';
        case '"':
            return '\"';
        case '?':
            return '\?';
        default:
            fprintf(stderr, "Unsupported escape-secuence: '\\%c'\n", c);
            exit(1);
    }
}

void skip_comment() {
    lex_advance();
    lex_advance();
    while (pos < source_len && lex_peek(0) != '\n') {
        lex_advance();
    }
}