#ifndef o_phantom_math_triangle2_h__
#define o_phantom_math_triangle2_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, math)

template<typename t_Ty>
class triangle2 : public polygon2<t_Ty, 3>
{
public:
	triangle2(void) {}
	~triangle2(void) {}
    
protected:
};

o_namespace_end(phantom, math)

o_classN((phantom, math), triangle2)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, math), triangle2);

#endif
