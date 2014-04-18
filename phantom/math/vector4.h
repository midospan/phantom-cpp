#ifndef o_math_vector4_h__
#define o_math_vector4_h__

#include "vector3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), vector4);

o_namespace_begin(phantom, math)
    
template<class t_Ty>
class vector4
{
	public:
		typedef vector4<t_Ty> self_type;
		// Construction.
		vector4 ();  // uninitialized
		vector4 (const vector4<t_Ty>& vec);
		vector4 (const vector3<t_Ty>& xyz, t_Ty w);
		vector4 (t_Ty x, t_Ty y, t_Ty z, t_Ty w);

		// Assignment.
		vector4<t_Ty>& operator= (const vector4<t_Ty>& vec);

		// Arithmetic operations.
		o_forceinline vector4<t_Ty> operator+ (const vector4<t_Ty>& vec) const;
        o_forceinline vector4<t_Ty> operator- (const vector4<t_Ty>& vec) const;
        o_forceinline vector4<t_Ty> operator* (const vector4<t_Ty>& vec) const;
        o_forceinline vector4<t_Ty> operator/ (const vector4<t_Ty>& vec) const;
        o_forceinline vector4<t_Ty> operator+ (t_Ty scalar) const;
        o_forceinline vector4<t_Ty> operator- (t_Ty scalar) const;
		o_forceinline vector4<t_Ty> operator* (t_Ty scalar) const;
		o_forceinline vector4<t_Ty> operator/ (t_Ty scalar) const;
		o_forceinline vector4<t_Ty> operator- () const;

		// Arithmetic updates.
		o_forceinline vector4<t_Ty>& operator+= (const vector4<t_Ty>& vec);
        o_forceinline vector4<t_Ty>& operator-= (const vector4<t_Ty>& vec);
        o_forceinline vector4<t_Ty>& operator*= (const vector4<t_Ty>& vec);
        o_forceinline vector4<t_Ty>& operator/= (const vector4<t_Ty>& vec);
        o_forceinline vector4<t_Ty>& operator+= (t_Ty scalar);
        o_forceinline vector4<t_Ty>& operator-= (t_Ty scalar);
        o_forceinline vector4<t_Ty>& operator*= (t_Ty scalar);
        o_forceinline vector4<t_Ty>& operator/= (t_Ty scalar);

		o_forceinline const vector3<t_Ty>& xyz() const { return *((const vector3<t_Ty>*)this); }
		o_forceinline vector3<t_Ty>& xyz() { return *((vector3<t_Ty>*)this); }

		o_forceinline void setXYZ(const vector3<t_Ty>& v) { *((vector3<t_Ty>*)this) = v;  }

		// Vector operations.
		o_forceinline t_Ty length () const;
        o_forceinline t_Ty lengthApproximated() const
        {
            // Approximated Squared Root
            union
            {
                int tmp;
                t_Ty f;
            } u;
            u.f = lengthSquared();
            u.tmp -= 1<<23; /* Remove last bit so 1.0 gives 1.0 */
            /* tmp is now an approximation to logbase2(z) */
            u.tmp >>= 1; /* divide by 2 */
            u.tmp += 1<<29; /* add 64 to exponent: (e+127)/2 =(e/2)+63, */
            /* that represents (e/2)-64 but want e/2 */
            return u.f;//(float32)b2Sqrt(lenSq);
        }
        o_forceinline t_Ty lengthSquared () const;
		
        o_forceinline t_Ty dot (const vector4<t_Ty>& vec) const;
		o_forceinline t_Ty normalize ();

		// Compute the axis-aligned bounding box of the points.
		static void computeExtremes (int numVectors, const vector4<t_Ty>* vectors,
				vector4<t_Ty>& vmin, vector4<t_Ty>& vmax);

		// Special vectors.
		o_export static const vector4<t_Ty> ZERO;
		o_export static const vector4<t_Ty> UNIT_X;  // (1,0,0,0)
		o_export static const vector4<t_Ty> UNIT_Y;  // (0,1,0,0)
		o_export static const vector4<t_Ty> UNIT_Z;  // (0,0,1,0)
		o_export static const vector4<t_Ty> UNIT_W;  // (0,0,0,1)
		o_export static const vector4<t_Ty> ONE;     // (1,1,1,1)


		o_forceinline const t_Ty&  operator[](unsigned int i) const   
		{
			o_assert(i<4);
			return m[i];
		}

		o_forceinline t_Ty&  operator[](unsigned int i) 
		{
			o_assert(i<4);
			return m[i];
		}


		o_forceinline bool operator==(const self_type& other) const { return other.x == x && other.y == y && other.z == z && other.w == w; }
		o_forceinline bool operator!=(const self_type& other) const { return other.x != x || other.y != y || other.z != z || other.w != w; }

        o_forceinline bool operator<=(const self_type&other) const
        {
            return (*this == other) || (*this < other);
        }

        o_forceinline bool operator>=(const self_type&other) const
        {
            return (*this == other) || (*this > other);
        }

        o_forceinline bool operator<(const self_type& other) const 
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

        o_forceinline bool operator>(const self_type & other) const 
        {
            return !operator<(other) && operator !=(other);
        }

	public:
		union
		{
			t_Ty m[4];
			struct
			{
				t_Ty x;
				t_Ty y;
				t_Ty z;
				t_Ty w;
			};
		};
};
	
/** Typdefs **/
typedef vector4<float32> vector4f;
typedef vector4<float64> vector4d;

// Arithmetic operations.
template<class t_Ty>
	o_forceinline vector4<t_Ty> operator* (t_Ty scalar, const vector4<t_Ty>& vec);

// debugging output
template<class t_Ty>
	std::ostream& operator<< (std::ostream& outFile, const vector4<t_Ty>& vec);

#include "vector4.inl"

o_namespace_end(phantom, math)
     
#endif o_math_vector4_h__
