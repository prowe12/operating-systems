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

#define HISTORY_LEN 100

/**
 * print the echo
 */
// void printTheEcho(char **array)
// {
//     printf("printTheEcho\n");
//     return;
// }

/**
 * print the history
 * @param array  Array with command and arguments
 */
// void printHistory(char **array)
// {
//     printf("In printHistory\n");
//     return;
// }

/**
 * Change the directory
 * @param array  Array with command and arguments
 */
void changeDir(char **array, int nargs)
{
    // cd with no arguments => cd to home directory
    if (nargs == 0)
    {
        printf("Get home directory from environment and cd to it\n");
        return;
    }

    if (chdir(array[1]) != 0)
        printf("cd: no such file or directory: %s\n", array[1]);
    return;
}

/**
 * Print the current working directory
 */
void printCwd()
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return;
    }
    return;
}

// TODO: write this method
// void executeCmd() {
//     // Full path given
//     if (array[1][1] == '/')
//     {
//         // TODO: implement
//         printf("I have the full path");
//     }
//     else
//     {
//         // TODO: implement
//         printf("Need to find the location of the executable");
//     }
//     return;
// }

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
 * Get the number of tokens in a string (based on delimiter)
 * @params str  The string to split
 * @params delim  The delimiter to split on
 * @returns  The number of tokens
 */
int getNumTokens(char *str, char *delim)
{
    // Count the number of delimiters in str
    int numtokens = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == delim[0])
        {
            numtokens++; // Increment for each delimiter
        }
        i++;
    }
    numtokens++; // There is one more token than there are delimiters

    return numtokens;
}

/**
 * Remove trailing spaces and return from end of input
 */
void cleanup(char str[MAXBUF])
{
    // Check for empty string. This should never happen because user
    // input includes a return character at the end
    if (strlen(str) <= 1)
    {
        str[0] = '\0';
        return;
    }

    // Remove trailing spaces
    int i = strlen(str) - 1; // subtract 1 to get index
    if (str[i - 1] == ' ')
    {
        i--;
        while (str[i] == ' ')
            i--;
        i++;
    }
    str[i] = '\0'; // Put null at end of string
    return;
}

/**
 * Split a string into tokens
 * @params str  The string to split
 * @params delim  The delimiter to split on
 * @returns  An array of tokens
 */
char **split(char *str, char *delim, int numtokens)
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
        char **array = (char **)malloc(sizeof(char *));
        array[0] = NULL;
        return array;
    }

    // // Count the number of delimiters in str int numtokens = 0;
    // int i = 0;
    // int numtokens = 0;
    // while (str[i] != '\0')
    // {
    //     if (str[i] == delim[0])
    //     {
    //         numtokens++; // Increment for each delimiter
    //     }
    //     i++;
    // }

    // printf("The previous character is [%c]\n", str[i - 1]);
    // printf("The final character is [%c]\n", str[i]);
    // printf("numtokens: %d\n", numtokens);

    // // TODO: do we need this?
    // printf("numtokens:%d\n", numtokens);
    // printf("i: %d\n", i);
    // printf("strlen(str)%ld\n", strlen(str));
    // str[i] = '\0'; // Set the end of the string

    // Create a 2d array of characters: that is, number of pointers to strings
    char **array = (char **)malloc((numtokens + 1) * sizeof(char *));

    // Setup the token
    char *token;

    // str is searched until the delimiter is found. The first token is
    // returned and the variable assigned the result points to that token (string)
    token = strtok(str, delim);
    int i = 0;
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

    array[numtokens] = (char *)malloc(sizeof(char));
    array[numtokens] = NULL;

    // Set nargs because it's useful to have
    // *nargs = numtokens - 1;

    return array;
}
