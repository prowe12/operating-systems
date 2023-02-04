#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	// stack stores the lines to print out
	stack_t *s = initstack();

	// TODO: Parse the inputs

	// TODO: Get the contents of path and put it in the stack

	// TODO: Loop over the path contents and see what the file type is ('.', dir, file, link, etc)
	// TODO: For every directory, repeat lines 17 - 20

	// TODO: Case 1: Only path entered

	// TODO: Case 2: pattern also entered
	push(s, "Hello1");
	push(s, "Hello2");
	push(s, "Hello3");

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;
}
