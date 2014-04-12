#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"

extern FILE *file;

Vector LinearAlgebra_createVector( int n )
{
	int i;
	Vector vector = NULL;
	vector = malloc( n*sizeof( varType ) );
	if( !vector )
	{
		fprintf( stderr, "Impossible to allocate memory: LinearAlgebra_createVector()\n" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_setVectorElement()\n" );
		exit(1);
	}

	if( position > n )
	{
		fprintf( stderr, "Invalid Position(out of bounds): LinearAlgebra_setVectorElement()\n" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_displayVector()\n" );
		exit(2);
	}

	for( i = 0; i < n ; i++ )
	{
		printf( "[ %.4f ]\n", vector[i]);
	}
	printf( "\n" );
}

void
LinearAlgebra_writeVectorsToFile( Vector vectorX, Vector vectorY, int n )
{
	int i;

	if( !vectorX || !vectorY )
	{
		fprintf( stderr, "Invalid Parameters: LinearAlgebra_writeVectorToFile()\n" );
		exit(1);
	}

	file = fopen( "dados.txt", "w" );

	for( i = 0; i < n; i++ )
	{
		fprintf( file, "%f\t%f\n", vectorX[i], vectorY[i]);
	}
	fprintf( file, "\n\n" );

	fclose( file );
}

int LinearAlgebra_subtractVector( Vector vector1, Vector vector2, int dim )
{
	int row;
	if( !vector1 || !vector2 )
	{
		fprintf( stderr, "Invalid Parameters: LinearAlgebra_subtractVector()\n" );
		exit(1);
	}

	for( row = 0; row < dim; row++ )
	{
		vector1[row] -= vector2[row];
	}

	return 0;
}

int LinearAlgebra_generateDeltaXVector( Vector vector, int dim, double deltaX )
{
	int i;
	double sum = 0;
	if( !vector )
	{
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_generateDeltaXVector()\n" );
		exit(1);
	}

	for( i = 0; i < dim; i++ )
	{
		sum += deltaX;
		vector[i] = sum;
	}

	return 0;
}

Matrix LinearAlgebra_createMatrix( int n )
{
	int i;
	Matrix matrix = NULL;
	matrix = malloc( n*n*sizeof( varType ) );
	if( !matrix )
	{
		fprintf( stderr, "Impossible to allocate memory: LinearAlgebra_createMatrix()\n");
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_setNullMatrix()\n" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_displayMatrix()\n" );
		exit(2);
	}

	for( row = 0; row < n; row++ )
	{
		printf( "[ " );
		for( column = 0; column < n; column++ )
		{
			printf( "%.4f ", matrix[row][column] );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_setMatrixElement()\n" );
		exit(1);
	}

	if( row >= n || column >= n || row < 0 || column < 0 )
	{
		fprintf( stderr, "Invalid row or Column(out of bounds): LinearAlgebra_setMatrixElement()" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_subtractMatrixRows()\n" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_subtractVectorElement()\n" );
		exit(1);
	}

	if( resultRow > n || row > n )
	{
		fprintf( stderr, "Invalid elements(out of bounds): LinearAlgebra_subtractVectorElement()\n" );
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
		fprintf( stderr, "Invalid Parameter: LinearAlgebra_gaussElimination()\n" );
		exit(1);
	}

	for( refRow = 0 ; refRow < n - 1; refRow++)
	{
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

Vector LinearAlgebra_solveLinearSystem( Matrix matrix, Vector vector, int n )
{
	Vector solutionVector = NULL;
	int k, j;
	varType sum;
	if( !matrix || !vector )
	{
		fprintf( stderr,  "Invalid Parameters: LinearAlgebra_solveLinearSystem()\n" );
		exit(1);
	}

	LinearAlgebra_gaussElimination( matrix, vector, n );

	solutionVector = LinearAlgebra_createVector( n );

	solutionVector[n - 1] = vector[n - 1] / matrix[n - 1][n - 1];

	for( k = n - 2; k >= 0; k-- )
	{
		sum = vector[k];
		for( j = k + 1; j < n; j++ )
		{
			sum = sum - matrix[k][j] * solutionVector[j];
		}
		solutionVector[k] = sum / matrix[k][k];
	}

	return solutionVector;
}

Matrix LinearAlgebra_copyMatrix( Matrix matrix, int dim, int newDim )
{
	Matrix newMatrix = NULL;
	int row, column;
	if( !matrix )
	{
		fprintf( stderr, "Invalid Paramenter: LinearAlgebra_copyMatrix()\n" );
		exit(1);
	}
	if( newDim < dim )
	{
		fprintf( stderr, "Impossible to copy matrix: new dimension is less than actual dimension\n" );
		exit(2);
	}

	newMatrix = LinearAlgebra_createMatrix( newDim );
	LinearAlgebra_setNullMatrix( newMatrix, newDim );

	for( row = 0; row < dim; row++ )
	{
		for( column = 0; column < dim; column++ )
		{
			newMatrix[row][column] = matrix[row][column];
		}
	}

	return newMatrix;
}
