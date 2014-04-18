
inline vector2<int>::vector2 ()
{
	// Uninitialized for performance in array construction.
}


inline vector2<int>::vector2 (const vector2<int>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
}


inline vector2<int>::vector2 (int x, int y)
{
	m[0] = x;
	m[1] = y;
}

inline vector2<int>& vector2<int>::operator= (const vector2<int>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    return *this;
}


inline vector2<int> vector2<int>::operator+ (const vector2<int>& vec) const
{
    return vector2<int>
    (
        m[0] + vec.m[0],
        m[1] + vec.m[1]
    );
}


inline vector2<int> vector2<int>::operator- (const vector2<int>& vec) const
{
    return vector2<int>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1]
    );
}



inline vector2<int> vector2<int>::operator* (int scalar) const
{
    return vector2<int>
    (
        scalar*m[0],
        scalar*m[1]
    );
}


inline vector2<int> vector2<int>::operator*( const vector2<int>& vec ) const 
{
    vector2<int> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    
    return result;
}


inline vector2<int> vector2<int>::operator/ (int integer) const
{
    vector2<int> result;

    if (integer != (int)0)
    {
        result.m[0] = m[0]/integer;
        result.m[1] = m[1]/integer;
    }
    else
    {
        result.m[0] = INT_MAX;
        result.m[1] = INT_MAX;
    }

    return result;
}


inline vector2<int> vector2<int>::operator/ ( const vector2<int>& vec ) const
{
    vector2<int> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];

    return result;
}


inline vector2<int> vector2<int>::operator- () const
{
    return vector2<int>
    (
        -m[0],
        -m[1]
    );
}


inline vector2<int>& vector2<int>::operator+= (const vector2<int>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    return *this;
}


inline vector2<int>& vector2<int>::operator-= (const vector2<int>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    return *this;
}


inline vector2<int>& vector2<int>::operator*= (int scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    return *this;
}


inline vector2<int>& vector2<int>::operator*= (const vector2<int>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    return *this;
}


inline vector2<int>& vector2<int>::operator/= (int scalar)
{
    if (scalar != (int)0)
    {
        m[0] /= scalar;
        m[1] /= scalar;
    }
    else
    {
        m[0] *= INT_MAX;
        m[1] *= INT_MAX;
    }

    return *this;
}
inline vector2<int> operator* (int scalar, const vector2<int>& vec)
{
    return vector2<int>
    (
        scalar*vec[0],
        scalar*vec[1]
    );
}


inline std::ostream& operator<< (std::ostream& outFile, const vector2<int>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ')';
}

