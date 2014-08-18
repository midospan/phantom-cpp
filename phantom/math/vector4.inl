template<class t_Ty>
inline vector4<t_Ty>::vector4 ()
{
    // Uninitialized for performance in array construction.
}


template<class t_Ty>
inline vector4<t_Ty>::vector4 (const vector4<t_Ty>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
}

template<class t_Ty>
inline vector4<t_Ty>::vector4 (const vector3<t_Ty>& xyz, t_Ty w)
{
    m[0] = xyz.m[0];
    m[1] = xyz.m[1];
    m[2] = xyz.m[2];
    m[3] = w;
}

template<class t_Ty>
inline vector4<t_Ty>::vector4 (t_Ty x, t_Ty y, t_Ty z, t_Ty w)
{
    m[0] = x;
    m[1] = y;
    m[2] = z;
    m[3] = w;
}

template<class t_Ty>
inline vector4<t_Ty>::vector4 (t_Ty s)
{
    m[0] = s;
    m[1] = s;
    m[2] = s;
    m[3] = s;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator= (const vector4<t_Ty>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator= (t_Ty s)
{
    m[0] = s;
    m[1] = s;
    m[2] = s;
    m[3] = s;
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator+ (const vector4<t_Ty>& vec) const
{
    return vector4<t_Ty>
    (
        m[0] + vec.m[0],
        m[1] + vec.m[1],
        m[2] + vec.m[2],
        m[3] + vec.m[3]
    );
}


template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator- (const vector4<t_Ty>& vec) const
{
    return vector4<t_Ty>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1],
        m[2] - vec.m[2],
        m[3] - vec.m[3]
    );
}

template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator* (const vector4<t_Ty>& vec) const
{
    return vector4<t_Ty>
        (
        m[0] * vec.m[0],
        m[1] * vec.m[1],
        m[2] * vec.m[2],
        m[3] * vec.m[3]
    );
}

template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator/ (const vector4<t_Ty>& vec) const
{
    t_Ty max = std::numeric_limits<t_Ty>::max();
    return vector4<t_Ty>
        (
        select(vec.m[0] != 0, m[0] / vec.m[0], max),
        select(vec.m[1] != 0, m[1] / vec.m[1], max),
        select(vec.m[2] != 0, m[2] / vec.m[2], max),
        select(vec.m[3] != 0, m[3] / vec.m[3], max)
    );
}

template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator+ (t_Ty scalar) const
{
    return vector4<t_Ty>
        (
        scalar+m[0],
        scalar+m[1],
        scalar+m[2],
        scalar+m[3]
    );
}
template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator- (t_Ty scalar) const
{
    return vector4<t_Ty>
        (
        m[0]-scalar,
        m[1]-scalar,
        m[2]-scalar,
        m[3]-scalar
    );
}

template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator* (t_Ty scalar) const
{
    return vector4<t_Ty>
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3]
    );
}


template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator/ (t_Ty scalar) const
{
    vector4<t_Ty> result;
    t_Ty max = std::numeric_limits<t_Ty>::max();

    if (scalar != (t_Ty)0)
    {
        t_Ty invScalar = ((t_Ty)1)/scalar;
        result.m[0] = invScalar*m[0];
        result.m[1] = invScalar*m[1];
        result.m[2] = invScalar*m[2];
        result.m[3] = invScalar*m[3];
    }
    else
    {
        result.m[0] = max;
        result.m[1] = max;
        result.m[2] = max;
        result.m[3] = max;
    }

    return result;
}


template<class t_Ty>
inline vector4<t_Ty> vector4<t_Ty>::operator- () const
{
    return vector4<t_Ty>
    (
        -m[0],
        -m[1],
        -m[2],
        -m[3]
    );
}


template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator+= (const vector4<t_Ty>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    m[2] += vec.m[2];
    m[3] += vec.m[3];
    return *this;
}


template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator-= (const vector4<t_Ty>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    m[2] -= vec.m[2];
    m[3] -= vec.m[3];
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator*= (const vector4<t_Ty>& vec)
{
    m[0] *= vec.m[0];
    m[1] *= vec.m[1];
    m[2] *= vec.m[2];
    m[3] *= vec.m[3];
    return *this;
}


template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator/= (const vector4<t_Ty>& vec)
{
    m[0] /= vec.m[0];
    m[1] /= vec.m[1];
    m[2] /= vec.m[2];
    m[3] /= vec.m[3];
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator*= (t_Ty scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator/= (t_Ty scalar)
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
        m[0] *= std::numeric_limits<t_Ty>::max();
        m[1] *= std::numeric_limits<t_Ty>::max();
        m[2] *= std::numeric_limits<t_Ty>::max();
        m[3] *= std::numeric_limits<t_Ty>::max();
    }

    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator+= (t_Ty scalar)
{
    m[0] += scalar;
    m[1] += scalar;
    m[2] += scalar;
    m[3] += scalar;
    return *this;
}

template<class t_Ty>
inline vector4<t_Ty>& vector4<t_Ty>::operator-= (t_Ty scalar)
{
    m[0] -= scalar;
    m[1] -= scalar;
    m[2] -= scalar;
    m[3] -= scalar;
    return *this;
}


template<class t_Ty>
inline t_Ty vector4<t_Ty>::length () const
{
    return sqrtf
    (
        m[0]*m[0] +
        m[1]*m[1] +
        m[2]*m[2] +
        m[3]*m[3]
    );
}


template<class t_Ty>
inline t_Ty vector4<t_Ty>::lengthSquared () const
{
    return
        m[0]*m[0] +
        m[1]*m[1] +
        m[2]*m[2] +
        m[3]*m[3];
}


template<class t_Ty>
inline t_Ty vector4<t_Ty>::dot (const vector4<t_Ty>& vec) const
{
    return
        m[0]*vec.m[0] +
        m[1]*vec.m[1] +
        m[2]*vec.m[2] +
        m[3]*vec.m[3];
}


template<class t_Ty>
inline t_Ty vector4<t_Ty>::normalize ()
{
    t_Ty len = length();

    if (len > std::numeric_limits<T>::epsilon())
    {
        t_Ty invLength = ((t_Ty)1)/len;
        m[0] *= invLength;
        m[1] *= invLength;
        m[2] *= invLength;
        m[3] *= invLength;
    }
    else
    {
        len = (t_Ty)0;
        m[0] = (t_Ty)0;
        m[1] = (t_Ty)0;
        m[2] = (t_Ty)0;
        m[3] = (t_Ty)0;
    }

    return len;
}


template<class t_Ty>
inline void vector4<t_Ty>::computeExtremes (int numVectors, const vector4<t_Ty>* vectors,
    vector4<t_Ty>& vmin, vector4<t_Ty>& vmax)
{
    o_assert(numVectors > 0 && vectors,
        "Invalid inputs to computeExtremes\n");

    vmin = vectors[0];
    vmax = vmin;
    for (int j = 1; j < numVectors; ++j)
    {
        const vector4<t_Ty>& vec = vectors[j];
        for (int i = 0; i < 4; ++i)
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
inline vector4<t_Ty> operator* (t_Ty scalar, const vector4<t_Ty>& vec)
{
    return vector4<t_Ty>
    (
        scalar*vec[0],
        scalar*vec[1],
        scalar*vec[2],
        scalar*vec[3]
    );
}


template<class t_Ty>
inline std::ostream& operator<< (std::ostream& outFile, const vector4<t_Ty>& vec)
{
     return outFile << vec.x << ' ' << vec.y << ' ' << vec.z
         << ' ' << vec.w;
}

