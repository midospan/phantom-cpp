#include "phantom/phantom.h"
#include "phantom/math/math.h"

o_registerNT((phantom, math), (typename), (t_Ty), vector2);
o_registerNT((phantom, math), (typename), (t_Ty), vector3);
o_registerNT((phantom, math), (typename), (t_Ty), vector4);
o_registerNT((phantom, math), (typename), (t_Ty), transform2);
o_registerNT((phantom, math), (typename), (t_Ty), rotation2D);
o_registerNT((phantom, math), (typename), (t_Ty), matrix2x2);
o_registerNT((phantom, math), (typename), (t_Ty), matrix3x3);
o_registerNT((phantom, math), (typename), (t_Ty), aabb2);

o_register(phantom::math::vector2<float>);
o_register(phantom::math::vector3<float>);
o_register(phantom::math::vector4<float>);
o_register(phantom::math::rotation2D<float>);
o_register(phantom::math::transform2<float>);
o_register(phantom::math::matrix2x2<float>);
o_register(phantom::math::matrix3x3<float>);
o_register(phantom::math::aabb2<float>);
o_register_typedefNC(phantom::math, matrix2x2<float>, vector2_type);
o_register_typedefNC(phantom::math, matrix3x3<float>, vector3_type);

o_register(phantom::math::vector2<double>);
o_register(phantom::math::vector3<double>);
o_register(phantom::math::vector4<double>);
o_register(phantom::math::rotation2D<double>);
o_register(phantom::math::transform2<double>);
o_register(phantom::math::matrix2x2<double>);
o_register(phantom::math::matrix3x3<double>);
o_register(phantom::math::aabb2<double>);
o_register_typedefNC(phantom::math, matrix2x2<double>, vector2_type);
o_register_typedefNC(phantom::math, matrix3x3<double>, vector3_type);

//o_register_typedefNC(phantom::math, matrix4x4<float>, vector4_type);

/*o_register_typedef(phantom, vector2);
o_register_typedef(phantom, vector2f);
o_register_typedef(phantom, vector2d);

o_register_typedef(phantom, vector3);
o_register_typedef(phantom, vector3f);
o_register_typedef(phantom, vector3d);

o_register_typedef(phantom, vector4);
o_register_typedef(phantom, vector4f);
o_register_typedef(phantom, vector4d);

o_register_typedef(phantom, matrix2x2);
o_register_typedef(phantom, matrix2x2f);
o_register_typedef(phantom, matrix2x2d);

o_register_typedef(phantom, matrix3x3);
o_register_typedef(phantom, matrix3x3f);
o_register_typedef(phantom, matrix3x3d);

o_register_typedef(phantom, transform2);
o_register_typedef(phantom, transform2f);
o_register_typedef(phantom, transform2d);

o_register_typedef(phantom, aabb2);
o_register_typedef(phantom, aabb2f);
o_register_typedef(phantom, aabb2d);*/
