#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

int main()
{
	Vector myvector = NULL;
	Matrix mymatrix = NULL;
	int vectorDim = 4;
	int matrixDim = 4;

	myvector = LinearAlgebra_createVector( vectorDim );
	mymatrix = LinearAlgebra_createMatrix( matrixDim );

	LinearAlgebra_setVectorElement( myvector, vectorDim, 0, 1 );
	LinearAlgebra_setVectorElement( myvector, vectorDim, 1, 0 );
	LinearAlgebra_setVectorElement( myvector, vectorDim, 2, 2 );
	LinearAlgebra_setVectorElement( myvector, vectorDim, 3, 1 );

	LinearAlgebra_setNullMatrix( mymatrix, matrixDim );

	FiniteDifferences_generateDirichletMatrix( mymatrix, matrixDim );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	FiniteDifferences_generateDirichletVector( myvector, vectorDim, 1, 0 );
	LinearAlgebra_displayVector( myvector, vectorDim );

	FiniteDifferences_generateVonNeumannMatrix( mymatrix, matrixDim, 1 );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	return 0;
}
