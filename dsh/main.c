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
	// Count the number of delimters in str
	int numtokens = 0;
	int i = 0;
	while (str[i] != '\n')
	{
		if (str[i] == delim[0])
		{
			numtokens++; // Increment for each delimiter
		}
		printf("%c\n", str[i]);
		i++;
	}
	str[i] = '\0'; // Set the end of the string
	numtokens++;   // There is one more token than there are delimters

	// Create a 2d array of characters: that is, number of pointers to strings
	char **array = (char **)malloc((numtokens + 1) * sizeof(char *));

	// Setup the token
	char *token;

	// str is searched until the delimiter is found. The first token is
	// returned and the variable assigned the result points to that token (string)
	token = strtok(str, delim);

	// Loop through each array element and instantiate an array
	// of capacity cap
	printf("number of tokens: %d\n", numtokens);
	for (int i = 0; i < numtokens; i++)
	{
		array[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(array[i], token);

		// strtok maintains a static pointer to the previously passed string.
		// Thus to get the next token for the same string, NULL is passed as
		// the first argument.
		token = strtok(NULL, delim);
	}

	array[numtokens] = (char *)malloc(1 * sizeof(char));
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
	// Sample input line
	char line[MAXBUF] = "hello there Penny\n";
	// char *line = "hello there Penny and Ben\n";
	printf("length of line %ld\n", strlen(line));

	// Tokenize user input
	char **array = split(line, " ");

	// Print the results
	printf("\nBack in testSplit, printing the array again\n");
	printarray(array);

	// Sample input line
	char line2[MAXBUF] = "git add .\n";

	// Tokenize user input
	array = split(line2, " ");

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
