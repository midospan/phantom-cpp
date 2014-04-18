#ifndef o_math_transform2_h
#define o_math_transform2_h

#include "angle.h"
#include "matrix2x2.h"
#include "matrix3x3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), transform2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class transform2
{    
public:
    typedef transform2<t_Ty> self_type;
    typedef matrix2x2<t_Ty> matrix2x2_type;
    typedef matrix3x3<t_Ty> matrix3x3_type;
    typedef vector2<t_Ty> vector2_type;
    typedef angle<t_Ty> angle_type;

	inline transform2()
		: position((t_Ty)0, (t_Ty)0)
		, orientation((t_Ty)1, (t_Ty)0)
		, scale((t_Ty)1, (t_Ty)1)
	{

	}

	inline transform2(const vector2_type& p, const angle_type& o, const vector2_type& s)
		: position(p)
		, orientation(o)
		, scale(s)
	{

	}

    inline transform2(const transform2& other)
        : position(other.position)
        , orientation(other.orientation)
        , scale(other.scale)
    {

    }

    inline transform2& operator=(const transform2& other) 
    {
        position = other.position;
        orientation = other.orientation;
        scale = other.scale;
        return *this;
    }

	/// Set this to the identity transform.
	inline void setIdentity()
	{
		position = vector2_type((t_Ty)0, (t_Ty)0);
		orientation.setIdentity();
		scale.x = (t_Ty)1;
		scale.y = (t_Ty)1;
	}

	/// Set this based on the position and angle.
	inline void set(const vector2_type& aPosition, t_Ty aAngle, const vector2_type& aScale)
	{
		position = aPosition;
		orientation.setRadian(aAngle);
		scale = aScale;
	}

	inline void set(const vector2_type& aPosition, t_Ty aAngle)
	{
		position = aPosition;
		orientation.setRadian(aAngle);
	}

	inline matrix3x3_type toMatrix() const
	{
		return matrix3x3_type(orientation.c * scale.x
				, orientation.s * scale.y
				, (t_Ty)0
				, -orientation.s * scale.x
				, orientation.c * scale.y
				, (t_Ty)0
				, position.x
				, position.y
				, (t_Ty)1);
	}


	inline void toMatrix(matrix3x3_type& inOut) const
	{
		t_Ty* m = inOut.m;

		// col 0
		*m++ = orientation.c * scale.x;
		*m++ = orientation.s * scale.y;
		*m++ = (t_Ty)0;

		// col 1
		*m++ = -orientation.s * scale.x;
		*m++ = orientation.c * scale.y;
		*m++ = (t_Ty)0;

		// col 2
		*m++ = position.x;
		*m++ = position.y;
		*m++ = (t_Ty)1;
	}

	inline matrix3x3_type toMatrixWithoutScale() const
	{
		return matrix3x3_type(orientation.c
				, orientation.s
				, (t_Ty)0
				, -orientation.s
				, orientation.c
				, (t_Ty)0
				, position.x
				, position.y
				, (t_Ty)1);
	}

	inline void toMatrixWithoutScale (matrix3x3_type& inOut) const
	{
		t_Ty* m = inOut.m;

		// col 0
		*m++ = orientation.c ;
		*m++ = orientation.s;
		*m++ = (t_Ty)0;

		// col 1
		*m++ = -orientation.s;
		*m++ = orientation.c ;
		*m++ = (t_Ty)0;

		// col 2
		*m++ = position.x;
		*m++ = position.y;
		*m++ = (t_Ty)1;
	}

	inline matrix2x2_type toRotationMatrix() const
	{
		return matrix2x2_type(orientation.c
				, orientation.s
				, -orientation.s
				, orientation.c );

	}

	inline void toRotationMatrix(matrix2x2_type& inOut) const
	{
		t_Ty* m = inOut.m;

		// col 0
		*m++ = orientation.c ;
		*m++ = orientation.s;

		// col 1
		*m++ = -orientation.s;
		*m++ = orientation.c ;

	}

	inline bool operator==(const self_type& other) const
	{
		return (other.position == position)
			&& (other.scale == scale)
			&& (other.orientation == orientation);
	}
		
	bool equals(const transform2& other,
						float positionEpsilon = FLT_EPSILON,
						float orientationEpsilon = FLT_EPSILON,
						float scaleEpsilon = FLT_EPSILON) const
	{
		return ((other.position.equals(position, positionEpsilon))
				&& (other.orientation.equals(orientation, orientationEpsilon))
				&& (other.scale.equals(scale, scaleEpsilon)));
	}
		
	inline bool operator!=(const self_type& other) const 
	{
		return (other.position != position)
		|| (other.scale != scale)
		|| (other.orientation != orientation);
	}
		
		
	inline vector2_type operator*(const vector2_type& p) const
	{
		vector2_type res = p * scale;
		res = orientation.rotate(res);
		return res + position;
	}
	inline self_type operator*(const self_type& other) const
	{
		return transform2(position + other.position,orientation+other.orientation, scale*other.scale);
		
	}
				
	vector2_type        position;
	angle<t_Ty>     orientation;
	vector2_type        scale;
};
	
typedef transform2<float32> transform2f;
typedef transform2<float64> transform2d;
	
o_namespace_end(phantom, math)

#endif // o_math_transform2_h
