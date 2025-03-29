#include "integer.h"

#include <stdlib.h>



void integer_add(const void *a, const void *b, void *result) {
    const Integer *s1 = (const Integer*)a;
    const Integer *s2 = (const Integer*)b;
    
    Integer *res = (Integer*)result;
    res->value = s1->value + s2->value;
    
}

void integer_multiply(const void *a, const void *b, void *result) {
    const Integer *s1 = (const Integer*)a;
    const Integer *s2 = (const Integer*)b;
    Integer *res = (Integer*)result;
    res->value = s1->value * s2->value;
}

void integer_assign(void *dest, const void *src) {
    Integer *d = (Integer*)dest;
    const Integer *s = (const Integer*)src;
    d->value = s->value;
}

void *integer_alloc() {
    return malloc(sizeof(Integer));
}

void integer_dealloc(void* data) {
    free(data);
}

static const int zero = 0;
static const int one = 1;
static struct TypeInfo* int_type = NULL;

const TypeInfo *getIntegerTypeInfo() {
    if (int_type == NULL) {
        int_type = malloc(sizeof(struct TypeInfo));
        if (int_type == NULL) return NULL; 

        
        int_type->element_size = sizeof(Integer);
        int_type->add = integer_add;
        int_type->multiply = integer_multiply;
        int_type->assign = integer_assign;
        int_type->allocate = integer_alloc;
        int_type->deallocate = integer_dealloc;
        int_type->zero = &zero;
        int_type->one = &one;
    }

    return int_type;
}
