#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

int FiniteDifferences_generateDirichletMatrix( Matrix matrix, int n, double dltX )
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
				matrix[row][column] = (dltX*dltX) - 2;
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

int FiniteDifferences_solveDirichletProblem( int n, double deltaX, double fi0, double fiL )
{
	Matrix matrix1 = NULL;
	Vector vector1 = NULL;
	Vector solution = NULL;
	Vector dltVector = NULL;

	dltVector = LinearAlgebra_createVector( n );

	matrix1 = LinearAlgebra_createMatrix( n - 1 );
	LinearAlgebra_setNullMatrix( matrix1, n - 1 );
	FiniteDifferences_generateDirichletMatrix( matrix1, n - 1, deltaX );

	printf( "Matrix A e vetor b ( Ax = b ) para o problema com C.C de Dirichlet\n" );
	LinearAlgebra_displayMatrix( matrix1, n - 1 );

	vector1 = LinearAlgebra_createVector( n - 1 );
	FiniteDifferences_generateDirichletVector( vector1, n - 1, fi0, fiL );

	LinearAlgebra_displayVector( vector1, n - 1 );

	printf( "A solucao (vetor x) do Sistema Linear eh dada por\n\n" );

	LinearAlgebra_generateDeltaXVector( dltVector, n, deltaX );

	solution = LinearAlgebra_createVector( n - 1 );

	solution = LinearAlgebra_solveLinearSystem( matrix1, vector1, n - 1 );

	LinearAlgebra_displayVector( solution, n - 1 );

	LinearAlgebra_writeVectorsToFile( dltVector, solution, n - 1);

	return 0;
}

int FiniteDifferences_solveVonNeumannBackwardProblem( int n, double deltaX, double fi0, double dFiL )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;
	Vector dltVector = NULL;

	dltVector = LinearAlgebra_createVector( n );

	matrix = LinearAlgebra_createMatrix( n );
	LinearAlgebra_setNullMatrix( matrix, n );
	FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( matrix, n, deltaX );

	printf( "A matriz A e o vetor b (Ax = b) para as C.C de Von Neumann, com diferencas atrasadas\n" );
	LinearAlgebra_displayMatrix( matrix, n );

	vector = LinearAlgebra_createVector( n );
	FiniteDifferences_generateVonNeumannVector_BackwardDiff( vector, n, fi0, dFiL, deltaX );

	LinearAlgebra_displayVector( vector, n );

	printf( "A solucao (vetor x) do sistema linear eh dada por\n\n" );

	LinearAlgebra_generateDeltaXVector( dltVector, n, deltaX );

	solution = LinearAlgebra_createVector( n );
	solution = LinearAlgebra_solveLinearSystem( matrix, vector, n );

	LinearAlgebra_displayVector( solution, n );	
	LinearAlgebra_writeVectorsToFile( dltVector, solution, n );

	return 0;
}

int FiniteDifferences_solveVonNeumannCenteredProblem( int n, double deltaX, double phi_0, double dPhi_L )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;
	Vector deltaVector = NULL;
	Vector confere = NULL;
	int dim = n + 1;

	deltaVector = LinearAlgebra_createVector( dim );
	matrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( dim, deltaX );

	vector = LinearAlgebra_createVector( dim );
	FiniteDifferences_generateVonNeumannVector_CenteredDiff( vector, dim, deltaX, phi_0, dPhi_L );

	LinearAlgebra_generateDeltaXVector( deltaVector, n, deltaX );

	LinearAlgebra_displayLinearSystem( matrix, vector, dim );

	solution = LinearAlgebra_createVector( dim );
	solution = LinearAlgebra_solveLinearSystem( matrix, vector, n - 1 );
	LinearAlgebra_displayVector( solution, dim );

	LinearAlgebra_writeVectorsToFile( deltaVector, solution, n );

	matrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( dim, deltaX );
	confere = LinearAlgebra_createVector( dim );
	confere = LinearAlgebra_matrixTimesVector( matrix, solution, dim );
	LinearAlgebra_displayVector( confere, dim );
	return 0;
}
	
