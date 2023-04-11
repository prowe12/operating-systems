
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"
#include "parseInputs.h"
#include "rtclock.h"
#include <assert.h>

// checking for memory leaks:
// valgrind --leak-check=full ./hashtest 2 2

// Make the hashmap global
ts_hashmap_t *map;

void test1()
{
	unsigned int capacity = 5;
	printf("Running test1, with capacity: %d\n", capacity);

	// The initial size of the array should be allocated to capacity
	// Get the thread-safe hashmap pointer.
	ts_hashmap_t *mymap = initmap(capacity);
	put(mymap, 3, 3);
	put(mymap, 1, 1);
	put(mymap, 10, 10);
	put(mymap, 7, 7);
	put(mymap, 8, 8);
	put(mymap, 9, 9);
	put(mymap, 11, 11);
	put(mymap, 12, 12);
	put(mymap, 13, 13);
	put(mymap, 14, 14);

	printf("The filled map: \n");
	printmap(mymap);

	// Test the get function
	assert(get(mymap, 7) == 7);
	assert(get(mymap, 10) == 10);
	assert(get(mymap, 3) == 3);
	assert(get(mymap, 8) == 8);
	assert(get(mymap, 13) == 13);

	// Test replacing (same key, different value)
	assert(mymap->size == 10);
	put(mymap, 3, 4);
	assert(mymap->size == 10);

	// Test deleting a key at the head that is also terminal
	del(mymap, 10);
	assert(mymap->size == 9);
	printf("After deleting a key at the head that is also terminal (10)\n");
	printmap(mymap);

	// Test deleting a key at the head, with a node after
	del(mymap, 9);
	assert(mymap->size == 8);
	printf("After deleting a key at the head (9)\n");
	printmap(mymap);

	// Test deleting a key in the middle
	printf("After deleting a key in the middle (8)\n");
	del(mymap, 8);
	assert(mymap->size == 7);
	printmap(mymap);

	// Test deleting a key at the end
	del(mymap, 13);
	assert(mymap->size == 6);

	// Test deleting a key that does not exist
	del(mymap, 13);
	assert(mymap->size == 6);

	printf("The final map: \n");
	printmap(mymap);

	// Free all the space
	printf("\n\nFreeing everything\n");
	freemap(mymap);

	return;
}

/**
 * Call the hashmap methods
 */
void hashmap_runner(int numtimes)
{
	int choice, randno;

	for (int i = 0; i < numtimes; i++)
	{
		// TODO: fix
		// Choose whether to delete, get, or put
		choice = rand() % 3;
		// choice = i % 3;

		// TODO: fix
		// Get a random number
		randno = rand() % 100000;
		// randno = i % 100000;

		if (choice == 0)
			del(map, randno);
		else if (choice == 1)
			get(map, randno);
		else if (choice == 2)
			put(map, randno, randno);
		else
		{
			printf("Bad value for choice; quitting\n");
			return;
		}
	}
	return;
}

void *hashmap_runner1thread()
{
	hashmap_runner(100000);
	return 0;
}

void *hashmap_runner2threads()
{
	hashmap_runner(200000);
	return 0;
}

void *hashmap_runner3threads()
{
	hashmap_runner(300000);
	return 0;
}

void *hashmap_runner4threads()
{
	hashmap_runner(400000);
	return 0;
}

void *hashmap_runner5threads()
{
	hashmap_runner(500000);
	return 0;
}

void *hashmap_runner100()
{
	hashmap_runner(100);
	return 0;
}

/**
 * Function to test the hashmap methods
 */
void timetest1thread(int capacity, int numthreads)
{
	double clockstart, clockend;

	// One run to warm up, then three to test
	clockstart = rtclock(); // start clocking

	int nruns = 10.;

	for (int i = 0; i < nruns; i++)
	{
		// The initial size of the array should be allocated to capacity
		// Get the thread-safe hashmap pointer.
		map = initmap(capacity);

		// allocate space to hold threads
		pthread_t *threads = (pthread_t *)malloc(1 * sizeof(pthread_t));

		// Create 1 thread, but run it the same number of times as would happen
		// for numthreads
		if (numthreads == 1)
			pthread_create(&threads[0], NULL, hashmap_runner1thread, NULL);
		else if (numthreads == 2)
			pthread_create(&threads[0], NULL, hashmap_runner2threads, NULL);
		else if (numthreads == 3)
			pthread_create(&threads[0], NULL, hashmap_runner3threads, NULL);
		else if (numthreads == 4)
			pthread_create(&threads[0], NULL, hashmap_runner4threads, NULL);
		else if (numthreads == 5)
			pthread_create(&threads[0], NULL, hashmap_runner5threads, NULL);
		else if (numthreads > 5)
			printf("Not implemented");

		// Join threads
		pthread_join(threads[0], NULL);

		// printmap(map);
		freemap(map);
		free(threads);
	}
	clockend = rtclock(); // stop clocking

	float time1thread = (clockend - clockstart) / nruns;
	printf("Time for one thread (avg of %d runs): %.6f sec\n", nruns, time1thread);

	return;
}

/**
 * Function to test the hashmap methods
 */
void timetestmultithreads(int capacity, int numthreads)
{
	double clockstart, clockend;

	// One run to warm up, then three to test
	clockstart = rtclock(); // start clocking

	int nruns = 10.;

	for (int i = 0; i < nruns; i++)
	{

		// The initial size of the array should be allocated to capacity
		// Get the thread-safe hashmap pointer.
		map = initmap(capacity);

		// allocate space to hold threads
		pthread_t *threads = (pthread_t *)malloc(numthreads * sizeof(pthread_t));

		// Create threads
		for (int i = 0; i < numthreads; i++)
		{
			pthread_create(&threads[i], NULL, hashmap_runner1thread, NULL);
		}

		// Join threads
		for (int ithread = 0; ithread < numthreads; ithread++)
		{
			pthread_join(threads[ithread], NULL);
		}

		// printmap(map);
		freemap(map);
		free(threads);
	}
	clockend = rtclock(); // stop clocking

	float timemultithreads = (clockend - clockstart) / nruns;
	printf("Time for %d threads (avg of %d runs): %.6f sec\n", numthreads, nruns, timemultithreads);

	return;
}

/**
 * Function to test the hashmap methods
 */
void test(int capacity, int numthreads)
{

	// TODO:
	// 1) make sure the multi-threaded one is faster.
	//    If not, then I just have one lock.
	// 2)

	// The initial size of the array should be allocated to capacity
	// Get the thread-safe hashmap pointer.
	map = initmap(capacity);

	// allocate space to hold threads
	pthread_t *threads = (pthread_t *)malloc(numthreads * sizeof(pthread_t));

	// Create threads
	for (int i = 0; i < numthreads; i++)
	{
		pthread_create(&threads[i], NULL, hashmap_runner100, NULL);
	}

	// Join threads
	for (int ithread = 0; ithread < numthreads; ithread++)
	{
		pthread_join(threads[ithread], NULL);
	}

	printmap(map);
	freemap(map);
	free(threads);

	return;
}

int main(int argc, char *argv[])
{
	if (parseInputs(argc, argv) == 0)
		return 1;

	// TODO: time(NULL) gives you the current time as a struct.
	// TODO: are there duplicate keys in the bucket?
	// TODO: does it segfault: should run awhile
	srand(time(NULL));

	int numthreads = atoi(argv[1]);
	int capacity = (unsigned int)atoi(argv[2]);

	// test1();
	// test(capacity, numthreads);
	//  lockfun();
	timetest1thread(capacity, numthreads);
	timetestmultithreads(capacity, numthreads);

	return 0;
}

// Building up from doing nothing but incrementing x:
// 0.0067 vs 0.0046:  0.69
// 0.0068 vs 0.00455: 0.67
// 0.025751 vs 0.051104: 1.98
// 0.053886 vs 0.165523: 3.07
// 0.079 vs 0.148: 1.86
// 0.105 vs 0.208: 1.99
// 0.132 vs 0.271: 2.06
// 0.384 vs 0.914: 2.38
// 0.388 vs 0.778: 2.00

// nruns, nthreads, capacity, time
// 2000000, 1, 1, 0.463
// 2000000, 2, 1, 0.955
// 2000000, 1, 100, 0.154
// 2000000, 2, 100, 0.441

// nruns, nthreads, capacity, time
// 3000000, 1, 1, 0.698
// 3000000, 3, 1, 1.043
// 3000000, 1, 2, 0.470
// 3000000, 3, 2, 0.602
// 3000000, 1, 3, 0.388
// 3000000, 3, 3, 0.814
// 3000000, 1, 4, 0.346
// 3000000, 3, 4, 0.948
// 3000000, 1, 100, 0.220
// 3000000, 3, 100, 0.820
// 3000000, 1, 1000, 0.220
// 3000000, 3, 1000, 0.673
// 3000000, 1, 10000, 0.222
// 3000000, 3, 10000, 0.729

// 1000000, 1, 100, 0.073769
// 1000000, 1, 100, 0.073774

// 2000000, 1, 100, 0.148 sec
// 2000000, 2, 100, 0.434 sec
// 2000000, 1, 1000, 0.146 sec
// 2000000, 2, 1000, 0.500 sec

// 5000000, 1, 100, 0.368
// 5000000, 5, 100, 1.431
