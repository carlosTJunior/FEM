#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"

int main()
{
	Vector myvector = NULL;
	Vector solution = NULL;
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
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 0, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 1, 2 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 2, 3 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 3, 4 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 0, 4 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 1, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 2, 3 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 3, 0 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 0, 2 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 1, 5 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 2, 4 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 3, 3 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 3, 0, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 3, 1, 0 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 3, 2, 2 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 3, 3, 1 );

	LinearAlgebra_displayMatrix( mymatrix, matrixDim );
	LinearAlgebra_displayVector( myvector, vectorDim );
/*	LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 1, 0, 2 );
	LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 2, 0, 3 );
	LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 2, 1, -0.2);
	LinearAlgebra_gaussElimination( mymatrix, myvector, matrixDim );*/

	solution = LinearAlgebra_solveLinearSystem( mymatrix, myvector, vectorDim );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );
	LinearAlgebra_displayVector( myvector, vectorDim );
	LinearAlgebra_displayVector( solution, vectorDim );

	return 0;
}
