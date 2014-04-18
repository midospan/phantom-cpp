#ifndef o_math_vector4i_h__
#define o_math_vector4i_h__

#include "vector4.h"

o_namespace_begin(phantom, math)

template<>
class vector4<int>
{
public:
    typedef vector4<int> self_type;

	// Construction.
	vector4 ();  // uninitialized
    vector4 (const vector4<int>& vec);
	vector4 (int x, int y, int z, int w);
		
	// Assignment.
	self_type& operator= (const self_type& vec);
		
	// Arithmetic operations.
    inline self_type operator+ (const self_type& vec) const;
    inline self_type operator- (const self_type& vec) const;
    inline self_type operator* (int integer) const;
    inline self_type operator* ( const self_type& vec ) const;
    inline self_type operator/ (int integer) const;
    inline self_type operator/ ( const self_type& vec ) const;
    inline self_type operator- () const;
		
	// Arithmetic updates.
	inline self_type& operator+= (const self_type& vec);
	inline self_type& operator-= (const self_type& vec);
	inline self_type& operator*= (const self_type& vec);
	inline self_type& operator*= (int integer);
	inline self_type& operator/= (int integer);
		
	const int&  operator[](unsigned int i) const
	{
		o_assert(i<4);
		return m[i];
	}
		
	int&  operator[](unsigned int i)
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
		
public:
	union
	{
		int m[4];
		struct
		{
			int x;
            int y;
            int z;
            int w;
		};
	};
};
	
// Arithmetic operations.
inline vector4<int> operator* (int scalar, const vector4<int>& vec);
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector4<int>& vec);
	
/** Typedefs **/
typedef vector4<int> vector4i;

#include "vector4i.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector4i_h__
