/*
 * main.c
 *
 *  Created on: Feb. 4, 2023
 *      Author: Penny Rowe
 *
 * Reminder: valgrind --leak-check=full ./ls2 dum2 file2a
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "stack.h"
#include "ls2.h"

void quit(stack_t *s, char *msg)
{
	freestack(s);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

// If it is the pointer, use the ->
// If it is the struct, use .

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	char *path;
	int getall = 1; // Boolean - whether to look for file in each dir
	int i;

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

	// TODO: remove following
	printf("You have chosen to look into path: %s\n", path);

	// TODO: if there are two inputs, get file to check for
	if (argc == 2)
	{
		// 	getall = 1;
		// printf("Get all filenames\n");
		pushToStack(s, path, 0);
	}
	else if (argc == 3)
	{
		char *fname = argv[2];
		// 	getall = 0;
		// printf("Get only file: %s\n", fname);
		pushToStack(s, path, 0);
	}

	// Add the top directory int npath = strlen(path);
	// strcat(path, "/ (directory)");
	// push(s, path);
	// printf("concat path: %s\n", path);
	// path[npath + 1] = '\0';
	// printf("original path: %s\n", path);

	// print stack
	printf("\n\nPrinting stack:\n");
	printstack(s);

	// free up memory
	freestack(s);
	return 0;
}
