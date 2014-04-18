
inline vector4<bool>::vector4 ()
{
	// Uninitialized for performance in array construction.
}



inline vector4<bool>::vector4 (const vector4<bool>& vec)
{
	m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
}



inline vector4<bool>::vector4 (bool x, bool y, bool z, bool w)
{
	m[0] = x;
    m[1] = y;
    m[2] = z;
    m[3] = w;
}


inline vector4<bool>& vector4<bool>::operator= (const vector4<bool>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    m[3] = vec.m[3];
    return *this;
}



inline vector4<bool> vector4<bool>::operator|| (const vector4<bool>& vec) const
{
    return vector4<bool>
    (
    m[0] || vec.m[0],
    m[1] || vec.m[1],
    m[2] || vec.m[2],
    m[3] || vec.m[3]
    );
}



inline vector4<bool> vector4<bool>::operator|| (bool b) const
{
    return vector4<bool>
        (
        m[0] || b,
        m[1] || b,
        m[2] || b,
        m[3] || b
    );
}



inline vector4<bool> vector4<bool>::operator&& (const vector4<bool>& vec) const
{
    return vector4<bool>
    (
        m[0] && vec.m[0],
        m[1] && vec.m[1],
        m[2] && vec.m[2],
        m[3] && vec.m[3]
    );
}



inline vector4<bool> vector4<bool>::operator&& (bool b) const
{
    return vector4<bool>
        (
        m[0] && b,
        m[1] && b,
        m[2] && b,
        m[3] && b
    );
}




inline vector4<bool> vector4<bool>::operator^ (const vector4<bool>& vec) const
{
    return vector4<bool>
        (
        m[0] & vec.m[0],
        m[1] & vec.m[1],
        m[2] & vec.m[2],
        m[3] & vec.m[3]
    );
}


inline vector4<bool> vector4<bool>::operator^ ( bool b ) const
{
    return vector4<bool>
        (
        m[0] ^ b,
        m[1] ^ b, 
        m[2] ^ b , 
        m[3] ^ b
    );
}



inline vector4<bool>& vector4<bool>::operator^= ( const vector4<bool>& vec )
{
    m[0] ^= vec.m[0];
    m[1] ^= vec.m[1];
    m[2] ^= vec.m[2];
    m[3] ^= vec.m[3];
    return *this;
}


inline vector4<bool>& vector4<bool>::operator^= ( bool b )
{
    m[0] ^= b;
    m[1] ^= b;
    m[2] ^= b;
    m[3] ^= b;
    return *this;
}



inline std::ostream& operator<< (std::ostream& outFile, const vector4<bool>& vec)
{
    return outFile << '(' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << ')';
}

