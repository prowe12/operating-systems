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
 * @param nargs  Number of arguments
 */
void changeDir(char **array, int nargs)
{
    if (nargs > 1)
    {
        printf("cd: too many arguments");
        return;
    }

    // cd with no arguments => cd to home directory
    char *direc;
    if (nargs == 0)
    {
        printf("Get home directory from HOME variable in environment and cd to it\n");
        direc = getenv("HOME");
        printf("directory: %s\n", direc);
    }
    else
        direc = array[1];

    if (chdir(direc) != 0)
        printf("cd: no such file or directory: %s\n", array[1]);
    return;
}

/**
 * Print the current working directory
 */
void printCwd(int nargs)
{
    if (nargs > 0)
    {
        printf("pwd: too many arguments\n");
        return;
    }

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

int executeCmd(char **array)
{
    // TODO: Work on command execution when given the full path to an executable. (Mode 1)
    // TODO: Finally, work on execution when given just the name of an executable. (Mode 2)

    printf("array[1][0] [%c]\n", array[0][0]);
    int status;

    if (array[0][0] == '/')
    {
        // Full path given
        printf("I have the full path\n");

        // Check if the path exists
        if (access(array[0], F_OK | X_OK) != 0)
        {
            printf("dsh: no such file or directory: %s\n", array[0]);
            return 1;
        }

        printf("File exists and is executable! Can run!\n");

        int child_pid = fork();
        printf("The child pid is %d\n", child_pid);

        if (child_pid == 0)
        {
            printf("Child process: Run the exec, then quit\n");
            status = execv(array[0], array);

            if (status == -1)
                printf("Problem with command");
            return child_pid;
        }
        else
        {
            printf("Parent process: Wait for child then keep going\n");
            wait(NULL);
            return child_pid;
        }
    }

    else
    {
        // TODO: implement
        printf("Need to find the location of the executable\n");
    }
    return 1;
}

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
 * Remove trailing return and leading and trailing spaces
 * @param str  The original string
 * @param str1  The final string
 * Note: Code for removal of leading spaces from
 * https://www.geeksforgeeks.org/c-program-to-trim-leading-white-spaces-from-string/
 */
void cleanup(char str[MAXBUF], char str1[MAXBUF])
{
    // Check for empty string. This should never happen because user
    // input includes a return character at the end
    if (strlen(str) <= 1)
    {
        str[0] = '\0';
        return;
    }

    // Remove final return and trailing spaces
    int i = strlen(str) - 1; // subtract 1 to get index
    if (str[i - 1] == ' ')
    {
        i--;
        while (str[i] == ' ')
            i--;
        i++;
    }
    str[i] = '\0'; // Put null at end of string

    // Remove preceding spaces
    int idx = 0, j, k = 0;
    while (str[idx] == ' ' || str[idx] == 't')
    {
        idx++;
    }

    for (j = idx; str[j] != '\0'; j++)
    {
        str1[k] = str[j];
        k++;
    }
    str1[k] = '\0';

    return;
}

/**
 * Split a string into tokens
 * @params str  The string to split
 * @params delim  The delimiter to split on
 * @params numtokens  The number of tokens
 * @returns  An array of tokens
 */
char **split(char *str, char *delim, int numtokens)
{
    // Check for NULL pointer
    // TODO: what is the use case?  How do I test this?
    if (str == NULL)
        return NULL;

    // Check for empty string. The string has been cleaned and so should
    // contain only the command and arguments
    if (strlen(str) <= 0)
    {
        char **array = (char **)malloc(sizeof(char *));
        array[0] = NULL;
        return array;
    }

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

    return array;
}
