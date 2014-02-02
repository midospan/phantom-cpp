#include "phantom/phantom.h"
#include "set.h"
#include "set.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerNT((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits);
o_registerNT((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits);

#endif

o_registerNT((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set);
o_registerNT((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset);