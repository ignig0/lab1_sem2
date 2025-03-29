#include <stdio.h>
#include "matrix.h"
#include "integer.h"
#include "complex.h"

int main() {
    
    const TypeInfo *int_type = getIntegerTypeInfo(); //матрица1
    Matrix *mat_int = create_matrix(10, 10, int_type);
    *(int*)mat_int->data[0] = 1;
    *(int*)mat_int->data[3] = 1;
    printf("Integer Matrix:\n");
    print_matrix(mat_int);
    printf("\n");

    const TypeInfo *complex_type = getComplexTypeInfo(); //матрица2
    Matrix *mat_complex = create_matrix(10, 10, complex_type);
    Complex* c = (Complex*)mat_complex->data[0];
    c->real = 1.0;
    c->imag = 2.0;

    printf("Complex Matrix:\n");
    print_matrix(mat_complex);
    printf("\n");

    Matrix *sum = matrix_add(mat_int, mat_int); //суммирование
    printf("Sum:\n");
    print_matrix(sum);
    destroy_matrix(sum);

    Matrix *product = matrix_multiply(mat_int, mat_int); //умножение
    printf("Product:\n");
    print_matrix(product);
    destroy_matrix(product);

    Matrix *transposed = matrix_transpose(mat_int); //транспонирование
    printf("Transpose:\n");
    print_matrix(transposed);
    

    destroy_matrix(mat_int);
    destroy_matrix(mat_complex);
    destroy_matrix(transposed);

    return 0;
}