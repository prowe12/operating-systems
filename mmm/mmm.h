#ifndef MMM_H_
#define MMM_H_

// globals (anything here would be shared with all threads) */
// I would declare the pointers to the matrices here (i.e., extern double **A, **B, **C),
// as well as the size of the matrices, etc.
extern int **mat1, **mat2, **mat3, **mat4;
extern int matdim;

/** struct to hold parameters to mmm_par() **/
typedef struct thread_args
{
    int tid;    // the given thread id (0, 1, ...)
    long first; // first row
    long last;  // last row
} thread_args;

void mmm_init();
void mmm_reset(int **);
void mmm_freeup();
void mmm_seq();
void *mmm_par(void *args);
double mmm_verify();
void mmm_print();
void mmm_print1(int **array);

#endif /* MMM_H_ */
