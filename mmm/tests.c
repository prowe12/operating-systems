#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>  // for errno
#include <limits.h> // for INT_MAX, INT_MIN
#include "rtclock.h"
#include "mmm.h"
#include "parseInputs.h"

void setToTestVals()
{
    for (int j = 0; j < matdim; j++)
    {
        mat1[0][j] = 1;
        mat1[1][j] = 2;
        mat1[2][j] = 3;
    }
    for (int i = 0; i < matdim; i++)
    {
        mat2[i][0] = 1;
        mat2[i][1] = 2;
        mat2[i][2] = 3;
    }

    return;
}

int main(int argc, char *argv[])
{

    // 3x3 sequential
    int inputs[3] = {1, 3, 0};

    // The variables
    int nthreads = inputs[0];
    int runtype = inputs[2];
    matdim = inputs[1];

    printf("Type of run (0=>single, 1=>parallel): %d\n", runtype);
    printf("nthreads = %d\n", nthreads);
    printf("size = %d\n", matdim);

    // Initialze the matrices
    mmm_init();

    // Set them to test values
    setToTestVals();

    // TODO: remove this line
    mmm_print();

    double clockstart, clockend;
    clockstart = rtclock(); // start clocking

    // start: stuff I want to clock
    if (runtype == 0)
    {
        // TODO: delete this line
        printf("You have chosen sequential\n");
        mmm_seq();
    }
    else if (runtype == 1)
    {
        // TODO: delete this line
        printf("You have chosen parallel implementation\n");
        // mmm_par();
    }
    else
    {
        printf("Unexpected value for runtype\n");
        exit(EXIT_FAILURE);
    }
    // end: stuff I want to clock

    clockend = rtclock(); // stop clocking
    printf("Time taken: %.6f sec\n", (clockend - clockstart));

    // Freeup the array
    mmm_freeup();

    return 0;
}
