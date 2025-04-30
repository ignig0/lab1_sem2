#pragma once
#include <stdbool.h>


typedef struct Matrix Matrix;
typedef struct TypeInfo TypeInfo;
typedef enum ErrorCode  {
    OK,
    TYPES_ARE_NOT_MATCHING,
    DATA_IS_NULL,
    INCORRECT_FORMAT_OF_MATRIX,
    INCORRECT_INPUT,
    MATRIX_IS_NULL,
    TYPE_IS_NULL,
    INCORRECT_TYPE,
    INCOMPATIBLE_SIZES,
    INCORRECT_READ,
} ErrorCode ;


typedef struct ErrorInfo{
    ErrorCode  code;
    char *message;
}ErrorInfo;

ErrorInfo *get_success_result();
ErrorCode  check_memory_allocation(const void *ptr);

void check_matrix(const Matrix* mat, ErrorInfo *error_st);
void check_matrix_addition(const Matrix* mat1, const Matrix* mat2, ErrorInfo *error_st);
void check_matrix_multiplication(const Matrix* mat1, const Matrix* mat2, ErrorInfo *error_st);

bool types_are_matching(const Matrix *matrix1, const Matrix *matrix2);

bool is_matrix_data_invalid(const Matrix *matrix);

bool is_type_null(const TypeInfo *type);

bool is_matrix_null(const Matrix *matrix);


bool is_malloc_correct(void *ptr);
