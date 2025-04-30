#include <stdio.h>
#include <stdlib.h>
#include "complex.h"


typedef struct {
    double real;
    double imag;
} Complex;

void complex_add(const void *a, const void *b, void *result) {
    const Complex *s1 = (const Complex*)a;
    const Complex *s2 = (const Complex*)b;
    Complex *res = (Complex*)result;
    
    res->real = s1->real +s2->real;
    res->imag = s1->imag + s2->imag;
}

void complex_swap(void *elem1, void *elem2) {
    Complex *complex1 = (Complex *)elem1;
    Complex *complex2 = (Complex *)elem2;

    Complex temp;
    temp.real = complex1->real;
    temp.imag = complex1->imag;

    complex1->real = complex2->real;
    complex1->imag = complex2->imag;

    complex2->real = temp.real;
    complex2->imag = temp.imag;
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
    const Complex *s = (Complex*)src;
    
    d->real = s->real;
    d->imag = s->imag;
}

void complex_input(void *data) {
    Complex *c = data;
    printf("Enter real part: ");
    scanf("%lf", &c->real);
    printf("Enter imaginary part: ");
    scanf("%lf", &c->imag);
}

void complex_print(const void *data) {
    const Complex *c = data;
    printf("(%.2f, %.2f) ", c->real, c->imag);
}

static const Complex zero = {0.0, 0.0};
static struct TypeInfo *complex_type = NULL;

const TypeInfo *get_complex_type_info() {
    if (!complex_type) {
        complex_type = malloc(sizeof(struct TypeInfo));
        complex_type->element_size = sizeof(Complex);
        complex_type->add = complex_add;
        complex_type->multiply = complex_multiply;
        complex_type->assign = complex_assign;
        complex_type->input = complex_input;
        complex_type->print = complex_print;
        complex_type->swap=complex_swap;
        complex_type->zero = &zero;
    }

    return complex_type;
}
