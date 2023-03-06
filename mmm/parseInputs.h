#ifndef PARSEINPUTS_H_
#define PARSEINPUTS_H_

void mmm_init();
void mmm_reset(double **);
void mmm_freeup();
void mmm_seq();
void *mmm_par(void *args);
double mmm_verify();
void mmm_print();
void mmm_print1(int **array);

#endif /* PARSEINPUTS_H_ */
