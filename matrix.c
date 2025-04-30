#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "complex.h"
#include "integer.h"

void  create_matrix(size_t rows, size_t cols, TypeInfo *type, Matrix *mat) {
    mat->rows = rows;
    mat->cols = cols;
    mat->type = type;
    mat->data = malloc(mat->rows * mat->cols * type->element_size); 
}

void  destroy_matrix(Matrix *mat) {
    if (is_matrix_null(mat)) return;
    
    free(mat->data);
    mat->data = NULL;
    mat->rows = 0;
    mat->cols = 0;
    mat->type = NULL;
}

void  matrix_add(const Matrix *mat1, const Matrix *mat2, Matrix *res, ErrorInfo *error_st) {
    check_matrix_addition(mat1, mat2, error_st);
    size_t size_of_element = mat1->type->element_size;
    unsigned int number_of_elements = mat1->rows * mat1->cols; 
    char *ptr1 = (char *)mat1->data;
    char *ptr2 = (char *)mat2->data;
    char *ptrResult = (char *)res->data;
    for (size_t i = 0; i < number_of_elements; i++) {
        res->type->add(ptr1, ptr2, ptrResult);
        ptr1 += size_of_element;
        ptr2 += size_of_element;
        ptrResult += size_of_element;
    }
}

void matrix_multiply(const Matrix *mat1, const Matrix *mat2, Matrix *result, ErrorInfo *error_st) {
    check_matrix_multiplication(mat1, mat2, error_st);
    const void *elemA = (char *)mat1->data;
    const void *elemB = (char *)mat2->data;
    size_t elementSize = mat1->type->element_size;
    void *temp = malloc(mat1->type->element_size);
    void *accumulator = malloc(elementSize);
    for (unsigned int i = 0; i < mat1->rows; i++) {
        for (unsigned int j = 0; j < mat2->cols; j++) {
            mat1->type->assign(accumulator, mat1->type->zero);
            for (unsigned int k = 0; k < mat1->cols; k++) {
                elemA = get_pos_el(i+1,k+1,mat1);
                elemB = get_pos_el(k+1,j+1,mat2);
                void *dst = get_pos_el(i+1,j+1,result);
               
                mat1->type->multiply(elemA, elemB, temp);
                mat1->type->add(accumulator, temp, accumulator);   
            }
            void *dst = (char *)result->data + (i * result->cols + j) * elementSize;
            mat1->type->assign(dst, accumulator);   
        }
    }
    free(temp);
    free(accumulator);   
   
}

void* get_pos_el(const size_t row, const size_t col, const Matrix *mat){   
    return (char *)mat->data + ((row - 1) * mat->cols + (col - 1)) * mat->type->element_size;
}

void  matrix_transpose(Matrix *mat, ErrorInfo *error_st) {
    check_matrix(mat, error_st);
    unsigned int height = mat->rows;
    unsigned int length = mat->cols;
    size_t elementSize = mat->type->element_size; 
    mat->rows = length;
    mat->cols = height;
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = i + 1; j < mat->cols; j++) {
            void *elem1 = (char *)mat->data + (i * height + j) * elementSize;
            void *elem2 = (char *)mat->data + (j * length + i) * elementSize;      
            mat->type->swap(elem1, elem2);
        }
    }
}

void input_matrix_elements(Matrix *mat) {
    for (size_t i = 0; i < mat->rows * mat->cols; i++) {
        mat->type->input((char*)mat->data + i * mat->type->element_size);
    }
}

void write_matrix_element(const Matrix *mat, const size_t row, const size_t col) {
    char *ptr = get_pos_el(row, col, mat);
    mat->type->print(ptr);
}

void  print_matrix(const Matrix *mat) {
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            write_matrix_element(mat, i + 1, j + 1);
        }
        printf("\n");
    }
}
