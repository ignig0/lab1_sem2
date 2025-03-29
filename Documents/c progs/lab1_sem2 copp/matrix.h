#pragma once

#include "typeinfo.h"

typedef struct Matrix {
    size_t rows;
    size_t cols;
    const TypeInfo* type;
    void** data;
} Matrix;

Matrix* create_matrix(size_t rows, size_t cols, const TypeInfo *type);
void destroy_matrix(Matrix *mat);
Matrix* matrix_add(const Matrix *a, const Matrix *b);
Matrix* matrix_multiply(const Matrix *a, const Matrix *b);
Matrix* matrix_transpose(const Matrix *mat);
void print_matrix(const Matrix *mat);
