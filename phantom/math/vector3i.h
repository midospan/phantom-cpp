
#ifndef o_math_vector3i_h__
#define o_math_vector3i_h__

#include "vector3.h"

o_namespace_begin(phantom, math)

	template<>
	class vector3<int>
	{
	public:
        typedef vector3<int> self_type;

		// Construction.
		vector3 ();  // uninitialized
        vector3 (const vector3<int>& vec);
		vector3 (int x, int y, int z);
		
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
			o_assert(i<3);
			return m[i];
		}
		
		int&  operator[](unsigned int i)
		{
			o_assert(i<3);
			return m[i];
		}
		
		bool operator==(const self_type& other) const { return other.x == x && other.y == y && other.z == z  ; }
		bool operator!=(const self_type& other) const { return other.x != x || other.y != y || other.z != z  ; }
		
		bool operator<=(const self_type&other) const
        {
            return (*this == other) || (*this < other);
		}
		
		bool operator>=(const self_type&other) const
        {
            return (*this == other) || (*this > other);
		}
		
		//! sort in order x, y, z. Difference must be above rounding tolerance.
		bool operator<(const self_type&other) const
		{
			return ((x == other.x) 
                        && ( ((y == other.y) && (z < other.z)) || (y < other.y) )) 
                        || (x < other.x) ;
		}
		
		//! sort in order x, y. Difference must be above rounding tolerance.
		bool operator>(const self_type&other) const
		{
			return 	!operator<(other) && operator !=(other);
		}
				
		// Special vectors.
		o_export static const self_type ZERO;    // (0,0)
		o_export static const self_type UNIT_X;  // (1,0)
        o_export static const self_type UNIT_Y;  // (0,1)
        o_export static const self_type UNIT_Z;  // (0,1)
		o_export static const self_type ONE;     // (1,1)
		o_export static const self_type INFINITE_VALUE;// (inf,inf)
		
	public:
		union
		{
			int m[3];
			struct
			{
				int x;
                int y;
                int z;
			};
		};
	};
	
	// Arithmetic operations.
	inline vector3<int> operator* (int scalar, const vector3<int>& vec);
	
	// Debugging output.
	std::ostream& operator<< (std::ostream& outFile, const vector3<int>& vec);
	
	/** Typedefs **/
	typedef vector3<int> vector3i;

#include "vector3i.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector3i_h__
