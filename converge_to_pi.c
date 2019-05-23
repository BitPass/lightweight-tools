/*

C Program to Compute pi
From Ryan Dahl's "Favorite Math Proofs"
https://tinyclouds.org/math/favorite-proofs.pdf

By picking points randomly from a square one can calculuate
pi. Keep track of how many points from the square you pick
lay in the inscribed circle. Supposing the square’s edges are
length 2, then the inscribed circle has radius 1. Thus the area
of the circle is pi*r^2 = pi. The area of the square is 4. The ratio
of points picked from the circle to the total number of picked
points will converge to pi/4.
This is a C program to demonstrate the convergence.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main(void) 
{
	unsigned int total=0, inside=0;
	while(1) 
		{
			float x = (float)rand() / RAND_MAX;
			float y = (float)rand() / RAND_MAX;
			total++;
			if(sqrt(x*x + y*y) < 1) inside++;
			printf("%f\n", 4.0 * inside / total);
		}
}
