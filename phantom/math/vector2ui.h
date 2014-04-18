#ifndef o_math_vector2ui_h__
#define o_math_vector2ui_h__

#include "vector2.h"

o_namespace_begin(phantom, math)

template<>
class vector2<unsigned int>
{
public:
    typedef vector2<unsigned int> self_type;

	// Construction.
	vector2 ();  // uninitialized
    vector2 (const vector2<unsigned int>& vec);
	vector2 (unsigned int x, unsigned int y);
		
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
		o_assert(i<2);
		return m[i];
	}
		
	unsigned int&  operator[](unsigned int i)
	{
		o_assert(i<2);
		return m[i];
	}
		
	bool operator==(const self_type& other) const { return other.x == x && other.y == y  ; }
	bool operator!=(const self_type& other) const { return other.x != x || other.y != y  ; }

    //! sort in order x, y. Equality with rounding tolerance.
    bool operator<=(const self_type&other) const
    {
        return (*this == other) || (*this < other);
    }

    //! sort in order x, y. Equality with rounding tolerance.
    bool operator>=(const self_type&other) const
    {
        return (*this == other) || (*this > other);
    }

    //! sort in order x, y. Difference must be above rounding tolerance.
    bool operator<(const self_type&other) const
    {
        return ((x == other.x) && (y < other.y)) || (x < other.x) ;
    }

    //! sort in order x, y. Difference must be above rounding tolerance.
    bool operator>(const self_type&other) const
    {
        return 	!operator<(other) && operator !=(other);
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
		unsigned int m[2];
		struct
		{
			unsigned int x;
			unsigned int y;
		};
	};
};
	
// Arithmetic operations.
inline vector2<unsigned int> operator* (unsigned int scalar, const vector2<unsigned int>& vec);
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector2<unsigned int>& vec);
	
/** Typedefs **/
typedef vector2<unsigned int> vector2ui;

#include "vector2ui.inl"
	
inline void getOrderingComponents( const vector2<unsigned int>& p1, const vector2<unsigned int>& p2, vector2<unsigned int>& scalarPoint )
{
	unsigned int scalar_p2, scalar_p1;
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
	scalarPoint = vector2<unsigned int>( scalar_p1, scalar_p2 ); 
}
	
o_namespace_end(phantom, math)

#endif // o_math_vector2ui_h__
