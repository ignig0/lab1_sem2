#include "check_for_errors.h"

#include <string.h>
#include "matrix.h"
#include <ctype.h> 

ErrorInfo *get_success_result()
{
    ErrorInfo *error_st = malloc(sizeof(ErrorInfo));
    error_st->code = OK;
    error_st->message = "Successful execution";
    return error_st;
}




void check_matrix(const Matrix *mat, ErrorInfo *error_st) {
    if (mat == NULL) {
        error_st->code = MATRIX_IS_NULL;
        error_st->message = "Error: Matrix is NULL";
        return;
    }
    if (mat->type == NULL) {
        error_st->code = TYPE_IS_NULL;
        error_st->message = "Error: Type is NULL";
        return;
    }
    if (mat->data == NULL) {
        error_st->code = DATA_IS_NULL;
        error_st->message = "Error: Data is NULL";
        return;
    }
    if (mat->rows == 0 || mat->cols == 0) {
        error_st->code = INCORRECT_FORMAT_OF_MATRIX;
        error_st->message = "Error: Incorrect format of matrix";
        return;
    }
    error_st->code = OK;
    error_st->message = "Successful execution";
}

void check_matrix_addition(const Matrix* mat1, const Matrix* mat2, ErrorInfo *error_st) {
    check_matrix(mat1, error_st);
    check_matrix(mat2, error_st);
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols){
        error_st->code =INCOMPATIBLE_SIZES;
        error_st->message = "Error: Incompatible sizes";
    } 
    else if (mat1->type != mat2->type)
    {
        error_st->code =TYPES_ARE_NOT_MATCHING;
        error_st->message = "Error: Types are not matching";
    }
    else
    {
        error_st->code = OK;
        error_st->message = "Successful execution";
    }
}

void check_matrix_multiplication(const Matrix* mat1, const Matrix* mat2, ErrorInfo *error_st) {
    check_matrix(mat1, error_st);
    check_matrix(mat2, error_st);
    if (mat1->cols != mat2->rows){
        error_st->code =INCOMPATIBLE_SIZES;
        error_st->message = "Error: Incompatible sizes";
    }
    else if (mat1->type != mat2->type){
        error_st->code =TYPES_ARE_NOT_MATCHING;
        error_st->message = "Error: Types are not matching";
    }
    else
    {
        error_st->code = OK;
        error_st->message = "Successful execution";
    }
}

bool is_matrix_data_invalid(const Matrix *matrix) {
    return matrix->data == NULL;
}

bool is_type_null(const TypeInfo *type) {
    return type == NULL;
}

bool is_matrix_null(const Matrix *matrix) {
    return matrix == NULL;
}

bool is_malloc_correct(void *ptr) {
    return ptr != NULL;
}





