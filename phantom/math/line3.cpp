#include "phantom/phantom.h"
#include "line3.h"
#include "line3.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), line3);
o_registerNTI((phantom, math), line3, (float));
o_registerNTI((phantom, math), line3, (double));

o_namespace_begin(phantom, math)

    // Special lines.
	template<>
    const line3<float32> line3<float32>::UNIT_X(vector3<float32>(0.0f, 0.0f, 0.0f), vector3<float32>(1.0f, 0.0f, 0.0f));
	template<>
    const line3<float32> line3<float32>::UNIT_Y(vector3<float32>(0.0f, 0.0f, 0.0f), vector3<float32>(0.0f, 1.0f, 0.0f));
    template<>
    const line3<float32> line3<float32>::UNIT_Z(vector3<float32>(0.0f, 0.0f, 0.0f), vector3<float32>(0.0f, 0.0f, 1.0f));

	template<>
    const line3<float64> line3<float64>::UNIT_X(vector3<float64>(0.0, 0.0, 0.0), vector3<float64>(1.0, 0.0, 0.0));
	template<>
    const line3<float64> line3<float64>::UNIT_Y(vector3<float64>(0.0, 0.0, 0.0), vector3<float64>(0.0, 1.0, 0.0));
    template<>
    const line3<float64> line3<float64>::UNIT_Z(vector3<float64>(0.0, 0.0, 0.0), vector3<float64>(0.0, 0.0, 1.0));
o_namespace_end(phantom, math)
