/**
 * @file vm.h
 * @brief Header file for define VM
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "chunk.h"

/**
 * @brief Base VM structure
 */
typedef struct {
    Chunk *chunk;                     /**< Chunk */
    uint8_t ip;                     /**< Pointer to current instruction */
} VM;

/**
 * @brief Function for create chunk
 *
 * This function creates a new VM in memory, initializes it with zeros, and returns it
 * 
 * @return Pointer to new chunk
 */
VM *create_vm(Chunk *chunk);

/**
 * @brief Function to free up the memory allocated for the VM
 *
 * This function deletes an array of chunks from memory and deletes the VM itself
 *
 * @param vm Pointer to the VM
 */
void free_vm(VM *vm);