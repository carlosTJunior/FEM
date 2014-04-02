#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"

Vector LinearAlgebra_createVector( int n )
{
	int i;
	Vector vector = NULL;
	vector = malloc( n*sizeof( varType ) );
	if( !vector )
	{
		fprintf( stderr, "Impossible to allocate memory\n" );
		exit(1);
	}

	for( i = 0; i < n ; i++ )
	{
		vector[i] = 0;
	}

	return vector;
}

int LinearAlgebra_setVectorElement( Vector vector, int n, int position, varType value )
{
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	if( position > n )
	{
		fprintf( stderr, "Invalid Position\n" );
		exit(2);
	}

	vector[position] = value;

	return 0;
}

void LinearAlgebra_displayVector( Vector vector, int n )
{
	int i;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(2);
	}

	for( i = 0; i < n ; i++ )
	{
		printf( "[ %.2f ]\n", vector[i]);
	}
	printf( "\n" );
}

Matrix LinearAlgebra_createMatrix( int n )
{
	int i;
	Matrix matrix = NULL;
	matrix = malloc( n*n*sizeof( varType ) );
	if( !matrix )
	{
		fprintf( stderr, "Impossible to allocate memory\n");
		exit(1);
	}

	for( i = 0; i < n; i++ )
	{
		matrix[i] = malloc( n*sizeof( varType ) );
	}

	return matrix;
}

int LinearAlgebra_setNullMatrix( Matrix matrix, int n )
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
			matrix[row][column] = 0;
		}
	}

	return 0;
}

void LinearAlgebra_displayMatrix( Matrix matrix, int n )
{
	int row, column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(2);
	}

	for( row = 0; row < n; row++ )
	{
		printf( "[ " );
		for( column = 0; column < n; column++ )
		{
			printf( "%.2f ", matrix[row][column] );
		}

		printf( "]\n" );
	}

	printf( "\n" );
}

int
LinearAlgebra_setMatrixElement( Matrix matrix, int n, int row, int column, varType value )
{
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	if( row >= n || column >= n || row < 0 || column < 0 )
	{
		fprintf( stderr, "Invalid row or Column" );
		exit(3);
	}

	matrix[row][column] = value;

	return 0;
}

int
LinearAlgebra_subtractMatrixRows( Matrix matrix, int n, int resultRow, int row, varType coeficient )
{
	int column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	for( column = 0; column < n; column++ )
	{
		matrix[resultRow][column] -= coeficient * matrix[row][column];
	}

	return 0;
}

int
LinearAlgebra_subtractVectorElements( Vector vector, int n, int resultRow, int row, varType coeficient )
{
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	if( resultRow > n || row > n )
	{
		fprintf( stderr, "Invalid elements\n" );
		exit(2);
	}

	vector[resultRow] = vector[resultRow] - coeficient*vector[row];

	return 0;
}

int LinearAlgebra_gaussElimination( Matrix matrix, Vector vector, int n )
{
	int row, refRow, refColumn;
	varType baseElement;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(1);
	}

	for( refRow = 0 ; refRow < n - 1; refRow++)
	{
		row = refRow + 1;
		refColumn = refRow;

		for( row = refRow + 1; row < n; row++ )
		{
			baseElement = matrix[row][refColumn] / matrix[refRow][refColumn];
			LinearAlgebra_subtractMatrixRows( matrix, n, row, refRow, baseElement );
			LinearAlgebra_subtractVectorElements( vector, n, row, refRow, baseElement );
		}
	}
	
	return 0;
}
