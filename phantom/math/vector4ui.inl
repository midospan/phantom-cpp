
inline vector4<unsigned int>::vector4 ()
{
	// Uninitialized for performance in array construction.
}



inline vector4<unsigned int>::vector4 (const vector4<unsigned int>& vec)
{
	m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
}



inline vector4<unsigned int>::vector4 (unsigned int x, unsigned int y, unsigned int z)
{
    m[0] = x;
    m[1] = y;
    m[2] = z;
    m[2] = w;
}


inline vector4<unsigned int>& vector4<unsigned int>::operator= (const vector4<unsigned int>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    return *this;
}



inline vector4<unsigned int> vector4<unsigned int>::operator+ (const vector4<unsigned int>& vec) const
{
    return vector4<unsigned int>
    (
        m[0] + vec.m[0],
        m[1] + vec.m[1],
        m[2] + vec.m[2]
    );
}



inline vector4<unsigned int> vector4<unsigned int>::operator- (const vector4<unsigned int>& vec) const
{
    return vector4<unsigned int>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1],
        m[2] - vec.m[2]
    );
}




inline vector4<unsigned int> vector4<unsigned int>::operator* (unsigned int scalar) const
{
    return vector4<unsigned int>
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2]
    );
}



inline vector4<unsigned int> vector4<unsigned int>::operator*( const vector4<unsigned int>& vec ) const 
{
    vector4<unsigned int> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    result.m[2] = m[2]*vec.m[2];
    
    return result;
}



inline vector4<unsigned int> vector4<unsigned int>::operator/ (unsigned int integer) const
{
    vector4<unsigned int> result;

    if (integer != (unsigned int)0)
    {
        result.m[0] = m[0]/integer;
        result.m[1] = m[1]/integer;
        result.m[2] = m[2]/integer;
    }
    else
    {
        result.m[0] = UINT_MAX;
        result.m[1] = UINT_MAX;
        result.m[2] = UINT_MAX;
    }

    return result;
}



inline vector4<unsigned int> vector4<unsigned int>::operator/ ( const vector4<unsigned int>& vec ) const
{
    vector4<unsigned int> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];
    result.m[2] = m[2]/vec.m[2];

    return result;
}



inline vector4<unsigned int>& vector4<unsigned int>::operator+= (const vector4<unsigned int>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    m[2] += vec.m[2];
    return *this;
}



inline vector4<unsigned int>& vector4<unsigned int>::operator-= (const vector4<unsigned int>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    m[2] -= vec.m[2];
    return *this;
}



inline vector4<unsigned int>& vector4<unsigned int>::operator*= (unsigned int scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    return *this;
}



inline vector4<unsigned int>& vector4<unsigned int>::operator*= (const vector4<unsigned int>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    m[2] *= vec.z;
    return *this;
}



inline vector4<unsigned int>& vector4<unsigned int>::operator/= (unsigned int scalar)
{
    if (scalar != (unsigned int)0)
    {
        m[0] /= scalar;
        m[1] /= scalar;
        m[2] /= scalar;
    }
    else
    {
        m[0] *= UINT_MAX;
        m[1] *= UINT_MAX;
        m[2] *= UINT_MAX;
    }

    return *this;
}

inline vector4<unsigned int> operator* (unsigned int scalar, const vector4<unsigned int>& vec)
{
    return vector4<unsigned int>
    (
        scalar*vec[0],
        scalar*vec[1],
        scalar*vec[2]
    );
}



inline std::ostream& operator<< (std::ostream& outFile, const vector4<unsigned int>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
}

