/*
 * ls2.c
 *
 *  Created on: Feb. 4, 2023
 *      Author: Penny Rowe
 *
 */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "ls2.h"

/**
 * Return the directory structure for a given path
 * @param *path a pointer to the path name
 * @returns A directory structure for the path
 * Notes:
 * From https://www.delftstack.com/howto/c/opendir-in-c/
 */
DIR *getdir(char *path)
{
    DIR *dirStruct;

    errno = 0;

    // opendir returns a DIR* structure or NULL if it encounters an error
    if ((dirStruct = opendir(path)) == NULL)
    {
        switch (errno)
        {
        case EACCES:
            printf("Permission denied for directory %s\n", path);
            break;
        case ENOTDIR:
            printf("'%s' is not a directory\n", path);
            break;
        case ENOENT:
            printf("Directory \"%s\" does not exist\n", path);
            break;
        }
        free(dirStruct);
        exit(EXIT_FAILURE);
    }
    return dirStruct;
}

/**
 * Helper function for printing the current working directory
 */
int printCwd()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

/**
 * Traverse the directory tree and push each directory and filename to the stack.
 * If fname is not NULL then only push files named fname, and only push directories
 * that contain fname within or in a subdirectory
 * @param s  The stack to save the name to
 * @param fname  The filename, or NULL if not used
 * @param topdir  The parent directory
 * @param depth  The depth down the tree (controls the appended spaces)
 */
int pushToStack(stack_t *s, char *fname, char *topdir, int depth)
{
    char *spaces = "    ";
    DIR *dirStruct = getdir(topdir);
    errno = 0;
    struct dirent *path;
    struct stat buf;
    int pathstat;

    // We only have the relative paths, so we need to change into the top directory first.
    chdir(topdir);

    // readdir returns a pointer to dirStruct representing the next directory entry.
    // When it gets to the end, it returns NULL.
    int keepDir = 0;
    while ((path = readdir(dirStruct)) != NULL)
    {
        pathstat = lstat(path->d_name, &buf);

        if ((pathstat != 0) || (strcmp(path->d_name, ".") == 0) || (strcmp(path->d_name, "..") == 0))
        {
            continue;
        }
        else if (S_ISREG(buf.st_mode))
        {
            int keepFile = 0;
            if ((fname == NULL) || (strcmp(path->d_name, fname) == 0))
            {
                keepFile = 1;
                keepDir = 1;
            }

            // Get file size in bytes and convert to string
            off_t filesizelu = buf.st_size;
            char filesize[50];
            snprintf(filesize, 50, "%lu", filesizelu);

            int flen = 4 * depth + strlen(path->d_name) + strlen(filesize) + strlen(" (bytes)") + 1;

            char *tempstr = (char *)malloc(sizeof(char) * flen + 265);
            tempstr[0] = '\0';

            // Add the appropriate number of sets of four spaces
            for (int i = 0; i < depth; i++)
            {
                strcat(tempstr, spaces);
            }
            strcat(tempstr, path->d_name);
            strcat(tempstr, " (");
            strcat(tempstr, filesize);
            strcat(tempstr, " bytes)");

            if (keepFile == 1)
                push(s, tempstr);
        }
        else if (S_ISDIR(buf.st_mode))
        {
            // Recurse through the directories, returning whether to save
            int keepDir = pushToStack(s, fname, path->d_name, depth + 1);

            // Get the file size and set this element of the array
            int flen = 4 * depth + strlen(path->d_name) + strlen("/ (directory)") + 1;
            char *tempstr = (char *)malloc(sizeof(char) * flen);
            tempstr[0] = '\0';

            // Add the appropriate number of sets of four spaces
            for (int i = 0; i < depth; i++)
            {
                strcat(tempstr, spaces);
            }
            strcat(tempstr, path->d_name);
            strcat(tempstr, "/ (directory)");

            chdir("../");
            if ((keepDir == 1) || (fname == NULL))
                push(s, tempstr);
        }
        else
        {
            printf("Error: unexpected value for status of %s", path->d_name);
        }
    }

    return keepDir;
}
