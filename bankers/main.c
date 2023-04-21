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
int NRES;  // number of resource types (number of columns)
int NPROC; // number of processes (number of rows)
int **availMat;
int **allocMat;
int **needMat;

/**
 * Sanity check: ensure the values given in the files are correct.
 * 1) Ensure currently allocated resources do not exceed total number of resources.
 * 2) Ensure each thread’s needs do not exceed its max demands for each resource type.
 * If either of these tests fail, output an error and exit.
 */
void sanityCheck(int **allocMat, int **totMat, int **needMat)
{
  // TODO: Ensure currently allocated resources do not exceed total number of resources.

  // TODO: Ensure each thread’s needs do not exceed its max demands for each resource type.

  // If either of these tests fail, output an error and exit.
  return;
}

void qcInputs(int argc, char *argv[])
{
  // TODO: should have one input, which is name of file
  // if not, print message:
  // Usage: ./bankersSol <scenario file>
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
  if (argc != 1)
  {
    printf("Usage: ./bankersSol <scenario file>\n");
    exit(EXIT_FAILURE);
  }
  // Return the filename
  char *filename = argv[0];
  return filename;
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

  // TODO: make sure file exists and return with error message if not
  // int status = fopen(filename);
  // if status == NULL:
  //    printf("File %c does not exist\n", filename);
  //    return;

  // TODO: attempt to open scenario file and scan data into allocated structures
  // File contents:
  // <number of resource types>
  // <number of processes>
  // <blank line>
  // <total resource vector>
  // <blank line>
  // <max demand matrix>
  // <blank line>
  // <allocation matrix>

  // TODO: function to read in the inputs from the file
  // Notes from assignment:
  // Notice the format of the state file. Every “token” is already separated
  // by whitespace (either tab or newline). That’s super convenient, because it
  // allows you to simply use successive fscanf() calls to grab every token in the file.
  //
  // fscanf(fp, "%d", &NRES);
  // fscanf(fp, "%d", &NPROC);
  // totalResource
  // maxDemand
  // alloc

  // These need to mallocd on the heap
  int **allocMat;
  int **totMat;
  int **needMat;

  // TODO: sanity check
  sanityCheck(allocMat, totMat, needMat);

  // Get the availability resource matrix
  int **availMat = subtractmats(totMat, allocMat);

  // TODO: Run banker's safety algorithm
  isSafe(availMat, allocMat, needMat);

  return 0;
}