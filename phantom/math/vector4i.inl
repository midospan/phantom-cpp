
inline vector4<int>::vector4 ()
{
	// Uninitialized for performance in array construction.
}


inline vector4<int>::vector4 (const vector4<int>& vec)
{
	m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
}


inline vector4<int>::vector4 (int x, int y, int z, int w)
{
	m[0] = x;
    m[1] = y;
    m[2] = z;
    m[2] = z;
}

inline vector4<int>& vector4<int>::operator= (const vector4<int>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
    return *this;
}


inline vector4<int> vector4<int>::operator+ (const vector4<int>& vec) const
{
    return vector4<int>
    (
    m[0] + vec.m[0],
    m[1] + vec.m[1],
    m[2] + vec.m[2],
    m[3] + vec.m[3]
    );
}


inline vector4<int> vector4<int>::operator- (const vector4<int>& vec) const
{
    return vector4<int>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1],
        m[2] - vec.m[2],
        m[3] - vec.m[3]
    );
}



inline vector4<int> vector4<int>::operator* (int scalar) const
{
    return vector4<int>
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2],
        scalar*m[3]
    );
}


inline vector4<int> vector4<int>::operator*( const vector4<int>& vec ) const 
{
    vector4<int> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    result.m[2] = m[2]*vec.m[2];
    result.m[3] = m[3]*vec.m[3];
    
    return result;
}


inline vector4<int> vector4<int>::operator/ (int integer) const
{
    vector4<int> result;

    if (integer != (int)0)
    {
        result.m[0] = m[0]/integer;
        result.m[1] = m[1]/integer;
        result.m[2] = m[2]/integer;
        result.m[3] = m[3]/integer;
    }
    else
    {
        result.m[0] = INT_MAX;
        result.m[1] = INT_MAX;
        result.m[2] = INT_MAX;
        result.m[3] = INT_MAX;
    }

    return result;
}


inline vector4<int> vector4<int>::operator/ ( const vector4<int>& vec ) const
{
    vector4<int> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];
    result.m[2] = m[2]/vec.m[2];
    result.m[3] = m[3]/vec.m[3];

    return result;
}


inline vector4<int> vector4<int>::operator- () const
{
    return vector4<int>
    (
        -m[0],
        -m[1],
        -m[2],
        -m[3]
    );
}


inline vector4<int>& vector4<int>::operator+= (const vector4<int>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    m[2] += vec.m[2];
    m[3] += vec.m[3];
    return *this;
}


inline vector4<int>& vector4<int>::operator-= (const vector4<int>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    m[2] -= vec.m[2];
    m[3] -= vec.m[3];
    return *this;
}


inline vector4<int>& vector4<int>::operator*= (int scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    m[3] *= scalar;
    return *this;
}


inline vector4<int>& vector4<int>::operator*= (const vector4<int>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    m[2] *= vec.z;
    m[3] *= vec.w;
    return *this;
}


inline vector4<int>& vector4<int>::operator/= (int scalar)
{
    if (scalar != (int)0)
    {
        m[0] /= scalar;
        m[1] /= scalar;
        m[2] /= scalar;
        m[3] /= scalar;
    }
    else
    {
        m[0] *= INT_MAX;
        m[1] *= INT_MAX;
        m[2] *= INT_MAX;
        m[3] *= INT_MAX;
    }

    return *this;
}
inline vector4<int> operator* (int scalar, const vector4<int>& vec)
{
    return vector4<int>
    (
        scalar*vec[0],
        scalar*vec[1],
        scalar*vec[2],
        scalar*vec[3]
    );
}


inline std::ostream& operator<< (std::ostream& outFile, const vector4<int>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << ')';
}

