#include "phantom/phantom.h"
#include "matrix4x4.h"
#include "matrix4x4.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), matrix4x4);
o_registerNTI((phantom, math), matrix4x4, (float));
o_registerNTI((phantom, math), matrix4x4, (double));

o_namespace_begin(phantom, math)

/** Constants **/
template<>
const matrix4x4<float> matrix4x4<float>::ZERO(true);

template<>
const matrix4x4<float> matrix4x4<float>::IDENTITY(false);

template<>
float matrix4x4<float>::PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT = 0.00001f;

template<>
const matrix4x4<double> matrix4x4<double>::ZERO(true);

template<>
const matrix4x4<double> matrix4x4<double>::IDENTITY(false);

template<>
double matrix4x4<double>::PROJECTION_INFINITE_FAR_PLANE_ADJUSTMENT = 0.00001;

o_namespace_end(phantom, math)
