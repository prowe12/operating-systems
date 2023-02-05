/*
 * main.c
 *
 *  Created on: Feb. 4, 2023
 *      Author: Penny Rowe
 *
 * Reminder: valgrind --leak-check=full ./ls2 dum2 file2a
 * If object is a pointer to a struct, use ->
 * If object is a struct, use .
 *
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

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	char *path;
	// int getall = 1; // Boolean - whether to look for file in each dir
	// int i;

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

	// We will need an array to store all the file and directory strings
	// malloc a size N array of pointers to ints
	// but what size?  What's the point of a malloc if we don't know the size?
	// Should we traverse through first to get the sizes?
	// For now, just assume 100 characters x 100 strings
	int nstrings = 100; // Just allow 100 for now
	int nchars = 100;
	char **dirArray = (char **)malloc(sizeof(char *) * nstrings);
	// iterate through each row and malloc a size N array of ints
	for (int i = 0; i < nstrings; i++)
	{
		dirArray[i] = (char *)malloc(sizeof(char) * nchars);
	}

	// TODO: remove following
	printf("You have chosen to look into path: %s\n", path);

	// TODO: if there are two inputs, get file to check for
	if (argc == 2)
	{
		// 	getall = 1;
		// printf("Get all filenames\n");
		pushToStack(s, path, dirArray, 0);
	}
	else if (argc == 3)
	{
		// char *fname = argv[2];
		// 	getall = 0;
		// printf("Get only file: %s\n", fname);
		pushToStack(s, path, dirArray, 0);
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

	// free the array; first free each row
	for (int i = 0; i < nstrings; i++)
	{
		free(dirArray[i]);
		dirArray[i] = NULL;
	}
	// free original array
	free(dirArray);
	dirArray = NULL;
	return 0;
}
