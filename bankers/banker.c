#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "banker.h"

// int checkSafetyAndPrint(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES) {
//     int safety;
//     safety = isSafe(availVec, allocMat, needMat, NPROC, NRES);
//     return safety;}

// int isSafe(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES)
// {
//     int rowOrder[NPROC];
//     for (int i = 0; i < NPROC; i++)
//         rowOrder[i] = i;

//     int safety = isSafeForOrdering(availVec, allocMat, needMat, rowOrder, 1, NPROC, NRES);
//     return safety;
// }

/**
 * Test if i is already in the list
 */
int notInList(int *list, int num, int len)
{
    // printf("Len: %d\n", len);
    for (int i = 0; i < len; i++)
    {
        // printf("on item %d: %d\n", i, list[i]);
        if (list[i] == num)
            return 0; // not not in list
    }
    return 1; // not in list
}

/**
 * Run isSafe for all orderings
 */
int getorder(int j, int n, int *order, int safe, int *availVec, int **allocMat, int **needMat, int NRES)
{

    if (j >= n)
    {
        printf("Safe: ");
        for (int k = 0; k < n; k++)
            printf("T%d ", order[k]);
        printf("\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        // if (j == 0)
        //     clonevec(availVec, workVec, NRES); // copy availability vector to workVec
        if (notInList(order, i, j))
        {
            // printf("trying %d for the %dth slot\n", i, j);
            int *workVec = (int *)malloc(sizeof(int) * NRES);
            clonevec(availVec, workVec, NRES); // copy availability vector to workVec
            order[j] = i;
            // Is it still safe?
            if (vec1GreaterOrEqualVec2(workVec, needMat[i], NRES))
            {
                addVec2toVec1(workVec, allocMat[i], NRES);
                safe = getorder(j + 1, n, order, safe, workVec, allocMat, needMat, NRES);
            }
            free(workVec);
        }
    }
    return safe;
}

/**
 * Test if the processes can run safely or if a deadlock is possible. If safe, print all possible thread orders.
 * If unsafe, print that it is unsafe.  Return status (0 for unsafe, 1 for safe)
 */
int isSafeForOrder(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES, int *threadorder)
{
    // Need to keep track of the order the threads run in in the simulation

    // Initialization of work vector for resources and finish vector for processes
    // The work vec holds the number of currently available resources,
    // which increases every time a thread finishes and its resources are freed up
    int *workVec = (int *)malloc(sizeof(int) * NRES);
    clonevec(availVec, workVec, NRES);

    // int *finishVec = (int *)malloc(sizeof(int) * NPROC);
    // for (int i = 0; i < NPROC; i++)
    //     finishVec[i] = 0;

    // Simulation: See if all threads can finish
    // int iorder = 0;
    int row;
    for (int i = 0; i < NPROC; i++)
    {
        // Select the row to try to run
        row = threadorder[i];

        // Can we run this thread?
        if (vec1GreaterOrEqualVec2(workVec, needMat[row], NRES))
        {
            // pretend that thread i finishes execution
            // then OS can reclaim thread i's allocated resources
            addVec2toVec1(workVec, allocMat[row], NRES);
            // finishVec[row] = 1;

            // Create the ordering for this string
            // threadorder[iorder] = row;
            // iorder++;
        }
        else
        {
            free(workVec);
            workVec = NULL;
            // free(finishVec);
            // finishVec = NULL;
            return 0;
        }
    }

    // If they all finished, we can return 1 for safe
    free(workVec);
    workVec = NULL;
    // free(finishVec);
    // finishVec = NULL;
    return 1;
}

/**
 * Test if the processes can run safely or if a deadlock is possible. If safe, print all possible thread orders.
 * If unsafe, print that it is unsafe.  Return status (0 for unsafe, 1 for safe)
 */
int isSafe(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES)
{
    // Need to keep track of the order the threads run in in the simulation
    int threadorder[NPROC];
    int rowOrder[NPROC];
    for (int i = 0; i < NPROC; i++)
        rowOrder[i] = i;

    // Initialization of work vector for resources and finish vector for processes
    // The work vec holds the number of currently available resources,
    // which increases every time a thread finishes and its resources are freed up
    int *workVec = (int *)malloc(sizeof(int) * NRES);
    clonevec(availVec, workVec, NRES);

    int *finishVec = (int *)malloc(sizeof(int) * NPROC);
    for (int i = 0; i < NPROC; i++)
        finishVec[i] = 0;

    // Simulation: See if all threads can finish
    int unfinished = 1;
    int notstuck = 1;
    int count = 0;
    int iorder = 0;
    int row;
    while (unfinished & notstuck)
    {
        count += 1;
        unfinished = 0; // Set to finished until we find a thread we *need* to do
        notstuck = 0;   // Set to stuck until we find a thread we *can* do
        for (int i = 0; i < NPROC; i++)
        {
            // Select the row to try to run
            row = rowOrder[i];

            // Can we run this thread?
            if ((finishVec[row] == 0) & (vec1GreaterOrEqualVec2(workVec, needMat[row], NRES)))
            {
                // pretend that thread i finishes execution
                // then OS can reclaim thread i's allocated resources
                addVec2toVec1(workVec, allocMat[row], NRES);
                finishVec[row] = 1;
                notstuck = 1; // We are not stuck because we just freed resources

                // Create the ordering for this string
                threadorder[iorder] = row;
                iorder++;
            }
            else if (finishVec[row] == 0)
                unfinished = 1; // We are not finished, but we may be stuck
        }
        if (count >= 100)
        {
            printf("too many tries, giving up!\n");
            free(workVec);
            workVec = NULL;
            return 0;
        }
    }

    free(workVec);
    workVec = NULL;

    // if ((unfinished) & (notstuck))
    //     printf("Unfinished and not stuck\n");
    // else if ((unfinished) & (notstuck == 0))
    //     printf("Unfinished and stuck\n");
    // else if ((unfinished == 0) & (notstuck))
    //     printf("Finished and not stuck!\n");
    // else if ((unfinished == 0) & (notstuck == 0))
    //     printf("Stuck but who cares, we finished!\n");
    // else
    //     printf("How did this happen?");

    // As soon as we find one that did not finish, we can return 0 for unsave
    if (unfinished)
    {
        printUnsafe(finishVec, NPROC);
        free(finishVec);
        finishVec = NULL;

        return 0;
    }
    // {
    //     printf("Unsafe: ");
    //     for (int i = 0; i < NPROC; i++)
    //     {
    //         if (finishVec[i] == 0)
    //             printf("T%d ", i);
    //     }
    //     printf("cannot finish\n");
    //     return 0;
    // }

    printf("Safe: ");
    for (int i = 0; i < NPROC; i++)
        if (finishVec[i] == 0)
        {
            printf("\nError: T%d not safe!", i);
            free(finishVec);
            finishVec = NULL;
            return 0;
        }
        else
            printf("T%d ", threadorder[i]);
    printf("\n");

    // If they all finished, we can return 1 for safe
    free(finishVec);
    finishVec = NULL;
    return 1;
}

/**
 * If isSafe did not finish, print that it is unsafe
 */
void printUnsafe(int *finishVec, int NPROC)
{
    printf("Unsafe: ");
    for (int i = 0; i < NPROC; i++)
    {
        if (finishVec[i] == 0)
            printf("T%d ", i);
    }
    printf("cannot finish\n");
    return;
}
