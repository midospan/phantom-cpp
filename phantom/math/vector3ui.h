#ifndef o_math_vector3ui_h__
#define o_math_vector3ui_h__

#include "vector3.h"

o_namespace_begin(phantom, math)

	template<>
	class vector3<unsigned int>
	{
	public:
        typedef vector3<unsigned int> self_type;

		// Construction.
		vector3 ();  // uninitialized
        vector3 (const vector3<unsigned int>& vec);
		vector3 (unsigned int x, unsigned int y, unsigned int z);
		
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
			o_assert(i<3);
			return m[i];
		}
		
		unsigned int&  operator[](unsigned int i)
		{
			o_assert(i<3);
			return m[i];
		}
		
		bool operator==(const self_type& other) const { return other.x == x && other.y == y  ; }
		bool operator!=(const self_type& other) const { return other.x != x || other.y != y  ; }
		
		//! sort in order x, y. Equality with rounding tolerance.
		bool operator<=(const self_type&other) const
		{
			return 	(x<other.x || x == other.x) ||
			((x == other.x) && ( y < other.y || (y == other.y)));
		}
		
		//! sort in order x, y. Equality with rounding tolerance.
		bool operator>=(const self_type&other) const
		{
			return 	(x>other.x || x == other.x) ||
			((x == other.x) && (y>other.y || (y == other.y)));
		}
		
		//! sort in order x, y. Difference must be above rounding tolerance.
		bool operator<(const self_type&other) const
        {
            return ((x == other.x) 
                && ( ((y == other.y) && (z < other.z)) || (y < other.y) )) 
                || (x < other.x) ;
		}
		
		//! sort in order x, y. Difference must be above rounding tolerance.
        bool operator>(const self_type&other) const
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
			unsigned int m[3];
			struct
			{
				unsigned int x;
                unsigned int y;
                unsigned int z;
			};
		};
	};
	
	// Arithmetic operations.
	inline vector3<unsigned int> operator* (unsigned int scalar, const vector3<unsigned int>& vec);
	
	// Debugging output.
	std::ostream& operator<< (std::ostream& outFile, const vector3<unsigned int>& vec);
	
	/** Typedefs **/
	typedef vector3<unsigned int> vector3ui;

#include "vector3ui.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector3ui_h__
