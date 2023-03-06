#ifndef PARSEINPUTS_H_
#define PARSEINPUTS_H_

void badNumberInputs();
int strToInt(char *inputStr);
int getSize(char *sizeStr);
int getRunType(char *runTypeStr);
int getNthreads(char *sizeStr);
void parseInputs(char *buf, int argc, char *argv[]);

#endif /* PARSEINPUTS_H_ */
