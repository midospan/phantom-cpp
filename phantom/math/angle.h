#ifndef o_math_angle_h__
#define o_math_angle_h__

#include "vector2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), angle);

o_namespace_begin(phantom, math)

/// Angle representation in radians (internal) and degree (computed)

template<typename t_Ty>
class angle
{
public:
    typedef angle<t_Ty> self_type;
    typedef vector2<t_Ty> vector2_type;

    inline angle() {}

    /// Initialize from an angle in radians
    inline angle(t_Ty angle)
    {
        c = cos(angle);
        s = sin(angle);
    }

    /// Initialize from an angle in radians
    inline angle(t_Ty ac, t_Ty as)
    {
        c = ac;
        s = as;
    }

    /// Initialize from other
    inline angle(const self_type& a)
    {
        c = a.c;
        s = a.s;
    }

    inline self_type& operator=(const self_type& a)
    {
        c = a.c;
        s = a.s;
        return *this;
    }

    /// Set to the identity rotation
    inline void setIdentity()
    {
        s = (t_Ty)0;
        c = (t_Ty)1;
    }

    /// Set value in radians.
    inline void setRadian(t_Ty radian)
    {
        /// TODO optimize
        s = sin(radian);
        c = cos(radian);
    }

    /// Get value in radians
    inline t_Ty getRadian() const
    {
        return atan2(s, c);
    }

    /// Set value in degree.
    inline void setDegree(t_Ty degree)
    {
        t_Ty radian = degree*o_math_to_radian;
        /// TODO optimize
        s = sin(radian);
        c = cos(radian);
    }

    /// Get value in degrees
    inline t_Ty getDegree() const
    {
        return atan2(s, c)*o_math_to_degree;
    }

    /// Get the x-axis
    inline vector2_type getXAxis() const
    {
        return vector2_type(c, s);
    }

    /// Get the u-axis
    inline vector2_type getYAxis() const
    {
        return vector2_type(-s, c);
    }

    inline bool operator==(const self_type& other) const 
    {
        return (other.s == s) AND (other.c == c);
    }

    inline bool operator!=(const self_type& other) const 
    {
        return (other.s != s) OR (other.c != c);
    }

    inline vector2_type rotate(const vector2_type& in) const
    {
        return vector2_type(in.x*c - in.y*s, in.x*s + in.y*c);
    }

    inline void rotate(const vector2_type& in, vector2_type& out) const
    {
        out.x = in.x*c - in.y*s;
        out.y = in.x*s + in.y*c;
    }

    inline void rotate(vector2_type& out) const
    {
        float x = out.x*c - out.y*s;
        out.y = out.x*s + out.y*c;
        out.x = x;
    }

    inline bool equals(const self_type& other,
        t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const
    {
        return (math::equals(c, other.c, epsilon) &&
            math::equals(s, other.s, epsilon));
    }

    inline self_type operator+(const self_type& other) const 
    {
        return self_type(c*other.c - s*other.s, s*other.c + c*other.s);
    }

    inline self_type operator-(const self_type& other) const 
    {
        return self_type(c*other.c + s*other.s, s*other.c - c*other.s);
    }

    inline void operator+=(const self_type& other) const 
    {
        *this = self_type(c*other.c - s*other.s, s*other.c + c*other.s);
    }

    inline void operator-=(const self_type& other) const 
    {
        *this = self_type(c*other.c + s*other.s, s*other.c - c*other.s);
    }

    /// Sine and cosine
    t_Ty s, c;
};

typedef angle<float32> anglef;
typedef angle<float64> angled;

o_namespace_end(phantom, math)

o_namespace_begin(phantom, detail)

template<typename t_Ty>
struct safe_constructor_ <math::angle<t_Ty> >
{
    static void safeConstruct(void* a_pInstance) 
    { 
        ((math::angle<t_Ty>*)a_pInstance)->c = 1;
        ((math::angle<t_Ty>*)a_pInstance)->s = 0;
    }
};

o_namespace_end(phantom, detail)

#endif // phantom_math_angle_h__
