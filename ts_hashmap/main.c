
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"
#include "parseInputs.h"

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
	printf("The value for key 7 is: %d\n", get(mymap, 7));
	printf("The value for key 10 is: %d\n", get(mymap, 10));
	printf("The value for key 3 is: %d\n", get(mymap, 3));
	printf("The value for key 8 is: %d\n", get(mymap, 8));
	printf("The value for key 13 is: %d\n", get(mymap, 13));

	// Test replacing (same key, different value)
	put(mymap, 3, 4);
	printf("The size does not change, it is still: %d\n", mymap->size);

	// Test deleting a key at the head that is also terminal
	del(mymap, 10);
	printf("After deleting a key at the head that is also terminal (10)\n");
	printmap(mymap);

	// Test deleting a key at the head, with a node after
	del(mymap, 9);
	printf("After deleting a key at the head (9)\n");
	printmap(mymap);

	// Test deleting a key in the middle
	printf("After deleting a key in the middle (8)\n");
	del(mymap, 8);
	printmap(mymap);

	// Test deleting a key at the end
	del(mymap, 13);

	printf("The final map: \n");
	printmap(mymap);

	// Free all the space
	printf("\n\nAbout to free everything\n");
	freemap(mymap);

	return;
}

/**
 * Call the hashmap methods
 */
void *hashmap_runner()
{
	int choice, randno;
	for (int i = 0; i < 100; i++)
	{
		// Choose whether to delete, get, or put
		choice = rand() % 3;

		// Get a random number
		randno = rand() % 100;

		if (choice == 0)
			del(map, randno);
		else if (choice == 1)
			get(map, randno);
		else if (choice == 2)
			put(map, randno, randno);
		else
		{
			printf("Bad value for choice; quitting\n");
			return 0;
		}
	}
	return 0;
}

/**
 * Function to test the hashmap methods
 */
void test(int capacity, int numthreads)
{
	printf("Running test1\n");

	// The initial size of the array should be allocated to capacity
	// Get the thread-safe hashmap pointer.
	map = initmap(capacity);

	// allocate space to hold threads
	pthread_t *threads = (pthread_t *)malloc(numthreads * sizeof(pthread_t));

	// Create threads
	for (int i = 0; i < numthreads; i++)
	{
		pthread_create(&threads[i], NULL, hashmap_runner, NULL);
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

	// Unthreaded
	// ts_hashmap_t *unthreaded_map = initmap(capacity);
	// int choice;
	// printf("Looping %d times\n", numthreads * 100);
	// for (int i = 0; i < numthreads * 100; i++)
	// {
	// 	// Choose whether to delete, get, or put
	// 	choice = rand() % 3;

	// 	// Get a random number
	// 	int randno = rand() % 100;

	// 	if (choice == 0)
	// 		del(map, randno);
	// 	else if (choice == 1)
	// 		get(map, randno);
	// 	else if (choice == 2)
	// 		put(map, randno, randno);
	// 	else
	// 	{
	// 		printf("Bad value for choice; quitting\n");
	// 		return;
	// 	}
	// }

	// printf("The filled map: \n");
	// printmap(map);

	// // Free all the space
	// freemap(map);

	// return;
}

int main(int argc, char *argv[])
{
	if (parseInputs(argc, argv) == 0)
		return 1;

	srand(time(NULL));

	int numthreads = atoi(argv[1]);
	int capacity = (unsigned int)atoi(argv[2]);

	// test1();
	test(capacity, numthreads);
	// lockfun();

	return 0;
}