#pragma once

#include "utility.hxx"
// _List_val
o_classNT((std), (typename, typename), (_Ty, _Alloc), _List_val) {o_reflection {};};
o_exposeNT((std), (typename, typename), (_Ty, _Alloc), _List_val);

// _List_const_iterator
o_classNT((std), (typename), (_Ty), _List_const_iterator){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _List_const_iterator);

o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (_Ty), _List_const_iterator);

// _List_iterator
o_classNTS((std), (typename), (_Ty), _List_iterator, (_List_const_iterator<_Ty>)){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _List_iterator);

o_traits_specializeNT(has_has_something, (static const bool value = false;), (std), (typename), (_Ty), _List_iterator);

// list
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), list, (_List_val<t_Ty, t_Alloc>))
{
    o_reflection 
    {
        o_typedef(iterator);
        o_typedef(const_iterator);
        o_typedef(reverse_iterator);
        o_typedef(const_reverse_iterator);
    };
};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), list);

o_classNTS((phantom), (typename), (t_Ty), list, (std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), list);