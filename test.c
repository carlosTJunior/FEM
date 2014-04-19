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
	int n = 4;
	double deltaX = (double) L/n;
	double fi0 = 1;
	double fiL = 0;
	double dFiL = -1;
	double x_i;
	int i, option = 1;

	printf( "\n\ndeltaX: %f\n", deltaX );
	printf( "Valores de x no intervalo\n" );
	for( i = 0; i < n; i++ )
	{
		x_i = i*deltaX;
		printf( "%f ", x_i );
	}
	printf( "\n\n" );

	switch( option )
	{
	case 1:
		FiniteDifferences_solveDirichletProblem( n, deltaX, fi0, fiL );
		break;
	case 2:
		FiniteDifferences_solveVonNeumannCenteredProblem( n , deltaX, fi0, dFiL );
		break;
	case 3:
		FiniteDifferences_solveVonNeumannBackwardProblem( n, deltaX, fi0, dFiL );
		break;
	default:
		printf( "Opcao invalida\n" );
		break;
	}

	return 0;
}
