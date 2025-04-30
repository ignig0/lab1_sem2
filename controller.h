#pragma once

#include "matrix.h"
#include "check_for_errors.h"

unsigned int input_matrix_dimension();

int input_choice(int min, int max, ErrorInfo *error_st);
int correct_input_choice(int min, int max, ErrorInfo *error_st);
void determine_matrix_element_type(Matrix *matrix, ErrorInfo *error_st);
void initialize_matrix(Matrix *matrix, ErrorInfo *error_st);

void input_matrix_dimensions(Matrix *matrix, ErrorInfo *error_st);
void print_menu();
void check_for_OK(ErrorInfo *error_st);
void do_operations();

