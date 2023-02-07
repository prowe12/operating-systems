/*
 * main.c
 *
 *  Created on: Feb. 4, 2023
 *      Author: Penny Rowe
 *
 * Reminders:
 *   valgrind --leak-check=full ./ls2 dum2 file2a
 *   If object is a pointer to a struct, use ->
 *   If object is a struct, use .
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>	  // for DIR* type from getdir
#include <sys/stat.h> // For stat, lstat, and S_ISDIR
#include "stack.h"
#include "ls2.h"

void quit(stack_t *s, char *msg)
{
	freestack(s);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	char *path;

	// stack stores the lines to print out
	stack_t *s = initstack();

	// QC number of inputs
	if ((argc < 2) || (argc > 3))
		quit(s, "Usage: ./ls2 <path> [optional-file]\n");

	// Get the path
	path = argv[1];

	// Check if it is a directory
	struct stat buf;
	int pathstat = lstat(path, &buf);
	if ((pathstat != 0) || (!S_ISDIR(buf.st_mode)))
		quit(s, "input not found or not a directory, exiting ...\n");

	// If there are two inputs, set fname to NULL to indicate that it
	// should not be used. If three inputs, capture entered filename
	char *fname = NULL;
	if (argc == 2)
		fname = NULL;
	else if (argc == 3)
		fname = argv[2];

	// Create the stack with the directory tree and put names into the array
	pushToStack(s, fname, path, 0);
	printstack(s);

	// free up memory
	freestack(s);

	return 0;
}
