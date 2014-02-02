#pragma once
#include "map.hxx"

// unordered_map
#if o_HAS_CPP0X
o_classNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);
#else
o_classNT((std, tr1), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map){o_reflection {};};
o_exposeNT((std, tr1), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);
#endif

#if o_HAS_CPP0X
o_classNTS((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>)){o_reflection {};};
#else
o_classNTS((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::tr1::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>)){o_reflection {};};
#endif
o_exposeNT((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map);