#pragma once

#include "set.hxx"


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

/// unordered_set
o_classNTB((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set, (_Hash<tr1::_Uset_traits<t_Kty,_Hash_compare<t_Kty, t_Hash, t_Keyeq>, t_Alloc, false> >))(
);

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)

/// unordered_set
o_classNT((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set)(
);

#else
#   error std::unordered_set reflection is not declared for this compiler
#endif
