#ifndef o_math_aabb3_h__
#define o_math_aabb3_h__

#include "vector3.h"
#include "transform3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), aabb3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class aabb3
{
public:
    typedef aabb3<t_Ty> self_type;
    typedef vector3<t_Ty> vector3_type;

	static const self_type INFINITE_VALUE;
		
	// Construction and destruction.
	inline aabb3 ();  // uninitialized
	inline aabb3 (const vector3_type& min, const vector3_type& max);
	// The caller must ensure that xmin <= xmax, ymin <= ymax, and
	// zmin <= zmax.
	inline aabb3 (t_Ty xmin, t_Ty xmax, t_Ty ymin, t_Ty ymax,
					t_Ty zmin, t_Ty zmax);
		
	~aabb3 ();
		
	// Compute the center of the box and the extents (half-lengths)
	// of the box edges.
	void centerExtents (vector3_type& center, t_Ty extent[3]);
		
	inline vector3_type center() const 
	{
		vector3_type center;
		center[0] = ((t_Ty)0.5)*(max[0] + min[0]);
		center[1] = ((t_Ty)0.5)*(max[1] + min[1]);
		center[2] = ((t_Ty)0.5)*(max[2] + min[2]);
		return center;
	}
		
	inline vector3_type halfSize() const 
	{
		vector3_type extent;
		extent[0] = ((t_Ty)0.5)*(max[0] - min[0]);
		extent[1] = ((t_Ty)0.5)*(max[1] - min[1]);
		extent[2] = ((t_Ty)0.5)*(max[2] - min[2]);
		return extent;
	}
		
	inline t_Ty width() const
	{
		return max[0] - min[0];
	}
		
	inline t_Ty height() const
	{
		return max[1] - min[1];
	}
		
	inline t_Ty depth() const
	{
		return max[2] - min[2];
	}
		
	inline bool isNull() const { return max == vector3_type::ZERO && min == vector3_type::ZERO; }
	inline bool isInfinite() const { return max == vector3_type::INFINITE_VALUE && min == vector3_type::INFINITE_VALUE; }
		
	// Overlap testing is in the strict sense.  If the two boxes are just
	// touching along a common edge or a common face, the boxes are reported
	// as overlapping.
	bool hasXOverlap (const self_type& box) const;
	bool hasYOverlap (const self_type& box) const;
	bool hasZOverlap (const self_type& box) const;
	bool intersects (const self_type& box) const;
		
	inline void combine(const self_type& box)
	{
		if(isNull())
		{
			*this = box;
			return;
		}
        if(box.isNull()) return;
		max[0] = math::max(max[0], box.max[0]);
		max[1] = math::max(max[1], box.max[1]);
		max[2] = math::max(max[2], box.max[2]); 
			
		min[0] = math::min(min[0], box.min[0]);
		min[1] = math::min(min[1], box.min[1]);
		min[2] = math::min(min[2], box.min[2]); 
	}
		
	// The return value is 'true' if there is overlap.  In this case the
	// intersection is stored in 'intersection'.  If the return value is
	// 'false', there is no overlap.  In this case 'intersection' is
	// undefined.
	bool findIntersection (const self_type& box,
							self_type& intersection) const;
		
	void set(const vector3_type& min, const vector3_type& max)
	{
		max = max;
		min = min;
	}
		
	void transform(const transform3<t_Ty>& t)
	{
		if(isInfinite()) return;
		vector3_type points[8];
			
		// Cube points
		points[0] = vector3_type(max.x, max.y, max.z)* t.scale;
		points[1] = vector3_type(max.x, max.y, min.z)* t.scale;
		points[2] = vector3_type(max.x, min.y, max.z)* t.scale;
		points[3] = vector3_type(max.x, min.y, min.z)* t.scale;
		points[4] = vector3_type(min.x, max.y, max.z)* t.scale;
		points[5] = vector3_type(min.x, max.y, min.z)* t.scale;
		points[6] = vector3_type(min.x, min.y, max.z)* t.scale;
		points[7] = vector3_type(min.x, min.y, min.z)* t.scale;
			
		min = vector3_type::ZERO;
		max = vector3_type::ZERO;
			
		// rotate all points and find min max
		for(int i = 0; i<8; ++i)
		{
			points[i] = t.orientation.rotate(points[i]);
				
			// update min/max
			min.x = math::min(points[i].x, min.x);
			min.y = math::min(points[i].y, min.y);
			min.z = math::min(points[i].z, min.z);
			max.x = math::max(points[i].x, max.x);
			max.y = math::max(points[i].y, max.y);
			max.z = math::max(points[i].z, max.z);
		}
			
		min += t.position;
		max += t.position;
			
	}
		
	self_type transformed(const matrix4x4<t_Ty>& m) const
	{
		self_type aabb = *this;
		aabb.transform(m);
		return aabb;
	}
		
	void transform(const matrix4x4<t_Ty>& m)
	{
		min = (m*vector4<t_Ty>(min, (t_Ty)1.0)).xyz();
		max = (m*vector4<t_Ty>(max, (t_Ty)1.0)).xyz();
		vector3_type points[8];
			
		// Cube points
		points[0] = vector3_type(max.x, max.y, max.z);
		points[1] = vector3_type(max.x, max.y, min.z);
		points[2] = vector3_type(max.x, min.y, max.z);
		points[3] = vector3_type(max.x, min.y, min.z);
		points[4] = vector3_type(min.x, max.y, max.z);
		points[5] = vector3_type(min.x, max.y, min.z);
		points[6] = vector3_type(min.x, min.y, max.z);
		points[7] = vector3_type(min.x, min.y, min.z);
			
		// rotate all points and find min max
		for(int i = 0; i<8; ++i)
		{
			// update min/max
			min.x = math::min(points[i].x, min.x);
			min.y = math::min(points[i].y, min.y);
			min.z = math::min(points[i].z, min.z);
			max.x = math::max(points[i].x, max.x);
			max.y = math::max(points[i].y, max.y);
			max.z = math::max(points[i].z, max.z);
		}
	}
		
	self_type operator+(const self_type& other) 
	{
		return self_type(min+other.min, max+other.max);
	}
		
	self_type operator-(const self_type& other) 
	{
		return self_type(min-other.min, max-other.max);
	}
		
	self_type operator*(t_Ty ratio) 
	{
		return self_type(min*ratio, max*ratio);
	}
		
	bool operator==(const self_type& other) const 
	{
		return (max == other.max) && (min == other.min);
	}
		
	bool operator!=(const self_type& other) const 
	{
		return !operator==(other);
	}
		
	vector3_type min, max;
};
	
	
// Typedefs
typedef aabb3<float32> aabb3f;
typedef aabb3<float64> aabb3d;
	
#include "aabb3.inl"

o_namespace_end(phantom, math)

#endif // o_math_aabb3_h__
