
template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2()
{
    makeZero();
}


template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2 (const matrix3x2<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
}


template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2 (t_Ty m00, t_Ty m01, t_Ty m10, t_Ty m11, t_Ty m20, t_Ty m21)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m10;
    m[3] = m11;
    m[4] = m20;
    m[5] = m21;
}


template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2 (const t_Ty entry[6], bool colMajor)
{
    if (colMajor)
    {
        m[0] = entry[0];
        m[1] = entry[1];
        m[2] = entry[2];
        m[3] = entry[3];
        m[4] = entry[4];
        m[5] = entry[5];
    }
    else
    {
        m[0] = entry[0];
        m[1] = entry[3];
        m[2] = entry[1];
        m[3] = entry[4];
        m[4] = entry[2];
        m[5] = entry[5];
    }
}


template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2 (const vector2_type* v)
{
    m[0] = v[0][0];
    m[1] = v[0][1];
    m[2] = v[1][0];
    m[3] = v[1][1];
    m[4] = v[2][0];
    m[5] = v[2][1];
}


template<class t_Ty>
inline matrix3x2<t_Ty>::matrix3x2 (const vector3<t_Ty>* v)
{
    m[0] = v[0][0];
    m[2] = v[0][1];
    m[4] = v[0][2];
    m[1] = v[1][0];
    m[3] = v[1][1];
    m[5] = v[1][2];
}


template<class t_Ty>
inline matrix3x2<t_Ty>& matrix3x2<t_Ty>::operator= (const matrix3x2<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
    return *this;
}


template<class t_Ty>
inline void matrix3x2<t_Ty>::makeZero ()
{
    m[0] = (t_Ty)0;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
    m[4] = (t_Ty)0;
    m[5] = (t_Ty)0;
}


template<class t_Ty>
inline matrix3x2<t_Ty> matrix3x2<t_Ty>::operator+ (const matrix3x2<t_Ty>& mat) const
{
    return matrix3x2
        (
        m[0] + mat.m[0],
        m[1] + mat.m[1],
        m[2] + mat.m[2],
        m[3] + mat.m[3],
        m[4] + mat.m[4],
        m[5] + mat.m[5]
    );
}


template<class t_Ty>
inline matrix3x2<t_Ty> matrix3x2<t_Ty>::operator- (const matrix3x2<t_Ty>& mat)
    const
{
    return matrix3x2
        (
        m[0] - mat.m[0],
        m[1] - mat.m[1],
        m[2] - mat.m[2],
        m[3] - mat.m[3],
        m[4] - mat.m[4],
        m[5] - mat.m[5]
    );
}


template<class t_Ty>
inline matrix3x2<t_Ty> matrix3x2<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix3x2
        (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3],
        scalar*m[4],
        scalar*m[5]
    );
}


template<class t_Ty>
inline matrix3x2<t_Ty> matrix3x2<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix3x2
            (
            invScalar*m[0],
            invScalar*m[1],
            invScalar*m[2],
            invScalar*m[3],
            invScalar*m[4],
            invScalar*m[5]
        );
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        return matrix3x2
            (
            max,
            max,
            max,
            max,
            max,
            max
            );
    }
}


template<class t_Ty>
inline matrix3x2<t_Ty> matrix3x2<t_Ty>::operator- () const
{
    return matrix3x2
        (
        -m[0],
        -m[1],
        -m[2],
        -m[3],
        -m[4],
        -m[5]
    );
}


template<class t_Ty>
inline matrix3x2<t_Ty>& matrix3x2<t_Ty>::operator+= (const matrix3x2<t_Ty>& mat)
{
    m[0] += mat.m[0];
    m[1] += mat.m[1];
    m[2] += mat.m[2];
    m[3] += mat.m[3];
    m[4] += mat.m[4];
    m[5] += mat.m[5];
    return *this;
}


template<class t_Ty>
inline matrix3x2<t_Ty>& matrix3x2<t_Ty>::operator-= (const matrix3x2<t_Ty>& mat)
{
    m[0] -= mat.m[0];
    m[1] -= mat.m[1];
    m[2] -= mat.m[2];
    m[3] -= mat.m[3];
    m[4] -= mat.m[4];
    m[5] -= mat.m[5];
    return *this;
}


template<class t_Ty>
inline matrix3x2<t_Ty>& matrix3x2<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    m[4] *= scalar;
    m[5] *= scalar;
    return *this;
}


template<class t_Ty>
inline matrix3x2<t_Ty>& matrix3x2<t_Ty>::operator/= (t_Ty scalar)
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        m[0] *= invScalar;
        m[1] *= invScalar;
        m[2] *= invScalar;
        m[3] *= invScalar;
        m[4] *= invScalar;
        m[5] *= invScalar;
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        m[0] = max;
        m[1] = max;
        m[2] = max;
        m[3] = max;
        m[4] = max;
        m[5] = max;
    }

    return *this;
}


template<class t_Ty>
inline vector2<t_Ty> matrix3x2<t_Ty>::operator* (const vector3<t_Ty>& vec) const
{
    return vector3<t_Ty>
        (
        m[0]*vec[0] + m[2]*vec[1] + m[4]*vec[2],
        m[1]*vec[0] + m[3]*vec[1] + m[5]*vec[2]
    );
}



template<class t_Ty>
inline matrix3x2<t_Ty> operator* (t_Ty scalar, const matrix3x2<t_Ty>& mat)
{
    return mat*scalar;
}


