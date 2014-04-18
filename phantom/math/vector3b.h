#ifndef o_math_vector3b_h__
#define o_math_vector3b_h__

#include "vector3.h"

o_namespace_begin(phantom, math)


	template<>
	class vector3<bool>
	{
	public:
        typedef vector3<bool> self_type;

		// Construction.
		vector3 ();  // uninitialized
        vector3 (const vector3<bool>& vec);
		vector3 (bool x, bool y, bool z);
		
		// Assignment.
		self_type& operator= (const self_type& vec);

        inline vector3<bool>  operator|| (const vector3<bool>& vec) const;
        inline vector3<bool>  operator|| (bool b) const;
        inline vector3<bool>  operator&& (const vector3<bool>& vec) const;
        inline vector3<bool>  operator&& (bool b) const;
        inline vector3<bool>  operator^ (const vector3<bool>& vec) const;
        inline vector3<bool>  operator^ ( bool b ) const;

        inline vector3<bool>& operator^= ( const vector3<bool>& vec );
        inline vector3<bool>& operator^= ( bool b );
		
		const bool&  operator[](unsigned int i) const
		{
			o_assert(i<3);
			return m[i];
		}
		
		bool&  operator[](unsigned int i)
		{
			o_assert(i<3);
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
			bool m[3];
			struct
			{
                bool x;
                bool y;
                bool z;
			};
		};
	};
	
	// Debugging output.
	std::ostream& operator<< (std::ostream& outFile, const vector3<bool>& vec);
	
	/** Typedefs **/
	typedef vector3<bool> vector3b;

#include "vector3b.inl"
	
o_namespace_end(phantom, math)

#endif // o_math_vector3b_h__
