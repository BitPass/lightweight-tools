/*4 dimensional array allocation and use */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10
#define N 10
#define O 10
#define P 10

int main()
{
    int ****A = (int****)malloc(sizeof(int***)*M);
    int i, j, k, m;
    srand((unsigned)time(NULL));

    if(A == NULL)
    {
        printf (" **** Out of Memory");
    }
    for(i = 0; i < M; i++)
    {
        A[i] = (int***)malloc(sizeof(int**)*N);
        if(A[i] == NULL)
        {
            printf(" *** Out of Memory");
        }
        for(j = 0; j < N; j++)
        {
            A[i][j] = (int**)malloc(sizeof(int*)*O);
            if(A[i][j] == NULL)
            {
                printf(" ** Out of Memory");
            }
            for(k = 0; k < O; k++)
            {
                A[i][j][k] = (int*)malloc(sizeof(int)*P);
                if(A[i][j][k] == NULL)
                {
                    printf(" * Out of Memory\n");
                }
                printf("Allocation: A[i][j][k] at %p, A[i][j]: %p, A[i]: %p, A: %p\n", A[i][j][k], A[i][j], A[i], A);
            }
        }
    }

    /* assign values */

    int x = 0;

    for (i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            for(k = 0; k < O; k++)
            {
                for(m = 0; m < P; m++)
                {
//                    A[i][j][k][m] = rand() % 256;
                    A[i][j][k][m] = x++;
                }
            }
        }
    }


// prints what the contents of multidim actually look like

    for (i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            for(k = 0; k < O; k++)
            {
                for(m = 0; m < P; m++)
                {
                     printf("%06d ", A[i][j][k][m]);
                }
                putchar('\n'); 
            }
            putchar('\n');
            puts("############################################################################");
            putchar('\n');
        }
        putchar('\n');
        puts("#######################################################################################################################################################");
        putchar('\n');
    }

    /* deallocate memory */

    for (i = 0; i < M; i++)
    {
        for (j = 0; j <	 N; j++)
        {
            for (k = 0; k < O; k++)
            {
                free(A[i][j][k]);
            }
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);

    return 0;
}
