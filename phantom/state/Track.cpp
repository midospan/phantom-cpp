/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/state/StateOrderingComparator.h>
#include "Track.h"
#include "Track.hxx"
#include "phantom/reflection/Compiler.h"
/* *********************************************** */
o_registerN((phantom, state), Track);

o_namespace_begin(phantom, state) 

reflection::Class* const Track::metaType = o_type_of(phantom::state::Track);

Track::~Track( void )
{
}

void Track::addState( State* a_pState )
{
    a_pState->m_uiKey = (m_uiIndex<<16) | m_States.size(); 
    a_pState->m_uiIndexInTrack = m_States.size();
    m_States.push_back(a_pState);
    a_pState->m_pParentTrack = this;
    getOwnerStateMachine()->registerState(a_pState);
#ifdef _DEBUG
    // To be sure that we add the states in the order they are declared, if not, need to check the code design...
    StateOrderingComparator comparator;
    vector<State*> debug_states = m_States;
    std::sort(m_States.begin(),m_States.end(),StateOrderingComparator::std_adapter(&comparator));
    o_assert(debug_states == m_States);
#endif
}

State* Track::getState( const string& a_strName ) const
{
    o_foreach(State* pState, m_States)
    {
        if(pState->getName() == a_strName) return pState;
    }
    return NULL;
}

int Track::getStateIndex( const State* a_pState )
{
    uint i = 0;
    uint count = m_States.size();
    for (;i<count;++i)
    {
        if(m_States[0] == a_pState) return (int)i;
    }
    return -1;
}

void Track::getCurrentStatesCascade( void* a_pObject, vector<State*>& out ) const
{
    State* pState = getCurrentState(a_pObject);
    if(pState == NULL) return;
    out.push_back(pState);
    uint i = 0;
    uint count = pState->getTrackCount();
    for(;i<count;++i)
    {
        pState->getTrack(i)->getCurrentStatesCascade(a_pObject, out);
    }
}

void Track::getTrackCountCascade( uint& a_count ) const
{
    o_foreach(State* pState, m_States)
    {
        a_count += pState->m_Tracks.size();
        o_foreach(Track* pTrack, pState->m_Tracks)
        {
            pTrack->getTrackCountCascade(a_count);
        }
    }
}

State* Track::getStateCascade( const string& a_strName ) const
{
    o_foreach(State* pState, m_States)
    {
        if(pState->getName() == a_strName)
        {
            return pState;
        }
        o_foreach(Track* pTrack, pState->m_Tracks)
        {
            State* pState = pTrack->getStateCascade(a_strName);
            if(pState) return pState;
        }
    }
    return NULL;
}

int Track::getLevel() const
{
  return m_pParentState 
    ? m_pParentState->getLevel() + 1 
    : 0;
}

void Track::transit( dynamic_state_machine_data* smdataptr, State* a_pNextState )
{
    void* pObject = smdataptr->owner;
    State*& rpCurrentState = smdataptr->current_states[m_uiIndex];
    State*& rpTransitState = smdataptr->transit_states[m_uiIndex]; 
    if(rpCurrentState == NULL) /// Track isn't active
    {
        if(m_pParentState) /// if it's not the root track
        {
            rpTransitState = a_pNextState;
            static_cast<Track*>(
                static_cast<State*>(m_pParentState)->m_pParentTrack
                )->transit(smdataptr, static_cast<State*>(m_pParentState));
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
        State* pPreviousState = rpCurrentState;
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

void Track::copyHierarchy( StateMachine* a_pStateMachine, Track* a_pSourceTrack )
{
    size_t i = 0;
    size_t count = a_pSourceTrack->getStateCount();
    m_States.resize(count);
    for(;i<count;++i)
    {
        m_States[i] = a_pStateMachine->getState(a_pSourceTrack->getState(i)->getIndex());
        static_cast<State*>(m_States[i])->m_pParentTrack = this;
        static_cast<State*>(m_States[i])->copyHierarchy(a_pStateMachine, a_pSourceTrack->getState(i));
    }
}

variant Track::compile( reflection::Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

o_namespace_end(phantom, state)
