
template<class t_Ty>
inline matrix2x3<t_Ty>::matrix2x3()
{
    makeZero();
}


template<class t_Ty>
inline matrix2x3<t_Ty>::matrix2x3 (const matrix2x3<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
}


template<class t_Ty>
inline matrix2x3<t_Ty>::matrix2x3 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m10, t_Ty m11, t_Ty m12)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m10;
    m[4] = m11;
    m[5] = m12;
}


template<class t_Ty>
inline matrix2x3<t_Ty>::matrix2x3 (const t_Ty entry[6], bool colMajor)
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
inline matrix2x3<t_Ty>::matrix2x3 (const vector2<t_Ty>* v)
{
    m[0] = v[0][0];
    m[1] = v[1][0];
    m[2] = v[2][0];
    m[3] = v[0][1];
    m[4] = v[1][1];
    m[5] = v[2][1];
}


template<class t_Ty>
inline matrix2x3<t_Ty>::matrix2x3 (const vector3_type* v)
{
    m[0] = v[0][0];
    m[1] = v[0][1];
    m[2] = v[0][2];
    m[3] = v[1][0];
    m[4] = v[1][1];
    m[5] = v[1][2];
}


template<class t_Ty>
inline matrix2x3<t_Ty>& matrix2x3<t_Ty>::operator= (const matrix2x3<t_Ty>& mat)
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
inline void matrix2x3<t_Ty>::makeZero ()
{
    m[0] = (t_Ty)0;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
    m[4] = (t_Ty)0;
    m[5] = (t_Ty)0;
}


template<class t_Ty>
inline matrix2x3<t_Ty> matrix2x3<t_Ty>::operator+ (const matrix2x3<t_Ty>& mat) const
{
    return matrix2x3
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
inline matrix2x3<t_Ty> matrix2x3<t_Ty>::operator- (const matrix2x3<t_Ty>& mat)
    const
{
    return matrix2x3
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
inline matrix2x3<t_Ty> matrix2x3<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix2x3
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
inline matrix2x3<t_Ty> matrix2x3<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix2x3
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
        t_Ty v = std::numeric_limits<t_Ty>::max();
        return matrix2x3
            (
            v,
            v,
            v,
            v,
            v,
            v
            );
    }
}


template<class t_Ty>
inline matrix2x3<t_Ty> matrix2x3<t_Ty>::operator- () const
{
    return matrix2x3
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
inline matrix2x3<t_Ty>& matrix2x3<t_Ty>::operator+= (const matrix2x3<t_Ty>& mat)
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
inline matrix2x3<t_Ty>& matrix2x3<t_Ty>::operator-= (const matrix2x3<t_Ty>& mat)
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
inline matrix2x3<t_Ty>& matrix2x3<t_Ty>::operator*= (t_Ty scalar)
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
inline matrix2x3<t_Ty>& matrix2x3<t_Ty>::operator/= (t_Ty scalar)
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
inline vector3<t_Ty> matrix2x3<t_Ty>::operator* (const vector2<t_Ty>& vec) const
{
    return vector3_type
        (
        m[0]*vec[0] + m[3]*vec[1],
        m[1]*vec[0] + m[4]*vec[1],
        m[2]*vec[0] + m[5]*vec[1]
    );
}



template<class t_Ty>
inline matrix2x3<t_Ty> operator* (t_Ty scalar, const matrix2x3<t_Ty>& mat)
{
    return mat*scalar;
}


