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
FiniteDifferences_generateVonNeumannMatrix( Matrix matrix, int n, int method )
{
	int row, column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	FiniteDifferences_generateDirichletMatrix( matrix, n );

	if( method == BACKWARD_DIFF )
	{
		for( column = 0, row = n - 1; column < n; column++ )
		{
			matrix[row][column] = 0;
		}

		matrix[n - 1][n - 1] = 1;
		matrix[n - 1][n - 2] = -1;
	}

	return 0;
}
			
