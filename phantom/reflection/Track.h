/* TODO LICENCE HERE */

#ifndef state_Track_h__
#define state_Track_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Track : public StateMachineElement
{
    o_language_element;

    friend class State;
    friend class StateMachine;

    typedef vector<State*>    state_vector;

public:
    static reflection::Class* const metaType;

public:
    Track(const string& a_strName
        , uint a_uiSerializationMask
        , modifiers_t bf = 0)
            : StateMachineElement(a_strName, bf)
            , m_uiIndex(0xffffffff)
            , m_pParentState(NULL)
            , m_uiSerializationMask(a_uiSerializationMask)
    {

    }
    o_destructor ~Track(void);

    virtual Track* asTrack() const { return (Track*)this; }

    State*                  getCurrentState(void* a_pObject) const 
    {
        return getOwnerStateMachine()->getCurrentState(a_pObject, this);
    }
    State*                  getTransitState(void* a_pObject) const 
    {
        return getOwnerStateMachine()->getTransitState(a_pObject, this);
    }

    boolean                 isEmpty() const { return m_States.empty(); }

    boolean                 isActive(void* a_pObject) const { return getOwnerStateMachine()->isTrackActive(a_pObject, this); }

    State*                  getInitialState() const {     return isEmpty() ? NULL : m_States[0]; }


    state_vector::const_iterator beginStates() const { return m_States.begin(); }
    state_vector::const_iterator endStates() const { return m_States.end(); }

    void                    addState(State* a_pState);
    State*                  getParentState() const { return m_pParentState; }
    int                     getStateIndex(const State* a_pState);
    State*                  getState(const string& a_strName) const;
    State*                  getState(uint i) const { return m_States[i]; }
    uint                    getStateCount() const { return m_States.size(); }
    size_t                  getIndex() const { return m_uiIndex; }

    void                    getCurrentStatesCascade(void* a_pObject, vector<State*>& out) const;

    void                    getTrackCountCascade(uint& a_count) const;

    State*                  getStateCascade(const string& a_strName) const;

    int                     getLevel() const;

    o_forceinline uint      getSerializationMask() const { return m_uiSerializationMask; }

    o_forceinline boolean   isSaved(uint a_uiSerializationFlag) const { return NOT(((m_Modifiers & o_transient) == o_transient)) AND ((m_uiSerializationMask & a_uiSerializationFlag) == a_uiSerializationFlag); }
    o_forceinline boolean   isReset() const { return ((m_Modifiers & o_reset) == o_reset); }
    o_forceinline boolean   isTransient() const { return ((m_Modifiers & o_transient) == o_transient); }

    void copyHierarchy(StateMachine* a_pStateMachine, Track* a_pSourceTrack);

    void transit(dynamic_state_machine_data* smdataptr, State* a_pNextState);

    inline void enter(dynamic_state_machine_data* smdataptr);

    inline void update(dynamic_state_machine_data* smdataptr);

    inline void leave(dynamic_state_machine_data* smdataptr);

protected:
    void                    setParentState(State* a_pState) { m_pParentState = a_pState; }

protected:
    state_vector            m_States;
    size_t                  m_uiIndex;
    State*                  m_pParentState;
    uint                    m_uiSerializationMask;
};

o_namespace_end(phantom, reflection)

#include <phantom/reflection/State.h>

o_namespace_begin(phantom, reflection)

inline void Track::enter(dynamic_state_machine_data* smdataptr)
{
    o_Track_TraceEnter();
    State*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    State* pTransitState = smdataptr->transit_states[m_uiIndex];
    o_assert(rpCurrentState == NULL) ;
    if(pTransitState == NULL)
    {
        pTransitState = static_cast<State*>(m_States[0]);
    }
    else
    {
        smdataptr->transit_states[m_uiIndex] = NULL;
    }
    rpCurrentState = pTransitState;
    smdataptr->lock();
    pTransitState->enter(smdataptr);
    smdataptr->unlock();
}

inline void Track::update(dynamic_state_machine_data* smdataptr)
{
    smdataptr->current_states[m_uiIndex]->update(smdataptr);
}

inline void Track::leave(dynamic_state_machine_data* smdataptr)
{
    State*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    smdataptr->lock();
    rpCurrentState->leave(smdataptr);
    smdataptr->unlock();
    rpCurrentState = NULL;
    o_Track_TraceLeave();
}

o_namespace_end(phantom, reflection)



#endif
