#pragma once

#include "utility.hxx"

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
o_classNTS((std), (typename, typename), (t_Ty, t_Alloc), vector, (_Vector_val<t_Ty, t_Alloc>))
{
    o_reflection 
    {
        o_default_template_argument_type(t_Alloc, std::allocator<t_Ty>);
        o_typedef(iterator);
        o_typedef(const_iterator);
        o_typedef(reverse_iterator);
        o_typedef(const_reverse_iterator);
    };
};
o_exposeNT((std), (typename, typename), (t_Ty, t_Alloc), vector);

o_classNTS((phantom), (typename), (t_Ty), vector, (std::vector<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>))
{
    o_reflection
    {

    };
};
o_exposeNT((phantom), (typename), (t_Ty), vector);