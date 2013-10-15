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
#include "phantom/def_runtime.h"
#include <phantom/state/StateOrderingComparator.h>
/* ** The Class Header must be the last #include * */
#include "RuntimeTrack.h"
/* *********************************************** */
o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

#define RuntimeTrack_statemachine_data(_object_) (*reinterpret_cast<State***>(reinterpret_cast<char*>(_object_)+m_uiStateMachineDataOffset))

boolean RuntimeTrack::transit( void* a_pObject, RuntimeState* a_pNextState )
{
    State*& rpCurrentState = RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex];
    State*& rpTransitState = RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex];
    State*& rpHistoryState = RuntimeTrack_statemachine_data(a_pObject)[m_uiHistoryStateIndex];
    RuntimeState* pPreviousState = static_cast<RuntimeState*>(rpCurrentState);
    if(pPreviousState == NULL) /// Track isn't active
    {
        if(m_pParentState) /// if it's not the root track
        {
            rpTransitState = a_pNextState;
            static_cast<RuntimeTrack*>(static_cast<RuntimeState*>(m_pParentState)->m_pParentTrack)->transit(a_pObject, static_cast<RuntimeState*>(m_pParentState));
        }
        else /// the root track
        {
            rpTransitState = NULL;
            rpCurrentState = a_pNextState;
            a_pNextState->enter(a_pObject);
        }
    }
    else 
    {
        rpTransitState = NULL;

        rpHistoryState = a_pNextState;
        pPreviousState->leave(a_pObject);
        rpCurrentState = a_pNextState;
        rpHistoryState = pPreviousState;
        a_pNextState->enter(a_pObject);
        rpHistoryState = a_pNextState;
    }
    return true;
}

void RuntimeTrack::enter( void* a_pObject )
{
    State*& rpCurrentState = RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex];
    State*& rpTransitState = RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex];
    RuntimeState* pTransitState = static_cast<RuntimeState*>(rpTransitState);
    o_assert(rpCurrentState == NULL) ;
    if(pTransitState == NULL)
    {
        pTransitState = static_cast<RuntimeState*>(m_States[0]);
    }
    else
    {
        rpTransitState = NULL;
    }

    rpCurrentState = pTransitState;
    pTransitState->enter(a_pObject);
}

void RuntimeTrack::leave( void* a_pObject )
{
    State*& rpCurrentState = RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex];
    State*& rpTransitState = RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex];

    RuntimeState* pCurrentState = static_cast<RuntimeState*>(rpCurrentState);
    pCurrentState->leave(a_pObject);
    rpCurrentState = NULL;
}

void RuntimeTrack::update( void* a_pObject )
{
    static_cast<RuntimeState*>(RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex])->update(a_pObject);
}

State* RuntimeTrack::handleEvent( void* a_pObject, Event* a_pEvent )
{
    return static_cast<RuntimeState*>(RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex])->handleEvent(a_pObject, a_pEvent);
}

void RuntimeTrack::solveTransitions( void* a_pObject )
{
    o_foreach(State* pState, m_States)
    {
        o_foreach(Track* pTrack, static_cast<RuntimeState*>(pState)->m_Tracks)
        {
            static_cast<RuntimeTrack*>(pTrack)->solveTransitions(a_pObject);
        }
    }
    if((RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex]) != NULL)
        static_cast<RuntimeState*>(RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex])->RuntimeState::activate(a_pObject);
}

void RuntimeTrack::setup( void* a_pObject )
{
    o_foreach(State* pState, m_States)
    {
        o_foreach(Track* pTrack, static_cast<RuntimeState*>(pState)->m_Tracks)
        {
            static_cast<RuntimeTrack*>(pTrack)->setup(a_pObject);
        }
    }
    (RuntimeTrack_statemachine_data(a_pObject)[m_uiCurrentStateIndex]) = 0;
    (RuntimeTrack_statemachine_data(a_pObject)[m_uiTransitStateIndex]) = 0;
}

#undef RuntimeTrack_statemachine_data

o_cpp_end