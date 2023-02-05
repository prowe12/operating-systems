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
    topdir = "dum1";

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
    // char *stringForStack[100]; // pointer to character array
    // dirStruct = opendir(topdir);
    // while ((path = readdir(dirStruct)) != NULL)
    // {
    //     // path is a pointer to a struct
    //     // path->d_name is a pointer to a character array?
    //     *stringForStack = path->d_name;
    //     push(s, *stringForStack);
    // }

    dirStruct = opendir(topdir);
    while ((path = readdir(dirStruct)) != NULL)
    {
        int flen = strlen(path->d_name);
        printf("file length: %d\n", flen);

        char *mystr = (char *)malloc(strlen("    ") + flen + 1);
        mystr[0] = '\0';
        strcpy(mystr, "    ");
        strcat(mystr, path->d_name);
        push(s, mystr);
    }

    // char *mystr = (char *)malloc(strlen("    ") + strlen(path->d_name) + 1);
    // char *mystr = (char *)malloc(strlen("    ") + 4 + 1);
    // mystr[0] = '\0';
    // strcpy(mystr, "hello");
    // push(s, mystr);
    //  strcpy(mystr, "penny");
    //  push(s, mystr);

    // Try to append spaces
    // dirStruct = opendir(topdir);
    // while ((path = readdir(dirStruct)) != NULL)
    // {
    //     // char *dumstr = (char *)malloc(strlen("    ") + strlen(path->d_name) + 1);
    //     // dumstr[0] = '\0';

    //     // strcpy(dumstr, "hello");
    //     char dumstr = "hello";
    //     // strcat(email, "@");    // append @
    //     // strcat(email, domain); // append domain
    //     // char *stringForStack[100];
    //     // *stringForStack = path->d_name;

    //     // char *mypointer = path->d_name;
    //     // strcpy(*stringForStack, "  ");
    //     // strcat(dumstr, stringForStack);
    //     // printf("%s\n", *dumstr);
    //     //*stringForStack = *dumstr;
    //     //  char *p[100] = dumstr;
    //     //  printf("%s\n", stringForStack);
    //     push(s, dumstr);
    //     free(dumstr);
    // }

    // print stack
    printf("\n\nPrinting stack:\n");
    printstack(s);

    // free up memory
    freestack(s);
    return 0;
}
