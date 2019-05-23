/* general purpose serial(non-GPU) matrix multiplication functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
/*
array length macro
LEN(array) gives rows
LEN(array[0]) gives columns
*/

void zeroMatrix(float *aPtr, int Rows, int Cols);
void onesMatrix(float *aPtr, int Rows, int Cols);
void populateMatrix(float *aPtr, int Rows, int Cols);
void matrixPrint(float *p, int Rows, int Cols);
void matrixMultply(float *pA, float *pB, float *pX, int A_Rows, int A_Cols, int B_Rows, int B_Cols);

int main()
{
    int programOn = 0;

    int A_Rows;
    int A_Cols;
    int B_Rows;
    int B_Cols;
    int X_Rows;
    int X_Cols;
    int h;
    int w;
    static int depth;

    while(programOn == 0)
    {

        printf("Input number of rows for the first matrix : ");
        scanf("%d", &A_Rows);
        printf("Input number of columns for the first matrix : ");
        scanf("%d", &A_Cols);
        printf("Input number of rows for the second matrix : ");
        scanf("%d", &B_Rows);
        printf("Input number of columns for the second matrix : ");
        scanf("%d", &B_Cols);

        if(A_Cols != B_Rows)
        {
            puts("\n This matrix multiplication is undefined. \n A and B must have matching inner dimensions");
            continue;
        }

        X_Rows = A_Rows;
        X_Cols = B_Cols;
        depth = A_Cols; /* since A_Cols and B_Rows must be equal anyway, either one will do */
        float matrixA[A_Rows][A_Cols];
        float matrixB[B_Rows][B_Cols];
        float matrixX[A_Rows][B_Cols];    /* composition matrix */

        void *ptrA = &matrixA;
        void *ptrB = &matrixB;
        void *ptrX = &matrixX;

        printf("\n Enter inividual elements of Matrix A: \n");
        populateMatrix(ptrA, A_Rows, A_Cols);
        printf("\n Enter inividual elements of Matrix B: \n");
        populateMatrix(ptrB, B_Rows, B_Cols);
        zeroMatrix(ptrX, X_Rows, X_Cols);
        zeroMatrix(ptrX, X_Rows, X_Cols);
        matrixMultply(ptrA, ptrB, ptrX, A_Rows, A_Cols, B_Rows, B_Cols);
        matrixPrint(ptrX, X_Rows, X_Cols);
        //printf("\n Address of matrixA: %p\n", matrixA);
    }
    return 0;
}

void matrixMultply(float *pA, float *pB, float *pX, int A_Rows, int A_Cols, int B_Rows, int B_Cols)
{
    printf("\n Multiplication %p\n\n", pA);
    int Rows = A_Rows;
    int Cols = B_Cols;
    int depth = A_Cols;

    float operand1, operand2;
    float adderArray[depth];
    float tmp_add_register = 0.0f;
    float tmp_mul_register = 0.0f;
    int w, h, i;

	for(h = 0 ; h < Rows; h++)
    {
        for(w = 0; w < Cols; w++)
        {
            for(i = 0; i < depth; i++)
            {
                operand1 = 0.0f;
                operand2 = 0.0f;
                operand1 = *((float*)pA + (h * A_Cols) + i);
                operand2 = *((float*)pB + (i * B_Cols) + w);
                tmp_mul_register = operand1 * operand2;
                adderArray[i] = tmp_mul_register;
            }
            tmp_add_register = 0.0f; 
            for(i = 0; i < depth; i++)
            {
                tmp_add_register += adderArray[i];
            }
             *(pX + (w * Cols) + h) = tmp_add_register; 
        }
    }
}


void matrixPrint(float *p, int Rows, int Cols)
{
    int h, w;
    for(w = 0; w < Rows; w++) {
        putchar('\n');
        for(h = 0; h < Cols; h++) {
            printf("%4d.%4d  %10.3f", w+1, h+1, *(p + (h * Cols) + w));
        }
        putchar('\n');
        putchar('\n');
        putchar('\n');
        putchar('\n');
	}
}

void populateMatrix(float *aPtr, int Rows, int Cols)
{
    int w, h, val;
	for(h = 0 ; h < Rows; h++)
    {
        for(w = 0; w < Cols; w++)
        {
            printf("A [%d],[%d]: ", h + 1, w + 1);  
            scanf("%f", &val);
            *((int*)aPtr + (h * Cols) + w) = val;//    /* equivalent of A[h][w] = val         */
        }
    }
}

void zeroMatrix(float *aPtr, int Rows, int Cols)
{
    // printf("\n Zeroing matrix at address %p\n\n", aPtr);
    int w, h, val = 0;
	for(h = 0 ; h < Rows; h++)
    {
        for(w = 0; w < Cols; w++)
        {
            *(aPtr + (h * Cols) + w) = val;
        }
    }
}

void onesMatrix(float *aPtr, int Rows, int Cols)
{
    // printf("\n 1-ing the matrix at address %p\n\n", aPtr);
    int w, h, val = 1;
	for(h = 0 ; h < Rows; h++)
    {
        for(w = 0; w < Cols; w++)
        {
            *(aPtr + (h * Cols) + w) = val;
        }
    }
}

