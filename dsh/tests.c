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

/**
 * Helper function:
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
 * Test the split functions on a simple case
 */
void testSplitSimple()
{
    // Setup
    // Sample input line
    char line[256] = "hello there Penny";

    // Run
    // Tokenize user input
    char **array = split(line, " ", 3);
    // Get the results
    char *outstr = getArrayAsStr(array);

    // Assert
    assert(strcmp(outstr, "hello there Penny\n") == 0);
    free(outstr);
    return;
}

/**
 * Test the split functions on a case with a '.'
 */
void testSplitDot()
{
    // Sample input line
    char line[256] = "git add .";

    // Tokenize user input
    char **array = split(line, " ", 3);

    // Get the results
    char *outstr = getArrayAsStr(array);

    // Assert
    assert(strcmp(outstr, "git add .\n") == 0);
    free(outstr);
    return;
}

/**
 * Test the split functions on an empty string
 */
void testEmptyString()
{
    // Sample input line
    char line[256] = "";

    // Tokenize user input
    char **array = split(line, " ", 0);

    // Get the results
    char *outstr = getArrayAsStr(array);

    // // Assert
    assert(strcmp(outstr, "") == 0);
    free(outstr);
    return;
}

/**
 * Test the split functions on an empty string
 */
void testReturnOnly()
{
    // Sample input line
    char line[256] = "\n";

    // Tokenize user input
    char **array = split(line, " ", 0);

    // Get the results
    char *outstr = getArrayAsStr(array);

    // // Assert
    assert(strcmp(outstr, "") == 0);
    free(outstr);
    return;
}

void testPath()
{
    char originalPath[256];
    strcpy(originalPath, getenv("PATH"));

    // Note: split modifies the string, which then changes PATH
    // Uncomment the following to see this
    // char *changingPath = getenv("PATH"); // path and PATH are now linked!
    // printf("Path: %s\n", changingPath);
    // int numtokens = getNumTokens(changingPath, ":");
    // printf("Path after getting numtokens: %s\n", changingPath);
    // split(changingPath, ":", numtokens); // Changes path, and thus PATH
    // printf("Path after split: %s\n", changingPath);
    // printf("PATH after split: %s\n", getenv("PATH"));

    // Split modifies the string, which then changes PATH, so make a copy first
    char path[256];
    strcpy(path, getenv("PATH"));
    // printf("Path: %s\n", path);
    int numtokens = getNumTokens(path, ":");
    // printf("numtokens: %d\n", numtokens);
    // printf("Path after getting numtokens: %s\n", path);
    split(path, ":", numtokens);
    // printf("Path after split: %s\n", path);
    // printf("PATH after split: %s\n", getenv("PATH"));
    assert(strcmp(getenv("PATH"), originalPath) == 0);
}

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
    testPath();

    // testSplitSimple();
    // testSplitDot();
    // testEmptyString();
    // testReturnOnly();

    return 0;
}