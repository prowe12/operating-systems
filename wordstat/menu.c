/*
 * menu.c
 *
 *  Created on: Jun 16, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include "menu.h"

int getMenuOption()
{
	int opt;
	int MENU_STATS = 1;
	int MENU_HISTO = 2;
	int MENU_INPUT = 3;
	int MENU_EXIT = 4;

	printf("*** WORD STATS MENU ***\n");
	printf("Enter %d to print vowel and consonant frequency.\n", MENU_STATS);
	printf("Enter %d to print histogram.\n", MENU_HISTO);
	printf("Enter %d to return to inputting more strings.\n", MENU_INPUT);
	printf("Enter %d to quit.\n", MENU_EXIT);
	scanf("%d", &opt);
	return opt;
}
