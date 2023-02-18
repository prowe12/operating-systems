/*
 * stringmanager.h
 *
 *  Created on: Feb. 18, 2023
 *      Author: Penny Rowe
 */

#define MAXBUF 256

void printarray(char **array);
int getNumTokens(char *str, char *delim);
char **split(char *str, char *delim, int numtokens);
int cleanup(char str[MAXBUF], char str1[MAXBUF]);
void removeTrailingSpaces(char *moddedStr);
void removeTrailingReturn(char *moddedStr);
int removeAmp(char *tempstr);
void freearray(char **array);
