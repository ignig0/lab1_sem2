#pragma once

#include "typeinfo.h"
#include "check_for_errors.h"

typedef struct Matrix { 
    size_t rows;
    size_t cols;
    const TypeInfo* type;
    void* data;
} Matrix;

void create_matrix(size_t rows, size_t cols, TypeInfo *type, Matrix *mat);
void destroy_matrix(Matrix *mat);

void matrix_add(const Matrix* mat1, const Matrix* mat2, Matrix* res, ErrorInfo *error_st);
void matrix_multiply(const Matrix* mat1, const Matrix* mat2, Matrix* result, ErrorInfo *error_st);
void matrix_transpose(Matrix* mat, ErrorInfo *error_st);

void input_matrix_elements(Matrix* mat);
void print_matrix(const Matrix* mat);

void write_matrix_element(const Matrix* mat, size_t row, size_t col);
void* get_pos_el(size_t row, size_t col, const Matrix* mat);