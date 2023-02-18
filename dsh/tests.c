/*
 * tests.c
 *
 *  Created on: Feb. 13, 2023
 *      Author: Penny
 *
 * Note:
 * valgrind --leak-check=full ./memtest
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dsh.h"

/**
 * Helper function:
 * Appends input strings into a single string.
 * @params strings  The array of strings
 * @params outstr  The appended string
 */
void getArrayAsStr(char **strings, char outstr[])
{
    /* Check special case of NULL input pointer. */
    if (strings == NULL)
        return;

    int i = 0;

    // Reinitialize and build up the string
    strcpy(outstr, "");
    while (strings[i] != NULL)
    {
        strcat(outstr, strings[i]);
        strcat(outstr, " ");
        i++;
    }

    // Remove final space
    outstr[strlen(outstr) - 1] = '\0';
    return;
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
    char outstr[256];
    getArrayAsStr(array, outstr);
    free(array);

    // Assert
    assert(strcmp(outstr, "hello there Penny") == 0);
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
    char outstr[256];
    getArrayAsStr(array, outstr);
    free(array);

    // Assert
    assert(strcmp(outstr, "git add .") == 0);
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
    char outstr[256];
    getArrayAsStr(array, outstr);

    // Assert
    assert(strcmp(outstr, "") == 0);
    // free(outstr);
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
    char outstr[256];
    getArrayAsStr(array, outstr);

    // Assert
    assert(strcmp(outstr, "") == 0);
    free(array);
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

void testFree()
{
    int i = 0;
    char **array = (char **)malloc((256 + 1) * sizeof(char *));
    array[i] = (char *)malloc((256 + 1) * sizeof(char));
    free(array[0]);
    free(array);
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    testFree();
    testPath();
    testSplitSimple(); // malloc(): invalid size (unsorted)
    testSplitDot();    // tests: tests.c:115: testSplitDot: Assertion `strcmp(outstr, "git add .\n") == 0' failed.
    testEmptyString(); // tests: tests.c:135: testEmptyString: Assertion `strcmp(outstr, "") == 0' failed.
    testReturnOnly();  // tests: tests.c:155: testReturnOnly: Assertion `strcmp(outstr, "") == 0' failed.

    return 0;
}