/**
 * Define vector and matrix operations
 * Penny Rowe
 * Apr 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * clone (deep copy) matrices
 */
void clonemat(int **mat, int **result, int nrows, int ncols)
{
    for (int row = 0; row < nrows; row++)
        for (int col = 0; col < ncols; col++)
            result[row][col] = mat[row][col];
    return;
}

/**
 * clone (deep copy) vectors
 */
void clonevec(int *vec, int *result, int ncols)
{
    for (int col = 0; col < ncols; col++)
        result[col] = vec[col];
    return;
}

// TODO - function to compare two vectors
int compare(int *vec1, int *vec2)
{
    // ???
    return 1;
}

// TODO - function to sum over rows of a matrix
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

// TODO - function to add two vectors/matrices
void addmats(int **mat1, int **mat2)
{
    return;
}

// TODO - function to subtract two matrices
void subtractmats(int **mat1, int **mat2, int **result, int ncols, int nrows)
{
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            result[i][j] = mat1[i][j] - mat2[i][j];
    return;
}

/**
 *
 */
int vec1GreaterOrEqualVec2(int *workVec, int *threadNeedVec, int NRES)
{
    int result[NRES];
    subtractvecs(workVec, threadNeedVec, result, NRES);
    for (int col = 0; col < NRES; col++)
        if (result[col] < 0)
            return 0;
    return 1;
}

/**
 * Subtract two vectors
 */
void subtractvecs(int *vec1, int *vec2, int *result, int ncols)
{
    for (int i = 0; i < ncols; i++)
        result[i] = vec1[i] - vec2[i];
    return;
}

/**
 * Add two vectors
 */
void addVec2toVec1(int *vec1, int *vec2, int ncols)
{
    for (int i = 0; i < ncols; i++)
        vec1[i] += vec2[i];
    return;
}

/**
 * print the contents of a matrix
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
 * print the contents of a vector
 */
void printvec(int *vec, int ncols)
{
    for (int j = 0; j < ncols; j++)
        printf("%d ", vec[j]);
    printf("\n\n");
    return;
}
