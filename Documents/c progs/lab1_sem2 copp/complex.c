#include "complex.h"

#include <stdlib.h>


void complex_add(const void *a, const void *b, void *result) {
    const Complex *s1 = (const Complex*)a;
    const Complex *s2 = (const Complex*)b;
    Complex *res = (Complex*)result;
    res->real = s1->real +s2->real;
    res->imag = s1->imag + s2->imag;
}

void complex_multiply(const void *a, const void *b, void *result) {
    const Complex *s1 = (const Complex*)a;
    const Complex *s2 = (const Complex*)b;
    Complex *res = (Complex*)result;
    res->real = s1->real * s2->real - s1->imag * s2->imag;
    res->imag = s1->real * s2->imag + s1->imag * s2->real;
}

void complex_assign(void *dest, const void *src) {
    Complex *d = (Complex*)dest;
    Complex *s = (Complex*)src;
    d->real = s->real;
    d->imag = s->imag;
}

void *complex_alloc() {
    return malloc(sizeof(Complex));
}

void complex_dealloc(void *data) {
    free(data);
}


static const Complex zero = {0.0, 0.0};
static const Complex one = {1.0, 0.0};


static struct TypeInfo *complex_type = NULL;

const TypeInfo *getComplexTypeInfo() {
    if (complex_type == NULL) {
        complex_type = malloc(sizeof(struct TypeInfo));
        if (complex_type == NULL) return NULL;

        complex_type->element_size = sizeof(Complex);
        complex_type->add = complex_add;
        complex_type->multiply = complex_multiply;
        complex_type->assign = complex_assign;
        complex_type->allocate = complex_alloc;
        complex_type->deallocate = complex_dealloc;
        complex_type->zero = &zero;
        complex_type->one = &one;
    }

    return complex_type;
}