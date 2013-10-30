

o_namespace_begin(phantom)


inline void rtti_data::deleteNow(o_memory_stat_insert_parameters) const
{
    (*dynamic_delete_func)(const_cast<void*>(base) o_memory_stat_append_parameters_use);
}


template<typename t_Ty>
boolean        is(void*    in)
{
    if(in == NULL) return true;
    reflection::Class* pClass = phantom::classOf(in);
    return pClass ? pClass->isKindOf(typeOf<t_Ty>()) : false;
}


template<typename t_Ty, typename t_ITy>
t_Ty           as(t_ITy    in)
{
    return detail::as_helper<t_Ty,
        boost::is_pointer<t_Ty>::value
        AND is_reflected_class<typename boost::remove_pointer<t_Ty>::type>::value
    >::apply(in);
}


template <typename t_Ty>
o_forceinline state::StateMachine* stateMachineOf(t_Ty* a_pPtr) 
{ 
    return a_pPtr->PHANTOM_CODEGEN_m_smdataptr->stateMachine(); 
}

o_forceinline state::StateMachine* stateMachineOf(void* a_pPtr) 
{ 
    return classOf(a_pPtr)->getStateMachineCascade(); 
}

namespace detail {

    template<typename t_Ty, boolean t_is_reflected_class>
    struct is_helper
    {
        template<typename t_ITy>
        static boolean apply(t_ITy* in)
        {
            return boost::is_base_of<t_Ty, t_ITy>::value;
        }
    };

    template<typename t_Ty>
    struct is_helper<t_Ty, true>
    {
        static boolean apply(void* in)
        {
            return in == NULL
                ? true
                : phantom::classOf(in)->isKindOf(classOf<t_Ty>());
        }
    };

    template<typename t_Ty, boolean t_is_ptr_to_reflected_class>
    struct as_helper
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            return static_cast<t_Ty>(in);
        }
    };

    template<typename t_Ty>
    struct as_helper<t_Ty, true>
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            if(in)
            {
                const rtti_data& oi = rttiDataOf(in);
                return oi.isNull()
                    ? NULL // If no rtti registered we cannot know how to cast, we return NULL which is safer than trying to cast
                    : static_cast<t_Ty>(
                    oi.cast(classOf<o_NESTED_TYPE boost::remove_pointer<t_Ty>::type>())
                    );
            }
            return NULL;
        }
    };

} // namespace detail

o_namespace_end(phantom)


o_namespace_begin(phantom, extension, detail)


template<typename t_Ty>
inline void rtti_data_registrer_helper_<t_Ty, 0>::registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func)
{
    if(phantom::Phantom::m_rtti_data_map->find(a_pThis) == phantom::Phantom::m_rtti_data_map->end())
    {
        (*phantom::Phantom::m_rtti_data_map)[a_pThis] = phantom::rtti_data(a_pBaseClass, (phantom::reflection::Class*)phantom::reflection::type_of<t_Ty>::object(), a_pBase, a_csac, a_dynamic_delete_func);
    }
    else
    {
        // The single case where the rtti layout could have been already registered is if the base address matched the current layout address
        o_assert(a_pThis == a_pBase);
    }
}

template<typename t_Ty>
void rtti_data_registrer_helper_<t_Ty, 0>::unregisterInfo(t_Ty* a_pThis)
{
    phantom::Phantom::rtti_data_map::iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    if(found != phantom::Phantom::m_rtti_data_map->end())
    {
        phantom::Phantom::m_rtti_data_map->erase(found);
    }
}


template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->deserializeValue(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask))
        pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
            pValueMember->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    // If you have a compilation error here 
    // that probably means that a super class declared 
    // in a reflection declaration ( the class t_Ty ) hasn't
    // itself a reflection declared
    // v
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
            pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)
{
    super_class_resetter<t_Ty>::remember(a_pInstance, a_pOutBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isReset()) 
        pValueMember->rememberValue(a_pInstance, a_pOutBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)
{
    super_class_resetter<t_Ty>::reset(a_pInstance, a_pInBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isReset()) 
        pValueMember->resetValue(a_pInstance, a_pInBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::remember(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
{
    super_class_resetter<t_Ty>::remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isReset())
        pValueMember->rememberValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::reset(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
{
    super_class_resetter<t_Ty>::reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    reflection::ClassType::member_const_iterator it = pClass->valueMembersBegin();
    reflection::ClassType::member_const_iterator end = pClass->valueMembersEnd();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isReset())
        pValueMember->resetValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
}



o_namespace_end(phantom, extension, detail)



o_namespace_begin(phantom, reflection, detail)

template<typename t_Ty, typename t_STy>
void super_class_adder_<t_Ty, t_STy>::apply(phantom::reflection::Class* a_pClass)
{
    enum { is_virtual_base_of = boost::is_virtual_base_of<t_STy,t_Ty>::value };
    o_static_assert_msg(!is_virtual_base_of, "phantom reflection system doesn't support virtual inheritance yet");
    t_Ty* pClass = reinterpret_cast<t_Ty*>((void*)1);
    t_STy* pSuperClass = static_cast<t_STy*>(pClass);
    phantom::uint uiOffset = reinterpret_cast<phantom::uint>(reinterpret_cast<void*>(pSuperClass))-1;
    a_pClass->addSuperClass(classOf<t_STy>(), uiOffset);
}

o_namespace_end(phantom, reflection, detail)
