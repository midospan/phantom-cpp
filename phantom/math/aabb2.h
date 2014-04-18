#ifndef o_math_aabb2_h__
#define o_math_aabb2_h__

#include "vector2.h"
#include "transform2.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), aabb2);

o_namespace_begin(phantom, math)

/// An axis aligned bounding box.
template<typename t_Ty>
class aabb2
{
public:
    typedef aabb2<t_Ty> self_type;
    typedef vector2<t_Ty> vector2_type;

    // default constructor : build a null aabb (reverted)
    inline aabb2()
        : min(std::numeric_limits<t_Ty>::max(), std::numeric_limits<t_Ty>::max())
        , max(std::numeric_limits<t_Ty>::lowest(), std::numeric_limits<t_Ty>::lowest()) {}

    inline aabb2(t_Ty minx, t_Ty miny, t_Ty maxx, t_Ty maxy)
        : min(minx, miny)
        , max(maxx, maxy) {}

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

    const static self_type NULL_BOUNDS;

    /// Verify that the bounds are sorted.
    bool isValid() const;

    o_forceinline bool isZero() const { return min.isZero() AND max.isZero(); }
    o_forceinline bool isPoint() const { return min == max; }
    o_forceinline bool isNull() const { return *this == NULL_BOUNDS; }

    /// Get the center of the AABB.
    vector2_type getCenter() const
    {
        return (min + max) * 0.5f;
    }

    /// Get the extents of the AABB (half-widths).
    vector2_type getExtents() const
    {
        return (max - min) * 0.5f;
    }

    t_Ty getWidth() const { return max.x-min.x; }
    t_Ty getHeight() const { return max.y-min.y; }

    /// Get the perimeter length
    t_Ty getPerimeter() const
    {
        t_Ty wx = max.x - min.x;
        t_Ty wy = max.y - min.y;
        return (wx + wy) * 2.f;
    }

    /// Combine an AABB into this one.
    inline void combine(const self_type& aabb)
    {
        // If null, directly set as the given aabb
        if(aabb.isNull()) return;
        if(isNull())
        {
            min = aabb.min;
            max = aabb.max;
        }
        else
        {
            min = math::min(min, aabb.min);
            max = math::max(max, aabb.max);
        }
    }

    /// Combine two AABBs into this one.
    void combineNoNull(const self_type& a1, const self_type& a2)
    {
        min = math::min(a1.min, a2.min);
        max = math::max(a1.max, a2.max);
    }

    void combineNoNull(const self_type& other)
    {
        min = math::min(min, other.min);
        max = math::max(max, other.max);
    }

    /// Does this aabb contain the given AABB.
    bool contains(const self_type& aabb) const
    {
        return (min.x <= aabb.min.x)
        AND (min.y <= aabb.min.y)
        AND (aabb.max.x <= max.x)
        AND (aabb.max.y <= max.y);
    }

    /// Does this aabb contain the given point.
    bool contains(const vector2_type& point) const
    {
        return  (point.x <= max.x) 
            AND (point.x >= min.x)
            AND (point.y <= max.y)
            AND (point.y >= min.y);
    }

    bool overlaps(const self_type& o) const
    {
        vector2_type d1, d2;
        d1 = o.min - max;
        d2 = min - o.max;

        return NOT((d1.x > 0.f) OR (d1.y > 0.f) OR (d2.x > 0.0f) OR (d2.y > 0.0f));
    }

    self_type transformed(const transform2<t_Ty>& t, bool rotation = true) const 
    { 
        self_type transformedAABB;

        // We rotate first the bounds
        if(rotation)
        {
            vector2_type center = (max+min)*0.5f;
            vector2_type diagonalTop = max-center;
            vector2_type diagonalTopRotated(diagonalTop.x*t.orientation.c - diagonalTop.y*t.orientation.s, diagonalTop.x*t.orientation.s + diagonalTop.y*t.orientation.c); 
            vector2_type diagonalBottomRotated(diagonalTop.x*t.orientation.c + diagonalTop.y*t.orientation.s, diagonalTop.x*t.orientation.s - diagonalTop.y*t.orientation.c); 
            t_Ty maxX = math::max(math::abs(diagonalTopRotated.x), math::abs(diagonalBottomRotated.x));
            t_Ty maxY = math::max(math::abs(diagonalTopRotated.y), math::abs(diagonalBottomRotated.y));
            transformedAABB.min.set(center.x-maxX, center.y-maxY);
            transformedAABB.max.set(center.x+maxX, center.y+maxY);
        }
		else
		{
			transformedAABB.min = min;
			transformedAABB.max = max;
		}

        transformedAABB.min.x *= t.scale.x;
        transformedAABB.min.y *= t.scale.y;
        transformedAABB.max.x *= t.scale.x;
        transformedAABB.max.y *= t.scale.y;

        transformedAABB.min += t.position;
        transformedAABB.max += t.position;

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
                if ( (p[i] < min[i]) OR (max[i] < p[i]) )
                {
                    return false;
                }
            }
            else
            {
                t_Ty inv_d = 1.0f / d[i];
                t_Ty t1 = (min[i] - p[i]) * inv_d;
                t_Ty t2 = (max[i] - p[i]) * inv_d;

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
        return (other.min == min) AND (other.max == max);
    }

    bool operator!=(const self_type& other) const 
    {
        return (other.min != min) OR (other.max != max);
    }

    vector2_type min;	///< the lower vertex
    vector2_type max;	///< the upper vertex
};

template<typename t_Ty>
inline bool aabb2<t_Ty>::isValid() const
{
    vector2_type d = max - min;
    bool valid = d.x >= 0.0f && d.y >= 0.0f;
    valid = valid && min.isValid() AND max.isValid();
    return valid;
}

o_namespace_end(phantom, math)

#endif // aabb2_h__
