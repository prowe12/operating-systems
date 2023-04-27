/**
 * By Penny Rowe
 * using starter code from David Chiu and Adam Smith
 * Apr. 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// Note: check for memory leaks using, e.g.:
// valgrind --leak-check=full ./bankers safe.txt

// Global variables: matrices and matrix dimensions
// TODO: I do not think these need to be globals (we are not multithreading)
// int NRES;       // number of resource types (number of columns)
// int NPROC;      // number of processes (number of rows)

/**
 * Sanity check: ensure the values given in the files are correct.
 * 1) Ensure currently allocated resources do not exceed total number of resources.
 * 2) Ensure each thread’s needs do not exceed its max demands for each resource type.
 * If either of these tests fail, output an error and exit.
 */
void sanityCheck(int *availVec, int **needMat, int **maxMat, int NPROC, int NRES)
{
  // Ensure currently allocated resources do not exceed total number of resources.
  // that is, totAlloc <= totVec
  for (int col = 0; col < NRES; col++)
  {
    if (availVec[col] < 0)
    {
      printf("Failed sanity check: currently allocated resources exeed total number of resources.\n");
      exit(EXIT_FAILURE);
    }
  }

  // Ensure each thread’s needs do not exceed its max demands for each resource type.
  // that is, ensure maxMat <= needMat for every element
  for (int row = 0; row < NPROC; row++)
  {
    for (int col = 0; col < NRES; col++)
    {
      if (needMat[row][col] < 0)
      {
        printf("Failed sanity check: need matrix has an element < 0.\n");
        exit(EXIT_FAILURE);
      }
      if (needMat[row][col] > maxMat[row][col])
      {
        printf("Failed sanity check: thread’s needs exceed max demands for one ore more resource type.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  return;
}

/**
 * Quality control the inputs and return the filename
 * @param argc  Number of inputs
 * @param argv  Inputs
 * @returns  The filename from the inputs
 * @throw EXIT_FAILURE if number of inputs is wrong
 */
char *parseInputs(int argc, char *argv[])
{
  // Get and QC number of inputs, where the possible run commands are:
  if (argc != 2)
  {
    printf("Usage: ./bankersSol <scenario file>\n");
    exit(EXIT_FAILURE);
  }
  // Return the filename
  char *filename = argv[1];
  return filename;
}

/**
 * Allocate the matrices on the heap.
 */
void initMats(int *availVec, int **allocMat, int **needMat, int **maxMat, int NRES, int NPROC)
{
  // TODO: this does not work

  // malloc the vectors
  availVec = (int *)malloc(sizeof(int) * NRES);

  // malloc the number of rows first - a size NPROC array of pointers to ints
  allocMat = (int **)malloc(sizeof(int *) * NPROC);
  needMat = (int **)malloc(sizeof(int *) * NPROC);
  maxMat = (int **)malloc(sizeof(int *) * NPROC);

  // iterate through each row and malloc a size NRES array of ints for the resources
  for (int i = 0; i < NPROC; i++)
  {
    allocMat[i] = (int *)malloc(sizeof(int) * NRES);
    needMat[i] = (int *)malloc(sizeof(int) * NRES);
    maxMat[i] = (int *)malloc(sizeof(int) * NRES);
  }

  return;
}

/**
 * Free the matrices from the heap.
 */
void freeMats(int *availVec, int **allocMat, int **needMat, int **maxMat, int NRES, int NPROC)
{
  // free each row
  for (int i = 0; i < NPROC; i++)
  {
    // Free ith row
    free(allocMat[i]);
    free(needMat[i]);
    free(maxMat[i]);
    // Remove dangling pointers
    allocMat[i] = NULL;
    needMat[i] = NULL;
    maxMat[i] = NULL;
  }

  // free the matrices
  free(availVec);
  free(allocMat);
  free(needMat);
  free(maxMat);

  // remove dangling pointers
  availVec = NULL;
  allocMat = NULL;
  needMat = NULL;
  maxMat = NULL;

  return;
}

/**
 * Run the bankers algorithm
 * @param argc  Number of input arguments
 * @param argv  Input arguments - file name
 */
int main(int argc, char *argv[])
{
  // Variables
  int NRES;       // number of resource types (number of columns)
  int NPROC;      // number of processes (number of rows)
  int *availVec;  // number of resources available for each type
  int **allocMat; // number of resources allocated to each thread for each resource type
  int **needMat;  // number of resources needed by each thread for each resource type
  int **maxMat;   // total number of resources each thread will ever need, for each rsrc type

  // Get and quality control inputs
  char *filename = parseInputs(argc, argv);

  // Return with message if file does not exist
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("File %s does not exist\n", filename);
    return 0;
  }

  // Open scenario file and scan data into allocated structures
  // File contents:
  // <number of resource types>
  // <number of processes> <blank line>
  // <total resource vector> <blank line>
  // <max demand matrix> <blank line>
  // <allocation matrix>
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);
  // scan in the total number of resources
  int totVec[NRES];
  int val;
  for (int i = 0; i < NRES; i++)
  {
    fscanf(fp, "%d", &val);
    totVec[i] = val;
  }

  // TODO: which way?
  // malloc space for matrices and vectors
  // initMats(*availVec, allocMat, needMat, maxMat, NRES, NPROC);
  // malloc the vectors
  availVec = (int *)malloc(sizeof(int) * NRES);

  // malloc the number of rows first - a size NPROC array of pointers to ints
  allocMat = (int **)malloc(sizeof(int *) * NPROC);
  needMat = (int **)malloc(sizeof(int *) * NPROC);
  maxMat = (int **)malloc(sizeof(int *) * NPROC);

  // iterate through each row and malloc a size NRES array of ints for the resources
  for (int i = 0; i < NPROC; i++)
  {
    allocMat[i] = (int *)malloc(sizeof(int) * NRES);
    needMat[i] = (int *)malloc(sizeof(int) * NRES);
    maxMat[i] = (int *)malloc(sizeof(int) * NRES);
  }

  // Fill in the max demand matrix. This is the maximum demand of each thread for
  // each resource over the thread's lifetime
  for (int row = 0; row < NPROC; row++)
  {
    for (int col = 0; col < NRES; col++)
    {
      fscanf(fp, "%d", &val);
      maxMat[row][col] = val;
    }
  }

  // Fill in the matrix for the allocation for each thread and each resource: allocMat
  // This is the number of resources that are currently allocated, for each type
  for (int row = 0; row < NPROC; row++)
  {
    for (int col = 0; col < NRES; col++)
    {
      fscanf(fp, "%d", &val);
      allocMat[row][col] = val;
    }
  }

  // Get the availability resource vector
  int totAllocVec[NRES];
  sumRows(allocMat, NPROC, NRES, totAllocVec);

  // Compute the availability vector
  // Recall that totVec contains the total number of resources
  // totAllocVec is the sum of the allocation matrix
  subtractvecs(totVec, totAllocVec, availVec, NRES);

  // The need matrix is maximum demand - current allocation
  subtractmats(maxMat, allocMat, needMat, NPROC, NRES);

  sanityCheck(availVec, needMat, maxMat, NPROC, NRES);

  // Run banker's safety algorithm
  int safety = isSafe(availVec, allocMat, needMat, NPROC, NRES);

  // Free the space for the matrices
  freeMats(availVec, allocMat, needMat, maxMat, NRES, NPROC);

  return safety;
}
