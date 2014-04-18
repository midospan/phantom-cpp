#ifndef o_math_polygon2
#define o_math_polygon2

#include <vector>
#include "line2.h"
#include "vector2.h"
#include "segment2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), polygon2);

o_namespace_begin(phantom, math)

template<class t_Ty, class Alloc = std::allocator<vector2<t_Ty> > >
class polygon2 : public std::vector<vector2<t_Ty>, Alloc>
{
public:
    typedef typename make_float<t_Ty>::type friendType;
    typedef typename polygon2<t_Ty, Alloc> self_type;
    typedef vector2<t_Ty> value_type;
    typedef t_Ty float_type;
		
	inline explicit polygon2 (const typename std::vector<vector2<t_Ty> >::allocator_type& alloc
								= Alloc())
	:	std::vector<vector2<t_Ty> >(alloc)
	{}
		
	inline explicit polygon2 (typename std::vector<vector2<t_Ty> >::size_type n,
								const typename std::vector<vector2<t_Ty> >::value_type& val = vector2<t_Ty>(),
								const typename std::vector<vector2<t_Ty> >::allocator_type& alloc =
								Alloc())
	:	std::vector<vector2<t_Ty> >(n, val, alloc)
	{}
		
	template<class Iterator>
	inline polygon2 (Iterator first, Iterator last,
						const typename std::vector<vector2<t_Ty> >::allocator_type& alloc
						= std::vector<vector2<t_Ty> >::allocator_type())
	:	std::vector<t_Ty>(first, last, alloc)
	{}
		
	inline polygon2 (const polygon2& p)
	:	std::vector<vector2<t_Ty> >(p)
	{}
		
	inline polygon2 (const std::vector<vector2<t_Ty> >& p)
	:	std::vector<vector2<t_Ty> >(p)
	{}
		
	inline polygon2 (const polygon2<friendType> p)
	{
		for (auto it = p.begin(); it != p.end(); ++it)
		{
			this->push_back(vector2<t_Ty>(*it));
		}
	}
		
	// Check if a polygon is simple by checking only segment intersection
	bool isSimpleWithOverlap(t_Ty epsilon = epsilon<t_Ty>()) const;
	 	
	bool isSimple(t_Ty epsilon = epsilon<t_Ty>()) const;

    t_Ty signedArea() const 
    {
        if(empty()) return 0.f;
        if(size() < 3)
            return (t_Ty)0.0;
        t_Ty acc = (t_Ty)0;
        size_t s = size()-1;
        size_t i = 0;
        for(; i < s; ++i)
        {
            acc += (operator[](i).x*operator[](i+1).y - operator[](i+1).x *operator[](i).y);
        }
        return acc/t_Ty(2.);
    }
		
    bool isCounterClockWise(t_Ty epsilon = epsilon<t_Ty>()) const 
    {
        return signedArea() > 0.f + epsilon;
    }

    bool isClockWise(t_Ty epsilon = epsilon<t_Ty>()) const 
    {
        return signedArea() < 0.f-epsilon;
    }
	/**
		* @brief Classic algorithm using Jordan theorem. Project an horizontal line and
		*	count the number of intersection. Even number means the point is outside
		*	the polygon
		*/
	bool containsExclusive(const vector2<t_Ty>& point, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool containsInclusive(const vector2<t_Ty>& point, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool includesExclusive(const polygon2<t_Ty, Alloc>& otherPolygon, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool includesInclusive(const polygon2<t_Ty, Alloc>& otherPolygon, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool intersectsExclusive(const segment2<t_Ty>& seg, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool intersectsInclusive(const segment2<t_Ty>& seg, t_Ty epsilon = epsilon<t_Ty>()) const;
		
	bool intersects(const polygon2<t_Ty, Alloc>& polygon, std::vector<math::vector2f>* intersectionPoints = nullptr, t_Ty epsilon = epsilon<t_Ty>()) const;

    bool closedIntersectsClosed(const polygon2<t_Ty, Alloc>& polygon, std::vector<math::vector2f>* intersectionPoints = nullptr, t_Ty epsilon = epsilon<t_Ty>()) const;

    bool isDegenerated(t_Ty epsilon = epsilon<t_Ty>()) const 
    {
        o_assert(back() == front());
        for(size_t i = 0; i<p.size()-1; ++i)
        {
            math::segment2f s0(operator[](i+0), operator[](i+1));

            for(size_t j = i+1; j<p.size()-1; ++j)
            {
                math::segment2f s1(operator[](j+0), operator[](j+1));

                if(s0.intersectsExclusive(s1, nullptr, epsilon))
                    return true;
            }
        }
        return false;
    }

    bool isSelfOverlapping(t_Ty epsilon = epsilon<t_Ty>()) const 
    {
        for(size_t i = 0; i<p.size()-1; ++i)
        {
            math::segment2f s0(operator[](i+0), operator[](i+1));

            for(size_t j = i+1; j<p.size()-1; ++j)
            {
                math::segment2f s1(operator[](j+0), operator[](j+1));

                if(s0.overlapsExclusive(s1, epsilon))
                    return true;
            }
        }
        return false;
    }

    void trace()
    {
        printf("Polygone[");
        for(auto it = begin(); it != end(); ++it)
        {
            if(it != begin())
                printf(",");
            printf("(%f,%f)", it->x, it->y);
        }
        printf("]\n");
    }
};
	
typedef polygon2<float32> polygon2f;
typedef polygon2<float64> polygon2d;
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::isSimpleWithOverlap(t_Ty epsilon) const
{
	if (this->size() < 3)
		return false;
	auto endIt = this->end();
	auto it1 = this->begin();
	segment2<t_Ty> seg1, seg2;
	seg1.end = *it1++;
	for (; it1 != endIt; ++it1)
	{
		seg1.start = seg1.end;
		seg1.end = *it1;
		auto it2 = it1;
		seg2.end = *it2++;
		for (; it2 != endIt; ++it2)
		{
			seg2.start = seg2.end;
			seg2.end = *it2;
			if (seg1.intersectsExclusive(seg2, nullptr, epsilon))
				return false;
		}
	}
	return true;
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::isSimple(t_Ty epsilon) const
{
	if (this->size() < 3)
		return false;
	auto endIt = this->end();
	auto it1 = this->begin();
	segment2<t_Ty> seg1, seg2;
	seg1.end = *it1++;
	for (; it1 != endIt; ++it1)
	{
		seg1.start = seg1.end;
		seg1.end = *it1;
		auto it2 = it1;
		seg2.end = *it2++;
		for (; it2 != endIt; ++it2)
		{
			seg2.start = seg2.end;
			seg2.end = *it2;
			if (seg1.intersectsExclusive(seg2, nullptr, epsilon) || seg1.overlapsExclusive(seg2, epsilon))
				return false;
		}
	}
	return true;
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::containsExclusive(const vector2<t_Ty>& point, t_Ty epsilon) const
{
	o_assert(this->size() > 1);
	line2<t_Ty> testRay(point, math::vector2<t_Ty>(1.f, 0.f));
	auto it = this->begin();
	vector2<t_Ty> lastPt, intersectionPoint, currPt = *it;
	t_Ty horizontalLimit = point.y;
	++it;
	int count = 0;
	for (; it != this->end(); ++it)
	{
		lastPt = currPt;
		currPt = *it;
		segment2<t_Ty> s(lastPt, currPt);
		if (s.containsInclusive(point, epsilon))
			return false;
		else if (s.intersectsRayInclusive(testRay, &intersectionPoint, epsilon))
		{
			// Only count an intersection with an extremity of the segment if
			// is other extremity is above the test line
			if (!((s.start.distance(intersectionPoint) < epsilon && s.end.y < horizontalLimit)
				|| (s.end.distance(intersectionPoint) < epsilon && s.start.y < horizontalLimit)))
			{
				++count;
			}
		}
	}
	return ((count % 2) == 1);
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::containsInclusive(const vector2<t_Ty>& point, t_Ty epsilon) const
{
		o_assert(this->size() > 1);
	line2<t_Ty> testRay(point, math::vector2<t_Ty>(1.f, 0.f));
	auto it = this->begin();
	vector2<t_Ty> lastPt, intersectionPoint, currPt = *it;
	t_Ty horizontalLimit = point.y;
	++it;
	int count = 0;
	for (; it != this->end(); ++it)
	{
		lastPt = currPt;
		currPt = *it;
		segment2<t_Ty> s(lastPt, currPt);
		if (s.containsInclusive(point, epsilon))
			return true;
		else if (s.intersectsRayInclusive(testRay, &intersectionPoint, epsilon))
		{
			// Only count an intersection with an extremity of the segment if
			// is other extremity is above the test line
			if (!((s.start.distance(intersectionPoint) < epsilon && s.end.y < horizontalLimit)
				|| (s.end.distance(intersectionPoint) < epsilon && s.start.y < horizontalLimit)))
			{
				++count;
			}
		}
	}
	return ((count % 2) == 1);
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::includesExclusive(const polygon2<t_Ty, Alloc>& otherPolygon, t_Ty epsilon) const
{
	auto it = otherPolygon.begin();
	for (; it != otherPolygon.end(); ++it)
	{
		if (!this->containsExclusive(*it, epsilon))
			return false;
	}
	return true;
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::includesInclusive(const polygon2<t_Ty, Alloc>& otherPolygon, t_Ty epsilon) const
{
	auto it = otherPolygon.begin();
	for (; it != otherPolygon.end(); ++it)
	{
		if (!this->containsInclusive(*it, epsilon))
			return false;
	}
	return true;
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::intersectsExclusive(const segment2<t_Ty>& seg, t_Ty epsilon) const
{
	if (this->size() < 2)
        return false;
	if (containsExclusive(seg.start, epsilon) || containsExclusive(seg.end, epsilon)
		|| containsExclusive((seg.start + seg.end)/2.f, epsilon))
	{
		return true;
	}
	segment2<t_Ty> seg1;
	auto it = this->begin();
	seg1.end = *it;
	++it;
	int count = 0;
	for (; it != this->end(); ++it)
	{
		seg1.start = seg1.end;
		seg1.end = *it;
		if (!seg.overlapsExclusive(seg1, epsilon) && seg.intersectsInclusive(seg1, nullptr, epsilon))
		{
			count += 1;
			if (count == 2)
				return true;
		}
	}
	return false;
}
	
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::intersectsInclusive(const segment2<t_Ty>& seg, t_Ty epsilon) const
{
	if (this->size() < 2)
		return false;
	if (contains(seg.start, epsilon) || contains(seg.end, epsilon)
		|| contains((seg.start + seg.end)/2.f, epsilon))
	{
		return true;
	}
	segment2<t_Ty> seg1;
	auto it = this->begin();
	seg1.end = *it;
	++it;

	for (; it != this->end(); ++it)
	{
		seg1.start = seg1.end;
		seg1.end = *it;
		if (seg.intersectsInclusive(seg1, nullptr, epsilon))
		{
			return true;
		}
	}
	return false;
}

/* Point inclusion version */
template<class t_Ty, class Alloc>
bool polygon2<t_Ty, Alloc>::intersects(const polygon2<t_Ty, Alloc>& otherPolygon, std::vector<math::vector2f>* intersectionPoints, t_Ty epsilon) const
{
    self_type p = *this;
    self_type q = otherPolygon;
    for(size_t i = 0; i<p.size()-1; ++i)
    {
        math::segment2f s0(operator[](i+0), operator[](i+1));

        for(size_t j = 0; j<q.size()-1; ++j)
        {
            math::segment2f s1(q[j+0], q[j+1]);

            math::vector2f intersectionPoint;
            if(s0.intersectsExclusive(s1, &intersectionPoint, epsilon))
            {
                if(intersectionPoints)
                {
                        intersectionPoints->push_back(intersectionPoint);           
                }
                else return true;
            }
        }
    }
    return intersectionPoints ? intersectionPoints->size() > 0 : false;
}
o_namespace_end(phantom, math)

#endif // o_math_polygon2
