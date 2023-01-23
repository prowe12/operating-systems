/*
 * menu.c
 *
 *  Created on: Jun 16, 2015
 *      Author: dchiu, prowe
 */

#include <stdio.h>
#include <string.h>
#include "menu.h"
#define MAXINPLEN 128

/**
 * Parse a string containing 1-4 into an integer,
 * or return 5-9 if the string contains anything else
 * @param intAsStr  The string containing the integer
 * @returns  The integer
 */
int parseInt(char *intAsStr)
{
	if ((strcmp(intAsStr, "0\n") >= 1) && (strcmp(intAsStr, "1\n") <= 4))
	{
		int thisint = intAsStr[0];
		return thisint - 48;
	}
	printf("Error: Unknown option %s\n", intAsStr);
	return 9;
}

/**
 * Print the menu and input user choice
 * @returns  The user input
 */
int getMenuOption()
{
	int opt;
	char optstr[MAXINPLEN] = "";

	int MENU_STATS = 1;
	int MENU_HISTO = 2;
	int MENU_INPUT = 3;
	int MENU_EXIT = 4;

	printf("*** WORD STATS MENU ***\n");
	printf("Enter %d to print vowel and consonant frequency.\n", MENU_STATS);
	printf("Enter %d to print histogram.\n", MENU_HISTO);
	printf("Enter %d to return to inputting more strings.\n", MENU_INPUT);
	printf("Enter %d to quit.\n", MENU_EXIT);

	// If user enters a character, this breaks:
	// scanf("%d%*c", &opt);

	// So use this instead
	fgets(optstr, MAXINPLEN, stdin);
	opt = parseInt(optstr);

	return opt;
}
