#include "phantom/phantom.h"
#include "phantom/math/math.h"
#include "phantom/math/math.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), vector2);
o_registerNT((phantom, math), (typename), (t_Ty), vector3);
o_registerNT((phantom, math), (typename), (t_Ty), vector4);
o_registerNT((phantom, math), (typename), (t_Ty), angle);
o_registerNT((phantom, math), (typename), (t_Ty), transform2);
o_registerNT((phantom, math), (typename), (t_Ty), axis_angle);
o_registerNT((phantom, math), (typename), (t_Ty), quaternion);
o_registerNT((phantom, math), (typename), (t_Ty), transform3);
o_registerNT((phantom, math), (typename), (t_Ty), matrix2x2);
o_registerNT((phantom, math), (typename), (t_Ty), matrix2x3);
o_registerNT((phantom, math), (typename), (t_Ty), matrix2x4);
o_registerNT((phantom, math), (typename), (t_Ty), matrix3x2);
o_registerNT((phantom, math), (typename), (t_Ty), matrix3x3);
o_registerNT((phantom, math), (typename), (t_Ty), matrix3x4);
o_registerNT((phantom, math), (typename), (t_Ty), matrix4x2);
o_registerNT((phantom, math), (typename), (t_Ty), matrix4x3);
o_registerNT((phantom, math), (typename), (t_Ty), matrix4x4);
o_registerNT((phantom, math), (typename), (t_Ty), aabb2);
o_registerNT((phantom, math), (typename), (t_Ty), aabb3);
o_registerNT((phantom, math), (typename), (t_Ty), line2);
o_registerNT((phantom, math), (typename), (t_Ty), segment2);
o_registerNT((phantom, math), (typename), (t_Ty), line3);
o_registerNT((phantom, math), (typename), (t_Ty), plane3);
o_registerNT((phantom, math), (typename), (t_Ty), rect);

o_registerNTI((phantom, math), vector2, (float));
o_registerNTI((phantom, math), vector3, (float));
o_registerNTI((phantom, math), vector4, (float));
o_registerNTI((phantom, math), angle, (float));
o_registerNTI((phantom, math), transform2, (float));
o_registerNTI((phantom, math), axis_angle, (float));
o_registerNTI((phantom, math), quaternion, (float));
o_registerNTI((phantom, math), transform3, (float));
o_registerNTI((phantom, math), matrix2x2, (float));
o_registerNTI((phantom, math), matrix2x3, (float));
o_registerNTI((phantom, math), matrix2x4, (float));
o_registerNTI((phantom, math), matrix3x2, (float));
o_registerNTI((phantom, math), matrix3x3, (float));
o_registerNTI((phantom, math), matrix3x4, (float));
o_registerNTI((phantom, math), matrix4x2, (float));
o_registerNTI((phantom, math), matrix4x3, (float));
o_registerNTI((phantom, math), matrix4x4, (float));
o_registerNTI((phantom, math), aabb2, (float));
o_registerNTI((phantom, math), aabb3, (float));
o_registerNTI((phantom, math), line2, (float));
o_registerNTI((phantom, math), segment2, (float));
o_registerNTI((phantom, math), line3, (float));
o_registerNTI((phantom, math), plane3, (float));
o_registerNTI((phantom, math), rect, (float));

o_registerNTI((phantom, math), vector2, (double));
o_registerNTI((phantom, math), vector3, (double));
o_registerNTI((phantom, math), vector4, (double));
o_registerNTI((phantom, math), angle, (double));
o_registerNTI((phantom, math), transform2, (double));
o_registerNTI((phantom, math), axis_angle, (double));
o_registerNTI((phantom, math), quaternion, (double));
o_registerNTI((phantom, math), transform3, (double));
o_registerNTI((phantom, math), matrix2x2, (double));
o_registerNTI((phantom, math), matrix2x3, (double));
o_registerNTI((phantom, math), matrix2x4, (double));
o_registerNTI((phantom, math), matrix3x2, (double));
o_registerNTI((phantom, math), matrix3x3, (double));
o_registerNTI((phantom, math), matrix3x4, (double));
o_registerNTI((phantom, math), matrix4x2, (double));
o_registerNTI((phantom, math), matrix4x3, (double));
o_registerNTI((phantom, math), matrix4x4, (double));
o_registerNTI((phantom, math), aabb2, (double));
o_registerNTI((phantom, math), aabb3, (double));
o_registerNTI((phantom, math), line2, (double));
o_registerNTI((phantom, math), segment2, (float));
o_registerNTI((phantom, math), line3, (double));
o_registerNTI((phantom, math), plane3, (double));
o_registerNTI((phantom, math), rect, (double));

o_registerNTI((phantom, math), rect, (int));
/// TODO : add o_registerNTP to phantom for registering partial specializations
// o_registerNTI((phantom, math), vector2, (bool));
// o_registerNTI((phantom, math), vector3, (bool));
// o_registerNTI((phantom, math), vector4, (bool));
// 
// o_registerNTI((phantom, math), vector2, (unsigned int));
// o_registerNTI((phantom, math), vector3, (unsigned int));
// o_registerNTI((phantom, math), vector4, (unsigned int));
// 
// o_registerNTI((phantom, math), vector2, (int));
// o_registerNTI((phantom, math), vector3, (int));
// o_registerNTI((phantom, math), vector4, (int));

o_namespace_begin(phantom, math)

o_namespace_end(phantom, math)