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
#include <limits.h>
#include "ls2.h"

// #include <unistd.h>
#include <errno.h>

// TODO: function definitions here for ls2

/**
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

int pushToStack(stack_t *s, char *fname, char *topdir, int depth)
{
    int keepitem = 1;
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

            // keepitem = keepifmatch();
            int keepFile = 0;
            if ((fname == NULL) || (strcmp(path->d_name, fname) == 0))
            {
                keepFile = 1;
                keepDir = 1;
            }

            // Get file size in bytes and convert to string
            off_t filesizelu = buf.st_size;
            // TODO: malloc this?
            char filesize[50];
            snprintf(filesize, 50, "%lu", filesizelu);

            int flen = 4 * depth + strlen(path->d_name) + strlen(filesize) + strlen(" (bytes)") + 1;

            char *tempstr = (char *)malloc(sizeof(char) * flen);
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
            int keepDir = pushToStack(s, fname, path->d_name, depth + 1);
            printf("On directory: %s with keepitem = %d\n", path->d_name, keepitem);

            // Get the file size
            int flen = 4 * depth + strlen(path->d_name) + strlen(" (directory)") + 1;

            // Set this element of the array
            char *tempstr = (char *)malloc(sizeof(char) * flen);
            tempstr[0] = '\0';

            // Add the appropriate number of sets of four spaces
            for (int i = 0; i < depth; i++)
            {
                strcat(tempstr, spaces);
            }
            strcat(tempstr, path->d_name);
            strcat(tempstr, " (directory)");

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

// int keepifmatch(char* fname1, char* fname2) {
//      (strcmp(path->d_name, fname) == 0)
// }

// paths = ls(path);
// nfiles = length(paths);

// TODO: Loop over the path contents and see what the file type is ('.', dir, file, link, etc)
// for (i = 0; i < nfiles; i++)
// {
// 	path = paths[i];
// 	filetype = getFileType(path);
// 	// ((path[0] == '.') || (filetype == 'link'))

// 	// If it is a directory, add it and go into it
// 	if (filetype == 'dir')
// 	{
// 		push(s, "path");
// 		// TODO: Go into it
// 	}
// 	else if (filetype == 'file')
// 	{
// 		if (getall)
// 		{
// 			push(s, path);
// 		}
// 		else if (strcmp(path, fname))
// 		{
// 			push(s, path);
// 			free(fname);
// 			fname = NULL;
// 		}
// 	}

// int pushToStackFile(stack_t *s, char *fname, char *topdir, char **dirArray, int depth, int iarray)
// {
//     char *spaces = "    ";
//     DIR *dirStruct = getdir(topdir);
//     errno = 0;
//     struct dirent *path;
//     struct stat buf;
//     int pathstat;

//     // We only have the relative paths, so we need to change into the top directory first.
//     // printf("%s: \n", topdir);
//     chdir(topdir);

//     // readdir returns a pointer to dirStruct representing the next directory entry.
//     // When it gets to the end, it returns NULL.
//     while ((path = readdir(dirStruct)) != NULL)
//     {
//         // printf("%s: \n", topdir);
//         // chdir(topdir);
//         // printCwd();
//         pathstat = lstat(path->d_name, &buf);

//         if ((pathstat != 0) || (strcmp(path->d_name, ".") == 0) || (strcmp(path->d_name, "..") == 0))
//         {
//             // printf("status=%d, path=%s, skip\n", pathstat, path->d_name);
//             continue;
//         }
//         else if ((S_ISREG(buf.st_mode)) && (strcmp(path->d_name, fname) == 0))
//         {
//             printf("status=%d, path=%s, regular file, ADD\n", pathstat, path->d_name);

//             // Get file size in bytes and convert to string
//             off_t filesizelu = buf.st_size;
//             // printf("%s size: %ld\n", path->d_name, filesize);
//             // TODO: malloc this?
//             char filesize[50];
//             snprintf(filesize, 50, "%lu", filesizelu);
//             // printf("%s size: %s\n", path->d_name, filesizestr);

//             int flen = 4 * depth + strlen(path->d_name) + strlen(filesize) + strlen(" (bytes)") + 1;

//             // Set this element of the array
//             dirArray[iarray] = (char *)malloc(sizeof(char) * flen);
//             dirArray[iarray][0] = '\0';
//             // Add the appropriate number of sets of four spaces
//             for (int i = 0; i < depth; i++)
//             {
//                 strcat(dirArray[iarray], spaces);
//             }
//             strcat(dirArray[iarray], path->d_name);
//             strcat(dirArray[iarray], " (");
//             strcat(dirArray[iarray], filesize);
//             strcat(dirArray[iarray], " bytes)");

//             printf("iarray: %d\n", iarray);
//             push(s, dirArray[iarray]);
//             iarray += 1;
//         }
//         else if (S_ISDIR(buf.st_mode))
//         {
//             printf("status=%d, path=%s, directory, recurse\n", pathstat, path->d_name);

//             // Recurse on directory
//             iarray = pushToStackFile(s, fname, path->d_name, dirArray, depth + 1, iarray);

//             // Get the file size
//             int flen = 4 * depth + strlen(path->d_name) + strlen(" (directory)") + 1;

//             // Set this element of the array
//             dirArray[iarray] = (char *)malloc(sizeof(char) * flen);
//             dirArray[iarray][0] = '\0';
//             // Add the appropriate number of sets of four spaces
//             for (int i = 0; i < depth; i++)
//             {
//                 strcat(dirArray[iarray], spaces);
//             }
//             strcat(dirArray[iarray], path->d_name);
//             strcat(dirArray[iarray], " (directory)");

//             // char *stringForStack = path->d_name;
//             // strcat(stringForStack, "/ (directory)");
//             // printf("back to directory %s\n", topdir);
//             chdir("../");
//             // printf("status=%d, path=%s, ADD\n", pathstat, path->d_name);

//             printf("iarray: %d\n", iarray);
//             push(s, dirArray[iarray]);
//             iarray += 1;
//         }
//         else if (S_ISREG(buf.st_mode))
//             ;
//         else
//             printf("Error: unexpected value for status of %s", path->d_name);
//     }

//     return iarray;
// }
