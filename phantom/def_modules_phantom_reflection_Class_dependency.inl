

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
    return detail::as_helper<t_Ty,boost::is_pointer<t_Ty>::value AND boost::is_pointer<t_ITy>::value>::apply(in);
}


template <typename t_Ty>
o_forceinline state::StateMachine* stateMachineOf(t_Ty* a_pPtr) 
{ 
    return a_pPtr->PHANTOM_CODEGEN_m_smdataptr->stateMachine(); 
}

o_forceinline state::StateMachine* stateMachineOf(void* a_pPtr, size_t a_uiLevel) 
{ 
    return classOf(a_pPtr, a_uiLevel)->getStateMachineCascade(); 
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

    template<typename t_Ty, boolean t_are_pointers>
    struct as_helper
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            reflection::Type* pDestType = reflection::detail::type_of_counter<o_NESTED_TYPE boost::remove_pointer<t_Ty>::type, o_read_compilation_counter>::object();
            if(pDestType AND pDestType->asClass())
            {
                const rtti_data& oi = rttiDataOf(in);
                
                return oi.isNull()
                    ? nullptr// If no rtti registered we cannot know how to cast, we return NULL which is safer than trying to cast
                    : static_cast<t_Ty>(oi.cast((reflection::Class*)pDestType));
            }
            return nullptr;
        }
    };

    template<typename t_Ty>
    struct as_helper<t_Ty, false>
    {
        template<typename t_ITy>
        static t_Ty apply(t_ITy in)
        {
            return in;
        }
    };

} // namespace detail

o_export inline const phantom::rtti_data&            rttiDataOf(void const* a_pThis, reflection::Class* a_pLayoutClass)
{
    static phantom::rtti_data null_info(0,0,0,0,0,0);
    phantom::Phantom::rtti_data_map::const_iterator found = phantom::Phantom::m_rtti_data_map->find(a_pThis);
    if(found != phantom::Phantom::m_rtti_data_map->end())
    {
        auto& levels = found->second;
        if(a_pLayoutClass)
        {
            for(auto it = levels.begin(); it != levels.end(); ++it)
            {
                if(it->layout_class == a_pLayoutClass) return *it;
            }
            for(auto it = levels.begin(); it != levels.end(); ++it)
            {
                if(it->object_class->isKindOf(a_pLayoutClass)) return *it;
            }
        }
        return levels[0];
    }
    return null_info;
}

template<typename t_Ty>
inline const phantom::rtti_data&            rttiDataOf(t_Ty const* a_pThis)
{
    return rttiDataOf(a_pThis, classOf<t_Ty>());
}

template<typename t_Ty>
inline reflection::Class*                   classOf(t_Ty const* a_pThis)
{
    return rttiDataOf(a_pThis, classOf<t_Ty>()).object_class;
}

o_namespace_end(phantom)


o_namespace_begin(phantom, extension, detail)


template<typename t_Ty>
inline void rtti_data_registrer_helper_<t_Ty, 0>::registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel)
{
    const rtti_data& rd = rttiDataOf(a_pThis, a_uiLevel);
    if(rd.isNull())
    {
        addRttiData(a_pThis, rtti_data(a_pBaseClass, (phantom::reflection::Class*)phantom::reflection::type_of<t_Ty>::object(), a_pBase, a_csac, a_dynamic_delete_func, a_uiLevel));
    }
    else
    {
        // The single case where the rtti layout could have been already registered is if the base address matched the current layout address
        o_assert(a_pThis == a_pBase);
    }
}

template<typename t_Ty>
void rtti_data_registrer_helper_<t_Ty, 0>::unregisterInfo(t_Ty* a_pThis, size_t a_uiLevel)
{
    const rtti_data& rd = rttiDataOf(a_pThis, a_uiLevel);
    if(!rd.isNull())
    {
        removeRttiData(a_pThis, a_uiLevel);
    }
}


template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->deserializeValue(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::serializeLayout(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask))
        pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
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
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
        pValueMember->serializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_serializer_helper<t_Ty, default_serializer_classtype>::deserializeLayout(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
{
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
            pValueMember->deserializeValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)
{
    super_class_resetter<t_Ty>::remember(a_pInstance, a_pOutBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isReset()) 
        pValueMember->rememberValue(a_pInstance, a_pOutBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)
{
    super_class_resetter<t_Ty>::reset(a_pInstance, a_pInBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
        if(pValueMember->isReset()) 
        pValueMember->resetValue(a_pInstance, a_pInBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::remember(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
{
    super_class_resetter<t_Ty>::remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = (*it);
        if(pValueMember->isReset())
        pValueMember->rememberValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
}

template <typename t_Ty>
void default_resetter_helper<t_Ty, default_resetter_classtype>::reset(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
{
    super_class_resetter<t_Ty>::reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    reflection::ClassType* pClass = classOf<t_Ty>();
    auto it = pClass->beginValueMembers();
    auto end = pClass->endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = (*it);
        if(pValueMember->isReset())
        pValueMember->resetValue(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
}



o_namespace_end(phantom, extension, detail)



o_namespace_begin(phantom, reflection, detail)

template<typename t_Ty, typename t_STy, int t_counter>
void super_class_adder<t_Ty, t_STy, t_counter>::apply(phantom::reflection::Class* a_pClass)
{
    enum { is_virtual_base_of = boost::is_virtual_base_of<t_STy,t_Ty>::value };
    o_static_assert_msg(!is_virtual_base_of, "phantom reflection system doesn't support virtual inheritance ... yet ... or never");
    t_Ty* pClass = reinterpret_cast<t_Ty*>((void*)1);
    t_STy* pSuperClass = static_cast<t_STy*>(pClass);
    phantom::uint uiOffset = reinterpret_cast<phantom::uint>(reinterpret_cast<void*>(pSuperClass))-1;
    a_pClass->addSuperClass(type_of_counter<t_STy, t_counter>::object(), uiOffset);
}

o_namespace_end(phantom, reflection, detail)
