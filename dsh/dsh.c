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
    // otherwise cd to path given
    char *direc;
    if (nargs == 0)
        direc = getenv("HOME");
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
        printf("%s\n", cwd);
    else
    {
        perror("getcwd() error");
        return;
    }
    return;
}

/**
 * Given the full path, execute the command
 * @param array  The array holding the command and arguments
 * @returns  0 for child pid, other for parent
 */
int executeCmd(char **array)
{
    // Full path given; check if the path exists
    if (access(array[0], F_OK | X_OK) != 0)
    {
        printf("dsh: no such file or directory: %s\n", array[0]);
        return 1;
    }

    int child_pid = fork();
    if (child_pid == 0)
    {
        int status = execv(array[0], array);
        if (status == -1)
            printf("Problem with command");
        return child_pid;
    }
    else
    {
        wait(NULL);
        return child_pid;
    }
    return 1;
}

/**
 * Use or build path to execute the command
 * @param array  The array holding the command and arguments
 * @returns  0 for child pid, other for parent
 */
int buildPathAndExecuteCmd(char **array)
{

    if (array[0][0] == '/')
    {
        int child_pid = executeCmd(array);
        return child_pid;
    }
    else
    {
        char cwd[MAXBUF];
        // First try the working directory
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            int numtokens;
            strcat(cwd, "/");
            strcat(cwd, array[0]);
            if (access(cwd, F_OK | X_OK) != 0)
            {
                // Try the other paths. Note that we have to copy path,
                // because it will be modified (which would then modify PATH)
                char path[MAXBUF];
                strcpy(path, getenv("PATH"));
                numtokens = getNumTokens(path, ":");

                // Build an array containing the paths.  Then test each path
                // one-by-one to see if the command is in it.
                char **paths = split(path, ":", numtokens);
                for (int i = 0; i < numtokens; i++)
                {
                    cwd[0] = '\0';
                    strcat(cwd, paths[i]);
                    strcat(cwd, "/");
                    strcat(cwd, array[0]);
                    if (access(cwd, F_OK | X_OK) == 0)
                    {
                        // Free up the mallocd space on the heap before leaving
                        freearray(paths);
                        strcpy(array[0], cwd);
                        int child_pid = executeCmd(array);
                        return child_pid;
                    }
                }
                freearray(paths); // If we get here, we haven't freed the array yet!

                // No paths worked, so the command is not found
                printf("ERROR: %s not found!\n", array[0]);
            }
        }
        else
        {
            perror("getcwd() error");
            return 1;
        }
    }
    return 1;
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
    char tempstr[MAXBUF];
    strcpy(tempstr, str);

    // Remove final return and trailing spaces
    int i = strlen(tempstr) - 1; // subtract 1 to get index
    while (i >= 0 && tempstr[i] == ' ')
        i--;
    tempstr[i] = '\0'; // Put null at end of string

    if (strlen(tempstr) < 1)
    {
        strcpy(str1, "\0");
        return;
    }

    // Remove preceding spaces
    int idx = 0, j, k = 0;
    while (tempstr[idx] == ' ' || tempstr[idx] == '\t')
    {
        idx++;
    }

    for (j = idx; tempstr[j] != '\0'; j++)
    {
        str1[k] = tempstr[j];
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
    // TODO: fix this
    char **array = (char **)malloc(256 * (numtokens + 1) * sizeof(char *));

    // Setup the token
    char *token;

    // str is searched until the delimiter is found. The first token is
    // returned and the variable assigned the result points to that token (string)
    token = strtok(str, delim);

    // Loop through each array element and instantiate an array
    // of capacity cap
    for (int i = 0; i < numtokens; i++)
    {
        // TODO: fix following
        array[i] = (char *)malloc((256 + 1) * sizeof(char));
        strcpy(array[i], token);

        // strtok maintains a static pointer to the previously passed string.
        // Thus to get the next token for the same string, NULL is passed as
        // the first argument.
        token = strtok(NULL, delim);
    }

    array[numtokens] = NULL;

    return array;
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
 * Frees up the array
 * @param array  The array
 */
void freearray(char **array)
{

    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
    return;
}
