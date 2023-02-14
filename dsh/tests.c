/*
 * tests.c
 *
 *  Created on: Feb. 13, 2023
 *      Author: Penny
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dsh.h"

/*
 * Concatenates input strings into a single string.
 * Returns the pointer to the resulting string.
 * The string memory is allocated with malloc(),
 * so the caller must release it using free().
 * The input string array must have NULL as last element.
 * If the input string array pointer is NULL,
 * NULL is returned.
 * On memory allocation error, NULL is returned.
 * From https://stackoverflow.com/questions/23130203/create-string-from-array-of-strings-in-c
 */
char *getArrayAsStr(char **strings)
{
    int i = 0;           /* Loop index               */
    int count = 0;       /* Count of input strings   */
    char *result = NULL; /* Result string            */
    int totalLength = 0; /* Length of result string  */

    /* Check special case of NULL input pointer. */
    if (strings == NULL)
    {
        return NULL;
    }

    /*
     * Iterate through the input string array,
     * calculating total required length for destination string.
     * Get the total string count, too.
     */
    while (strings[i] != NULL)
    {
        totalLength += strlen(strings[i]);
        i++;
    }
    count = i;
    totalLength++; /* Consider NUL terminator. */

    /*
     * Allocate memory for the destination string.
     */
    result = malloc(sizeof(char) * totalLength);
    if (result == NULL)
    {
        /* Memory allocation failed. */
        return NULL;
    }

    /*
     * Concatenate the input strings.
     */
    for (i = 0; i < count; i++)
    {
        strcat(result, strings[i]);
        if (i < count - 1)
            strcat(result, " ");
        else
            strcat(result, "\n");
    }

    return result;
}

/**
 * Test the split functions
 */
void testSplitSimple()
{
    // Setup
    // Sample input line
    char line[256] = "hello there Penny\n";

    // Run
    // Tokenize user input
    char **array = split(line, " ");
    // Get the results
    char *outstr = getArrayAsStr(array);

    // Assert
    assert(strcmp(outstr, "hello there Penny\n") == 0);
}

/**
 * Test the split functions
 */
void testSplitDot()
{
    // Sample input line
    char line[256] = "git add .\n";

    // Tokenize user input
    char **array = split(line, " ");

    // Get the results
    char *outstr = getArrayAsStr(array);

    // Assert
    assert(strcmp(outstr, "git add .\n") == 0);
}

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
    testSplitSimple();
    testSplitDot();
    return 0;
}