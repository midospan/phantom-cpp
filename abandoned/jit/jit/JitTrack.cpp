/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitTrack.h"
#include "JitTrack.hxx"
#include "JitState.h"
#include "JitStateMachine.h"
/* *********************************************** */
o_registerN((phantom, state, jit), JitTrack);

o_namespace_begin(phantom, state, jit)

void JitTrack::transit( jit_state_machine_data* smdataptr, JitState* a_pNextState )
{
    void* pObject = smdataptr->owner;
    JitState*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    JitState*& rpTransitState = smdataptr->transit_states[m_uiIndex]; 
    if(rpCurrentState == NULL) /// Track isn't active
    {
        if(m_pParentState) /// if it's not the root track
        {
            rpTransitState = a_pNextState;
            static_cast<JitTrack*>(
                static_cast<JitState*>(m_pParentState)->m_pParentTrack
                )->transit(smdataptr, static_cast<JitState*>(m_pParentState));
        }
        else /// the root track
        {
            rpTransitState = NULL;
            rpCurrentState = a_pNextState;
            smdataptr->lock();
            a_pNextState->enter(smdataptr);
            smdataptr->unlock();
        }
    }
    else
    {
        JitState* pPreviousState = rpCurrentState;
        rpTransitState = NULL;
        State*& rpHistoryState = smdataptr->history_state;
        rpHistoryState = a_pNextState;
        smdataptr->lock();
        pPreviousState->leave(smdataptr);
        rpCurrentState = a_pNextState;
        rpHistoryState = pPreviousState;
        a_pNextState->enter(smdataptr);
        smdataptr->unlock();
        rpHistoryState = a_pNextState;
    }
}

void JitTrack::copyHierarchy( JitStateMachine* a_pStateMachine, Track* a_pSourceTrack )
{
    size_t i = 0;
    size_t count = a_pSourceTrack->getStateCount();
    m_States.resize(count);
    for(;i<count;++i)
    {
        m_States[i] = a_pStateMachine->getState(a_pSourceTrack->getState(i)->getIndex());
        static_cast<JitState*>(m_States[i])->m_pParentTrack = this;
        static_cast<JitState*>(m_States[i])->copyHierarchy(a_pStateMachine, a_pSourceTrack->getState(i));
    }
}

o_namespace_end(phantom, state, jit)