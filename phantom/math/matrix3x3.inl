
template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (bool doMakeZero)
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
inline matrix3x3<t_Ty>::matrix3x3 (const matrix3x3<t_Ty>& mat)
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
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (t_Ty m00, t_Ty m01, t_Ty m02, t_Ty m10, t_Ty m11,
    t_Ty m12, t_Ty m20, t_Ty m21, t_Ty m22)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m10;
    m[4] = m11;
    m[5] = m12;
    m[6] = m20;
    m[7] = m21;
    m[8] = m22;
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (const t_Ty entry[9], bool colMajor)
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
    }
    else
    {
        m[0] = entry[0];
        m[1] = entry[3];
        m[2] = entry[6];
        m[3] = entry[1];
        m[4] = entry[4];
        m[5] = entry[7];
        m[6] = entry[2];
        m[7] = entry[5];
        m[8] = entry[8];
    }
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (const vector3<t_Ty>& u, const vector3<t_Ty>& v,
    const vector3<t_Ty>& w, bool columns)
{
    if (columns)
    {
        m[0] = u[0];
        m[1] = u[1];
        m[2] = u[2];
        m[3] = v[0];
        m[4] = v[1];
        m[5] = v[2];
        m[6] = w[0];
        m[7] = w[1];
        m[8] = w[2];
    }
    else
    {
        m[0] = u[0];
        m[1] = v[0];
        m[2] = w[0];
        m[3] = u[1];
        m[4] = v[1];
        m[5] = w[1];
        m[6] = u[2];
        m[7] = v[2];
        m[8] = w[2];
    }
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (const vector3<t_Ty>* v, bool columns)
{
    if (columns)
    {
        m[0] = v[0][0];
        m[1] = v[0][1];
        m[2] = v[0][2];
        m[3] = v[1][0];
        m[4] = v[1][1];
        m[5] = v[1][2];
        m[6] = v[2][0];
        m[7] = v[2][1];
        m[8] = v[2][2];
    }
    else
    {
        m[0] = v[0][0];
        m[1] = v[1][0];
        m[2] = v[2][0];
        m[3] = v[0][1];
        m[4] = v[1][1];
        m[5] = v[2][1];
        m[6] = v[0][2];
        m[7] = v[1][2];
        m[8] = v[2][2];
    }
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (t_Ty m00, t_Ty m11, t_Ty m22)
{
    makeDiagonal(m00, m11, m22);
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (const vector3<t_Ty>& axis, t_Ty angle)
{
    makeRotation(axis, angle);
}


template<class t_Ty>
inline matrix3x3<t_Ty>::matrix3x3 (const vector3<t_Ty>& u, const vector3<t_Ty>& v)
{
    makeTensorProduct(u, v);
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::operator= (const matrix3x3<t_Ty>& mat)
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
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::makeZero ()
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
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::makeIdentity ()
{
    m[0] = (t_Ty)1;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
    m[4] = (t_Ty)1;
    m[5] = (t_Ty)0;
    m[6] = (t_Ty)0;
    m[7] = (t_Ty)0;
    m[8] = (t_Ty)1;
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::makeDiagonal (t_Ty m00, t_Ty m11, t_Ty m22)
{
    m[0] = m00;
    m[1] = (t_Ty)0;
    m[2] = (t_Ty)0;
    m[3] = (t_Ty)0;
    m[4] = m11;
    m[5] = (t_Ty)0;
    m[6] = (t_Ty)0;
    m[7] = (t_Ty)0;
    m[8] = m22;
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::makeRotation (const vector3<t_Ty>& axis,
    t_Ty angle)
{
    t_Ty cs = cosf(angle);
    t_Ty sn = sinf(angle);
    t_Ty oneMinusCos = ((t_Ty)1) - cs;
    t_Ty x2 = axis[0]*axis[0];
    t_Ty y2 = axis[1]*axis[1];
    t_Ty z2 = axis[2]*axis[2];
    t_Ty xym = axis[0]*axis[1]*oneMinusCos;
    t_Ty xzm = axis[0]*axis[2]*oneMinusCos;
    t_Ty yzm = axis[1]*axis[2]*oneMinusCos;
    t_Ty xSin = axis[0]*sn;
    t_Ty ySin = axis[1]*sn;
    t_Ty zSin = axis[2]*sn;

    m[0] = x2*oneMinusCos + cs;
    m[3] = xym - zSin;
    m[6] = xzm + ySin;
    m[1] = xym + zSin;
    m[4] = y2*oneMinusCos + cs;
    m[7] = yzm - xSin;
    m[2] = xzm - ySin;
    m[5] = yzm + xSin;
    m[8] = z2*oneMinusCos + cs;
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::makeTensorProduct (const vector3<t_Ty>& u,
    const vector3<t_Ty>& v)
{
    m[0] = u[0]*v[0];
    m[3] = u[0]*v[1];
    m[6] = u[0]*v[2];
    m[1] = u[1]*v[0];
    m[4] = u[1]*v[1];
    m[7] = u[1]*v[2];
    m[2] = u[2]*v[0];
    m[5] = u[2]*v[1];
    m[8] = u[2]*v[2];
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator+ (const matrix3x3<t_Ty>& mat) const
{
    return matrix3x3<t_Ty>
    (
        m[0] + mat.m[0],
        m[1] + mat.m[1],
        m[2] + mat.m[2],
        m[3] + mat.m[3],
        m[4] + mat.m[4],
        m[5] + mat.m[5],
        m[6] + mat.m[6],
        m[7] + mat.m[7],
        m[8] + mat.m[8]
    );
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator- (const matrix3x3<t_Ty>& mat) const
{
    return matrix3x3<t_Ty>
    (
        m[0] - mat.m[0],
        m[1] - mat.m[1],
        m[2] - mat.m[2],
        m[3] - mat.m[3],
        m[4] - mat.m[4],
        m[5] - mat.m[5],
        m[6] - mat.m[6],
        m[7] - mat.m[7],
        m[8] - mat.m[8]
    );
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator* (t_Ty scalar) const
{
    return matrix3x3<t_Ty>
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3],
        scalar*m[4],
        scalar*m[5],
        scalar*m[6],
        scalar*m[7],
        scalar*m[8]
    );
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator/ (t_Ty scalar) const
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        return matrix3x3<t_Ty>
        (
            invScalar*m[0],
            invScalar*m[1],
            invScalar*m[2],
            invScalar*m[3],
            invScalar*m[4],
            invScalar*m[5],
            invScalar*m[6],
            invScalar*m[7],
            invScalar*m[8]
        );
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        return matrix3x3<t_Ty>
        (
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
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator- () const
{
    return matrix3x3<t_Ty>
    (
        -m[0],
        -m[1],
        -m[2],
        -m[3],
        -m[4],
        -m[5],
        -m[6],
        -m[7],
        -m[8]
    );
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::operator+= (const matrix3x3<t_Ty>& mat)
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
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::operator-= (const matrix3x3<t_Ty>& mat)
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
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::operator*= (t_Ty scalar)
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
    return *this;
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::operator/= (t_Ty scalar)
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
    }

    return *this;
}


template<class t_Ty>
inline vector3<t_Ty> matrix3x3<t_Ty>::operator* (const vector3<t_Ty>& vec) const
{
    return vector3<t_Ty>
    (
        m[0]*vec[0] + m[3]*vec[1] + m[6]*vec[2],
        m[1]*vec[0] + m[4]*vec[1] + m[7]*vec[2],
        m[2]*vec[0] + m[5]*vec[1] + m[8]*vec[2]
    );
}


template<class t_Ty>
inline t_Ty matrix3x3<t_Ty>::qForm (const vector3<t_Ty>& u, const vector3<t_Ty>& v)
    const
{
    return u.dot((*this)*v);
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::transpose () const
{
    return matrix3x3
    (
        m[0],
        m[3],
        m[6],
        m[1],
        m[4],
        m[7],
        m[2],
        m[5],
        m[8]
    );
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::operator* (const matrix3x3<t_Ty>& mat) const
{
    // A*B
    return matrix3x3
    (
        m[0]*mat.m[0] +
        m[3]*mat.m[1] +
        m[6]*mat.m[2],

        m[1]*mat.m[0] +
        m[4]*mat.m[1] +
        m[7]*mat.m[2],

        m[2]*mat.m[0] +
        m[5]*mat.m[1] +
        m[8]*mat.m[2],

        m[0]*mat.m[3] +
        m[3]*mat.m[4] +
        m[6]*mat.m[5],

        m[1]*mat.m[3] +
        m[4]*mat.m[4] +
        m[7]*mat.m[5],

        m[2]*mat.m[3] +
        m[6]*mat.m[4] +
        m[8]*mat.m[5],

        m[0]*mat.m[6] +
        m[3]*mat.m[7] +
        m[6]*mat.m[8],

        m[1]*mat.m[6] +
        m[4]*mat.m[7] +
        m[7]*mat.m[8],

        m[2]*mat.m[6] +
        m[6]*mat.m[7] +
        m[8]*mat.m[8]
    );
}

template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::inverse (t_Ty epsilon) const
{
    // Invert a 3x3 using cofactors.  This is faster than using a generic
    // Gaussian elimination because of the loop overhead of such a method.

    matrix3x3 inverse;

    // Compute the adjoint.
    inverse.m[0] = m[4]*m[8] - m[5]*m[7];
    inverse.m[3] = m[6]*m[5] - m[3]*m[8];
    inverse.m[6] = m[3]*m[7] - m[6]*m[4];
    inverse.m[1] = m[7]*m[2] - m[1]*m[8];
    inverse.m[4] = m[0]*m[8] - m[6]*m[2];
    inverse.m[7] = m[6]*m[1] - m[0]*m[7];
    inverse.m[2] = m[1]*m[5] - m[4]*m[2];
    inverse.m[5] = m[3]*m[2] - m[0]*m[5];
    inverse.m[8] = m[0]*m[4] - m[3]*m[1];

    t_Ty det = m[0]*inverse.m[0] + m[1]*inverse.m[3] +
        m[2]*inverse.m[6];

    if (fabs(det) > epsilon)
    {
        t_Ty invDet = ((t_Ty)1)/det;
        inverse.m[0] *= invDet;
        inverse.m[1] *= invDet;
        inverse.m[2] *= invDet;
        inverse.m[3] *= invDet;
        inverse.m[4] *= invDet;
        inverse.m[5] *= invDet;
        inverse.m[6] *= invDet;
        inverse.m[7] *= invDet;
        inverse.m[8] *= invDet;
        return inverse;
    }

    return ZERO;
}


template<class t_Ty>
inline matrix3x3<t_Ty> matrix3x3<t_Ty>::adjoint () const
{
    return matrix3x3
    (
        m[4]*m[8] - m[5]*m[7],
        m[6]*m[5] - m[3]*m[8],
        m[3]*m[7] - m[6]*m[4],
        m[7]*m[2] - m[1]*m[8],
        m[0]*m[8] - m[6]*m[2],
        m[6]*m[1] - m[0]*m[7],
        m[1]*m[5] - m[4]*m[2],
        m[1]*m[2] - m[0]*m[5],
        m[0]*m[4] - m[1]*m[1]
    );
}


template<class t_Ty>
inline t_Ty matrix3x3<t_Ty>::determinant () const
{
    t_Ty co00 = m[4]*m[8] - m[5]*m[7];
    t_Ty co10 = m[7]*m[2] - m[1]*m[8];
    t_Ty co20 = m[1]*m[5] - m[4]*m[2];
    t_Ty det = m[0]*co00 + m[3]*co10 + m[6]*co20;
    return det;
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::extractAxisAngle (vector3<t_Ty>& axis, t_Ty& angle) const
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    t_Ty trace = m[0] + m[4] + m[8];
    t_Ty cs = ((t_Ty)0.5)*(trace - (t_Ty)1);
    angle = acosf(cs);  // in [0,o_math_Pi]

    if (angle > (t_Ty)0)
    {
        if (angle < o_math_Pi)
        {
            axis[0] = m[5] - m[7];
            axis[1] = m[6] - m[2];
            axis[2] = m[1] - m[3];
            axis.normalize();
        }
        else
        {
            // angle is o_math_Pi
            t_Ty halfInverse;
            if (m[0] >= m[4])
            {
                // r00 >= r11
                if (m[0] >= m[8])
                {
                    // r00 is maximum diagonal term
                    axis[0] = ((t_Ty)0.5)*sqrt((t_Ty)1
                        + m[0] - m[4] - m[8]);
                    halfInverse = ((t_Ty)0.5)/axis[0];
                    axis[1] = halfInverse*m[3];
                    axis[2] = halfInverse*m[6];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = ((t_Ty)0.5)*sqrt((t_Ty)1
                        + m[8] - m[0] - m[4]);
                    halfInverse = ((t_Ty)0.5)/axis[2];
                    axis[0] = halfInverse*m[6];
                    axis[1] = halfInverse*m[7];
                }
            }
            else
            {
                // r11 > r00
                if (m[4] >= m[8])
                {
                    // r11 is maximum diagonal term
                    axis[1] = ((t_Ty)0.5)*sqrt((t_Ty)1
                        + m[4] - m[0] - m[8]);
                    halfInverse  = ((t_Ty)0.5)/axis[1];
                    axis[0] = halfInverse*m[3];
                    axis[2] = halfInverse*m[7];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = ((t_Ty)0.5)*sqrt((t_Ty)1
                        + m[8] - m[0] - m[4]);
                    halfInverse = ((t_Ty)0.5)/axis[2];
                    axis[0] = halfInverse*m[6];
                    axis[1] = halfInverse*m[7];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        axis[0] = (t_Ty)1;
        axis[1] = (t_Ty)0;
        axis[2] = (t_Ty)0;
    }
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // Compute q0.
    t_Ty invLength = invSqrt(m[0]*m[0] +
        m[1]*m[1] + m[2]*m[2]);

    m[0] *= invLength;
    m[1] *= invLength;
    m[2] *= invLength;

    // Compute q1.
    t_Ty dot0 = m[0]*m[3] + m[1]*m[4] +
        m[2]*m[5];

    m[3] -= dot0*m[0];
    m[4] -= dot0*m[1];
    m[5] -= dot0*m[2];

    invLength = invSqrt(m[3]*m[3] +
        m[4]*m[4] + m[5]*m[5]);

    m[3] *= invLength;
    m[4] *= invLength;
    m[5] *= invLength;

    // compute q2
    t_Ty dot1 = m[3]*m[6] + m[4]*m[7] +
        m[5]*m[8];

    dot0 = m[0]*m[6] + m[1]*m[7] +
        m[2]*m[8];

    m[6] -= dot0*m[0] + dot1*m[3];
    m[7] -= dot0*m[1] + dot1*m[4];
    m[8] -= dot0*m[2] + dot1*m[5];

    invLength = invSqrt(m[6]*m[6] +
        m[7]*m[7] + m[8]*m[8]);

    m[6] *= invLength;
    m[7] *= invLength;
    m[8] *= invLength;
}

/*
template<class t_Ty>
inline void matrix3x3<t_Ty>::eigenDecomposition (matrix3x3<t_Ty>& rot, matrix3x3<t_Ty>& diag) const
{
    // factor M = R*D*R^t_Ty.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    t_Ty diagonal[3], subdiagonal[2];
    rot = *this;
    bool reflection = rot.tridiagonalize(diagonal, subdiagonal);
    bool converged = rot.qlAlgorithm(diagonal, subdiagonal);
    o_assert(converged, "qlAlgorithm failed to converge\n");
    //BOOST_UNUSED(converged);

    // Sort the eigenvalues in increasing order, d0 <= d1 <= d2.  This is an
    // insertion sort.
    int i;
    t_Ty save;

    if (diagonal[1] < diagonal[0])
    {
        // Swap d0 and d1.
        save = diagonal[0];
        diagonal[0] = diagonal[1];
        diagonal[1] = save;

        // Swap V0 and V1.
        for (i = 0; i < 3; ++i)
        {
            save = rot[0][i];
            rot[0][i] = rot[1][i];
            rot[1][i] = save;
        }
        reflection = !reflection;
    }

    if (diagonal[2] < diagonal[1])
    {
        // Swap d1 and d2.
        save = diagonal[1];
        diagonal[1] = diagonal[2];
        diagonal[2] = save;

        // Swap V1 and V2.
        for (i = 0; i < 3; ++i)
        {
            save = rot[1][i];
            rot[1][i] = rot[2][i];
            rot[2][i] = save;
        }
        reflection = !reflection;
    }

    if (diagonal[1] < diagonal[0])
    {
        // Swap d0 and d1.
        save = diagonal[0];
        diagonal[0] = diagonal[1];
        diagonal[1] = save;

        // Swap V0 and V1.
        for (i = 0; i < 3; ++i)
        {
            save = rot[0][i];
            rot[0][i] = rot[1][i];
            rot[1][i] = save;
        }
        reflection = !reflection;
    }

    diag.makeDiagonal(diagonal[0], diagonal[1], diagonal[2]);

    if (reflection)
    {
        // The orthogonal transformation that diagonalizes M is a reflection.
        // Make the eigenvectors a right-handed system by changing sign on
        // the last column.
        rot[2][0] = -rot[2][0];
        rot[2][1] = -rot[2][1];
        rot[2][2] = -rot[2][2];
    }
}*/


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerXYZ (t_Ty xAngle, t_Ty yAngle, t_Ty zAngle)
{
    t_Ty cs, sn;

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    *this = xMat*(yMat*zMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerXZY (t_Ty xAngle, t_Ty zAngle, t_Ty yAngle)
{
    t_Ty cs, sn;

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    *this = xMat*(zMat*yMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerYXZ (t_Ty yAngle, t_Ty xAngle, t_Ty zAngle)
{
    t_Ty cs, sn;

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    *this = yMat*(xMat*zMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerYZX (t_Ty yAngle, t_Ty zAngle, t_Ty xAngle)
{
    t_Ty cs, sn;

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1,(t_Ty)0,(t_Ty)0,
        (t_Ty)0,cs,sn,
        (t_Ty)0,-sn,cs);

    *this = yMat*(zMat*xMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerZXY (t_Ty zAngle, t_Ty xAngle, t_Ty yAngle)
{
    t_Ty cs, sn;

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    *this = zMat*(xMat*yMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerZYX (t_Ty zAngle, t_Ty yAngle, t_Ty xAngle)
{
    t_Ty cs, sn;

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    *this = zMat*(yMat*xMat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerXYX (t_Ty x0Angle, t_Ty yAngle, t_Ty x1Angle)
{
    t_Ty cs, sn;

    cs = cosf(x0Angle);
    sn = sinf(x0Angle);
    matrix3x3 x0Mat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(x1Angle);
    sn = sinf(x1Angle);
    matrix3x3 x1Mat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    *this = x0Mat*(yMat*x1Mat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerXZX (t_Ty x0Angle, t_Ty zAngle, t_Ty x1Angle)
{
    t_Ty cs, sn;

    cs = cosf(x0Angle);
    sn = sinf(x0Angle);
    matrix3x3 x0Mat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(x1Angle);
    sn = sinf(x1Angle);
    matrix3x3 x1Mat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    *this = x0Mat*(zMat*x1Mat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerYXY (t_Ty y0Angle, t_Ty xAngle, t_Ty y1Angle)
{
    t_Ty cs, sn;

    cs = cosf(y0Angle);
    sn = sinf(y0Angle);
    matrix3x3 y0Mat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(y1Angle);
    sn = sinf(y1Angle);
    matrix3x3 y1Mat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    *this = y0Mat*(xMat*y1Mat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerYZY (t_Ty y0Angle, t_Ty zAngle, t_Ty y1Angle)
{
    t_Ty cs, sn;

    cs = cosf(y0Angle);
    sn = sinf(y0Angle);
    matrix3x3 y0Mat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(zAngle);
    sn = sinf(zAngle);
    matrix3x3 zMat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(y1Angle);
    sn = sinf(y1Angle);
    matrix3x3 y1Mat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    *this = y0Mat*(zMat*y1Mat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerZXZ (t_Ty z0Angle, t_Ty xAngle, t_Ty z1Angle)
{
    t_Ty cs, sn;

    cs = cosf(z0Angle);
    sn = sinf(z0Angle);
    matrix3x3 z0Mat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(xAngle);
    sn = sinf(xAngle);
    matrix3x3 xMat(
        (t_Ty)1, (t_Ty)0, (t_Ty)0,
        (t_Ty)0, cs,      sn,
        (t_Ty)0, -sn,      cs);

    cs = cosf(z1Angle);
    sn = sinf(z1Angle);
    matrix3x3 z1Mat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    *this = z0Mat*(xMat*z1Mat);
}


template<class t_Ty>
inline void matrix3x3<t_Ty>::makeEulerZYZ (t_Ty z0Angle, t_Ty yAngle, t_Ty z1Angle)
{
    t_Ty cs, sn;

    cs = cosf(z0Angle);
    sn = sinf(z0Angle);
    matrix3x3 z0Mat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    cs = cosf(yAngle);
    sn = sinf(yAngle);
    matrix3x3 yMat(
        cs,      (t_Ty)0, -sn,
        (t_Ty)0, (t_Ty)1, (t_Ty)0,
        sn,     (t_Ty)0, cs);

    cs = cosf(z1Angle);
    sn = sinf(z1Angle);
    matrix3x3 z1Mat(
        cs,      sn,     (t_Ty)0,
        -sn,      cs,      (t_Ty)0,
        (t_Ty)0, (t_Ty)0, (t_Ty)1);

    *this = z0Mat*(yMat*z1Mat);
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerXYZ (
    t_Ty& xAngle, t_Ty& yAngle, t_Ty& zAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz           -cy*sz            sy    |
    // | r10 r11 r12 | = |  cz*sx*sy+cx*sz   cx*cz-sx*sy*sz  -cy*sx |
    // | r20 r21 r22 |   | -cx*cz*sy+sx*sz   cz*sx+cx*sy*sz   cx*cy |
    // +-           -+   +-                                        -+

    if (m[6] < (t_Ty)1)
    {
        if (m[6] > -(t_Ty)1)
        {
            // yAngle = asin(r02)
            // xAngle = atan2(-r12,r22)
            // zAngle = atan2(-r01,r00)
            yAngle = (t_Ty)asin((double)m[6]);
            xAngle = atan2f(-m[7], m[8]);
            zAngle = atan2f(-m[3], m[0]);
            return EA_UNIQUE;
        }
        else
        {
            // yAngle = -pi/2
            // zAngle - xAngle = atan2(r10,r11)
            // WARNING.  The solution is not unique.  Choosing zAngle = 0.
            yAngle = -o_math_Pi_by_2;
            xAngle = -atan2f(m[1], m[4]);
            zAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // yAngle = +pi/2
        // zAngle + xAngle = atan2(r10,r11)
        // WARNING.  The solutions is not unique.  Choosing zAngle = 0.
        yAngle = o_math_Pi_by_2;
        xAngle = atan2f(m[1], m[4]);
        zAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerXZY (
    t_Ty& xAngle, t_Ty& zAngle, t_Ty& yAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz           -sz      cz*sy          |
    // | r10 r11 r12 | = |  sx*sy+cx*cy*sz   cx*cz  -cy*sx+cx*sy*sz |
    // | r20 r21 r22 |   | -cx*sy+cy*sx*sz   cz*sx   cx*cy+sx*sy*sz |
    // +-           -+   +-                                        -+

    if (m[3] < (t_Ty)1)
    {
        if (m[3] > -(t_Ty)1)
        {
            // zAngle = asin(-r01)
            // xAngle = atan2(r21,r11)
            // yAngle = atan2(r02,r00)
            zAngle = (t_Ty)asin(-(double)m[3]);
            xAngle = atan2f(m[5], m[4]);
            yAngle = atan2f(m[6], m[0]);
            return EA_UNIQUE;
        }
        else
        {
            // zAngle = +pi/2
            // yAngle - xAngle = atan2(-r20,r22)
            // WARNING.  The solution is not unique.  Choosing yAngle = 0.
            zAngle = o_math_Pi_by_2;
            xAngle = -atan2f(-m[2] ,m[8]);
            yAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // zAngle = -pi/2
        // yAngle + xAngle = atan2(-r20,r22)
        // WARNING.  The solution is not unique.  Choosing yAngle = 0.
        zAngle = -o_math_Pi_by_2;
        xAngle = atan2f(-m[2], m[8]);
        yAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerYXZ (
    t_Ty& yAngle, t_Ty& xAngle, t_Ty& zAngle) const
{
    // +-           -+   +-                                       -+
    // | r00 r01 r02 |   |  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz   cx*sy |
    // | r10 r11 r12 | = |  cx*sz           cx*cz           -sx    |
    // | r20 r21 r22 |   | -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz   cx*cy |
    // +-           -+   +-                                       -+

    if (m[7] < (t_Ty)1)
    {
        if (m[7] > -(t_Ty)1)
        {
            // xAngle = asin(-r12)
            // yAngle = atan2(r02,r22)
            // zAngle = atan2(r10,r11)
            xAngle = (t_Ty)asin(-(double)m[7]);
            yAngle = atan2f(m[6], m[8]);
            zAngle = atan2f(m[1], m[4]);
            return EA_UNIQUE;
        }
        else
        {
            // xAngle = +pi/2
            // zAngle - yAngle = atan2(-r01,r00)
            // WARNING.  The solution is not unique.  Choosing zAngle = 0.
            xAngle = o_math_Pi_by_2;
            yAngle = -atan2f(-m[3], m[0]);
            zAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // xAngle = -pi/2
        // zAngle + yAngle = atan2(-r01,r00)
        // WARNING.  The solution is not unique.  Choosing zAngle = 0.
        xAngle = -o_math_Pi_by_2;
        yAngle = atan2f(-m[3], m[0]);
        zAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerYZX (
    t_Ty& yAngle, t_Ty& zAngle, t_Ty& xAngle) const
{
    // +-           -+   +-                                       -+
    // | r00 r01 r02 |   |  cy*cz  sx*sy-cx*cy*sz   cx*sy+cy*sx*sz |
    // | r10 r11 r12 | = |  sz     cx*cz           -cz*sx          |
    // | r20 r21 r22 |   | -cz*sy  cy*sx+cx*sy*sz   cx*cy-sx*sy*sz |
    // +-           -+   +-                                       -+

    if (m[1] < (t_Ty)1)
    {
        if (m[1] > -(t_Ty)1)
        {
            // zAngle = asin(r10)
            // yAngle = atan2(-r20,r00)
            // xAngle = atan2(-r12,r11)
            zAngle = (t_Ty)asin((double)m[1]);
            yAngle = atan2f(-m[2], m[0]);
            xAngle = atan2f(-m[7], m[4]);
            return EA_UNIQUE;
        }
        else
        {
            // zAngle = -pi/2
            // xAngle - yAngle = atan2(r21,r22)
            // WARNING.  The solution is not unique.  Choosing xAngle = 0.
            zAngle = -o_math_Pi_by_2;
            yAngle = -atan2f(m[5], m[8]);
            xAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // zAngle = +pi/2
        // xAngle + yAngle = atan2(r21,r22)
        // WARNING.  The solution is not unique.  Choosing xAngle = 0.
        zAngle = o_math_Pi_by_2;
        yAngle = atan2f(m[5], m[8]);
        xAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerZXY (
    t_Ty& zAngle, t_Ty& xAngle, t_Ty& yAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz-sx*sy*sz  -cx*sz   cz*sy+cy*sx*sz |
    // | r10 r11 r12 | = |  cz*sx*sy+cy*sz   cx*cz  -cy*cz*sx+sy*sz |
    // | r20 r21 r22 |   | -cx*sy            sx      cx*cy          |
    // +-           -+   +-                                        -+

    if (m[5] < (t_Ty)1)
    {
        if (m[5] > -(t_Ty)1)
        {
            // xAngle = asin(r21)
            // zAngle = atan2(-r01,r11)
            // yAngle = atan2(-r20,r22)
            xAngle = (t_Ty)asin((double)m[5]);
            zAngle = atan2f(-m[3], m[4]);
            yAngle = atan2f(-m[2], m[8]);
            return EA_UNIQUE;
        }
        else
        {
            // xAngle = -pi/2
            // yAngle - zAngle = atan2(r02,r00)
            // WARNING.  The solution is not unique.  Choosing yAngle = 0.
            xAngle = -o_math_Pi_by_2;
            zAngle = -atan2f(m[6], m[0]);
            yAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // xAngle = +pi/2
        // yAngle + zAngle = atan2(r02,r00)
        // WARNING.  The solution is not unique.  Choosing yAngle = 0.
        xAngle = o_math_Pi_by_2;
        zAngle = atan2f(m[6], m[0]);
        yAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerZYX (
    t_Ty& zAngle, t_Ty& yAngle, t_Ty& xAngle) const
{
    // +-           -+   +-                                      -+
    // | r00 r01 r02 |   |  cy*cz  cz*sx*sy-cx*sz  cx*cz*sy+sx*sz |
    // | r10 r11 r12 | = |  cy*sz  cx*cz+sx*sy*sz -cz*sx+cx*sy*sz |
    // | r20 r21 r22 |   | -sy     cy*sx           cx*cy          |
    // +-           -+   +-                                      -+

    if (m[2] < (t_Ty)1)
    {
        if (m[2] > -(t_Ty)1)
        {
            // yAngle = asin(-r20)
            // zAngle = atan2(r10,r00)
            // xAngle = atan2(r21,r22)
            yAngle = (t_Ty)asin(-(double)m[2]);
            zAngle = atan2f(m[1], m[0]);
            xAngle = atan2f(m[5], m[8]);
            return EA_UNIQUE;
        }
        else
        {
            // yAngle = +pi/2
            // xAngle - zAngle = atan2(r01,r02)
            // WARNING.  The solution is not unique.  Choosing xAngle = 0.
            yAngle = o_math_Pi_by_2;
            zAngle = -atan2f(m[3], m[6]);
            xAngle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // yAngle = -pi/2
        // xAngle + zAngle = atan2(-r01,-r02)
        // WARNING.  The solution is not unique.  Choosing xAngle = 0;
        yAngle = -o_math_Pi_by_2;
        zAngle = atan2f(-m[3], -m[6]);
        xAngle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerXYX (
    t_Ty& x0Angle, t_Ty& yAngle, t_Ty& x1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy      sy*sx1               sy*cx1             |
    // | r10 r11 r12 | = |  sy*sx0  cx0*cx1-cy*sx0*sx1  -cy*cx1*sx0-cx0*sx1 |
    // | r20 r21 r22 |   | -sy*cx0  cx1*sx0+cy*cx0*sx1   cy*cx0*cx1-sx0*sx1 |
    // +-           -+   +-                                                -+

    if (m[0] < (t_Ty)1)
    {
        if (m[0] > -(t_Ty)1)
        {
            // yAngle  = acos(r00)
            // x0Angle = atan2(r10,-r20)
            // x1Angle = atan2(r01,r02)
            yAngle = (t_Ty)acos((double)m[0]);
            x0Angle = atan2f(m[1], -m[2]);
            x1Angle = atan2f(m[3], m[6]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  x1Angle - x0Angle = atan2(-r12,r11)
            yAngle = o_math_Pi;
            x0Angle = -atan2f(-m[7], m[4]);
            x1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  x1Angle + x0Angle = atan2(-r12,r11)
        yAngle = (t_Ty)0;
        x0Angle = atan2f(-m[7], m[4]);
        x1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerXZX (
    t_Ty& x0Angle, t_Ty& zAngle, t_Ty& x1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   | cz      -sz*cx1               sz*sx1             |
    // | r10 r11 r12 | = | sz*cx0   cz*cx0*cx1-sx0*sx1  -cx1*sx0-cz*cx0*sx1 |
    // | r20 r21 r22 |   | sz*sx0   cz*cx1*sx0+cx0*sx1   cx0*cx1-cz*sx0*sx1 |
    // +-           -+   +-                                                -+

    if (m[0] < (t_Ty)1)
    {
        if (m[0] > -(t_Ty)1)
        {
            // zAngle  = acos(r00)
            // x0Angle = atan2(r20,r10)
            // x1Angle = atan2(r02,-r01)
            zAngle = (t_Ty)acos((double)m[0]);
            x0Angle = atan2f(m[2], m[1]);
            x1Angle = atan2f(m[6], -m[3]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  x1Angle - x0Angle = atan2(r21,r22)
            zAngle = o_math_Pi;
            x0Angle = -atan2f(m[5], m[8]);
            x1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  x1Angle + x0Angle = atan2(r21,r22)
        zAngle = (t_Ty)0;
        x0Angle = atan2f(m[5], m[8]);
        x1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerYXY (
    t_Ty& y0Angle, t_Ty& xAngle, t_Ty& y1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy0*cy1-cx*sy0*sy1  sx*sy0   cx*cy1*sy0+cy0*sy1 |
    // | r10 r11 r12 | = |  sx*sy1              cx      -sx*cy1             |
    // | r20 r21 r22 |   | -cy1*sy0-cx*cy0*sy1  sx*cy0   cx*cy0*cy1-sy0*sy1 |
    // +-           -+   +-                                                -+

    if (m[4] < (t_Ty)1)
    {
        if (m[4] > -(t_Ty)1)
        {
            // xAngle  = acos(r11)
            // y0Angle = atan2(r01,r21)
            // y1Angle = atan2(r10,-r12)
            xAngle = (t_Ty)acos((double)m[4]);
            y0Angle = atan2f(m[3], m[5]);
            y1Angle = atan2f(m[1], -m[7]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  y1Angle - y0Angle = atan2(r02,r00)
            xAngle = o_math_Pi;
            y0Angle = -atan2f(m[6], m[0]);
            y1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  y1Angle + y0Angle = atan2(r02,r00)
        xAngle = (t_Ty)0;
        y0Angle = atan2f(m[6], m[0]);
        y1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerYZY (
    t_Ty& y0Angle, t_Ty& zAngle, t_Ty& y1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cz*cy0*cy1-sy0*sy1  -sz*cy0  cy1*sy0+cz*cy0*sy1 |
    // | r10 r11 r12 | = |  sz*cy1               cz      sz*sy1             |
    // | r20 r21 r22 |   | -cz*cy1*sy0-cy0*sy1   sz*sy0  cy0*cy1-cz*sy0*sy1 |
    // +-           -+   +-                                                -+

    if (m[4] < (t_Ty)1)
    {
        if (m[4] > -(t_Ty)1)
        {
            // zAngle  = acos(r11)
            // y0Angle = atan2(r21,-r01)
            // y1Angle = atan2(r12,r10)
            zAngle = (t_Ty)acos((double)m[4]);
            y0Angle = atan2f(m[5], -m[3]);
            y1Angle = atan2f(m[7], m[1]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  y1Angle - y0Angle = atan2(-r20,r22)
            zAngle = o_math_Pi;
            y0Angle = -atan2f(-m[2], m[8]);
            y1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  y1Angle + y0Angle = atan2(-r20,r22)
        zAngle = (t_Ty)0;
        y0Angle = atan2f(-m[2], m[8]);
        y1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerZXZ (
    t_Ty& z0Angle, t_Ty& xAngle, t_Ty& z1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   | cz0*cz1-cx*sz0*sz1  -cx*cz1*sz0-cz0*sz1   sx*sz0 |
    // | r10 r11 r12 | = | cz1*sz0+cx*cz0*sz1   cx*cz0*cz1-sz0*sz1  -sz*cz0 |
    // | r20 r21 r22 |   | sx*sz1               sx*cz1               cx     |
    // +-           -+   +-                                                -+

    if (m[8] < (t_Ty)1)
    {
        if (m[8] > -(t_Ty)1)
        {
            // xAngle  = acos(r22)
            // z0Angle = atan2(r02,-r12)
            // z1Angle = atan2(r20,r21)
            xAngle = (t_Ty)acos((double)m[8]);
            z0Angle = atan2f(m[6], -m[7]);
            z1Angle = atan2f(m[2], m[5]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  z1Angle - z0Angle = atan2(-r01,r00)
            xAngle = o_math_Pi;
            z0Angle = -atan2f(-m[3], m[0]);
            z1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  z1Angle + z0Angle = atan2(-r01,r00)
        xAngle = (t_Ty)0;
        z0Angle = atan2f(-m[3], m[0]);
        z1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline typename matrix3x3<t_Ty>::EulerResult matrix3x3<t_Ty>::extractEulerZYZ (
    t_Ty& z0Angle, t_Ty& yAngle, t_Ty& z1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy*cz0*cz1-sz0*sz1  -cz1*sz0-cy*cz0*sz1  sy*cz0 |
    // | r10 r11 r12 | = |  cy*cz1*sz0+cz0*sz1   cz0*cz1-cy*sz0*sz1  sy*sz0 |
    // | r20 r21 r22 |   | -sy*cz1               sy*sz1              cy     |
    // +-           -+   +-                                                -+

    if (m[8] < (t_Ty)1)
    {
        if (m[8] > -(t_Ty)1)
        {
            // yAngle  = acos(r22)
            // z0Angle = atan2(r12,r02)
            // z1Angle = atan2(r21,-r20)
            yAngle = (t_Ty)acos((double)m[8]);
            z0Angle = atan2f(m[7], m[6]);
            z1Angle = atan2f(m[5], -m[2]);
            return EA_UNIQUE;
        }
        else // r22 = -1
        {
            // Not a unique solution:  z1Angle - z0Angle = atan2(r10,r11)
            yAngle = o_math_Pi;
            z0Angle = -atan2f(m[1], m[4]);
            z1Angle = (t_Ty)0;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else // r22 = +1
    {
        // Not a unique solution:  z1Angle + z0Angle = atan2(r10,r11)
        yAngle = (t_Ty)0;
        z0Angle = atan2f(m[1], m[4]);
        z1Angle = (t_Ty)0;
        return EA_NOT_UNIQUE_SUM;
    }
}


template<class t_Ty>
inline matrix3x3<t_Ty>& matrix3x3<t_Ty>::slerp (t_Ty t, const matrix3x3<t_Ty>& rot0,
    const matrix3x3<t_Ty>& rot1)
{
    vector3<t_Ty> axis;
    t_Ty angle;
    matrix3x3 prod = rot0.transposeTimes(rot1);
    prod.extractAxisAngle(axis, angle);
    makeRotation(axis, t*angle);
    *this = rot0*(*this);
    return *this;
}

/*
template<class t_Ty>
inline void matrix3x3<t_Ty>::singularValueDecomposition (matrix3x3<t_Ty>& left,
    matrix3x3<t_Ty>& diag, matrix3x3<t_Ty>& rightTranspose) const
{
    // TODO.  Replace by a call to eigenDecomposition and a QR factorization
    // that is specialized for 3x3.  The qduDecomposition appears to assume
    // the input matrix is invertible, but a general QR factorization has to
    // deal with non-full rank.

    Gmatrix M(3, 3);
    memcpy((t_Ty*)M, m, 9*sizeof(double));

    Gmatrix tmpL(3, 3), tmpD(3, 3), tmpRTranspose(3, 3);
    Wm5::singularValueDecomposition(M, tmpL, tmpD, tmpRTranspose);

    memcpy(left.m, (t_Ty*)tmpL, 9*sizeof(t_Ty));
    memcpy(diag.m,(t_Ty*)tmpD, 9*sizeof(t_Ty));
    memcpy(rightTranspose.m, (t_Ty*)tmpRTranspose, 9*sizeof(t_Ty));
}*/


/*template<class t_Ty>
inline void matrix3x3<t_Ty>::polarDecomposition (matrix3x3<t_Ty>& qMat, matrix3x3<t_Ty>& sMat)
{
    // Decompose M = L*D*R^t_Ty.
    matrix3x3 left, diag, rightTranspose;
    singularValueDecomposition(left, diag, rightTranspose);

    // Compute Q = L*R^t_Ty.
    qMat = left*rightTranspose;

    // Compute S = R*D*R^t_Ty.
    sMat = rightTranspose.transposeTimes(diag*rightTranspose);

    // Numerical round-off errors can cause S not to be symmetric in the
    // sense that S[i][j] and S[j][i] are slightly different for i != j.
    // Correct this by averaging S = (S + S^t_Ty)/2.
    sMat[0][1] = ((t_Ty)0.5)*(sMat[0][1] + sMat[1][0]);
    sMat[1][0] = sMat[0][1];
    sMat[0][2] = ((t_Ty)0.5)*(sMat[0][2] + sMat[2][0]);
    sMat[2][0] = sMat[0][2];
    sMat[1][2] = ((t_Ty)0.5)*(sMat[1][2] + sMat[2][1]);
    sMat[2][1] = sMat[1][2];
}*/

/*
template<class t_Ty>
inline void matrix3x3<t_Ty>::qduDecomposition (matrix3x3<t_Ty>& qMat, matrix3x3<t_Ty>& diag,
    matrix3x3<t_Ty>& uMat) const
{
    // factor M = QR = QDU where Q is orthogonal (rotation), D is diagonal
    // (scaling),  and U is upper triangular with ones on its diagonal
    // (shear).  Algorithm uses Gram-Schmidt orthogonalization (the QR
    // algorithm).
    //
    // If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.  The matrix R has entries
    //
    //   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
    //   r10 = 0      r11 = q1*m1  r12 = q1*m2
    //   r20 = 0      r21 = 0      r22 = q2*m2
    //
    // so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
    // u02 = r02/r00, and u12 = r12/r11.

    // Build orthogonal matrix Q.
    t_Ty invLength = invSqrt(m[0]*m[0] +
        m[3]*m[3] + m[6]*m[6]);
    qMat[0][0] = m[0]*invLength;
    qMat[1][0] = m[3]*invLength;
    qMat[2][0] = m[6]*invLength;

    t_Ty fDot = qMat[0][0]*m[1] + qMat[1][0]*m[4] +
        qMat[2][0]*m[7];
    qMat[0][1] = m[1]-fDot*qMat[0][0];
    qMat[1][1] = m[4]-fDot*qMat[1][0];
    qMat[2][1] = m[7]-fDot*qMat[2][0];
    invLength = invSqrt(qMat[0][1]*qMat[0][1] +
        qMat[1][1]*qMat[1][1] + qMat[2][1]*qMat[2][1]);
    qMat[0][1] *= invLength;
    qMat[1][1] *= invLength;
    qMat[2][1] *= invLength;

    fDot = qMat[0][0]*m[2] + qMat[1][0]*m[5] +
        qMat[2][0]*m[8];
    qMat[0][2] = m[2]-fDot*qMat[0][0];
    qMat[1][2] = m[5]-fDot*qMat[1][0];
    qMat[2][2] = m[8]-fDot*qMat[2][0];
    fDot = qMat[0][1]*m[2] + qMat[1][1]*m[5] +
        qMat[2][1]*m[8];
    qMat[0][2] -= fDot*qMat[0][1];
    qMat[1][2] -= fDot*qMat[1][1];
    qMat[2][2] -= fDot*qMat[2][1];
    invLength = invSqrt(qMat[0][2]*qMat[0][2] +
        qMat[1][2]*qMat[1][2] + qMat[2][2]*qMat[2][2]);
    qMat[0][2] *= invLength;
    qMat[1][2] *= invLength;
    qMat[2][2] *= invLength;

    // Guarantee that orthogonal matrix has determinant 1 (no reflections).
    t_Ty det =
        qMat[0][0]*qMat[1][1]*qMat[2][2] + qMat[0][1]*qMat[1][2]*qMat[2][0] +
        qMat[0][2]*qMat[1][0]*qMat[2][1] - qMat[0][2]*qMat[1][1]*qMat[2][0] -
        qMat[0][1]*qMat[1][0]*qMat[2][2] - qMat[0][0]*qMat[1][2]*qMat[2][1];

    if (det < (t_Ty)0)
    {
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                qMat[row][col] = -qMat[row][col];
            }
        }
    }

    // Build "right" matrix R.
    matrix3x3 right;
    right[0][0] = qMat[0][0]*m[0] + qMat[1][0]*m[3] +
        qMat[2][0]*m[6];
    right[0][1] = qMat[0][0]*m[1] + qMat[1][0]*m[4] +
        qMat[2][0]*m[7];
    right[1][1] = qMat[0][1]*m[1] + qMat[1][1]*m[4] +
        qMat[2][1]*m[7];
    right[0][2] = qMat[0][0]*m[2] + qMat[1][0]*m[5] +
        qMat[2][0]*m[8];
    right[1][2] = qMat[0][1]*m[2] + qMat[1][1]*m[5] +
        qMat[2][1]*m[8];
    right[2][2] = qMat[0][2]*m[2] + qMat[1][2]*m[5] +
        qMat[2][2]*m[8];

    // The scaling component.
    diag.makeDiagonal(right[0][0], right[1][1], right[2][2]);

    // the shear component
    t_Ty invD00 = ((t_Ty)1)/diag[0][0];
    uMat[0][0] = (t_Ty)1;
    uMat[0][1] = right[0][1]*invD00;
    uMat[0][2] = right[0][2]*invD00;
    uMat[1][0] = (t_Ty)0;
    uMat[1][1] = (t_Ty)1;
    uMat[1][2] = right[1][2]/diag[1][1];
    uMat[2][0] = (t_Ty)0;
    uMat[2][1] = (t_Ty)0;
    uMat[2][2] = (t_Ty)1;
}*/

/*
template<class t_Ty>
inline bool matrix3x3<t_Ty>::tridiagonalize (t_Ty diagonal[3], t_Ty subdiagonal[2])
{
    // Householder reduction t_Ty = Q^t M Q
    //   Input:
    //     mat, symmetric 3x3 matrix M
    //   Output:
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of t_Ty
    //     subd, subdiagonal entries of t_Ty (t_Ty is symmetric)

    t_Ty m00 = m[0];
    t_Ty m01 = m[1];
    t_Ty m02 = m[2];
    t_Ty m11 = m[4];
    t_Ty m12 = m[5];
    t_Ty m22 = m[8];

    diagonal[0] = m00;
    if (fabs(m02) >= ZERO_TOLERANCE)
    {
        subdiagonal[0] = sqrt(m01*m01 + m02*m02);
        t_Ty invLength = ((t_Ty)1)/subdiagonal[0];
        m01 *= invLength;
        m02 *= invLength;
        t_Ty tmp = ((t_Ty)2)*m01*m12 + m02*(m22 - m11);
        diagonal[1] = m11 + m02*tmp;
        diagonal[2] = m22 - m02*tmp;
        subdiagonal[1] = m12 - m01*tmp;

        m[0] = (t_Ty)1;
        m[1] = (t_Ty)0;
        m[2] = (t_Ty)0;
        m[3] = (t_Ty)0;
        m[4] = m01;
        m[5] = m02;
        m[6] = (t_Ty)0;
        m[7] = m02;
        m[8] = -m01;
        return true;
    }
    else
    {
        diagonal[1] = m11;
        diagonal[2] = m22;
        subdiagonal[0] = m01;
        subdiagonal[1] = m12;

        m[0] = (t_Ty)1;
        m[1] = (t_Ty)0;
        m[2] = (t_Ty)0;
        m[3] = (t_Ty)0;
        m[4] = (t_Ty)1;
        m[5] = (t_Ty)0;
        m[6] = (t_Ty)0;
        m[7] = (t_Ty)0;
        m[8] = (t_Ty)1;
        return false;
    }
}*/

/*
template<class t_Ty>
inline bool matrix3x3<t_Ty>::qlAlgorithm (t_Ty diagonal[3], t_Ty subdiagonal[2])
{
    // This is an implementation of the symmetric QR algorithm from the book
    // "matrix Computations" by Gene H. Golub and Charles F. Van Loan,
    // second edition.  The algorithm is 8.2.3.  The implementation has a
    // slight variation to actually make it a QL algorithm, and it traps the
    // case when either of the subdiagonal terms s0 or s1 is zero and reduces
    // the 2-by-2 subblock directly.

    const int imax = 32;
    for (int i = 0; i < imax; ++i)
    {
        t_Ty sum, diff, discr, eigVal0, eigVal1, cs, sn, tmp;
        int row;

        sum = fabs(diagonal[0]) + fabs(diagonal[1]);
        if (fabs(subdiagonal[0]) + sum == sum)
        {
            // The matrix is effectively
            //       +-        -+
            //   M = | d0  0  0 |
            //       | 0  d1 s1 |
            //       | 0  s1 d2 |
            //       +-        -+

            // Test whether M is diagonal (within numerical round-off).
            sum = fabs(diagonal[1]) +
                fabs(diagonal[2]);
            if (fabs(subdiagonal[1]) + sum == sum)
            {
                return true;
            }

            // Compute the eigenvalues as roots of a quadratic equation.
            sum = diagonal[1] + diagonal[2];
            diff = diagonal[1] - diagonal[2];
            discr = sqrt(diff*diff +
                ((t_Ty)4)*subdiagonal[1]*subdiagonal[1]);
            eigVal0 = ((t_Ty)0.5)*(sum - discr);
            eigVal1 = ((t_Ty)0.5)*(sum + discr);

            // Compute the Givens rotation.
            if (diff >= (t_Ty)0)
            {
                cs = subdiagonal[1];
                sn = diagonal[1] - eigVal0;
            }
            else
            {
                cs = diagonal[2] - eigVal0;
                sn = subdiagonal[1];
            }
            tmp = invSqrt(cs*cs + sn*sn);
            cs *= tmp;
            sn *= tmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (row = 0; row < 3; ++row)
            {
                tmp = m[2+3*row];
                m[2+3*row] = sn*m[1+3*row] + cs*tmp;
                m[1+3*row] = cs*m[1+3*row] - sn*tmp;
            }

            // Update the tridiagonal matrix.
            diagonal[1] = eigVal0;
            diagonal[2] = eigVal1;
            subdiagonal[0] = (t_Ty)0;
            subdiagonal[1] = (t_Ty)0;
            return true;
        }

        sum = fabs(diagonal[1]) + fabs(diagonal[2]);
        if (fabs(subdiagonal[1]) + sum == sum)
        {
            // The matrix is effectively
            //       +-         -+
            //   M = | d0  s0  0 |
            //       | s0  d1  0 |
            //       | 0   0  d2 |
            //       +-         -+

            // Test whether M is diagonal (within numerical round-off).
            sum = fabs(diagonal[0]) +
                fabs(diagonal[1]);
            if (fabs(subdiagonal[0]) + sum == sum)
            {
                return true;
            }

            // Compute the eigenvalues as roots of a quadratic equation.
            sum = diagonal[0] + diagonal[1];
            diff = diagonal[0] - diagonal[1];
            discr = sqrt(diff*diff +
                ((t_Ty)4.0)*subdiagonal[0]*subdiagonal[0]);
            eigVal0 = ((t_Ty)0.5)*(sum - discr);
            eigVal1 = ((t_Ty)0.5)*(sum + discr);

            // Compute the Givens rotation.
            if (diff >= (t_Ty)0)
            {
                cs = subdiagonal[0];
                sn = diagonal[0] - eigVal0;
            }
            else
            {
                cs = diagonal[1] - eigVal0;
                sn = subdiagonal[0];
            }
            tmp = invSqrt(cs*cs + sn*sn);
            cs *= tmp;
            sn *= tmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (row = 0; row < 3; ++row)
            {
                tmp = m[1+3*row];
                m[1+3*row] = sn*m[0+3*row] + cs*tmp;
                m[0+3*row] = cs*m[0+3*row] - sn*tmp;
            }

            // Update the tridiagonal matrix.
            diagonal[0] = eigVal0;
            diagonal[1] = eigVal1;
            subdiagonal[0] = (t_Ty)0;
            subdiagonal[1] = (t_Ty)0;
            return true;
        }

        // The matrix is
        //       +-        -+
        //   M = | d0 s0  0 |
        //       | s0 d1 s1 |
        //       | 0  s1 d2 |
        //       +-        -+

        // Set up the parameters for the first pass of the QL step.  The
        // value for A is the difference between diagonal term D[2] and the
        // implicit shift suggested by Wilkinson.
        t_Ty ratio = (diagonal[1] - diagonal[0])/(((t_Ty)2)*subdiagonal[0]);
        t_Ty root = sqrt((t_Ty)1 + ratio*ratio);
        t_Ty b = subdiagonal[1];
        t_Ty a = diagonal[2] - diagonal[0];
        if (ratio >= (t_Ty)0)
        {
            a += subdiagonal[0]/(ratio + root);
        }
        else
        {
            a += subdiagonal[0]/(ratio - root);
        }

        // Compute the Givens rotation for the first pass.
        if (fabs(b) >= fabs(a))
        {
            ratio = a/b;
            sn = invSqrt((t_Ty)1 + ratio*ratio);
            cs = ratio*sn;
        }
        else
        {
            ratio = b/a;
            cs = invSqrt((t_Ty)1 + ratio*ratio);
            sn = ratio*cs;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (row = 0; row < 3; ++row)
        {
            tmp = m[2+3*row];
            m[2+3*row] = sn*m[1+3*row] + cs*tmp;
            m[1+3*row] = cs*m[1+3*row] - sn*tmp;
        }

        // Set up the parameters for the second pass of the QL step.  The
        // values tmp0 and tmp1 are required to fully update the tridiagonal
        // matrix at the end of the second pass.
        t_Ty tmp0 = (diagonal[1] - diagonal[2])*sn +
            ((t_Ty)2)*subdiagonal[1]*cs;
        t_Ty tmp1 = cs*subdiagonal[0];
        b = sn*subdiagonal[0];
        a = cs*tmp0 - subdiagonal[1];
        tmp0 *= sn;

        // Compute the Givens rotation for the second pass.  The subdiagonal
        // term S[1] in the tridiagonal matrix is updated at this time.
        if (fabs(b) >= fabs(a))
        {
            ratio = a/b;
            root = sqrt((t_Ty)1 + ratio*ratio);
            subdiagonal[1] = b*root;
            sn = ((t_Ty)1)/root;
            cs = ratio*sn;
        }
        else
        {
            ratio = b/a;
            root = sqrt((t_Ty)1 + ratio*ratio);
            subdiagonal[1] = a*root;
            cs = ((t_Ty)1)/root;
            sn = ratio*cs;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (row = 0; row < 3; ++row)
        {
            tmp = m[1+3*row];
            m[1+3*row] = sn*m[0+3*row] + cs*tmp;
            m[0+3*row] = cs*m[0+3*row] - sn*tmp;
        }

        // Complete the update of the tridiagonal matrix.
        t_Ty tmp2 = diagonal[1] - tmp0;
        diagonal[2] += tmp0;
        tmp0 = (diagonal[0] - tmp2)*sn + ((t_Ty)2)*tmp1*cs;
        subdiagonal[0] = cs*tmp0 - tmp1;
        tmp0 *= sn;
        diagonal[1] = tmp2 + tmp0;
        diagonal[0] -= tmp0;
    }
    return false;
}*/


template<class t_Ty>
inline matrix3x3<t_Ty> operator* (t_Ty scalar, const matrix3x3<t_Ty>& mat)
{
    return mat*scalar;
}


template<class t_Ty>
inline vector3<t_Ty> operator* (const vector3<t_Ty>& vec,
    const matrix3x3<t_Ty>& mat)
{
    return vector3<t_Ty>
    (
        vec[0]*mat[0][0] + vec[1]*mat[0][1] + vec[2]*mat[0][2],
        vec[0]*mat[1][0] + vec[1]*mat[1][1] + vec[2]*mat[1][2],
        vec[0]*mat[2][0] + vec[1]*mat[2][1] + vec[2]*mat[2][2]
    );
}

