

    template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (bool doMakeZero)
{
    if (doMakeZero)
    {
        makeZero();
    }
    else
    {
        makeIdentity();
    }
}

template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (const vector3<t_Ty>& position,
    const vector3<t_Ty>& scale, const quaternion<t_Ty>& orientation)
{
    // Ordering:
    //    1. Scale
    //    2. Rotate
    //    3. Translate

    matrix3x3<t_Ty> rot3x3;
    orientation.toRotationmatrix(rot3x3);

    // Set up final matrix with scale, rotation and translation
    mm[0][0] = scale.x * rot3x3[0][0];	mm[1][0] = scale.y * rot3x3[1][0];	mm[2][0] = scale.z * rot3x3[2][0];	mm[3][0] = position.x;
    mm[0][1] = scale.x * rot3x3[0][1];	mm[1][1] = scale.y * rot3x3[1][1];	mm[2][1] = scale.z * rot3x3[2][1];	mm[3][1] = position.y;
    mm[0][2] = scale.x * rot3x3[0][2];	mm[1][2] = scale.y * rot3x3[1][2];	mm[2][2] = scale.z * rot3x3[2][2];	mm[3][2] = position.z;

    // No projection term
    mm[0][3] = 0; mm[1][3] = 0; mm[2][3] = 0; mm[3][3] = 1;
}


template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (const matrix4x4<t_Ty>& mat)
{
    m[ 0] = mat.m[ 0];
    m[ 1] = mat.m[ 1];
    m[ 2] = mat.m[ 2];
    m[ 3] = mat.m[ 3];
    m[ 4] = mat.m[ 4];
    m[ 5] = mat.m[ 5];
    m[ 6] = mat.m[ 6];
    m[ 7] = mat.m[ 7];
    m[ 8] = mat.m[ 8];
    m[ 9] = mat.m[ 9];
    m[10] = mat.m[10];
    m[11] = mat.m[11];
    m[12] = mat.m[12];
    m[13] = mat.m[13];
    m[14] = mat.m[14];
    m[15] = mat.m[15];
}

template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (const matrix3x3<t_Ty>& mat)
{
    m[ 0] = mat.m[ 0];
    m[ 1] = mat.m[ 1];
    m[ 2] = mat.m[ 2];
    m[ 3] = 0;
    m[ 4] = mat.m[ 3];
    m[ 5] = mat.m[ 4];
    m[ 6] = mat.m[ 5];
    m[ 7] = 0;
    m[ 8] = mat.m[ 6];
    m[ 9] = mat.m[ 7];
    m[10] = mat.m[ 8];
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m03, t_Ty m10,
    t_Ty m11, t_Ty m12, t_Ty m13, t_Ty m20, t_Ty m21, t_Ty m22, t_Ty m23,
    t_Ty m30, t_Ty m31, t_Ty m32, t_Ty m33)
{
    m[ 0] = m00;
    m[ 1] = m01;
    m[ 2] = m02;
    m[ 3] = m03;
    m[ 4] = m10;
    m[ 5] = m11;
    m[ 6] = m12;
    m[ 7] = m13;
    m[ 8] = m20;
    m[ 9] = m21;
    m[10] = m22;
    m[11] = m23;
    m[12] = m30;
    m[13] = m31;
    m[14] = m32;
    m[15] = m33;
}

template<class t_Ty>
inline matrix4x4<t_Ty>::matrix4x4 (const t_Ty entry[16], bool colMajor)
{
    if (colMajor)
    {
        m[ 0] = entry[ 0];
        m[ 1] = entry[ 1];
        m[ 2] = entry[ 2];
        m[ 3] = entry[ 3];
        m[ 4] = entry[ 4];
        m[ 5] = entry[ 5];
        m[ 6] = entry[ 6];
        m[ 7] = entry[ 7];
        m[ 8] = entry[ 8];
        m[ 9] = entry[ 9];
        m[10] = entry[10];
        m[11] = entry[11];
        m[12] = entry[12];
        m[13] = entry[13];
        m[14] = entry[14];
        m[15] = entry[15];
    }
    else
    {
        m[ 0] = entry[ 0];
        m[ 1] = entry[ 4];
        m[ 2] = entry[ 8];
        m[ 3] = entry[12];
        m[ 4] = entry[ 1];
        m[ 5] = entry[ 5];
        m[ 6] = entry[ 9];
        m[ 7] = entry[13];
        m[ 8] = entry[ 2];
        m[ 9] = entry[ 6];
        m[10] = entry[10];
        m[11] = entry[14];
        m[12] = entry[ 3];
        m[13] = entry[ 7];
        m[14] = entry[11];
        m[15] = entry[15];
    }
}

template<class t_Ty>
inline matrix4x4<t_Ty>& matrix4x4<t_Ty>::operator= (const matrix4x4<t_Ty>& mat)
{
    m[ 0] = mat.m[ 0];
    m[ 1] = mat.m[ 1];
    m[ 2] = mat.m[ 2];
    m[ 3] = mat.m[ 3];
    m[ 4] = mat.m[ 4];
    m[ 5] = mat.m[ 5];
    m[ 6] = mat.m[ 6];
    m[ 7] = mat.m[ 7];
    m[ 8] = mat.m[ 8];
    m[ 9] = mat.m[ 9];
    m[10] = mat.m[10];
    m[11] = mat.m[11];
    m[12] = mat.m[12];
    m[13] = mat.m[13];
    m[14] = mat.m[14];
    m[15] = mat.m[15];
    return *this;
}

template<class t_Ty>
inline void matrix4x4<t_Ty>::makeZero ()
{
    m[ 0] = (t_Ty)0;
    m[ 1] = (t_Ty)0;
    m[ 2] = (t_Ty)0;
    m[ 3] = (t_Ty)0;
    m[ 4] = (t_Ty)0;
    m[ 5] = (t_Ty)0;
    m[ 6] = (t_Ty)0;
    m[ 7] = (t_Ty)0;
    m[ 8] = (t_Ty)0;
    m[ 9] = (t_Ty)0;
    m[10] = (t_Ty)0;
    m[11] = (t_Ty)0;
    m[12] = (t_Ty)0;
    m[13] = (t_Ty)0;
    m[14] = (t_Ty)0;
    m[15] = (t_Ty)0;
}

template<class t_Ty>
inline void matrix4x4<t_Ty>::makeIdentity ()
{
    m[ 0] = (t_Ty)1;
    m[ 1] = (t_Ty)0;
    m[ 2] = (t_Ty)0;
    m[ 3] = (t_Ty)0;
    m[ 4] = (t_Ty)0;
    m[ 5] = (t_Ty)1;
    m[ 6] = (t_Ty)0;
    m[ 7] = (t_Ty)0;
    m[ 8] = (t_Ty)0;
    m[ 9] = (t_Ty)0;
    m[10] = (t_Ty)1;
    m[11] = (t_Ty)0;
    m[12] = (t_Ty)0;
    m[13] = (t_Ty)0;
    m[14] = (t_Ty)0;
    m[15] = (t_Ty)1;
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator+ (const matrix4x4<t_Ty>& mat) const
{
    return matrix4x4
        (
        m[ 0] + mat.m[ 0],
        m[ 1] + mat.m[ 1],
        m[ 2] + mat.m[ 2],
        m[ 3] + mat.m[ 3],
        m[ 4] + mat.m[ 4],
        m[ 5] + mat.m[ 5],
        m[ 6] + mat.m[ 6],
        m[ 7] + mat.m[ 7],
        m[ 8] + mat.m[ 8],
        m[ 9] + mat.m[ 9],
        m[10] + mat.m[10],
        m[11] + mat.m[11],
        m[12] + mat.m[12],
        m[13] + mat.m[13],
        m[14] + mat.m[14],
        m[15] + mat.m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator- (const matrix4x4<t_Ty>& mat) const
{
    return matrix4x4<t_Ty>
        (
        m[ 0] - mat.m[ 0],
        m[ 1] - mat.m[ 1],
        m[ 2] - mat.m[ 2],
        m[ 3] - mat.m[ 3],
        m[ 4] - mat.m[ 4],
        m[ 5] - mat.m[ 5],
        m[ 6] - mat.m[ 6],
        m[ 7] - mat.m[ 7],
        m[ 8] - mat.m[ 8],
        m[ 9] - mat.m[ 9],
        m[10] - mat.m[10],
        m[11] - mat.m[11],
        m[12] - mat.m[12],
        m[13] - mat.m[13],
        m[14] - mat.m[14],
        m[15] - mat.m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix4x4<t_Ty>
        (
        scalar*m[ 0],
        scalar*m[ 1],
        scalar*m[ 2],
        scalar*m[ 3],
        scalar*m[ 4],
        scalar*m[ 5],
        scalar*m[ 6],
        scalar*m[ 7],
        scalar*m[ 8],
        scalar*m[ 9],
        scalar*m[10],
        scalar*m[11],
        scalar*m[12],
        scalar*m[13],
        scalar*m[14],
        scalar*m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix4x4
            (
            invScalar*m[ 0],
            invScalar*m[ 1],
            invScalar*m[ 2],
            invScalar*m[ 3],
            invScalar*m[ 4],
            invScalar*m[ 5],
            invScalar*m[ 6],
            invScalar*m[ 7],
            invScalar*m[ 8],
            invScalar*m[ 9],
            invScalar*m[10],
            invScalar*m[11],
            invScalar*m[12],
            invScalar*m[13],
            invScalar*m[14],
            invScalar*m[15]
        );
    }
    else
    {
        return matrix4x4
            (
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max(),
            std::numeric_limits<t_Ty>::max()
            );
    }
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator- () const
{
    return matrix4x4<t_Ty>
        (
        -m[ 0],
        -m[ 1],
        -m[ 2],
        -m[ 3],
        -m[ 4],
        -m[ 5],
        -m[ 6],
        -m[ 7],
        -m[ 8],
        -m[ 9],
        -m[10],
        -m[11],
        -m[12],
        -m[13],
        -m[14],
        -m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty>& matrix4x4<t_Ty>::operator+= (const matrix4x4<t_Ty>& mat)
{
    m[ 0] += mat.m[ 0];
    m[ 1] += mat.m[ 1];
    m[ 2] += mat.m[ 2];
    m[ 3] += mat.m[ 3];
    m[ 4] += mat.m[ 4];
    m[ 5] += mat.m[ 5];
    m[ 6] += mat.m[ 6];
    m[ 7] += mat.m[ 7];
    m[ 8] += mat.m[ 8];
    m[ 9] += mat.m[ 9];
    m[10] += mat.m[10];
    m[11] += mat.m[11];
    m[12] += mat.m[12];
    m[13] += mat.m[13];
    m[14] += mat.m[14];
    m[15] += mat.m[15];
    return *this;
}

template<class t_Ty>
inline matrix4x4<t_Ty>& matrix4x4<t_Ty>::operator-= (const matrix4x4<t_Ty>& mat)
{
    m[ 0] -= mat.m[ 0];
    m[ 1] -= mat.m[ 1];
    m[ 2] -= mat.m[ 2];
    m[ 3] -= mat.m[ 3];
    m[ 4] -= mat.m[ 4];
    m[ 5] -= mat.m[ 5];
    m[ 6] -= mat.m[ 6];
    m[ 7] -= mat.m[ 7];
    m[ 8] -= mat.m[ 8];
    m[ 9] -= mat.m[ 9];
    m[10] -= mat.m[10];
    m[11] -= mat.m[11];
    m[12] -= mat.m[12];
    m[13] -= mat.m[13];
    m[14] -= mat.m[14];
    m[15] -= mat.m[15];
    return *this;
}

template<class t_Ty>
inline matrix4x4<t_Ty>& matrix4x4<t_Ty>::operator*= (t_Ty scalar)
{
    m[ 0] *= scalar;
    m[ 1] *= scalar;
    m[ 2] *= scalar;
    m[ 3] *= scalar;
    m[ 4] *= scalar;
    m[ 5] *= scalar;
    m[ 6] *= scalar;
    m[ 7] *= scalar;
    m[ 8] *= scalar;
    m[ 9] *= scalar;
    m[10] *= scalar;
    m[11] *= scalar;
    m[12] *= scalar;
    m[13] *= scalar;
    m[14] *= scalar;
    m[15] *= scalar;
    return *this;
}

template<class t_Ty>
inline matrix4x4<t_Ty>& matrix4x4<t_Ty>::operator/= (t_Ty scalar)
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        m[ 0] *= invScalar;
        m[ 1] *= invScalar;
        m[ 2] *= invScalar;
        m[ 3] *= invScalar;
        m[ 4] *= invScalar;
        m[ 5] *= invScalar;
        m[ 6] *= invScalar;
        m[ 7] *= invScalar;
        m[ 8] *= invScalar;
        m[ 9] *= invScalar;
        m[10] *= invScalar;
        m[11] *= invScalar;
        m[12] *= invScalar;
        m[13] *= invScalar;
        m[14] *= invScalar;
        m[15] *= invScalar;
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        m[ 0] = max;
        m[ 1] = max;
        m[ 2] = max;
        m[ 3] = max;
        m[ 4] = max;
        m[ 5] = max;
        m[ 6] = max;
        m[ 7] = max;
        m[ 8] = max;
        m[ 9] = max;
        m[10] = max;
        m[11] = max;
        m[12] = max;
        m[13] = max;
        m[14] = max;
        m[15] = max;
    }

    return *this;
}

template<class t_Ty>
inline vector4<t_Ty> matrix4x4<t_Ty>::operator* (const vector4<t_Ty>& vec) const
{
    return vector4<t_Ty>
        (
        m[ 0]*vec[0] +
        m[ 4]*vec[1] +
        m[ 8]*vec[2] +
        m[12]*vec[3],

        m[ 1]*vec[0] +
        m[ 5]*vec[1] +
        m[ 9]*vec[2] +
        m[13]*vec[3],

        m[ 2]*vec[0] +
        m[ 6]*vec[1] +
        m[10]*vec[2] +
        m[14]*vec[3],

        m[ 3]*vec[0] +
        m[ 7]*vec[1] +
        m[11]*vec[2] +
        m[15]*vec[3]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::transpose () const
{
    return matrix4x4<t_Ty>
        (
        m[ 0],
        m[ 4],
        m[ 8],
        m[12],
        m[ 1],
        m[ 5],
        m[ 9],
        m[13],
        m[ 2],
        m[ 6],
        m[10],
        m[14],
        m[ 3],
        m[ 7],
        m[11],
        m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::operator* (const matrix4x4<t_Ty>& mat) const
{
    // A*B
    return matrix4x4<t_Ty>
        (
        m[ 0]*mat.m[0] +
        m[ 4]*mat.m[1] +
        m[ 8]*mat.m[2] +
        m[12]*mat.m[3],

        m[ 1]*mat.m[0] +
        m[ 5]*mat.m[1] +
        m[ 9]*mat.m[2] +
        m[13]*mat.m[3],

        m[ 2]*mat.m[0] +
        m[ 6]*mat.m[1] +
        m[10]*mat.m[2] +
        m[14]*mat.m[3],

        m[ 3]*mat.m[0] +
        m[ 7]*mat.m[1] +
        m[11]*mat.m[2] +
        m[15]*mat.m[3],

        m[ 0]*mat.m[4] +
        m[ 4]*mat.m[5] +
        m[ 8]*mat.m[6] +
        m[12]*mat.m[7],

        m[ 1]*mat.m[4] +
        m[ 5]*mat.m[5] +
        m[ 9]*mat.m[6] +
        m[13]*mat.m[7],

        m[ 2]*mat.m[4] +
        m[ 6]*mat.m[5] +
        m[10]*mat.m[6] +
        m[14]*mat.m[7],

        m[ 3]*mat.m[4] +
        m[ 7]*mat.m[5] +
        m[11]*mat.m[6] +
        m[15]*mat.m[7],

        m[ 0]*mat.m[8]  +
        m[ 4]*mat.m[9]  +
        m[ 8]*mat.m[10] +
        m[12]*mat.m[11],

        m[ 1]*mat.m[8]  +
        m[ 5]*mat.m[9]  +
        m[ 9]*mat.m[10] +
        m[13]*mat.m[11],

        m[ 2]*mat.m[8]  +
        m[ 6]*mat.m[9]  +
        m[10]*mat.m[10] +
        m[14]*mat.m[11],

        m[ 3]*mat.m[8]  +
        m[ 7]*mat.m[9]  +
        m[11]*mat.m[10] +
        m[15]*mat.m[11],

        m[ 0]*mat.m[12] +
        m[ 4]*mat.m[13] +
        m[ 8]*mat.m[14] +
        m[12]*mat.m[15],

        m[ 1]*mat.m[12] +
        m[ 5]*mat.m[13] +
        m[ 9]*mat.m[14] +
        m[13]*mat.m[15],

        m[ 2]*mat.m[12] +
        m[ 6]*mat.m[13] +
        m[10]*mat.m[14] +
        m[14]*mat.m[15],

        m[ 3]*mat.m[12] +
        m[ 7]*mat.m[13] +
        m[11]*mat.m[14] +
        m[15]*mat.m[15]
    );
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::inverse (t_Ty epsilon) const
{    
    t_Ty a0 = m[ 0]*m[ 5] - m[ 4]*m[ 1];
    t_Ty a1 = m[ 0]*m[ 9] - m[ 8]*m[ 1];
    t_Ty a2 = m[ 0]*m[13] - m[12]*m[ 1];
    t_Ty a3 = m[ 4]*m[ 9] - m[ 8]*m[ 5];
    t_Ty a4 = m[ 4]*m[13] - m[12]*m[ 5];
    t_Ty a5 = m[ 8]*m[13] - m[12]*m[ 9];
    t_Ty b0 = m[ 2]*m[ 7] - m[ 6]*m[ 3];
    t_Ty b1 = m[ 2]*m[11] - m[10]*m[ 3];
    t_Ty b2 = m[ 2]*m[15] - m[14]*m[ 3];
    t_Ty b3 = m[ 6]*m[11] - m[10]*m[ 7];
    t_Ty b4 = m[ 6]*m[15] - m[14]*m[ 7];
    t_Ty b5 = m[10]*m[15] - m[14]*m[11];

    t_Ty det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    if (fabs(det) > epsilon)
    {
        matrix4x4<t_Ty> inverse;
        inverse.m[ 0] = + m[ 5]*b5 - m[ 9]*b4 + m[13]*b3;
        inverse.m[ 1] = - m[ 1]*b5 + m[ 9]*b2 - m[13]*b1;
        inverse.m[ 2] = + m[ 1]*b4 - m[ 5]*b2 + m[13]*b0;
        inverse.m[ 3] = - m[ 1]*b3 + m[ 5]*b1 - m[ 9]*b0;
        inverse.m[ 4] = - m[ 4]*b5 + m[ 8]*b4 - m[12]*b3;
        inverse.m[ 5] = + m[ 0]*b5 - m[ 8]*b2 + m[12]*b1;
        inverse.m[ 6] = - m[ 0]*b4 + m[ 4]*b2 - m[12]*b0;
        inverse.m[ 7] = + m[ 0]*b3 - m[ 4]*b1 + m[ 8]*b0;
        inverse.m[ 8] = + m[ 7]*a5 - m[11]*a4 + m[15]*a3;
        inverse.m[ 9] = - m[ 3]*a5 + m[11]*a2 - m[15]*a1;
        inverse.m[10] = + m[ 3]*a4 - m[ 7]*a2 + m[15]*a0;
        inverse.m[11] = - m[ 3]*a3 + m[ 7]*a1 - m[11]*a0;
        inverse.m[12] = - m[ 6]*a5 + m[10]*a4 - m[14]*a3;
        inverse.m[13] = + m[ 2]*a5 - m[10]*a2 + m[14]*a1;
        inverse.m[14] = - m[ 2]*a4 + m[ 6]*a2 - m[14]*a0;
        inverse.m[15] = + m[ 2]*a3 - m[ 6]*a1 + m[10]*a0;

        t_Ty invDet = ((t_Ty)1)/det;
        inverse.m[ 0] *= invDet;
        inverse.m[ 4] *= invDet;
        inverse.m[ 8] *= invDet;
        inverse.m[12] *= invDet;
        inverse.m[ 1] *= invDet;
        inverse.m[ 5] *= invDet;
        inverse.m[ 9] *= invDet;
        inverse.m[13] *= invDet;
        inverse.m[ 2] *= invDet;
        inverse.m[ 6] *= invDet;
        inverse.m[10] *= invDet;
        inverse.m[14] *= invDet;
        inverse.m[ 3] *= invDet;
        inverse.m[ 7] *= invDet;
        inverse.m[11] *= invDet;
        inverse.m[15] *= invDet;

        return inverse;
    }

    return ZERO;
}

template<class t_Ty>
inline matrix4x4<t_Ty> matrix4x4<t_Ty>::adjoint () const
{
    t_Ty a0 = m[ 0]*m[ 5] - m[ 4]*m[ 1];
    t_Ty a1 = m[ 0]*m[ 9] - m[ 8]*m[ 1];
    t_Ty a2 = m[ 0]*m[13] - m[12]*m[ 1];
    t_Ty a3 = m[ 4]*m[ 9] - m[ 8]*m[ 5];
    t_Ty a4 = m[ 4]*m[13] - m[12]*m[ 5];
    t_Ty a5 = m[ 8]*m[13] - m[12]*m[ 9];
    t_Ty b0 = m[ 2]*m[ 7] - m[ 6]*m[ 3];
    t_Ty b1 = m[ 2]*m[11] - m[10]*m[ 3];
    t_Ty b2 = m[ 2]*m[15] - m[14]*m[ 3];
    t_Ty b3 = m[ 6]*m[11] - m[10]*m[ 7];
    t_Ty b4 = m[ 6]*m[15] - m[14]*m[ 7];
    t_Ty b5 = m[10]*m[15] - m[14]*m[11];

    return matrix4x4<t_Ty>
        (
        + m[ 5]*b5 - m[ 9]*b4 + m[13]*b3, // 0
        - m[ 1]*b5 + m[ 9]*b2 - m[13]*b1, // 1
        + m[ 1]*b4 - m[ 5]*b2 + m[13]*b0, // 2
        - m[ 1]*b3 + m[ 5]*b1 - m[ 9]*b0, // 3

        - m[ 4]*b5 + m[ 8]*b4 - m[12]*b3, // 4
        + m[ 0]*b5 - m[ 8]*b2 + m[12]*b1, // 5
        - m[ 0]*b4 + m[ 4]*b2 - m[12]*b0, // 6
        + m[ 0]*b3 - m[ 4]*b1 + m[ 8]*b0, // 7

        + m[ 7]*a5 - m[11]*a4 + m[15]*a3, // 8
        - m[ 3]*a5 + m[11]*a2 - m[15]*a1, // 9
        + m[ 3]*a4 - m[ 7]*a2 + m[15]*a0, // 10
        - m[ 3]*a3 + m[ 7]*a1 - m[11]*a0, // 11

        - m[ 6]*a5 + m[10]*a4 - m[14]*a3, // 12
        + m[ 2]*a5 - m[10]*a2 + m[14]*a1, // 13
        - m[ 2]*a4 + m[ 6]*a2 - m[14]*a0, // 14
        + m[ 2]*a3 - m[ 6]*a1 + m[10]*a0  // 15
        );
}

template<class t_Ty>
inline t_Ty matrix4x4<t_Ty>::determinant () const
{
    t_Ty a0 = m[ 0]*m[ 5] - m[ 4]*m[ 1];
    t_Ty a1 = m[ 0]*m[ 9] - m[ 8]*m[ 1];
    t_Ty a2 = m[ 0]*m[13] - m[12]*m[ 1];
    t_Ty a3 = m[ 4]*m[ 9] - m[ 8]*m[ 5];
    t_Ty a4 = m[ 4]*m[13] - m[12]*m[ 5];
    t_Ty a5 = m[ 8]*m[13] - m[12]*m[ 9];
    t_Ty b0 = m[ 2]*m[ 7] - m[ 6]*m[ 3];
    t_Ty b1 = m[ 2]*m[11] - m[10]*m[ 3];
    t_Ty b2 = m[ 2]*m[15] - m[14]*m[ 3];
    t_Ty b3 = m[ 6]*m[11] - m[10]*m[ 7];
    t_Ty b4 = m[ 6]*m[15] - m[14]*m[ 7];
    t_Ty b5 = m[10]*m[15] - m[14]*m[11];
    t_Ty det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    return det;
}

template<class t_Ty>
inline void matrix4x4<t_Ty>::makeObliqueProjection (const vector3<t_Ty>& normal,
    const vector3<t_Ty>& origin, const vector3<t_Ty>& direction)
{
    // The projection plane is dot(N,X-P) = 0 where N is a 3-by-1 unit-length
    // normal vector and P is a 3-by-1 point on the plane.  The projection
    // is oblique to the plane, in the direction of the 3-by-1 vector D.
    // Necessarily dot(N,D) is not zero for this projection to make sense.
    // Given a 3-by-1 point U, compute the intersection of the line U+t*D
    // with the plane to obtain t = -dot(N,U-P)/dot(N,D).  Then
    //
    //   projection(U) = P + [I - D*N^t_Ty/dot(N,D)]*(U-P)
    //
    // A 4-by-4 homogeneous transformation representing the projection is
    //
    //       +-                               -+
    //   M = | D*N^t_Ty - dot(N,D)*I   -dot(N,P)D |
    //       |          0^t_Ty          -dot(N,D) |
    //       +-                               -+
    //
    // where M applies to [U^t_Ty 1]^t_Ty by M*[U^t_Ty 1]^t_Ty.  The matrix is chosen so
    // that M[3][3] > 0 whenever dot(N,D) < 0 (projection is onto the
    // "positive side" of the plane).

    t_Ty dotND = normal.dot(direction);
    t_Ty dotNO = normal.dot(origin);
    m[ 0] = direction[0]*normal[0] - dotND;
    m[ 4] = direction[0]*normal[1];
    m[ 8] = direction[0]*normal[2];
    m[ 12] = -dotNO*direction[0];
    m[ 1] = direction[1]*normal[0];
    m[ 5] = direction[1]*normal[1] - dotND;
    m[ 9] = direction[1]*normal[2];
    m[ 13] = -dotNO*direction[1];
    m[ 2] = direction[2]*normal[0];
    m[ 6] = direction[2]*normal[1];
    m[10] = direction[2]*normal[2] - dotND;
    m[14] = -dotNO*direction[2];
    m[ 3] = (t_Ty)0.0;
    m[ 7] = (t_Ty)0.0;
    m[11] = (t_Ty)0.0;
    m[15] = -dotND;
}

template<class t_Ty>
inline void matrix4x4<t_Ty>::makePerspectiveProjection (
    const vector3<t_Ty>& normal, const vector3<t_Ty>& origin,
    const vector3<t_Ty>& eye)
{
    //     +-                                                 -+
    // M = | dot(N,E-P)*I - E*N^t_Ty    -(dot(N,E-P)*I - E*N^t_Ty)*E |
    //     |        -N^t                      dot(N,E)         |
    //     +-                                                 -+
    //
    // where E is the eye point, P is a point on the plane, and N is a
    // unit-length plane normal.

    t_Ty dotND = normal.dot(eye - origin);
    m[ 0] = dotND - eye[0]*normal[0];
    m[ 4] = -eye[0]*normal[1];
    m[ 8] = -eye[0]*normal[2];
    m[ 12] = -(m[0]*eye[0] + m[1]*eye[1] + m[2]*eye[2]);
    m[ 1] = -eye[1]*normal[0];
    m[ 5] = dotND - eye[1]*normal[1];
    m[ 9] = -eye[1]*normal[2];
    m[ 13] = -(m[4]*eye[0] + m[5]*eye[1] + m[6]*eye[2]);
    m[ 2] = -eye[2]*normal[0];
    m[ 6] = -eye[2]*normal[1];
    m[10] = dotND- eye[2]*normal[2];
    m[14] = -(m[8]*eye[0] + m[9]*eye[1] + m[10]*eye[2]);
    m[ 3] = -normal[0];
    m[ 7] = -normal[1];
    m[11] = -normal[2];
    m[15] = normal.dot(eye);
}

template<class t_Ty>
inline void matrix4x4<t_Ty>::makeReflection (const vector3<t_Ty>& normal,
    const vector3<t_Ty>& origin)
{
    //     +-                         -+
    // M = | I-2*N*N^t_Ty    2*dot(N,P)*N |
    //     |     0^t_Ty            1      |
    //     +-                         -+
    //
    // where P is a point on the plane and N is a unit-length plane normal.

    t_Ty twoDotNO = ((t_Ty)2)*(normal.dot(origin));
    m[ 0] = (t_Ty)1 - ((t_Ty)2)*normal[0]*normal[0];
    m[ 4] = -((t_Ty)2)*normal[0]*normal[1];
    m[ 8] = -((t_Ty)2)*normal[0]*normal[2];
    m[ 12] = twoDotNO*normal[0];
    m[ 1] = -((t_Ty)2)*normal[1]*normal[0];
    m[ 5] = (t_Ty)1 - ((t_Ty)2)*normal[1]*normal[1];
    m[ 9] = -((t_Ty)2)*normal[1]*normal[2];
    m[ 13] = twoDotNO*normal[1];
    m[ 2] = -((t_Ty)2)*normal[2]*normal[0];
    m[ 6] = -((t_Ty)2)*normal[2]*normal[1];
    m[10] = (t_Ty)1 - ((t_Ty)2)*normal[2]*normal[2];
    m[14] = twoDotNO*normal[2];
    m[3] = (t_Ty)0;
    m[7] = (t_Ty)0;
    m[11] = (t_Ty)0;
    m[15] = (t_Ty)1;
}

template<class t_Ty>
inline matrix4x4<t_Ty> operator* (t_Ty scalar, const matrix4x4<t_Ty>& mat)
{
    return mat*scalar;
}

template<class t_Ty>
inline vector4<t_Ty> operator* (const vector4<t_Ty>& vec,
    const matrix4x4<t_Ty>& mat)
{
    return vector4<t_Ty>(
        vec[0]*mat[0][0]+vec[1]*mat[0][1]+vec[2]*mat[0][2]+vec[3]*mat[0][3],
        vec[0]*mat[1][0]+vec[1]*mat[1][1]+vec[2]*mat[1][2]+vec[3]*mat[1][3],
        vec[0]*mat[2][0]+vec[1]*mat[2][1]+vec[2]*mat[2][2]+vec[3]*mat[2][3],
        vec[0]*mat[3][0]+vec[1]*mat[3][1]+vec[2]*mat[3][2]+vec[3]*mat[3][3]);
}

