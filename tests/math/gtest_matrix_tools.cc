/*
 * Test cases for the matrix tools.
 * Written by Simon Fuhrmann.
 */

#include <gtest/gtest.h>

#include "math/matrix.h"
#include "math/matrix_tools.h"

TEST(MatrixToolsTest, DiagonalMatrix)
{
    using namespace math;
    /* Matrix init diagonal tests. */
    Vec3f diag_vector(1, 2, 3);
    Matrix3f diag_mat = math::matrix_from_diagonal(diag_vector);
    EXPECT_EQ(diag_mat[0], 1);
    EXPECT_EQ(diag_mat[1], 0);
    EXPECT_EQ(diag_mat[2], 0);
    EXPECT_EQ(diag_mat[3], 0);
    EXPECT_EQ(diag_mat[4], 2);
    EXPECT_EQ(diag_mat[5], 0);
    EXPECT_EQ(diag_mat[6], 0);
    EXPECT_EQ(diag_mat[7], 0);
    EXPECT_EQ(diag_mat[8], 3);

    Vec3f diag_vector2(4, 5, 6);
    math::matrix_set_diagonal(diag_mat, *diag_vector2);
    EXPECT_EQ(diag_mat[0], 4);
    EXPECT_EQ(diag_mat[1], 0);
    EXPECT_EQ(diag_mat[2], 0);
    EXPECT_EQ(diag_mat[3], 0);
    EXPECT_EQ(diag_mat[4], 5);
    EXPECT_EQ(diag_mat[5], 0);
    EXPECT_EQ(diag_mat[6], 0);
    EXPECT_EQ(diag_mat[7], 0);
    EXPECT_EQ(diag_mat[8], 6);

    Vec3f diag_test = math::matrix_get_diagonal(diag_mat);
    EXPECT_EQ(diag_test, diag_vector2);
}

TEST(MatrixToolsTest, MatrixIsIdentity)
{
    math::Matrix3f mat, mat2;
    math::matrix_set_identity(&mat);
    EXPECT_TRUE(math::matrix_is_identity(mat));

    mat2 = mat;
    mat2[0] = 0.0f;
    EXPECT_FALSE(math::matrix_is_identity(mat2));

    mat2 = mat;
    mat2[1] = 1.0f;
    EXPECT_FALSE(math::matrix_is_identity(mat2));

    mat2 = mat;
    mat2[3] = 1.0f;
    EXPECT_FALSE(math::matrix_is_identity(mat2));
}

TEST(MatrixToolsTest, MatrixTranspose)
{
    int mat_a[6];
    mat_a[0] = 1;  mat_a[1] = 3;  mat_a[2] = 5;
    mat_a[3] = 2;  mat_a[4] = 4;  mat_a[5] = 6;

    math::matrix_transpose(mat_a, 2, 3);

    int groundtruth_mat_a_t[6];
    groundtruth_mat_a_t[0] = 1; groundtruth_mat_a_t[1] = 2;
    groundtruth_mat_a_t[2] = 3; groundtruth_mat_a_t[3] = 4;
    groundtruth_mat_a_t[4] = 5; groundtruth_mat_a_t[5] = 6;

    for (int i = 0; i < 6; ++i)
        EXPECT_EQ(groundtruth_mat_a_t[i], mat_a[i]);
}

TEST(MatrixToolsTest, MatrixMultiply)
{
    math::Matrix<int, 3, 2> mat_a;
    mat_a[0] = 0;
    mat_a[1] = 1;
    mat_a[2] = 2;
    mat_a[3] = 3;
    mat_a[4] = 4;
    mat_a[5] = 5;

    math::Matrix<int, 2, 4> mat_b;
    mat_b[0] = 4;
    mat_b[1] = 6;
    mat_b[2] = 8;
    mat_b[3] = 2;
    mat_b[4] = 5;
    mat_b[5] = 7;
    mat_b[6] = 9;
    mat_b[7] = 3;

    math::Matrix<int, 3, 4> mat_ret;
    mat_ret[0] = 0 * 4 + 1 * 5;
    mat_ret[1] = 0 * 6 + 1 * 7;
    mat_ret[2] = 0 * 8 + 1 * 9;
    mat_ret[3] = 0 * 2 + 1 * 3;
    mat_ret[4] = 2 * 4 + 3 * 5;
    mat_ret[5] = 2 * 6 + 3 * 7;
    mat_ret[6] = 2 * 8 + 3 * 9;
    mat_ret[7] = 2 * 2 + 3 * 3;
    mat_ret[8] = 4 * 4 + 5 * 5;
    mat_ret[9] = 4 * 6 + 5 * 7;
    mat_ret[10] = 4 * 8 + 5 * 9;
    mat_ret[11] = 4 * 2 + 5 * 3;

    math::Matrix<int, 3, 4> ret;
    math::matrix_multiply(mat_a.begin(), 3, 2, mat_b.begin(), 4, ret.begin());
    for (int i = 0; i < 12; ++i)
        EXPECT_EQ(mat_ret[i], ret[i]);
}
