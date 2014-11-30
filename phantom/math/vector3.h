#ifndef o_math_vector3_h__
#define o_math_vector3_h__

#include "vector2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), vector3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class vector3
{
public:
	typedef vector3<t_Ty> self_type;
	// Construction.
	inline vector3 ();  // uninitialized
	inline vector3 (const self_type & vec);
	inline vector3 (t_Ty s);
	inline vector3 (t_Ty x, t_Ty y, t_Ty z);
		
	// Assignment.
    inline self_type& operator= (const self_type& vec);
    inline self_type& operator= (t_Ty s);
		
	// Arithmetic operations.
	inline self_type  operator+ (const self_type & vec) const;
	inline self_type  operator- (const self_type & vec) const;
    inline self_type  operator* (const self_type & vec) const;
    inline self_type  operator/ (const self_type & vec) const;
    inline self_type  operator+ (t_Ty scalar) const;
    inline self_type  operator- (t_Ty scalar) const;
	inline self_type  operator* (t_Ty scalar) const;
	inline self_type  operator/ (t_Ty scalar) const;
	inline self_type  operator- () const;
		
	// Arithmetic updates.
	inline self_type & operator+= (const self_type & vec);
	inline self_type & operator-= (const self_type & vec);
    inline self_type & operator*= (const self_type & vec);
    inline self_type & operator/= (const self_type & vec);
    inline self_type & operator+= (t_Ty scalar);
    inline self_type & operator-= (t_Ty scalar);
	inline self_type & operator*= (t_Ty scalar);
	inline self_type & operator/= (t_Ty scalar);
		
	// self_type  operations.
	inline t_Ty length () const;
	inline t_Ty lengthSquared () const;
	inline t_Ty dot (const self_type & vec) const;
	inline t_Ty absDot(const self_type & vec) const
	{
		return fabs(x * vec.x) + fabs(y * vec.y) + fabs(z * vec.z);
	}
		
	inline t_Ty normalize ();
	inline self_type  normalized () const;
		
	inline t_Ty distance(const self_type & other) const
	{
		return ((*this)-other).length();
	}
		
	// Compute the axis-aligned bounding box of the points.
	static void computeExtremes (int numVectors, const self_type * vectors,
									self_type & vmin, self_type & vmax);
		
	// The cross products are computed using the right-handed rule.  Be aware
	// that some graphics APIs use a left-handed rule.  If you have to compute
	// a cross product with these functions and send the result to the API
	// that expects left-handed, you will need to change sign on the vector
	// (replace each component value c by -c).
	self_type  cross (const self_type & vec) const;
	self_type  unitCross (const self_type & vec) const;
		
	// Gram-Schmidt orthonormalization.  Take linearly independent vectors
	// U, V, and W and compute an orthonormal set (unit length, mutually
	// perpendicular).
	static void orthonormalize (self_type & u, self_type & v, self_type & w);
	static void orthonormalize (self_type * v);
		
	// Input W must be a nonzero vector. The output is an orthonormal basis
	// {U,V,W}.  The input W is normalized by this function.  If you know
	// W is already unit length, use GenerateComplementBasis to compute U
	// and V.
	static void generateOrthonormalBasis (self_type & u, self_type & v, self_type & w);
		
	// Input W must be a unit-length vector.  The output vectors {U,V} are
	// unit length and mutually perpendicular, and {U,V,W} is an orthonormal
	// basis.
	static void generateComplementBasis (self_type & u, self_type & v,
											const self_type & w);
		
	// Compute the barycentric coordinates of the point V with respect to the
	// tetrahedron <V0,V1,V2,V3>, V = b0*V0 + b1*V1 + b2*V2 + b3*V3, where
	// b0 + b1 + b2 + b3 = 1.  The return value is 'true' iff {V0,V1,V2,V3} is
	// a linearly independent set.  Numerically, this is measured by
	// |det[V0 V1 V2 V3]| <= epsilon.  The values bary[...] are valid only
	// when the return value is 'true' but set to zero when the return value
	// is 'false'.
	bool barycentrics (const self_type & v0, const self_type & v1,
						const self_type & v2, const self_type & v3, t_Ty bary[4],
						t_Ty epsilon = (t_Ty)0) const;
		
		
	const t_Ty&  operator[](unsigned int i) const   
	{
		o_assert(i<3);
		return m[i];
	}
		
	t_Ty&  operator[](unsigned int i) 
	{
		o_assert(i<3);
		return m[i];
	}
		
	bool equals(const self_type & other) const
	{
		return math::equals(x, other.x) && math::equals(y, other.y) && math::equals(z, other.z);
	}
		
	t_Ty angleTo(const self_type & other) const
	{
        return acosf(normalized().dot(other.normalized()));
	}

	t_Ty positiveAngleTo(const self_type & other, const self_type & axis) const
	{
		return cross(other).dot(axis) > 0.f 
        ? acosf( normalized().dot(other.normalized()))
        : -acosf( normalized().dot(other.normalized()));
	}
		
	bool operator==(const self_type & other) const { return other.x == x && other.y == y && other.z == z ; }
		
	bool operator!=(const self_type & other) const { return other.x != x || other.y != y || other.z != z ; }

    bool operator<=(const self_type&other) const
    {
        return (*this == other) || (*this < other);
    }

    bool operator>=(const self_type&other) const
    {
        return (*this == other) || (*this > other);
    }

	bool operator<(const self_type & other) const 
    {
        return ((x == other.x) 
            && ( ((y == other.y) && (z < other.z)) || (y < other.y) )) 
            || (x < other.x) ;
    }

    bool operator>(const self_type & other) const 
    {
        return !operator<(other) && operator !=(other);
    }
		
	inline bool isCollinearTo(const self_type & v) const;
		
	// Special vectors.
	o_export static const self_type  ZERO;    // (0,0,0)
	o_export static const self_type  UNIT_X;  // (1,0,0)
	o_export static const self_type  UNIT_Y;  // (0,1,0)
	o_export static const self_type  UNIT_Z;  // (0,0,1)
	o_export static const self_type  ONE;     // (1,1,1)
	o_export static const self_type  INFINITE_VALUE;// (inf,inf,inf)
		
	inline void makeFloor(const self_type & cmp) 
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
		if( cmp.z < z ) z = cmp.z;
	}
		
	inline void makeCeil(const self_type & cmp) 
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
		if( cmp.z > z ) z = cmp.z;
	}
		
	inline const vector2<t_Ty>& xy() const { return *((const vector2<t_Ty>*)this); }
		
	inline vector2<t_Ty>& xy() { return *((vector2<t_Ty>*)this); }
		
	inline vector2<t_Ty> xz() const { return vector2<t_Ty>(x, z); }
		
	inline void setXy(const vector2<t_Ty>& v) { *((vector2<t_Ty>*)this) = v;  }
			
public:
	union
	{
		t_Ty m[3];
		struct
		{
			t_Ty x;
			t_Ty y;
			t_Ty z;
		};
	};
};

			
// Arithmetic operations.
template<class t_Ty>
inline vector3<t_Ty> operator* (t_Ty scalar, const vector3<t_Ty> & vec);
	
// Debugging output.
template<class t_Ty>
std::ostream& operator<< (std::ostream& outFile, const vector3<t_Ty> & vec);
	
/** Typedefs **/
typedef vector3<float32> vector3f;
typedef vector3<float64> vector3d;

#include "vector3.inl"

o_namespace_end(phantom, math)


#include "vector3i.h"
#include "vector3ui.h"
#include "vector3b.h"

o_namespace_begin(phantom, detail)

template<typename t_Ty>
struct safe_constructor_ <math::vector3<t_Ty>>
{
    static void safeConstruct(void* a_pInstance) 
    { 
        ((math::vector3<t_Ty>*)a_pInstance)->x = 0;
        ((math::vector3<t_Ty>*)a_pInstance)->y = 0;
        ((math::vector3<t_Ty>*)a_pInstance)->z = 0;
    }
};

o_namespace_end(phantom, detail)

#endif // o_math_vector3_h__
