#ifndef o_math_vector2_h__
#define o_math_vector2_h__

#include <phantom/phantom.h>

o_declareNT(class, (phantom, math), (typename), (t_Ty), vector2);

o_namespace_begin(phantom, math)

template<typename t_Ty>
struct vector2_default_base
{
    o_forceinline vector2_default_base() {}
    o_forceinline vector2_default_base(t_Ty a_x, t_Ty a_y)
        : x(a_x), y(a_y) {}
    
};

template<typename t_Ty>
class vector2 
{
public:
    typedef vector2<t_Ty> self_type;

    o_forceinline vector2() {}
    o_forceinline explicit vector2(t_Ty a_Value) : x(a_Value), y(a_Value) {}
    o_forceinline vector2(t_Ty a_x, t_Ty a_y)
        : x(a_x), y(a_y) {}


    o_forceinline void set(t_Ty a_x, t_Ty a_y) { x = a_x; y = a_y; }
    o_forceinline void setZero() { x = t_Ty(0); y = t_Ty(0); }

    o_forceinline static self_type const&  Zero() { static self_type VALUE(t_Ty(0),t_Ty(0)); return VALUE; }

    o_forceinline bool isValid() const { return isNumberValid(x) AND isNumberValid(y); }

    o_forceinline t_Ty          length() const
    {
        // Standard Squared Root
        return phantom::math::sqrt(lengthSquared());
    }
    o_forceinline t_Ty          lengthApproximated() const
    {
       return phantom::math::approximatedSqrt(lengthSquared());
    }
    o_forceinline t_Ty       lengthSquared() const
    {
        return x*x+y*y;
    }
    o_forceinline t_Ty          normalize() 
    {
        t_Ty len = length();
        if(len == 0) 
        {
            x = 0;
            y = 0;
            return 0;
        }
        o_NESTED_TYPE make_float<t_Ty>::type invLen = make_float<t_Ty>::type(1.)/len;
        x *= invLen;
        y *= invLen;
        return len;
    }
    o_forceinline t_Ty          normalizeApproximated() 
    {
        t_Ty len = lengthApproximated();
        if(len == 0) 
        {
            x = 0;
            y = 0;
            return 0;
        }
        o_NESTED_TYPE make_float<t_Ty>::type invLen = make_float<t_Ty>::type(1.)/len;
        x *= invLen;
        y *= invLen;
        return len;
    }
    o_forceinline self_type       normalized() const
    {
        t_Ty len = length();
        if(len == 0) 
        {
            return self_type(0,0);
        }
        t_Ty invLen = t_Ty(1.)/len;
        return self_type(x * invLen, y*invLen);
    }
    o_forceinline self_type       normalizedApproximated() const
    {
        t_Ty len = lengthApproximated();
        if(len == 0) 
        {
            return self_type(0,0);
        }
        t_Ty invLen = t_Ty(1.)/len;
        return self_type(x * invLen, y*invLen);
    }

    o_forceinline t_Ty          distance(const self_type& other) const 
    {
        return (other-*this).length();
    }

    o_forceinline t_Ty          distanceApproximated(const self_type& other) const 
    {
        return (other-*this).lengthApproximated();
    }

    o_forceinline t_Ty          distanceSquared(const self_type& other) const 
    {
        return (other-*this).lengthSquared();
    }

    o_forceinline self_type       to(const self_type& other) const 
    {
        return (other-*this);
    }

    inline t_Ty                 angle(const self_type& other) const 
    {
        t_Ty theta1,theta2;

        theta1 = atan2(y,x);
        theta2 = atan2(other.y,other.x);
        return theta2 - theta1;
    }

    inline t_Ty                 clampedAngle(const self_type& other) const 
    {
        t_Ty a = angle(other);
        while (a > o_math_Pi)
            a -= o_math_Pi*2;
        while (a < -o_math_Pi)
            a += o_math_Pi*2;
        return(a);
    }

    /**@brief Return the linear interpolation between this and another vector 
   * @param v The other vector 
   * @param t The ration of this to v (t = 0 => return this, t=1 => return other) */
	o_forceinline self_type lerp(const self_type& v, const t_Ty& t) const 
	{
		return self_type(a[0] + (v.a[0] - a[0]) * t,
			a[1] + (v.a[1] - a[1]) * t);
	}

    o_forceinline bool isZero() const 
    {
        return x == t_Ty(0) AND y == t_Ty(0);
    }

    /// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
    o_forceinline self_type skewed() const
    {
        return self_type(-y, x);
    }

    // vector2/vector2 operation
    o_forceinline self_type   operator+(self_type const& other) const
    {
        return self_type(x+other.x, y+other.y);
    }
    o_forceinline self_type   operator-(self_type const& other) const
    {
        return self_type(x-other.x, y-other.y);
    }
    o_forceinline self_type   operator*(self_type const& other) const
    {
        return self_type(x*other.x, y*other.y);
    }
    o_forceinline self_type   operator/(self_type const& other) const
    {
        return self_type(x/other.x, y/other.y);
    }

    /// Add a vector to this vector.
    o_forceinline  self_type const& operator += (const self_type& v)
    {
        x += v.x; y += v.y; 
        return *this;
    }

    /// Subtract a vector from this vector.
    o_forceinline  self_type const& operator -= (const self_type& v)
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    o_forceinline t_Ty   dot(self_type const& other) const
    {
        return other.x*x + other.y*y;
    }

    o_forceinline t_Ty   cross(self_type const& other) const
    {
        return x * other.y - y * other.x;
    }

    o_forceinline self_type cross(t_Ty s) const
    {
        return self_type(s * y, -s * x);
    }

    // vector2/floating point operation
    o_forceinline self_type   operator+(t_Ty otherTy) const
    {
        return self_type(x+otherTy, y+otherTy);
    }
    o_forceinline self_type   operator-(t_Ty otherTy) const
    {
        return self_type(x-otherTy, y-otherTy);
    }
    o_forceinline self_type   operator*(t_Ty otherTy) const
    {
        return self_type(x*otherTy, y*otherTy);
    }
    o_forceinline self_type   operator/(t_Ty otherTy) const
    {
        otherTy = t_Ty(1)/otherTy;
        return self_type(x*otherTy, y*otherTy);
    }

    /// Multiply this vector by a scalar.
    o_forceinline self_type const& operator *= (t_Ty s)
    {
        x *= s; y *= s;
        return *this;
    }

    /// Divide this vector by a scalar.
    o_forceinline self_type const& operator /= (t_Ty s)
    {
        x /= s; y /= s;
        return *this;
    }

    o_forceinline t_Ty&          operator[](uint i)
    {
        o_assert(i < 2);
        return a[i];
    }

    o_forceinline t_Ty const&          operator[](uint i) const
    {
        o_assert(i < 2);
        return a[i];
    }

    /// Negate this vector.
    o_forceinline self_type operator -() const {  return self_type(-x, -y); }


    o_forceinline bool operator == (const self_type& v) const
    {
        return x == v.x AND y == v.y;
    }
    o_forceinline bool operator != (const self_type& v) const
    {
        return x != v.x OR y != v.y;
    }

    union
    {
        struct 
        {
            t_Ty x;
            t_Ty y;
        };
        t_Ty    m[2];
    };

};

typedef vector2<float32> vector2f;
typedef vector2<float64> vector2d;

o_namespace_end(phantom, math)

o_namespace_begin(phantom, extension, detail)

template<typename t_Ty>
struct safe_constructor_ <math::vector2<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        ((math::vector2<t_Ty>*)a_pInstance)->x = 0;
        ((math::vector2<t_Ty>*)a_pInstance)->y = 0;
    }
};

o_namespace_end(phantom, extension, detail)

#endif // phantom_math_vector2_h__
