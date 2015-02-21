#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

/// std::_List_val
o_classNT((std), (typename, typename), (_Ty, _Alloc), _List_val)
(
);

/// std::_List_const_iterator
o_classNT((std), (typename), (_Ty), _List_const_iterator)(
);

o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (_Ty), _List_const_iterator);

/// std::_List_iterator
o_classNTB((std), (typename), (_Ty), _List_iterator, (_List_const_iterator<_Ty>))(
);

o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (_Ty), _List_iterator);

/// std::list
o_classNTB((std), (typename, typename), (t_Ty, t_Alloc), list, (_List_val<t_Ty, t_Alloc>))
(
o_public:
    o_nested_typedef(iterator);
    o_nested_typedef(const_iterator);
    o_nested_typedef(reverse_iterator);
    o_nested_typedef(const_reverse_iterator);
    o_nested_typedef(reference);
    o_nested_typedef(const_reference);
    o_nested_typedef(pointer);
    o_nested_typedef(const_pointer);
    o_nested_typedef(size_type);
    o_member_function(size_type, size, ());
    o_member_function(bool, empty, ());
    o_member_function(void, push_front, (const_reference));
    o_member_function(void, push_back, (const_reference));
);

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)

/// std::list
o_classNT((std), (typename, typename), (t_Ty, t_Alloc), list)
(
o_public:
    o_nested_typedef(iterator);
    o_nested_typedef(const_iterator);
    o_nested_typedef(reverse_iterator);
    o_nested_typedef(const_reverse_iterator);
    o_nested_typedef(reference);
    o_nested_typedef(const_reference);
    o_nested_typedef(pointer);
    o_nested_typedef(const_pointer);
    o_nested_typedef(size_type);
    o_member_function(size_type, size, ());
    o_member_function(bool, empty, ());
    o_member_function(void, push_front, (const_reference));
    o_member_function(void, push_back, (const_reference));
);

#else
#   error std::list reflection is not declared for this compiler
#endif

