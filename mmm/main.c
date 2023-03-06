#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>	// for errno
#include <limits.h> // for INT_MAX, INT_MIN
#include <math.h>	// ceil
#include "rtclock.h"
#include "mmm.h"
#include "parseInputs.h"

void run_mmm_par(int nthreads, int matdim)
{
	// prepare thread arguments
	thread_args *args = (thread_args *)malloc(nthreads * sizeof(thread_args));

	// TODO: do this, or change command line requirements?
	// If there are more threads than there are rows, dial back nthreads
	if (nthreads > matdim)
	{
		printf("Dialing back number of threads from %d to %d to stay <= matrix size\n", nthreads, matdim);
		nthreads = matdim;
	}
	// Get the number of rows per thread
	// int rows_per_thread, rem;
	// printf("number of rows: %d\n", matdim);
	int nrows;
	int nrowsdone = 0;
	int count = 0;
	for (int i = 0; i < nthreads; i++)
	{
		nrows = (int)ceil((float)(matdim - nrowsdone) / (nthreads - i));
		args[i].tid = i;
		args[i].first = count;
		args[i].last = count + nrows;
		nrowsdone += nrows;
		count += nrows;
	}

	// allocate space to hold threads
	pthread_t *threads = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	for (int i = 0; i < nthreads; i++)
		pthread_create(&threads[i], NULL, mmm_par, &args[i]);

	// Wait for threads to finish, then join
	for (int i = 0; i < nthreads; i++)
		pthread_join(threads[i], NULL);

	// clean up dynamically allocated memory
	free(threads);
	threads = NULL;
	free(args);
	args = NULL;
}

int main(int argc, char *argv[])
{

	// Command Line call
	// $ ./mmm S <size>
	// $ ./mmm P <threads> <size>

	// Get the inputs
	int inputs[3] = {0};
	parseInputs(inputs, argc, argv);

	// The variables
	int runtype = inputs[0];
	int nthreads = inputs[1];
	matdim = inputs[2];

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

	double clockstart, clockend;

	// Always do sequential.  One run to warm up, then three to test
	mmm_seq();
	clockstart = rtclock(); // start clocking
	int nruns = 3.;
	for (int i = 0; i < nruns; i++)
		mmm_seq();
	clockend = rtclock(); // stop clocking
	float seqTime = (clockend - clockstart) / nruns;
	printf("Sequential Time (avg of 3 runs): %.6f sec\n", seqTime);

	// start: stuff I want to clock
	if (runtype == 1)
	{
		// windup
		run_mmm_par(nthreads, matdim);

		// start clocking
		clockstart = rtclock();
		for (int i = 0; i < nruns; i++)
			run_mmm_par(nthreads, matdim);
		// stop clocking
		clockend = rtclock();

		// Get average run time
		float parTime = (clockend - clockstart) / nruns;

		// Get maximum error between matrix for sequential and for parallel
		float maxerr = mmm_verify();

		printf("Parallel Time (avg of 3 runs): %.6f sec\n", parTime);
		printf("Speedup: %.6f\n", (seqTime / parTime));
		printf("Verifying... largest error between parallel and sequential matrix: %f\n", maxerr);
	}

	// Freeup the arrays
	mmm_freeup();

	return 0;
}
