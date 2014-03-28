#include <stdio.h>
#include <stdlib.h>
#include "LinearSystem.h"

int main()
{
	Vector myvector = NULL;
	Matrix mymatrix = NULL;
	int vectorDim = 6;
	int matrixDim = 4;

	myvector = LinearSystem_createVector( vectorDim );
	mymatrix = LinearSystem_createMatrix( matrixDim );

	LinearSystem_setNullMatrix( mymatrix, matrixDim );

	LinearSystem_displayVector( myvector, vectorDim );

	LinearSystem_displayMatrix( mymatrix, matrixDim );

	return 0;
}
