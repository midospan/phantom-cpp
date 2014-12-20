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

#ifndef o_phantom_reflection_native_TNativeInstanceDataMember_h__
#define o_phantom_reflection_native_TNativeInstanceDataMember_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ContentType>
class TNativeInstanceDataMember : public InstanceDataMember
{
public:
    typedef TNativeInstanceDataMember<t_Ty, t_ContentType> self_type;
    typedef t_ContentType (t_Ty::*data_member_pointer_t);
    typedef o_NESTED_TYPE boost::remove_const<t_ContentType>::type t_ContentTypeNoConst;
    typedef o_NESTED_TYPE canonical_meta_class_type_of<t_ContentTypeNoConst>::type meta_value_type;

public:
    TNativeInstanceDataMember(Type* a_pContentType, const string& a_strName, data_member_pointer_t a_member_field_pointer, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_uiModifiers = 0 )
        : InstanceDataMember(a_pContentType
                            , a_strName
                            , (size_t)const_cast<t_ContentTypeNoConst*>(&(((t_Ty const*)nullptr)->*a_member_field_pointer))
                            , a_pRange
                            , a_uiSerializationMask
                            , a_uiModifiers|o_native)
     , m_member_field_pointer(a_member_field_pointer)
    {}

    virtual void*        getAddress( void const* a_pObject ) const
    {
        return
            const_cast<t_ContentTypeNoConst*>
            (
                &(static_cast<t_Ty const*>(a_pObject)->*m_member_field_pointer)
            );
    }
    virtual void        getValue( void const* a_pObject, void* dest ) const
    {
        value_getter<t_ContentType>::apply(dest, const_cast<t_Ty*>(reinterpret_cast<t_Ty const*>(a_pObject))->*m_member_field_pointer) ;
    }
    virtual void        setValue( void* a_pObject, void const* src ) const
    {
        value_setter<t_ContentType>::apply(src, reinterpret_cast<t_Ty*>(a_pObject)->*m_member_field_pointer);
    }

    void serializeValue( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        phantom::serializer<t_ContentType>::serialize(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , a_pOutBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void serializeValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::serializer<t_ContentType>::serialize(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , a_pOutBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    
    void deserializeValue( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        phantom::serializer<t_ContentType>::deserialize(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
            , a_pInBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void deserializeValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::serializer<t_ContentType>::deserialize(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                , a_pInBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void serializeValue( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        property_tree value_tree;
        
        m_pValueType->serialize(
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , value_tree
            , a_uiSerializationMask, a_pDataBase);
        a_OutBranch.add_child(m_strName, value_tree);
    }

    void serializeValue( void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this
            property_tree value_tree;
            m_pValueType->serialize(
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , value_tree
                , a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(m_strName, value_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void deserializeValue( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
        if(value_tree_opt.is_initialized())
        {
            m_pValueType->deserialize(
                &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
                , *value_tree_opt
                , a_uiSerializationMask, a_pDataBase);
        }
    }

    void deserializeValue( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this ... all values will taken from the same tag... bad me, baaad
            boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
            if(value_tree_opt.is_initialized())
            {
                m_pValueType->deserialize(
                    &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                    , *value_tree_opt
                    , a_uiSerializationMask, a_pDataBase);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }

    void rememberValue( void const* a_pInstance, byte*& a_pOutBuffer ) const
    {
        phantom::resetter<t_ContentType>::remember(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty const*>(a_pInstance)->*m_member_field_pointer)
            , a_pOutBuffer);
    }

    void rememberValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::resetter<t_ContentType>::remember(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty const*>(pChunk)->*m_member_field_pointer)
                , a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void resetValue( void* a_pInstance, byte const*& a_pInBuffer ) const
    {
        phantom::resetter<t_ContentType>::reset(static_cast<meta_value_type*>(getValueType()),
            &(static_cast<t_Ty*>(a_pInstance)->*m_member_field_pointer)
            , a_pInBuffer);
    }

    void resetValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::resetter<t_ContentType>::reset(static_cast<meta_value_type*>(getValueType()),
                &(reinterpret_cast<t_Ty*>(pChunk)->*m_member_field_pointer)
                , a_pInBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    data_member_pointer_t    m_member_field_pointer;
};

template<typename t_Ty, typename t_ContentType>
class TNativeInstanceDataMember<t_Ty, t_ContentType const>
    : public TNativeInstanceDataMember<t_Ty,t_ContentType>
{
public:
    typedef TNativeInstanceDataMember<t_Ty, t_ContentType const> self_type;
    typedef t_ContentType const (t_Ty::*data_member_pointer_t);

public:
    TNativeInstanceDataMember(Type* a_pContentType, const string& a_strName, data_member_pointer_t a_member_field_pointer, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_uiModifiers = 0)
        : TNativeInstanceDataMember<t_Ty,t_ContentType>(a_pContentType, a_strName

        // We manage const-type attributes like no-const-type attributes : we break the const qualifier to be able to force write with "setValue"
        , const_cast<typename TNativeInstanceDataMember<t_Ty,t_ContentType>::data_member_pointer_t>(a_member_field_pointer)
        , a_pRange
        , a_uiSerializationMask
        , a_uiModifiers)
    {}

};

o_namespace_end(phantom, reflection, native)

#endif // TNativeInstanceDataMember_h__
