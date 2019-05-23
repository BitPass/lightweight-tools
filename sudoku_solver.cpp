#include <stdio.h>
#define SIZE 9

// sample input matrices to test algo 
// can be rewritten to take an int ***p2Darr; 
int matrix[9][9] = {
    {8,0,0,0,0,0,0,0,0},
    {0,0,3,6,0,0,0,0,0},
    {0,7,0,0,9,0,2,0,0},
    {0,5,0,0,0,7,0,0,0},
    {0,0,0,0,4,5,7,0,0},
    {0,0,0,0,1,0,0,3,0},
    {0,0,1,0,0,0,0,6,8},
    {0,0,8,5,0,0,0,1,0},
    {0,9,0,0,0,0,4,0,0}
};


int number_unassigned(int *row, int *col)
{
    int num_unassign = 0;
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(matrix[i][j] == 0)
            {
                *row = i;
                *col = j;
                num_unassign = 1;
                return num_unassign;
            }
        }
    }
    return num_unassign;
}

int is_safe(int n, int r, int c)
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        if(matrix[r][i] == n)
            return 0;
    }
    for(i=0;i<SIZE;i++)
    {
        if(matrix[i][c] == n)
            return 0;
    }
    int row_start = (r/3)*3;
    int col_start = (c/3)*3;
    for(i=row_start;i<row_start+3;i++)
    {
        for(j=col_start;j<col_start+3;j++)
        {
            if(matrix[i][j]==n)
                return 0;
        }
    }
    return 1;
}

int solve_sudoku()
{
    int row;
    int col;
    if(number_unassigned(&row, &col) == 0)
        return 1;
    int n,i;
    for(i=1;i<=SIZE;i++)
    {
         if(is_safe(i, row, col))
        {
            matrix[row][col] = i;
            if(solve_sudoku())
                return 1;
            matrix[row][col]=0;
        }
    }
    return 0;
}

void print_sudoku()
{
    int i,j;

    printf("\n\n\n\n");
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            printf("%6d",matrix[i][j]);
        }
        printf("\n\n\n\n");
    }
}


int main()
{
    if (solve_sudoku())
        print_sudoku();
    else
        printf("No solution\n");
    return 0;
}
