template<class t_Ty>
inline line3<t_Ty>::line3(const vector3<t_Ty>& p, const vector3<t_Ty>& dir)
{
    o_assert( equals(dir.lengthSquared(), (t_Ty)1.0, (t_Ty)0.001) );
	direction = dir;
	point = p;
}

template<class t_Ty>
inline line3<t_Ty>& line3<t_Ty>::operator=(const line3<t_Ty>& l)
{
	direction = l.direction;
	point = l.point;
	return *this;
}

template<class t_Ty>
inline bool line3<t_Ty>::operator==(const line3<t_Ty>& l) const
{
	return direction == l.direction && point == l.point;
}

template<class t_Ty>
inline bool line3<t_Ty>::operator!=(const line3<t_Ty>& l) const
{
	return !(*this == l);
}

template<class t_Ty>
inline bool line3<t_Ty>::absoluteEqual(const line3<t_Ty>& l) const
{
	return contains(l.point) && direction.isCollinearTo(l.direction);
}

template<class t_Ty>
inline bool line3<t_Ty>::contains(const vector3<t_Ty>& p) const
{
	vector3<t_Ty> pPoint = p - point;
	pPoint.normalize();
	return (pPoint.normalized().dot(direction) - 1) <= EPSILON;
}

template<class t_Ty>
inline bool line3<t_Ty>::isCoplanarTo(const line3<t_Ty>& l) const
{
	return fabs(direction.dot(l.direction.cross(point - l.point))) < EPSILON;
}

template<class t_Ty>
inline bool line3<t_Ty>::intersects(const line3<t_Ty>& l, vector3<t_Ty>& intersectionPoint) const
{
	if (!isCoplanarTo(l) || direction.isCollinearTo(l.direction))
		return false;
	// Switch coordinate system
	vector3<t_Ty> v = direction.normalized();
	vector3<t_Ty> n = v.cross(l.direction).normalized();
	vector3<t_Ty> w = n.cross(direction).normalized();
	matrix3x3<t_Ty> changeBasis(v.x, v.y, v.z,
			w.x, w.y, w.z,
			n.x, n.y, n.z);
	vector3<t_Ty> newDirection = changeBasis * direction;
	vector3<t_Ty> newPoint = changeBasis * point;
	line3<t_Ty> newL(changeBasis*l.point, changeBasis*l.direction);
	line2<t_Ty> thisline2f(vector2<t_Ty>(newPoint.x, newPoint.y),
			vector2<t_Ty>(newDirection.x, newDirection.y));
	line2<t_Ty> newline2f(vector2<t_Ty>(newL.point.x, newL.point.y),
			vector2<t_Ty>(newL.direction.x, newL.direction.y));
	vector2<t_Ty> intersectionPoint2;
	if (thisline2f.intersects(newline2f, &intersectionPoint2))
	{
		intersectionPoint = vector3<t_Ty>(intersectionPoint2.x, intersectionPoint2.y,
				newPoint.z);
		changeBasis.transpose();
		intersectionPoint = changeBasis * intersectionPoint;
		return true;
	}
	return false;
}

template<class t_Ty>
inline bool line3<t_Ty>::intersects(const aabb3<t_Ty>& aabb, vector3<t_Ty>& intersectionPoint) const
{
            
#define NUMDIM	3
#define RIGHT	0
#define LEFT	1
#define MIDDLE	2
	bool inside = true;
	char quadrant[NUMDIM];
	register int i;
	int whichPlane;
	vector3<t_Ty> maxT;
	vector3<t_Ty> candidatePlane;

	/* Find candidate planes; this loop can be avoided if
   	rays cast all from the eye(assume perpsective view) */
	for (i=0; i < NUMDIM; i++)
    {
        if(point[i] < aabb.mMin[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = aabb.mMin[i];
            inside = false;
        }
        else if (point[i] > aabb.mMax[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = aabb.mMax[i];
            inside = false;
        }
        else	{
            quadrant[i] = MIDDLE;
        }
    }

	/* Ray origin inside bounding box */
	if(inside)	{
		intersectionPoint = point;
		return true;
	}


	/* Calculate t_Ty distances to candidate planes */
	for (i = 0; i < NUMDIM; i++)
    {
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-point[i]) / direction[i];
        else
            maxT[i] = -1.;
    }

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	for (i = 1; i < NUMDIM; i++)
    {
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;
    }

	/* Check final candidate actually inside box */
	if (maxT[whichPlane] < 0.) return false;
	for (i = 0; i < NUMDIM; i++)
    {
        if (whichPlane != i) {
            intersectionPoint[i] = point[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < aabb.mMin[i] || intersectionPoint[i] > aabb.mMax[i])
                return false;
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    }
    return true;				/* ray hits box */
#undef NUMDIM	
#undef RIGHT	
#undef LEFT	    
#undef MIDDLE	
}
