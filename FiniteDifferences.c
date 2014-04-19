#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

Matrix FiniteDifferences_generateDirichletMatrix( int dim, double dltX )
{
	Matrix matrix = NULL;
	int row, column, newDim = dim - 1;

	matrix = LinearAlgebra_createMatrix( newDim );
	LinearAlgebra_setNullMatrix( matrix, newDim );

	for( row = 0; row < newDim; row++ )
	{
		for( column = 0; column < newDim; column++ )
		{
			if( row == column )
				matrix[row][column] = (dltX*dltX) - 2;
			else if( row - column == 1 || column - row == 1 )
				matrix[row][column] = 1;
			else
				matrix[row][column] = 0;
		}
	}

	return matrix;
}

Vector
FiniteDifferences_generateDirichletVector( int dim, varType phi_0, varType phi_L )
{
	Vector vector = NULL;
	int row, newDim = dim - 1;

	vector = LinearAlgebra_createVector( newDim );

	for( row = 0; row < newDim; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= phi_0;
	vector[newDim - 1] -= phi_L;

	return vector;
}

Matrix FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( int dim, double dltX )
{
	Matrix matrix = NULL;
	int row, column;
	row = dim - 1;

	matrix = FiniteDifferences_generateDirichletMatrix( dim, dltX );

	for( column = 0; column < dim; column++ )
	{
		matrix[row][column] = 0;
	}
	matrix[row][dim - 1] = 1;
	matrix[row][dim - 2] = -1;

	return matrix;
}

Vector FiniteDifferences_generateVonNeumannVector_BackwardDiff( int dim, double phi_0, double dPhi_L, double dltX )
{
	Vector vector = NULL;
	int row;

	vector = LinearAlgebra_createVector( dim );
	for( row = 0; row < dim; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= phi_0;
	vector[dim - 1] = dPhi_L * dltX;

	return vector;
}


Matrix FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( int dim, double dltX )
{
	Matrix matrix = NULL;
	int row, column;

	matrix = FiniteDifferences_generateDirichletMatrix( dim, dltX );
	for( row = dim - 1, column = 0; column < dim; column++ )
	{
		matrix[row][column] = 0;
	}

	matrix[dim - 1][dim - 1] = 1;
	matrix[dim - 1][dim - 3] = -1;

	return matrix;
}

Vector FiniteDifferences_generateVonNeumannVector_CenteredDiff( int dim, double dltX, double phi_0, double dPhi_L )
{	
	Vector vector = NULL;
	int row;

	vector = LinearAlgebra_createVector( dim );
	for( row = 0; row < dim; row++ )
	{
		vector[row] = 0;
	}

	vector[0] -= phi_0;
	vector[dim - 1] = dPhi_L * ( 2 * dltX );
	return vector;
}

int FiniteDifferences_solveDirichletProblem( int dim, double deltaX, double phi_0, double phi_L )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;
	Vector dltVector = NULL;

	matrix = FiniteDifferences_generateDirichletMatrix( dim, deltaX );
	vector = FiniteDifferences_generateDirichletVector( dim, phi_0, phi_L );
	dltVector = LinearAlgebra_generateDeltaXVector( dim - 1, deltaX );

	printf( "Matrix A e vetor b ( Ax = b ) para o problema com C.C de Dirichlet\n\n" );

	LinearAlgebra_displayLinearSystem( matrix, vector, dim - 1 );

	printf( "A solucao (vetor x) do Sistema Linear eh dada por\n\n" );

	solution = LinearAlgebra_solveLinearSystem( matrix, vector, dim - 1 );

	LinearAlgebra_displayVector( solution, dim - 1 );

	LinearAlgebra_writeVectorsToFile( dltVector, solution, dim - 1);

	return 0;
}

int FiniteDifferences_solveVonNeumannBackwardProblem( int dim, double deltaX, double phi_0, double dPhi_L )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;
	Vector dltVector = NULL;

	matrix = FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( dim, deltaX );
	vector = FiniteDifferences_generateVonNeumannVector_BackwardDiff( dim, phi_0, dPhi_L, deltaX );
	dltVector = LinearAlgebra_generateDeltaXVector( dim, deltaX );

	printf( "A matriz A e o vetor b (Ax = b) para as C.C de Von Neumann, com diferencas atrasadas\n" );

	LinearAlgebra_displayLinearSystem( matrix, vector, dim );

	printf( "A solucao (vetor x) do sistema linear eh dada por\n\n" );

	solution = LinearAlgebra_solveLinearSystem( matrix, vector, dim );

	LinearAlgebra_displayVector( solution, dim );	

	LinearAlgebra_writeVectorsToFile( dltVector, solution, dim );

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

	matrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( dim, deltaX );
	vector = FiniteDifferences_generateVonNeumannVector_CenteredDiff( dim, deltaX, phi_0, dPhi_L );
	deltaVector = LinearAlgebra_generateDeltaXVector( dim, deltaX );

	printf( "A matriz A e o vetor b (Ax = b) para as C.C de Von Neumann, com diferencas centrais\n" );

	LinearAlgebra_displayLinearSystem( matrix, vector, dim );

	printf( "A solucao (vetor x) do sistema linear eh dada por\n\n" );

	solution = LinearAlgebra_solveLinearSystem( matrix, vector, dim );
	LinearAlgebra_displayVector( solution, dim );

	LinearAlgebra_writeVectorsToFile( deltaVector, solution, n );

	matrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( dim, deltaX );
	confere = LinearAlgebra_createVector( dim );
	confere = LinearAlgebra_matrixTimesVector( matrix, solution, dim );
	LinearAlgebra_displayVector( confere, dim );
	return 0;
}
