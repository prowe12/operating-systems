/*
 * histo.c
 *
 *  Created on: Jun 16, 2015
 *      Author: dchiu, prowe
 */

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "stats.h"

/*
 * Print out the values in the histogram, with no formatting
 * @param hist  The histogram
 * @param histLen  The length of the histogram
 */
void printSimpleHistogram(int hist[], int histLen)
{
    printf("The values are: ");
    for (int i = 0; i < histLen; i++)
    {
        printf("%d, ", hist[i]);
    }
    printf("\n");
}

/*
 * Choose which stats to print, based on the input option
 * and call the function to print them
 *
 * @param opt  The option for printing stats
 * @param hist  The histogram
 * @param histLen  The length of the histogram
 */
void printStats(int opt, int hist[], int histLen)
{
    printf("In printStats, with option %d:\n", opt);

    printf("Here is what is currently in the histogram:\n");
    for (int i = 0; i < histLen; i++)
    {
        printf("%d, ", hist[i]);
    }
    printf("\n");
}

// TODO: function definitions for dealing with histogram below

/**
 * Increment the letter counts in histogram
 * @param newstr  The string to add
 * @param hist  The current histogram
 * Notes:
 * For histogram, the elements correspond to:
 * a b c d e f g h i j k l m n o p q r s t u v w x y z
 * Recall that
 */
void incrementHistogram(char newstr[], int hist[])
{
    int num;
    int i;

    // TODO: loop over newstr
    i = 0;
    printf("first letter of string: %c\n", newstr[i]);
    num = newstr[i] - 97;
    printf("Corresponding number: %d\n", num);
}