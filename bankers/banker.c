#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "banker.h"

/**
 * Determine if there is a safe thread order, and, if so, print all safe orderings.
 * If not, print an instance of unsafe orderings.
 * @param j  The current index to the thread running order
 * @param order  The thread running order
 * @param finishVec  The state of each thread (finished=>1, else 0)
 * @param workVec  The current work vector
 * @param allocMat  number of resources allocated to each thread for each resource type
 * @param needMat  Number of resources needed by each thread for each resource type
 * @param nres  Number of resource types (number of columns)
 * @param nproc  Number of processes/threads (number of rows)
 * @returns 1 if the threads can be run safely, else 0
 */
int isSafe(int j, int *order, int *finishVec, int *workVec, int **allocMat, int **needMat, int nres, int nproc)
{
    int safe = 0;           // Assume at first that the current ordering is unsafe
    int thisThreadSafe = 0; // Assume at first that the current thread is unsafe

    // Return condition: we have completed all threads for a given thread sequence
    // Note that we will only meet this condition if we have found a safe ordering,
    // since j is the number of processes that have been run, thus nproc process must
    // have been run, and those processes must have been unique, since no thread is
    // allowed to run twice. If there is one or more safe order, the final one will
    // return safe=1.
    if (j >= nproc)
    {
        // Print the thread order and return 1 for safe
        printf("Safe: ");
        for (int k = 0; k < nproc; k++)
            printf("T%d ", order[k]);
        printf("\n");
        return 1;
    }

    // Loop over all the threads and test each one if it is safe for the given order slot
    for (int t = 0; t < nproc; t++)
    {
        // Have we run this thread before?  If so, its element of the finish vector will be 1
        // If not, check if it is safe to run now.
        if ((finishVec[t] == 0) && (vec1GreaterOrEqualVec2(workVec, needMat[t], nres)))
        {
            // Put this thread into the ordering, set its thread's state to run (1)
            // and add the freed resources to the work vector
            thisThreadSafe = 1; // This thread ran safely (even if the next might not)
            order[j] = t;
            finishVec[t] = 1;
            addVec2toVec1(workVec, allocMat[t], nres);

            // Return whether there is a safe thread for the next process.
            safe = isSafe(j + 1, order, finishVec, workVec, allocMat, needMat, nres, nproc);

            // We are about to try a different thread in this order slot, so undo changes made:
            // undo setting this thread's state to run and remove the resources. Note that
            // we do *not* undo the state of safe here, so if even one thread ordering is safe,
            // then safe=1 will be returned at the end, otherwise it will be left at 0.
            // We do not need to undo order[j] because it will be replaced.
            finishVec[t] = 0;
            subtractVec2fromVec1(workVec, allocMat[t], nres);
        }
    }

    // At the point when we cannot find a safe thread, print the unsafe message. However, after
    // printing this message, the recursion must unwind, delivering safe=0 back to the original
    // call for the 0th order slot. We do not want the unsafe message printed every time.
    // Therefore, only print the unsafe message only when:
    // 1) The current thread order is unsafe and
    // 2) The current thread is unsafe.
    if ((safe == 0) && (thisThreadSafe == 0))
        printUnsafe(finishVec, nproc);
    return safe;
}

/**
 * If isSafe did not finish, print that it is unsafe and print the unsafe threads
 * @param finishVec  The state of each thread (finished=>1, else 0)
 * @param nproc  Number of processes/threads (number of rows)
 */
void printUnsafe(int *finishVec, int nproc)
{
    printf("Unsafe: ");
    for (int i = 0; i < nproc; i++)
        if (finishVec[i] == 0)
            printf("T%d ", i);
    printf("cannot finish\n");
    return;
}
