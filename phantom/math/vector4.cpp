#include "phantom/phantom.h"
#include "vector4.h"

o_namespace_begin(phantom, math)

/** Constants **/
template<>
o_export const vector4<float> vector4<float>::ZERO(0.0f,0.0f,0.0f,0.0f);
template<>
o_export const vector4<float> vector4<float>::UNIT_X(1.0f,0.0f,0.0f,0.0f);
template<>
o_export const vector4<float> vector4<float>::UNIT_Y(0.0f,1.0f,0.0f,0.0f);
template<>
o_export const vector4<float> vector4<float>::UNIT_Z(0.0f,0.0f,1.0f,0.0f);
template<>
o_export const vector4<float> vector4<float>::UNIT_W(0.0f,0.0f,0.0f,1.0f);
template<>
o_export const vector4<float> vector4<float>::ONE(1.0f,1.0f,1.0f,1.0f);
	
template<>
o_export const vector4<double> vector4<double>::ZERO(0.0,0.0,0.0,0.0);
template<>
o_export const vector4<double> vector4<double>::UNIT_X(1.0,0.0,0.0,0.0);
template<>
o_export const vector4<double> vector4<double>::UNIT_Y(0.0,1.0,0.0,0.0);
template<>
o_export const vector4<double> vector4<double>::UNIT_Z(0.0,0.0,1.0,0.0);
template<>
o_export const vector4<double> vector4<double>::UNIT_W(0.0,0.0,0.0,1.0);
template<>
o_export const vector4<double> vector4<double>::ONE(1.0,1.0,1.0,1.0);

o_namespace_end(phantom, math)