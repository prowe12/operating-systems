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
void cleanup(char str[MAXBUF], char str1[MAXBUF]);
int executeCmd(char **array);
int buildPathAndExecuteCmd(char **array, int nargs);
void freearray(char **array);
