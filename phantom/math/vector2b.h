#ifndef o_math_vector2b_h__
#define o_math_vector2b_h__

#include "vector2.h"

o_namespace_begin(phantom, math)


template<>
class vector2<bool>
{
public:
    typedef vector2<bool> self_type;

	// Construction.
	vector2 ();  // uninitialized
    vector2 (const vector2<bool>& vec);
	vector2 (bool x, bool y);
		
	// Assignment.
	self_type& operator= (const self_type& vec);

    inline vector2<bool>  operator|| (const vector2<bool>& vec) const;
    inline vector2<bool>  operator|| (bool b) const;
    inline vector2<bool>  operator&& (const vector2<bool>& vec) const;
    inline vector2<bool>  operator&& (bool b) const;
    inline vector2<bool>  operator^ (const vector2<bool>& vec) const;
    inline vector2<bool>  operator^ ( bool b ) const;

    inline vector2<bool>& operator^= ( const vector2<bool>& vec );
    inline vector2<bool>& operator^= ( bool b );
		
	const bool&  operator[](unsigned int i) const
	{
		o_assert(i<2);
		return m[i];
	}
		
	bool&  operator[](unsigned int i)
	{
		o_assert(i<2);
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
		bool m[2];
		struct
		{
            bool x;
            bool y;
		};
	};
};
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector2<bool>& vec);
	
/** Typedefs **/
typedef vector2<bool> vector2b;

#include "vector2b.inl"
	
inline void getOrderingComponents( const vector2<bool>& p1, const vector2<bool>& p2, vector2<bool>& scalarPoint )
{
	bool scalar_p2, scalar_p1;
	if ( p1.x == p2.x )
	{
		scalar_p1 = p1.y;
		scalar_p2 = p2.y;
	}
	else
	{
		scalar_p1 = p1.x;
		scalar_p2 = p2.x;
	}
	scalarPoint = vector2<bool>( scalar_p1, scalar_p2 ); 
}
	
o_namespace_end(phantom, math)

#endif
