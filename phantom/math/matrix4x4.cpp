#include "phantom/phantom.h"
#include "matrix4x4.h"

o_namespace_begin(phantom, math)

/** Constants **/
template<>
const matrix4x4<float> matrix4x4<float>::ZERO(true);

template<>
const matrix4x4<float> matrix4x4<float>::IDENTITY(false);

template<>
const matrix4x4<double> matrix4x4<double>::ZERO(true);

template<>
const matrix4x4<double> matrix4x4<double>::IDENTITY(false);

o_namespace_end(phantom, math)
