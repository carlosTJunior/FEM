#ifndef _FINITE_DIFFERENCES
#define _FINITE_DIFFERENCES

#define BACKWARD_DIFF 1
#define CENTERED_DIFF 2 
#define FORWARD_DIFF 3

int FiniteDifferences_generateDirichletMatrix( Matrix, int );
int FiniteDifferences_generateDirichletVector( Vector, int , varType, varType );

Matrix FiniteDifferences_auxMatrixCenteredDiff( Matrix, int );
int FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( Matrix, int );
int FiniteDifferences_generateVonNeumannVector( Vector, int, varType, varType );

#endif
