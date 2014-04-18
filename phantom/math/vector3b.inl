
inline vector3<bool>::vector3 ()
{
	// Uninitialized for performance in array construction.
}



inline vector3<bool>::vector3 (const vector3<bool>& vec)
{
	m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
}



inline vector3<bool>::vector3 (bool x, bool y, bool z)
{
	m[0] = x;
    m[1] = y;
    m[2] = z;
}


inline vector3<bool>& vector3<bool>::operator= (const vector3<bool>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    return *this;
}



inline vector3<bool> vector3<bool>::operator|| (const vector3<bool>& vec) const
{
    return vector3<bool>
    (
    m[0] || vec.m[0],
    m[1] || vec.m[1],
    m[2] || vec.m[2]
    );
}



inline vector3<bool> vector3<bool>::operator|| (bool b) const
{
    return vector3<bool>
        (
        m[0] || b,
        m[1] || b,
        m[2] || b
    );
}



inline vector3<bool> vector3<bool>::operator&& (const vector3<bool>& vec) const
{
    return vector3<bool>
    (
        m[0] && vec.m[0],
        m[1] && vec.m[1],
        m[2] && vec.m[2]
    );
}



inline vector3<bool> vector3<bool>::operator&& (bool b) const
{
    return vector3<bool>
        (
        m[0] && b,
        m[1] && b,
        m[2] && b
    );
}




inline vector3<bool> vector3<bool>::operator^ (const vector3<bool>& vec) const
{
    return vector3<bool>
        (
        m[0] & vec.m[0],
        m[1] & vec.m[1],
        m[2] & vec.m[2]
    );
}


inline vector3<bool> vector3<bool>::operator^ ( bool b ) const
{
    return vector3<bool>
        (
        m[0] ^ b,
        m[1] ^ b, 
        m[2] ^ b 
    );
}



inline vector3<bool>& vector3<bool>::operator^= ( const vector3<bool>& vec )
{
    m[0] ^= vec.m[0];
    m[1] ^= vec.m[1];
    m[2] ^= vec.m[2];
    return *this;
}


inline vector3<bool>& vector3<bool>::operator^= ( bool b )
{
    m[0] ^= b;
    m[1] ^= b;
    m[2] ^= b;
    return *this;
}



inline std::ostream& operator<< (std::ostream& outFile, const vector3<bool>& vec)
{
    return outFile << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
}

