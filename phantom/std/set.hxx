#pragma once

#include "utility.hxx"

// _Uset_traits
o_classNTS((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits, (_Container_base)){o_reflection{};};
o_exposeNT((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits);
// set
o_classNTS((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set, (_Tree<_Tset_traits<t_Ty, t_Pr, t_Alloc, false>>)) {o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set);

// _Tset_traits
o_classNTS((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits, (_Container_base)) {o_reflection{};};
o_exposeNT((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits);

// multiset
o_classNTS((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset, (_Tree<_Tset_traits<t_Kty, t_Pr, t_Alloc, true>>)) {o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset);