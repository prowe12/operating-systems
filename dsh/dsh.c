/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"

/**
 * Print the array
 * @params array  The array
 */
void printarray(char **array)
{

    int i = 0;
    while (array[i])
    {
        printf("%s\n", array[i]);
        i++;
    }
    return;
}

/**
 * Split a string into tokens
 * @params str  The string to split
 * @params delim  The delimiter to split on
 * @returns  An array of tokens
 */
char **split(char *str, char *delim)
{
    // Check for NULL pointer
    // TODO: what is the use case?  How do I test this?
    if (str == NULL)
    {
        return NULL;
    }

    // Check for empty string. This should never happen because user
    // input includes a return character at the end
    if (strlen(str) <= 1)
    {
        char **array = (char **)malloc((1) * sizeof(char *));
        array[0] = NULL;
        return array;
    }

    // Count the number of delimiters in str
    int numtokens = 0;
    int i = 0;
    while (str[i] != '\n')
    {
        if (str[i] == delim[0])
        {
            numtokens++; // Increment for each delimiter
        }
        i++;
    }
    str[i] = '\0'; // Set the end of the string
    numtokens++;   // There is one more token than there are delimiters

    // Create a 2d array of characters: that is, number of pointers to strings
    char **array = (char **)malloc((numtokens + 1) * sizeof(char *));

    // Setup the token
    char *token;

    // str is searched until the delimiter is found. The first token is
    // returned and the variable assigned the result points to that token (string)
    token = strtok(str, delim);
    i = 0;
    array[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
    strcpy(array[i], token);

    // Loop through each array element and instantiate an array
    // of capacity cap
    for (int i = 0; i < numtokens; i++)
    {
        array[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(array[i], token);

        // strtok maintains a static pointer to the previously passed string.
        // Thus to get the next token for the same string, NULL is passed as
        // the first argument.
        token = strtok(NULL, delim);
    }

    array[numtokens] = (char *)malloc(1 * sizeof(char));
    array[numtokens] = NULL;

    return array;
}
