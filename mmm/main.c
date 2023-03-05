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

int getSize(int argc, char *argv[])
{
	int size = 0;
	if (argc == 2)
		size = strToInt(argv[1]);
	else if (argc == 3)
		size = strToInt(argv[2]);
	else
		badNumberInputs();
	return size;
}

int getNthreads(int argc, char *argv[])
{
	int nthreads = 0;
	if (argc == 2)
		nthreads = 1;
	else if (argc == 3)
		nthreads = strToInt(argv[1]);
	else
		badNumberInputs();

	return nthreads;
}

int main(int argc, char *argv[])
{
	// Command Line call
	// $ ./mmm S <size>
	// $ ./mmm P <threads> <size>
	int nthreads = getNthreads(argc, argv);
	int size = getSize(argc, argv);

	printf("nthreads = %d\n", nthreads);
	printf("size = %d\n", size);

	double clockstart, clockend;
	clockstart = rtclock(); // start clocking

	// start: stuff I want to clock

	// end: stuff I want to clock

	clockend = rtclock(); // stop clocking
	printf("Time taken: %.6f sec\n", (clockend - clockstart));

	return 0;
}
