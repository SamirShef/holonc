/**
 * @file vm.c
 * @brief Implementation of @file vm.h
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../../include/vm/vm.h"
#include <stdlib.h>

/**
 * @brief Function for create chunk
 *
 * This function creates a new VM in memory, initializes it with zeros, and returns it
 * 
 * @return Pointer to new chunk
 */
VM *create_vm() {
    VM *vm = malloc(sizeof(VM));
    vm->chunks = NULL;
    vm->count = 0;
    return vm;
}

/**
 * @brief Function for add new operation code into chunk
 *
 * This function adds the passed chunk to the VM and increments the count of exists chunks in VM
 *
 * @param vm Pointer to the VM
 * @param chunk Pointer to the chunk
 */
void add_chunk(VM *vm, Chunk *chunk) {
    if (vm->chunks == NULL) {
        vm->chunks = malloc(sizeof(Chunk));
    }
    vm->chunks = realloc(vm->chunks, sizeof(Chunk) * (vm->count + 1));
    vm->chunks[vm->count++] = chunk;
}

/**
 * @brief Function to free up the memory allocated for the VM
 *
 * This function deletes an array of chunks from memory and deletes the VM itself
 *
 * @param vm Pointer to the VM
 */
void free_vm(VM *vm) {
    free(vm->chunks);
    free(vm);
}