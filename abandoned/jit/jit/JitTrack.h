#ifndef o_phantom_moon_JitTrack_h__
#define o_phantom_moon_JitTrack_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, state, jit), JitTrack);
/* *********************************************** */

o_namespace_begin(phantom, state, jit)

class o_jit_export JitTrack : public Track
{
    friend class JitState;
    friend class JitStateMachine;
public:
    JitTrack(const string& a_strName, bitfield modifiers)
        : Track(a_strName, modifiers)
    {
    }
    ~JitTrack(void) {}
    
    void copyHierarchy(JitStateMachine* a_pStateMachine, Track* a_pSourceTrack);
    
    void transit(jit_state_machine_data* smdataptr, JitState* a_pNextState);
    
    inline void enter(jit_state_machine_data* smdataptr);
    
    inline void update(jit_state_machine_data* smdataptr);
    
    inline void leave(jit_state_machine_data* smdataptr);


protected:
};

o_namespace_end(phantom, state, jit)

#include <phantom/state/jit/JitState.h>

o_namespace_begin(phantom, state, jit)
    inline void JitTrack::enter(jit_state_machine_data* smdataptr)
{
    o_Track_TraceEnter();
    JitState*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    JitState* pTransitState = smdataptr->transit_states[m_uiIndex];
    o_assert(rpCurrentState == NULL) ;
    if(pTransitState == NULL)
    {
        pTransitState = static_cast<JitState*>(m_States[0]);
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

inline void JitTrack::update(jit_state_machine_data* smdataptr)
{
    smdataptr->current_states[m_uiIndex]->update(smdataptr);
}

inline void JitTrack::leave(jit_state_machine_data* smdataptr)
{
    JitState*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    smdataptr->lock();
    rpCurrentState->leave(smdataptr);
    smdataptr->unlock();
    rpCurrentState = NULL;
    o_Track_TraceLeave();
}


o_namespace_end(phantom, state, jit)

#endif
