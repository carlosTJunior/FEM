#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"
#include "FiniteDifferences.h"

int main()
{
	Vector myvector = NULL;
	Matrix mymatrix = NULL;
	Matrix myNewMatrix = NULL;
	int vectorDim = 4;
	int matrixDim = 4;
	int newMatrixDim = 5;

	myvector = LinearAlgebra_createVector( vectorDim );
	mymatrix = LinearAlgebra_createMatrix( matrixDim );

	LinearAlgebra_setNullMatrix( mymatrix, matrixDim );

	FiniteDifferences_generateDirichletMatrix( mymatrix, matrixDim );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	FiniteDifferences_generateDirichletVector( myvector, vectorDim, 1, 0 );
	LinearAlgebra_displayVector( myvector, vectorDim );

	FiniteDifferences_generateVonNeumannMatrix_BackwardDiff( mymatrix, matrixDim );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	myNewMatrix = FiniteDifferences_generateVonNeumannMatrix_CenteredDiff( matrixDim );

	LinearAlgebra_displayMatrix( myNewMatrix, newMatrixDim );

	return 0;
}
