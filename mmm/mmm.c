/**
 * By Penny Rowe using starter code from dchiu
 */
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <math.h> // fmax
#include "mmm.h"

int **mat1, **mat2, **mat3, **mat4;
int matdim;

/**
 * Allocate and initialize the matrices on the heap. Populate
 * the input matrices with random integers from 0 to 99
 */
void mmm_init()
{
	// Intialize random number generator
	time_t t;
	srand((unsigned)time(&t));

	// malloc a size N array of pointers to ints
	mat1 = (int **)malloc(sizeof(int *) * matdim);
	mat2 = (int **)malloc(sizeof(int *) * matdim);
	mat3 = (int **)malloc(sizeof(int *) * matdim); // for mat1 x mat2, seq
	mat4 = (int **)malloc(sizeof(int *) * matdim); // for mat1 x mat2, par

	// iterate through each row and malloc a size N array of ints
	for (int i = 0; i < matdim; i++)
	{
		mat1[i] = (int *)malloc(sizeof(int) * matdim);
		mat2[i] = (int *)malloc(sizeof(int) * matdim);
		mat3[i] = (int *)malloc(sizeof(int) * matdim);
		mat4[i] = (int *)malloc(sizeof(int) * matdim);
	}

	// Populate the array with random numbers
	for (int i = 0; i < matdim; i++)
		for (int j = 0; j < matdim; j++)
		{
			int maxval = 100;
			mat1[i][j] = rand() % maxval;
			mat2[i][j] = rand() % maxval;
		}

	// Set matrices 3 and 4 to zero
	mmm_reset(mat3);
	mmm_reset(mat4);
	return;
}

/**
 * Reset a given matrix to zeroes
 * @param matrix pointer to a 2D array
 */
void mmm_reset(int **matrix)
{
	for (int i = 0; i < matdim; i++)
		for (int j = 0; j < matdim; j++)
			matrix[i][j] = 0;
	return;
}

/**
 * Free up memory allocated to all matrices
 */
void mmm_freeup()
{
	// free each row
	for (int i = 0; i < matdim; i++)
	{
		// Free ith row
		free(mat1[i]);
		free(mat2[i]);
		free(mat3[i]);
		free(mat4[i]);
		// remove dangling pointers
		mat1[i] = NULL;
		mat2[i] = NULL;
		mat3[i] = NULL;
		mat4[i] = NULL;
	}
	// free original arrays
	free(mat1);
	free(mat2);
	free(mat3);
	free(mat4);
	// remove dangling pointers
	mat1 = NULL;
	mat2 = NULL;
	mat3 = NULL;
	mat4 = NULL;
	return;
}

/**
 * Sequential MMM
 */
void mmm_seq()
{

	// Zero out mat3
	mmm_reset(mat3);

	// Loop over rows of mat1
	for (int i = 0; i < matdim; i++)
	{
		for (int j = 0; j < matdim; j++)
		{
			for (int k = 0; k < matdim; k++)
			{
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	mmm_print1(mat3);

	return;
}

/**
 * Parallel MMM
 */
void *mmm_par(void *args)
{

	// cast input as struct thread_args
	thread_args *params = (thread_args *)args;

	// Loop over rows of mat1
	for (int i = params->first; i < params->last; i++)
	{
		printf("On row %d\n", i);
		for (int j = 0; j < matdim; j++)
		{
			for (int k = 0; k < matdim; k++)
			{
				mat4[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return NULL;
}

/**
 * Verifies the correctness between the matrices generated by
 * the sequential run and the parallel run.
 *
 * @return the largest error between two corresponding elements
 * in the result matrices
 */
double mmm_verify()
{
	// Compare matrix 3 (sequential) to matrix 4 (parallel)
	double maxerr = 0;
	for (int i = 0; i < matdim; i++)
		for (int j = 0; j < matdim; j++)
			maxerr = fmax(maxerr, fabs(mat3[i][j] - mat4[i][j]));

	return maxerr;
}

/**
 * Print a matrix
 */
void mmm_print1(int **array)
{
	for (int i = 0; i < matdim; i++)
	{
		for (int j = 0; j < matdim; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}

/**
 * Print the matrices
 */
void mmm_print()
{
	printf("\nmatrix 1:\n");
	mmm_print1(mat1);

	printf("\nmatrix 2:\n");
	mmm_print1(mat2);

	printf("\nmatrix 3:\n");
	mmm_print1(mat3);

	printf("\nmatrix 4:\n");
	mmm_print1(mat4);

	return;
}
