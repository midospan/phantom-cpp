#ifndef phantom_math_rotation2D_h__
#define phantom_math_rotation2D_h__

o_namespace_begin(phantom, math)

/// rotation in 2D space, adapted from Box2D

template<typename t_Ty>
struct rotation2D
{
    typedef vector2<t_Ty> vector2_type;
    typedef rotation2D<t_Ty> self_type;

    rotation2D() {}

    /// Initialize from an angle in radians
    rotation2D(t_Ty angle)
    {
        /// TODO optimize
        s = sin(angle);
        c = cos(angle);
    }

    /// Set using an angle in radians.
    void setAngle(t_Ty angle)
    {
        /// TODO optimize
        s = sin(angle);
        c = cos(angle);
    }

    /// Set to the identity rotation
    void setIdentity()
    {
        s = 0.0f;
        c = 1.0f;
    }

    /// Get the angle in radians
    t_Ty getAngle() const
    {
        return atan2(s, c);
    }

    /// Get the x-axis
    vector2_type getXAxis() const
    {
        return vector2_type(c, s);
    }

    /// Get the u-axis
    vector2_type getYAxis() const
    {
        return vector2_type(-s, c);
    }

    bool operator==(const self_type& other) const 
    {
        return (other.s == s) AND (other.c == c);
    }

    bool operator!=(const self_type& other) const 
    {
        return (other.s != s) OR (other.c != c);
    }

    /// Sine and cosine
    t_Ty s, c;
};

o_namespace_end(phantom, math)

o_namespace_begin(phantom, extension, detail)

template<typename t_Ty>
struct safe_constructor_ <math::rotation2D<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        ((math::rotation2D<t_Ty>*)a_pInstance)->c = 1;
        ((math::rotation2D<t_Ty>*)a_pInstance)->s = 0;
    }
};

o_namespace_end(phantom, extension, detail)

#endif // phantom_math_rotation2D_h__
