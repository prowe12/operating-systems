#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"

// TODO: function definitions here for ls2

// TODO: Get contents of path
void getDirs(stack_t *s)
{
    printf("In getDirs\n");
    return;
}

void getDirsWithFile(stack_t *s, char *fname)
{
    printf("In getDirsWithFile\n");
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
