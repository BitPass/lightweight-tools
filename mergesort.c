/*
Classic Lightweight Mergesort
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 20


void stitch(int *A, int *L, int Lsize, int *R, int Rsize)
{
	int Lct, Rct, Act;
	Lct = 0; Rct = 0; Act = 0;
	while((Lct < Lsize) && (Rct < Rsize))
	{
		if(L[Lct] > R[Rct])
		{
			A[Act++] = L[Lct++];
		}
		else
		{
			A[Act++] = R[Rct++];
		}
	}
	while(Lct < Lsize)  A[Act++] = L[Lct++];
	while(Rct < Rsize)  A[Act++] = R[Rct++];
}

void mergesort(int *A, const int n)
{
	if(n < 2) return;
	int mid, i, *L, *R;
	mid = n/2;
	L = malloc(mid * sizeof(int));
	R = malloc((n - mid)*sizeof(int));
	for(i = 0;    i < mid;  i++)  L[i]     = A[i];
	for(i = mid;  i < n;    i++)  R[i-mid] = A[i];
	mergesort(L, mid);
	mergesort(R, n - mid);
	stitch(A, L, mid, R, n-mid);
	free(L);
	free(R);
}

void printarr(int *A, const int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%8d\n", A[i]);
}


int main()
{
	srand((unsigned)time(NULL));
	int i, A[SIZE];
	for(i = 0; i < SIZE; i++)
		A[i] = rand() % 100;
	printarr(A, SIZE);
	mergesort(A, SIZE);
	puts("\n\n");
	printarr(A, SIZE);
	return 0;
}
