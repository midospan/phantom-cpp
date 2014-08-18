

template<class t_Ty>
inline vector2<t_Ty>::vector2 ()
{
	// Uninitialized for performance in array construction.
}


template<class t_Ty>
inline vector2<t_Ty>::vector2 (const vector2<t_Ty>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
}

template<class t_Ty>
inline vector2<t_Ty>::vector2 (t_Ty x, t_Ty y)
{
	m[0] = x;
	m[1] = y;
}

template<class t_Ty>
inline vector2<t_Ty>::vector2 (t_Ty s)
{
    m[0] = s;
    m[1] = s;
}

template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator= (const vector2<t_Ty>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    return *this;
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator+ (const vector2<t_Ty>& vec) const
{
    return vector2<t_Ty>
    (
        m[0] + vec.m[0],
        m[1] + vec.m[1]
    );
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator- (const vector2<t_Ty>& vec) const
{
    return vector2<t_Ty>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1]
    );
}



template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator* (t_Ty scalar) const
{
    return vector2<t_Ty>
    (
        scalar*m[0],
        scalar*m[1]
    );
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator*( const vector2<t_Ty>& vec ) const 
{
    vector2<t_Ty> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    
    return result;
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator/ (t_Ty scalar) const
{
    vector2<t_Ty> result;

    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        result.m[0] = invScalar*m[0];
        result.m[1] = invScalar*m[1];
    }
    else
    {
        result.m[0] = std::numeric_limits<t_Ty>::max();
        result.m[1] = std::numeric_limits<t_Ty>::max();
    }

    return result;
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator/ ( const vector2<t_Ty>& vec ) const
{
    vector2<t_Ty> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];

    return result;
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator- () const
{
    return vector2<t_Ty>
    (
        -m[0],
        -m[1]
    );
}

template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator+( t_Ty scalar ) const
{
    return self_type(x+scalar, y+scalar);
}

template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::operator-( t_Ty scalar ) const
{
    return self_type(x-scalar, y-scalar);
}

template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator+= (const vector2<t_Ty>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    return *this;
}


template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator-= (const vector2<t_Ty>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    return *this;
}


template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    return *this;
}


template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator*= (const vector2<t_Ty>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    return *this;
}

template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator/= (const vector2<t_Ty>& vec)
{
    m[0] /= vec.x;
    m[1] /= vec.y;
    return *this;
}


template<class t_Ty>
inline vector2<t_Ty>& vector2<t_Ty>::operator/= (t_Ty scalar)
{
    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        m[0] *= invScalar;
        m[1] *= invScalar;
    }
    else
    {
        m[0] *= std::numeric_limits<t_Ty>::max();
        m[1] *= std::numeric_limits<t_Ty>::max();
    }

    return *this;
}


template<class t_Ty>
inline t_Ty vector2<t_Ty>::length () const
{
    return sqrt
    (
        m[0]*m[0] +
        m[1]*m[1]
    );
}


template<class t_Ty>
inline t_Ty vector2<t_Ty>::lengthSquared () const
{
    return
        m[0]*m[0] +
        m[1]*m[1];
}


template<class t_Ty>
inline t_Ty vector2<t_Ty>::dot (const vector2<t_Ty>& vec) const
{
    return
        m[0]*vec.m[0] +
        m[1]*vec.m[1];
}


template<class t_Ty>
inline t_Ty vector2<t_Ty>::normalize ()
{
    t_Ty len = length();

    if (len > epsilon<t_Ty>())
    {
        t_Ty invLength = 1.f/len;
        m[0] *= invLength;
        m[1] *= invLength;
    }
    else
    {
        len = (t_Ty)0;
        m[0] = (t_Ty)0;
        m[1] = (t_Ty)0;
    }

    return len;
}

template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::normalized () const
{
    vector2<t_Ty> result = *this;
    t_Ty len = length();

    if (len > epsilon<t_Ty>())
    {
        t_Ty invLength = ((t_Ty)1)/len;
        result.x *= invLength;
        result.y *= invLength;
    }
    else
    {
        result.x = (t_Ty)0;
        result.y = (t_Ty)0;
    }

    return result;
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::orthogonalCW() const
{
    return vector2<t_Ty>
    (
        m[1],
        -m[0]
    );
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::orthogonalCCW() const
{
    return vector2<t_Ty>
        (
        -m[1],
        m[0]
    );
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::normalizedOrthogonalCW () const
{
    vector2<t_Ty> perp(m[1], -m[0]);
    return perp.normalized();
}


template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::normalizedOrthogonalCCW () const
{
    vector2<t_Ty> perp(-m[1], m[0]);
    return perp.normalized();
}


template<class t_Ty>
inline t_Ty vector2<t_Ty>::cross (const vector2<t_Ty>& vec) const
{
    return m[0]*vec.m[1] - m[1]*vec.m[0];
}


template<class t_Ty>
inline void vector2<t_Ty>::computeExtremes (int numVectors, const vector2<t_Ty>* vectors,
    vector2<t_Ty>& vmin, vector2<t_Ty>& vmax)
{
    o_assert(numVectors > 0 && vectors,
        "Invalid inputs to computeExtremes\n");

    vmin = vectors[0];
    vmax = vmin;
    for (int j = 1; j < numVectors; ++j)
    {
        const vector2<t_Ty>& vec = vectors[j];
        for (int i = 0; i < 2; ++i)
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
inline void vector2<t_Ty>::orthonormalize (vector2<t_Ty>& u, vector2<t_Ty>& v)
{
    // If the input vectors are v0 and v1, then the Gram-Schmidt
    // orthonormalization produces vectors u0 and u1 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // Compute u0.
    u.normalize();

    // Compute u1.
    t_Ty dot0 = u.dot(v); 
    v -= u*dot0;
    v.normalize();
}


template<class t_Ty>
inline void vector2<t_Ty>::generateOrthonormalBasis (vector2<t_Ty>& u, vector2<t_Ty>& v)
{
    v.normalize();
    u = v.orthogonalCW();
}


template<class t_Ty>
inline bool vector2<t_Ty>::barycentrics (const vector2<t_Ty>& v0, const vector2<t_Ty>& v1,
    const vector2<t_Ty>& v2, t_Ty bary[3], t_Ty epsilon) const
{
    // Compute the vectors relative to V2 of the triangle.
    vector2<t_Ty> diff[3] = { v0 - v2, v1 - v2, *this - v2 };

    t_Ty det = diff[0].cross(diff[1]);
    if (fabs(det) > epsilon)
    {
        t_Ty invDet = ((t_Ty)1)/det;
        bary[0] = diff[2].cross(diff[1])*invDet;
        bary[1] = diff[0].cross(diff[2])*invDet;
        bary[2] = (t_Ty)1 - bary[0] - bary[1];
        return true;
    }

    for (int i = 0; i < 3; ++i)
    {
        bary[i] = (t_Ty)0;
    }

#ifdef WM5_ASSERT_ON_BARYCENTRIC2_DEGENERATE
    o_assert(false, "Input triangle is degenerate.\n");
#endif
    return false;
}


template<class t_Ty>
inline bool vector2<t_Ty>::isBetweenPoints(const vector2<t_Ty>& start, const vector2<t_Ty>& end
										, t_Ty epsilon) const
{
	math::vector2<t_Ty> n = end - start;
	math::vector2<t_Ty> v = *this - start;
	t_Ty det = n.x*v.y - n.y*v.x;
	if (fabs(det) > (t_Ty)epsilon)
	{
		// Not collinear
		return false;
	}
	// Parameter
	t_Ty t = (n.dot(*this - start))/n.lengthSquared();
	
	return t > (t_Ty)epsilon && t < (t_Ty)(1 - epsilon);
}


template<class t_Ty>
inline vector2<t_Ty> operator* (t_Ty scalar, const vector2<t_Ty>& vec)
{
    return vector2<t_Ty>
    (
        scalar*vec[0],
        scalar*vec[1]
    );
}

template<class t_Ty>
inline t_Ty vector2<t_Ty>::lengthApproximated() const
{
    return phantom::math::approximatedSqrt(lengthSquared());
}

template<class t_Ty>
inline vector2<t_Ty> vector2<t_Ty>::normalizedApproximated() const
{
    t_Ty len = lengthApproximated();
    if(len == 0) 
    {
        return self_type(0,0);
    }
    t_Ty invLen = t_Ty(1.)/len;
    return self_type(x * invLen, y*invLen);
}

template<class t_Ty>
inline t_Ty vector2<t_Ty>::normalizeApproximated()
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

template<class t_Ty>
inline std::ostream& operator<< (std::ostream& outFile, const vector2<t_Ty>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ')';
}

