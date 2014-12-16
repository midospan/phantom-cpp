#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

/// std::_String_const_iterator
o_classNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator)
(
);


/// std::_String_iterator
o_classNTB((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator, (_String_const_iterator<_Elem , _Traits , _Alloc>))
(
);

/// std::basic_string
o_classNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string)
(
o_public:
    o_nested_typedef(iterator);
    o_nested_typedef(const_iterator);
    o_nested_typedef(reverse_iterator);
    o_nested_typedef(const_reverse_iterator);
    o_nested_typedef(const_pointer);
    o_nested_typedef(size_type);
    o_nested_typedef(value_type);
    o_nested_typedef(_Myt);

    o_constructor((value_type const*));

    o_member_function(iterator, begin, ());
    o_member_function(iterator, end, ());
    o_member_function(const_iterator, begin, ());
    o_member_function(const_iterator, end, ());
    o_member_function(reverse_iterator, rbegin, ());
    o_member_function(reverse_iterator, rend, ());
    o_member_function(const_reverse_iterator, rbegin, ());
    o_member_function(const_reverse_iterator, rend, ());
    o_member_function(_Myt&, append, (const_pointer, const_pointer));
    o_member_function(_Myt&, append, (const_iterator, const_iterator));
    o_member_function(_Myt&, append, (size_type, t_Elem));
);

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)

/// std::basic_string
o_classNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string)
(
o_public:
    o_nested_typedef(iterator);
    o_nested_typedef(const_iterator);
    o_nested_typedef(reverse_iterator);
    o_nested_typedef(const_reverse_iterator);
    o_nested_typedef(const_pointer);
    o_nested_typedef(size_type);
    o_nested_typedef(value_type);

    o_constructor((value_type const*));

    o_member_function(iterator, begin, ());
    o_member_function(iterator, end, ());
    o_member_function(const_iterator, begin, ());
    o_member_function(const_iterator, end, ());
    o_member_function(reverse_iterator, rbegin, ());
    o_member_function(reverse_iterator, rend, ());
    o_member_function(const_reverse_iterator, rbegin, ());
    o_member_function(const_reverse_iterator, rend, ());
);

#else
#   error std::basic_string reflection is not declared for this compiler
#endif
