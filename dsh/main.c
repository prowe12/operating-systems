/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For getcwd(), chdir()
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"
#include "dsh.h"

int main(int argc, char **argv)
{

	// TODO: clean up following
	char cmdline[MAXBUF];	// = "git add .\n"; // stores user input from commmand line
	char cmdlineIn[MAXBUF]; // = "git add .\n"; // stores user input from commmand line

	// Main command-prompt loop that repeatedly accepts input
	while (1)
	{
		// Print the prompt, then get and split user input
		printf("dsh> ");
		fgets(cmdlineIn, MAXBUF, stdin); // read up to 256 chars into buffer

		// Remove trailing spaces and replace return at end with null character
		cleanup(cmdlineIn, cmdline);
		printf("[%s]\n", cmdline);

		if (strlen(cmdline) == 0)
			continue;

		int numtokens = getNumTokens(cmdline, " ");
		printf("numtokens: %d\n", numtokens);

		char **array = split(cmdline, " ", numtokens);
		printf("array[0]: %s\n", array[0]);
		printarray(array);

		int nargs = numtokens - 1;
		printf("nargs: %d\n", nargs);

		char *cmd = array[0];
		if (cmd == NULL)
			continue;
		else if (!strcmp(cmd, "exit"))
			break;
		else if (!strcmp(cmd, "cd"))
			changeDir(array, nargs);
		else if (!strcmp(cmd, "pwd"))
			printCwd(nargs);
		// else if (!strcmp(cmd, "history"))
		// 	printf("history\n");
		// else if (!strcmp(cmd, "echo"))
		// 	printf("echo\n");

		// TODO: Work on command execution when given the full path to an executable. (Mode 1)
		// TODO: Finally, work on execution when given just the name of an executable. (Mode 2)
	}
}
