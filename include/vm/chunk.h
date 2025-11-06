/**
 * @file chunk.h
 * @brief Header file for define chunk structure
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdint.h>
#define MAX_CHANK_CODES_COUNT 256           /**< Maximum count of operations codes in chunk */

/**
 * @brief All bytecode's operations codes
 */
typedef enum : uint8_t {
    OP_RETURN,                  /**< 'return' operator instruction */
} OpCode;

/**
 * @brief Base chunk structure
 */
typedef struct {
    uint8_t code[MAX_CHANK_CODES_COUNT];        /**< Array of instructions codes */
    uint32_t count;                             /**< Count of exists codes */
} Chunk;

/**
 * @brief Function for create chunk
 *
 * This function creates a new chunk in memory, initializes it with zeros, and returns it
 * 
 * @return Pointer to new chunk
 */
Chunk *create_chunk();

/**
 * @brief Function for add new operation code into chunk
 *
 * This function adds the passed operation code to the chunk and increments the count of exists codes in chunk
 *
 * @param chunk Pointer to the chunk
 * @param code Operation code
 */
void add_code(Chunk *chunk, OpCode code);

/**
 * @brief Function to free up the memory allocated for the chunk
 *
 * This function deletes an array of operations codes from memory and deletes the chunk itself
 *
 * @param chunk Pointer to the chunk
 */
void free_chunk(Chunk *chunk);