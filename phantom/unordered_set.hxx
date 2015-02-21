#pragma once

#include "std/unordered_set.hxx"

/// unordered_set
#if o_HAS_CPP0X
o_classNTB((phantom), (typename, typename, typename), (t_Kty, t_Hash, t_Keyeq), unordered_set, (std::unordered_set<t_Kty, t_Hash, t_Keyeq, o__t1_class__partioned_memory_allocator(t_Kty)>))(
    );
#else
o_classNTB((phantom), (typename, typename, typename), (t_Kty, t_Hash, t_Keyeq), unordered_set, (std::tr1::unordered_set<t_Kty, t_Hash, t_Keyeq, o__t1_class__partioned_memory_allocator(t_Kty)>))(
    );
#endif

