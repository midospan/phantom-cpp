#ifndef o_math_line3_h__
#define o_math_line3_h__

#include "vector3.h"
#include "matrix3x3.h"
#include "aabb3.h"
#include "line2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), line3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class line3
{
public:
    typedef line3<t_Ty>    self_type;
    typedef vector3<t_Ty>  vector3_type;

	inline line3(const vector3_type& p, const vector3_type& dir);

	inline self_type& operator=(const self_type& l);

	inline bool operator==(const self_type& l) const;

	inline bool operator!=(const self_type& l) const;

	inline bool absoluteEqual(const self_type& l) const;

    static const self_type UNIT_X;  // (0,0,0) (1,0,0)
    static const self_type UNIT_Y;  // (0,0,0) (0,1,0)
    static const self_type UNIT_Z;  // (0,0,0) (0,0,1)

	inline bool contains(const vector3_type& p) const;

	inline bool isCoplanarTo(const self_type& l) const;

    inline bool intersects(const self_type& l, vector3_type& intersectionPoint) const;
    inline bool intersects(const aabb3<t_Ty>& aabb, vector3_type& intersectionPoint) const;

public:
	vector3_type direction;
	vector3_type point;
};

typedef line3<float32> line3f;
typedef line3<float64> line3d;

#include "line3.inl"

o_namespace_end(phantom, math)

#endif // o_math_line3_h__
