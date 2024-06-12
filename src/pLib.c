/**
 * @file pLib.c
 * @author Mahmud Bera KARAGÖZ
 */

#include "pLib.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

float covariance(float *vec1, float *vec2, int size);

float *returnVector(int size)
{
    float *vector = (float *)malloc(size * sizeof(float));
    for (int j = 0; j < size; j++)
    {
        vector[j] = 1 + (rand() % 9);
    }
    return vector;
}

float **returnMatrix(int row, int col)
{
    float **mat;
    mat = (float **)malloc(row * sizeof(float *));
    for (int i = 0; i < row; i++)
    {
        mat[i] = (float *)malloc(col * sizeof(float));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            mat[i][j] = 1 + (rand() % 10);
        }
    }
    return mat;
}

void freeMatrix(float **mat, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(mat[i]);
    }
    free(mat);
    printf("\tFree islemi yapilmistir.\n");
}

float mean(float *vec, int size)
{
    float count = 0;
    for (int i = 0; i < size; i++)
        count += vec[i];

    count = count / (float)size;
    return count;
}

float correlation(float *vec, float *vec2, int size)
{
    float cov = covariance(vec, vec2, size);
    float mean1, mean2, var1, var2, result = 0;
    for (int i = 0; i < size; i++)
    {
        mean1 += vec[i];
        mean2 += vec2[i];
    }
    mean1 = mean1 / (float)size;
    mean2 = mean2 / (float)size;

    for (int i = 0; i < size; i++)
    {
        var1 += pow(vec[i] - mean1, 2);
        var2 += pow(vec2[i] - mean2, 2);
    }

    var1 = var1 / (float)(size - 1);
    var2 = var2 / (float)(size - 1);
    float cor = cov / (float)sqrt(var1 * var2);
    return cor;
}

float covariance(float *vec1, float *vec2, int size)
{
    float cov1 = 0;
    float cov2 = 0;
    float result = 0;
    for (int i = 0; i < size; i++)
    {
        cov1 += vec1[i];
        cov2 += vec2[i];
    }
    cov1 = cov1 / (float)size;
    cov2 = cov2 / (float)size;

    for (int i = 0; i < size; i++)
    {
        result += (vec1[i] - cov1) * (vec2[i] - cov2);
    }
    return result / (float)(size - 1);
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{
    float **matMult;
    matMult = returnMatrix(row1, col2);
    float result = 0;
    for (int i = 0; i < row1; i++)
    {
        for (int k = 0; k < col2; k++)
        {
            for (int j = 0; j < col1; j++)
            {
                result += mat1[i][j] * mat2[j][k];
            }
            matMult[i][k] = result;
            result = 0;
        }
    }
    return matMult;
}

float **matrixTranspose(float **mat, int row, int col)
{
    float **mTranspose;
    mTranspose = (float **)malloc(col * sizeof(float *));
    for (int i = 0; i < col; i++)
    {
        mTranspose[i] = (float *)malloc(row * sizeof(float));
    }
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            mTranspose[k][i] = mat[i][k];
        }
    }
    return mTranspose;
}

float *rowMeans(float **mat, int row, int col)
{
    float result = 0.0;
    float *rVector = (float *)malloc(row * sizeof(float));
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            result += mat[i][k];
        }
        rVector[i] = result / (float)col;
        result = 0.0;
    }
    return rVector;
}

float *columnMeans(float **mat, int row, int col)
{
    float result;
    float *rVector = (float *)malloc(col * sizeof(float));
    for (int i = 0; i < col; i++)
    {
        for (int k = 0; k < row; k++)
        {
            result += mat[k][i];
        }
        rVector[i] = result / (float)row;
        result = 0.0;
    }
    return rVector;
}

float **covarianceMatrix(float **mat, int row, int col)
{
    float *meansOfColumns = columnMeans(mat, row, col);
    float **covMat = returnMatrix(row, col);
    float res = 0;
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            if (i == k)
            {
                for (int j = 0; j < row; j++)
                {
                    res += pow(mat[j][k] - meansOfColumns[k], 2.0);
                }
                covMat[i][k] = res / col;
                res = 0;
            }
            else
            {
                for (int j = 0; j < row; j++)
                {
                    res += (mat[j][i] - meansOfColumns[i]) * (mat[j][k] - meansOfColumns[k]);
                }
                covMat[i][k] = res / col;
                res = 0;
            }
        }
    }
    return covMat;
}

float determinant(float **mat, int row)
{
    for (int i = 0; i < row; i++)
        mat[i] = realloc(mat[i], sizeof(float) * 5);

    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < row; k++)
        {
            mat[k][i + 3] = mat[k][i];
        }
    }
    float toplama[3];
    float cikarma[3];
    for (int i = 0; i < 3; i++)
    {
        int sonuc1 = 1;
        int sonuc2 = 1;
        if (i == 0)
        {
            for (int k = 0; k < 3; k++)
            {
                sonuc1 *= mat[k][k];
                sonuc2 *= mat[2 - k][k];
            }
            toplama[i] = sonuc1;
            cikarma[i] = sonuc2;
        }
        else if (i == 1)
        {
            for (int k = 0; k < 3; k++)
            {
                sonuc1 *= mat[k][k + 1];
                sonuc2 *= mat[2 - k][k + 1];
            }
            toplama[i] = sonuc1;
            cikarma[i] = sonuc2;
        }
        else
        {
            for (int k = 0; k < 3; k++)
            {
                sonuc1 *= mat[k][k + 2];
                sonuc2 *= mat[2 - k][k + 2];
            }
            toplama[i] = sonuc1;
            cikarma[i] = sonuc2;
        }
    }
    float toplam = 0;
    for (int i = 0; i < 3; i++)
    {
        toplam += toplama[i];
        toplam -= cikarma[i];
    }
    return toplam;
}

void printVector(float *vec, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("\t%d. deger = %.2f \n", i, vec[i]);
    }
}

void printMatrix(float **mat, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            printf("\t%.2f\t", mat[i][k]);
        }
        printf("\n");
    }
}