#ifndef o_math_transform3_h
#define o_math_transform3_h

#include "vector3.h"
#include "quaternion.h"
#include "matrix4x4.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), transform3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class transform3
{
public:
    typedef transform3<t_Ty> self_type;
    typedef vector3<t_Ty> vector3_type;
    typedef quaternion<t_Ty> quaternion_type;
    typedef matrix3x3<t_Ty> matrix3x3_type;
    typedef matrix4x4<t_Ty> matrix4x4_type;

	transform3 () // initialized to identity
	: position(0,0,0)
	, orientation(1,0,0,0)
	, scale(1,1,1)
	{}
		
	transform3 (const vector3_type& aposition, const quaternion_type& aorientation, const vector3_type& ascale) // initialized to identity
	: position(aposition)
	, orientation(aorientation)
	, scale(ascale)
	{}
		
	// Transform multiplication, for example : World = Parent(this) * Local
	inline self_type operator*(const self_type& local) const
	{
		self_type world = *this; // initialize world as parent
			
		// rotate the local position according to the parent world orientation
		world.position += orientation.rotate(local.position*world.scale);
		world.orientation = orientation*local.orientation;
		world.scale *= local.scale;
		return world;
	}
		
	inline self_type operator*(t_Ty scalar) const
	{
		self_type result = *this; // initialize world as parent
			
		// rotate the local position according to the parent world orientation
		result.position *= scalar;
		result.orientation *= scalar;
		result.scale *= scalar;
		return result;
	}
		
	inline self_type operator+(const self_type& added) const
	{
		self_type result = *this; // initialize world as parent
			
		// rotate the local position according to the parent world orientation
		result.position += added.position;
		result.orientation = result.orientation * added.orientation;
		result.scale += added.scale;
		return result;
	}
	inline self_type operator-(const self_type& added) const
	{
		self_type result = *this; // initialize world as parent
			
		// rotate the local position according to the parent world orientation
		result.position -= added.position;
		result.orientation = result.orientation * added.orientation.inverse();
		result.scale -= added.scale;
		return result;
	}
		
	inline vector3_type operator*(const vector3_type& vec) const
	{        
		// rotate the local position according to the parent world orientation
		vector3_type result = vec;
		result *= scale;
		result = orientation.rotate(result);
		result += position;
		return result;
	}
		
	matrix4x4_type toMatrix() const
	{
		return matrix4x4_type(position, scale, orientation);
    }

    void toMatrix(matrix4x4_type& out) const
    {
        out = matrix4x4_type(position, scale, orientation);
    }
		
	inline void interpolate(const self_type& dest, t_Ty coef)
	{
		*this = interpolated(dest, coef);
	}
		
	self_type slerpInterpolated(const self_type& dest, const vector3_type& rotationPoint, const vector3_type& up, t_Ty coef) const
	{
		self_type newTransform = *this;
		newTransform.position = newTransform.position + (dest.position - position)*coef;
		vector3_type s0 = position - rotationPoint;
		float len0 = s0.normalize();
		vector3_type s1 = dest.position - rotationPoint;
		float len1 = s1.normalize();
		float len = len0 + (len1-len0)*coef;
		float angle = s0.positiveAngleTo(s1, up);
		vector3_type rotationAxis = s0.cross(s1);
		quaternion_type rot(rotationAxis.normalized(), angle*coef);
		newTransform.position = rot.rotate(s0)*len + rotationPoint;
		newTransform.orientation = newTransform.orientation.nlerp(coef, orientation, dest.orientation, true);
		newTransform.scale = newTransform.scale + (dest.scale - scale) * coef;
		return newTransform;
	}
		
	self_type interpolated(const self_type& dest, t_Ty coef, bool slerp = true) const
	{
		self_type newTransform = *this;
		newTransform.position = newTransform.position + (dest.position - position)*coef;
		if(slerp)
			newTransform.orientation = newTransform.orientation.slerp(coef, orientation, dest.orientation);
		else
			newTransform.orientation = newTransform.orientation.nlerp(coef, orientation, dest.orientation, true);
			
		newTransform.scale = newTransform.scale + (dest.scale - scale) * coef;
		return newTransform;
	}
		
		
	void lookAt( const vector3_type& eye, const vector3_type& target, const vector3_type& up = vector3_type::UNIT_Y )
	{
		vector3_type zaxis = eye-target;    // The "look-at" vector.
		zaxis.normalize();
		vector3_type xaxis = up.cross(zaxis);// The "right" vector.
		xaxis.normalize();
		vector3_type yaxis = zaxis.cross(xaxis);     // The "up" vector.
			
		orientation.fromAxes(xaxis, yaxis, zaxis);
		position = eye;
	}
		
	void setDirection(const vector3_type& dir, const vector3_type& up = vector3_type::UNIT_Y)
	{
		lookAt(position, position+dir, up);
	}
		
	vector3_type getDirection() const
	{
		matrix3x3_type rot;
		orientation.toRotationmatrix(rot);
		return -rot[2];
	}
		
	vector3_type getRight() const
	{
		matrix3x3_type rot;
		orientation.toRotationmatrix(rot);
		return rot[0];
	}
		
	vector3_type getUp() const
	{
		matrix3x3_type rot;
		orientation.toRotationmatrix(rot);
		return rot[1];
	}
		
	bool operator==(const self_type& t) const
	{
		return position == t.position && orientation == t.orientation && scale == t.scale;
	}
		
	bool operator!=(const self_type& t) const
	{
		return !operator==(t);
	}
		
	self_type inverse() const 
	{
		return self_type(-position, orientation.inverse(), vector3_type(1/scale.x, 1/scale.y, 1/scale.z));
	}
		
public:
	vector3_type     position;
	quaternion_type  orientation;
	vector3_type     scale;
};
	
typedef transform3<float32> transform3f;
typedef transform3<float64> transform3d;

o_namespace_end(phantom, math)

#endif // o_math_transform3_h
