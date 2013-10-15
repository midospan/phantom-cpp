
o_namespace_begin(phantom, state, detail)
    
template<typename t_Ty>
void state_machine_serializer<t_Ty>::serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const * a_pDataBase)
{
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State*const*    current_states  = pStateMachine->getCurrentStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            *reinterpret_cast<uint*>(a_pOutBuffer) = (*current_states++)->getIndexInTrack();
            a_pOutBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const * a_pDataBase)
{
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State**    transit_states = pStateMachine->getTransitStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            *transit_states++ = pTrack->getState(*reinterpret_cast<uint const*>(a_pInBuffer));
            a_pInBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
{ 
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State*const*    current_states = pStateMachine->getCurrentStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            State* pState = *current_states++;
            a_OutBranch.put<string>(pTrack->getName(), pState?pState->getName():"");
        }
    }
}

template<typename t_Ty>
void state_machine_serializer<t_Ty>::deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
{ 
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State**    transit_states = pStateMachine->getTransitStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isSaved(a_uiSerializationMask))
        {
            const boost::optional<string>& a_opt_strStateName = a_InBranch.get_optional<string>(pTrack->getName());
            const string& a_strStateName = a_opt_strStateName.get_value_or("");
            *transit_states++ = a_strStateName.empty() ? NULL : pTrack->getState(a_strStateName);
        }
    }
}


template<typename t_Ty>
void state_machine_resetter<t_Ty>::remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)
{
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State*const*    current_states  = pStateMachine->getCurrentStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isReset())
        {
            *reinterpret_cast<uint*>(a_pOutBuffer) = (*current_states++)->getIndexInTrack();
            a_pOutBuffer += sizeof(uint);
        }
    }
}

template<typename t_Ty>
void state_machine_resetter<t_Ty>::reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)
{
    StateMachine* pStateMachine = a_pInstance->PHANTOM_CODEGEN_m_smdataptr->stateMachine();
    State**    transit_states = pStateMachine->getTransitStates(a_pInstance);
    uint i = 0;
    uint count = pStateMachine->getTrackCount();
    for(;i<count;++i)
    {
        Track*  pTrack = pStateMachine->getTrack(i);
        if(pTrack->isReset())
        {
            *transit_states++ = pTrack->getState(*reinterpret_cast<uint const*>(a_pInBuffer));
            a_pInBuffer += sizeof(uint);
        }
        else
        {
            // if not savec, we reset to the initial state (the first declared in the track)
            *transit_states++ = pTrack->getInitialState();
        }
    }
}
o_namespace_end(phantom, state, detail)


o_namespace_begin(phantom, state)

o_forceinline void          base_state_machine_data::initialize() const { state_machine->initialize(owner); }
o_forceinline void          base_state_machine_data::terminate() const { state_machine->terminate(owner); }
o_forceinline void          base_state_machine_data::update() const { state_machine->update(owner); }
o_forceinline void          base_state_machine_data::reset() const { state_machine->reset(owner); }
o_forceinline void          base_state_machine_data::postEvent(uint a_uiEventId) const { state_machine->postEvent(owner, a_uiEventId); }

o_namespace_end(phantom, state)