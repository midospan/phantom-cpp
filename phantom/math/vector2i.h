#ifndef o_math_vector2i_h__
#define o_math_vector2i_h__

#include "vector2.h"

o_namespace_begin(phantom, math)

template<>
class vector2<int>
{
public:
    typedef vector2<int> self_type;

	// Construction.
	vector2 ();  // uninitialized
    vector2 (const vector2<int>& vec);
	vector2 (int x, int y);
		
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
		o_assert(i<2);
		return m[i];
	}
		
	int&  operator[](unsigned int i)
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
		int m[2];
		struct
		{
			int x;
			int y;
		};
	};
};
	
// Arithmetic operations.
inline vector2<int> operator* (int scalar, const vector2<int>& vec);
	
// Debugging output.
std::ostream& operator<< (std::ostream& outFile, const vector2<int>& vec);
	
/** Typedefs **/
typedef vector2<int> vector2i;

#include "vector2i.inl"
	
inline void getOrderingComponents( const vector2<int>& p1, const vector2<int>& p2, vector2<int>& scalarPoint )
{
	int scalar_p2, scalar_p1;
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
	scalarPoint = vector2<int>( scalar_p1, scalar_p2 ); 
}
	
o_namespace_end(phantom, math)

#endif // o_math_vector2i_h__
