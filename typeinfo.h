#pragma once

#include <stdlib.h>

typedef struct TypeInfo TypeInfo;

typedef void (*BinaryOperation)(const void*, const void*, void*);

typedef void (*UnaryOperation)(void*, const void*);
typedef void* (*Allocator)();
typedef void (*Deallocator)(void*);

struct TypeInfo {
    size_t element_size;
    BinaryOperation add;
    BinaryOperation multiply;
    UnaryOperation assign;
    Allocator allocate;
    Deallocator deallocate;
    const void* zero;
    const void* one;
};
