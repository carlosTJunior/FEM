#ifndef _FINITE_DIFFERENCES
#define _FINITE_DIFFERENCES

#define BACKWARD_DIFF 1
#define CENTERED_DIFF 2 

int FiniteDifferences_generateDirichletMatrix( Matrix, int );

int FiniteDifferences_generateVonNeumannMatrix( Matrix, int, int );

#endif
