#ifndef o_phantom_externals_std_h__
#define o_phantom_externals_std_h__

#include <phantom/def_export.h>

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO


// _Container_base
o_classN((std), _Container_base0)
{
    o_reflection {};
};
o_exposeN((std), _Container_base0);

// _Container_base12
o_classN((std), _Container_base12)
{
    o_reflection {};
};
o_exposeN((std), _Container_base12);

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

// char_traits
o_classNT((std), (typename), (_Elem), char_traits)
{
    o_reflection
    {

    };
};
o_exposeNT((std), (typename), (_Elem), char_traits);

// basic_string
o_classNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string)
{
    o_reflection
    {
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
    };
};
o_exposeNT((std), (typename, typename, typename), (t_Elem, t_Traits, t_Ax), basic_string);



/// MAP

// _Pair_base
o_classNT((std), (typename, typename), (t_First, t_Second), _Pair_base
    , o_no_copy * (phantom::has_copy_disabled_cascade<t_First>::value 
    OR phantom::has_copy_disabled<t_Second>::value))
{
    o_reflection 
    {
        o_data_member(t_First, first, o_public) ;
        o_data_member(t_Second, second, o_public);
    };
};
o_exposeNT((std), (typename, typename), (t_First, t_Second), _Pair_base);

// pair
o_classNT((std), (typename, typename), (t_First, t_Second), pair, o_no_copy * (phantom::has_copy_disabled_cascade<t_First>::value 
    OR phantom::has_copy_disabled<t_Second>::value))
{
    o_reflection
    {
        o_data_member(t_First, first, o_no_range, o_public) ;
        o_data_member(t_Second, second, o_no_range, o_public);
    };
};
o_exposeNT((std), (typename, typename), (t_First, t_Second), pair);

// _Tmap_traits
o_classNTS((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits, (_Container_base)){o_reflection {};};
o_exposeNT((std), (class, class, class, class, bool), (t_Kty, t_Ty, t_Pr, t_Alloc, t_Mfl), _Tmap_traits);

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

// map
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map, (_Tree<_Tmap_traits<t_Kty, t_Ty, t_Pr, t_Alloc, false>>)){o_reflection{};};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), map);

// multimap
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap, (_Tree<_Tmap_traits<t_Kty, t_Ty, t_Pr, t_Alloc, true>>)){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Pr, t_Alloc), multimap);

// unordered_map
o_classNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr, t_Alloc), unordered_map);

// _Hash_compare
o_classNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare){o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Kty, t_Hasher, t_Keyeq), _Hash_compare)

// _Umap_traits
o_classNTS((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits, (_Container_base)){o_reflection {};};
o_exposeNT((std, tr1), (typename, typename, typename, typename, bool), (t_Kty, t_Ty, t_Hashcomp, t_Alloc, t_Mfl), _Umap_traits);

// _Hash
o_classNTS((std), (typename), (t_Traits), _Hash, (t_Traits)){o_reflection {};};
o_exposeNT((std), (typename), (t_Traits), _Hash);


/// VECTOR

// _Vector_val
o_classNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val){o_reflection {};};
o_exposeNT((std), (typename, typename), (_Ty, _Alloc), _Vector_val);

// _Vector_const_iterator
o_classNT((std), (typename), (_Ty), _Vector_const_iterator){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _Vector_const_iterator);

// _Vector_iterator
o_classNTS((std), (typename), (_Ty), _Vector_iterator, (_Vector_const_iterator<_Ty>)){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _Vector_iterator);

// vector
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), vector, (_Vector_val<t_Ty, t_Alloc>)){o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), vector);

/// LIST

// _List_nod
o_classNTS((std), (typename, typename), (_Ty, _Alloc), _List_nod, (_Container_base)){o_reflection {};};
o_exposeNT((std), (typename, typename), (_Ty, _Alloc), _List_nod);

// _List_val
o_classNTS((std), (typename, typename), (_Ty, _Alloc), _List_val, (_List_nod<_Ty, _Alloc>)) {o_reflection {};};
o_exposeNT((std), (typename, typename), (_Ty, _Alloc), _List_val);

// _List_const_iterator
o_classNT((std), (typename), (_Ty), _List_const_iterator){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _List_const_iterator);

// _List_iterator
o_classNTS((std), (typename), (_Ty), _List_iterator, (_List_const_iterator<_Ty>)){o_reflection {};};
o_exposeNT((std), (typename), (_Ty), _List_iterator);

// list
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), list, (_List_val<t_Ty, t_Alloc>)){o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), list);

/// MISC

// allocator
o_classNT((std), (typename), (_Elem), allocator){o_reflection {};};
o_exposeNT((std), (typename), (_Elem), allocator);

// binary_function
o_classNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function){o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Arg1, t_Arg2, t_Result), binary_function);

// unary_function
o_classNT((std), (typename, typename), (t_Arg, t_Result), unary_function){o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Arg, t_Result), unary_function);

// less
o_classNTS((std), (typename), (t_Ty), less, (binary_function<t_Ty, t_Ty, bool>)){o_reflection {};};
o_exposeNT((std), (typename), (t_Ty), less);

// _Uset_traits
o_classNTS((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits, (_Container_base)){o_reflection{};};
o_exposeNT((std, tr1), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Uset_traits);

// unordered_set
o_classNTS((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set, (_Hash<tr1::_Uset_traits<t_Kty,_Hash_compare<t_Kty, t_Hash, t_Keyeq>, t_Alloc, false> >)){o_reflection {};};
o_exposeNT((std), (typename, typename, typename, typename), (t_Kty, t_Hash, t_Keyeq, t_Alloc), unordered_set);

// hash
o_classNTS((std), (typename), (_Kty), hash, (unary_function<_Kty, size_t>)){o_reflection {};};
o_exposeNT((std), (typename), (_Kty), hash);

// equal_to
o_classNTS((std), (typename), (t_Ty), equal_to, (binary_function<t_Ty,t_Ty,bool>)){o_reflection {};};
o_exposeNT((std), (typename), (t_Ty), equal_to);

// reverse_iterator
o_classNT((std), (typename), (t_RanIt), reverse_iterator){o_reflection {};};
o_exposeNT((std), (typename), (t_RanIt), reverse_iterator);

// set
o_classNTS((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set, (_Tree<_Tset_traits<t_Ty, t_Pr, t_Alloc, false>>)) {o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Ty, t_Pr, t_Alloc), set);

// _Tset_traits
o_classNTS((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits, (_Container_base)) {o_reflection{};};
o_exposeNT((std), (typename, typename, typename, bool), (t_Kty, t_Tr, t_Alloc, t_Mfl), _Tset_traits);

// multiset
o_classNTS((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset, (_Tree<_Tset_traits<t_Kty, t_Pr, t_Alloc, true>>)) {o_reflection {};};
o_exposeNT((std), (typename, typename, typename), (t_Kty, t_Pr, t_Alloc), multiset);

/// DEQUE

// _Deque_val
o_classNTS((std), (typename, typename), (_Kty, _Alloc), _Deque_val, (_Container_base12)) {o_reflection{};};
o_exposeNT((std), (typename, typename), (_Kty, _Alloc), _Deque_val);

// deque
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), deque, (_Deque_val<t_Ty, t_Alloc>)) { o_reflection {};};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), deque);

#endif // VISUAL_STUDIO STL



// Phantom std specialization

o_classNTS((phantom), (typename), (t_Ty), vector, (std::vector<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), vector);

o_classNTS((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map, (std::map<t_Key,t_Value,t_Pred, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Key, t_Value))>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename,typename,typename), (t_Key,t_Value,t_Pred), map);

o_classNTS((phantom), (typename), (t_Ty), list, (std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), list);



o_classNTS((phantom), (typename), (t_Ty), deque, (std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), deque);

#if o_HAS_CPP0X
o_classNTS((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>)){o_reflection {};};
#else
o_classNTS((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map, (std::tr1::unordered_map<t_Kty, t_Ty, t_Hash, t_Pr, o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>)){o_reflection {};};
#endif

o_exposeNT((phantom), (typename, typename, typename, typename), (t_Kty, t_Ty, t_Hash, t_Pr), unordered_map);

o_namespace_begin(phantom, extension, detail)

    template <>
struct default_serializer<vector<bool>>
{
    typedef vector<bool>::value_type value_type;
    typedef vector<bool>::size_type size_type;
    typedef vector<bool>::const_iterator const_iterator;

public:
    static void serialize(vector<bool> const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = a_pInstance->size();
        serializer<size_type>::serialize(&size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        const_iterator it = a_pInstance->begin();
        const_iterator end = a_pInstance->end();
        for(;it!=end;++it)
        {
            bool value = *it;
            serializer<value_type>::serialize(&value, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    static void deserialize(vector<bool>* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = 0;
        serializer<size_type>::deserialize(&size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        a_pInstance->reserve(size);
        size_type i = 0;
        for(;i<size;++i)
        {
            value_type deserialized;
            serializer<value_type>::deserialize(&deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            a_pInstance->push_back(deserialized);
        }
    }
    static void serialize(vector<bool> const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            vector<bool> const* pInstance = reinterpret_cast<vector<bool> const*>(pChunk);
            size_type   size = pInstance->size();
            serializer<size_type>::serialize(&size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            const_iterator it = pInstance->begin();
            const_iterator end = pInstance->end();
            for(;it!=end;++it)
            {
                bool value = *it;
                serializer<value_type>::serialize(&value, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(vector<bool>* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            vector<bool>* pInstance = reinterpret_cast<vector<bool>*>(pChunk);
            size_type   size = 0;
            serializer<size_type>::deserialize(&size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            pInstance->reserve(size);
            size_type i = 0;
            for(;i<size;++i)
            {
                value_type deserialized;
                serializer<value_type>::deserialize(&deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                pInstance->push_back(deserialized);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serialize(vector<bool> const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = a_pInstance->size();
        a_OutBranch.put<string>("size", phantom::lexical_cast<string>(size));
        const_iterator it = a_pInstance->begin();
        const_iterator end = a_pInstance->end();
        int i = 0;
        for(;it!=end;++it)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            property_tree index_tree;
            bool value = *it;
            serializer<value_type>::serialize(&value, index_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(index_buffer, index_tree);
        }
    }
    static void deserialize(vector<bool>* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        boost::optional<string> size_str_opt = a_InBranch.get_optional<string>("size");
        if(size_str_opt.is_initialized())
        {
            size_type   size = phantom::lexical_cast<size_type>(*size_str_opt);
            a_pInstance->reserve(size);
            size_type i = 0;
            for(;i<size;++i)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i);
                boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
                if(index_tree_opt.is_initialized())
                {
                    value_type pDeserialized;
                    serializer<value_type>::deserialize(&pDeserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                    a_pInstance->push_back(pDeserialized);
                }
            }
        }
    }
    static void serialize(vector<bool> const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            vector<bool> const* pInstance = reinterpret_cast<vector<bool> const*>(pChunk);
            size_type   size = pInstance->size();
            property_tree container_tree;
            container_tree.put<string>("size", phantom::lexical_cast<string>(size));
            const_iterator it = pInstance->begin();
            const_iterator end = pInstance->end();
            {
                size_t i = 0;
                for(;it!=end;++it)
                {
                    char index_buffer[32]="";
                    o_secured_sprintf(index_buffer, 32, "_%d", i++);
                    property_tree index_tree;
                    bool value = *it;
                    serializer<value_type>::serialize(&value, index_tree, a_uiSerializationMask, a_pDataBase);
                    container_tree.add_child(index_buffer, index_tree);
                }
            }
            a_OutBranch.add_child(index_buffer, container_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(vector<bool>* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            vector<bool>* pInstance = reinterpret_cast<vector<bool>*>(pChunk);
            boost::optional<const property_tree&> container_tree_opt = a_InBranch.get_child_optional(index_buffer);
            if(container_tree_opt.is_initialized())
            {
                const property_tree& container_tree = *container_tree_opt;
                size_type size = phantom::lexical_cast<size_type>(container_tree.get<string>("size"));
                pInstance->reserve(size);
                {
                    size_type i = 0;
                    for(;i<size;++i)
                    {
                        char index_buffer[32]="";
                        o_secured_sprintf(index_buffer, 32, "_%d", i);
                        boost::optional<const property_tree&> index_tree_opt = container_tree.get_child_optional(index_buffer);
                        if(index_tree_opt.is_initialized())
                        {
                            value_type deserialized;
                            serializer<value_type>::deserialize(&deserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                            pInstance->push_back(deserialized);
                        }
                    }
                }
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(vector<bool> const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(vector<bool>* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(vector<bool> const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(vector<bool>* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(vector<bool> const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(vector<bool>* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(vector<bool> const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(vector<bool>* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};

o_namespace_end(phantom, extension, detail)

#endif
