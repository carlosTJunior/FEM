#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"
#include <math.h>

#define PI acos(-1)
#define L PI/2

int solveDirichletProblem( int, double, double, double );
int solveVonNeumannBackwardProblem( int, double, double, double );
int solveVonNeumannCenteredProblem( int, double, double, double );

int main()
{
	int n = 4;
	double deltaX = (double) L/n;
	double fi0 = 1;
	double fiL = 0;
	double dFiL = -1;
	printf( "deltaX: %f\n", deltaX );

	solveDirichletProblem( n, deltaX, fi0, fiL );
	solveVonNeumannCenteredProblem( n, deltaX, fi0, dFiL );
	solveVonNeumannBackwardProblem( n, deltaX, fi0, dFiL );

	return 0;
}


int solveDirichletProblem( int n, double deltaX, double fi0, double fiL )
{
	Matrix matrix1 = NULL;
	Vector vector1 = NULL;
	Vector solution = NULL;

	matrix1 = LinearAlgebra_createMatrix( n - 1 );
	LinearAlgebra_setNullMatrix( matrix1, n - 1 );
	FiniteDifferences_generateDirichletMatrix( matrix1, n - 1, deltaX );

	printf( "Solucao da equacao com as condicoes de contorno de Dirichlet\n\n");
	LinearAlgebra_displayMatrix( matrix1, n - 1 );

	vector1 = LinearAlgebra_createVector( n - 1 );
	FiniteDifferences_generateDirichletVector( vector1, n - 1, fi0, fiL );

	LinearAlgebra_displayVector( vector1, n - 1 );

	printf( "A solucao do Sistema Linear eh dada por\n\n" );

	solution = LinearAlgebra_createVector( n - 1 );

	solution = LinearAlgebra_solveLinearSystem( matrix1, vector1, n - 1 );

	LinearAlgebra_displayVector( solution, n - 1 );

	return 0;
}

int solveVonNeumannBackwardProblem( int n, double deltaX, double fi0, double dFiL )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;

	matrix = LinearAlgebra_createMatrix( n );
	LinearAlgebra_setNullMatrix( matrix, n );
	FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( matrix, n, deltaX );

	printf( "Solucao da equacao com as condicoes de contorno de Von Neumann, diferencas atrasadas\n\n" );
	LinearAlgebra_displayMatrix( matrix, n );

	vector = LinearAlgebra_createVector( n );
	FiniteDifferences_generateVonNeumannVector_BackwardDiff( vector, n, fi0, dFiL, deltaX );

	LinearAlgebra_displayVector( vector, n );

	printf( "A solucao do sistema linear eh dada por\n\n" );

	solution = LinearAlgebra_createVector( n );
	solution = LinearAlgebra_solveLinearSystem( matrix, vector, n );

	LinearAlgebra_displayVector( solution, n );	

	return 0;
}

int solveVonNeumannCenteredProblem( int n, double deltaX, double fi0, double dFiL )
{
	Matrix matrix = NULL;
	Vector vector = NULL;
	Vector solution = NULL;

	matrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( n + 1 , deltaX );

	printf( "Solucao da equacao com as condicoes de contorno de Von Neumann, diferencas centrais\n\n" );
	LinearAlgebra_displayMatrix( matrix, n + 1 );

	vector = LinearAlgebra_createVector( n + 1 );
	FiniteDifferences_generateVonNeumannVector_CenteredDiff( vector, n + 1, deltaX, fi0, dFiL );

	LinearAlgebra_displayVector( vector, n + 1 );

	printf( "A solucao do sistema linear eh dada por\n\n" );

	solution = LinearAlgebra_createVector( n + 1 );
	solution = LinearAlgebra_solveLinearSystem( matrix, vector, n );

	LinearAlgebra_displayVector( solution, n + 1 );
	return 0;
}
