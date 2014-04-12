#ifndef _LINEAR_ALGEBRA
#define _LINEAR_ALGEBRA

typedef double varType;
typedef varType* Vector;
typedef varType** Matrix;

Vector LinearAlgebra_createVector( int );
int LinearAlgebra_setVectorElement( Vector, int, int, varType );
void LinearAlgebra_displayVector( Vector, int );
void LinearAlgebra_writeVectorsToFile( Vector, Vector, int n );
int LinearAlgebra_subtractVectorElements( Vector, int, int, int, varType );
int LinearAlgebra_subtractVector( Vector, Vector, int );
int LinearAlgebra_generateDeltaXVector( Vector, int, double );

Matrix LinearAlgebra_createMatrix( int );
int LinearAlgebra_setNullMatrix( Matrix, int );
int LinearAlgebra_setMatrixElement( Matrix, int, int, int, varType );
void LinearAlgebra_displayMatrix( Matrix, int );
int LinearAlgebra_subtractMatrixRows( Matrix, int, int, int, varType );
int LinearAlgebra_gaussElimination( Matrix, Vector, int );

Vector LinearAlgebra_gaussSeidel( Matrix, Vector, int );

Matrix LinearAlgebra_copyMatrix( Matrix, int, int );

Vector LinearAlgebra_solveLinearSystem( Matrix, Vector, int );

#endif
