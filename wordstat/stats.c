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
 * Initialize the histogram by filling with zeros
 * @param hist  The histogram
 * @param histLen  The length of the histogram
 */
void initializeHistogram(int hist[], int histlen)
{
    for (int i = 0; i < histlen; i++)
    {
        hist[i] = 0;
    }
}

/*
 * Print the values in the histogram, with no formatting
 * @param hist  The histogram
 * @param histLen  The length of the histogram
 */
void printSimpleHistogram(int hist[], int histLen)
{
    printf("\nThe histogram is: ");
    for (int i = 0; i < histLen; i++)
    {
        printf("%d, ", hist[i]);
    }
    printf("\n\n");
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

    if (opt == 1)
    {
        printFrequencies(hist);
    }
    else if (opt == 2)
    {
        // TODO: implement option 2
        printHistogram(hist);
    }
}

/**
 * Print the frequencies of the vowels and consonants
 */
void printFrequencies(int hist[])
{
    int nvowel = 0;
    int nconsonant = 0;
    int ivowel[] = {0, 4, 8, 14, 20};
    int iconsonant[] = {1, 2, 3, 5, 6, 7, 9, 10, 11, 12, 13, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25};
    int nivowel = 5;
    int niconsonant = 20;
    int i;
    int j;

    // Get the number of vowels
    for (i = 0; i < nivowel; i++)
    {
        j = ivowel[i];
        nvowel += hist[j];
    }

    // Get the number of consonants
    for (i = 0; i < niconsonant; i++)
    {
        j = iconsonant[i];
        nconsonant += hist[j];
    }
    int ntotal = nvowel + nconsonant;
    float vowelpc = nvowel / (float)ntotal * 100;
    float consonantpc = nconsonant / (float)ntotal * 100;
    printf("\nVowels = %d (%2.2f%%), Consonants = %d (%2.2f%%), Total= %d\n\n", nvowel, vowelpc, nconsonant, consonantpc, ntotal);
}

/**
 * Pretty print the histogram
 * @params hist  The counts of each letter
 */
void printHistogram(int hist[])
{
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetlen = 26;
    int maxcount = 0;

    // Get the maximum occurrences for any letter
    for (int i = 0; i < alphabetlen; i++)
    {
        if (hist[i] > maxcount)
        {
            maxcount = hist[i];
        }
    }

    // Set the spacing
    // TODO: Make this a function
    int nspaces = 1;
    float curr = maxcount;
    while (curr >= 10)
    {
        curr = curr / 10.;
        nspaces++;
    }
    char spaces[] = "           ";
    spaces[nspaces] = '\0';

    // Print the histogram
    printf("\n");
    for (int count = maxcount; maxcount > 0; maxcount--)
    {
        for (int i = 0; i < alphabetlen; i++)
        {
            if (hist[i] >= maxcount)
            {
                printf("*%s", spaces);
            }
            else
            {
                printf(" %s", spaces);
            }
        }
        printf("\n");
    }

    // Print the alphabet
    // TODO Create the string in the above loop, and then just print it here
    for (int i = 0; i < alphabetlen; i++)
    {
        printf("%c%s", alphabet[i], spaces);
        if (hist[i] > maxcount)
        {
            maxcount = hist[i];
        }
    }
    printf("\n");

    // Print the number of occurences of each letter
    // TODO: Handle spacing for frequencies > 9
    for (int i = 0; i < alphabetlen; i++)
    {
        char spaces[] = "           ";
        int nspacesnum = 0;
        float curr = hist[i];
        while (curr >= 10)
        {
            curr = curr / 10.;
            nspacesnum++;
        }
        int nspaceshere = nspaces - nspacesnum;
        spaces[nspaceshere] = '\0';
        printf("%d%s", hist[i], spaces);
    }
    printf("\n");
    printf("\n");
}

/**
 * Increment the letter counts in histogram
 * @param newstr  The string to add
 * @param hist  The current histogram
 * Notes:
 * For histogram, the elements correspond to:
 * a b c d e f g h i j k l m n o p q r s t u v w x y z
 * A B C D E F G H I J K etc
 * Recall that
 */
void incrementHistogram(char newstr[], int hist[], int histlen)
{
    int ihist;
    int i;

    // Loop over the string and if a letter is found,
    // increment the count in histogram
    // TODO: Add capital letters
    i = 0;
    while (newstr[i] != '\0')
    {

        // Get the lowercase
        ihist = newstr[i] - 97;
        if ((ihist >= 0) && (ihist < histlen))
        {
            hist[ihist] += 1;
        }
        else
        {
            // Get the uppercase
            ihist = newstr[i] - 65;
            if ((ihist >= 0) || (ihist < histlen))
            {
                hist[ihist] += 1;
            }
        }
        i++;
    }
}