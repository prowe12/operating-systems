/**
 * Matrix and vector operations
 * Penny Rowe
 * Apr. 2023
 */
void clonemat(int **mat, int **result, int nrows, int ncols);
void clonevec(int *vec, int *result, int ncols);
int compare(int *vec1, int *vec2);
void addmats(int **mat1, int **mat2);
void subtractvecs(int *vec1, int *vec2, int *result, int ncols);
void subtractmats(int **mat1, int **mat2, int **result, int nrows, int ncols);
void addVec2toVec1(int *vec1, int *vec2, int ncols);
void subtractVec2fromVec1(int *vec1, int *vec2, int ncols);
void sumRows(int **mat, int nrows, int ncols, int *result);
void printmat(int **mat, int nrows, int ncols);
void printvec(int *totVec, int NRES);
int vec1GreaterOrEqualVec2(int *greater, int *lesser, int ncols);
