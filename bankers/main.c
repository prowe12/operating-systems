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
// I do not think these need to be global after all (we are not multithreading!)
int NRES;       // number of resource types (number of columns)
int NPROC;      // number of processes (number of rows)
int *availVec;  // number of resources available for each type
int **allocMat; // number of resources allocated to each thread for each resource type
int **needMat;  // number of resources needed by each thread for each resource type
int **maxMat;   // total number of resources each thread will ever need, for each rsrc type

/**
 * Sanity check: ensure the values given in the files are correct.
 * 1) Ensure currently allocated resources do not exceed total number of resources.
 * 2) Ensure each thread’s needs do not exceed its max demands for each resource type.
 * If either of these tests fail, output an error and exit.
 */
void sanityCheck(int *availVec, int **needMat, int **maxMat, int NPROC, int NRES)
{
  // TODO: Ensure currently allocated resources do not exceed total number of resources.
  // that is, totAlloc <= totVec
  for (int col = 0; col < NRES; col++)
  {
    if (availVec[col] < 0)
    {
      printf("Failed sanity check: currently allocated resources exeed total number of resources.\n");
      exit(EXIT_FAILURE);
    }
  }

  // TODO: Ensure each thread’s needs do not exceed its max demands for each resource type.
  // that is, ensure maxMat <= needMat for every element
  for (int row = 0; row < NPROC; row++)
  {
    for (int col = 0; col < NRES; col++)
    {
      // TODO: is it ok if the need matrix is less than 0?
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
void initMats()
{
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
void freeMats()
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

  // TODO: attempt to open scenario file and scan data into allocated structures
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
  printf("Got %d for NRES and %d for NPROC\n", NRES, NPROC);

  // malloc space for availVec, allocMat, needMat, and maxMat
  initMats();

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
  int totAllocVec[NRES]; //  = {0}; // =
  sumRows(allocMat, NPROC, NRES, totAllocVec);

  printf("Total allocation vector (totAllocVec):\n");
  printvec(totAllocVec, NRES);

  // Compute the availability vector
  subtractvecs(totVec, totAllocVec, availVec, NRES);

  // The need matrix is maximum demand - current allocation
  subtractmats(maxMat, allocMat, needMat, NPROC, NRES);

  // Make sure everything read in ok
  printf("Total number of resources (totVec):\n");
  printvec(totVec, NRES);
  printf("availability resource vector (availVec):\n");
  printvec(availVec, NRES);

  printf("Maximum demand of resources, per thread (maxMat):\n");
  printmat(maxMat, NPROC, NRES);
  printf("allocation for each thread and each resource (allocMat):\n");
  printmat(allocMat, NPROC, NRES);
  printf("Need matrix (needMat):\n");
  printmat(needMat, NPROC, NRES);

  sanityCheck(availVec, needMat, maxMat, NPROC, NRES);

  // TODO: Run banker's safety algorithm
  int safety = isSafe(availVec, allocMat, needMat, NPROC, NRES);

  // Free the space for the matrices
  freeMats();

  return safety;
}