/**
 * @file main.c
 * @brief Compilator's entry point
 * 
 * Copyright (c) 2025 SamirShef
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../include/vm/vm.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {
    printf("Hello from holonc!\n");
    VM *vm = create_vm();
    Chunk *chunk = create_chunk();
    add_code(chunk, OP_RETURN);
    add_code(chunk, OP_RETURN);
    add_chunk(vm, chunk);
    free_vm(vm);
    return 0;
}