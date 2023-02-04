#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	char *path;
	int getall = 1; // Boolean - whether to look for file in each dir
	// int i;

	// stack stores the lines to print out
	stack_t *s = initstack();

	// QC number of inputs
	char *welcome = "Usage: ./ls2 <path> [optional-file]";
	if ((argc < 2) || (argc > 3))
	{
		printf("%s\n", welcome);
		return 0;
	}

	// Get the path and make sure it exists
	path = argv[1];
	// TODO: remove following
	printf("You have chosen to look into path: %s\n", path);

	// TODO QC: make sure the path exists
	// TODO: remove following line
	int pathexists = 1;
	if (!pathexists)
	{
		printf("%s is not a directory path! Exiting ...\n", path);
		return 0;
	}

	// TODO: if there are two inputs, get file to check for
	if (argc == 2)
	{
		getall = 1;
		printf("Get all filenames\n");
		getDirs(s);
	}
	else if (argc == 3)
	{
		char *fname = argv[1];
		getall = 0;
		printf("Get only file: %s\n", fname);
		getDirsWithFile(s, fname);
	}

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;
}
