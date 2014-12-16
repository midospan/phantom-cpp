#ifndef o_math_segment2
#define o_math_segment2

#include "line2.h"
#include "vector2.h"
#include <iostream>

o_declareNT(class, (phantom, math), (typename), (t_Ty), segment2);

o_namespace_begin(phantom, math)

template<class t_Ty>
class segment2
{
public:
    typedef segment2<t_Ty>    self_type;
    typedef vector2<t_Ty>  vector2_type;
	// Construction
	segment2 (); // start & end initialized to vector2_type::ZERO
	segment2 (const self_type& line );
	segment2 (const vector2_type& vec1, const vector2_type& vec2 );
		
	// Assignment.
	inline self_type& operator= (const self_type& line );
	inline bool operator== (const self_type& line ) const
	{
		return line.start == start && line.end == end;
	}
		
	inline bool operator!=(const self_type& line) const
	{
		return !(*this == line);
	}
		
	inline const vector2_type& operator[](size_t index) const
	{
		return index == 0 ? start : end;
	}
		
	inline vector2_type& operator[](size_t index)
	{
		return index == 0 ? start : end;
	}
		
	inline bool equals(const self_type& seg, t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const
	{
		return ((start.equals(seg.start, epsilon) && end.equals(seg.end, epsilon))
				|| (start.equals(seg.end, epsilon) && end.equals(seg.start, epsilon)));
	}
		
	inline bool absoluteEquals(const self_type& line) const 
	{
		return (line.start == start && line.end == end) || (line.start == end && line.end == start);
	}
		
	// Special lines.
	static const self_type ZERO;    // (0,0) (0,0)
	static const self_type UNIT_X;  // (0,0) (1,0)
	static const self_type UNIT_Y;  // (0,0) (0,1)
	static const self_type ONE;     // (0,0) (1,1)
		
	// Geometry
	inline vector2_type closestPoint( const vector2_type& point ) const; // The closest point will always be on the segment limits.
		
	bool containsExclusive( const vector2_type& point, t_Ty epsilon = phantom::math::epsilon<t_Ty>() ) const;
		
	bool containsInclusive( const vector2_type& point, t_Ty epsilon = phantom::math::epsilon<t_Ty>() ) const;
		
	t_Ty   getPointOrientation( const vector2_type& point ) const;
		
	line2<t_Ty> getLine() const { return line2<t_Ty>(start, (end-start).normalized()); }
	vector2_type getDirection() const { return (end-start).normalized(); }
	vector2_type getLengthVector() const { return (end-start); }
    vector2_type getCenter() const { return (start + end) * 0.5f; }
		
	//! Check if the given point is between start and end of the line.
	/** Assumes that the point is already somewhere on the line. */
	bool isPointBetweenStartAndEnd(const vector2_type& point) const
	{
		return point.isBetweenPoints(start, end);
	}
		
	t_Ty minimumPointDistance(const vector2_type& p) 
	{
		vector2_type lv = end - start;
		const t_Ty l2 = lv.lengthSquared();  // i.e. |w-v|^2 -  avoid a sqrt
		// Consider the line extending the segment, parameterized as v + t (w - v).
		// We find projection of point p onto the line. 
		// It falls where t = [(p-v) . (w-v)] / |w-v|^2
		const t_Ty t = (p - start).dot(lv) / l2;
		if (t < 0.0) return p.distance(start);       // Beyond the 'v' end of the segment
		else if (t > 1.0) return p.distance(end);  // Beyond the 'w' end of the segment
		return p.distance(start + t * lv);
	}
		
	vector2_type middle() const { return (start + end) * (t_Ty)0.5; }
		
	inline self_type split(const vector2_type& where)
	{
		o_assert(contains(where));
			
		self_type secondPart(where, end);
			
		end = where;
			
		return secondPart;
	}
		
	inline void reverse()
	{
		vector2_type temp = start;
		start = end;
		end = temp;
	}
		
	inline self_type reversed()
	{
		return self_type(end, start);
	}
		
	inline bool hasCommonPoint(const self_type seg,
								t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsRayExclusive(const line2<t_Ty>& line
                                , vector2_type* out = nullptr
                                , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsRayInclusive(const line2<t_Ty>& line
            	                , vector2_type* out = nullptr
                                , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsExclusive(const self_type& other
                                , vector2_type* out = nullptr
                                , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsInclusive(const self_type& other
									, vector2_type* out = nullptr
                                    , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsExclusive(const line2<t_Ty>& line
                                    , vector2_type* out = nullptr
                                    , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsInclusive(const line2<t_Ty>& line
                                    , vector2_type* out
                                    , t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool intersectsOrContains(const self_type& other,
										vector2_type* out = nullptr) const;
		
	inline bool overlapsExclusive(const self_type& other, t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
	inline bool overlapsInclusive(const self_type& other, t_Ty epsilon = phantom::math::epsilon<t_Ty>()) const;
		
public:
	vector2_type start;
	vector2_type end;
};
/** Typdefs **/
typedef segment2<float32> segment2f;
typedef segment2<float64> segment2d;
	
// Debugging output.
template<class t_Ty>
std::ostream& operator<< (std::ostream& outFile, const segment2<t_Ty>& line );
	
	
template<class t_Ty>
inline segment2<t_Ty>::segment2 ()
: start(vector2_type::ZERO)
, end(vector2_type::ZERO)
{}
	
	
template<class t_Ty>
inline segment2<t_Ty>::segment2 (const self_type& line)
{
	start = line.start;
	end = line.end;
}
	
	
template<class t_Ty>
inline segment2<t_Ty>::segment2 (const vector2_type& vec1, const vector2_type& vec2)
{
	start.m[0] = vec1.m[0];
	start.m[1] = vec1.m[1];
		
	end.m[0] = vec2.m[0];
	end.m[1] = vec2.m[1];
}
	
	
template<class t_Ty>
inline segment2<t_Ty>& segment2<t_Ty>::operator= (const self_type& line)
{
	start   = line.start;
	end     = line.end;
	return *this;
}
	
	
template<class t_Ty>
inline vector2<t_Ty> segment2<t_Ty>::closestPoint(const vector2_type& point) const
{
	vector2_type c = point - start;
	vector2_type v = end - start;
	t_Ty d = v.length();
	v /= d;
	t_Ty t = v.dot(c);
		
	if ( t < 0.0 ) return start;
	if ( t > d ) return end;
		
	v *= t;
	return start + v;
}
	
	
template<class t_Ty>
inline bool segment2<t_Ty>::containsInclusive(const vector2_type& point, t_Ty epsilon) const
{
    if((point.equals(start, epsilon)) || (point.equals(end, epsilon)))
    {
        return true;
    }

    vector2_type sp = point - start;
    vector2_type se = end - start;

    t_Ty selen = (end - start).length();
    t_Ty splen = (point - start).length();

    t_Ty lenProj = sp.dot(se) / selen;
    return (lenProj >= epsilon && lenProj <= selen
        && ((lenProj / splen) > t_Ty(1) - epsilon));
}
	
	
	
template<class t_Ty>
bool segment2<t_Ty>::containsExclusive(const vector2_type& point, t_Ty epsilon) const
{
	if((point.equals(start, epsilon)) || (point.equals(end, epsilon)))
	{
		return false;
	}

    vector2_type sp = point - start;
    vector2_type se = end - start;

    t_Ty selen = (end-start).length();
    t_Ty splen = (point - start).length();

    t_Ty lenProj = sp.dot(se) / selen;
    return (lenProj > epsilon && lenProj < selen
        && ((lenProj / splen) > t_Ty(1) - epsilon));

}
	
	
template<class t_Ty>
inline t_Ty segment2<t_Ty>::getPointOrientation(const vector2_type& point) const
{
    return ( (end.x - start.x) * (point.y - start.y) -
            (point.x - start.x) * (end.y - start.y) );
}
	
	
template<class t_Ty>
inline std::ostream& operator<< (std::ostream& outFile, const segment2<t_Ty>& line)
{
	return outFile << line.start << ' ' << line.end;
}
	
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsExclusive(const self_type& other, vector2_type* out, t_Ty epsilon) const
{
	vector2_type n1 = end - start;
	vector2_type n2 = other.start - other.end;
	vector2_type m = other.start - start;
	t_Ty det = n1.x*n2.y - n1.y*n2.x;
	if (fabs(det) <= epsilon)
	{
		// Vectors are collinear
		return false;
	}
	t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
	t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
	if ((t > (((t_Ty)0) + epsilon)) && (t < (((t_Ty)1)- epsilon)) && (u > (((t_Ty)0) + epsilon)) && (u < (((t_Ty)1) - epsilon)))
	{
		if(out)
		{
			*out = start + n1*t;
		}
		return true;
	}
	return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsInclusive(const self_type& other, vector2_type* out, t_Ty epsilon) const
{
	vector2_type n1 = end - start;
	vector2_type n2 = other.start - other.end;
	vector2_type m = other.start - start;
	t_Ty det = n1.x*n2.y - n1.y*n2.x;
	if (fabs(det) <= epsilon)
	{
		// Vectors are collinear
		return false;
	}
	t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
	t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
	if (t >= (t_Ty)(-epsilon) && t <= (t_Ty)(1+epsilon) && u >= (t_Ty)(-epsilon) && u < (t_Ty)(1 - epsilon))
	{
		if(out)
		{
			*out = start + n1*t;
		}
		return true;
	}
	return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::hasCommonPoint(const self_type seg
                                        , t_Ty epsilon) const
{
	return (start.equals(seg.start, epsilon)
			|| start.equals(seg.end, epsilon)
			|| end.equals(seg.start, epsilon)
			|| end.equals(seg.end, epsilon));
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsRayExclusive(const line2<t_Ty>& line
                                                , vector2_type* out
                                                , t_Ty epsilon) const
{
	vector2_type n1 = end - start;
    vector2_type n2 = -line.direction;
    vector2_type m = line.point - start;
    t_Ty det = n1.x*n2.y - n1.y*n2.x;
    if (fabs(det) <= epsilon)
    {
        // Vectors are collinear
        return false;
    }
    t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
    t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
    if (t > ((t_Ty)0 + epsilon) && t < ((t_Ty)1 - epsilon) && u > epsilon)
    {
        if(out)
        {
            *out = start + n1*t;
        }
        return true;
    }
    return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsRayInclusive(const line2<t_Ty>& line, vector2_type* out, t_Ty epsilon) const
{
	vector2_type n1 = end - start;
    vector2_type n2 = -line.direction;
    vector2_type m = line.point - start;
    t_Ty det = n1.x*n2.y - n1.y*n2.x;
    if (fabs(det) <= epsilon)
    {
        // Vectors are collinear
        return false;
    }
    t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
    t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
    if (t >= -epsilon && t <= ((t_Ty)1 + epsilon) && u >= -epsilon)
    {
        if(out)
        {
            *out = start + n1*t;
        }
        return true;
    }
    return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsExclusive(const line2<t_Ty>& line, vector2_type* out, t_Ty epsilon /*= nullptr*/) const
{
    vector2_type n1 = end - start;
    vector2_type n2 = -line.direction;
    vector2_type m = line.point - start;
    t_Ty det = n1.x*n2.y - n1.y*n2.x;
    if (fabs(det) <= epsilon)
    {
        // Vectors are collinear
        return false;
    }
    t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
    //t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
    if (t > ((t_Ty)0 + epsilon) && t < ((t_Ty)1- epsilon))
    {
        if(out)
        {
            *out = start + n1*t;
        }
        return true;
    }
    return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsInclusive(const line2<t_Ty>& line
                                    , vector2_type* out
                                    , t_Ty epsilon) const
{
	vector2_type n1 = end - start;
    vector2_type n2 = -line.direction;
    vector2_type m = line.point - start;
    t_Ty det = n1.x*n2.y - n1.y*n2.x;
    if (fabs(det) <= epsilon)
    {
        // Vectors are collinear
        return false;
    }
    t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
    //t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
    if (t > ((t_Ty)(-epsilon)) && t < ((t_Ty)1 + epsilon))
    {
        if(out)
        {
            *out = start + n1*t;
        }
        return true;
    }
    return false;
}
	
	
	
template<class t_Ty>
inline bool segment2<t_Ty>::intersectsOrContains( const segment2<t_Ty>& other, vector2_type* out ) const
{
	vector2_type n1 = end - start;
	vector2_type n2 = other.start - other.end;
	vector2_type m = other.start - start;
	t_Ty det = n1.x*n2.y - n1.y*n2.x;
	if (fabs(det) <= 1e-4)
	{
		// Vectors are collinear
		return false;
	}
	t_Ty t = (n2.y*m.x - n2.x*m.y) / det;
	t_Ty u = (n1.x*m.y - n1.y*m.x) / det;
	if (t >= (t_Ty)0.0 && t <= (t_Ty)1.0 && u >= (t_Ty)0.0 && u <= (t_Ty)1.0)
	{
		if(out)
		{
			*out = start + n1*t;
		}
		return true;
	}
	return false;
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::overlapsExclusive( const segment2<t_Ty>& other, t_Ty epsilon /*= FLT_EPSILON*/ ) const
{
	if(absoluteEquals(other))
	{
		return true;
	}
		
	// not collinear
	math::vector2f n1 = getDirection();
	math::vector2f n2 = -other.getDirection();
	float d = fabs((n1.x*n2.y - n1.y*n2.x));
	if (d > epsilon)
	{
		return false;
	}
	return (containsExclusive(other.start, epsilon)
			|| containsExclusive(other.end, epsilon)
			|| other.containsExclusive(start, epsilon)
			|| other.containsExclusive(end, epsilon));
}
	
template<class t_Ty>
inline bool segment2<t_Ty>::overlapsInclusive(const segment2<t_Ty>& other, t_Ty epsilon) const
{
	// not collinear
	math::vector2f n1 = getDirection();
	math::vector2f n2 = other.getDirection();
	float d = fabs((n1.x*n2.y - n1.y*n2.x));
	if (d > epsilon)
	{
		return false;
	}
	return (containsInclusive(other.start, epsilon)
			|| containsInclusive(other.end, epsilon)
			|| other.containsInclusive(start, epsilon)
			|| other.containsInclusive(end, epsilon));
}
o_namespace_end(phantom, math)
	
#endif
