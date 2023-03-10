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

    if ((nvowel < 0) || (nconsonant < 0))
    {
        // TODO: throw an error here
        printf("Number of vowels and consonants must be >= 0\n");
    }
    int ntotal = nvowel + nconsonant;

    // Get the percentages. If ntotal = 0, avoid nan
    float vowelpc;
    float consonantpc;
    if (ntotal == 0)
    {
        vowelpc = 0.;
        consonantpc = 0.;
    }
    else if (ntotal > 0)
    {
        vowelpc = nvowel / (float)ntotal * 100;
        consonantpc = nconsonant / (float)ntotal * 100;
    }
    else
    {
        // TODO: throw an error here
        printf("Error: ntotal should not be < 0!");
    }
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

    // Loop over the string and if a letter is found,
    // increment the count in histogram
    int i = 0;
    while (newstr[i] != '\0')
    {
        // Uppercase: 65 - 91
        // Lowercase 97 - 123
        int iupper = 65;
        int ilower = 97;

        // Get the lowercase
        ihist = newstr[i];

        if ((ihist >= ilower) && (ihist < ilower + histlen))
        {
            hist[ihist - ilower] += 1;
        }
        else if ((ihist >= iupper) && (ihist < iupper + histlen))
        {
            hist[ihist - iupper] += 1;
        }
        i++;
    }
}