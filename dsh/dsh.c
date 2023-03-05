/*
 * dsh.c
 *
 *   Created on: Aug 2, 2013
 *      Authors: chiu and Penny Rowe
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
#include "stringmanager.h"

/**
 * Change the directory
 * @param array  Array with command and arguments
 * @param nargs  Number of arguments
 */
void changeDir(char **array, int nargs)
{
    if (nargs > 1)
    {
        printf("cd: too many arguments\n");
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
 * @param hasAmp  Whether to wait for child to finish
 * @returns  0 for child pid, other for parent
 */
int executeCmd(char **array, int hasAmp)
{
    // Full path given; check if the path exists
    if (access(array[0], F_OK | X_OK) != 0)
    {
        printf("dsh: no such file or directory: %s\n", array[0]);
        return 1;
    }

    int child_pid = fork();
    if (child_pid != 0)
    {
        // parent
        if (!hasAmp)
            wait(NULL);
        return child_pid;
    }
    else
    {
        // child - run command
        int status = execv(array[0], array);
        if (status == -1)
            printf("Problem with command");
        return child_pid;
    }
    return 1;
}

/**
 * Use or build path to execute the command
 * @param array  The array holding the command and arguments
 * @returns  0 for child pid, other for parent
 */
int buildPathAndExecuteCmd(char **array, int nargs, int hasAmp)
{

    if (array[0][0] == '/')
    {
        int child_pid = executeCmd(array, hasAmp);
        return child_pid;
    }
    else
    {
        int numtokens;
        char cwd[MAXBUF];
        // First try the working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd() error");
            return 1;
        }

        // Build the path to the file to run from the working dir
        strcat(cwd, "/");
        strcat(cwd, array[0]);

        // If the path exists and is executable, run it
        if (access(cwd, F_OK | X_OK) == 0)
        {
            strcpy(array[0], cwd);
            int child_pid = executeCmd(array, hasAmp);
            return child_pid;
        }
        else
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
                    int child_pid = executeCmd(array, hasAmp);
                    return child_pid;
                }
            }
            freearray(paths); // If we get here, we haven't freed the array yet!

            // No paths worked, so the command is not found or did not work
            printf("ERROR: %s not found or is not executable!\n", array[0]);
        }
    }
    return 1;
}
