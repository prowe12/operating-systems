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
	// int nstrings = 100; // Just allow 100 for now
	// char **dirArray = (char **)malloc(sizeof(char *) * nstrings);
	// int nchars = 100;
	// iterate through each row and malloc a size N array of ints
	// for (int i = 0; i < nstrings; i++)
	// {
	// 	dirArray[i] = (char *)malloc(sizeof(char) * nchars);
	// }

	// TODO: remove following
	printf("You have chosen to look into path: %s\n", path);

	// If there are two inputs, just print the directory tree.
	// If there are three inputs, go through stack and remove
	// elements that do not lead to the filename
	char *fname = NULL;
	if (argc == 2)
	{
		fname = NULL;
	}
	else if (argc == 3)
	{

		// Get the file name from the inputs and append " (" to the end
		// to avoid matching files that begin with the same substring
		fname = argv[2];
	}

	// Create the stack with the directory tree and put names into the array
	pushToStack(s, fname, path, 0);
	printstack(s);

	// int arraylen = pushToStackFile(s, fname, path, dirArray, 0, 0);
	// int arraylen = pushToStack(s, fname, path, 0);

	// printf("\n\nPrinting dirArray\n");
	// for (int i = 0; i < arraylen; i++)
	// {
	// 	printf("%d\n", i);
	// 	printf("%s\n", dirArray[i]);
	// }
	// printf("\n\n\n");

	// // print stack
	// printf("\n\nPrinting original stack:\n");
	// printstack(s);

	// // Concatenate to fname to be able to use strstr without identifying
	// // different files with fname within their names
	// strcat(fname, " (");

	// // Initialize a new stack to hold the final tree that only pertains
	// // to the file of interest
	// stack_t *t = initstack();

	// printf("\nGet tree for file: %s\n", fname);

	// stacknode_t *current = s->top;
	// printf("%s\n", (char *)current->data);

	// while (pop(s) != NULL)
	// {
	// 	// printf("\nPrinting stack after popping:\n");
	// 	// printstack(s);
	// 	stacknode_t *current = s->top;
	// 	if (current == NULL)
	// 		continue;

	// 	printf("%s\n", (char *)current->data);
	// 	// If the current item is a directory, recurse through it
	// 	// and look for files
	// 	if (strstr(current->data, "    "))
	// 	{
	// 		printf("Found item in a subfolder, skipping for now: ");
	// 		printf("%s\n", (char *)current->data);
	// 	}
	// 	else if (strstr(current->data, "(directory)") != NULL)
	// 	{
	// 		printf("Found a directory, skipping for now: ");
	// 		printf("%s\n", (char *)current->data);
	// 	}
	// 	else if (strstr(current->data, "bytes)") != NULL)
	// 	{
	// 		// If the current item is a file and it is not the file
	// 		// of interest, pop it off
	// 		printf("Found a file: ");
	// 		printf("%s\n", (char *)current->data);
	// 		printf("Checking for match with %s\n", fname);
	// 		printf("Match? %s\n", strstr(current->data, fname));
	// 		if (strstr((current->data), fname) != NULL)
	// 		{
	// 			printf("File matches, add to new stack!\n");
	// 			push(t, current->data);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		printf("Error: unexpected value in directory structure!");
	// 		return 0;
	// 	}

	// 	// current = current->next;
	// }
	// // print whats left of original stack (should be empty)
	// printf("\n\nPrinting stack:\n");
	// printstack(s);

	// // print new stack
	// printf("\n\nPrinting new stack:\n");
	// printstack(t);

	// // free up memory for the new stack
	// freestack(t);
	// }

	// Add the top directory int npath = strlen(path);
	// strcat(path, "/ (directory)");
	// push(s, path);
	// printf("concat path: %s\n", path);
	// path[npath + 1] = '\0';
	// printf("original path: %s\n", path);

	// free up memory
	freestack(s);

	// free the array; first free each row
	// for (int i = 0; i < nstrings; i++)
	// {
	// 	free(dirArray[i]);
	// 	dirArray[i] = NULL;
	// }
	// free original array
	// free(dirArray);
	// dirArray = NULL;
	return 0;
}

// // Loop over the stack
// stacknode_t *current = s->top;
// while (current != NULL)
// {
// 	pop(s);
// 	printf("\nPrinting stack after popping:\n");
// 	printstack(s);
// 	current = current->next;
// }
