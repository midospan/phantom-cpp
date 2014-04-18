
inline vector2<unsigned int>::vector2 ()
{
	// Uninitialized for performance in array construction.
}



inline vector2<unsigned int>::vector2 (const vector2<unsigned int>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
}



inline vector2<unsigned int>::vector2 (unsigned int x, unsigned int y)
{
	m[0] = x;
	m[1] = y;
}


inline vector2<unsigned int>& vector2<unsigned int>::operator= (const vector2<unsigned int>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    return *this;
}



inline vector2<unsigned int> vector2<unsigned int>::operator+ (const vector2<unsigned int>& vec) const
{
    return vector2<unsigned int>
    (
        m[0] + vec.m[0],
        m[1] + vec.m[1]
    );
}



inline vector2<unsigned int> vector2<unsigned int>::operator- (const vector2<unsigned int>& vec) const
{
    return vector2<unsigned int>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1]
    );
}




inline vector2<unsigned int> vector2<unsigned int>::operator* (unsigned int scalar) const
{
    return vector2<unsigned int>
    (
        scalar*m[0],
        scalar*m[1]
    );
}



inline vector2<unsigned int> vector2<unsigned int>::operator*( const vector2<unsigned int>& vec ) const 
{
    vector2<unsigned int> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    
    return result;
}



inline vector2<unsigned int> vector2<unsigned int>::operator/ (unsigned int integer) const
{
    vector2<unsigned int> result;

    if (integer != (unsigned int)0)
    {
        result.m[0] = m[0]/integer;
        result.m[1] = m[1]/integer;
    }
    else
    {
        result.m[0] = UINT_MAX;
        result.m[1] = UINT_MAX;
    }

    return result;
}



inline vector2<unsigned int> vector2<unsigned int>::operator/ ( const vector2<unsigned int>& vec ) const
{
    vector2<unsigned int> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];

    return result;
}



inline vector2<unsigned int>& vector2<unsigned int>::operator+= (const vector2<unsigned int>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    return *this;
}



inline vector2<unsigned int>& vector2<unsigned int>::operator-= (const vector2<unsigned int>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    return *this;
}



inline vector2<unsigned int>& vector2<unsigned int>::operator*= (unsigned int scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    return *this;
}



inline vector2<unsigned int>& vector2<unsigned int>::operator*= (const vector2<unsigned int>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    return *this;
}



inline vector2<unsigned int>& vector2<unsigned int>::operator/= (unsigned int scalar)
{
    if (scalar != (unsigned int)0)
    {
        m[0] /= scalar;
        m[1] /= scalar;
    }
    else
    {
        m[0] *= UINT_MAX;
        m[1] *= UINT_MAX;
    }

    return *this;
}

inline vector2<unsigned int> operator* (unsigned int scalar, const vector2<unsigned int>& vec)
{
    return vector2<unsigned int>
    (
        scalar*vec[0],
        scalar*vec[1]
    );
}



inline std::ostream& operator<< (std::ostream& outFile, const vector2<unsigned int>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ')';
}

