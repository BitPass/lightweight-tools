#ifndef MATH_TOOLS
#define MATH_TOOLS

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void matrixPrint(GLfloat *p, int Rows, int Cols);
void makeTranslate (GLfloat* result, GLfloat x, GLfloat y, GLfloat z);
void makeIdentity (GLfloat* result);
void translateMatrixBy (GLfloat* result, GLfloat x, GLfloat y, GLfloat z);
void makePerspectiveMatrix (GLfloat* result, GLfloat fov, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);
void copyMatrix(GLfloat* src, GLfloat* dest); // try memcpy?	
void makeScale (GLfloat* result, GLfloat x, GLfloat y, GLfloat z);
void makeRotateX (GLfloat* result, GLfloat rotation);
void makeRotateY (GLfloat* result, GLfloat rotation);
void makeRotateZ (GLfloat* result, GLfloat rotation);
void matrixMult4x4 (GLfloat* result, GLfloat* m1, GLfloat* m2);
void matrixMultiply(GLfloat *pResultBuffer,GLfloat *pA, GLfloat *pB, int A_rows, int A_cols, int B_rows, int B_cols);
void makeIdentityAnysize(GLfloat *pMat, GLuint width);

#endif