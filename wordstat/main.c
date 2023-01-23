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
 * @brief Main function
 *
 * @param argc Ignore
 * @param argv Ignore
 * @return int
 */
int main(int argc, char *argv[])
{
	char buf[MAXSTRLEN] = "";

	// declare and initialize the histogram
	int histogram[ALPHABET_SIZE];
	initializeHistogram(histogram, ALPHABET_SIZE);
	printSimpleHistogram(histogram, ALPHABET_SIZE);

	// TODO: start by getting strings from users until # is input
	printf("Enter strings (# to stop):\n");
	while (strcmp(buf, "#\n") != 0)
	{
		// Get the string input by the user
		fgets(buf, MAXSTRLEN, stdin);
		printf("string is: %s\n", buf);

		// Increment letters in histogram
		incrementHistogram(buf, histogram, ALPHABET_SIZE);
		printSimpleHistogram(histogram, ALPHABET_SIZE);
	}

	// TODO: after # is input, print menu options
	// Only repeat this a maximum of maxrepeats times
	int maxrepeats = 1000;
	int count = 0;
	int opt;
	while (count < maxrepeats)
	{
		count++;
		opt = getMenuOption();

		// TODO: Print stats based on user input
		if ((opt == 1) || (opt == 2))
		{
			printStats(opt, histogram, ALPHABET_SIZE);
		}
		else if (opt == 3)
		{
			printf("return to inputting more strings");
			// TODO: concatenate letters with getstrings() result
			// int letters[] = getstrings();
		}
		else if (opt == 4)
		{
			printf("quitting");
			return 0;
		}
	}

	printf("Please try again (the menu repeats a maximum of %d times)\n", maxrepeats);
	return 0;
}
