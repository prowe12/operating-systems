#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

// pseudocode (from homework assignment description):
//
int isSafe(int **availMat, int **allocMat, int **needMat)
{
    //
    // 	Work[m] = Available.clone();
    // 	Finish[n] = [0, 0, ..., 0] for all 0 <= i < n
    //
    // 	while (exists unfinished thread i && Need[i] <= Work) {
    // 		// pretend that thread i finishes execution
    // 		// then OS can reclaim thread i's allocated resources
    // 		Work += Alloc[i]
    // 		Finish[i] = 1
    // 	}
    // 	// there's an execution order in which all threads
    // 	if (Finish == [1, 1, ..., 1])
    // 		return true	// safe!
    // 	return false		// unsafe!
    // }
    return 1;
}
