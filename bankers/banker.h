/* declarations related to banker's algorithm */
int isSafe(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES);
// int isSafeForOrdering(int *availVec, int **allocMat, int **needMat, int *rowOrder, int printUnsafeMsg, int NPROC, int NRES);
void printUnsafe(int *finishVec, int NPROC);
int isSafeForOrder(int *availVec, int **allocMat, int **needMat, int NPROC, int NRES, int *threadorder);
int getorder(int j, int n, int *order, int safe, int *availVec, int **allocMat, int **needMat, int NRES);
