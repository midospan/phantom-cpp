#ifndef o_phantom_math_polygon2_h__
#define o_phantom_math_polygon2_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, math)

template<typename t_Ty, size_t t_PointCount>
struct polygon2
{
    o_static_assert(t_PointCount >= 3);

    typedef vector2<t_Ty> vector2_type;

    static const size_t count = t_PointCount;

	polygon2(void)  {}
	~polygon2(void) {}

    o_forceinline boolean isNull() const 
    {
        size_t i = 1;
        for(;i<t_PointCount;++i)
        {
            if(points[0] != points[i]) return false;
        }
        return true;
    }

    o_forceinline boolean isZero() const 
    {
        size_t i = 0;
        for(;i<t_PointCount;++i)
        {
            if(points[i] != vector2_type::Zero()) return false;
        }
        return true;
    }

    vector2_type    points[t_PointCount];
};

o_namespace_end(phantom, math)

o_classNT((phantom, celsius), (typename, size_t), (t_Ty, t_PointCount), polygon2)
{
	o_reflection
	{
		o_data_member(vector2_type[t_PointCount], points, o_public);
	};
};
o_exposeN((phantom, celsius), polygon2);

#endif
