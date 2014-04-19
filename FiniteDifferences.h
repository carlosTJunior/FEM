#ifndef _FINITE_DIFFERENCES
#define _FINITE_DIFFERENCES

#define BACKWARD_DIFF 1
#define CENTERED_DIFF 2 
#define FORWARD_DIFF 3

Matrix FiniteDifferences_generateDirichletMatrix( int, double );
Vector FiniteDifferences_generateDirichletVector( int , varType, varType );

Matrix FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( int, double );
Vector FiniteDifferences_generateVonNeumannVector_CenteredDiff( int, double, double, double );

Matrix FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( int, double );
Vector FiniteDifferences_generateVonNeumannVector_BackwardDiff( int, double, double, double );

int FiniteDifferences_solveDirichletProblem( int, double, double, double );
int FiniteDifferences_solveVonNeumannBackwardProblem( int, double, double, double );
int FiniteDifferences_solveVonNeumannCenteredProblem( int, double, double, double );

#endif
