/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitStateMachine.h"
#include "JitState.h"
#include "JitTrack.h"
/* *********************************************** */
o_registerN((phantom, state, runtime), JitStateMachine);

o_namespace_begin(phantom, state, runtime)
    
State*  JitStateMachine::getCurrentState(void* a_pObject, const Track* a_pTrack) const 
{ 
    return JitStateMachine_smdataptr(a_pObject)->current_states[((const JitTrack*)a_pTrack)->m_uiIndex]; 
}

State*  JitStateMachine::getTransitState(void* a_pObject, const Track* a_pTrack) const 
{ 
    return JitStateMachine_smdataptr(a_pObject)->transit_states[((const JitTrack*)a_pTrack)->m_uiIndex]; 
}

void JitStateMachine::setup( StateMachine* a_pSuper )
{
    o_assert(m_Tracks.empty(), "Tracks have already been created, cannot inherit anymore");
    if(a_pSuper == nullptr) // No super state machine, we create a root track from scratch
    {
        setRootTrack(o_new(JitTrack)("Root", m_bfModifiers));
        return;
    }

    // duplicate states and tracks content
    size_t i = 0;
    size_t count = a_pSuper->getTrackCount();
    m_Tracks.resize(count);
    for(;i<count;++i)
    {
        Track* pSourceTrack = a_pSuper->getTrack(i);
        JitTrack* pNewTrack = o_new(JitTrack)(pSourceTrack->getName(), pSourceTrack->getModifiers());
        pNewTrack->m_uiIndex = i;
        pNewTrack->m_pOwner = this;
        m_Tracks[i] = pNewTrack;
    }
    i = 0;
    count = a_pSuper->getStateCount();
    m_States.resize(count);
    for(;i<count;++i)
    {
        State* pSourceState = a_pSuper->getState(i);
        JitState* pNewState = o_new(JitState)(pSourceState->getName(), pSourceState->getModifiers());
        pNewState->setEnterClosure(pSourceState->getEnterGenericMemberFunctionPointer());
        pNewState->setUpdateClosure(pSourceState->getUpdateGenericMemberFunctionPointer());
        pNewState->setLeaveClosure(pSourceState->getLeaveGenericMemberFunctionPointer());
        pNewState->m_uiIndex = i;
        pNewState->m_pOwner = this;
        m_States[i] = pNewState;
    }
    // copy state/track hierarchy recursively
    static_cast<JitTrack*>(getRootTrack())->copyHierarchy(this, a_pSuper->getRootTrack());
}

void JitStateMachine::initialize( void* a_pObject )
{
    jit_state_machine_data* smdataptr = JitStateMachine_smdataptr(a_pObject);
    if(smdataptr->state_machine == this)
    {
        smdataptr->flags &= ~jit_state_machine_data::e_Flag_Inactive;
        smdataptr->history_state = NULL;
        static_cast<JitTrack*>(m_Tracks[0])->enter(smdataptr);
    }
    else
    {
        smdataptr->state_machine->initialize(smdataptr->owner);
    }
}

void JitStateMachine::update( void* a_pObject )
{
    jit_state_machine_data* smdataptr = JitStateMachine_smdataptr(a_pObject);
    static_cast<JitTrack*>(m_Tracks[0])->update(smdataptr);
}

void JitStateMachine::terminate( void* a_pObject )
{
    jit_state_machine_data* smdataptr = JitStateMachine_smdataptr(a_pObject);
    // leave root track
    static_cast<JitTrack*>(m_Tracks[0])->leave(smdataptr);
    smdataptr->history_state = NULL;
    smdataptr->flags |= jit_state_machine_data::e_Flag_Inactive;
}

void JitStateMachine::postEvent( void* a_pObject, uint a_uiEventId )
{
    o_StateMachine_TracePostEvent(a_uiEventId);
    jit_state_machine_data*    smdataptr = JitStateMachine_smdataptr(a_pObject);
    queue(smdataptr, a_uiEventId);
    if(!smdataptr->isLocked())
    {
        solveQueuedTransitions(smdataptr);
    }
}

void JitStateMachine::solveTransitions( jit_state_machine_data* smdataptr, uint a_uiEventId )
{
    size_t count = m_Tracks.size();
    for(size_t i = 0; i < count; ++i)
    {
        State* pCurrentState = smdataptr->current_states[i];
        if(pCurrentState != nullptr) 
        {
            State* pTransitionState = smdataptr->state_machine->getTransitionState(smdataptr->current_states[i], a_uiEventId);
            if(pTransitionState != nullptr) 
            {
                o_StateMachine_TraceDispatchEvent(a_uiEventId);
                static_cast<JitTrack*>(pTransitionState->getParentTrack())->transit(smdataptr, static_cast<JitState*>(pTransitionState));
            }
        }
    }
}

void JitStateMachine::install( void* a_pObject ) const
{
    if(!m_bFinalized)
    {
        finalize();
    }
    jit_state_machine_data* data =  new (o_allocate(jit_state_machine_data)) jit_state_machine_data(a_pObject, (JitStateMachine*)this);
    JitStateMachine_smdataptr(a_pObject) = data;
}

void JitStateMachine::uninstall( void* a_pObject ) const
{
    jit_state_machine_data*& data_ptr_ref = JitStateMachine_smdataptr(a_pObject);
    o_assert(data_ptr_ref != nullptr, "state machine data not installed");
    data_ptr_ref->~jit_state_machine_data();
    o_deallocate(data_ptr_ref, jit_state_machine_data);
    data_ptr_ref = nullptr;
}

State*const* JitStateMachine::getTransitStates( void const* a_pObject ) const
{
    return (State*const*)JitStateMachine_smdataptr(a_pObject)->transit_states;
}

State*const* JitStateMachine::getCurrentStates( void const* a_pObject ) const
{
    return (State*const*)JitStateMachine_smdataptr(a_pObject)->current_states;
}

void JitStateMachine::finalize() const
{
    size_t i = 0;
    size_t count = getStateCount();
    for(;i<count;++i)
    {
        static_cast<JitState*>(m_States[i])->finalize();
    }
    m_bFinalized = true;
}


void JitStateMachine::solveQueuedTransitions( jit_state_machine_data* smdataptr )
{
    o_assert(!smdataptr->isLocked());
    for(int i = o__uint__state_machine_event_queue_size-smdataptr->event_queue_size
        ; i<o__uint__state_machine_event_queue_size; )
    {
        if(smdataptr->event_queue[i] != UCHAR_MAX)
        {
            uint8 event = smdataptr->event_queue[i];
            smdataptr->event_queue[i] = UCHAR_MAX; // clear event
            smdataptr->event_queue_size--;
            solveTransitions(smdataptr, event);
            o_assert(!smdataptr->isLocked());
            i = o__uint__state_machine_event_queue_size-smdataptr->event_queue_size; // restart from the beginning
        }
        else 
        {
            ++i; // continue
        }
    }
}

void JitStateMachine::queue( jit_state_machine_data* smdataptr, uint a_uiEventId )
{
    uint currentEventId = a_uiEventId;
    int i = o__uint__state_machine_event_queue_size;
    while(i--)
    {
        if(smdataptr->event_queue[i] == UCHAR_MAX) // free 
        {
            smdataptr->event_queue[i] = (uint8)currentEventId;
            smdataptr->event_queue_size++;
            o_StateMachine_TraceQueued(a_uiEventId);
            return;
        }
        else // occupied by another event for this track
        {
            uint event = smdataptr->event_queue[i];
            smdataptr->event_queue[i] = currentEventId; // clear event
            currentEventId = event;
        }
    }
    o_StateMachine_TraceQueued(a_uiEventId);
    o_StateMachine_TraceEventQueueFull(currentEventId);
}


o_namespace_end(phantom, state, runtime)