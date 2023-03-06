#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>	// for errno
#include <limits.h> // for INT_MAX, INT_MIN
#include "rtclock.h"
#include "mmm.h"
#include "parseInputs.h"

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
	int inputs[3] = {1, 4, 0};

	// The variables
	int nthreads = inputs[0];
	int runtype = inputs[2];
	matdim = inputs[1];

	printf("Type of run (0=>single, 1=>parallel): %d\n", runtype);
	printf("nthreads = %d\n", nthreads);
	printf("size = %d\n", matdim);

	// Initialze the matrices
	mmm_init();

	// TODO: remove this line
	mmm_print();

	double clockstart, clockend;
	clockstart = rtclock(); // start clocking

	// start: stuff I want to clock
	if (runtype == 0)
	{
		// TODO: delete this line
		printf("You have chosen sequential\n");
		mmm_seq();
	}
	else if (runtype == 1)
	{
		// TODO: delete this line
		printf("You have chosen parallel implementation\n");
		// mmm_par();
	}
	else
	{
		printf("Unexpected value for runtype\n");
		exit(EXIT_FAILURE);
	}
	// end: stuff I want to clock

	clockend = rtclock(); // stop clocking
	printf("Time taken: %.6f sec\n", (clockend - clockstart));

	// Freeup the array
	mmm_freeup();

	return 0;
}
