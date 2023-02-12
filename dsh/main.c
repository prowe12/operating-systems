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
	char cmdline[MAXBUF]; // stores user input from commmand line

	// Print the prompt
	printf("dsh> ");

	// Accept user input
	char *line = (char *)malloc(256); // empty buffer to store the input
	fgets(line, 256, stdin);		  // read up to 256 chars into buffer

	// Print the results
	printf("%s", line);
	return 0;
}
