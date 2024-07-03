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
}

void subMatrix(int **matrix1, int **matrix2, int **matrix3, int size, int *numofsub)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix1[i][j] = matrix2[i][j] - matrix3[i][j];
            *numofsub += 1;
        }
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

void Strassen(int **matrix1, int **matrix2, int **matrix3, int size, int *numofadd, int *numofmul, int *numofsub){
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
    int **temp1, **temp2;

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
    P1 = (int **)malloc(sizeof(int *) * size / 2);
    P2 = (int **)malloc(sizeof(int *) * size / 2);
    P3 = (int **)malloc(sizeof(int *) * size / 2);
    P4 = (int **)malloc(sizeof(int *) * size / 2);
    P5 = (int **)malloc(sizeof(int *) * size / 2);
    P6 = (int **)malloc(sizeof(int *) * size / 2);
    P7 = (int **)malloc(sizeof(int *) * size / 2);
    temp1 = (int **)malloc(sizeof(int *) * size / 2);
    temp2 = (int **)malloc(sizeof(int *) * size / 2);

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
        P1[i] = (int *)malloc(sizeof(int) * size / 2);
        P2[i] = (int *)malloc(sizeof(int) * size / 2);
        P3[i] = (int *)malloc(sizeof(int) * size / 2);
        P4[i] = (int *)malloc(sizeof(int) * size / 2);
        P5[i] = (int *)malloc(sizeof(int) * size / 2);
        P6[i] = (int *)malloc(sizeof(int) * size / 2);
        P7[i] = (int *)malloc(sizeof(int) * size / 2);
        temp1[i] = (int *)malloc(sizeof(int) * size / 2);
        temp2[i] = (int *)malloc(sizeof(int) * size / 2);
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

    for(int i = 0; i < size / 2; i++){
        for(int j = 0; j < size / 2; j++){
            C11[i][j] = 0;
            C12[i][j] = 0;
            C21[i][j] = 0;
            C22[i][j] = 0;
            temp1[i][j] = 0;
            temp2[i][j] = 0;
            P1[i][j] = 0;
            P2[i][j] = 0;
            P3[i][j] = 0;
            P4[i][j] = 0;
            P5[i][j] = 0;
            P6[i][j] = 0;
            P7[i][j] = 0;
        }
    }

    if (size == 1){
        for(int i = 0; i < size / 2; i++){
            for(int j = 0; j < size / 2; j++){
                C11[i][j] = A11[i][j] * B11[i][j];
                *numofmul += 1;
            }
        }

        return;
    }



        subMatrix(temp1, B12, B22, size / 2, numofsub); // B12 - B22
        Strassen(A11, temp1, P1, size / 2, numofadd, numofmul, numofsub); // A11 * (B12 - B22)
        addMatrix(temp1, A11, A12, size / 2, numofadd); // A11 + A12
        Strassen(temp1, B22, P2, size / 2, numofadd, numofmul, numofsub); // (A11 + A12) * B22
        addMatrix(temp1, A21, A22, size / 2, numofadd); // A21 + A22
        Strassen(temp1, B11, P3, size / 2, numofadd, numofmul, numofsub); // (A21 + A22) * B11
        subMatrix(temp1, B21, B11, size / 2, numofsub); // B21 - B11
        Strassen(A22, temp1, P4, size / 2, numofadd, numofmul, numofsub); // A22 * (B21 - B11)
        addMatrix(temp1, A11, A22, size / 2, numofadd); // A11 + A22
        addMatrix(temp2, B11, B22, size / 2, numofadd); // B11 + B22'
        Strassen(temp1, temp2, P5, size / 2, numofadd, numofmul, numofsub); // (A11 + A22) * (B11 + B22)
        subMatrix(temp1, A12, A22, size / 2, numofsub); // A12 - A22
        addMatrix(temp2, B21, B22, size / 2, numofadd); // B21 + B22
        Strassen(temp1, temp2, P6, size / 2, numofadd, numofmul, numofsub); // (A12 - A22) * (B21 + B22)
        subMatrix(temp1, A11, A21, size / 2, numofsub); // A11 - A21
        addMatrix(temp2, B11, B12, size / 2, numofadd); // B11 + B12
        Strassen(temp1, temp2, P7, size / 2, numofadd, numofmul, numofsub); // (A11 - A21) * (B11 + B12)

        addMatrix(temp1, P5, P4, size / 2, numofadd); // P5 + P4
        subMatrix(temp2, temp1, P2, size / 2, numofsub); // (P5 + P4) - P2
        addMatrix(C11, P6, temp2, size / 2, numofadd); // (P5 + P4 - P2) + P6
        addMatrix(C12, P2, P1, size / 2, numofadd); // P1 + P2
        addMatrix(C21, P4, P3, size / 2, numofadd); // P3 + P4
        addMatrix(temp1, P1, P5, size / 2, numofadd); // P5 + P1
        subMatrix(temp2, temp1, P3, size / 2, numofsub); // (P5 + P1) - P3
        subMatrix(C22, temp2, P7, size / 2, numofsub); // (P5 + P1 - P3) - P7
        
        mergeMatrix(C11, C12, C21, C22, matrix3, size);

    for(int i = 0; i < size; i ++){
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
        free(P1[i]);
        free(P2[i]);
        free(P3[i]);
        free(P4[i]);
        free(P5[i]);
        free(P6[i]);
        free(P7[i]);
        free(temp1[i]);
        free(temp2[i]);
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
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);
    free(temp1);
    free(temp2);
}

int main(){
    srand(time(NULL));
    int **A, **B, **C;
    int numofadd = 0;
    int numofmul = 0;
    int numofsub = 0;
    A = malloc(sizeof(int *) * 4);
    B = malloc(sizeof(int *) * 4);
    C = malloc(sizeof(int *) * 4);
    for(int i = 0 ; i < 4 ; i ++){
        A[i] = malloc(sizeof(int) * 4);
        B[i] = malloc(sizeof(int) * 4);
        C[i] = malloc(sizeof(int) * 4);
    }
    createMatrix(A, 4);
    createMatrix(B, 4);
    printf("Matrix A is: \n");
    printMatrix(A, 4);
    printf("Matrix B is: \n");
    printMatrix(B, 4);
    Strassen(A, B, C, 4, &numofadd, &numofmul, &numofsub);
    printf("Matrix C is: \n");
    printMatrix(C, 4);
    printf("Number of multiplication: %d\n", numofmul);
    printf("Number of addition: %d\n", numofadd);
    printf("Number of subtraction: %d\n\n", numofsub);

    for(int i = 0 ; i < 4 ; i ++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}