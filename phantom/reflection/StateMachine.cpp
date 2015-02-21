/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "StateMachine.h"
#include "StateMachine.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), StateMachine);

o_namespace_begin(phantom, reflection) 

Class* const StateMachine::metaType = o_type_of(StateMachine);

StateMachine::StateMachine( modifiers_t a_Modifiers )
    : NamedElement("", a_Modifiers)
    , m_uiTrackCount(0) 
    , m_pCompilationData(nullptr)
{
    if((a_Modifiers & o_native) == 0)
    {
        m_pCompilationData = new state_machine_compilation_data;
    }
}

StateMachine::~StateMachine( void )
{
    delete m_pCompilationData;
}

uint StateMachine::addEvent( const string& name )
{
    o_assert(getEventId(name) == 0xffffffff, "An event with the same name already exists");
    uint id = m_EventNames.size();
    m_EventNames.push_back(name);
    m_EventIds[name] = id;
    return id;
}

const string& StateMachine::getEventName( uint a_uiId ) const
{
    return m_EventNames[a_uiId];
}

void StateMachine::setRootTrack( Track* a_pRootTrack )
{
    o_assert(m_Tracks.empty());
    registerTrack(a_pRootTrack);
    a_pRootTrack->getTrackCountCascade(m_uiTrackCount);
}

Track* StateMachine::getTrack( const string& a_strName ) const
{
    o_foreach(Track* pTrack, m_Tracks)
    {
        if(pTrack->getName() == a_strName) return pTrack;
    }
    return NULL;
}

State* StateMachine::getState( const string& a_strName ) const
{
    o_foreach(State* pState, m_States)
    {
        if(pState->getName() == a_strName) return pState;
    }
    return NULL;
}

uint StateMachine::getEventId( const string& a_strName ) const
{
    auto found = m_EventIds.find(a_strName);
    if(found != m_EventIds.end()) return found->second;
    return 0xffffffff;
}

Signature* StateMachine::StateMemberFunctionSignature()
{
    static Signature*    s_Value = NULL;
    if(s_Value == NULL)
    {
        s_Value = o_new(Signature)();
        s_Value->parse(o_CS("void()"));
        s_Value->setShared();
    }
    return s_Value;
}

void StateMachine::registerTrack( Track* a_pTrack )
{
    if(m_pCompilationData->m_bCompiled)
    {
        o_exception(std::exception, "The reflection machine is compiled, you cannot add any more reflection or tracks");
    }
    o_assert(getTrack(a_pTrack->getName()) == NULL);
    addElement(a_pTrack);
    a_pTrack->m_uiIndex = m_Tracks.size();
    m_Tracks.push_back(a_pTrack);
}

void StateMachine::registerState( State* a_pState )
{
    if(m_pCompilationData->m_bCompiled)
    {
        o_exception(std::exception, "The reflection machine is compiled, you cannot add any more reflection or tracks");
    }
    o_assert(getState(a_pState->getName()) == NULL);
    addElement(a_pState);
    a_pState->m_uiIndex = m_States.size();
    m_States.push_back(a_pState);
}

void StateMachine::postRandomEvent( void* a_pObject, vector<uint>* eventIds /*= nullptr*/ )
{
    float randRatio = ((float)(rand())) / RAND_MAX ;
    if(randRatio == 1.f) 
        randRatio = 0.999f;
    if(eventIds)
    {
        float r = eventIds->size() * randRatio;
        uint id = (*eventIds)[(uint)r];
        o_assert(id < m_EventIds.size());
        postEvent(a_pObject, id);
    }
    else 
    {
        float r = m_EventIds.size() * randRatio;
        postEvent(a_pObject, (uint)r);
    }
}

/// JIT

State*  StateMachine::getCurrentState(void* a_pObject, const Track* a_pTrack) const 
{ 
    o_assert(m_pCompilationData);
    return o_dynamic_smdataptr(a_pObject)->current_states[((const Track*)a_pTrack)->m_uiIndex]; 
}

State*  StateMachine::getTransitState(void* a_pObject, const Track* a_pTrack) const 
{ 
    o_assert(m_pCompilationData);
    return o_dynamic_smdataptr(a_pObject)->transit_states[((const Track*)a_pTrack)->m_uiIndex]; 
}

void StateMachine::setup( StateMachine* a_pBase )
{
    o_assert(m_pCompilationData);
    o_assert(m_Tracks.empty(), "Tracks have already been created, cannot inherit anymore");
    if(a_pBase == nullptr) // No base reflection machine, we create a root track from scratch
    {
        setRootTrack(o_new(Track)("Root", 0xffffffff, m_Modifiers));
        return;
    }

    // duplicate states and tracks content
    size_t i = 0;
    size_t count = a_pBase->getTrackCount();
    m_Tracks.resize(count);
    for(;i<count;++i)
    {
        Track* pSourceTrack = a_pBase->getTrack(i);
        Track* pNewTrack = o_new(Track)(pSourceTrack->getName(), pSourceTrack->getSerializationMask(), pSourceTrack->getModifiers());
        pNewTrack->m_uiIndex = i;
        pNewTrack->m_pOwner = this;
        m_Tracks[i] = pNewTrack;
    }
    i = 0;
    count = a_pBase->getStateCount();
    m_States.resize(count);
    for(;i<count;++i)
    {
        State* pSourceState = a_pBase->getState(i);
        State* pNewState = o_new(State)(pSourceState->getName(), pSourceState->getModifiers());
        pNewState->setEnterClosure(pSourceState->getEnterClosure());
        pNewState->setUpdateClosure(pSourceState->getUpdateClosure());
        pNewState->setLeaveClosure(pSourceState->getLeaveClosure());
        pNewState->m_uiIndex = i;
        pNewState->m_pOwner = this;
        m_States[i] = pNewState;
    }
    // copy reflection/track hierarchy recursively
    static_cast<Track*>(getRootTrack())->copyHierarchy(this, a_pBase->getRootTrack());
}

void StateMachine::initialize( void* a_pObject )
{
    o_assert(m_pCompilationData);
    dynamic_state_machine_data* smdataptr = o_dynamic_smdataptr(a_pObject);
    if(smdataptr->state_machine == this)
    {
        smdataptr->flags &= ~dynamic_state_machine_data::e_Flag_Inactive;
        smdataptr->history_state = NULL;
        static_cast<Track*>(m_Tracks[0])->enter(smdataptr);
    }
    else
    {
        smdataptr->initialize();
    }
}

void StateMachine::update( void* a_pObject )
{
    o_assert(m_pCompilationData);
    dynamic_state_machine_data* smdataptr = o_dynamic_smdataptr(a_pObject);
    if(!smdataptr->isLocked())
    {
        solveQueuedTransitions(smdataptr);
    }
    static_cast<Track*>(m_Tracks[0])->update(smdataptr);
    if(!smdataptr->isLocked())
    {
        solveQueuedTransitions(smdataptr);
    }
}

void StateMachine::terminate( void* a_pObject )
{
    o_assert(m_pCompilationData);
    dynamic_state_machine_data* smdataptr = o_dynamic_smdataptr(a_pObject);
    // leave root track
    static_cast<Track*>(m_Tracks[0])->leave(smdataptr);
    smdataptr->history_state = NULL;
    smdataptr->flags |= dynamic_state_machine_data::e_Flag_Inactive;
}

void StateMachine::postEvent( void* a_pObject, uint a_uiEventId )
{
    o_assert(m_pCompilationData);
    o_StateMachine_TracePostEvent(a_uiEventId);
    dynamic_state_machine_data*    smdataptr = o_dynamic_smdataptr(a_pObject);
    queue(smdataptr, a_uiEventId);
    if(!smdataptr->isLocked())
    {
        solveQueuedTransitions(smdataptr);
    }
}

void StateMachine::queueEvent( void* a_pObject, uint a_uiEventId )
{
    o_assert(m_pCompilationData);
    o_StateMachine_TracePostEvent(a_uiEventId);
    dynamic_state_machine_data*    smdataptr = o_dynamic_smdataptr(a_pObject);
    queue(smdataptr, a_uiEventId);
}

void StateMachine::solveTransitions( dynamic_state_machine_data* smdataptr, uint a_uiEventId )
{
    o_assert(m_pCompilationData);
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
                static_cast<Track*>(pTransitionState->getParentTrack())->transit(smdataptr, static_cast<State*>(pTransitionState));
            }
        }
    }
}

void StateMachine::install( void* a_pObject ) const
{
    o_assert(m_pCompilationData);
    o_assert(m_pCompilationData->m_bCompiled);
    dynamic_state_machine_data* data =  new (o_allocate(dynamic_state_machine_data)) dynamic_state_machine_data(a_pObject, (StateMachine*)this);
    o_dynamic_smdataptr(a_pObject) = data;
}

void StateMachine::uninstall( void* a_pObject ) const
{
    o_assert(m_pCompilationData);
    dynamic_state_machine_data*& data_ptr_ref = o_dynamic_smdataptr(a_pObject);
    o_assert(data_ptr_ref != nullptr, "reflection machine data not installed");
    data_ptr_ref->~dynamic_state_machine_data();
    o_deallocate(data_ptr_ref, dynamic_state_machine_data);
    data_ptr_ref = nullptr;
}

State*const* StateMachine::getTransitStates( void const* a_pObject ) const
{
    o_assert(m_pCompilationData);
    return (State*const*)o_dynamic_smdataptr(a_pObject)->transit_states;
}

State*const* StateMachine::getCurrentStates( void const* a_pObject ) const
{
    o_assert(m_pCompilationData);
    return (State*const*)o_dynamic_smdataptr(a_pObject)->current_states;
}

State** StateMachine::getTransitStates( void* a_pObject ) const
{
    o_assert(m_pCompilationData);
    return (State**)o_dynamic_smdataptr(a_pObject)->transit_states;
}

State** StateMachine::getCurrentStates( void* a_pObject ) const
{
    o_assert(m_pCompilationData);
    return (State**)o_dynamic_smdataptr(a_pObject)->current_states;
}

void StateMachine::solveQueuedTransitions( dynamic_state_machine_data* smdataptr )
{
    o_assert(m_pCompilationData);
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

void StateMachine::queue( dynamic_state_machine_data* smdataptr, uint a_uiEventId )
{
    o_assert(m_pCompilationData);
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

o_namespace_end(phantom, reflection)

o_namespace_begin(phantom)

dynamic_state_machine_data::dynamic_state_machine_data( void* a_pOwner, reflection::StateMachine* a_pSM ) :  base_state_machine_data(a_pOwner, a_pSM)
{
    current_states = o_allocate_n(state_machine->getTrackCount(), reflection::State*);
    memset(current_states, 0, state_machine->getTrackCount()*sizeof(void*));
    transit_states = o_allocate_n(state_machine->getTrackCount(), reflection::State*);
    memset(transit_states, 0, state_machine->getTrackCount()*sizeof(void*));
}

dynamic_state_machine_data::~dynamic_state_machine_data()
{
    o_deallocate_n(current_states, state_machine->getTrackCount(), reflection::State*);
    o_deallocate_n(transit_states, state_machine->getTrackCount(), reflection::State*);
}

o_namespace_end(phantom)