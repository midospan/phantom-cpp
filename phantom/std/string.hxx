#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _String_const_iterator
o_classNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator)
{
    o_reflection 
    {
    };
};
o_exposeNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_const_iterator);

// _String_iterator
o_classNTS((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator, (_String_const_iterator<_Elem , _Traits , _Alloc>))
{
    o_reflection 
    {
    };
};
o_exposeNT((std), (typename, typename, typename), (_Elem, _Traits, _Alloc), _String_iterator);

#endif

// basic_string
o_classNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string)
{
    o_reflection
    {
        o_nested_typedef(iterator);
        o_nested_typedef(const_iterator);
        o_nested_typedef(reverse_iterator);
        o_nested_typedef(const_reverse_iterator);
        o_nested_typedef(const_pointer);
        o_nested_typedef(size_type);
        o_member_function(iterator, begin, ());
        o_member_function(iterator, end, ());
        o_member_function(const_iterator, begin, ());
        o_member_function(const_iterator, end, ());
        o_member_function(reverse_iterator, rbegin, ());
        o_member_function(reverse_iterator, rend, ());
        o_member_function(const_reverse_iterator, rbegin, ());
        o_member_function(const_reverse_iterator, rend, ());
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
        o_nested_typedef(_Myt);
        o_member_function(_Myt&, append, (const_pointer, const_pointer));
        o_member_function(_Myt&, append, (const_iterator, const_iterator));
        o_member_function(_Myt&, append, (size_type, t_Elem));
#endif
    };
};
o_exposeNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);