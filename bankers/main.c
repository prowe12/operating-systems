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

/**
 * Sanity check: ensure the values given in the files are correct.
 * 1) Ensure currently allocated resources do not exceed total number of resources.
 * 2) Ensure each thread’s needs do not exceed its max demands for each resource type.
 * If either of these tests fail, output an error and exit.
 * @param availVec  Number of resources available for each type
 * @param needMat  Number of resources needed by each thread for each resource type
 * @param maxMat  Total number of resources each thread will ever need, for each resource type
 * @param nproc  Number of processes/threads (number of rows)
 * @param nres  Number of resource types (number of columns)
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
 * Free the vectors from the heap
 * @param availVec  Number of resources available for each type
 * @param threadorderVec  The order the threads/process are run
 * @param workVec  The current work vector
 * @param finishVec  The state of each thread (finished=>1, else 0)
 */
void freeVecs(int *availVec, int *threadorderVec, int *workVec, int *finishVec)
{
  // free the vectors
  free(availVec);
  free(threadorderVec);
  free(workVec);
  free(finishVec);

  // remove dangling pointers
  availVec = NULL;
  threadorderVec = NULL;
  workVec = NULL;
  finishVec = NULL;
  return;
}

/**
 * Free the matrices from the heap.
 * @param allocMat  number of resources allocated to each thread for each resource type
 * @param needMat  Number of resources needed by each thread for each resource type
 * @param maxMat  Total number of resources each thread will ever need, for each resource type
 * @param nproc  Number of processes/threads (number of rows)
 */
void freeMats(int **allocMat, int **needMat, int **maxMat, int nproc)
{
  // free each row
  for (int i = 0; i < nproc; i++)
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

  // free the vectors and matrices
  free(allocMat);
  free(needMat);
  free(maxMat);

  // remove dangling pointers
  allocMat = NULL;
  needMat = NULL;
  maxMat = NULL;

  return;
}

/**
 * Run the bankers algorithm
 * @param argc  Number of input arguments
 * @param argv  Input arguments - file name
 * @returns  1 if the threads can be run safely, else 0
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

  // Malloc the vectors and matrices
  availVec = (int *)malloc(sizeof(int) * NRES);
  allocMat = (int **)malloc(sizeof(int *) * NPROC);
  needMat = (int **)malloc(sizeof(int *) * NPROC);
  maxMat = (int **)malloc(sizeof(int *) * NPROC);

  // For the matrices iterate through each row and malloc a size NRES array of ints for the resources
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

  // Set up the other vectors; set all threads to unfinished
  // and clone the work vector from the availability vector
  int *finishVec = (int *)malloc(sizeof(int) * NPROC);
  for (int t = 0; t < NPROC; t++)
    finishVec[t] = 0;
  int *threadorderVec = (int *)malloc(sizeof(int) * NPROC);
  int *workVec = (int *)malloc(sizeof(int) * NRES);
  clonevec(availVec, workVec, NRES);

  // Run the Bankers safety algorithm
  int safety = isSafe(0, threadorderVec, finishVec, workVec, allocMat, needMat, NRES, NPROC);

  // Free the mallocd space for the vectors and matrices
  freeVecs(availVec, threadorderVec, workVec, finishVec);
  freeMats(allocMat, needMat, maxMat, NPROC);

  return safety;
}
