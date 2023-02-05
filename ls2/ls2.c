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

void pushToStackForFile(stack_t *s, DIR *dirStruct, char *fname)
{
    return;
}

void pushToStack(stack_t *s, char *topdir)
{
    // 	st_mode, st_ino, st_dev, st_uid, st_gid, st_atime, st_ctime and st_mtime
    // printf("Is it a regular file?: %d\n", dum);

    DIR *dirStruct = getdir(topdir);
    errno = 0;
    struct dirent *path;
    struct stat buf;
    int pathstat;

    // We only have the relative paths, so we need to change into the top directory first.
    chdir(topdir);

    // readdir returns a pointer to dirStruct representing the next directory entry.
    // When it gets to the end, it returns NULL.
    while ((path = readdir(dirStruct)) != NULL)
    {
        printf("%s: ", path->d_name);

        pathstat = lstat(path->d_name, &buf);
        printf("status=%d", pathstat);

        if ((pathstat != 0) || (strcmp(path->d_name, ".") == 0) || (strcmp(path->d_name, "..") == 0))
        {
            printf("\n");
            continue;
        }
        else if ((S_ISREG(buf.st_mode)) || S_ISDIR(buf.st_mode))
        {
            printf(", Directory or Regular file, adding\n");
            push(s, path->d_name);
        }
        else
        {
            printf("Error: unexpected value for status of %s", path->d_name);
        }
    }

    return;
}

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
