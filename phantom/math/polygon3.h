#if !defined(_polygon3_h_)
#define _polygon3_h_

#include <vector>
#include "vector3.h"

o_namespace_begin(phantom, math)

template<class t_Ty, class Alloc = std::allocator<vector3<t_Ty> > >
class polygon3 : public std::vector<vector3<t_Ty> >
{
public:
    typedef vector2<t_Ty> value_type;
    typedef t_Ty float_type;
    typedef typename make_float<t_Ty>::type friendType;
		
	inline explicit polygon3 (const typename std::vector<vector3<t_Ty> >::allocator_type& alloc
								= Alloc())
	:	std::vector<vector3<t_Ty> >(alloc)
	{}
		
	inline explicit polygon3 (typename std::vector<vector3<t_Ty> >::size_type n,
								const typename std::vector<vector3<t_Ty> >::value_type& val = vector3<t_Ty>(),
								const typename std::vector<vector3<t_Ty> >::allocator_type& alloc =
								Alloc())
	:	std::vector<vector3<t_Ty> >(n, val, alloc)
	{}
		
	template<class Iterator>
	inline polygon3 (Iterator first, Iterator last,
						const typename std::vector<vector3<t_Ty> >::allocator_type& alloc
						= std::vector<vector3<t_Ty> >::allocator_type())
	:	std::vector<t_Ty>(first, last, alloc)
	{}
		
	inline polygon3 (const polygon3& p)
	:	std::vector<vector3<t_Ty> >(p)
	{}
		
	inline polygon3 (const std::vector<vector3<t_Ty> >& p)
	:	std::vector<vector3<t_Ty> >(p)
	{}
		
	inline polygon3 (const polygon3<friendType> p)
	{
		for (auto it = p.begin(); it != p.end(); ++it)
		{
			this->push_back(vector3<t_Ty>(*it));
		}
	}
};
	
typedef polygon3<float32> polygon3f;
typedef polygon3<float64> polygon3d;

o_namespace_end(phantom, math)

#endif // _Polygon_h_