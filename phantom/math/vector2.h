#ifndef o_math_vector2_h__
#define o_math_vector2_h__

#include "phantom/math/scalar_funcs.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), vector2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class vector2
{
public:
    typedef vector2<t_Ty> self_type;
	// Construction.
	vector2 ();  // uninitialized
	vector2 (const self_type& vec);
	vector2 (t_Ty x, t_Ty y);
		
	// Assignment.
	o_forceinline self_type& operator= (const self_type& vec);
		
	// Arithmetic operations.
	o_forceinline self_type operator+ (const self_type& vec) const;
	o_forceinline self_type operator- (const self_type& vec) const;
	o_forceinline self_type operator* ( const self_type& vec ) const;
    o_forceinline self_type operator/ ( const self_type& vec ) const;
    o_forceinline self_type operator+ (t_Ty scalar) const;
    o_forceinline self_type operator- (t_Ty scalar) const;
    o_forceinline self_type operator* (t_Ty scalar) const;
    o_forceinline self_type operator/ (t_Ty scalar) const;
	o_forceinline self_type operator- () const;
		
	// Arithmetic updates.
	o_forceinline self_type& operator+= (const self_type& vec);
	o_forceinline self_type& operator-= (const self_type& vec);
    o_forceinline self_type& operator*= (const self_type& vec);
    o_forceinline self_type& operator/= (const self_type& vec);
	o_forceinline self_type& operator*= (t_Ty scalar);
	o_forceinline self_type& operator/= (t_Ty scalar);
		
    o_forceinline void setZero() { x = 0; y = 0; }
    o_forceinline bool isZero() const { return (x == 0) && (y == 0); }
    o_forceinline void set (t_Ty a_x, t_Ty a_y) {x = a_x; y = a_y; }

    /// Get a skew vector such that dot(skew_vec, other) == cross(vec, other)
    o_forceinline self_type skewed() const
    {
        return self_type(-y, x);
    }

    o_forceinline bool isValid() const { return isNumberValid(x) AND isNumberValid(y); }

	// Vector operations.
    inline t_Ty length () const;
    inline t_Ty lengthApproximated() const;
	inline t_Ty lengthSquared () const;
	inline t_Ty dot (const self_type& vec) const;
    inline t_Ty normalize ();
    inline t_Ty normalizeApproximated();
    inline self_type normalized () const;
    inline self_type normalizedApproximated() const;

    inline self_type lerp(const self_type& v, const t_Ty& t) const 
    {
        return self_type(m[0] + (v.m[0] - m[0]) * t,
            m[1] + (v.m[1] - m[1]) * t);
    }
		
	self_type rotated(t_Ty angle) const
	{
		t_Ty c = cosf(angle);
		t_Ty s = sinf(angle);
		return self_type(c*x - s*y, s*x + c*y);
	}
		
	void rotate(t_Ty angle)
	{
		*this = rotated(angle);
	}
		
	// Returns (y,-x).
	inline self_type orthogonalCW() const;
	inline self_type orthogonalCCW() const;
		
	// Returns (y,-x)/sqrt(x*x+y*y).
	inline self_type normalizedOrthogonalCW () const;
	inline self_type normalizedOrthogonalCCW () const;
		
	// Returns cross((x,y),(V.x,V.y)) = x*V.y - y*V.x.
    inline t_Ty cross (const self_type& vec) const;

    inline self_type cross(t_Ty s) const
    {
        return self_type(s * y, -s * x);
    }
		
	// Compute the axis-aligned bounding box of the points.
	static void computeExtremes (int numVectors, const self_type* vectors,
									self_type& vmin, self_type& vmax);
		
	// Gram-Schmidt orthonormalization.  Take linearly independent vectors U
	// and V and compute an orthonormal set (unit length, mutually
	// perpendicular).
	static void orthonormalize (self_type& u, self_type& v);
		
	// Input V must be a nonzero vector.  The output is an orthonormal basis
	// {U,V}.  The input V is normalized by this function.  If you know V is
	// already unit length, use U = V.perp().
	static void generateOrthonormalBasis (self_type& u, self_type& v);
		
	/**
		* @brief Compute the barycentric coordinates of the point V with respect to the
		*	triangle <V0,V1,V2>, V = b0*V0 + b1*V1 + b2*V2, where b0 + b1 + b2 = 1.
		*	The return value is 'true' iff {V0,V1,V2} is a linearly independent
		*	set.  Numerically, this is measured by |det[V0 V1 V2]| <= epsilon.
		*	The values bary[...] are valid only when the return value is 'true'
		*	but set to zero when the return value is 'false'.
		*/
	bool barycentrics (const self_type& v0, const self_type& v1,
						const self_type& v2, t_Ty bary[3], t_Ty epsilon = (t_Ty)0) const;
		
	// return True if this vector is between begin and end, false if not.
	inline bool isBetweenPoints(const self_type& begin, const self_type& end
								,t_Ty epsilon = epsilon<t_Ty>()) const;
		
	const t_Ty&  operator[](unsigned int i) const
	{
		o_assert(i<2);
		return m[i];
	}
		
	t_Ty&  operator[](unsigned int i)
	{
		o_assert(i<2);
		return m[i];
	}
		
	bool equals(const self_type& other, t_Ty epsilon = epsilon<t_Ty>()) const
	{
		return math::equals<t_Ty>(x, other.x, epsilon) && math::equals(y, other.y, epsilon);
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
		if (fabs(x - other.x) < std::numeric_limits<float32>::epsilon())
			return y < other.y;
		else
			return x < other.x;
	}
		
	//! sort in order x, y. Difference must be above rounding tolerance.
	bool operator>(const self_type&other) const
	{
		return 	!operator<(other) && operator !=(other);
	}


    inline t_Ty  fromPiToMinusPiAngleTo(const self_type& other) const 
    {
        t_Ty a = angleTo(other);
        while (a > o_math_Pi)
            a -= o_math_Pi*2;
        while (a < -o_math_Pi)
            a += o_math_Pi*2;
        return(a);
    }

	t_Ty angleTo(const self_type& other) const
	{
        t_Ty dotResult = normalized().dot(other.normalized());
        o_assert(*((int*)&dotResult) != 0xffc00000);
        t_Ty angle = 0;
        if(dotResult >= t_Ty(1)-epsilon<t_Ty>())
        {
            angle = t_Ty(0);
        }
        else if(dotResult <= t_Ty(-1)+epsilon<t_Ty>())
        {
            angle = t_Ty(o_math_Pi);
        }
        else 
        {
            angle = acos(dotResult);
        }
        o_assert(*((int*)&angle) != 0xffc00000);
        t_Ty crossResult = cross(other);
        if(crossResult < 0)
        {
            angle = -angle;
        }
		return angle;
	}

    t_Ty positiveAngleTo(const self_type& other) const
    {
        t_Ty angle = angleTo(other);

        if(angle < 0) 
            angle += 2.0f*(float)o_math_Pi;
        return angle;
    }
		
	inline t_Ty distance(const self_type& other) const 
	{
		return ((*this)-other).length();
    }

    inline t_Ty distanceApproximated(const self_type& other) const 
    {
        return (other-*this).lengthApproximated();
    }
		
	inline t_Ty distanceSquared(const self_type& other) const 
	{
		return ((*this)-other).lengthSquared();
	}

    inline self_type to(const self_type& other) const { return other-(*this); }
		
	inline t_Ty angleTrigDegree() const
	{
		if (y == 0)
			return x < 0 ? 180.f : 0;
		else
			if (x == 0)
				return y < 0 ? 270.f : 90.f;
			
		if ( y > 0)
			if (x > 0)
				return atan(y/x) * o_math_to_degree;
			else
				return 180.f-atan(y/-x) * o_math_to_degree;
			else
				if (x > 0)
					return 360.f-atan(-y/x) * o_math_to_degree;
				else
					return 180.f+atan(-y/-x) * o_math_to_degree;
	}
		
	inline t_Ty angleTrig() const 
	{
		return angleTrigDegree() * o_math_to_radian;
	}
		
	inline bool isCollinearTo(const self_type& other, t_Ty epsilon = epsilon<t_Ty>()) const
	{
		return fabs(other.normalized().dot(normalized())) >= (1.0f - epsilon);
	}
		
	inline bool isOrthogonalTo(const self_type& other, t_Ty epsilon = epsilon<t_Ty>()) const
	{
		return fabs(dot(other)) <= (0.f + epsilon); 
	}
		
	// Special vectors.
	o_export static const self_type ZERO;    // (0,0)
	o_export static const self_type UNIT_X;  // (1,0)
	o_export static const self_type UNIT_Y;  // (0,1)
	o_export static const self_type ONE;     // (1,1)
	o_export static const self_type INFINITE_VALUE;// (inf,inf)
	o_export static const self_type IDENTITY;// (inf,inf)
				
public:
	union
	{
		t_Ty m[2];
		struct
		{
			t_Ty x;
			t_Ty y;
		};
	};
};
	
// Arithmetic operations.
template<class t_Ty>
inline vector2<t_Ty> operator* (t_Ty scalar, const vector2<t_Ty>& vec);
	
// Debugging output.
template<class t_Ty>
std::ostream& operator<< (std::ostream& outFile, const vector2<t_Ty>& vec);
	
/** Typedefs **/
typedef vector2<float32> vector2f;
typedef vector2<float64> vector2d;

#include "vector2.inl"
	
template<class t_Ty>
inline void getOrderingComponents( const vector2<t_Ty>& p1, const vector2<t_Ty>& p2, vector2<t_Ty>& scalarPoint )
{
	t_Ty scalar_p2, scalar_p1;
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
	scalarPoint = vector2<t_Ty>( scalar_p1, scalar_p2 ); 
}
	
o_namespace_end(phantom, math)

#include "vector2i.h"
#include "vector2ui.h"
#include "vector2b.h"

#endif // o_math_vector2_h__
