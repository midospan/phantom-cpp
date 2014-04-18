#include "phantom/phantom.h"
#include "vector2.h"

o_namespace_begin(phantom, math)
/** Constants **/
// Float
template<>
o_export const vector2<float> vector2<float>::ZERO(0.0f, 0.0f);
template<>
o_export const vector2<float> vector2<float>::UNIT_X(1.0f, 0.0f);
template<>
o_export const vector2<float> vector2<float>::UNIT_Y(0.0f, 1.0f);
template<>
o_export const vector2<float> vector2<float>::ONE(1.0f, 1.0f);
template<>
o_export const vector2<float> vector2<float>::IDENTITY(1.0f, 1.0f);
template<>
o_export const vector2<float> vector2<float>::INFINITE_VALUE
(
	std::numeric_limits<float>::max(),
	std::numeric_limits<float>::max()
	);
	
// Double
template<>
o_export const vector2<double> vector2<double>::ZERO(0.0, 0.0);
template<>
o_export const vector2<double> vector2<double>::UNIT_X(1.0, 0.0);
template<>
o_export const vector2<double> vector2<double>::UNIT_Y(0.0, 1.0);
template<>
o_export const vector2<double> vector2<double>::ONE(1.0, 1.0);
template<>
o_export const vector2<double> vector2<double>::IDENTITY(1.0, 1.0);
template<>
o_export const vector2<double> vector2<double>::INFINITE_VALUE
(
	std::numeric_limits<double>::max(),
	std::numeric_limits<double>::max()
	);

o_namespace_end(phantom, math)

