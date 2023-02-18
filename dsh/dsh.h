/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100

void printarray(char **array);
int getNumTokens(char *str, char *delim);
char **split(char *str, char *delim, int numtokens);
void printCwd(int nargs);
void changeDir(char **array, int nargs);
void printTheEcho(char **array);
void printHistory(char **array);
int cleanup(char str[MAXBUF], char str1[MAXBUF]);
void removeTrailingSpaces(char *moddedStr);
void removeTrailingReturn(char *moddedStr);
int removeAmp(char *tempstr);
int executeCmd(char **array, int hasAmp);
int buildPathAndExecuteCmd(char **array, int nargs, int hasAmp);
void freearray(char **array);
