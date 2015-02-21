/* TODO LICENCE HERE */

#ifndef state_StateMachine_h__
#define state_StateMachine_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom)

#define o_dynamic_smdataptr(a_pObject) (*((phantom::dynamic_state_machine_data**)((byte*)a_pObject + m_pCompilationData->m_uiDataPtrOffset)))

struct dynamic_state_machine_data : base_state_machine_data
{
    friend class phantom::reflection::StateMachine;
    friend class phantom::reflection::State;
    friend class phantom::reflection::Track;

    dynamic_state_machine_data(void* a_pOwner, reflection::StateMachine* a_pSM);
    ~dynamic_state_machine_data();
    reflection::State**  current_states;
    reflection::State**  transit_states;
};

o_namespace_end(phantom)

o_namespace_begin(phantom, reflection)

struct state_machine_compilation_data
{
    state_machine_compilation_data() : m_uiDataSize(0), m_uiDataPtrOffset(0), m_bCompiled(false) {}
    /// JIT
    size_t m_uiDataSize;
    size_t m_uiDataPtrOffset;
    bool m_bCompiled;
};

class o_export StateMachine : public NamedElement
{    
    o_language_element;

    typedef list<Event*>        EventQueue;
    typedef map<uint, Event*>   EventMap;

    friend class State;
    friend class Track;
    friend class Class;
    friend class base_state_machine_data;
    friend struct dynamic_state_machine_data;

public:
    static Class* const metaType;

public:
    enum
    {
        eMaxDispatchingEventPass = 1,
        eEventQueueSize = 16,
    };
    static Signature*        StateMemberFunctionSignature();
    static Signature*        StateSignalSignature()
    {
        return StateMemberFunctionSignature();
    }

public:
    StateMachine(modifiers_t a_Modifiers = 0);
    o_destructor ~StateMachine(void);

    virtual StateMachine* asStateMachine() const { return (StateMachine*)this; }
    Class*    getOwnerClass() const { return static_cast<Class*>(m_pOwner); }

    virtual void    install(void* a_pObject) const;
    virtual void    uninstall(void* a_pObject) const;
    
    void            postRandomEvent(void* a_pObject, vector<uint>* eventIds = nullptr);
    template<typename t_EventTy>
    o_forceinline
    void            postEvent(void* a_pObject)
    {
        postEvent(a_pObject, t_EventTy::Id());
    }
    void            postEvent(void* a_pInstance, const string& a_strName) { postEvent(a_pInstance, getEventId(a_strName)); }

    virtual State*const* getTransitStates(void const* a_pInstance) const;
    virtual State*const* getCurrentStates(void const* a_pInstance) const;
    virtual State**      getTransitStates(void * a_pInstance) const;
    virtual State**      getCurrentStates(void * a_pInstance) const;

    Track*          getRootTrack() const { return m_Tracks[0]; }
    void            setRootTrack(Track* a_pRootTrack);
    Track*          getTrack(const string& a_strName) const;
    State*          getState(const string& a_strName) const;
    uint            getEventId(const string& a_strName) const;
    const string&   getEventName(uint a_uiId) const;
    uint            addEvent(const string& name);
    size_t          getEventCount() const { return m_EventNames.size(); }
    Track*          getTrack(uint i) const { return m_Tracks[i]; }
    uint            getTrackCount() const { return m_Tracks.size(); }
    State*          getState(uint i) const { return m_States[i]; }
    uint            getStateCount() const { return m_States.size(); }

    inline State*   getStateByKey(uint a_uiKey) const;

    State*          getSurrogateState(State* a_pState) const;
    Track*          getSurrogateTrack(Track* a_pTrack) const;

    virtual base_state_machine_data* getInstanceData(void* a_pInstance) const
    {
        return o_dynamic_smdataptr(a_pInstance);
    }
    
    inline void     addTransition(State* a_pSrcState, uint a_uiEventId, State* a_pDestState);
    inline State*   getTransitionState(State* a_pSrcState, uint a_uiEventId) const ;
    
    virtual State*  getCurrentState(void* a_pObject, const Track* a_pTrack) const;
    virtual State*  getTransitState(void* a_pObject, const Track* a_pTrack) const;
    
    boolean         isTrackActive(void* a_pObject, const Track* a_pTrack)
    {
        return getCurrentState(a_pObject, a_pTrack) != nullptr;
    }

    /// JIT 

    inline size_t getDataSize() const { o_assert(m_pCompilationData); return m_pCompilationData->m_uiDataSize; }

    virtual size_t  getDataPtrOffset() const { o_assert(m_pCompilationData); return m_pCompilationData->m_uiDataPtrOffset; }

    // Internal methods
    void    solveQueuedTransitions(dynamic_state_machine_data* smdataptr);
    void    solveTransitions( dynamic_state_machine_data* smdataptr, uint a_uiEventId );
    void    queue(dynamic_state_machine_data* smdataptr, uint a_uiEventId);
    virtual void    setup( StateMachine* a_pBase );

protected:
    void setDataPtrOffset(size_t offset)
    {
        o_assert(m_pCompilationData);
        m_pCompilationData->m_uiDataPtrOffset = offset;
    }
    
protected:
    virtual void    initialize(void* a_pObject) ;
    virtual void    update(void* a_pObject) ;
    virtual void    reset(void* a_pObject)
    {
        terminate(a_pObject);
        initialize(a_pObject);
    }
    virtual void    terminate(void* a_pObject);
    virtual void    postEvent(void* a_pObject, uint a_uiEventId);
    virtual void    queueEvent(void* a_pObject, uint a_uiEventId);
    virtual void    registerTrack(Track* a_pTrack);
    virtual void    registerState(State* a_pState);

protected:
    typedef vector<Track*>              track_vector;
    typedef vector<string>              event_name_vector;
    typedef vector<State*>              state_vector;
    typedef map<string, uint>           event_id_map;
    typedef unordered_map<uint, uint> transition_map;

    Class*      m_pOwnerClass;
    track_vector            m_Tracks;
    state_vector            m_States;
    event_name_vector       m_EventNames;
    event_id_map            m_EventIds;
    transition_map          m_Transitions;
    uint                    m_uiTrackCount;
    state_machine_compilation_data* m_pCompilationData;

};

o_namespace_end(phantom, reflection)

#include "phantom/reflection/Track.h"
#include "phantom/reflection/State.h"

inline phantom::reflection::State* phantom::reflection::StateMachine::getStateByKey( phantom::uint a_uiKey ) const
{
    return m_Tracks[a_uiKey>>16]->getState(a_uiKey&0xffff);
}
inline phantom::reflection::State* phantom::reflection::StateMachine::getSurrogateState( phantom::reflection::State* a_pState ) const
{
    return getState(a_pState->getKey());
}
inline phantom::reflection::Track* phantom::reflection::StateMachine::getSurrogateTrack( phantom::reflection::Track* a_pTrack ) const
{
    return getTrack(a_pTrack->getIndex());
}


void            phantom::reflection::StateMachine::addTransition(phantom::reflection::State* a_pSrcState, uint a_uiEventId, phantom::reflection::State* a_pDestState)
{
    m_Transitions[a_pSrcState->getIndex() | a_uiEventId << 16] = a_pDestState->getIndex();
}

phantom::reflection::State*          phantom::reflection::StateMachine::getTransitionState(phantom::reflection::State* a_pSrcState, uint a_uiEventId) const 
{
    auto found = m_Transitions.find(a_pSrcState->getIndex() | (a_uiEventId << 16));
    if(found != m_Transitions.end()) return m_States[found->second];
    return nullptr;
}


#endif
