
inline vector2<bool>::vector2 ()
{
	// Uninitialized for performance in array construction.
}


inline vector2<bool>::vector2 (const vector2<bool>& vec)
{
	m[0] = vec.m[0];
	m[1] = vec.m[1];
}



inline vector2<bool>::vector2 (bool x, bool y)
{
	m[0] = x;
	m[1] = y;
}


inline vector2<bool>& vector2<bool>::operator= (const vector2<bool>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    return *this;
}



inline vector2<bool> vector2<bool>::operator|| (const vector2<bool>& vec) const
{
    return vector2<bool>
    (
    m[0] || vec.m[0],
    m[1] || vec.m[1]
    );
}



inline vector2<bool> vector2<bool>::operator|| (bool b) const
{
    return vector2<bool>
        (
        m[0] || b,
        m[1] || b
    );
}



inline vector2<bool> vector2<bool>::operator&& (const vector2<bool>& vec) const
{
    return vector2<bool>
    (
        m[0] && vec.m[0],
        m[1] && vec.m[1]
    );
}



inline vector2<bool> vector2<bool>::operator&& (bool b) const
{
    return vector2<bool>
        (
        m[0] && b,
        m[1] && b
    );
}




inline vector2<bool> vector2<bool>::operator^ (const vector2<bool>& vec) const
{
    return vector2<bool>
        (
        m[0] & vec.m[0],
        m[1] & vec.m[1]
    );
}


inline vector2<bool> vector2<bool>::operator^ ( bool b ) const
{
    return vector2<bool>
        (
        m[0] ^ b,
        m[1] ^ b 
    );
}



inline vector2<bool>& vector2<bool>::operator^= ( const vector2<bool>& vec )
{
    m[0] ^= vec.m[0];
    m[1] ^= vec.m[1];
    return *this;
}


inline vector2<bool>& vector2<bool>::operator^= ( bool b )
{
    m[0] ^= b;
    m[1] ^= b;
    return *this;
}



inline std::ostream& operator<< (std::ostream& outFile, const vector2<bool>& vec)
{
    return outFile << '(' << vec.x << ',' << vec.y << ')';
}

