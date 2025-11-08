/**
 * @file main.c
 * @brief Compilator's entry point
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../include/vm/vm.h"
#include "../include/lexer/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Use: holonc path/to/source.hn\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "File '%s' does not exist!\n", argv[1]);
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
    char *buffer = malloc(sizeof(char) * (file_size + 1));
    size_t readed_bytes = fread(buffer, sizeof(char), file_size, file);
    buffer[readed_bytes] = '\0';
    fclose(file);

    lex_init(buffer);
    TokenArray *tokens = lex_tokenize();
    return 0;
}