/**
 * @file chunk.c
 * @brief Implementation of @file chunk.h
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../../include/vm/chunk.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Chunk *create_chunk() {
    Chunk *chunk = (Chunk *)malloc(sizeof(Chunk));
    chunk->code = malloc(0);
    chunk->count = 0;
    return chunk;
}

void add_code(Chunk *chunk, OpCode code) {
    chunk->code = realloc(chunk->code, sizeof(uint8_t) * (chunk->count + 1));
    chunk->code[chunk->count++] = code;
}

void free_chunk(Chunk *chunk) {
    free(chunk->code);
    free(chunk);
}

void disassembly_chunk(Chunk *chunk) {
    for (size_t i = 0; i < chunk->count; i++) {
        print_instruction(chunk->code[i]);
    }
}

void print_instruction(OpCode code) {
    printf("%04d %s\n", code, instruction_name_by_code(code));
}

const char *instruction_name_by_code(OpCode code) {
    switch (code) {
        case OP_RETURN:
            return "RETURN";
        default:
            fprintf(stderr, "Unknown operation code: %04d\n", code);
            exit(1);
    }
}