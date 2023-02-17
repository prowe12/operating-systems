/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For getcwd(), chdir(), etc
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"
#include "dsh.h"

// TODO: ./feelGood does nothing
// TOOD: implement &
// TODO: run valgrind to check for memory leaks
// TODO: improve overall organization
int main(int argc, char **argv)
{
	char cmdlineIn[MAXBUF]; // stores user input from commmand line
	char cmdline[MAXBUF];	// stores cleaned user input
	char **array;			// Here or down below?

	// Main command-prompt loop that repeatedly accepts input
	while (1)
	{

		// Print the prompt, then get and split user input
		printf("dsh> ");
		fgets(cmdlineIn, MAXBUF, stdin); // read up to 256 chars into buffer

		// Remove trailing spaces and replace return at end with null character
		cleanup(cmdlineIn, cmdline);

		printf("cmdline [%s]\n", cmdline);
		printf("strlen(cmdline) %ld\n", strlen(cmdline));
		if (strlen(cmdline) <= 1)
			continue;

		// Build the array for the command and get the number of arguments
		int numtokens = getNumTokens(cmdline, " ");
		array = split(cmdline, " ", numtokens);
		int nargs = numtokens - 1;

		// Perform the command
		if (array[0] == NULL)
		{
			freearray(array);
			continue;
		}
		else if (!strcmp(array[0], "exit"))
		{
			freearray(array);
			break;
		}
		else if (!strcmp(array[0], "cd"))
			changeDir(array, nargs);
		else if (!strcmp(array[0], "pwd"))
			printCwd(nargs);
		else
		{
			int child_pid = buildPathAndExecuteCmd(array);
			if (child_pid == 0)
			{
				printf("In child, about to free\n");

				freearray(array);
				printf("In child, just freed\n");
				break; // Child process - done!
			}
		}
		printf("Got to line 72 in main\n");
		freearray(array);
		// printarray(array);
		// printf("array[0] = [%s]\n", array[0]);
		// free(array[0]);
		// int i = 0;
		//  while (array[i])
		//  {
		//  	printf("%s\n", array[i]);
		//  	printf("got to line 326\n");
		//  	free(array[i]);
		//  	printf("In freearray, got to line 327\n");
		//  	i++;
		//  }
		// free(array);

		printf("Got past final free\n");
	}
}
