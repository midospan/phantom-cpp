#ifndef o_std_map_h__
#define o_std_map_h__

#include <map>

#include "utility.h"

/// MAP
// _Tmap_traits
o_declareNT(class, (std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits);
// _Umap_traits
o_declareNT(class, (std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);
// _Hash
o_declareNT(class, (std), (typename), (t_Traits), _Hash);
// map
o_declareNT(class, (std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map);
// multimap
o_declareNT(class, (std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap);

o_declareNT(class, (phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map);

#endif // vector_h__