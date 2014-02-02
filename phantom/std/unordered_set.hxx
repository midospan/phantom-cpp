#pragma once

#include "set.hxx"

// unordered_set
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set, (_Hash<tr1::_Uset_traits<t_Kty,_Hash_compare<t_Kty, t_Hash, t_Keyeq>, t_Alloc, false> >)){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set);