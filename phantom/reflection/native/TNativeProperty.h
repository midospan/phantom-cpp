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

#ifndef o_phantom_reflection_native_TNativeProperty_h__
#define o_phantom_reflection_native_TNativeProperty_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)



template<typename t_Ty, typename t_ContentType>
class TNativeProperty : public Property
{

    template<typename t_CTy>
    struct value_getter
    {
        typedef o_NESTED_TYPE boost::remove_const<t_CTy>::type no_const;
        static void apply(void* dest, t_CTy& src)
        {
            *reinterpret_cast<no_const*>(dest) = src;
        }
    };

    template<typename t_CTy, size_t t_size>
    struct value_getter<t_CTy[t_size]>
    {
        typedef o_NESTED_TYPE boost::remove_const<t_CTy>::type no_const;
        static void apply(void* dest, t_CTy src[t_size])
        {
            size_t i = 0;
            for(;i<t_size;++i)
            {
                value_getter<t_CTy>::apply(&reinterpret_cast<no_const*>(dest)[i], src[i]);
            }
        }
    };
    template<typename t_CTy>
    struct value_setter
    {
        typedef o_NESTED_TYPE boost::remove_const<t_CTy>::type no_const;
        static void apply(void const* src, t_CTy& dest)
        {
            dest = *const_cast<no_const*>(reinterpret_cast<t_CTy const*>(src));
        }
    };

    template<typename t_CTy, size_t t_size>
    struct value_setter<t_CTy[t_size]>
    {
        typedef o_NESTED_TYPE boost::remove_const<t_CTy>::type no_const;
        static void apply(void const* src, t_CTy dest[t_size])
        {
            size_t i = 0;
            for(;i<t_size;++i)
            {
                value_setter<t_CTy>::apply(&(const_cast<no_const*>(reinterpret_cast<t_CTy const*>(src))[i]), dest[i]);
            }
        }
    };

    typedef o_NESTED_TYPE boost::remove_reference<t_ContentType>::type      t_ContentTypeNoRef;
    typedef o_NESTED_TYPE boost::remove_const<t_ContentTypeNoRef>::type     t_ContentTypeNoConstNoRef;
    
public:
    typedef TNativeProperty<t_Ty, t_ContentType> self_type;
    typedef t_ContentType (t_Ty::*getter)() const;
    typedef void (t_Ty::*setter)(t_ContentType);

    
public:
    TNativeProperty(const string& a_strName, Type* a_pValueType, InstanceMemberFunction* a_pSetMemberFunction, InstanceMemberFunction* a_pGetMemberFunction, Signal* a_pSignal, Range* a_pRange, setter a_setter, getter a_getter, uint a_uiSerializationMask, bitfield a_uiModifiers = 0)
     : Property(a_strName, a_pValueType, a_pSetMemberFunction, a_pGetMemberFunction, a_pSignal, a_pRange, a_uiSerializationMask, a_uiModifiers)
     , m_setter(a_setter)
     , m_getter(a_getter)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void        getValue( void const* a_pObject, void* dest ) const
    {
        *((t_ContentTypeNoConstNoRef*)dest) = (reinterpret_cast<t_Ty const*>(a_pObject)->*m_getter)();
    }
    virtual void        setValue( void* a_pObject, void const* src ) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_setter)(*((t_ContentTypeNoConstNoRef*)src));
    }
    void                copyValue(void* dest, void const* src) const
    {
        (reinterpret_cast<t_Ty*>(dest)->*m_setter)((reinterpret_cast<t_Ty const*>(src)->*m_getter)());
    }

    void serializeValue( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        phantom::extension::serializer<t_ContentTypeNoConstNoRef>::serialize(
            (t_ContentTypeNoConstNoRef*)&contentType
            , a_pOutBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void serializeValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            t_ContentType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
            phantom::extension::serializer<t_ContentTypeNoConstNoRef>::serialize(
                (t_ContentTypeNoConstNoRef*)&contentType
                , a_pOutBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }
    
    void deserializeValue( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentTypeNoConstNoRef contentType;
        phantom::extension::serializer<t_ContentTypeNoConstNoRef>::deserialize(
            &contentType
            , a_pInBuffer
            , a_uiSerializationMask, a_pDataBase);
        (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
    }

    void deserializeValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentTypeNoConstNoRef contentType;
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::extension::serializer<t_ContentTypeNoConstNoRef>::deserialize(
                &contentType
                , a_pInBuffer
                , a_uiSerializationMask, a_pDataBase);
            (reinterpret_cast<t_Ty*>(pChunk)->*m_setter)(contentType);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void serializeValue( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        property_tree value_tree;
        m_pValueType->removeReference()->removeConst()->serialize(
            (t_ContentTypeNoConstNoRef*)&contentType
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
            t_ContentType contentType = (reinterpret_cast<t_Ty const*>(pChunk)->*m_getter)();
            property_tree value_tree;
            m_pValueType->removeReference()->removeConst()->serialize(
                (t_ContentTypeNoConstNoRef*)&contentType
                , value_tree
                , a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(m_strName, value_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void deserializeValue( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentTypeNoConstNoRef contentType;
        boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
        if(value_tree_opt.is_initialized())
        {
            m_pValueType->removeReference()->removeConst()->deserialize(
                &contentType
                , *value_tree_opt
                , a_uiSerializationMask, a_pDataBase);
            (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
        }
    }

    void deserializeValue( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ContentTypeNoConstNoRef contentType;
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this ... all values will be written on the same tag
            boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
            if(value_tree_opt.is_initialized())
            {
                m_pValueType->removeReference()->removeConst()->deserialize(
                    &contentType
                    , *value_tree_opt
                    , a_uiSerializationMask, a_pDataBase);
                (reinterpret_cast<t_Ty*>(pChunk)->*m_setter)(contentType);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }

    void rememberValue( void const* a_pInstance, byte*& a_pOutBuffer ) const
    {
        t_ContentType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        phantom::extension::resetter<t_ContentTypeNoConstNoRef>::remember(
            (t_ContentTypeNoConstNoRef*)&contentType
            , a_pOutBuffer);
    }

    void rememberValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            t_ContentType contentType = (reinterpret_cast<t_Ty const*>(pChunk)->*m_getter)();
            phantom::extension::resetter<t_ContentTypeNoConstNoRef>::remember(
                (t_ContentTypeNoConstNoRef*)&contentType
                , a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void resetValue( void* a_pInstance, byte const*& a_pInBuffer ) const
    {
        t_ContentTypeNoConstNoRef contentType;
        phantom::extension::resetter<t_ContentTypeNoConstNoRef>::reset(
            &contentType
            , a_pInBuffer);
        (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
    }

    void resetValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        t_ContentTypeNoConstNoRef contentType;
        while(a_uiCount--)
        {
            phantom::extension::resetter<t_ContentTypeNoConstNoRef>::reset(
                &contentType
                , a_pInBuffer);

            (reinterpret_cast<t_Ty*>(pChunk)->*m_setter)(contentType);
            pChunk += a_uiChunkSectionSize;
        }
    }

    virtual void        deleteNow()
    {
        o_proxy_delete(phantom::reflection::Property, self_type) this;
    }

    reflection::Type*   getValueType() const { return m_pValueType; }

    getter              m_getter;
    setter              m_setter;
};

template<typename t_Ty, typename t_ContentType>
class TNativeProperty<t_Ty, t_ContentType const>
    : public TNativeProperty<t_Ty,t_ContentType>
{
public:
    typedef TNativeProperty<t_Ty, t_ContentType const> self_type;
    typedef t_ContentType const (t_Ty::*member_field_pointer);

public:
    TNativeProperty(const string& a_strName, Type* a_pContentType, member_field_pointer a_member_field_pointer, bitfield a_uiModifiers = 0)
        : TNativeProperty<t_Ty,t_ContentType>(a_strName, a_pContentType

        // We manage const-type attributes like no-const-type attributes : we break the const qualifier to be able to force write with "setValue"
        , const_cast<typename TNativeProperty<t_Ty,t_ContentType>::member_field_pointer>(a_member_field_pointer)
        , a_uiModifiers)
    {}

};

o_namespace_end(phantom, reflection, native)
/*o_traits_specialize_all_super_traitNTS(
(phantom,reflection,native)
, (typename, typename)
, (t_Ty, t_ContentType)
, TNativeProperty
, (Property)
)*/

#endif // TNativeProperty_h__
