/**
 * @file chunk.c
 * @brief Implementation of @file chunk.h
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../../include/vm/chunk.h"
#include <stdlib.h>

/**
 * @brief Function for create chunk
 *
 * This function creates a new chunk in memory, initializes it with zeros, and returns it
 * 
 * @return Pointer to new chunk
 */
Chunk *create_chunk() {
    Chunk *chunk = (Chunk *)malloc(sizeof(Chunk));
    chunk->count = 0;
    return chunk;
}

/**
 * @brief Function for add new operation code into chunk
 *
 * This function adds the passed opcode to the chunk and increments the count of exists codes in chunk
 *
 * @param chunk Pointer to the chunk
 * @param code Operation code
 */
void add_code(Chunk *chunk, OpCode code) {
    chunk->code[chunk->count++] = code;
}

/**
 * @brief Function to free up the memory allocated for the chunk
 *
 * This function deletes an array of chunk operation codes from memory and deletes the chunk itself
 *
 * @param chunk Pointer to the chunk
 */
void free_chunk(Chunk *chunk) {
    free(chunk->code);
    free(chunk);
}