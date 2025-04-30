#include <stdio.h>
#include <stdlib.h>
#include "integer.h"


typedef struct Integer {
    int value;
} Integer;

void integer_add(const void *a, const void *b, void *result) {
    const Integer *s1 = (const Integer*)a;
    const Integer *s2 = (const Integer*)b;
    Integer *res = (Integer*)result;
    res->value = s1->value + s2->value;  
}

void integer_swap(void *a, void *b) {
    int *dbl1 = (int *)a;
    int *dbl2 = (int *)b;
    int temp = *dbl1;
    *dbl1 = *dbl2;
    *dbl2 = temp;
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

void integer_input(void *data) {
    Integer *val = data;
    printf("Enter integer: ");
    scanf("%d", &val->value);
}

void integer_print(const void *data) {
    const Integer *val = data;
    printf("%d ", val->value);
}


static const Integer zero = {0};
static struct TypeInfo* int_type = NULL;

const TypeInfo *get_integer_type_info() {
    if (!int_type) {
        int_type = malloc(sizeof(struct TypeInfo)); 
        int_type->element_size = sizeof(Integer);
        int_type->add = integer_add;
        int_type->multiply = integer_multiply;
        int_type->assign = integer_assign;
        int_type->input = integer_input;
        int_type->print = integer_print;
        int_type->swap = integer_swap;
        int_type->zero = &zero;
    }

    return int_type;
}
