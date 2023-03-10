#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

// TODO: Function declarations here for ls2
void getDirs(stack_t *s);
void getDirsWithFile(stack_t *s, char *fname);
DIR *getdir(char *path);
int pushToStack(stack_t *s, char *fname, char *topdir, int depth); //, int iarray);
int pushToStackFile(stack_t *s, char *fname, char *topdir, char **dirArray, int depth, int iarray);
int printCwd();

#endif

// void pushToStack(stack_t *s, char *topdir, int depth);
// void pushToStack(stack_t *s, char *topdir, char **dirArray, int depth);
