#pragma once

#include <stdlib.h>

typedef struct TypeInfo TypeInfo;
typedef void (*binary_operation)(const void*, const void*, void*);
typedef size_t (*get_size)();   
typedef void (*unary_operation)(void*, const void*);
typedef void (*swapper)(void *element1, void *element2);
typedef void (*printer)(const void *element);
typedef void (*inputter)(void *element);

struct TypeInfo {
    size_t element_size;
    binary_operation add;
    binary_operation multiply;
    unary_operation assign;
    printer print;
    swapper swap;
    inputter input;
    const void* zero;
};
