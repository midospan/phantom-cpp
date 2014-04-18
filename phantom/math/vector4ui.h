#ifndef o_math_vector4ui_h__
#define o_math_vector4ui_h__

#include "vector4.h"

o_namespace_begin(phantom, math)

template<>
class vector4<unsigned int>
{
public:
    typedef vector4<unsigned int> self_type;

	// Construction.
	vector4 ();  // uninitialized
    vector4 (const vector4<unsigned int>& vec);
	vector4 (unsigned int x, unsigned int y, unsigned int z);
		
	// Assignment.
	self_type& operator= (const self_type& vec);
		
	// Arithmetic operations.
    inline self_type operator+ (const self_type& vec) const;
    inline self_type operator- (const self_type& vec) const;
    inline self_type operator* (unsigned int integer) const;
    inline self_type operator* ( const self_type& vec ) const;
    inline self_type operator/ (unsigned int integer) const;
    inline self_type operator/ ( const self_type& vec ) const;
		
	// Arithmetic updates.
	inline self_type& operator+= (const self_type& vec);
	inline self_type& operator-= (const self_type& vec);
	inline self_type& operator*= (const self_type& vec);
	inline self_type& operator*= (unsigned int integer);
	inline self_type& operator/= (unsigned int integer);
		
	const unsigned int&  operator[](unsigned int i) const
	{
		o_assert(i<4);
		return m[i];
	}
		
	unsigned int&  operator[](unsigned int i)
	{
		o_assert(i<4);
		return m[i];
	}
		
	bool operator==(const self_type& other) const { return other.x == x && other.y == y  ; }
	bool operator!=(const self_type& other) const { return other.x != x || other.y != y  ; }
		
    bool operator<=(const self_type&other) const
    {
        return (*this == other) || (*this < other);
    }

    bool operator>=(const self_type&other) const
    {
        return (*this == other) || (*this > other);
    }

    bool operator<(const self_type& other) const 
    {
        return ((x == other.x) 
            && (
            (
            (y == other.y) 
            && (
            (
            (z == other.z) && (w < other.w)
            ) 
            || (z < other.z)
            )
            ) 
            || (y < other.y) )
            ) 
            || (x < other.x) ;
    }

    bool operator>(const self_type & other) const 
    {
        return !operator<(other) && operator !=(other);
    }
				
	// Special vectors.
	static const self_type ZERO;    // (0,0)
	static const self_type UNIT_X;  // (1,0)
	static const self_type UNIT_Y;  // (0,1)
	static const self_type ONE;     // (1,1)
	static const self_type INFINITE_VALUE;// (inf,inf)
	static const self_type IDENTITY;// (inf,inf)
		
public:
	union
	{
		unsigned int m[4];
		struct
		{
			unsigned int x;
            unsigned int y;
            unsigned int z;
            unsigned int w;
		};
	};
};
	
// Arithmetic operations.
inline vector4<unsigned int> operator* (unsigned int scalar, const vector4<unsigned int>& vec);
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector4<unsigned int>& vec);
	
/** Typedefs **/
typedef vector4<unsigned int> vector4ui;

#include "vector4ui.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector4ui_h__
