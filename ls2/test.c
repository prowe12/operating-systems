/*
 * main.c
 *
 *  Created on: Feb. 4, 2023
 *      Author: Penny Rowe
 *
 * Reminder: valgrind --leak-check=full ./ls2 dum2 file2a
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "stack.h"
#include "ls2.h"

void quit(stack_t *s, char *msg)
{
    freestack(s);
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

// If it is the pointer, use the ->
// If it is the struct, use .

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
    // stack stores the lines to print out
    stack_t *s = initstack();

    char *topdir;
    DIR *dirStruct;
    topdir = "dumdir";

    struct dirent *path;

    // // First way: works
    // dirStruct = opendir(topdir);
    // while ((path = readdir(dirStruct)) != NULL)
    // {
    // 	push(s, path->d_name);
    // }

    // // Another way:
    // dirStruct = opendir(topdir);
    // while ((path = readdir(dirStruct)) != NULL)
    // {
    // 	char *dumstr = path->d_name;
    // 	push(s, dumstr);
    // }

    // // This works too
    char *stringForStack[100];
    dirStruct = opendir(topdir);
    while ((path = readdir(dirStruct)) != NULL)
    {
        *stringForStack = path->d_name;
        push(s, *stringForStack);
    }

    // This prints the same thing
    // dirStruct = opendir(topdir);
    // while ((path = readdir(dirStruct)) != NULL)
    // {
    //     char *stringForStack[100];
    //     // char *mypointer = path->d_name;
    //     strcpy(*stringForStack, "  ");
    //     strcat(*stringForStack, path->d_name);
    //     // printf("%s\n", stringForStack);
    //     push(s, &stringForStack);
    // }

    // print stack
    printf("\n\nPrinting stack:\n");
    printstack(s);

    // free up memory
    freestack(s);
    return 0;
}
