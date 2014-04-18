#ifndef phantom_math_vector3_h__
#define phantom_math_vector3_h__

o_namespace_begin(phantom, math)
    
template<typename t_Ty>
struct vector3 
{
    typedef vector3<t_Ty>    self_type;

    static const self_type  ZERO;

    o_forceinline vector3() {}

    o_forceinline explicit vector3(t_Ty a_Value) : x(a_Value), y(a_Value), z(a_Value) {}

    o_forceinline vector3(t_Ty a_x, t_Ty a_y, t_Ty a_z)
        : x(a_x), y(a_y), z(a_z) {}

    o_forceinline bool isValid() const { return isNumberValid(x) AND isNumberValid(y) AND isNumberValid(z); }

    o_forceinline void set(t_Ty a_x, t_Ty a_y, t_Ty a_z) { x = a_x; y = a_y; z = a_z; }
    o_forceinline void setZero() { x = t_Ty(0); y = t_Ty(0); z = t_Ty(0); }

    o_forceinline static self_type const&  Zero() { static self_type VALUE(t_Ty(0),t_Ty(0),t_Ty(0)); return VALUE; }

    o_forceinline t_Ty          length() const
    {
        // Standard Squared Root
        return phantom::math::sqrt(lengthSquared());
    }
    o_forceinline t_Ty          lengthApproximated() const
    {
        // Approximated Squared Root
        union
        {
            int tmp;
            t_Ty f;
        } u;
        u.f = lengthSquared();
        u.tmp -= 1<<23; /* Remove last bit so 1.0 gives 1.0 */
        /* tmp is now an approximation to logbase2(z) */
        u.tmp >>= 1; /* divide by 2 */
        u.tmp += 1<<29; /* add 64 to exponent: (e+127)/2 =(e/2)+63, */
        /* that represents (e/2)-64 but want e/2 */
        return u.f;//(float32)b2Sqrt(lenSq);
    }
    o_forceinline t_Ty       lengthSquared() const
    {
        return x*x+y*y+z*z;
    }
    o_forceinline t_Ty          normalize() 
    {
        t_Ty len = length();
        t_Ty invLen = t_Ty(1.)/len;
        x *= invLen;
        y *= invLen;
        z *= invLen;
        return len;
    }
    o_forceinline t_Ty          normalizeApproximated() 
    {
        t_Ty len = lengthApproximated();
        t_Ty invLen = t_Ty(1.)/len;
        x *= invLen;
        y *= invLen;
        z *= invLen;
        return len;
    }
    o_forceinline self_type       normalized() const
    {
        t_Ty invLen = t_Ty(1.)/length();
        return self_type(x * invLen, y*invLen, z*invLen);
    }
    o_forceinline self_type       normalizedApproximated() const
    {
        t_Ty invLen = t_Ty(1.)/lengthApproximated();
        return self_type(x * invLen, y*invLen, z*invLen);
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

    /**@brief Return the angle between this and another vector
   * @param v The other vector */
	o_forceinline t_Ty angle(const self_type& v) const 
	{
		t_Ty s = math::sqrt(lengthSquared() * v.lengthSquared());
		o_assert(s != t_Ty(0.0));
		return math::acos(dot(v) / s);
	}

    o_forceinline t_Ty clampedAngle(const self_type& other) const 
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
			a[1] + (v.a[1] - a[1]) * t,
			a[2] + (v.a[2] -a[2]) * t);
	}

    o_forceinline bool isZero() const 
    {
        return x == t_Ty(0) && y == t_Ty(0) && z == t_Ty(0);
    }

    // vector3/vector3 operation
    o_forceinline self_type   operator+(self_type const& other) const
    {
        return self_type(x+other.x, y+other.y, z+other.z);
    }
    o_forceinline self_type   operator-(self_type const& other) const
    {
        return self_type(x-other.x, y-other.y, z-other.z);
    }
    o_forceinline self_type   operator*(self_type const& other) const
    {
        return self_type(x*other.x, y*other.y, z*other.z);
    }
    o_forceinline self_type   operator/(self_type const& other) const
    {
        return self_type(x/other.x, y/other.y, z/other.z);
    }
    /// Add a vector to this vector.
    o_forceinline self_type const& operator += (const self_type& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    /// Subtract a vector from this vector.
    o_forceinline  self_type const& operator -= (const self_type& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }

    o_forceinline t_Ty   dot(self_type const& other) const
    {
        return other.x*x + other.y*y + other.z*z;
    }
    o_forceinline self_type   cross(self_type const& other) const
    {
        return self_type(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    // vector3/floating point operation
    o_forceinline self_type   operator+(t_Ty otherTy) const
    {
        return self_type(x+otherTy, y+otherTy, z+otherTy);
    }
    o_forceinline self_type   operator-(t_Ty otherTy) const
    {
        return self_type(x-otherTy, y-otherTy, z-otherTy);
    }
    o_forceinline self_type   operator*(t_Ty otherTy) const
    {
        return self_type(x*otherTy, y*otherTy, z*otherTy);
    }
    o_forceinline self_type   operator/(t_Ty otherTy) const
    {
        otherTy = t_Ty(1)/otherTy;
        return self_type(x*otherTy, y*otherTy, z*otherTy);
    }

    /// Multiply this vector by a scalar.
    o_forceinline self_type const& operator *= (t_Ty s)
    {
        x *= s; y *= s; z *= s;
        return *this;
    }

    /// Divide this vector by a scalar.
    o_forceinline self_type const& operator /= (t_Ty s)
    {
        x /= s; y /= s; z /= s;
        return *this;
    }

    o_forceinline t_Ty&          operator[](uint i) 
    {
        o_assert(i < 3);
        return a[i];
    }

    o_forceinline t_Ty const&    operator[](uint i) const
    {
        o_assert(i < 3);
        return a[i];
    }

    /// Negate this vector.
    o_forceinline self_type operator -() const {  return self_type(-x, -y, -z); }

    o_forceinline bool operator == (const self_type& v) const
    {
        return x == v.x AND y == v.y AND z == v.z;
    }
    o_forceinline bool operator != (const self_type& v) const
    {
        return x != v.x OR y != v.y OR z != v.z;
    }

    union
    {
        struct 
        {
            t_Ty x;
            t_Ty y;
            t_Ty z;
        };
        struct 
        {
            t_Ty r;
            t_Ty g;
            t_Ty b;
        };
        t_Ty    a[3];
    };
};

o_namespace_end(phantom, math)

o_namespace_begin(phantom, extension, detail)

template<typename t_Ty>
struct safe_constructor_ <math::vector3<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        ((math::vector3<t_Ty>*)a_pInstance)->x = 0;
        ((math::vector3<t_Ty>*)a_pInstance)->y = 0;
        ((math::vector3<t_Ty>*)a_pInstance)->z = 0;
    }
};
o_namespace_end(phantom, extension, detail)

#endif // phantom_math_vector3_h__