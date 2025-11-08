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

    while (pos < source_len) {
        const char c = lex_peek(0);
        if (c == ' ' || c == '\n') {
            lex_advance();
        }
        else if (isdigit(c)) {
            lex_add_token(tokens, lex_tokenize_number());
        }
        else if (isalpha(c) || c == '_') {
            lex_add_token(tokens, lex_tokenize_id());
        }
    }
    
    return tokens;
}

void lex_add_token(TokenArray *tokens, Token *token) {
    tokens->tokens = realloc(tokens->tokens, sizeof(Token) * (tokens->count + 1));
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
                fprintf(stderr, "Invalid number literal (twice dot)\n");
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

// Unuse yet
Token *lex_tokenize_string_lit() {

}

// Unuse yet
Token *lex_tokenize_char_lit() {

}

// Unuse yet
Token *lex_tokenize_op() {

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