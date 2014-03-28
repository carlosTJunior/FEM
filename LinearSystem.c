#include <stdio.h>
#include <stdlib.h>
#include "LinearSystem.h"

Vector LinearSystem_createVector( int n )
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

void LinearSystem_displayVector( Vector vector, int n )
{
	int i;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter\n" );
		exit(2);
	}

	for( i = 0; i < n ; i++ )
	{
		printf( "[ %d ]\n", vector[i]);
	}
	printf( "\n" );
}

Matrix LinearSystem_createMatrix( int n )
{
	int i;
	Matrix matrix = NULL;
	matrix = malloc( n*sizeof( varType ) );
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

int LinearSystem_setNullMatrix( Matrix matrix, int n )
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

void LinearSystem_displayMatrix( Matrix matrix, int n )
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
			printf( "%d ", matrix[row][column] );
		}

		printf( "]\n" );
	}

	printf( "\n" );
}
