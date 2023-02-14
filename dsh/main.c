/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

int main(int argc, char **argv)
{

	// TODO: clean up following
	char cmdline[MAXBUF]; // = "git add .\n"; // stores user input from commmand line

	// Main command-prompt loop that repeatedly accepts input
	while (1)
	{
		// Print the prompt, then get and split user input
		printf("dsh> ");
		fgets(cmdline, MAXBUF, stdin); // read up to 256 chars into buffer

		char **array = split(cmdline, " ");
		printarray(array);

		// TODO: Work on handling the built-in commands.

		// TODO: Work on command execution when given the full path to an executable. (Mode 1)
		// TODO: Finally, work on execution when given just the name of an executable. (Mode 2)

		if ((array[0] != NULL) && (strcmp(array[0], "exit") == 0))
			break;
	}
}
