#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"
#include <math.h>

#define PI acos(-1)
#define L PI/2

FILE *file;

int main()
{
	int n = 32;
	double deltaX = (double) L/n;
	double fi0 = 1;
	double fiL = 0;
	double dFiL = -1;
	double x_i;
	int i;

	printf( "deltaX: %f\n", deltaX );
	printf( "Valores de x no intervalo\n" );
	for( i = 0; i < n; i++ )
	{
		x_i = i*deltaX;
		printf( "%f ", x_i );
	}
	printf( "\n" );

	/*solveDirichletProblem( n, deltaX, fi0, fiL );*/
	FiniteDifferences_solveVonNeumannCenteredProblem( n , deltaX, fi0, dFiL );
	/*solveVonNeumannBackwardProblem( n, deltaX, fi0, dFiL );*/

	return 0;
}
