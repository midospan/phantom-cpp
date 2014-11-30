#include "phantom/phantom.h"
#include "aabb3.h"
#include "aabb3.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), aabb3);
o_registerNTI((phantom, math), aabb3, (float));
o_registerNTI((phantom, math), aabb3, (double));

o_namespace_begin(phantom, math)

// Constants
template<>
const aabb3<float32> aabb3<float32>::INFINITE_VALUE
(
    vector3<float32>(std::numeric_limits<float32>::max(), std::numeric_limits<float32>::max(), std::numeric_limits<float32>::max()),
    vector3<float32>(std::numeric_limits<float32>::max(), std::numeric_limits<float32>::max(), std::numeric_limits<float32>::max())
);
	
template<>
const aabb3<float64> aabb3<float64>::INFINITE_VALUE
(
    vector3<float64>(std::numeric_limits<float64>::max(), std::numeric_limits<float64>::max(), std::numeric_limits<float64>::max()),
    vector3<float64>(std::numeric_limits<float64>::max(), std::numeric_limits<float64>::max(), std::numeric_limits<float64>::max())
);

o_namespace_end(phantom, math)
