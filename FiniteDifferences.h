#ifndef _FINITE_DIFFERENCES
#define _FINITE_DIFFERENCES

#define BACKWARD_DIFF 1
#define CENTERED_DIFF 2 
#define FORWARD_DIFF 3

int FiniteDifferences_generateDirichletMatrix( Matrix, int, double );
int FiniteDifferences_generateDirichletVector( Vector, int , varType, varType );

Matrix FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( int, double );
int FiniteDifferences_generateVonNeumannVector_CenteredDiff( Vector, int, double, double, double );

int FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( Matrix, int, double );
int FiniteDifferences_generateVonNeumannVector_BackwardDiff( Vector, int, double, double, double );

#endif
