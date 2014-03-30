#ifndef _LINEAR_ALGEBRA
#define _LINEAR_ALGEBRA

typedef double varType;
typedef varType* Vector;
typedef varType** Matrix;

Vector LinearAlgebra_createVector( int );
void LinearAlgebra_displayVector( Vector, int );

Matrix LinearAlgebra_createMatrix( int );
int LinearAlgebra_setNullMatrix( Matrix, int );
int LinearAlgebra_setMatrixElement( Matrix, int, int, int, varType );
void LinearAlgebra_displayMatrix( Matrix, int );
int LinearAlgebra_subtractMatrixRows( Matrix, int, int, int, varType );
int LinearAlgebra_gaussElimination( Matrix, int );

#endif
