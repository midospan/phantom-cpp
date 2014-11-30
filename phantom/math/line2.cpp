#include "phantom/phantom.h"
#include "line2.h"
#include "line2.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), line2);
o_registerNTI((phantom, math), line2, (float));
o_registerNTI((phantom, math), line2, (double));

o_namespace_begin(phantom, math)

// Special lines.
template<>
const line2<float32> line2<float32>::UNIT_X(vector2<float32>(0.0f, 0.0f), vector2<float32>(1.0f, 0.0f));
template<>
const line2<float32> line2<float32>::UNIT_Y(vector2<float32>(0.0f, 0.0f), vector2<float32>(0.0f, 1.0f));
	
template<>
const line2<float64> line2<float64>::UNIT_X(vector2<float64>(0.0, 0.0), vector2<float64>(1.0, 0.0));
template<>
const line2<float64> line2<float64>::UNIT_Y(vector2<float64>(0.0, 0.0), vector2<float64>(0.0, 1.0));

o_namespace_end(phantom, math)
