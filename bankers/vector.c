/**
 * Define vector and matrix operations
 * Penny Rowe
 * Apr 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * Clone (deep copy) a matrix
 * @param mat  A pointer to the matrix to be cloned
 * @param result  A pointer to the matrix to hold the clone
 * @param nrows  The number of rows
 * @param ncols  The number of columns
 */
void clonemat(int **mat, int **result, int nrows, int ncols)
{
    for (int row = 0; row < nrows; row++)
        for (int col = 0; col < ncols; col++)
            result[row][col] = mat[row][col];
    return;
}

/**
 * Clone (deep copy) a vector
 * @param vec  A pointer to the vector to be cloned
 * @param result  A pointer to the vector to hold the clone
 * @param ncols  The number of elements
 */
void clonevec(int *vec, int *result, int ncols)
{
    for (int col = 0; col < ncols; col++)
        result[col] = vec[col];
    return;
}

// Sum over rows of a matrix
void sumRows(int **mat, int nrows, int ncols, int *result)
{
    for (int col = 0; col < ncols; col++)
    {
        result[col] = 0;
        for (int row = 0; row < nrows; row++)
            result[col] += mat[row][col];
    }
    return;
}

/**
 * Subtract two matrices, placing the result in another matrix
 * @param mat1  A pointer to the matrix to subtract from
 * @param mat2  A pointer to the matrix to be subtracted
 * @param result  A pointer to the matrix to hold the result
 * @param nrows  The number of rows
 * @param ncols  The number of columns
 */
void subtractmats(int **mat1, int **mat2, int **result, int nrows, int ncols)
{
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            result[i][j] = mat1[i][j] - mat2[i][j];
    return;
}

/**
 * Determine if one vector is >= another
 * @param greater  A pointer to the vector to test (should be >= the other)
 * @param lesser  A pointer to the vector to compare against (should be < the other)
 * @param ncols  The number of elements in the vectors
 * @returns 1 if True, 0 if False
 */
int vec1GreaterOrEqualVec2(int *greater, int *lesser, int ncols)
{
    // since ncols is unknown, malloc result
    int *result = (int *)malloc(sizeof(int) * ncols);

    subtractvecs(greater, lesser, result, ncols);
    for (int col = 0; col < ncols; col++)
        if (result[col] < 0)
        {
            free(result);
            result = NULL;
            return 0;
        }

    // free result and remove dangling pointers
    free(result);
    result = NULL;

    return 1;
}

/**
 * Subtract two vectors and modify the result
 * @param vec1  A pointer to the vector that vector to subtract from
 * @param vec2  A pointer to the vector that will be subtracted
 * @param result  A pointer to the resulting vector
 * @param ncols  The number of elements in each vector
 */
void subtractvecs(int *vec1, int *vec2, int *result, int ncols)
{
    for (int i = 0; i < ncols; i++)
        result[i] = vec1[i] - vec2[i];
    return;
}

/**
 * Add one vector to another vector
 * @param vec1  A pointer to the vector that will hold the sum
 * @param vec2  A pointer to the vector that will be added to vec1
 * @param ncols  The number of columns in each vector
 */
void addVec2toVec1(int *vec1, int *vec2, int ncols)
{
    for (int i = 0; i < ncols; i++)
        vec1[i] += vec2[i];
    return;
}

/**
 * Subtract one vector from another vector
 * @param vec1  The vector that will hold the sum
 * @param vec2  The vector that will be added to vec1
 * @param ncols  The number of columns in each vector
 */
void subtractVec2fromVec1(int *vec1, int *vec2, int ncols)
{
    for (int i = 0; i < ncols; i++)
        vec1[i] -= vec2[i];
    return;
}

/**
 * Print the contents of a matrix
 * @param mat  The matrix to print
 * @param nrows  The number of nrows
 * @param ncols  The number of columns
 */
void printmat(int **mat, int nrows, int ncols)
{
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
    return;
}

/**
 * Print the contents of a vector
 * @param vec  The vector to print
 * @param ncols  The number of elements
 */
void printvec(int *vec, int ncols)
{
    for (int j = 0; j < ncols; j++)
        printf("%d ", vec[j]);
    printf("\n\n");
    return;
}
