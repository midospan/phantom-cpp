
template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4()
{
    makeZero();
}


template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4 (const matrix3x4<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
    m[6] = mat.m[6];
    m[7] = mat.m[7];
    m[8] = mat.m[8];
    m[9] = mat.m[9];
    m[10] = mat.m[10];
    m[11] = mat.m[11];
}


template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m03, t_Ty m10, t_Ty m11, t_Ty m12, t_Ty m13, t_Ty m20, t_Ty m21, t_Ty m22, t_Ty m23)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;
    m[4] = m10;
    m[5] = m11;
    m[6] = m12;
    m[7] = m13;
    m[8] = m20;
    m[9] = m21;
    m[10] = m22;
    m[11] = m23;
}


template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4 (const t_Ty entry[8], bool colMajor)
{
    if (colMajor)
    {
        m[0] = entry[0];
        m[1] = entry[1];
        m[2] = entry[2];
        m[3] = entry[3];
        m[4] = entry[4];
        m[5] = entry[5];
        m[6] = entry[6];
        m[7] = entry[7];
        m[8] = entry[8];
        m[9] = entry[9];
        m[10] = entry[10];
        m[11] = entry[11];
    }
    else
    {
        m[0] = entry[0];
        m[1] = entry[4];
        m[2] = entry[8];
        m[3] = entry[1];
        m[4] = entry[5];
        m[5] = entry[9];
        m[6] = entry[2];
        m[7] = entry[6];
        m[8] = entry[10];
        m[9] = entry[3];
        m[10] = entry[7];
        m[11] = entry[11];
    }
}


template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4 (const vector3<t_Ty>* v)
{
    m[0] = v[0][0];
    m[1] = v[1][0];
    m[2] = v[2][0];
    m[3] = v[3][0];
    m[4] = v[0][1];
    m[5] = v[1][1];
    m[6] = v[2][1];
    m[7] = v[3][1];
    m[8] = v[0][2];
    m[9] = v[1][2];
    m[10] = v[2][2];
    m[11] = v[3][2];
}


template<class t_Ty>
inline matrix3x4<t_Ty>::matrix3x4 (const vector4<t_Ty>* v)
{
    m[0] = v[0][0];
    m[1] = v[0][1];
    m[2] = v[0][2];
    m[3] = v[0][3];
    m[4] = v[1][0];
    m[5] = v[1][1];
    m[6] = v[1][2];
    m[7] = v[1][3];
    m[8] = v[2][0];
    m[9] = v[2][1];
    m[10] = v[2][2];
    m[11] = v[2][3];
}


template<class t_Ty>
inline matrix3x4<t_Ty>& matrix3x4<t_Ty>::operator= (const matrix3x4<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
    m[6] = mat.m[6];
    m[7] = mat.m[7];
    m[8] = mat.m[8];
    m[9] = mat.m[9];
    m[10] = mat.m[10];
    m[11] = mat.m[11];
    return *this;
}


template<class t_Ty>
inline void matrix3x4<t_Ty>::makeZero ()
{
    m[0] = (t_Ty)0;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
    m[4] = (t_Ty)0;
    m[5] = (t_Ty)0;
    m[6] = (t_Ty)0;
    m[7] = (t_Ty)0;
    m[8] = (t_Ty)0;
    m[9] = (t_Ty)0;
    m[10] = (t_Ty)0;
    m[11] = (t_Ty)0;
}


template<class t_Ty>
inline matrix3x4<t_Ty> matrix3x4<t_Ty>::operator+ (const matrix3x4<t_Ty>& mat) const
{
    return matrix3x4
        (
        m[0] + mat.m[0],
        m[1] + mat.m[1],
        m[2] + mat.m[2],
        m[3] + mat.m[3],
        m[4] + mat.m[4],
        m[5] + mat.m[5],
        m[6] + mat.m[6],
        m[7] + mat.m[7],
        m[8] + mat.m[8],
        m[9] + mat.m[9],
        m[10] + mat.m[10],
        m[11] + mat.m[11]
    );
}


template<class t_Ty>
inline matrix3x4<t_Ty> matrix3x4<t_Ty>::operator- (const matrix3x4<t_Ty>& mat)
    const
{
    return matrix3x4
        (
        m[0] - mat.m[0],
        m[1] - mat.m[1],
        m[2] - mat.m[2],
        m[3] - mat.m[3],
        m[4] - mat.m[4],
        m[5] - mat.m[5],
        m[6] - mat.m[6],
        m[7] - mat.m[7],
        m[8] - mat.m[8],
        m[9] - mat.m[9],
        m[10] - mat.m[10],
        m[11] - mat.m[11]
    );
}


template<class t_Ty>
inline matrix3x4<t_Ty> matrix3x4<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix3x4
        (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3],
        scalar*m[4],
        scalar*m[5],
        scalar*m[6],
        scalar*m[7],
        scalar*m[8],
        scalar*m[9],
        scalar*m[10],
        scalar*m[11]
    );
}


template<class t_Ty>
inline matrix3x4<t_Ty> matrix3x4<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix3x4
            (
            invScalar*m[0],
            invScalar*m[1],
            invScalar*m[2],
            invScalar*m[3],
            invScalar*m[4],
            invScalar*m[5],
            invScalar*m[6],
            invScalar*m[7],
            invScalar*m[8],
            invScalar*m[9],
            invScalar*m[10],
            invScalar*m[11]
        );
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        return matrix3x4
            (
            max,
            max,
            max,
            max,
            max,
            max,
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
inline matrix3x4<t_Ty> matrix3x4<t_Ty>::operator- () const
{
    return matrix3x4
        (
        -m[0],
        -m[1],
        -m[2],
        -m[3],
        -m[4],
        -m[5],
        -m[6],
        -m[7],
        -m[8],
        -m[9],
        -m[10],
        -m[11]
    );
}


template<class t_Ty>
inline matrix3x4<t_Ty>& matrix3x4<t_Ty>::operator+= (const matrix3x4<t_Ty>& mat)
{
    m[0] += mat.m[0];
    m[1] += mat.m[1];
    m[2] += mat.m[2];
    m[3] += mat.m[3];
    m[4] += mat.m[4];
    m[5] += mat.m[5];
    m[6] += mat.m[6];
    m[7] += mat.m[7];
    m[8] += mat.m[8];
    m[9] += mat.m[9];
    m[10] += mat.m[10];
    m[11] += mat.m[11];
    return *this;
}


template<class t_Ty>
inline matrix3x4<t_Ty>& matrix3x4<t_Ty>::operator-= (const matrix3x4<t_Ty>& mat)
{
    m[0] -= mat.m[0];
    m[1] -= mat.m[1];
    m[2] -= mat.m[2];
    m[3] -= mat.m[3];
    m[4] -= mat.m[4];
    m[5] -= mat.m[5];
    m[6] -= mat.m[6];
    m[7] -= mat.m[7];
    m[8] -= mat.m[8];
    m[9] -= mat.m[9];
    m[10] -= mat.m[10];
    m[11] -= mat.m[11];
    return *this;
}


template<class t_Ty>
inline matrix3x4<t_Ty>& matrix3x4<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    m[4] *= scalar;
    m[5] *= scalar;
    m[6] *= scalar;
    m[7] *= scalar;
    m[8] *= scalar;
    m[9] *= scalar;
    m[10] *= scalar;
    m[11] *= scalar;
    return *this;
}


template<class t_Ty>
inline matrix3x4<t_Ty>& matrix3x4<t_Ty>::operator/= (t_Ty scalar)
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
        m[6] *= invScalar;
        m[7] *= invScalar;
        m[8] *= invScalar;
        m[9] *= invScalar;
        m[10] *= invScalar;
        m[11] *= invScalar;
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
        m[6] = max;
        m[7] = max;
        m[8] = max;
        m[9] = max;
        m[10]= max;
        m[11]= max;
    }

    return *this;
}


template<class t_Ty>
inline vector4<t_Ty> matrix3x4<t_Ty>::operator* (const vector3<t_Ty>& vec) const
{
    return vector4<t_Ty>
        (
        m[0]*vec[0] + m[4]*vec[1] + m[8]*vec[2],
        m[1]*vec[0] + m[5]*vec[1] + m[9]*vec[2],
        m[2]*vec[0] + m[6]*vec[1] + m[10]*vec[2],
        m[3]*vec[0] + m[7]*vec[1] + m[11]*vec[2]
    );
}



template<class t_Ty>
inline matrix3x4<t_Ty> operator* (t_Ty scalar, const matrix3x4<t_Ty>& mat)
{
    return mat*scalar;
}


