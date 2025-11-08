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

VM *create_vm(Chunk *chunk) {
    VM *vm = malloc(sizeof(VM));
    vm->chunk = chunk;
    vm->ip = 0;
    return vm;
}

void free_vm(VM *vm) {
    free(vm);
}