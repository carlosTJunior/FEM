#ifndef _LINEAR_SYS
#define _LINEAR_SYS

typedef int varType;
typedef varType* Vector;
typedef varType** Matrix;

Vector LinearSystem_createVector( int );
void LinearSystem_displayVector( Vector, int );

Matrix LinearSystem_createMatrix( int );
int LinearSystem_setNullMatrix( Matrix, int );
void LinearSystem_displayMatrix( Matrix, int );

#endif
