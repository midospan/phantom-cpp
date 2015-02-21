#ifndef o_std_set_h__
#define o_std_set_h__

#include <set>

#include "utility.h"


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _Uset_traits
o_declareNT(class, (std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits);
// _Tset_traits
o_declareNT(class, (std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits);

#endif

/// UNORDERED MAP
// set
o_declareNT(class, (std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set);
// multiset
o_declareNT(class, (std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset);

#endif // o_std_set_h__