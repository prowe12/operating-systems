/* declarations related to banker's algorithm */
void printUnsafe(int *finishVec, int NPROC);
int isSafe(int j, int *order, int *finishVec, int *workVec, int **allocMat, int **needMat, int NRES, int nproc);
