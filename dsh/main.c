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

// TODO NotARealcommand -o should return ERROR: NotARealcommand not found!
// TODO cat feelGood.c does not end with a carriage return
// TODO after cat feelGood.c, it hangs
// TODO: ./feelGood does nothing
// TOOD: implement &
// TODO: run valgrind to check for memory leaks
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

		if (strlen(cmdline) == 0)
			continue;

		int numtokens = getNumTokens(cmdline, " ");

		char **array = split(cmdline, " ", numtokens);
		int nargs = numtokens - 1;

		char *cmd = array[0];
		if (cmd == NULL)
			continue;
		else if (!strcmp(cmd, "exit"))
			break;
		else if (!strcmp(cmd, "cd"))
			changeDir(array, nargs);
		else if (!strcmp(cmd, "pwd"))
			printCwd(nargs);
		else
		{
			int child_pid = buildPathAndExecuteCmd(array);
			if (child_pid == 0)
				break; // Child process - done!
		}
	}
}
