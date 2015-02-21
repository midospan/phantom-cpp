#pragma once

#include "phantom/phantom.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Hash_compare
o_classNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare)(
        );

// _Hash
o_classNTB((std), (typename), (t_Traits), _Hash, (t_Traits))(
        );

#endif

/// VECTOR

/// LIST

/// MISC


// binary_function
o_classNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function)(
        );


// unary_function
o_classNT((std), (typename, typename), (t_Arg, t_Result), unary_function)(
        );


// less
o_classNTB((std), (typename), (t_Ty), less, (binary_function<t_Ty, t_Ty, bool>))(
        );


// hash
o_classNTB((std), (typename), (_Kty), hash, (unary_function<_Kty, size_t>))(
        );


// equal_to
o_classNTB((std), (typename), (t_Ty), equal_to, (binary_function<t_Ty,t_Ty,bool>))(
        );


// reverse_iterator
o_classNT((std), (typename), (_RanIt), reverse_iterator)(
        );


o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (_RanIt), reverse_iterator);

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

// _Tree
o_classNTB((std), (typename), (_Traits), _Tree, (_Tree_val<_Traits>))(
        );


// _Tree_nod
o_classNTB((std), (typename), (_Traits), _Tree_nod, (_Traits))
 (
o_protected:
    o_nested_begin(_Node, o_no_copy)

    o_nested_end(_Node)
    o_nested_typedef(_Node*, _Nodeptr);
    o_nested_typedef(size_type);
    o_data_member(_Nodeptr, _Myhead);	// pointer to head node
    o_data_member(size_type, _Mysize);	// number of elements
);

// _Tree_val
o_classNTB((std), (typename), (_Traits), _Tree_val, (_Tree_nod<_Traits>))
(
        );

// _Tree_const_iterator
o_classNT((std), (typename), (_Ty), _Tree_const_iterator)
(
        );

// _Tree_iterator
o_classNTB((std), (typename), (_Ty), _Tree_iterator, (_Tree_const_iterator<_Ty>))
(
        );

#endif


