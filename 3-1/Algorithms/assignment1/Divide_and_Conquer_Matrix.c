#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 1000;
        }
    }
}

void printMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void addMatrix(int **matrix1, int **matrix2, int **matrix3, int size, int *numofadd)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix1[i][j] = matrix2[i][j] + matrix3[i][j];
            *numofadd += 1;
        }
    }
    if(size != 1)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n ");
        }
        printf("\n");
    }
}

void mergeMatrix(int **matrix1, int **matrix2, int **matrix3, int **matrix4, int **matrix5, int size)
{

    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            matrix5[i][j] = matrix1[i][j];
            matrix5[i][j + size / 2] = matrix2[i][j];
            matrix5[i + size / 2][j] = matrix3[i][j];
            matrix5[i + size / 2][j + size / 2] = matrix4[i][j];
        }
    }
}

void DivideandConquer(int **matrix1, int **matrix2, int **matrix3, int size, int *numofmul, int *numofadd)
{
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **temp; 
    A11 = (int **)malloc(sizeof(int *) * size / 2);
    A12 = (int **)malloc(sizeof(int *) * size / 2);
    A21 = (int **)malloc(sizeof(int *) * size / 2);
    A22 = (int **)malloc(sizeof(int *) * size / 2);
    B11 = (int **)malloc(sizeof(int *) * size / 2);
    B12 = (int **)malloc(sizeof(int *) * size / 2);
    B21 = (int **)malloc(sizeof(int *) * size / 2);
    B22 = (int **)malloc(sizeof(int *) * size / 2);
    C11 = (int **)malloc(sizeof(int *) * size / 2);
    C12 = (int **)malloc(sizeof(int *) * size / 2);
    C21 = (int **)malloc(sizeof(int *) * size / 2);
    C22 = (int **)malloc(sizeof(int *) * size / 2);
    temp = (int **)malloc(sizeof(int *) * size / 2);

    for (int i = 0; i < size / 2; i++)
    {
        A11[i] = (int *)malloc(sizeof(int) * size / 2);
        A12[i] = (int *)malloc(sizeof(int) * size / 2);
        A21[i] = (int *)malloc(sizeof(int) * size / 2);
        A22[i] = (int *)malloc(sizeof(int) * size / 2);
        B11[i] = (int *)malloc(sizeof(int) * size / 2);
        B12[i] = (int *)malloc(sizeof(int) * size / 2);
        B21[i] = (int *)malloc(sizeof(int) * size / 2);
        B22[i] = (int *)malloc(sizeof(int) * size / 2);
        C11[i] = (int *)malloc(sizeof(int) * size / 2);
        C12[i] = (int *)malloc(sizeof(int) * size / 2);
        C21[i] = (int *)malloc(sizeof(int) * size / 2);
        C22[i] = (int *)malloc(sizeof(int) * size / 2);
        temp[i] = (int *)malloc(sizeof(int) * size / 2);
    }
    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            A11[i][j] = matrix1[i][j]; //a
            A12[i][j] = matrix1[i][j + size / 2]; //b
            A21[i][j] = matrix1[i + size / 2][j]; //c
            A22[i][j] = matrix1[i + size / 2][j + size / 2]; //d
            B11[i][j] = matrix2[i][j]; //e
            B12[i][j] = matrix2[i][j + size / 2]; //f
            B21[i][j] = matrix2[i + size / 2][j]; //g
            B22[i][j] = matrix2[i + size / 2][j + size / 2]; //h
        }
    }
    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            C11[i][j] = 0;
            C12[i][j] = 0;
            C21[i][j] = 0;
            C22[i][j] = 0;
            temp[i][j] = 0;
        }
    }

    if (size == 1)
    {
        matrix3[0][0] = matrix1[0][0] * matrix2[0][0];
        *numofmul += 1;
        return;
    }

    DivideandConquer(A11, B11, C11, size / 2, numofmul, numofadd); //P1
    DivideandConquer(A12, B21, temp, size / 2, numofmul, numofadd);
    addMatrix(C11, temp, C11, size / 2, numofadd);
    printf("C11\n");
    printMatrix(C11, size / 2);
    DivideandConquer(A11, B12, C12, size / 2, numofmul, numofadd);
    DivideandConquer(A12, B22, temp, size / 2, numofmul, numofadd);
    addMatrix(C12, temp, C12, size / 2, numofadd);
    DivideandConquer(A21, B11, C21, size / 2, numofmul, numofadd);
    DivideandConquer(A22, B21, temp, size / 2, numofmul, numofadd);
    addMatrix(C21, temp, C21, size / 2, numofadd);
    DivideandConquer(A21, B12, C22, size / 2, numofmul, numofadd);
    DivideandConquer(A22, B22, temp, size / 2, numofmul, numofadd);
    addMatrix(C22, temp, C22, size / 2, numofadd);

    mergeMatrix(C11, C12, C21, C22, matrix3, size);

    for (int i = 0; i < size / 2; i++)
    {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);
        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);
        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);
        free(temp[i]);
    }
    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(B11);
    free(B12);
    free(B21);
    free(B22);
    free(C11);
    free(C12);
    free(C21);
    free(C22);
    free(temp);
}

int main()
{
    srand(time(NULL));
    int **A, **B, **C;
    int numofmul = 0;
    int numofadd = 0;
    int numofsub = 0;
    A = (int **)malloc(sizeof(int *) * 4);
    B = (int **)malloc(sizeof(int *) * 4);
    C = (int **)malloc(sizeof(int *) * 4);
    for (int i = 0; i < 4; i++)
    {
        A[i] = (int *)malloc(sizeof(int) * 4);
        B[i] = (int *)malloc(sizeof(int) * 4);
        C[i] = (int *)malloc(sizeof(int) * 4);

    }
    createMatrix(A, 4);
    createMatrix(B, 4);
    printf("Matrix A is: \n");
    printMatrix(A, 4);
    printf("Matrix B is: \n");
    printMatrix(B, 4);
    DivideandConquer(A, B, C, 4, &numofmul, &numofadd);
    printf("Matrix C is: \n");
    printMatrix(C, 4);
    printf("Number of multiplication: %d\n", numofmul);
    printf("Number of addition: %d\n", numofadd);
    printf("Number of subtraction: %d\n\n", numofsub);

    for (int i = 0; i < 4; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    
    numofadd = 0;
    numofsub = 0;
    numofmul = 0;

    A = (int **)malloc(sizeof(int *) * 8);
    B = (int **)malloc(sizeof(int *) * 8);
    C = (int **)malloc(sizeof(int *) * 8);
    for (int i = 0; i < 8; i++)
    {
        A[i] = (int *)malloc(sizeof(int) * 8);
        B[i] = (int *)malloc(sizeof(int) * 8);
        C[i] = (int *)malloc(sizeof(int) * 8);
    }
    createMatrix(A, 8);
    createMatrix(B, 8);
    printf("Matrix A is: \n");
    printMatrix(A, 8);
    printf("Matrix B is: \n");
    printMatrix(B, 8);
    DivideandConquer(A, B, C, 8, &numofmul, &numofadd);
    printf("Matrix C is: \n");
    printMatrix(C, 8);
    printf("Number of multiplication: %d\n", numofmul);
    printf("Number of addition: %d\n", numofadd);
    printf("Number of subtraction: %d\n\n", numofsub);
    for (int i = 0; i < 8; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    numofadd = 0;
    numofsub = 0;
    numofmul = 0;

    A = (int **)malloc(sizeof(int *) * 16);
    B = (int **)malloc(sizeof(int *) * 16);
    C = (int **)malloc(sizeof(int *) * 16);
    for (int i = 0; i < 16; i++)
    {
        A[i] = (int *)malloc(sizeof(int) * 16);
        B[i] = (int *)malloc(sizeof(int) * 16);
        C[i] = (int *)malloc(sizeof(int) * 16);
    }
    createMatrix(A, 16);
    createMatrix(B, 16);
    printf("Matrix A is: \n");
    printMatrix(A, 16);
    printf("Matrix B is: \n");
    printMatrix(B, 16);
    DivideandConquer(A, B, C, 16, &numofmul, &numofadd);
    printf("Matrix C is: \n");
    printMatrix(C, 16);
    printf("Number of multiplication: %d\n", numofmul);
    printf("Number of addition: %d\n", numofadd);
    printf("Number of subtraction: %d\n\n", numofsub);
    for (int i = 0; i < 16; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}