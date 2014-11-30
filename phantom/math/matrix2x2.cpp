#include "phantom/phantom.h"
#include "matrix2x2.h"
#include "matrix2x2.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), matrix2x2);
o_registerNTI((phantom, math), matrix2x2, (float));
o_registerNTI((phantom, math), matrix2x2, (double));

o_namespace_begin(phantom, math)

    /** Constants **/
template<>
const matrix2x2<float> matrix2x2<float>::ZERO(true);
	
template<>
const matrix2x2<float> matrix2x2<float>::IDENTITY(false);
	
template<>
const matrix2x2<double> matrix2x2<double>::ZERO(true);
	
template<>
const matrix2x2<double> matrix2x2<double>::IDENTITY(false);

o_namespace_end(phantom, math)