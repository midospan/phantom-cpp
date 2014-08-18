#include "phantom/phantom.h"
#include "vector3.h"

o_namespace_begin(phantom, math)

	/** Constants **/
	template<>
	o_export const vector3<float> vector3<float>::ZERO(0.0f, 0.0f, 0.0f);
	template<>
	o_export const vector3<float> vector3<float>::UNIT_X(1.0f, 0.0f, 0.0f);
	template<>
	o_export const vector3<float> vector3<float>::UNIT_Y(0.0f, 1.0f, 0.0f);
	template<>
	o_export const vector3<float> vector3<float>::UNIT_Z(0.0f, 0.0f, 1.0f);
	template<>
	o_export const vector3<float> vector3<float>::ONE(1.0f, 1.0f, 1.0f);
	template<>
	o_export const vector3<float> vector3<float>::INFINITE_VALUE
	(
	 std::numeric_limits<float>::max(),
	 std::numeric_limits<float>::max(),
	 std::numeric_limits<float>::max()
	 );
	
	template<>
	o_export const vector3<double> vector3<double>::ZERO(0.0, 0.0, 0.0);
	template<>
	o_export const vector3<double> vector3<double>::UNIT_X(1.0, 0.0, 0.0f);
	template<>
	o_export const vector3<double> vector3<double>::UNIT_Y(0.0, 1.0, 0.0);
	template<>
	o_export const vector3<double> vector3<double>::UNIT_Z(0.0, 0.0, 1.0);
	template<>
	o_export const vector3<double> vector3<double>::ONE(1.0, 1.0, 1.0);
	template<>
	o_export const vector3<double> vector3<double>::INFINITE_VALUE
	(
	 std::numeric_limits<double>::max(),
	 std::numeric_limits<double>::max(),
	 std::numeric_limits<double>::max()
	 );

    o_export const vector3<int> vector3<int>::ZERO(0, 0, 0);
    o_export const vector3<int> vector3<int>::UNIT_X(1, 0, 0);
    o_export const vector3<int> vector3<int>::UNIT_Y(0, 1, 0);
    o_export const vector3<int> vector3<int>::UNIT_Z(0, 0, 1);
    o_export const vector3<int> vector3<int>::ONE(1, 1, 1);
    o_export const vector3<int> vector3<int>::INFINITE_VALUE
        (
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
        );

o_namespace_end(phantom, math)