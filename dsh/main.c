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

/**
 * Split a string into tokens
 * @params str  The string to split
 * @params delim  The delimiter to split on
 * @returns  An array of tokens
 */
char **split(char *str, char *delim)
{
	int CAP = 256;			// Max string length
	char str3[strlen(str)]; // Cannot use strtok with char*

	// Count the number of delimters in str
	int numtokens = 0;
	int i = 0;
	while (str[i])
	{
		str3[i] = str[i];

		if (str[i] == delim[0])
		{
			numtokens++; // Increment for each delimiter
						 // printf("delim: ");
		}
		// printf("%c\n", str[i]);
		i++;
	}
	numtokens++; // There is one more token than there are delimters
	// printf("There are %d tokens\n", numtokens);

	// Create a 2d array of characters: that is, number of pointers to strings
	char **array = (char **)malloc((numtokens + 1) * sizeof(char *));

	// Setup the token
	char *token;
	token = strtok(str3, delim);
	// printf("%s\n", token);

	// Loop through each array element and instantiate an array
	// of capacity cap
	for (int i = 0; i < numtokens; i++)
	{
		array[i] = (char *)malloc(CAP * sizeof(char));
		strcpy(array[i], token);
		token = strtok(NULL, delim); // What is this???
	}
	array[numtokens] = (char *)malloc(CAP * sizeof(char));
	array[numtokens] = NULL;

	return array;
}

/**
 * Print the array
 * @params array  The array
 */
void printarray(char **array)
{

	int i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return;
}

/**
 * Test the split functions
 */
void testSplit()
{
	// char *line = (char *)malloc(256); // empty buffer to store the input
	char *line = "hello there Penny";

	// Tokenize user input
	char **array = split(line, " ");

	// Print the results
	printf("\nBack in testSplit, printing the array again\n");
	printarray(array);
}

int main(int argc, char **argv)
{

	testSplit();

	// TODO: undo following comment
	// char cmdline[MAXBUF]; // stores user input from commmand line

	// Print the prompt
	printf("dsh> ");

	// TODO: Uncomment this line
	// fgets(cmdline, 256, stdin);		  // read up to 256 chars into buffer

	// TODO: Delete this line
	printf("\n");

	// TODO: Uncomment fgets line; delete line =
	// Accept user input
}
