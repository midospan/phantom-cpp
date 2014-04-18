
template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (bool doMakeZero)
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
inline matrix2x2<t_Ty>::matrix2x2 (const matrix2x2<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (t_Ty m00, t_Ty m01, t_Ty m10, t_Ty m11)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m10;
    m[3] = m11;
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (const t_Ty entry[4], bool colMajor)
{
    if (colMajor)
    {
        m[0] = entry[0];
        m[1] = entry[1];
        m[2] = entry[2];
        m[3] = entry[3];
    }
    else
    {
        m[0] = entry[0];
        m[1] = entry[2];
        m[2] = entry[1];
        m[3] = entry[3];
    }
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (const vector2<t_Ty>& u, const vector2<t_Ty>& v,
    bool columns)
{
    if (columns)
    {
        m[0] = u[0];
        m[1] = u[1];
        m[2] = v[0];
        m[3] = v[1];
    }
    else
    {
        m[0] = u[0];
        m[1] = v[0];
        m[2] = u[1];
        m[3] = v[1];
    }
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (const vector2<t_Ty>* v, bool columns)
{
    if (columns)
    {
        m[0] = v[0][0];
        m[1] = v[0][1];
        m[2] = v[1][0];
        m[3] = v[1][1];
    }
    else
    {
        m[0] = v[0][0];
        m[1] = v[1][0];
        m[2] = v[0][1];
        m[3] = v[1][1];
    }
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (t_Ty m00, t_Ty m11)
{
    makeDiagonal(m00, m11);
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (t_Ty angle)
{
    makeRotation(angle);
}


template<class t_Ty>
inline matrix2x2<t_Ty>::matrix2x2 (const vector2<t_Ty>& u, const vector2<t_Ty>& v)
{
    makeTensorProduct(u, v);
}


template<class t_Ty>
inline matrix2x2<t_Ty>& matrix2x2<t_Ty>::operator= (const matrix2x2<t_Ty>& mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    return *this;
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::makeZero ()
{
    m[0] = (t_Ty)0;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::makeIdentity ()
{
    m[0] = (t_Ty)1;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)1;
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::makeDiagonal (t_Ty m00, t_Ty m11)
{
    m[0] = m00;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = m11;
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::makeRotation (t_Ty angle)
{
    m[0] = cosf(angle);
    m[1] = sinf(angle);
    m[2] = -m[1];
    m[3] =  m[0];
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::makeTensorProduct (const vector2<t_Ty>& u,
    const vector2<t_Ty>& v)
{
    m[0] = u[0]*v[0];
    m[2] = u[0]*v[1];
    m[1] = u[1]*v[0];
    m[3] = u[1]*v[1];
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator+ (const matrix2x2<t_Ty>& mat) const
{
    return matrix2x2
    (
        m[0] + mat.m[0],
        m[1] + mat.m[1],
        m[2] + mat.m[2],
        m[3] + mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator- (const matrix2x2<t_Ty>& mat)
    const
{
    return matrix2x2
    (
        m[0] - mat.m[0],
        m[1] - mat.m[1],
        m[2] - mat.m[2],
        m[3] - mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix2x2
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix2x2
        (
            invScalar*m[0],
            invScalar*m[1],
            invScalar*m[2],
            invScalar*m[3]
        );
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        return matrix2x2
        (
            max,
            max,
            max,
            max
        );
    }
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator- () const
{
    return matrix2x2
    (
        -m[0],
        -m[1],
        -m[2],
        -m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty>& matrix2x2<t_Ty>::operator+= (const matrix2x2<t_Ty>& mat)
{
    m[0] += mat.m[0];
    m[1] += mat.m[1];
    m[2] += mat.m[2];
    m[3] += mat.m[3];
    return *this;
}


template<class t_Ty>
inline matrix2x2<t_Ty>& matrix2x2<t_Ty>::operator-= (const matrix2x2<t_Ty>& mat)
{
    m[0] -= mat.m[0];
    m[1] -= mat.m[1];
    m[2] -= mat.m[2];
    m[3] -= mat.m[3];
    return *this;
}


template<class t_Ty>
inline matrix2x2<t_Ty>& matrix2x2<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    return *this;
}


template<class t_Ty>
inline matrix2x2<t_Ty>& matrix2x2<t_Ty>::operator/= (t_Ty scalar)
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        m[0] *= invScalar;
        m[1] *= invScalar;
        m[2] *= invScalar;
        m[3] *= invScalar;
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        m[0] = max;
        m[1] = max;
        m[2] = max;
        m[3] = max;
    }

    return *this;
}


template<class t_Ty>
inline vector2<t_Ty> matrix2x2<t_Ty>::operator* (const vector2<t_Ty>& vec) const
{
    return vector2<t_Ty>
    (
        m[0]*vec[0] + m[2]*vec[1],
        m[1]*vec[0] + m[3]*vec[1]
    );
}


template<class t_Ty>
inline t_Ty matrix2x2<t_Ty>::qForm (const vector2<t_Ty>& u, const vector2<t_Ty>& v)
    const
{
    return u.dot((*this)*v);
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::transpose () const
{
    return matrix2x2
    (
        m[0],
        m[2],
        m[1],
        m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::operator* (const matrix2x2<t_Ty>& mat) const
{
    // A*B
    return matrix2x2
    (
        m[0]*mat.m[0] + m[2]*mat.m[1],
        m[1]*mat.m[0] + m[3]*mat.m[1],
        m[0]*mat.m[2] + m[2]*mat.m[3],
        m[1]*mat.m[2] + m[3]*mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::transposeTimes (const matrix2x2<t_Ty>& mat) const
{
// A^t_Ty*B
    return matrix2x2
    (
        m[0]*mat.m[0] + m[2]*mat.m[2],
        m[1]*mat.m[0] + m[3]*mat.m[2],
        m[1]*mat.m[1] + m[3]*mat.m[3],
        m[0]*mat.m[1] + m[2]*mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::timesTranspose (const matrix2x2<t_Ty>& mat) const
{
    // A*B^t_Ty
    return matrix2x2
    (
        m[0]*mat.m[0] + m[1]*mat.m[1],
        m[2]*mat.m[0] + m[3]*mat.m[1],
        m[0]*mat.m[2] + m[1]*mat.m[3],
        m[2]*mat.m[2] + m[3]*mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::transposeTimesTranspose (const matrix2x2<t_Ty>& mat)
    const
{
    // A^t_Ty*B^t_Ty
    return matrix2x2
    (
        m[0]*mat.m[0] + m[1]*mat.m[2],
        m[2]*mat.m[0] + m[3]*mat.m[2],
        m[0]*mat.m[1] + m[1]*mat.m[3],
        m[2]*mat.m[1] + m[3]*mat.m[3]
    );
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::inverse (t_Ty epsilon) const
{
    matrix2x2<t_Ty> inverse;

    t_Ty det = m[0]*m[3] - m[2]*m[1];
    if (fabs(det) > epsilon)
    {
        t_Ty invDet = ((t_Ty)1)/det;
        inverse.m[0] =  m[3]*invDet;
        inverse.m[2] = -m[2]*invDet;
        inverse.m[1] = -m[1]*invDet;
        inverse.m[3] =  m[0]*invDet;
    }
    else
    {
        inverse.m[0] = (t_Ty)0;
        inverse.m[2] = (t_Ty)0;
        inverse.m[1] = (t_Ty)0;
        inverse.m[3] = (t_Ty)0;
    }

    return inverse;
}


template<class t_Ty>
inline matrix2x2<t_Ty> matrix2x2<t_Ty>::adjoint () const
{
    return matrix2x2(m[3], -m[1], -m[2], m[0]);
}


template<class t_Ty>
inline t_Ty matrix2x2<t_Ty>::determinant () const
{
    return m[0]*m[3] - m[1]*m[2];
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::extractAngle (t_Ty& angle) const
{
    // assert:  'this' matrix represents a rotation
    angle = atan2f(m[1], m[0]);
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1], then orthonormal output matrix is Q = [q0|q1],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // Compute q0.
    t_Ty invLength = invSqrt(m[0]*m[0] +
        m[1]*m[1]);

    m[0] *= invLength;
    m[1] *= invLength;

    // Compute q1.
    t_Ty dot0 = m[0]*m[2] + m[1]*m[3];
    m[2] -= dot0*m[0];
    m[3] -= dot0*m[1];

    invLength = invSqrt(m[2]*m[2] +
        m[3]*m[3]);

    m[2] *= invLength;
    m[3] *= invLength;
}


template<class t_Ty>
inline void matrix2x2<t_Ty>::eigenDecomposition (matrix2x2<t_Ty>& rot, matrix2x2<t_Ty>& diag) const
{
    t_Ty sum = fabs(m[0]) + fabs(m[3]);
    if (fabs(m[2]) + sum == sum)
    {
        // The matrix M is diagonal (within numerical round-off).
        rot.m[0] = (t_Ty)1;
        rot.m[1] = (t_Ty)0;
        rot.m[2] = (t_Ty)0;
        rot.m[3] = (t_Ty)1;
        diag.m[0] = m[0];
        diag.m[1] = (t_Ty)0;
        diag.m[2] = (t_Ty)0;
        diag.m[3] = m[3];
        return;
    }

    t_Ty trace = m[0] + m[3];
    t_Ty diff = m[0] - m[3];
    t_Ty discr = sqrtf(diff*diff + ((t_Ty)4)*m[2]*m[2]);
    t_Ty eigVal0 = ((t_Ty)0.5)*(trace - discr);
    t_Ty eigVal1 = ((t_Ty)0.5)*(trace + discr);
    diag.makeDiagonal(eigVal0, eigVal1);

    t_Ty cs, sn;
    if (diff >= (t_Ty)0)
    {
        cs = m[2];
        sn = eigVal0 - m[0];
    }
    else
    {
        cs = eigVal0 - m[3];
        sn = m[2];
    }
    t_Ty invLength = invSqrt(cs*cs + sn*sn);
    cs *= invLength;
    sn *= invLength;

    rot.m[0] = cs;
    rot.m[2] = -sn;
    rot.m[1] = sn;
    rot.m[3] = cs;
}


template<class t_Ty>
inline matrix2x2<t_Ty> operator* (t_Ty scalar, const matrix2x2<t_Ty>& mat)
{
    return mat*scalar;
}


template<class t_Ty>
inline vector2<t_Ty> operator* (const vector2<t_Ty>& vec,
    const matrix2x2<t_Ty>& mat)
{
    return vector2<t_Ty>
    (
        vec[0]*mat[0][0] + vec[1]*mat[0][1],
        vec[0]*mat[1][0] + vec[1]*mat[1][1]
    );
}

