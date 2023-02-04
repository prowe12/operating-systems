#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

// TODO: Function declarations here for ls2
void getDirs(stack_t *s);
void getDirsWithFile(stack_t *s, char *fname);

#endif
