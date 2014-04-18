#include "phantom/phantom.h"
#include "matrix3x3.h"

o_namespace_begin(phantom, math)

    /// Constants
	template<>
	const matrix3x3<float> matrix3x3<float>::ZERO(true);
	template<>
	const matrix3x3<float> matrix3x3<float>::IDENTITY(false);
	
	template<>
	const matrix3x3<double> matrix3x3<double>::ZERO(true);
	template<>
    const matrix3x3<double> matrix3x3<double>::IDENTITY(false);

    /*
    const float matrix3x3<float>::SVD_EPSILON = 1e-04f;
    const unsigned int matrix3x3<float>::SVD_MAX_ITERATIONS = 32;

    const double matrix3x3<double>::SVD_EPSILON = 1e-04;
    const unsigned int matrix3x3<double>::SVD_MAX_ITERATIONS = 32;*/

o_namespace_end(phantom, math)