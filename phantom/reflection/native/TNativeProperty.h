/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeProperty_h__
#define o_phantom_reflection_native_TNativeProperty_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
struct is_property_value_type
{
    const static bool value = !boost::is_reference<t_Ty>::value && !boost::is_const<t_Ty>::value;
};

template<typename t_Ty>
struct is_property_value_type<const t_Ty&>
{
    const static bool value = !boost::is_reference<t_Ty>::value && !boost::is_const<t_Ty>::value;
};

template<typename t_Ty, typename t_ValueType>
class TNativeProperty : public Property
{
    o_static_assert_msg(is_property_value_type<t_ValueType>::value, "Type is not a valid property value type");

    template<typename t_CTy>
    struct value_getter
    {
        typedef o_NESTED_TYPE boost::remove_cv<t_CTy>::type no_const;
        static void apply(void* dest, t_CTy& src)
        {
            *reinterpret_cast<no_const*>(dest) = src;
        }
    };

    template<typename t_CTy, size_t t_size>
    struct value_getter<t_CTy[t_size]>
    {
        typedef o_NESTED_TYPE boost::remove_cv<t_CTy>::type no_const;
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
        typedef o_NESTED_TYPE boost::remove_cv<t_CTy>::type no_const;
        static void apply(void const* src, t_CTy& dest)
        {
            dest = *const_cast<no_const*>(reinterpret_cast<t_CTy const*>(src));
        }
    };

    template<typename t_CTy, size_t t_size>
    struct value_setter<t_CTy[t_size]>
    {
        typedef o_NESTED_TYPE boost::remove_cv<t_CTy>::type no_const;
        static void apply(void const* src, t_CTy dest[t_size])
        {
            size_t i = 0;
            for(;i<t_size;++i)
            {
                value_setter<t_CTy>::apply(&(const_cast<no_const*>(reinterpret_cast<t_CTy const*>(src))[i]), dest[i]);
            }
        }
    };

    typedef o_NESTED_TYPE boost::remove_reference<t_ValueType>::type      t_ValueTypeNoRef;
    typedef o_NESTED_TYPE boost::remove_cv<t_ValueTypeNoRef>::type     t_ValueTypeNoConstNoRef;
    typedef o_NESTED_TYPE canonical_meta_class_type_of<t_ValueTypeNoConstNoRef>::type meta_value_type;
    
public:
    typedef TNativeProperty<t_Ty, t_ValueType> self_type;
    typedef t_ValueType (t_Ty::*getter)() const;
    typedef void (t_Ty::*setter)(t_ValueType);
    
public:
    TNativeProperty(Type* a_pValueType, const string& a_strName, MemberFunction* a_pSetMemberFunction, MemberFunction* a_pGetMemberFunction, Signal* a_pSignal, Range* a_pRange, setter a_setter, getter a_getter, uint a_uiSerializationMask, modifiers_t a_uiModifiers = 0)
     : Property(a_pValueType, a_strName, a_pSetMemberFunction, a_pGetMemberFunction, a_pSignal, a_pRange, a_uiSerializationMask, a_uiModifiers|o_native, 0)
     , m_setter(a_setter)
     , m_getter(a_getter)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void        getValue( void const* a_pObject, void* dest ) const
    {
        *((t_ValueTypeNoConstNoRef*)dest) = (reinterpret_cast<t_Ty const*>(a_pObject)->*m_getter)();
    }
    virtual void        setValue( void* a_pObject, void const* src ) const
    {
        (reinterpret_cast<t_Ty*>(a_pObject)->*m_setter)(*((t_ValueTypeNoConstNoRef*)src));
    }
    void                copyValue(void* dest, void const* src) const
    {
        (reinterpret_cast<t_Ty*>(dest)->*m_setter)((reinterpret_cast<t_Ty const*>(src)->*m_getter)());
    }

    void serializeValue( void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        phantom::serializer<t_ValueTypeNoConstNoRef>::serialize(static_cast<meta_value_type*>(getValueType()),
            (t_ValueTypeNoConstNoRef*)&contentType
            , a_pOutBuffer
            , a_uiSerializationMask, a_pDataBase);
    }

    void serializeValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            t_ValueType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
            phantom::serializer<t_ValueTypeNoConstNoRef>::serialize(static_cast<meta_value_type*>(getValueType()),
                (t_ValueTypeNoConstNoRef*)&contentType
                , a_pOutBuffer
                , a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }
    
    void deserializeValue( void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueTypeNoConstNoRef contentType;
        phantom::serializer<t_ValueTypeNoConstNoRef>::deserialize(static_cast<meta_value_type*>(getValueType()),
            &contentType
            , a_pInBuffer
            , a_uiSerializationMask, a_pDataBase);
        (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
    }

    void deserializeValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueTypeNoConstNoRef contentType;
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        while(a_uiCount--)
        {
            phantom::serializer<t_ValueTypeNoConstNoRef>::deserialize(static_cast<meta_value_type*>(getValueType()),
                &contentType
                , a_pInBuffer
                , a_uiSerializationMask, a_pDataBase);
            (reinterpret_cast<t_Ty*>(pChunk)->*m_setter)(contentType);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void serializeValue( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        property_tree value_tree;
        m_pValueType->removeReference()->removeQualifiers()->serialize(
            (t_ValueTypeNoConstNoRef*)&contentType
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
            t_ValueType contentType = (reinterpret_cast<t_Ty const*>(pChunk)->*m_getter)();
            property_tree value_tree;
            m_pValueType->removeReference()->removeQualifiers()->serialize(
                (t_ValueTypeNoConstNoRef*)&contentType
                , value_tree
                , a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(m_strName, value_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void deserializeValue( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueTypeNoConstNoRef contentType;
        boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
        if(value_tree_opt.is_initialized())
        {
            m_pValueType->removeReference()->removeQualifiers()->deserialize(
                &contentType
                , *value_tree_opt
                , a_uiSerializationMask, a_pDataBase);
            (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
        }
    }

    void deserializeValue( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
    {
        t_ValueTypeNoConstNoRef contentType;
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            // TODO : correct this ... all values will be written on the same tag
            boost::optional<const property_tree&> value_tree_opt = a_InBranch.get_child_optional(m_strName);
            if(value_tree_opt.is_initialized())
            {
                m_pValueType->removeReference()->removeQualifiers()->deserialize(
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
        t_ValueType contentType = (reinterpret_cast<t_Ty const*>(a_pInstance)->*m_getter)();
        phantom::resetter<t_ValueTypeNoConstNoRef>::remember(static_cast<meta_value_type*>(getValueType()),
            (t_ValueTypeNoConstNoRef*)&contentType
            , a_pOutBuffer);
    }

    void rememberValue( void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer ) const
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pInstance);
        while(a_uiCount--)
        {
            t_ValueType contentType = (reinterpret_cast<t_Ty const*>(pChunk)->*m_getter)();
            phantom::resetter<t_ValueTypeNoConstNoRef>::remember(static_cast<meta_value_type*>(getValueType()),
                (t_ValueTypeNoConstNoRef*)&contentType
                , a_pOutBuffer);
            pChunk += a_uiChunkSectionSize;
        }
    }

    void resetValue( void* a_pInstance, byte const*& a_pInBuffer ) const
    {
        t_ValueTypeNoConstNoRef contentType;
        phantom::resetter<t_ValueTypeNoConstNoRef>::reset(static_cast<meta_value_type*>(getValueType()),
            &contentType
            , a_pInBuffer);
        (reinterpret_cast<t_Ty*>(a_pInstance)->*m_setter)(contentType);
    }

    void resetValue( void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer ) const
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pInstance);
        t_ValueTypeNoConstNoRef contentType;
        while(a_uiCount--)
        {
            phantom::resetter<t_ValueTypeNoConstNoRef>::reset(static_cast<meta_value_type*>(getValueType()),
                &contentType
                , a_pInBuffer);

            (reinterpret_cast<t_Ty*>(pChunk)->*m_setter)(contentType);
            pChunk += a_uiChunkSectionSize;
        }
    }

    reflection::Type*   getValueType() const { return m_pValueType; }

    getter              m_getter;
    setter              m_setter;
};

template<typename t_Ty, typename t_ValueType>
class TNativeProperty<t_Ty, t_ValueType const>
    : public TNativeProperty<t_Ty,t_ValueType>
{
public:
    typedef TNativeProperty<t_Ty, t_ValueType const> self_type;
    typedef t_ValueType const (t_Ty::*member_field_pointer);

public:
    TNativeProperty(Type* a_pContentType, const string& a_strName, member_field_pointer a_member_field_pointer, modifiers_t a_uiModifiers = 0)
        : TNativeProperty<t_Ty,t_ValueType>(a_pContentType, a_strName

        // We manage const-type attributes like no-const-type attributes : we break the const qualifier to be able to force write with "setValue"
        , const_cast<typename TNativeProperty<t_Ty,t_ValueType>::member_field_pointer>(a_member_field_pointer)
        , a_uiModifiers)
    {}

};

o_namespace_end(phantom, reflection, native)
    
#endif // TNativeProperty_h__
