#pragma once
#include "map.hxx"

/// std::unordered_map
#if o_HAS_CPP0X
o_classNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map)(
        );

#else
o_classNT((std, tr1), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map)(
        );

#endif
