/**
* @file pLib.h
* @author Mahmud Bera KARAGÖZ
*/

float *returnVector(int size); 
float **returnMatrix(int row, int col); 
void freeMatrix(float **mat, int row); 
float mean(float *vec, int size); 
float correlation(float *vec, float *vec2, int size); 
float covariance(float *vec1, float *vec2, int size); 
float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2); 
float **matrixTranspose(float **mat, int row, int col); 
float *rowMeans(float **mat, int row, int col); 
float *columnMeans(float **mat, int row, int col); 
float **covarianceMatrix(float **mat, int row, int col); 
float determinant(float **mat, int row); 
void printVector(float *vec, int N); 
void printMatrix(float **mat, int row, int col); 