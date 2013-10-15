#ifndef o_phantom_math_types_h__
#define o_phantom_math_types_h__


#include "phantom/math/vector2.h"
#include "phantom/math/vector3.h"
#include "phantom/math/vector4.h"
#include "phantom/math/matrix2x2.h"
#include "phantom/math/matrix3x3.h"
#include "phantom/math/rotation2D.h"
#include "phantom/math/transform2.h"
#include "phantom/math/aabb2.h"

#include "phantom/_kernel.noclassdef.h"
// Easy root namespace access

o_namespace_begin(phantom)

typedef math::vector2<real>     vector2;
typedef math::vector2<float>    vector2f;
typedef math::vector2<double>   vector2d;
typedef math::vector2<int>      vector2i;

typedef math::vector3<real>     vector3;
typedef math::vector3<float>    vector3f;
typedef math::vector3<double>   vector3d;
typedef math::vector3<int>      vector3i;

typedef math::vector4<real>     vector4;
typedef math::vector4<float>    vector4f;
typedef math::vector4<double>   vector4d;
typedef math::vector4<int>      vector4i;

typedef math::matrix2x2<real>   matrix2x2;
typedef math::matrix2x2<float>  matrix2x2f;
typedef math::matrix2x2<double> matrix2x2d;

typedef math::matrix3x3<real>   matrix3x3;
typedef math::matrix3x3<float>  matrix3x3f;
typedef math::matrix3x3<double> matrix3x3d;

typedef math::transform2<real>   transform2;
typedef math::transform2<float>  transform2f;
typedef math::transform2<double> transform2d;

typedef math::aabb2<real>       aabb2;
typedef math::aabb2<float>      aabb2f;
typedef math::aabb2<double>     aabb2d;

typedef math::rotation2D<real>       rotation2D;
typedef math::rotation2D<float>      rotation2Df;
typedef math::rotation2D<double>     rotation2Dd;

o_namespace_end(phantom)



#endif // o_phantom_math_types_h__
