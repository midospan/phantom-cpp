#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

/// std::_Uset_traits
o_classNTB((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits, (_Container_base))(
);

/// std::set
o_classNTB((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set, (_Tree<_Tset_traits<t_Ty, t_Pr, t_Alloc, false> >)) (
);


/// std::_Tset_traits
o_classNTB((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits, (_Container_base)) (
);


/// std::multiset
o_classNTB((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset, (_Tree<_Tset_traits<t_Kty, t_Pr, t_Alloc, true> >)) (
);

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)

/// std::set
o_classNT((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set) (
    );

/// std::multiset
o_classNT((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset)(
    );

#else
#   error std::set/multiset reflection is not declared for this compiler
#endif
