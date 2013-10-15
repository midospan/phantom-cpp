#include "phantom/phantom.h"
#include "phantom/math/math.h"

o_namespace_begin(phantom, math)

    //  constants
const float matrix3x3<float>::msSvdEpsilon = 1e-04f;
const unsigned int matrix3x3<float>::msSvdMaxIterations = 32;

const double matrix3x3<double>::msSvdEpsilon = 1e-04;
const unsigned int matrix3x3<double>::msSvdMaxIterations = 32;

o_namespace_end(phantom, math)