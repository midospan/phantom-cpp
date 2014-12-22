/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_def_serializer_h__
#define o_def_serializer_h__

o_namespace_begin(phantom)

enum default_serializer_id
{
    default_serializer_not_serializable,
    default_serializer_not_supported_and_must_be_customized,
    default_serializer_canonical,
    default_serializer_enum,
    default_serializer_structure_or_union,
    default_serializer_class,
    default_serializer_class_with_root_statechart,
    default_serializer_pointer,
    default_serializer_array,
    default_serializer_container,
    default_serializer_basic_string_char,
    default_serializer_basic_string_wchar_t,
};

namespace detail
{
    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_not_serializable>
    {
        static void throw_exception() { o_exception(exception::unsupported_member_function_exception, "This type is not serializable"); }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            throw_exception();
        }
    };

    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_not_supported_and_must_be_customized>
    {
        o_static_assert_msg(sizeof(t_Ty) == sizeof(t_Ty),
            "no serializer defined for the given class, \
            you must define it by yourself and declare it \
            using template specialization or 'o_Serializer' macro-variable \
            in the classdef.h" );

    };

    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_canonical>
    {
    public:
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            *reinterpret_cast<t_Ty*>(a_pOutBuffer) = *a_pInstance;
            a_pOutBuffer += sizeof(t_Ty);
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            *a_pInstance = *reinterpret_cast<t_Ty const*>(a_pInBuffer);
            a_pInBuffer += sizeof(t_Ty);
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                *reinterpret_cast<t_Ty*>(a_pOutBuffer) = *reinterpret_cast<t_Ty const*>(pChunk);
                a_pOutBuffer += sizeof(t_Ty);
            }
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                *reinterpret_cast<t_Ty*>(pChunk) = *reinterpret_cast<t_Ty const*>(a_pInBuffer);
                a_pInBuffer += sizeof(t_Ty);
            }
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_OutBranch.put_value(phantom::lexical_cast<string>(*a_pInstance));
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            const boost::optional<string>& value = a_InBranch.get_value_optional<string>();
            if(value.is_initialized())
            {
                *reinterpret_cast<t_Ty*>(a_pInstance) = phantom::lexical_cast<t_Ty>(*value);
            }
        }
        o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                t_Ty value = *reinterpret_cast<t_Ty const*>(pChunk);
                a_OutBranch.put<string>(index_buffer, phantom::lexical_cast<string>(value));
                pChunk += a_uiChunkSectionSize;
            }
        }
        o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                const boost::optional<string>& value = a_InBranch.get_optional<string>(index_buffer);
                if(value.is_initialized())
                {
                    *reinterpret_cast<t_Ty*>(pChunk) = phantom::lexical_cast<t_Ty>(*value);
                }
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };



    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_array>
    {
        o_static_assert_msg(boost::extent<t_Ty>::value, "t_Ty is not an array type, weird...");
        enum {extent = boost::extent<t_Ty>::value};
        typedef o_NESTED_TYPE boost::remove_extent<t_Ty>::type content_type;

        typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<content_type>::type meta_content_type;

        static void serialize(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            phantom::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type const*>(a_pInstance), extent, sizeof(content_type), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ArrayType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            phantom::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type*>(a_pInstance), extent, sizeof(content_type), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serialize(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
        {
            phantom::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type const*>(a_pInstance), extent, sizeof(content_type), a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ArrayType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
        {
            phantom::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type*>(a_pInstance), extent, sizeof(content_type), a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void        serialize(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            while(a_uiCount--)
            {
                phantom::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type const*>(pChunk), extent, sizeof(content_type), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                pChunk += a_uiChunkSectionSize;
            }
        }

        static void        deserialize(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            while(a_uiCount--)
            {
                phantom::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type*>(pChunk), extent, sizeof(content_type), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                pChunk += a_uiChunkSectionSize;
            }
        }

        static void        serialize(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                property_tree index_tree;
                phantom::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type const*>(pChunk), extent, sizeof(content_type), index_tree, a_uiSerializationMask, a_pDataBase);
                a_OutBranch.add_child(index_buffer, index_tree);
                pChunk += a_uiChunkSectionSize;
            }
        }

        static void        deserialize(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
                if(index_tree_opt.is_initialized())
                {
                    phantom::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getItemType()), reinterpret_cast<content_type*>(pChunk), extent, sizeof(content_type), *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                }
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

    };

    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_pointer>
    {
        static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }

        static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }

        static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
        {
            a_pType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }

        static void deserialize( reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
        {
            a_pType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

        static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }

        static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }

        static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }

        static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_pType->deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };



    template<typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_enum>
    {
        typedef o_NESTED_TYPE phantom::enum_integral_type<t_Ty>::type proxy_type;
        o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }



        o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };


    template <typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_class_with_root_statechart>
    {
    public:
        o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            state::state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }



        o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            state::root_class_state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

    };

    template<typename t_Ty, size_t t_base_class_count_of>
    struct base_class_serializer_helper
    {
        o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::serialize(a_pClass, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::serialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::deserialize(a_pClass, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::deserialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::serialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::serialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::deserialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::deserialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::serialize(a_pClass, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::serialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::deserialize(a_pClass, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::deserialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::serialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::serialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer_helper<t_Ty, t_base_class_count_of-1>::deserialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            phantom::serializer<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::deserialize(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };



    template<typename t_Ty>
    struct base_class_serializer_helper<t_Ty, 0> // recursion stop 
    {
        o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
        o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
        o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
        o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
        o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
        o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
        o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
        o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    };

    template <typename t_Ty>
    struct base_class_serializer : public base_class_serializer_helper<t_Ty, phantom::base_class_count_of<t_Ty>::value>
    {

    };

    template <typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_class>
    {
    public:
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            serializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            deserializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            property_tree class_tree;
            serializeLayout(a_pType, a_pInstance, class_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(/*encodeQualifiedDecoratedNameToIdentifierName*/(a_pType->getQualifiedDecoratedName()), class_tree);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            auto it = a_InBranch.begin();
            auto end = a_InBranch.end();
            for(;it!=end;++it)
            {
                // The test below could seem dirty but it's useful to deserialize typedefs or placeholder types 
                // which goal is to point to a type without having the same representation name (ex: my_vector2 could point to phantom::math::vector2<float>)
                // It's also useful is you have a type versionning (a script class rebuilt with a different name but you still want to deserialize from the older type name
                reflection::Type* solvedType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(it->first)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(it->first));
                if(solvedType AND (solvedType->getQualifiedDecoratedName() == a_pType->getQualifiedDecoratedName()))
                {
                    deserializeLayout(a_pType, a_pInstance, it->second, a_uiSerializationMask, a_pDataBase);
                }
            }
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            property_tree class_tree;
            serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, class_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(/*encodeQualifiedDecoratedNameToIdentifierName*/(a_pType->getQualifiedDecoratedName()), class_tree);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            base_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            auto it = a_InBranch.begin();
            auto end = a_InBranch.end();
            for(;it!=end;++it)
            {
                // The test below could seem dirty but it's useful to deserialize typedefs or placeholder types 
                // which goal is to point to a type without having the same representation name (ex: my_vector2 could point to phantom::math::vector2<float>)
                // It's also useful is you have a type versionning (a script class rebuilt with a different name but you still want to deserialize from the older type name
                reflection::Type* solvedType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(it->first)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(it->first));
                if(solvedType AND (solvedType->getQualifiedDecoratedName() == a_pType->getQualifiedDecoratedName()))
                {
                    deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, it->second, a_uiSerializationMask, a_pDataBase);
                }
            }
        }

        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask))
                    pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            // If you have a compilation error here 
            // that probably means that a base class declared 
            // in a reflection declaration ( the class t_Ty ) hasn't
            // itself a reflection declared
            // v
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        }
    };

    template <typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_structure_or_union>
    {
    public:
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }

        inline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serializeLayout(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }

        inline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserializeLayout(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

        inline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }

        inline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }

        inline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask))
                    pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            // If you have a compilation error here 
            // that probably means that a base class declared 
            // in a reflection declaration ( the class t_Ty ) hasn't
            // itself a reflection declared
            // v
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
        }

        inline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isSaved(a_uiSerializationMask)) 
                    pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        }
    };

    template <typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_container>
    {
        typedef o_NESTED_TYPE t_Ty::value_type value_type;
        typedef o_NESTED_TYPE t_Ty::size_type size_type;
        typedef o_NESTED_TYPE t_Ty::const_iterator const_iterator;

        typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<t_Ty>::type meta_type;
        typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<value_type>::type meta_value_type;

    public:
        static void serialize(meta_type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            size_type   size = a_pInstance->size();
            serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            const_iterator it = a_pInstance->begin();
            const_iterator end = a_pInstance->end();
            for(;it!=end;++it)
            {
                serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
        }
        static void deserialize(meta_type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            size_type   size = 0;
            serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::container::reserver<t_Ty>::apply(a_pInstance, size);
            size_type i = 0;
            for(;i<size;++i)
            {
                value_type deserialized;
                serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                phantom::container::adder<t_Ty>::apply(a_pInstance, deserialized);
            }
        }
        static void serialize(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            while(a_uiCount--)
            {
                t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
                size_type   size = pInstance->size();
                serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                const_iterator it = pInstance->begin();
                const_iterator end = pInstance->end();
                for(;it!=end;++it)
                {
                    serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                }
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void deserialize(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            while(a_uiCount--)
            {
                t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
                size_type   size = 0;
                serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                phantom::container::reserver<t_Ty>::apply(pInstance, size);
                size_type i = 0;
                for(;i<size;++i)
                {
                    value_type deserialized;
                    serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                    phantom::container::adder<t_Ty>::apply(pInstance, deserialized);
                }
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serialize(meta_type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
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
                serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), index_tree, a_uiSerializationMask, a_pDataBase);
                a_OutBranch.add_child(index_buffer, index_tree);
            }
        }
        static void deserialize(meta_type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            boost::optional<string> size_str_opt = a_InBranch.get_optional<string>("size");
            if(size_str_opt.is_initialized())
            {
                size_type   size = phantom::lexical_cast<size_type>(*size_str_opt);
                phantom::container::reserver<t_Ty>::apply(a_pInstance, size);
                size_type i = 0;
                for(;i<size;++i)
                {
                    char index_buffer[32]="";
                    o_secured_sprintf(index_buffer, 32, "_%d", i);
                    boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
                    if(index_tree_opt.is_initialized())
                    {
                        value_type pDeserialized;
                        serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &pDeserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                        phantom::container::adder<t_Ty>::apply(a_pInstance, pDeserialized);
                    }
                }
            }
        }
        static void serialize(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
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
                        serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), index_tree, a_uiSerializationMask, a_pDataBase);
                        container_tree.add_child(index_buffer, index_tree);
                    }
                }
                a_OutBranch.add_child(index_buffer, container_tree);
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void deserialize(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
                boost::optional<const property_tree&> container_tree_opt = a_InBranch.get_child_optional(index_buffer);
                if(container_tree_opt.is_initialized())
                {
                    const property_tree& container_tree = *container_tree_opt;
                    size_type size = phantom::lexical_cast<size_type>(container_tree.get<string>("size"));
                    phantom::container::reserver<t_Ty>::apply(pInstance, size);
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
                                serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                                phantom::container::adder<t_Ty>::apply(pInstance, deserialized);
                            }
                        }
                    }
                }
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serializeLayout(meta_type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(meta_type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(meta_type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(meta_type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };


    // some util template functions
    template<typename t_Ty2>
    struct to_property_branch_value
    {
        static const char* apply(t_Ty2 const* a_pInstance) { return a_pInstance->c_str(); }
    };
    template<>
    struct to_property_branch_value<phantom::string>
    {
        static phantom::string const & apply(phantom::string const* a_pInstance) { return *a_pInstance; }
    };
    template<typename t_Ty2>
    struct from_property_branch_value
    {
        static const char* apply(phantom::string const& a_pInstance) { return a_pInstance.c_str(); }
    };
    template<>
    struct from_property_branch_value<phantom::string>
    {
        static phantom::string const & apply(phantom::string const& a_pInstance)
        {
            return a_pInstance;
        }
    };

    template <typename t_Ty>
    struct default_serializer_helper<t_Ty, default_serializer_basic_string_char>
    {

        typedef o_NESTED_TYPE t_Ty::value_type      value_type;
        typedef o_NESTED_TYPE t_Ty::size_type       size_type;
        typedef o_NESTED_TYPE t_Ty::const_iterator  const_iterator;

    public:
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            size_type size = a_pInstance->size();
            serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            memcpy(a_pOutBuffer, a_pInstance->c_str(), size);
            a_pOutBuffer += size;
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            size_type   size = 0;
            serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            a_pInstance->assign((char const*)a_pInBuffer, size);
            a_pInBuffer += size;
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            while(a_uiCount--)
            {
                t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
                size_type size = pInstance->size();
                serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                memcpy(a_pOutBuffer, pInstance->c_str(), size);
                a_pOutBuffer += size;
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            while(a_uiCount--)
            {
                t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
                size_type   size = 0;
                serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                pInstance->assign((char const*)a_pInBuffer, size);
                a_pInBuffer += size;
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            a_OutBranch.put_value(to_property_branch_value<t_Ty>::apply(a_pInstance));
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            boost::optional<string> opt = a_InBranch.get_value_optional<string>();
            if(opt.is_initialized())
            {
                a_pInstance->assign(from_property_branch_value<t_Ty>::apply(*opt));
            }
            else a_pInstance->clear();
        }
        static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                a_OutBranch.put<string>(index_buffer, to_property_branch_value<t_Ty>::apply(pInstance));
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            int i = 0;
            while(a_uiCount--)
            {
                t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i++);
                boost::optional<string> opt = a_InBranch.get_optional<string>(index_buffer);
                if(opt.is_initialized())
                {
                    pInstance->assign(from_property_branch_value<t_Ty>::apply(*opt));
                }
                else pInstance->clear();
                pChunk += a_uiChunkSectionSize;
            }
        }
        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
        static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
        {
            deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    };
}


template <typename t_Ty>
struct default_serializer : public detail::default_serializer_helper<t_Ty,
    (boost::is_void<t_Ty>::value OR phantom::is_signal_t<t_Ty>::value)
    ? default_serializer_not_serializable
    : boost::is_array<t_Ty>::value
    ? default_serializer_array
    : phantom::is_data_pointer<t_Ty>::value
        ? default_serializer_pointer
        : boost::is_enum<t_Ty>::value
        ? default_serializer_enum
        : boost::is_union<t_Ty>::value 
        ? default_serializer_structure_or_union
        : boost::is_class<t_Ty>::value 
            ? is_basic_string_char<t_Ty>::value
                ? default_serializer_basic_string_char
                : (is_map_container<t_Ty>::value OR is_sequential_container<t_Ty>::value OR is_set_container<t_Ty>::value)
                    ? default_serializer_container
                    : /*has_reflection<t_Ty>::value
                        ? */has_root_statechart<t_Ty>::value
                            ? default_serializer_class_with_root_statechart
                            : is_structure<t_Ty>::value
                                ? default_serializer_structure_or_union
                                : default_serializer_class
                        //: detail::default_serializer_not_supported_and_must_be_customized
        : default_serializer_canonical>

{
    o_rebind(default_serializer)
};

template <>
class default_serializer<phantom::signal_t>
{
public:
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(phantom::exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }


    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }

};



#if o_HAS_BUILT_IN_WCHAR_T
template <>
struct default_serializer<wchar_t>
{
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }



    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct serializer
///
/// \brief  Serializer. (see instance creation process)
/// 		Serialization is applied when the users wants it. It's used inside the high-level serialization system provided with phantom.
/// 		Deserialization is applied just after installation (see instance creation process)
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct serializer : public default_serializer<t_Ty>
{
};


o_namespace_end(phantom)

#endif // o_def_serializer_h__