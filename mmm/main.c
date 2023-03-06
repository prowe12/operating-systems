#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>	// for errno
#include <limits.h> // for INT_MAX, INT_MIN
#include "rtclock.h"
#include "mmm.h"

void badNumberInputs()
{
	printf("Usage: ./mmm S <size> or \n");
	printf("./mmm P <threads> <size> \n");
	exit(EXIT_FAILURE);
	return;
}

int strToInt(char *inputStr)
{
	// From https://stackoverflow.com/questions/9748393/how-can-i-get-argv-as-int
	// Check for errors: e.g., the string does not represent an integer
	// or the integer is larger than int

	char *p;
	int num = 0;
	long conv = strtol(inputStr, &p, 10);

	if (errno != 0 || *p != '\0')
	{
		// User entered a character; quit
		printf("%s\n", "Please enter integers for the matrix size and/or number of threads.\n");
		exit(EXIT_FAILURE);
	}
	else if (conv < 0 || conv > INT_MAX)
	{ // Integer outside range; quit
		printf("Matrix size and number of threads must be betwen 0 and %d.\n", INT_MAX);
		exit(EXIT_FAILURE);
	}
	else
		num = conv;
	return num;
}

int getSize(char *sizeStr)
{
	printf("In getSize\n");
	int size = strToInt(sizeStr);
	return size;
}

int getRunType(char *runTypeStr)
{
	if (strlen(runTypeStr) == 1 && *runTypeStr == 'S')
		return 0;
	else if (strlen(runTypeStr) == 1 && *runTypeStr == 'P')
		return 1;
	else
	{
		printf("The type of run must be S for single or P for Parallel\n");
		exit(EXIT_FAILURE);
	}
	return -1;
}

int getNthreads(char *sizeStr)
{
	printf("In getNthreads \n");
	int nthreads = strToInt(sizeStr);
	return nthreads;
}

void parseInputs(char *buf, int argc, char *argv[])
{
	// Get and QC number of inputs, where the possible run commands are:
	if (argc != 3 && argc != 4)
	{
		badNumberInputs();
		return;
	}

	int runType = getRunType(argv[1]);
	int nthreads = 0;
	int size = 0;
	if (runType == 0 && argc == 3)
	{
		nthreads = 1;
		size = getSize(argv[2]);
	}
	else if (runType == 1 && argc == 4)
	{
		nthreads = getNthreads(argv[2]);
		size = getSize(argv[3]);
	}
	else
	{
		badNumberInputs();
		return;
	}
	buf[0] = nthreads;
	buf[1] = size;
	buf[2] = 0;
	return;
}

int main(int argc, char *argv[])
{
	// Command Line call
	// $ ./mmm S <size>
	// $ ./mmm P <threads> <size>

	// Get the inputs
	// int inputs[3] = {0};
	// TODO: uncomment following block
	// parseInputs(inputs, argc, argv);

	// TODO: remove following block
	int inputs[3] = {1, 3, 0};

	// The variables
	int nthreads = inputs[0];
	int runtype = inputs[2];
	matdim = inputs[1];

	printf("Type of run (0=>single, 1=>parallel): %d\n", runtype);
	printf("nthreads = %d\n", nthreads);
	printf("size = %d\n", matdim);

	// Initialze the matrices
	mmm_init();

	mmm_print();

	double clockstart, clockend;
	clockstart = rtclock(); // start clocking

	// start: stuff I want to clock

	// end: stuff I want to clock

	clockend = rtclock(); // stop clocking
	printf("Time taken: %.6f sec\n", (clockend - clockstart));

	return 0;
}
