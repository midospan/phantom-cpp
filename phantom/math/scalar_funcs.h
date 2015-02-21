#ifndef o_math_scalar_funcs_h__
#define o_math_scalar_funcs_h__

#include "phantom/phantom.h"
#include "def_math.h"

o_namespace_begin(phantom, math)

// DOUBLE PRECISION


o_forceinline double sqrt BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::sqrt(x); }

o_forceinline double fabs BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::fabs(x); }

o_forceinline double cos BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::cos(x); }

o_forceinline double sin BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::sin(x); }

o_forceinline double tan BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::tan(x); }

o_forceinline double acos BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { if (x<double(-1))	x=double(-1); if (x>double(1))	x=double(1); return ::acos(x); }

o_forceinline double asin BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { if (x<double(-1))	x=double(-1); if (x>double(1))	x=double(1); return ::asin(x); }

o_forceinline double atan BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::atan(x); }

o_forceinline double atan2 BOOST_PREVENT_MACRO_SUBSTITUTION (double x, double y) { return ::atan2(x, y); }

o_forceinline double exp BOOST_PREVENT_MACRO_SUBSTITUTION  (double x) { return ::exp(x); }

o_forceinline double log BOOST_PREVENT_MACRO_SUBSTITUTION (double x) { return ::log(x); }

o_forceinline double pow BOOST_PREVENT_MACRO_SUBSTITUTION (double x,double y) { return ::pow(x,y); }

o_forceinline double fmod BOOST_PREVENT_MACRO_SUBSTITUTION (double x,double y) { return fmod(x,y); }

o_forceinline double approximatedSqrt(double x) { return sqrt(x); }




// SINGLE PRECISION

o_forceinline float sqrt BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::sqrtf(x); }

o_forceinline float fabs BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::fabsf(x); }

o_forceinline float cos BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::cosf(x); }

o_forceinline float sin BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::sinf(x); }

o_forceinline float tan BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::tanf(x); }

o_forceinline float acos BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { if (x<float(-1))	x=float(-1); if (x>float(1))	x=float(1); return ::acosf(x); }

o_forceinline float asin BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { if (x<float(-1))	x=float(-1); if (x>float(1))	x=float(1); return ::asinf(x); }

o_forceinline float atan BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::atanf(x); }

o_forceinline float atan2 BOOST_PREVENT_MACRO_SUBSTITUTION (float x, float y) { return ::atan2f(x, y); }

o_forceinline float exp BOOST_PREVENT_MACRO_SUBSTITUTION  (float x) { return ::expf(x); }

o_forceinline float log BOOST_PREVENT_MACRO_SUBSTITUTION (float x) { return ::logf(x); }

o_forceinline float pow BOOST_PREVENT_MACRO_SUBSTITUTION (float x,float y) { return ::powf(x,y); }

o_forceinline float fmod BOOST_PREVENT_MACRO_SUBSTITUTION (float x,float y) { return fmodf(x,y); }


o_forceinline float approximatedSqrt(float x)
{
    // Approximated Squared Root
    union
    {
        int tmp;
        float f;
    } u;
    u.f = x;
    u.tmp -= 1<<23; /* Remove last bit so 1.0 gives 1.0 */
    /* tmp is now an approximation to logbase2(z) */
    u.tmp >>= 1; /* divide by 2 */
    u.tmp += 1<<29; /* add 64 to exponent: (e+127)/2 =(e/2)+63, */
    /* that represents (e/2)-64 but want e/2 */
    return u.f;//(float32)b2Sqrt(lenSq);
}

o_forceinline float invSqrt(float x)
{
    union
    {
        float x;
        int i;
    } convert;

    convert.x = x;
    float xhalf = 0.5f * x;
    convert.i = 0x5f3759df - (convert.i >> 1);
    x = convert.x;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

o_forceinline double invSqrt(double x)
{
    return 1.0/math::sqrt(x);
}

template <typename t_Ty>
inline t_Ty    epsilon();

template <>
inline float    epsilon<float>()
{
    return FLT_EPSILON;
}

template <>
inline double    epsilon<double>()
{
    return DBL_EPSILON;
}

template <typename t_Ty>
bool            equals(t_Ty a, t_Ty b, t_Ty tolerance = phantom::math::epsilon<t_Ty>())
{
    return (abs(b-a) <= tolerance);
}

template<typename t_Ty>
bool isNumberValid(t_Ty value)
{
    if (value != value)
    {
        // NaN.
        return false;
    }

    t_Ty infinity = std::numeric_limits<t_Ty>::infinity();
    return -infinity < value && value < infinity;
}


template <typename t_Ty>
inline t_Ty abs(t_Ty a)
{
    return a > t_Ty(0) ? a : -a;
}

template <typename t_Ty>
inline t_Ty min(t_Ty a, t_Ty b)
{
    return a < b ? a : b;
}

template <typename t_Ty>
inline t_Ty max(t_Ty a, t_Ty b)
{
    return a > b ? a : b;
}

template <typename t_Ty>
inline t_Ty clamp(t_Ty a, t_Ty low, t_Ty high)
{
    return max(low, min(a, high));
}

o_namespace_end(phantom, math)

#endif // scalar_funcs_h__
