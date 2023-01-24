/*
 * main.c
 *
 *  Created on: Jun 15, 2015
 *      Author: dchiu, prowe
 */
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "stats.h"
#include "menu.h"
#define MAXSTRLEN 128

/**
 * Get strings from user and increment histogram
 * @param  The starting histogram (counts per letter)
 */
void inputStrings(int histogram[])
{
	char buf[MAXSTRLEN] = "";

	printf("Enter strings (# to stop):\n");
	while (strcmp(buf, "#\n") != 0)
	{
		// Get the string input by the user
		fgets(buf, MAXSTRLEN, stdin);

		// Increment letters in histogram
		incrementHistogram(buf, histogram, ALPHABET_SIZE);
	}
}

/**
 * @brief Main function
 *
 * @param argc Ignore
 * @param argv Ignore
 * @return int
 */
int main(int argc, char *argv[])
{

	// Declare and initialize the histogram
	int histogram[ALPHABET_SIZE];
	initializeHistogram(histogram, ALPHABET_SIZE);

	// Only repeat this a maximum of maxrepeats times
	int maxrepeats = 1000;
	int count = 0;
	int opt = 3;
	while (count < maxrepeats)
	{
		count++;

		if ((opt == 1) || (opt == 2))
		{
			printStats(opt, histogram, ALPHABET_SIZE);
		}
		else if (opt == 3)
		{
			inputStrings(histogram);
		}
		else if (opt == 4)
		{
			printf("Exiting...\n");
			return 0;
		}
		else
		{
			printf("Unexpected result.");
		}
		opt = getMenuOption();
	}

	printf("Please try again (the menu repeats a maximum of %d times)\n", maxrepeats);
	return 0;
}
