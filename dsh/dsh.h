/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100

void printCwd(int nargs);
void changeDir(char **array, int nargs);
int executeCmd(char **array, int hasAmp);
int buildPathAndExecuteCmd(char **array, int nargs, int hasAmp);
