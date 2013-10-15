#ifndef aabb2_h__
#define aabb2_h__

// Adapted from Box2D b2AABB : http://www.box2D.org

o_namespace_begin(phantom, math)
    

/// An axis aligned bounding box.
template<typename t_Ty>
struct aabb2
{
    aabb2()
        : lowerBound(0,0)
        , upperBound(0,0) {}
    typedef aabb2<t_Ty> self_type;
    typedef vector2<t_Ty> vector2_type;
    /// Ray-cast input data. The ray extends from p1 to p1 + maxFraction * (p2 - p1).
    struct ray_cast_input
    {
        vector2_type   p1, p2;
        t_Ty           maxFraction;
    };

    /// Ray-cast output data. The ray hits at p1 + fraction * (p2 - p1), where p1 and p2
    /// come from RayCastInput.
    struct ray_cast_output
    {
        vector2_type   normal;
        t_Ty           fraction;
    };


    /// Verify that the bounds are sorted.
    bool isValid() const;

    o_forceinline bool isZero() const { return lowerBound.isZero() AND upperBound.isZero(); }
    o_forceinline bool isNull() const { return lowerBound == upperBound; }

    /// Get the center of the AABB.
    vector2_type getCenter() const
    {
        return (lowerBound + upperBound) * 0.5f;
    }

    /// Get the extents of the AABB (half-widths).
    vector2_type getExtents() const
    {
        return (upperBound - lowerBound) * 0.5f;
    }

    /// Get the perimeter length
    t_Ty getPerimeter() const
    {
        t_Ty wx = upperBound.x - lowerBound.x;
        t_Ty wy = upperBound.y - lowerBound.y;
        return (wx + wy) * 2.f;
    }

    /// Combine an AABB into this one.
    inline void combine(const self_type& aabb)
    {
        // If null, directly set as the given aabb
        if(isNull())
        {
            lowerBound = aabb.lowerBound;
            upperBound = aabb.upperBound;
        }
        else
        {
            lowerBound = min(lowerBound, aabb.lowerBound);
            upperBound = max(upperBound, aabb.upperBound);
        }
    }

    /// Combine two AABBs into this one.
    void combine(const self_type& a1, const self_type& a2)
    {
        lowerBound = min(a1.lowerBound, a2.lowerBound);
        upperBound = max(a1.upperBound, a2.upperBound);
    }

    /// Does this aabb contain the given AABB.
    bool contains(const self_type& aabb) const
    {

        return (lowerBound.x <= aabb.lowerBound.x)
        AND (lowerBound.y <= aabb.lowerBound.y)
        AND (aabb.upperBound.x <= upperBound.x)
        AND (aabb.upperBound.y <= upperBound.y);
    }

    /// Does this aabb contain the given point.
    bool contains(const vector2_type& point) const
    {
        return  (point.x <= upperBound.x) 
            AND (point.x >= lowerBound.x)
            AND (point.y <= upperBound.y)
            AND (point.y >= lowerBound.y);
    }

    bool overlaps(const self_type& o) const
    {

        vector2_type d1, d2;
        d1 = o.lowerBound - upperBound;
        d2 = lowerBound - o.upperBound;

        return NOT((d1.x > 0.f) OR (d1.y > 0.f) OR (d2.x > 0.0f) OR (d2.y > 0.0f));
    }

    self_type transformed(const transform2<t_Ty>& t, bool rotation = true) const 
    { 
        self_type transformedAABB;

        // We rotate first the bounds
        if(rotation)
        {
            vector2_type center = (upperBound+lowerBound)*0.5f;
            vector2_type diagonalTop = upperBound-center;
            vector2_type diagonalTopRotated(diagonalTop.x*t.orientation.c - diagonalTop.y*t.orientation.s, diagonalTop.x*t.orientation.s + diagonalTop.y*t.orientation.c); 
            vector2_type diagonalBottomRotated(diagonalTop.x*t.orientation.c + diagonalTop.y*t.orientation.s, diagonalTop.x*t.orientation.s - diagonalTop.y*t.orientation.c); 
            float maxX = math::max(math::abs(diagonalTopRotated.x), math::abs(diagonalBottomRotated.x));
            float maxY = math::max(math::abs(diagonalTopRotated.y), math::abs(diagonalBottomRotated.y));
            transformedAABB.lowerBound.set(center.x-maxX, center.y-maxY);
            transformedAABB.upperBound.set(center.x+maxX, center.y+maxY);
        }
		else
		{
			transformedAABB.lowerBound = lowerBound;
			transformedAABB.upperBound = upperBound;
		}

        transformedAABB.lowerBound.x *= t.scale.x;
        transformedAABB.lowerBound.y *= t.scale.y;
        transformedAABB.upperBound.x *= t.scale.x;
        transformedAABB.upperBound.y *= t.scale.y;

        transformedAABB.lowerBound += t.position;
        transformedAABB.upperBound += t.position;

        return transformedAABB;
    }

    bool rayCast(ray_cast_output& output, const ray_cast_input& input) const
    {
        t_Ty tmin = -std::numeric_limits<t_Ty>::max();
        t_Ty tmax = std::numeric_limits<t_Ty>::max();

        vector2_type p = input.p1;
        vector2_type d = input.p2 - input.p1;
        vector2_type absD = abs(d);

        vector2_type normal;

        for (int i = 0; i < 2; ++i)
        {
            if (absD[i] < epsilon<t_Ty>())
            {
                // Parallel.
                if ( (p[i] < lowerBound[i]) OR (upperBound[i] < p[i]) )
                {
                    return false;
                }
            }
            else
            {
                t_Ty inv_d = 1.0f / d[i];
                t_Ty t1 = (lowerBound[i] - p[i]) * inv_d;
                t_Ty t2 = (upperBound[i] - p[i]) * inv_d;

                // Sign of the normal vector.
                t_Ty s = -1.0f;

                if (t1 > t2)
                {
                    std::swap(t1, t2);
                    s = 1.0f;
                }

                // Push the min up
                if (t1 > tmin)
                {
                    normal.setZero();
                    normal[i] = s;
                    tmin = t1;
                }

                // Pull the max down
                tmax = min(tmax, t2);

                if (tmin > tmax)
                {
                    return false;
                }
            }
        }

        // Does the ray start inside the box?
        // Does the ray intersect beyond the max fraction?
        if (tmin < 0.0f OR input.maxFraction < tmin)
        {
            return false;
        }

        // Intersection.
        output.fraction = tmin;
        output.normal = normal;
        return true;
    }

    bool operator==(const self_type& other) const 
    {
        return (other.lowerBound == lowerBound) AND (other.upperBound == upperBound);
    }

    bool operator!=(const self_type& other) const 
    {
        return (other.lowerBound != lowerBound) OR (other.upperBound != upperBound);
    }

    vector2_type lowerBound;	///< the lower vertex
    vector2_type upperBound;	///< the upper vertex
};

template<typename t_Ty>
inline bool aabb2<t_Ty>::isValid() const
{
    vector2_type d = upperBound - lowerBound;
    bool valid = d.x >= 0.0f && d.y >= 0.0f;
    valid = valid && lowerBound.isValid() AND upperBound.isValid();
    return valid;
}

o_namespace_end(phantom, math)

#endif // aabb2_h__
