/**
 * @file pMain.c
 * @author Mahmud Bera KARAGÖZ
 */

#include "pLib.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int number, char *args[])
{
    printf("");
    if (number < 2)
    {
        printf("\nArguman sayisi yeterli degildir.\n");
        return 0;
    }

    srand(atoi(args[1]));

    int v1S = 0;
    int v2S = 0;
    printf("Lutfen birinci vektorun boyutunu giriniz:");
    scanf("%d", &v1S);
    printf("Lutfen ikinci vektorun boyutunu giriniz:");
    scanf("%d", &v2S);

    int mR = 0;
    int mC = 0;
    printf("\nLutfen birinci matrisin satir sayisini giriniz:");
    scanf("%d", &mR);
    printf("Lutfen birinci matrisin sutun sayisini giriniz:");
    scanf("%d", &mC);

    int mR2 = 0;
    int mC2 = 0;
    printf("\nLutfen ikinci matrisin satir sayisini giriniz:");
    scanf("%d", &mR2);
    printf("Lutfen ikinci matrisin sutun sayisini giriniz:");
    scanf("%d", &mC2);

    printf("Girmis oldugunuz degerlere gore olusturulan vectorler:\n");
    float *v1 = returnVector(v1S);
    float *v2 = returnVector(v2S);
    printf("Birinci vektor: \n");
    printVector(v1, v1S);
    printf("\nIkinci vektor: \n");
    printVector(v2, v2S);

    printf("\nGirmis oldugunuz degerlere gore olusturulan birinci matris:\n");
    float **m1 = returnMatrix(mR, mC);
    printMatrix(m1, mR, mC);

    printf("\nGirmis oldugunuz degerlere gore olusturulan ikinci matris:\n");
    float **m2 = returnMatrix(mR2, mC2);
    printMatrix(m2, mR2, mC2);

    printf("\nOlusturulan vektorlerdeki degerlerin ortalamasi soyledir:\n");
    float v1SM = mean(v1, v1S);
    float v2SM = mean(v2, v2S);
    printf("\tBirinci vektorun ortalamasi: %.4f", v1SM);
    printf("\n\tIkinci vektorun ortalamasi: %.4f\n", v2SM);

    printf("\nOlusturulan vektorler arasindaki korelasyon hesabi:\n");
    if (v1S != v2S)
    {
        printf("\tIslem yapmak istediginiz vektorlerin boyutlari ayni olmadigi icin islem yapilamamaktadir.\n");
    }
    else
    {
        float cR = correlation(v1, v2, v1S);
        printf("\tIslem sonucu = %f\n", cR);
    }

    printf("\nOlusturulan vektorler arasindaki kovaryans hesabi:\n");
    if (v1S != v2S)
    {
        printf("\tIslem yapmak istediginiz vektorlerin boyutlari ayni olmadigi icin islem yapilamamaktadir.\n");
    }
    else
    {
        float covR = covariance(v1, v2, v1S);
        printf("\tIslem sonucu = %f\n", covR);
    }

    printf("\nOlusturulan iki matrisin carpiminin sonucu:\n");
    if (mC == mR2)
    {
        float **mMR = matrixMultiplication(m1, m2, mR, mC, mR2, mC2);
        printMatrix(mMR, mR, mC2);
    }
    else
    {
        printf("\tBirinci matrisin sutun sayisi ile ikinci matrisin satir sayisi esit olmadigi icin islem yapilamamaktadir.\n");
    }

    printf("\nBirinci matrisin transpozesi:\n ");
    printMatrix(matrixTranspose(m1, mR, mC), mC, mR);

    printf("\nBirinci matrisin satir elemanlarinin ortalamasi:\n ");
    printVector(rowMeans(m1, mR, mC), mR);

    printf("\nBirinci matrisin sutun elemanlarinin ortalamasi:\n ");
    printVector(columnMeans(m1, mR, mC), mC);

    printf("\nBirinci matrisin kovaryans matris hesabi:\n ");
    if (mR == mC)
    {
        printMatrix(covarianceMatrix(m1, mR, mC), mR, mC);
    }
    else
    {
        printf("\tMatris NxN boyutunda olmadigi icin bu islem yapilamamaktadir.\n");
    }

    printf("\nBirinci matrisin determinanti:\n ");
    if (mR == 3 && mC == 3)
        printf("\tDeterminant sonucu: %f", determinant(m1, mR));
    else
        printf("\tMatris boyutu 3x3 olmadigi icin determinant hesabi yapilamamaktadir.\n");

    printf("\nIkinci olarak olusturulan matris icin free islemi:\n");
    freeMatrix(m2, mR2);
    printMatrix(m2, mR2, mC2);
    return 0;
}