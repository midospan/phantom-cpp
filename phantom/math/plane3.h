#ifndef o_math_plane3
#define o_math_plane3

#include "vector3.h"
#include "line3.h"

o_declareNT(class, (phantom, math), (typename), (t_Ty), plane3);

o_namespace_begin(phantom, math)

template<class t_Ty>
class plane3
{
public:
    typedef plane3<t_Ty> self_type;
    typedef vector3<t_Ty> vector3_type;

    /** Default constructor - sets everything to 0.
        */
    plane3 ();
    plane3 (const self_type& rhs);
    /** Construct a plane through a normal, and a distance to move the plane along the normal.*/
    plane3 (const vector3_type& rkNormal, t_Ty fConstant);
	/** Construct a plane using the 4 constants directly **/
	plane3 (t_Ty a, t_Ty b, t_Ty c, t_Ty d);
    plane3 (const vector3_type& rkNormal, const vector3_type& rkPoint);
    plane3 (const vector3_type& rkPoint0, const vector3_type& rkPoint1,
            const vector3_type& rkPoint2);
        
    /** The "positive side" of the plane is the half space to which the
        plane normal points. The "negative side" is the other half
        space. The flag "no side" indicates the plane itself.
        */
    enum ESide
    {
        eSideNone,
        eSidePositive,
        eSideNegative,
        eSideBoth
    };
        
    ESide side (const vector3_type& rkPoint) const;
        
    /**
        Returns the side where the alignedBox is. The flag BOTH_SIDE indicates an intersecting box.
        One corner ON the plane is sufficient to consider the box and the plane intersecting.
        */
    ESide side (const aabb3<t_Ty>& rkBox) const;
        
    /** Returns which side of the plane that the given box lies on.
        The box is defined as centre/half-size pairs for effectively.
        @param centre The centre of the box.
        @param halfSize The half-size of the box.
        @return
        POSITIVE_SIDE if the box complete lies on the "positive side" of the plane,
        NEGATIVE_SIDE if the box complete lies on the "negative side" of the plane,
        and BOTH_SIDE if the box intersects the plane.
        */
    ESide side (const vector3_type& centre, const vector3_type& halfSize) const;
        
    /** This is a pseudodistance. The sign of the return value is
        positive if the point is on the positive side of the plane,
        negative if the point is on the negative side, and zero if the
        point is on the plane.
        @par
        The absolute value of the return value is the true distance only
        when the plane normal is a unit length vector.
        */
    t_Ty distance (const vector3_type& rkPoint) const;
        
    /** Redefine this plane based on 3 points. */
    void redefine(const vector3_type& rkPoint0, const vector3_type& rkPoint1,
                    const vector3_type& rkPoint2);
        
	/** Redefine this plane based on a normal and a point. */
	void redefine(const vector3_type& rkNormal, const vector3_type& rkPoint);
        
	/** Project a vector onto the plane. 
        @remarks This gives you the element of the input vector that is perpendicular 
        to the normal of the plane. You can get the element which is parallel
        to the normal of the plane by subtracting the result of this method
        from the original vector, since parallel + perpendicular = original.
        @param v The input vector
        */
	vector3_type projectVector(const vector3_type& v) const;
        
    /** Normalises the plane.
        @remarks
        This method normalises the plane's normal and the length scale of d
        is as well.
        @note
        This function will not crash for zero-sized vectors, but there
        will be no changes made to their components.
        @return The previous length of the plane's normal.
        */
    t_Ty normalise(void);
		
	bool intersects(const line3<t_Ty>& l, vector3_type& intersectionPoint) const;
        
	vector3_type normal;
    t_Ty d;
        
    /// Comparison operator
    bool operator==(const plane3& rhs) const
    {
        return (rhs.d == d && rhs.normal == normal);
    }

    bool operator!=(const plane3& rhs) const
    {
        return (rhs.d != d || rhs.normal != normal);
    }

    t_Ty intersectionParameter(const line3<t_Ty>& l) const;
};
	
typedef plane3<float32> plane3f;
typedef plane3<float64> plane3d;
	
#include "plane3.inl"
    
o_namespace_end(phantom, end)

#endif
