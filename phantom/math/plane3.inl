//
//  plane3.cpp
//  Math
//
//  Created by Vivien on 09/07/12.
//  Copyright (c) 2012 MyCompanyName__. All rights reserved.
//

//-----------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 ()
{
	normal = vector3<t_Ty>::ZERO;
	d = (t_Ty)0.0;
}
//-----------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 (const plane3<t_Ty>& rhs)
{
	normal = rhs.normal;
	d = rhs.d;
}
//-----------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 (const vector3<t_Ty>& rkNormal, t_Ty fConstant)
{
	normal = rkNormal;
	d = -fConstant;
}
//---------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 (t_Ty a, t_Ty b, t_Ty c, t_Ty _d)
: normal(a, b, c), d(_d)
{
}
//-----------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 (const vector3<t_Ty>& rkNormal, const vector3<t_Ty>& rkPoint)
{
	redefine(rkNormal, rkPoint);
}
//-----------------------------------------------------------------------
template<class t_Ty>
plane3<t_Ty>::plane3 (const vector3<t_Ty>& rkPoint0, const vector3<t_Ty>& rkPoint1,
				 const vector3<t_Ty>& rkPoint2)
{
	redefine(rkPoint0, rkPoint1, rkPoint2);
}
//-----------------------------------------------------------------------
template<class t_Ty>
t_Ty plane3<t_Ty>::distance (const vector3<t_Ty>& rkPoint) const
{
	return normal.dot(rkPoint) + d;
}
//-----------------------------------------------------------------------
template<class t_Ty>
typename plane3<t_Ty>::ESide plane3<t_Ty>::side (const vector3<t_Ty>& rkPoint) const
{
	t_Ty fDistance = distance(rkPoint);
	
	if ( fDistance < (t_Ty)0.0 )
		return eSideNegative;
	
	if ( fDistance > (t_Ty)0.0 )
		return eSidePositive;
	
	return eSideNone;
}


//-----------------------------------------------------------------------
template<class t_Ty>
typename plane3<t_Ty>::ESide plane3<t_Ty>::side (const aabb3<t_Ty>& box) const
{
	if (box.isNull()) 
		return eSideNone;
	if (box.isInfinite())
		return eSideBoth;
	
	return side(box.center(), box.halfSize());
}
//-----------------------------------------------------------------------
template<class t_Ty>
typename plane3<t_Ty>::ESide plane3<t_Ty>::side (const vector3<t_Ty>& centre, const vector3<t_Ty>& halfSize) const
{
	// Calculate the distance between box centre and the plane
	t_Ty dist = distance(centre);
	
	// Calculate the maximise allows absolute distance for
	// the distance between box centre and plane
	t_Ty maxAbsDist = normal.absDot(halfSize);
	
	if (dist < -maxAbsDist)
		return plane3<t_Ty>::eSideNegative;
	
	if (dist > +maxAbsDist)
		return plane3<t_Ty>::eSidePositive;
	
	return plane3<t_Ty>::eSideBoth;
}
//-----------------------------------------------------------------------
template<class t_Ty>
void plane3<t_Ty>::redefine(const vector3<t_Ty>& rkPoint0, const vector3<t_Ty>& rkPoint1,
						const vector3<t_Ty>& rkPoint2)
{
	vector3<t_Ty> kEdge1 = rkPoint1 - rkPoint0;
	vector3<t_Ty> kEdge2 = rkPoint2 - rkPoint0;
	normal = kEdge1.cross(kEdge2);
	normal.normalize();
	d = -normal.dot(rkPoint0);
}
//-----------------------------------------------------------------------
template<class t_Ty>
void plane3<t_Ty>::redefine(const vector3<t_Ty>& rkNormal, const vector3<t_Ty>& rkPoint)
{
	normal = rkNormal;
	d = -rkNormal.dot(rkPoint);
}
//-----------------------------------------------------------------------
template<class t_Ty>
vector3<t_Ty> plane3<t_Ty>::projectVector(const vector3<t_Ty>& p) const
{
	// We know plane normal is unit length, so use simple method
	matrix3x3<t_Ty> xform;
	xform[0][0] = (t_Ty)1.0 - normal.x * normal.x;
	xform[1][0] = -normal.x * normal.y;
	xform[2][0] = -normal.x * normal.z;
	xform[0][1] = -normal.y * normal.x;
	xform[1][1] = (t_Ty)1.0 - normal.y * normal.y;
	xform[2][1] = -normal.y * normal.z;
	xform[0][2] = -normal.z * normal.x;
	xform[1][2] = -normal.z * normal.y;
	xform[2][2] = (t_Ty)1.0 - normal.z * normal.z;
	return xform * p;
	
}
//-----------------------------------------------------------------------
template<class t_Ty>
t_Ty plane3<t_Ty>::normalise(void)
{
	t_Ty fLength = normal.length();
	
	if ( fLength > t_Ty(0.0) )
	{
		t_Ty fInvLength = (t_Ty)1.0 / fLength;
		normal *= fInvLength;
		d *= fInvLength;
	}
	
	return fLength;
}

template<class t_Ty>
bool plane3<t_Ty>::intersects(const line3<t_Ty>& l, vector3<t_Ty>& intersectionPoint) const
{
	t_Ty dotProd = l.direction.normalized().dot(normal.normalized());
	if (fabs(dotProd) <= std::numeric_limits<t_Ty>::epsilon())
		return false;
	vector3<t_Ty> planePt = -d * normal.normalized();
	t_Ty param = (planePt - l.point).dot(normal.normalized()) / (dotProd);
	intersectionPoint = param*l.direction.normalized() + l.point;
	return true;
}

template<class t_Ty>
t_Ty plane3<t_Ty>::intersectionParameter(const line3<t_Ty>& l) const
{
	t_Ty dotProd = l.direction.normalized().dot(normal.normalized());
	if (fabs(dotProd) <= std::numeric_limits<t_Ty>::epsilon())
		return std::numeric_limits<t_Ty>::max();
	vector3<t_Ty> planePt = -d * normal.normalized();
	return (planePt - l.point).dot(normal.normalized()) / (dotProd);
}