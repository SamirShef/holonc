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

int main(int argc, const char *argv[]) {
    lex_init("_aw2 123 12.3 let awda \'\\n\' \"Hello Holon!\"+ += && /");
    TokenArray *tokens = lex_tokenize();
    for (size_t i = 0; i < tokens->count; i++) {
        printf("%02d : '%s' (%d:%d)\n", tokens->tokens[i]->type, tokens->tokens[i]->value, tokens->tokens[i]->line, tokens->tokens[i]->column);
    }
    
    Chunk *chunk = create_chunk();
    add_code(chunk, OP_RETURN);
    add_code(chunk, OP_RETURN);
    disassembly_chunk(chunk);
    VM *vm = create_vm(chunk);
    free_vm(vm);
    return 0;
}