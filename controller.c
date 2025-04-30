#include "controller.h"
#include "typeinfo.h"
#include "complex.h"
#include "integer.h"
#include <ctype.h> 
#include <stdio.h>

void do_operations(){
    ErrorInfo *error_st = get_success_result();
    int should_repeat = 1;
 	while (should_repeat) {
	    print_menu();
		int choice= correct_input_choice(1,4,error_st);
		switch (choice) {
		case 1: { // Matrix addition
			Matrix mat1, mat2, res;
			printf("Addition A + B:\n"); 
			initialize_matrix(&mat1,error_st);
			initialize_matrix(&mat2,error_st);
			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			}
			
			printf("First matrix:\n");
			print_matrix(&mat1);
			printf("Second matrix:\n");
			print_matrix(&mat2);
			
			create_matrix(mat1.rows, mat1.cols, (TypeInfo *)mat1.type, &res);
			matrix_add(&mat1, &mat2, &res,error_st);
			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			}
			printf("Result:\n");
			print_matrix(&res);
				
			destroy_matrix(&mat1);
			destroy_matrix(&mat2);
			destroy_matrix(&res);
			break;
		}
		case 2: { // Matrix multiplication
			Matrix mat1, mat2, res;
			printf("Multiplication A x B:\n");

			initialize_matrix(&mat1,error_st);
			initialize_matrix(&mat2,error_st);

			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			}
			
			printf("First matrix:\n");
			print_matrix(&mat1);
			printf("Second matrix:\n");
			print_matrix(&mat2);
			
			create_matrix(mat1.rows, mat2.cols, (TypeInfo *)mat1.type, &res);
			matrix_multiply(&mat1, &mat2, &res, error_st);

			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			} 
			printf("Result:\n");
			print_matrix(&res); 
			
			destroy_matrix(&mat1);
			destroy_matrix(&mat2);
			destroy_matrix(&res);
			break;
		}
		case 3: { // Matrix transposition
			Matrix mat;
			printf("Matrix Transposition:\n");

			initialize_matrix(&mat, error_st);

			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			}

			printf("Matrix before transposition:\n");
			print_matrix(&mat);
			matrix_transpose(&mat, error_st);
			check_for_OK(error_st);
			if (error_st->code != OK) {
				break;
			}
			printf("Matrix after transposition:\n");
			print_matrix(&mat);
											
			destroy_matrix(&mat);
			break;
		}
		case 4://exit
			should_repeat = 0;
			break;    
		default:
			printf("Unexpected error: Invalid choice.\n");
			break;
		}


	}
}
int correct_input_choice(int min, int max, ErrorInfo *error_st){
	int choice;
	printf("Choose an option (%d-%d):\n", min, max);
	printf("Enter your choice: ");
	do{
    choice = input_choice(1,4,error_st);
	check_for_OK(error_st);
	}while(error_st->code !=OK);
	
	return choice;
}

void initialize_matrix(Matrix *matrix, ErrorInfo *error_st)
{
	input_matrix_dimensions(matrix,error_st);
	determine_matrix_element_type(matrix,error_st);
	create_matrix(matrix->rows, matrix->cols, (TypeInfo *)matrix->type, matrix);
	input_matrix_elements(matrix);
	
}


unsigned int input_matrix_dimension(ErrorInfo *error_st) {
	char input[256];
    if (scanf(" %255[^\n]", input) != 1) {
        error_st->code = INCORRECT_INPUT;
        error_st->message = "Error: Failed to read input";
        return 0;
    }
	error_st->code= OK;
    error_st->message = "Successful execution";


	char* ptr = input;
	while (*ptr)
	{
        
        if (!(isdigit(*ptr)))
        {
            error_st->code = INCORRECT_INPUT;
            error_st->message = "Error: Size must be a natural number";
			break;
        }
        ptr++;
		
		
	}
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	if (error_st->code != OK) {
		return 0; 
	}

	return atoi(input);
}

int input_choice(int min, int max, ErrorInfo *error_st) {
    char input[256];
    if (scanf(" %255[^\n]", input) != 1) {
        error_st->code = INCORRECT_READ;
        error_st->message = "Error: Failed to read input";
        return 0;
    }
	error_st->code= OK;
    error_st->message = "Successful execution";


	char* ptr = input;
	while (*ptr)
	{
        
        if (!(isdigit(*ptr)))
        {
            error_st->code = INCORRECT_TYPE;
            error_st->message = "Error: Must be a natural number";
			break;
        }
        ptr++;
		
		
	}
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	if (error_st->code != OK) {
		return 0; 
	}
	int j;
	j=atoi(input);
	if (j >= min && j <= max) {
		return j;
	}
	else{
		error_st->code = INCORRECT_INPUT;
        error_st->message = "Error: a non-existent option";
		return 0; 
	}
	
}
void determine_matrix_element_type(Matrix *matrix, ErrorInfo *error_st) {
    int type_code;
    printf("Enter type:\n");
    printf("1) Complex \n");
    printf("2) Integer \n");
	
    type_code = correct_input_choice(1, 2,error_st);
	
    const TypeInfo *type_of_matrix;
    switch (type_code) {
	    case 1:
	        type_of_matrix = get_complex_type_info();
	        break;
	    case 2:
	        type_of_matrix = get_integer_type_info();
	        break;
	    default:
	        type_of_matrix = NULL;
	        break;
    }
	
    matrix->type = type_of_matrix;
	
    matrix->data = malloc(matrix->cols * matrix->rows * matrix->type->element_size);
	
	
}
void check_for_OK(ErrorInfo *error_st)
{
	if (error_st->code != OK)
	{
		printf(error_st->message);
		printf("\n");
	}
}


void input_matrix_dimensions(Matrix *matrix, ErrorInfo *error_st) {
    int rows, cols;
    printf("\n Entering the matrix size:\n");
    printf("-----------------------\n");
    printf("Enter matrix height: ");
	do{
    rows = input_matrix_dimension(error_st);
	check_for_OK(error_st);
	}while(error_st->code !=OK);
    printf("Enter matrix length: ");
	do{
    cols = input_matrix_dimension(error_st);
	check_for_OK(error_st);
	}while(error_st->code !=OK);
    matrix->rows = rows;
    matrix->cols = cols;
} 

void print_menu() {
    printf("----- Matrix Operations: -----\n");
    printf("1) Add matrices\n");
    printf("2) Multiply matrices\n");
    printf("3) Transpose matrix\n");
    printf("4) Exit\n");
    printf("---------------------------\n");
}