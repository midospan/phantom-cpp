#include "phantom/phantom.h"
#include "segment2.h"

o_namespace_begin(phantom, math)

/** Constants **/
template<>
const segment2<float32> segment2<float32>::ZERO(vector2<float32>(0.0f, 0.0f), vector2<float32>(0.0f, 0.0f));
template<>
const segment2<float32> segment2<float32>::UNIT_X(vector2<float32>(0.0f, 0.0f), vector2<float32>(1.0f, 0.0f));
template<>
const segment2<float32> segment2<float32>::UNIT_Y(vector2<float32>(0.0f, 0.0f), vector2<float32>(0.0f, 1.0f));
template<>
const segment2<float32> segment2<float32>::ONE(vector2<float32>(0.0f, 0.0f), vector2<float32>(1.0f, 1.0f));
	
template<>
const segment2<float64> segment2<float64>::ZERO(vector2<float64>(0.0, 0.0), vector2<float64>(0.0, 0.0));
template<>
const segment2<float64> segment2<float64>::UNIT_X(vector2<float64>(0.0, 0.0), vector2<float64>(1.0, 0.0));
template<>
const segment2<float64> segment2<float64>::UNIT_Y(vector2<float64>(0.0, 0.0), vector2<float64>(0.0, 1.0));
template<>
const segment2<float64> segment2<float64>::ONE(vector2<float64>(0.0, 0.0), vector2<float64>(1.0, 1.0));

o_namespace_end(phantom, math)
