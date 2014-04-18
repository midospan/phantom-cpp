#pragma once

#include "phantom/phantom.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Hash_compare
o_classNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare){ o_reflection {}; };
o_exposeNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare)


// _Hash
o_classNTS((std), (typename), (t_Traits), _Hash, (t_Traits)){o_reflection {};};
o_exposeNT((std), (typename), (t_Traits), _Hash);


/// VECTOR

/// LIST

/// MISC


// binary_function
o_classNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function){o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function);

// unary_function
o_classNT((std), (typename, typename), (t_Arg, t_Result), unary_function){o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Arg, t_Result), unary_function);

// less
o_classNTS((std), (typename), (t_Ty), less, (binary_function<t_Ty, t_Ty, bool>)){o_reflection {};};
o_exposeNT((std), (typename), (t_Ty), less);

// hash
o_classNTS((std), (typename), (_Kty), hash, (unary_function<_Kty, size_t>)){o_reflection {};};
o_exposeNT((std), (typename), (_Kty), hash);

// equal_to
o_classNTS((std), (typename), (t_Ty), equal_to, (binary_function<t_Ty,t_Ty,bool>)){o_reflection {};};
o_exposeNT((std), (typename), (t_Ty), equal_to);

// reverse_iterator
o_classNT((std), (typename), (t_RanIt), reverse_iterator){o_reflection {};};
o_exposeNT((std), (typename), (t_RanIt), reverse_iterator);

o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (t_RanIt), reverse_iterator);

// _Tree
o_classNTS((std), (typename), (t_Traits), _Tree, (_Tree_val<t_Traits>)){o_reflection{};};
o_exposeNT((std), (typename), (t_Traits), _Tree);

// _Tree_nod
o_classNTS((std), (typename), (t_Traits), _Tree_nod, (t_Traits)){o_reflection {};};
o_exposeNT((std), (typename), (t_Traits), _Tree_nod);

// _Tree_val
o_classNTS((std), (typename), (t_Traits), _Tree_val, (_Tree_nod<t_Traits>)){o_reflection{};};
o_exposeNT((std), (typename), (t_Traits), _Tree_val);

// _Tree_const_iterator
o_classNT((std), (typename), (_Ty), _Tree_const_iterator){o_reflection{};};
o_exposeNT((std), (typename), (_Ty), _Tree_const_iterator);

// _Tree_iterator
o_classNTS((std), (typename), (_Ty), _Tree_iterator, (_Tree_const_iterator<_Ty>)){o_reflection{};};
o_exposeNT((std), (typename), (_Ty), _Tree_iterator);


#endif // VISUAL_STUDIO STL

// Phantom std specialization
/*

o_classNS((phantom, reflection), MapValueIterator, (Iterator))
{
    o_reflection {};
};
o_exposeN((phantom,reflection), MapValueIterator);*/

