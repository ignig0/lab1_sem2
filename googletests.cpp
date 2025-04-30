#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C" {
#include "check_for_errors.h"
#include "complex.h"
#include "integer.h"
#include "controller.h"
}
#endif

TEST(CheckMatrixTest, NullMatrix) {
    ErrorInfo error_st;
    check_matrix(NULL, &error_st);
    EXPECT_EQ(error_st.code, MATRIX_IS_NULL);
    EXPECT_STREQ(error_st.message, "Error: Matrix is NULL");
}

TEST(CheckMatrixTest, NullType) {
    Matrix mat = {2, 2, NULL, malloc(4 * sizeof(int))};
    ErrorInfo error_st;
    check_matrix(&mat, &error_st);
    EXPECT_EQ(error_st.code, TYPE_IS_NULL);
    EXPECT_STREQ(error_st.message, "Error: Type is NULL");
    free(mat.data);
}

TEST(CheckMatrixTest, NullData) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat = {2, 2, type, NULL};
    ErrorInfo error_st;
    check_matrix(&mat, &error_st);
    EXPECT_EQ(error_st.code, DATA_IS_NULL);
    EXPECT_STREQ(error_st.message, "Error: Data is NULL");
}

TEST(CheckMatrixTest, ZeroRows) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat = {0, 2, type, malloc(0)};
    ErrorInfo error_st;
    check_matrix(&mat, &error_st);
    EXPECT_EQ(error_st.code, INCORRECT_FORMAT_OF_MATRIX);
    EXPECT_STREQ(error_st.message, "Error: Incorrect format of matrix");
    free(mat.data);
}

TEST(CheckMatrixTest, ZeroCols) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat = {2, 0, type, malloc(0)};
    ErrorInfo error_st;
    check_matrix(&mat, &error_st);
    EXPECT_EQ(error_st.code, INCORRECT_FORMAT_OF_MATRIX);
    EXPECT_STREQ(error_st.message, "Error: Incorrect format of matrix");
    free(mat.data);
}

TEST(CheckMatrixTest, ValidMatrix) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat = {2, 2, type, malloc(4 * type->element_size)};
    ErrorInfo error_st;
    check_matrix(&mat, &error_st);
    EXPECT_EQ(error_st.code, OK);
    EXPECT_STREQ(error_st.message, "Successful execution");
    free(mat.data);
}


TEST(CheckMatrixAdditionTest, IncompatibleSizes) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat1 = {2, 3, type, malloc(6 * type->element_size)};
    Matrix mat2 = {3, 2, type, malloc(6 * type->element_size)};
    ErrorInfo error_st;
    check_matrix_addition(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, INCOMPATIBLE_SIZES);
    EXPECT_STREQ(error_st.message, "Error: Incompatible sizes");
    free(mat1.data);
    free(mat2.data);
}

TEST(CheckMatrixAdditionTest, DifferentTypes) {
    const TypeInfo* type1 = get_integer_type_info();
    const TypeInfo* type2 = get_complex_type_info();
    Matrix mat1 = {2, 2, type1, malloc(4 * type1->element_size)};
    Matrix mat2 = {2, 2, type2, malloc(4 * type2->element_size)};
    ErrorInfo error_st;
    check_matrix_addition(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, TYPES_ARE_NOT_MATCHING);
    EXPECT_STREQ(error_st.message, "Error: Types are not matching");
    free(mat1.data);
    free(mat2.data);
}

TEST(CheckMatrixAdditionTest, ValidIntegerAddition) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat1 = {2, 2, type, malloc(4 * type->element_size)};
    Matrix mat2 = {2, 2, type, malloc(4 * type->element_size)};
    ErrorInfo error_st;
    check_matrix_addition(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, OK);
    EXPECT_STREQ(error_st.message, "Successful execution");
    free(mat1.data);
    free(mat2.data);
}


TEST(CheckMatrixMultiplicationTest, IncompatibleSizes) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat1 = {2, 3, type, malloc(6 * type->element_size)};
    Matrix mat2 = {2, 3, type, malloc(6 * type->element_size)};
    ErrorInfo error_st;
    check_matrix_multiplication(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, INCOMPATIBLE_SIZES);
    EXPECT_STREQ(error_st.message, "Error: Incompatible sizes");
    free(mat1.data);
    free(mat2.data);
}

TEST(CheckMatrixMultiplicationTest, DifferentTypes) {
    const TypeInfo* type1 = get_integer_type_info();
    const TypeInfo* type2 = get_complex_type_info();
    Matrix mat1 = {2, 3, type1, malloc(6 * type1->element_size)};
    Matrix mat2 = {3, 2, type2, malloc(6 * type2->element_size)};
    ErrorInfo error_st;
    check_matrix_multiplication(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, TYPES_ARE_NOT_MATCHING);
    EXPECT_STREQ(error_st.message, "Error: Types are not matching");
    free(mat1.data);
    free(mat2.data);
}

TEST(CheckMatrixMultiplicationTest, ValidMultiplication) {
    const TypeInfo* type = get_integer_type_info();
    Matrix mat1 = {2, 3, type, malloc(6 * type->element_size)};
    Matrix mat2 = {3, 2, type, malloc(6 * type->element_size)};
    ErrorInfo error_st;
    check_matrix_multiplication(&mat1, &mat2, &error_st);
    EXPECT_EQ(error_st.code, OK);
    EXPECT_STREQ(error_st.message, "Successful execution");
    free(mat1.data);
    free(mat2.data);
}


TEST(HelperFunctionsTest, IsMatrixNull) {
    EXPECT_TRUE(is_matrix_null(NULL));
    Matrix mat = {0};
    EXPECT_FALSE(is_matrix_null(&mat));
}

TEST(HelperFunctionsTest, IsTypeNull) {
    EXPECT_TRUE(is_type_null(NULL));
    const TypeInfo* type = get_integer_type_info();
    EXPECT_FALSE(is_type_null(type));
}

TEST(HelperFunctionsTest, IsMatrixDataInvalid) {
    Matrix mat = {0};
    mat.data = NULL;
    EXPECT_TRUE(is_matrix_data_invalid(&mat));
    int data[4];
    mat.data = data;
    EXPECT_FALSE(is_matrix_data_invalid(&mat));
}

TEST(HelperFunctionsTest, IsMallocCorrect) {
    void* ptr = malloc(10);
    EXPECT_TRUE(is_malloc_correct(ptr));
    free(ptr);
    EXPECT_FALSE(is_malloc_correct(NULL));
}

TEST(HelperFunctionsTest, GetSuccessResult) {
    ErrorInfo* result = get_success_result();
    EXPECT_EQ(result->code, OK);
    EXPECT_STREQ(result->message, "Successful execution");
    free(result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}