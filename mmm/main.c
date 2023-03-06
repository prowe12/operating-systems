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
	// TODO list
	// matrices int or double?

	// Command Line call
	// $ ./mmm S <size>
	// $ ./mmm P <threads> <size>

	// Get the inputs
	// int inputs[3] = {0};
	// TODO: uncomment following block
	// parseInputs(inputs, argc, argv);

	// TODO: remove following block
	int inputs[3] = {1, 4, 1};

	// The variables
	int nthreads = inputs[0];
	int runtype = inputs[2];
	matdim = inputs[1];

	printf("========\n");
	if (runtype == 0)
		printf("mode: sequential\n");
	else
		printf("mode: parallel\n");

	printf("thread count: %d\n", nthreads);
	printf("size: %d\n", matdim);
	printf("========\n");

	printf("Type of run (0=>single, 1=>parallel): %d\n", runtype);
	printf("nthreads = %d\n", nthreads);
	printf("size = %d\n", matdim);

	// Initialze the matrices
	mmm_init();

	// TODO: remove this line
	mmm_print();

	double clockstart, clockend;

	// Always do sequential.  One run to warm up, then three to test
	mmm_seq();
	clockstart = rtclock(); // start clocking
	mmm_seq();
	mmm_seq();
	mmm_seq();
	clockend = rtclock(); // stop clocking
	float seqTime = (clockend - clockstart) / 3;
	printf("Sequential Time (avg of 3 runs): %.6f sec\n", seqTime);

	// start: stuff I want to clock
	if (runtype == 1)
	{
		clockstart = rtclock(); // start clocking
		mmm_seq();				// TODO: change to mmm_par!
		clockend = rtclock();	// stop clocking
		float parTime = (clockend - clockstart) / 3;

		printf("Parallel Time (avg of 3 runs): %.6f sec\n", parTime);
		printf("Speedup: %.6f sec\n", (seqTime / parTime));
		printf("Verifying... largest error between parallel and sequential matrix: \n");
	}

	// Freeup the arrays
	mmm_freeup();

	return 0;
}
