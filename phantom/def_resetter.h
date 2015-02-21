/* TODO LICENCE HERE */

#ifndef o_def_resetter_h__
#define o_def_resetter_h__

o_namespace_begin(phantom)

enum default_resetter_id
{
    default_resetter_not_resettable,
    default_resetter_not_supported_and_must_be_customized,
    default_resetter_canonical,
    default_resetter_class,
    default_resetter_class_with_root_statechart,
    default_resetter_default,
};

namespace detail
{
    template<typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_not_resettable>
    {
        static void throw_exception() { o_exception(exception::unsupported_member_function_exception, "This type is not resettable"); }
        o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            throw_exception();
        }
        o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            throw_exception();
        }
        o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            throw_exception();
        }
        o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            throw_exception();
        }
    };

    template<typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_not_supported_and_must_be_customized>
    {
        o_static_assert_msg(sizeof(t_Ty) == sizeof(t_Ty),
            "no resetter defined for the given class, \
            you must define it by yourself and declare it \
            using template specialization or 'o_Resetter' macro-variable \
            in the classdef.h" );

    };

    template<typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_canonical>
    {
        o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            default_serializer_helper<t_Ty, default_serializer_canonical>::serialize(a_pType, a_pInstance, a_pOutBuffer, 0, NULL);
        }
        o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            default_serializer_helper<t_Ty, default_serializer_canonical>::deserialize(a_pType, a_pInstance, a_pInBuffer, 0, NULL);
        }
        o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            default_serializer_helper<t_Ty, default_serializer_canonical>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, 0, NULL);
        }
        o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            default_serializer_helper<t_Ty, default_serializer_canonical>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, 0, NULL);
        }
    };

    template<typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_default>
    {
        template<typename t_MetaTy>
        o_forceinline static void remember(t_MetaTy* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            serializer<t_Ty>::serialize(a_pType, a_pInstance, a_pOutBuffer, 0, NULL);
        }
        template<typename t_MetaTy>
        o_forceinline static void reset(t_MetaTy* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            serializer<t_Ty>::deserialize(a_pType, a_pInstance, a_pInBuffer, 0, NULL);
        }
        template<typename t_MetaTy>
        o_forceinline static void remember(t_MetaTy* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            serializer<t_Ty>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, 0, NULL);
        }
        template<typename t_MetaTy>
        o_forceinline static void reset(t_MetaTy* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            serializer<t_Ty>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, 0, NULL);
        }
    };

    template <typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_class_with_root_statechart>
    {
    public:
        o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            default_resetter_helper<t_Ty, default_resetter_class>::remember(a_pType, a_pInstance, a_pOutBuffer);
            state_machine_resetter<t_Ty>::remember(a_pInstance, a_pOutBuffer);
        }
        o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            default_resetter_helper<t_Ty, default_resetter_class>::reset(a_pType, a_pInstance, a_pInBuffer);
            state_machine_resetter<t_Ty>::reset(a_pInstance, a_pInBuffer);
        }
        o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            default_resetter_helper<t_Ty, default_resetter_class>::remember(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
            state_machine_resetter<t_Ty>::remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
        }
        o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            default_resetter_helper<t_Ty, default_resetter_class>::reset(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
            state_machine_resetter<t_Ty>::reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
        }
    };

    template<typename t_Ty, size_t t_base_class_count_of>
    struct base_class_resetter_helper
    {
        o_forceinline static void remember(reflection::Class* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            base_class_resetter_helper<t_Ty, t_base_class_count_of-1>::remember(a_pClass, a_pInstance, a_pOutBuffer);
            phantom::resetter<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::remember(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_pOutBuffer);
        }
        o_forceinline static void reset(reflection::Class* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            base_class_resetter_helper<t_Ty, t_base_class_count_of-1>::reset(a_pClass, a_pInstance, a_pInBuffer);
            phantom::resetter<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::reset(a_pClass->getBaseClass(t_base_class_count_of-1), a_pInstance, a_pInBuffer);
        }
        o_forceinline static void remember(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            base_class_resetter_helper<t_Ty, t_base_class_count_of-1>::remember(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
            phantom::resetter<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::remember(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
        }
        o_forceinline static void reset(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            base_class_resetter_helper<t_Ty, t_base_class_count_of-1>::reset(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
            phantom::resetter<o_traits_t_Ty_base_class(t_base_class_count_of-1)>::reset(a_pClass->getBaseClass(t_base_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
        }

    };

    template<typename t_Ty>
    struct base_class_resetter_helper<t_Ty, 0> // recursion stop 
    {
        o_forceinline static void remember(reflection::Type* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer) {    }
        o_forceinline static void reset(reflection::Type* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer) {    }
        o_forceinline static void remember(reflection::Type* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) {    }
        o_forceinline static void reset(reflection::Type* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) {    }
    };

    template <typename t_Ty>
    struct base_class_resetter : public base_class_resetter_helper<t_Ty, phantom::base_class_count_of<t_Ty>::value>
    {

    };

    template <typename t_Ty>
    struct default_resetter_helper<t_Ty, default_resetter_class>
    {

        inline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
        {
            base_class_resetter<t_Ty>::remember(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pOutBuffer);
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isReset()) 
                    pValueMember->rememberValue(a_pInstance, a_pOutBuffer);
            }
        }

        inline static void reset(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
        {
            base_class_resetter<t_Ty>::reset(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pInBuffer);
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isReset()) 
                    pValueMember->resetValue(a_pInstance, a_pInBuffer);
            }
        }

        inline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
        {
            base_class_resetter<t_Ty>::remember(static_cast<reflection::Class*>(a_pType), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember*const pValueMember = (*it);
                if(pValueMember->isReset())
                    pValueMember->rememberValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
            }
        }

        inline static void reset(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
        {
            base_class_resetter<t_Ty>::reset(static_cast<reflection::Class*>(a_pType), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
            auto it = a_pType->beginValueMembers();
            auto end = a_pType->endValueMembers();
            for(;it != end; ++it)
            {
                reflection::ValueMember* const pValueMember = (*it);
                if(pValueMember->isReset())
                    pValueMember->resetValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
            }
        }


    };
}

template <typename t_Ty>
struct default_resetter : public detail::default_resetter_helper<t_Ty,
    NOT(phantom::is_serializable<t_Ty>::value)
    ? default_resetter_not_resettable
    : boost::is_array<t_Ty>::value
    ? default_resetter_default
    : phantom::is_data_pointer<t_Ty>::value
        ? default_resetter_canonical
        : boost::is_enum<t_Ty>::value
        ? default_resetter_default
        : boost::is_class<t_Ty>::value
            ? is_basic_string_char<t_Ty>::value
                ? default_resetter_default
                : is_container<t_Ty>::value
                    ? default_resetter_default
                    : /*has_reflection<t_Ty>::value
                        ? */has_root_statechart<t_Ty>::value
                            ? default_resetter_class_with_root_statechart
                            : default_resetter_class
                        //: detail::default_serializer_not_supported_and_must_be_customized
        : default_resetter_canonical>

{
    o_rebind(default_resetter)
};

template <>
class default_resetter<phantom::signal_t>
{
public:
    o_forceinline static void remember(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte*& a_pOutBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void reset(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void remember(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void reset(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
};

#if o_HAS_BUILT_IN_WCHAR_T
template <>
class default_resetter<wchar_t>
{
public:
    o_forceinline static void remember(reflection::Type* a_pType, wchar_t const* a_pInstance, byte*& a_pOutBuffer)
    {
        default_resetter<short>::remember(a_pType, (short const*)a_pInstance, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer)
    {
        default_resetter<short>::reset(a_pType, (short*)a_pInstance, a_pInBuffer);
    }
    o_forceinline static void remember(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        default_resetter<short>::remember(a_pType, (short const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        default_resetter<short>::reset(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct resetter
///
/// \brief  Resetter. (see instance creation process)
/// 		Used to remember the state of an object at a time 'T' and reset it when desired
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct resetter : public default_resetter<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_resetter_h__