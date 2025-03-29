#include <stdio.h>

#include "integer.h"

#include "matrix.h"
#include "complex.h"

Matrix *create_matrix(size_t rows, size_t cols, const TypeInfo *type) {
    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->type = type;
    mat->data = (void**)calloc(rows * cols, sizeof(void*));
    for (size_t i = 0; i < rows * cols; i++) {
        mat->data[i] = type->allocate();
        type->assign(mat->data[i], (void*)type->zero);
    }

    return mat;
}

void destroy_matrix(Matrix *mat) {
    if (!mat) return;
    for (size_t i = 0; i < mat->rows * mat->cols; i++) {
        mat->type->deallocate(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

Matrix* matrix_add(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols || a->type != b->type) return NULL;

    Matrix* res = create_matrix(a->rows, a->cols, a->type);

    for (size_t i = 0; i < a->rows * a->cols; i++) {
        a->type->add(a->data[i], b->data[i], res->data[i]);
    }

    return res;
}

Matrix* matrix_multiply(const Matrix *a, const Matrix *b) {
    if (a->cols != b->rows || a->type != b->type) return NULL;

    Matrix* res = create_matrix(a->rows, b->cols, a->type);
    
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            void* sum = a->type->allocate();
            a->type->assign(sum, (void*)a->type->zero);

            for (size_t k = 0; k < a->cols; k++) {
                void *temp = a->type->allocate();
                a->type->multiply(a->data[i * a->cols + k],b->data[k * b->cols + j],temp);
                a->type->add(sum, temp, sum);
                a->type->deallocate(temp);
            }

            a->type->assign(res->data[i * res->cols + j], sum);
            a->type->deallocate(sum);
        }
    }

    return res;
}

Matrix *matrix_transpose(const Matrix *mat) {
    Matrix *res = create_matrix(mat->cols, mat->rows, mat->type);

    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            mat->type->assign(
                res->data[j * res->cols + i],
                mat->data[i * mat->cols + j]
            );
        }
    }

    return res;
}

void print_matrix(const Matrix* mat) {
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            void *elem = mat->data[i * mat->cols + j];
            if (mat->type == getIntegerTypeInfo()) {
                printf("%d ", *(Integer*)elem);
            } else if (mat->type == getComplexTypeInfo()) {
                Complex* c = (Complex*)elem;
                printf("(%f, %f) ", c->real, c->imag);
            }
        }
        printf("\n");
    }
}