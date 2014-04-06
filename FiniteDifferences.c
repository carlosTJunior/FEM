#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

int FiniteDifferences_generateDirichletMatrix( Matrix matrix, int n )
{
	int row, column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	for( row = 0; row < n; row++ )
	{
		for( column = 0; column < n; column++ )
		{
			if( row == column )
				matrix[row][column] = -2;
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
		fprintf( stderr, "Invalid Parameter\n" );
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

int FiniteDifferences_auxMatrixBackwardDiff( Matrix matrix, int n )
{
	int row, column;
	row = n - 1;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	for( column = 0; column < n; column++ )
	{
		matrix[row][column] = 0;
	}
	matrix[row][n - 1] = 1;
	matrix[row][n - 2] = -1;

	return 0;
}

int
FiniteDifferences_generateVonNeumannMatrix( Matrix matrix, int n, int method )
{
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	FiniteDifferences_generateDirichletMatrix( matrix, n );

	if( method == BACKWARD_DIFF )
	{
		FiniteDifferences_auxMatrixBackwardDiff( matrix, n );
	}
	else if( method == FORWARD_DIFF )
	{

	}
	else if( method == CENTERED_DIFF )
	{

	}
	else
	{

	}

	return 0;
}
			
