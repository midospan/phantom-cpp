
template<class t_Ty>
inline vector3<t_Ty>::vector3 ()
{
    // Uninitialized for performance in array construction.
}

template<class t_Ty>
inline vector3<t_Ty>::vector3 (t_Ty s)
{
	m[0] = s;
	m[1] = s;
	m[2] = s;
}

template<class t_Ty>
inline vector3<t_Ty>::vector3 (const vector3<t_Ty>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
	m[2] = vec.m[2];
}

template<class t_Ty>
inline vector3<t_Ty>::vector3 (t_Ty x, t_Ty y, t_Ty z)
{
	m[0] = x;
	m[1] = y;
	m[2] = z;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator= (const vector3<t_Ty>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
	m[2] = vec.m[2];
	return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator= (t_Ty s)
{
    m[0] = s;
    m[1] = s;
    m[2] = s;
    return *this;
}


template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator+ (const vector3<t_Ty>& vec) const
{
	return vector3<t_Ty>
	(
		m[0] + vec.m[0],
		m[1] + vec.m[1],
		m[2] + vec.m[2]
		);
}


template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator- (const vector3<t_Ty>& vec) const
{
	return vector3<t_Ty>
	(
		m[0] - vec.m[0],
		m[1] - vec.m[1],
		m[2] - vec.m[2]
	);
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator* (const vector3<t_Ty>& vec) const
{
    return vector3<t_Ty>
        (
        m[0] * vec.m[0],
        m[1] * vec.m[1],
        m[2] * vec.m[2]
    );
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator/ (const vector3<t_Ty>& vec) const
{
    t_Ty max = std::numeric_limits<t_Ty>::max();
    return vector3<t_Ty>
        (
        select(vec.m[0] != (t_Ty)0, m[0] / vec.m[0], max),
        select(vec.m[1] != (t_Ty)0, m[1] / vec.m[1], max),
        select(vec.m[2] != (t_Ty)0, m[2] / vec.m[2], max)
        );
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator+ (t_Ty scalar) const
{
    return vector3<t_Ty>
        (
        m[0]-scalar,
        m[1]-scalar,
        m[2]-scalar
    );
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator- (t_Ty scalar) const
{
    return vector3<t_Ty>
        (
        m[0]-scalar,
        m[1]-scalar,
        m[2]-scalar
    );
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator* (t_Ty scalar) const
{
	return vector3<t_Ty>
	(
		scalar*m[0],
		scalar*m[1],
		scalar*m[2]
	);
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator/ (t_Ty scalar) const
{
    vector3<t_Ty> result;

    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        result.m[0] = invScalar*m[0];
        result.m[1] = invScalar*m[1];
        result.m[2] = invScalar*m[2];
    }
    else
    {
        t_Ty max = std::numeric_limits<t_Ty>::max();
        result.m[0] = max;
        result.m[1] = max;
        result.m[2] = max;
    }

    return result;
}


template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::operator- () const
{
    return vector3<t_Ty>
    (
        -m[0],
        -m[1],
        -m[2]
    );
}


template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator+= (const vector3<t_Ty>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    m[2] += vec.m[2];
    return *this;
}


template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator-= (const vector3<t_Ty>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    m[2] -= vec.m[2];
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator*= (const vector3<t_Ty>& vec)
{
    m[0] *= vec.m[0];
    m[1] *= vec.m[1];
    m[2] *= vec.m[2];
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator/= (const vector3<t_Ty>& vec)
{
    m[0] /= vec.m[0];
    m[1] /= vec.m[1];
    m[2] /= vec.m[2];
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator+= (t_Ty scalar)
{
    m[0] += scalar;
    m[1] += scalar;
    m[2] += scalar;
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator-= (t_Ty scalar)
{
    m[0] -= scalar;
    m[1] -= scalar;
    m[2] -= scalar;
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    return *this;
}

template<class t_Ty>
inline vector3<t_Ty>& vector3<t_Ty>::operator/= (t_Ty scalar)
{
    t_Ty max = std::numeric_limits<t_Ty>::max();
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        m[0] *= invScalar;
        m[1] *= invScalar;
        m[2] *= invScalar;
    }
    else
    {
        m[0] = max;
        m[1] = max;
        m[2] = max;
    }

    return *this;
}


template<class t_Ty>
inline t_Ty vector3<t_Ty>::length () const
{
    return sqrtf
    (
        m[0]*m[0] +
        m[1]*m[1] +
        m[2]*m[2]
    );
}


template<class t_Ty>
inline t_Ty vector3<t_Ty>::lengthSquared () const
{
    return
        m[0]*m[0] +
        m[1]*m[1] +
        m[2]*m[2];
}


template<class t_Ty>
inline t_Ty vector3<t_Ty>::dot (const vector3<t_Ty>& vec) const
{
    return
        m[0]*vec.m[0] +
        m[1]*vec.m[1] +
        m[2]*vec.m[2];
}


template<class t_Ty>
inline t_Ty vector3<t_Ty>::normalize ()
{
    t_Ty len = length();

    if (len > std::numeric_limits<t_Ty>::epsilon())
    {
        t_Ty invLength = ((t_Ty)1)/len;
        m[0] *= invLength;
        m[1] *= invLength;
        m[2] *= invLength;
    }
    else
    {
        len = (t_Ty)0;
        m[0] = (t_Ty)0;
        m[1] = (t_Ty)0;
        m[2] = (t_Ty)0;
    }

    return len;
}

template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::normalized () const
{
    t_Ty len = length();

    if (len > epsilon<t_Ty>())
    {
        vector3<t_Ty> result = *this;
        t_Ty invLength = ((t_Ty)1)/len;
        result.x *= invLength;
        result.y *= invLength;
        result.z *= invLength;
        return result;
    }

    return ZERO;
}


template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::cross (const vector3<t_Ty>& vec) const
{
    return vector3<t_Ty>
    (
        m[1]*vec.m[2] - m[2]*vec.m[1],
        m[2]*vec.m[0] - m[0]*vec.m[2],
        m[0]*vec.m[1] - m[1]*vec.m[0]
    );
}


template<class t_Ty>
inline vector3<t_Ty> vector3<t_Ty>::unitCross (const vector3<t_Ty>& vec) const
{
    vector3<t_Ty> cross
    (
        m[1]*vec.m[2] - m[2]*vec.m[1],
        m[2]*vec.m[0] - m[0]*vec.m[2],
        m[0]*vec.m[1] - m[1]*vec.m[0]
    );
    cross.normalize();
    return cross;
}


template<class t_Ty>
inline void vector3<t_Ty>::computeExtremes (int numVectors, const vector3<t_Ty>* vectors,
    vector3<t_Ty>& vmin, vector3<t_Ty>& vmax)
{
    o_assert(numVectors > 0 && vectors,
        "Invalid inputs to computeExtremes\n");

    vmin = vectors[0];
    vmax = vmin;
    for (int j = 1; j < numVectors; ++j)
    {
        const vector3<t_Ty>& vec = vectors[j];
        for (int i = 0; i < 3; ++i)
        {
            if (vec[i] < vmin[i])
            {
                vmin[i] = vec[i];
            }
            else if (vec[i] > vmax[i])
            {
                vmax[i] = vec[i];
            }
        }
    }
}


template<class t_Ty>
inline void vector3<t_Ty>::orthonormalize (vector3<t_Ty>& u, vector3<t_Ty>& v, vector3<t_Ty>& w)
{
    // If the input vectors are v0, v1, and v2, then the Gram-Schmidt
    // orthonormalization produces vectors u0, u1, and u2 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    u.normalize();

    // compute u1
    t_Ty dot0 = u.dot(v);
    v -= dot0*u;
    v.normalize();

    // compute u2
    t_Ty dot1 = v.dot(w);
    dot0 = u.dot(w);
    w -= dot0*u + dot1*v;
    w.normalize();
}


template<class t_Ty>
inline void vector3<t_Ty>::orthonormalize (vector3<t_Ty>* v)
{
    orthonormalize(v[0], v[1], v[2]);
}


template<class t_Ty>
inline void vector3<t_Ty>::generateOrthonormalBasis (vector3<t_Ty>& u, vector3<t_Ty>& v,
    vector3<t_Ty>& w)
{
    w.normalize();
    generateComplementBasis(u, v, w);
}


template<class t_Ty>
inline void vector3<t_Ty>::generateComplementBasis (vector3<t_Ty>& u, vector3<t_Ty>& v,
    const vector3<t_Ty>& w)
{
    t_Ty invLength;

    if (fabs(w.m[0]) >= fabs(w.m[1]))
    {
        // W.x or W.z is the largest magnitude component, swap them
        invLength = invSqrt(w.m[0]*w.m[0] +
            w.m[2]*w.m[2]);
        u.m[0] = -w.m[2]*invLength;
        u.m[1] = (t_Ty)0;
        u.m[2] = +w.m[0]*invLength;
        v.m[0] = w.m[1]*u.m[2];
        v.m[1] = w.m[2]*u.m[0] - w.m[0]*u.m[2];
        v.m[2] = -w.m[1]*u.m[0];
    }
    else
    {
        // W.y or W.z is the largest magnitude component, swap them
        invLength = invSqrt(w.m[1]*w.m[1] +
            w.m[2]*w.m[2]);
        u.m[0] = (t_Ty)0;
        u.m[1] = +w.m[2]*invLength;
        u.m[2] = -w.m[1]*invLength;
        v.m[0] = w.m[1]*u.m[2] - w.m[2]*u.m[1];
        v.m[1] = -w.m[0]*u.m[2];
        v.m[2] = w.m[0]*u.m[1];
    }
}


template<class t_Ty>
inline bool vector3<t_Ty>::barycentrics (const vector3<t_Ty>& v0, const vector3<t_Ty>& v1,
    const vector3<t_Ty>& v2, const vector3<t_Ty>& v3, t_Ty bary[4], t_Ty epsilon)
    const
{
    // Compute the vectors relative to V3 of the tetrahedron.
    vector3<t_Ty> diff[4] = { v0 - v3, v1 - v3, v2 - v3, *this - v3 };

    t_Ty det = diff[0].dot(diff[1].cross(diff[2]));
    vector3<t_Ty> e1ce2 = diff[1].cross(diff[2]);
    vector3<t_Ty> e2ce0 = diff[2].cross(diff[0]);
    vector3<t_Ty> e0ce1 = diff[0].cross(diff[1]);
    if (fabs(det) > epsilon)
    {
        t_Ty invDet = ((t_Ty)1)/det;
        bary[0] = diff[3].dot(e1ce2)*invDet;
        bary[1] = diff[3].dot(e2ce0)*invDet;
        bary[2] = diff[3].dot(e0ce1)*invDet;
        bary[3] = (t_Ty)1 - bary[0] - bary[1] - bary[2];
        return true;
    }

    for (int i = 0; i < 4; ++i)
    {
        bary[i] = (t_Ty)0;
    }

#ifdef MATH_ASSERT_ON_BARYCENTRIC3_DEGENERATE
    o_assert(false, "Input tetrahedron is degenerate.\n");
#endif
    return false;
}


template<class t_Ty>
inline bool vector3<t_Ty>::isCollinearTo(const vector3<t_Ty>& v) const
{
	return fabs(dot(v) - 1) <= std::numeric_limits<t_Ty>::epsilon();
}

template<class t_Ty>
inline vector3<t_Ty> operator* (t_Ty scalar, const vector3<t_Ty>& vec)
{
    return vector3<t_Ty>
    (
        scalar*vec[0],
        scalar*vec[1],
        scalar*vec[2]
    );
}


template<class t_Ty>
inline std::ostream& operator<< (std::ostream& outFile, const vector3<t_Ty>& vec)
{
     return outFile << vec.x << ' ' << vec.y << ' ' << vec.z;
}

