#ifndef _LINEAR_ALGEBRA
#define _LINEAR_ALGEBRA

typedef double varType;
typedef varType* Vector;
typedef varType** Matrix;

/*Functions to manipulate vectors*/
Vector LinearAlgebra_createVector( int );
int LinearAlgebra_setVectorElement( Vector, int, int, varType );
void LinearAlgebra_displayVector( Vector, int );
void LinearAlgebra_writeVectorsToFile( Vector, Vector, int n );
int LinearAlgebra_subtractVectorElements( Vector, int, int, int, varType );
Vector LinearAlgebra_subtractTwoVectors( Vector, Vector, int );
Vector LinearAlgebra_generateDeltaXVector( int, double );

/*Functions to manipulate matrices*/
Matrix LinearAlgebra_createMatrix( int );
int LinearAlgebra_setNullMatrix( Matrix, int );
int LinearAlgebra_setMatrixElement( Matrix, int, int, int, varType );
void LinearAlgebra_displayMatrix( Matrix, int );
int LinearAlgebra_subtractMatrixRows( Matrix, int, int, int, varType );
int LinearAlgebra_gaussElimination( Matrix, Vector, int );

/*Functions that manipulate matrices and vectors*/
Vector LinearAlgebra_matrixTimesVector( Matrix, Vector, int );
Vector LinearAlgebra_solveLinearSystem( Matrix, Vector, int );
void LinearAlgebra_displayLinearSystem( Matrix, Vector, int );

#endif
