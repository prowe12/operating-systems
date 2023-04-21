/**
 * Define vector and matrix operations
 * Penny Rowe
 * Apr 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - function to clone (deep copy) vectors/matrices
int **clonemat(int **mat)
{
    return mat;
}

// TODO - function to compare two vectors
void compare(int **mat1, int **mat2)
{
    return;
}

// TODO - function to add two vectors/matrices
int **addmats(int **mat1, int **mat2)
{
    int **mat3 = clonemat(mat1);
    return mat3;
}

// TODO - function to subtract two vectors/matrices
int **subtractmats(int **mat1, int **mat2)
{
    int **mat3 = clonemat(mat1);
    return mat3;
}

// TODO - function to  print the contents of vectors/matrices
void printmat(int **mat)
{
    printf("Print the matrix\n");
    return;
}
