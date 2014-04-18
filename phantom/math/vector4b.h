#ifndef o_math_vector4b_h__
#define o_math_vector4b_h__

#include "vector4.h"

o_namespace_begin(phantom, math)

template<>
class vector4<bool>
{
public:
    typedef vector4<bool> self_type;

	// Construction.
	vector4 ();  // uninitialized
    vector4 (const vector4<bool>& vec);
	vector4 (bool x, bool y, bool z, bool w);
		
	// Assignment.
	self_type& operator= (const self_type& vec);

    inline vector4<bool>  operator|| (const vector4<bool>& vec) const;
    inline vector4<bool>  operator|| (bool b) const;
    inline vector4<bool>  operator&& (const vector4<bool>& vec) const;
    inline vector4<bool>  operator&& (bool b) const;
    inline vector4<bool>  operator^ (const vector4<bool>& vec) const;
    inline vector4<bool>  operator^ ( bool b ) const;

    inline vector4<bool>& operator^= ( const vector4<bool>& vec );
    inline vector4<bool>& operator^= ( bool b );
		
	const bool&  operator[](unsigned int i) const
	{
		o_assert(i<4);
		return m[i];
	}
		
	bool&  operator[](unsigned int i)
	{
		o_assert(i<4);
		return m[i];
	}
		
	bool operator==(const self_type& other) const { return other.x == x && other.y == y  ; }
	bool operator!=(const self_type& other) const { return other.x != x || other.y != y  ; }
						
	// Special vectors.
	static const self_type ZERO;    // (0,0)
	static const self_type UNIT_X;  // (1,0)
	static const self_type UNIT_Y;  // (0,1)
	static const self_type ONE;     // (1,1)
		
public:
	union
	{
		bool m[4];
		struct
		{
            bool x;
            bool y;
            bool z;
            bool w;
		};
	};
};
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector4<bool>& vec);
	
/** Typedefs **/
typedef vector4<bool> vector4b;

#include "vector4b.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector4b_h__
