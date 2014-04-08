#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

int FiniteDifferences_generateDirichletMatrix( Matrix matrix, int n, double dtX )
{
	int row, column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter: FiniteDifferences_generateDirichletMatrix()\n" );
		exit(1);
	}

	for( row = 0; row < n; row++ )
	{
		for( column = 0; column < n; column++ )
		{
			if( row == column )
				matrix[row][column] = (dtX*dtX) - 2;
			else if( row - column == 1 || column - row == 1 )
				matrix[row][column] = 1;
			else
				matrix[row][column] = 0;
		}
	}

	return 0;
}

int
FiniteDifferences_generateDirichletVector( Vector vector, int n, varType F0, varType FL )
{
	int row;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter: FiniteDifferences_generateDirichletVector()\n" );
		exit(1);
	}

	for( row = 0; row < n; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= F0;
	vector[n - 1] -= FL;

	return 0;
}

int FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( Matrix matrix, int n, double dltX )
{
	int row, column;
	row = n - 1;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter: FiniteDifferences_auxMatrixBackwardDiff()\n" );
		exit(1);
	}
	FiniteDifferences_generateDirichletMatrix( matrix, n, dltX );

	for( column = 0; column < n; column++ )
	{
		matrix[row][column] = 0;
	}
	matrix[row][n - 1] = 1;
	matrix[row][n - 2] = -1;

	return 0;
}

int FiniteDifferences_generateVonNeumannVector_BackwardDiff( Vector vector, int n, double fi0, double dFiL, double dltX )
{
	int row;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter: FiniteDifferences_generateVonNeumannVector_BackwardDiff()\n" );
		exit(1);
	}

	for( row = 0; row < n; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= fi0;
	vector[n - 1] = dFiL * dltX;

	return 0;
}


Matrix FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( int n, double dltX )
{
	Matrix newMatrix = NULL;
	int row, column;

	newMatrix = LinearAlgebra_createMatrix( n );
	LinearAlgebra_setNullMatrix( newMatrix, n );
	FiniteDifferences_generateDirichletMatrix( newMatrix, n, dltX );
	for( row = n - 1, column = 0; column < n; column++ )
	{
		newMatrix[row][column] = 0;
	}

	newMatrix[n - 1][n - 1] = 1;
	newMatrix[n - 1][n - 3] = -1;

	return newMatrix;
}

int FiniteDifferences_generateVonNeumannVector_CenteredDiff( Vector vector, int n, double dltX, double fi0, double dFiL )
{
	int row;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter: FiniteDifferences_generateVonNeumannVector_CenteredDiff()\n" );
		exit(1);
	}

	for( row = 0; row < n; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= fi0;
	vector[n - 1] = dFiL * ( 2 * dltX );
	return 0;
}
