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

#ifndef state_StateMachine_h__
#define state_StateMachine_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "StateMachine.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export StateMachine : public reflection::LanguageElement
{
    typedef list<Event*>        EventQueue;
    typedef map<uint, Event*>   EventMap;

    friend class State;
    friend class Track;
    friend class reflection::Class;

public:
    enum
    {
        eMaxDispatchingEventPass = 1,
        eEventQueueSize = 16,
    };
    static reflection::Signature*        StateMemberFunctionSignature();
    static reflection::Signature*        StateSignalSignature()
    {
        return StateMemberFunctionSignature();
    }

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    StateMachine(bitfield a_Modifiers = 0);
    o_destructor ~StateMachine(void);

    reflection::Class*    getOwnerClass() const { return static_cast<reflection::Class*>(m_pOwner); }

    virtual void    install(void* a_pObject) const = 0;
    virtual void    uninstall(void* a_pObject) const = 0;
    virtual void    initialize(void* a_pObject) = 0;
    virtual void    update(void* a_pObject) = 0;
    virtual void    reset(void* a_pObject)
    {
        terminate(a_pObject);
        initialize(a_pObject);
    }
    virtual void    terminate(void* a_pObject) = 0;
    virtual void    postEvent(void* a_pObject, uint a_uiEventId) = 0;
    void            postRandomEvent(void* a_pObject, vector<uint>* eventIds = nullptr);
    template<typename t_EventTy>
    o_forceinline
    void            postEvent(void* a_pObject)
    {
        postEvent(a_pObject, t_EventTy::Id());
    }
    virtual State*const* getTransitStates(void const* a_pInstance) const = 0;
    virtual State*const* getCurrentStates(void const* a_pInstance) const = 0;
    virtual State**      getTransitStates(void * a_pInstance) const = 0;
    virtual State**      getCurrentStates(void * a_pInstance) const = 0;

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

    virtual size_t  getDataPtrOffset() const = 0;

    virtual base_state_machine_data* getInstanceData(void* a_pInstance) const = 0;
    
    inline void     addTransition(State* a_pSrcState, uint a_uiEventId, State* a_pDestState);
    inline State*   getTransitionState(State* a_pSrcState, uint a_uiEventId) const ;
    
    virtual State*  getCurrentState(void* a_pObject, const Track* a_pTrack) const = 0;
    virtual State*  getTransitState(void* a_pObject, const Track* a_pTrack) const = 0;
    
    boolean         isTrackActive(void* a_pObject, const Track* a_pTrack)
    {
        return getCurrentState(a_pObject, a_pTrack) != nullptr;
    }
    
protected:
    virtual void    registerTrack(Track* a_pTrack);
    virtual void    registerState(State* a_pState);

protected:
    typedef vector<Track*>              track_vector;
    typedef vector<string>              event_name_vector;
    typedef vector<State*>              state_vector;
    typedef map<string, uint>           event_id_map;
    typedef unordered_map<uint, uint> transition_map;

    reflection::Class*      m_pOwnerClass;
    track_vector            m_Tracks;
    state_vector            m_States;
    event_name_vector       m_EventNames;
    event_id_map            m_EventIds;
    transition_map          m_Transitions;
    uint                    m_uiTrackCount;
};

o_h_end

#include "phantom/state/Track.h"
#include "phantom/state/State.h"

inline phantom::state::State* phantom::state::StateMachine::getStateByKey( phantom::uint a_uiKey ) const
{
    return m_Tracks[a_uiKey>>16]->getState(a_uiKey&0xffff);
}
inline phantom::state::State* phantom::state::StateMachine::getSurrogateState( phantom::state::State* a_pState ) const
{
    return getState(a_pState->getKey());
}
inline phantom::state::Track* phantom::state::StateMachine::getSurrogateTrack( phantom::state::Track* a_pTrack ) const
{
    return getTrack(a_pTrack->getIndex());
}


void            phantom::state::StateMachine::addTransition(phantom::state::State* a_pSrcState, uint a_uiEventId, phantom::state::State* a_pDestState)
{
    m_Transitions[a_pSrcState->getIndex() | a_uiEventId << 16] = a_pDestState->getIndex();
}

phantom::state::State*          phantom::state::StateMachine::getTransitionState(phantom::state::State* a_pSrcState, uint a_uiEventId) const 
{
    auto found = m_Transitions.find(a_pSrcState->getIndex() | (a_uiEventId << 16));
    if(found != m_Transitions.end()) return m_States[found->second];
    return nullptr;
}

#else // state_StateMachine_h__
#include "StateMachine.classdef.h"
#endif
