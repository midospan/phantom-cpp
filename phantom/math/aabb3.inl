
template<class t_Ty>
inline aabb3<t_Ty>::aabb3 ()
{
}


template<class t_Ty>
inline aabb3<t_Ty>::aabb3 (const vector3<t_Ty>& mi, const vector3<t_Ty>& ma)
    : min(mi)
    , max(ma)
{
}


template<class t_Ty>
inline aabb3<t_Ty>::~aabb3 ()
{
}


template<class t_Ty>
inline aabb3<t_Ty>::aabb3 (t_Ty xmin, t_Ty xmax, t_Ty ymin,
    t_Ty ymax, t_Ty zmin, t_Ty zmax)
{
    min[0] = xmin;
    max[0] = xmax;
    min[1] = ymin;
    max[1] = ymax;
    min[2] = zmin;
    max[2] = zmax;
}



template<class t_Ty>
inline void aabb3<t_Ty>::centerExtents (vector3<t_Ty>& center,
    t_Ty extent[3])
{
    center[0] = ((t_Ty)0.5)*(max[0] + min[0]);
    center[1] = ((t_Ty)0.5)*(max[1] + min[1]);
    center[2] = ((t_Ty)0.5)*(max[2] + min[2]);
    extent[0] = ((t_Ty)0.5)*(max[0] - min[0]);
    extent[1] = ((t_Ty)0.5)*(max[1] - min[1]);
    extent[2] = ((t_Ty)0.5)*(max[2] - min[2]);
}


template<class t_Ty>
inline bool aabb3<t_Ty>::hasXOverlap (const aabb3<t_Ty>& box) const
{
    return (max[0] >= box.min[0] && min[0] <= box.max[0]);
}


template<class t_Ty>
inline bool aabb3<t_Ty>::hasYOverlap (const aabb3<t_Ty>& box) const
{
    return (max[1] >= box.min[1] && min[1] <= box.max[1]);
}


template<class t_Ty>
inline bool aabb3<t_Ty>::hasZOverlap (const aabb3<t_Ty>& box) const
{
    return (max[2] >= box.min[2] && min[2] <= box.max[2]);
}


template<class t_Ty>
inline bool aabb3<t_Ty>::intersects (const aabb3<t_Ty>& box) const
{
    for (int i = 0; i < 3; i++)
    {
        if (max[i] < box.min[i] || min[i] > box.max[i])
        {
            return false;
        }
    }
    return true;
}


template<class t_Ty>
inline bool aabb3<t_Ty>::findIntersection(const aabb3<t_Ty>& box,
    aabb3<t_Ty>& intersection) const
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (max[i] < box.min[i] || min[i] > box.max[i])
        {
            return false;
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (max[i] <= box.max[i])
        {
            intersection.max[i] = max[i];
        }
        else
        {
            intersection.max[i] = box.max[i];
        }

        if (min[i] <= box.min[i])
        {
            intersection.min[i] = box.min[i];
        }
        else
        {
            intersection.min[i] = min[i];
        }
    }
    return true;
}

