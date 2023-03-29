#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // for errno
#include <ctype.h> // for isdigit
#include "parseInputs.h"

// From https://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
int isPositiveInteger(char number[])
{

    // checking for negative numbers
    if (number[0] == '-')
        return 0;

    for (int i = 0; number[i] != 0; i++)
    {
        // if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

// void badNumberInputs()
// {
//     printf("Usage: ./mmmSol <mode> [num threads] <size>\n");
//     exit(EXIT_FAILURE);
//     return;
// }

int parseInputs(int argc, char *argv[])
{
    char *msg = "Usage: %s <num threads> <hashmap capacity>\n";

    if (argc < 3)
    {
        printf(msg, argv[0]);
        return 0;
    }

    if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2]))
    {
        printf("num threads and capacity must be positive whole numbers\n");
        printf(msg, argv[0]);
        return 0;
    }

    return 1;
}
