/*
 * stringmanager.c
 *
 *  Created on: Feb. 18, 2023
 *      Author: prowe
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stringmanager.h"

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
            // Skip remaining delimiters and position index at next different character
            while (str[i + 1] == delim[0])
                i++;
        }
        i++;
    }
    numtokens++; // There is one more token than there are delimiters

    return numtokens;
}

/**
 * Remove trailing spaces
 *  @param moddedStr (OUT)
 */
void removeTrailingSpaces(char *moddedStr)
{
    int i = strlen(moddedStr) - 1; // subtract 1 to get index
    while (i >= 0 && moddedStr[i] == ' ')
        i--;
    moddedStr[i + 1] = '\0'; // Put null at end of string
}

/**
 * Remove trailing spaces
 * @param moddedStr (OUT)
 */
void removeTrailingReturn(char *moddedStr)
{
    int i = strlen(moddedStr) - 1; // subtract 1 to get index
    if (moddedStr[i] != '\n')
        perror("String did not end with return as expected!");
    moddedStr[i] = '\0';
    return;
}

/**
 * Remove ampersand at end
 * @param moddedStr (OUT)
 */
int removeAmp(char *moddedStr)
{
    int hasAmp = 0;
    if (moddedStr[strlen(moddedStr) - 1] == '&')
    {
        // & found at end! Remove the & along with any trailing spaces
        hasAmp = 1;
        moddedStr[strlen(moddedStr) - 1] = '\0';
        removeTrailingSpaces(moddedStr);
    }
    return hasAmp;
}

/**
 * Remove trailing return and leading and trailing spaces
 * @param str  The original string
 * @param str1  The final string
 * Note: Code for removal of leading spaces from
 * https://www.geeksforgeeks.org/c-program-to-trim-leading-white-spaces-from-string/
 */
int cleanup(char str[MAXBUF], char str1[MAXBUF])
{
    char tempstr[MAXBUF];
    strcpy(tempstr, str);

    // Remove final return and trailing spaces
    removeTrailingReturn(tempstr);
    removeTrailingSpaces(tempstr);

    // Remove & at end, if present, and return whether one was found
    int hasAmp = removeAmp(tempstr);

    if (strlen(tempstr) < 1)
    {
        strcpy(str1, "\0");
        return hasAmp;
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

    // Return whether there is an & at the end
    return hasAmp;
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
    char **array = (char **)malloc(MAXBUF * (numtokens + 1) * sizeof(char *));

    // Setup the token
    char *token;

    // str is searched until the delimiter is found. The first token is
    // returned and the variable assigned the result points to that token (string)
    token = strtok(str, delim);

    // Loop through each array element and instantiate an array
    // of capacity cap
    for (int i = 0; i < numtokens; i++)
    {
        array[i] = (char *)malloc((MAXBUF + 1) * sizeof(char));
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
