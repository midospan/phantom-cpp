#ifndef o_math_line2_h__
#define o_math_line2_h__

#include "vector2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), line2);

o_namespace_begin(phantom, math)
	
template<class t_Ty>
class line2
{
public:
    typedef line2<t_Ty>    self_type;
    typedef vector2<t_Ty>  vector2_type;
	// Construction
	line2 ();
	line2 (const vector2_type& p, const vector2_type& d )
	: point(p)
	, direction(d)
	{}
		
	// Assignment.
	inline line2& operator= (const line2<t_Ty>& line )
	{
		point = line.point;
		direction = line.direction;
		return *this;
	}
		
	inline bool operator== (const line2<t_Ty>& line ) const
	{
		return line.point == point && line.direction == direction;
	}
		
	inline bool operator!=(const line2<t_Ty>& line) const
	{
		return !(*this == line);
	}
		
	inline bool absoluteEquals(const line2<t_Ty>& line) const 
	{
		return contains(line.point) && direction.isCollinearTo(line.direction);
	}
		
	// Special lines.
	static const line2<t_Ty> ZERO;    // (0,0) (0,0)
	static const line2<t_Ty> UNIT_X;  // (0,0) (1,0)
	static const line2<t_Ty> UNIT_Y;  // (0,0) (0,1)
	static const line2<t_Ty> ONE;     // (0,0) (1,1)
		
	bool contains( const vector2_type& otherPoint ) const
	{
		return equals(fabs((otherPoint - point).normalized().dot(direction)), (t_Ty)1.0);
	}
	vector2_type getDirection() const { return direction; }
		
	vector2_type getPoint() const { return point; }
		
	inline bool intersects(const line2<t_Ty>& other, vector2_type* out = nullptr, t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const
	{
		vector2_type n1 = direction;
		vector2_type n2 = -other.direction;
		vector2_type m = other.point - point;
		t_Ty det = n1.x*n2.y - n1.y*n2.x;
		if (std::fabs(det) <= epsilon)
		{
			// Vectors are collinear
			return false;
		}
		t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
		if(out)
		{
			*out = point + n1*t;
		}
		return true;
	}
		
	inline bool overlaps( const line2<t_Ty>& other ) const { return contains(other.point); }
		
	inline t_Ty minimumPointDistance(const vector2_type& p) const
	{
		return fabs((p - point).dot(direction.normalized().orthogonalCW()));
	}
		
	inline t_Ty getParameter(vector2_type v, t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
public:
	vector2_type point;
	vector2_type direction;
};
	
typedef line2<float32> line2f;
typedef line2<float64> line2d;
	
#include "line2.inl"
	
o_namespace_end(phantom, math)

#endif
