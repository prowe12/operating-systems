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

	// TODO: Write the main command-prompt loop to repeatedly accept input. Test the split(..) function you just wrote on various inputs, including empty string.
	// TODO: You should be using fgets() to accept user inputs. Remember that the “enter” key is logged as a '\n' character at the end of the string! You’ll probably want to truncate that newline character as soon as you obtain the user input, and that’s as simple as putting the '\0' character in its place.
	// TODO: Work on handling the built-in commands next.
	// TODO: Work on command execution when given the full path to an executable. (Mode 1)
	// TODO: Finally, work on execution when given just the name of an executable. (Mode 2)

	// TODO: remove assignment in following
	char cmdline[MAXBUF] = "git add .\n"; // stores user input from commmand line

	// Print the prompt
	printf("dsh> ");

	// TODO: Uncomment this line
	// fgets(cmdline, 256, stdin);		  // read up to 256 chars into buffer

	// TODO: Delete this line
	printf("\n");

	// TODO: Uncomment fgets line; delete line =
	// Accept user input
}
