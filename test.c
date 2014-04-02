#include <stdio.h>
#include <stdlib.h>
#include "LinearAlgebra.h"

int main()
{
	Vector myvector = NULL;
	Matrix mymatrix = NULL;
	int vectorDim = 3;
	int matrixDim = 3;

	myvector = LinearAlgebra_createVector( vectorDim );
	mymatrix = LinearAlgebra_createMatrix( matrixDim );

	LinearAlgebra_setVectorElement( myvector, vectorDim, 0, 4 );
	LinearAlgebra_setVectorElement( myvector, vectorDim, 1, 5 );
	LinearAlgebra_setVectorElement( myvector, vectorDim, 2, 7 );

	LinearAlgebra_setNullMatrix( mymatrix, matrixDim );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 0, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 1, 3 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 0, 2, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 0, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 1, -2 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 1, 2, -1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 0, 2 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 1, 1 );
	LinearAlgebra_setMatrixElement( mymatrix, matrixDim, 2, 2, 2 );

	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	/*LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 1, 0, 2 );
	LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 2, 0, 3 );
	LinearAlgebra_subtractMatrixRows( mymatrix, matrixDim, 2, 1, -0.2);*/
	LinearAlgebra_gaussElimination( mymatrix, myvector, matrixDim );

	LinearAlgebra_displayVector( myvector, vectorDim );
	LinearAlgebra_displayMatrix( mymatrix, matrixDim );

	return 0;
}
