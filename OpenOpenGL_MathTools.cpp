/* OpenOpenGL_MathTools.cpp */

#include "OpenOpenGL_MathTools.h"


/* matrix mul 4x4 case translated form Jeff Chastine's openGL series */
#define T0 0
#define T1 4
#define T2 8
#define T3 12
#define T4 1
#define T5 5
#define T6 9
#define T7 13
#define T8 2
#define T9 6
#define T10 10
#define T11 14
#define T12 3
#define T13 7
#define T14 11
#define T15 15

/* general case - slower than matrixMult4x4 and takes more arguments*/
void matrixMultiply(GLfloat *pResultBuffer,GLfloat *pA, GLfloat *pB, int A_rows, int A_cols, int B_rows, int B_cols)
{
	memset(pResultBuffer, 0.0f, ((A_rows*B_cols)*sizeof(GLfloat)));
    int i, j, k, m, n, p;
    int idxA, idxB, idxResult;
    m = A_rows;
    k = A_cols; // or B rows aka depth
    n = B_cols;
    for (i = 0; i < m; i++) // for each row in result matrix
    {
        for (j = 0; j < n; j++) // for each col in result matrix
        {
            for (p = 0; p < k; p++)
            {  // C(i, j) += A(i, p) * B(p, j);
                idxA = (i * A_cols) + p;    // recalculate linear index from 2D cell location
                idxB = (p * B_cols) + j;
                idxResult = (i * B_cols) + j;
                *(pResultBuffer + idxResult) += ((*(pA + idxA)) * (*(pB + idxB)));
            }
        }
  }
}

void matrixMult4x4 (GLfloat *result, GLfloat *m1, GLfloat *m2)
{
	for (int i = 0; i < 16; i++) {
		result[i] = 0.0f;
	}
	result[0] = m1[0]*m2[0]+m1[1]*m2[4]+m1[2]*m2[8]+m1[3]*m2[12];
	result[1] = m1[0]*m2[1]+m1[1]*m2[5]+m1[2]*m2[9]+m1[3]*m2[13];
	result[2] = m1[0]*m2[2]+m1[1]*m2[6]+m1[2]*m2[10]+m1[3]*m2[14];
	result[3] = m1[0]*m2[3]+m1[1]*m2[7]+m1[2]*m2[11]+m1[3]*m2[15];

	result[4] = m1[4]*m2[0]+m1[5]*m2[4]+m1[6]*m2[8]+m1[7]*m2[12];
	result[5] = m1[4]*m2[1]+m1[5]*m2[5]+m1[6]*m2[9]+m1[7]*m2[13];
	result[6] = m1[4]*m2[2]+m1[5]*m2[6]+m1[6]*m2[10]+m1[7]*m2[14];
	result[7] = m1[4]*m2[3]+m1[5]*m2[7]+m1[6]*m2[11]+m1[7]*m2[15];

	result[8] = m1[8]*m2[0]+m1[9]*m2[4]+m1[10]*m2[8]+m1[11]*m2[12];
	result[9] = m1[8]*m2[1]+m1[9]*m2[5]+m1[10]*m2[9]+m1[11]*m2[13];
	result[10] = m1[8]*m2[2]+m1[9]*m2[6]+m1[10]*m2[10]+m1[11]*m2[14];
	result[11] = m1[8]*m2[3]+m1[9]*m2[7]+m1[10]*m2[11]+m1[11]*m2[15];

	result[12] = m1[12]*m2[0]+m1[13]*m2[4]+m1[14]*m2[8]+m1[15]*m2[12];
	result[13] = m1[12]*m2[1]+m1[13]*m2[5]+m1[14]*m2[9]+m1[15]*m2[13];
	result[14] = m1[12]*m2[2]+m1[13]*m2[6]+m1[14]*m2[10]+m1[15]*m2[14];
	result[15] = m1[12]*m2[3]+m1[13]*m2[7]+m1[14]*m2[11]+m1[15]*m2[15];
}


void makeIdentity(GLfloat* pMat)
{
	int i, j = 0;
	int width = 4;
	int n = width * width;
	
	for(i = 0; i < n; i++) {
		pMat[i] = 0.0f;
	}

	for(i = 0; i < width; i++) {
		j = i*(width + 1);
		pMat[j] = 1.0f;
	}
}


void makeIdentityAnysize(GLfloat *pMat, GLuint width)
{
	int i, j = 0;
	int n = width * width;
		
	for(i = 0; i < n; i++) {
		pMat[i] = 0.0f;
	}

	for(i = 0; i < width; i++)
	{
		j = i*(width + 1);
		printf("%d\n", j);
	}
}




void makeRotateX (GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[5] = result[10] = cos(rotation);
	result[6] = sin(rotation);
	result[9] = -result[6];
}
void makeRotateY (GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[0] = result[10] = cos(rotation);
	result[2] = -sin(rotation);
	result[8] = -result[2];
}
void makeRotateZ (GLfloat* result, GLfloat rotation)
{
	makeIdentity(result);
	result[0] = result[5] = cos(rotation);
	result[1] = sin(rotation);
	result[4] = -result[1];
}

void makeScale(GLfloat* result, GLfloat x, GLfloat y, GLfloat z) 
{
	makeIdentity (result);
	result [0] = x;
	result [5] = y;
	result [10] = z;
}

void makePerspectiveMatrix (GLfloat* pMatrix, GLfloat fov, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane) 
{
	makeIdentity(pMatrix);
	GLfloat f = 1.0f/(tan(fov*(3.1415926f/360.0f)));
	pMatrix[0] = f / aspect;
	pMatrix[5] = f;
	pMatrix[10] = ((farPlane + nearPlane)/(nearPlane - farPlane));
	pMatrix[11] = -1;
	pMatrix[14] = (2.0f * farPlane * nearPlane)/(nearPlane - farPlane);
	pMatrix[15] = 0;
}

void translateMatrixBy (GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	result[3] += x;
	result[7] += y;
	result[11] += z;
}

void copyMatrix (GLfloat* src, GLfloat* dest)
{
	for (int i = 0; i < 16; i++) {
		dest[i] = src[i];
	}
}

void print4x4Matrix(GLfloat* mat)
{
	printf ("====================================");
	for (int i = 0; i < 16; i++) {
		if (i%4 == 0) printf ("\n");
		printf ("%f\t", mat[i]);
	}
	printf ("\n");
}

void matrixPrint(GLfloat *pM, int Rows, int Cols)
{
    int h, w;
    for(h = 0; h < Rows; h++)
    {
        putchar('\n');
        for(w = 0; w < Cols; w++)
        {
            printf(" %10.5f", *(pM + (h * Cols) + w));
        }
        putchar('\n');
        putchar('\n');
        putchar('\n');
	}
	putchar('\n');
}


void makeTranslate (GLfloat* result, GLfloat x, GLfloat y, GLfloat z)
{
	makeIdentity(result);
	result[3] = x;
	result[7] = y;
	result[11] = z;
}
