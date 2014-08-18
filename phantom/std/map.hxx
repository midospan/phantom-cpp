#pragma once

#include "utility.hxx"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
// _Umap_traits
o_classNTS((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits, (_Container_base)){o_reflection {};};
o_exposeNT((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);

// _Tmap_traits
o_classNTS((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits, (_Container_base)){o_reflection {};};
o_exposeNT((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits);


// map
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map, (_Tree<_Tmap_traits<t_Kty, t_Ty, t_Pr, t_Alloc, false>>))
{
    o_reflection
    {
        o_default_template_argument_type(t_Alloc, std::allocator<std::pair<const t_Kty, t_Ty>>);
        o_default_template_argument_type(t_Pr, std::less<t_Kty>);

        o_nested_typedef(iterator);
        o_nested_typedef(const_iterator);
        o_nested_typedef(reverse_iterator);
        o_nested_typedef(const_reverse_iterator);
        o_nested_typedef(value_type);
        o_nested_typedef(mapped_type);
        o_nested_typedef(key_type);
        o_nested_typedef(reference);
        o_nested_typedef(const_reference);
        o_nested_typedef(pointer);
        o_nested_typedef(const_pointer);
        o_nested_typedef(size_type);

        o_member_function(mapped_type&, operator[], (const key_type&), o_public);
        o_member_function(mapped_type&, at, (const key_type& k), o_public);
        o_member_function(const mapped_type&, at, (const key_type& k), o_public|o_const);

        o_member_function(const_iterator, begin, (), o_public|o_const);
        o_member_function(const_reverse_iterator, rbegin, (), o_public|o_const);
        o_member_function(iterator, begin, (), o_public|o_noconst);
        o_member_function(reverse_iterator, rbegin, (), o_public|o_noconst);
        o_member_function(const_iterator, cbegin, (), o_public);
        o_member_function(const_reverse_iterator, crbegin, (), o_public);

        o_member_function(const_iterator, end, (), o_public|o_const);
        o_member_function(const_reverse_iterator, rend, (), o_public|o_const);
        o_member_function(iterator, end, (), o_public|o_noconst);
        o_member_function(reverse_iterator, rend, (), o_public|o_noconst);
        o_member_function(const_iterator, cend, (), o_public);
        o_member_function(const_reverse_iterator, crend, (), o_public);

        o_member_function(size_type, size, (), o_public);
        o_member_function(bool, empty, (), o_public);

    };
};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map);

// multimap
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap, (_Tree<_Tmap_traits<t_Kty, t_Ty, t_Pr, t_Alloc, true>>)){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap);

o_classNTS((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map, (std::map<t_Key,t_Value,t_Pred, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Key, t_Value))>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map);

#endif