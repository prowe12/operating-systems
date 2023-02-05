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

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

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

void pushToStack(stack_t *s, char *topdir, int depth)
{
    // 	st_mode, st_ino, st_dev, st_uid, st_gid, st_atime, st_ctime and st_mtime
    // printf("Is it a regular file?: %d\n", dum);

    DIR *dirStruct = getdir(topdir);
    errno = 0;
    struct dirent *path;
    struct stat buf;
    int pathstat;

    //*stringForStack = "    ";

    // We only have the relative paths, so we need to change into the top directory first.
    // printf("%s: \n", topdir);
    chdir(topdir);

    // readdir returns a pointer to dirStruct representing the next directory entry.
    // When it gets to the end, it returns NULL.
    while ((path = readdir(dirStruct)) != NULL)
    {

        // printf("%s: \n", topdir);
        // chdir(topdir);
        // printCwd();
        pathstat = lstat(path->d_name, &buf);

        if ((pathstat != 0) || (strcmp(path->d_name, ".") == 0) || (strcmp(path->d_name, "..") == 0))
        {
            // printf("status=%d, path=%s, skip\n", pathstat, path->d_name);
            continue;
        }
        else if (S_ISREG(buf.st_mode))
        {
            // printf("status=%d, path=%s, regular file, ADD\n", pathstat, path->d_name);
            // Get file size in bytes and convert to string
            off_t filesize = buf.st_size;
            // printf("%s size: %ld\n", path->d_name, filesize);
            char filesizestr[50];
            snprintf(filesizestr, 50, "%lu", filesize);
            // printf("%s size: %s\n", path->d_name, filesizestr);

            int flen = strlen(path->d_name);
            char *mystr = (char *)malloc(strlen("    ") + flen + 1);
            mystr[0] = '\0';
            for (int i = 0; i < depth; i++)
            {
                strcat(mystr, "    ");
            }
            strcat(mystr, path->d_name);
            strcat(mystr, " (");
            strcat(mystr, filesizestr);
            strcat(mystr, " bytes)");

            push(s, mystr);

            // push(s, stringForStack);
        }
        else if (S_ISDIR(buf.st_mode))
        {
            // printf("status=%d, path=%s, directory, recurse\n", pathstat, path->d_name);
            pushToStack(s, path->d_name, depth + 1);
            char *stringForStack = path->d_name;
            strcat(stringForStack, "/ (directory)");
            // printf("back to directory %s\n", topdir);
            chdir("../");
            // printf("status=%d, path=%s, ADD\n", pathstat, path->d_name);
            push(s, stringForStack);
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
