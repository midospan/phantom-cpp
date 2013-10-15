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

#ifndef state_Track_h__
#define state_Track_h__



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Track.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export Track : public StateMachineElement
{
    friend class State;
    friend class StateMachine;

    typedef vector<State*>    StateVector;

public:

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    Track(const string& a_strName
        , uint a_uiSerializationMask
        , bitfield bf = bitfield())
            : StateMachineElement(a_strName, bf)
            , m_uiIndex(0xffffffff)
            , m_pParentState(NULL)
            , m_uiSerializationMask(a_uiSerializationMask)
    {

    }
    o_destructor ~Track(void);

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

    o_forceinline boolean   isSaved(uint a_uiSerializationFlag) const { return NOT(m_bfModifiers.matchesMask(o_transient)) AND ((m_uiSerializationMask & a_uiSerializationFlag) == a_uiSerializationFlag); }
    o_forceinline boolean   isReset() const { return m_bfModifiers.matchesMask(o_reset); }
    o_forceinline boolean   isTransient() const { return m_bfModifiers.matchesMask(o_transient); }
        
protected:
    void                    setParentState(State* a_pState) { m_pParentState = a_pState; }

protected:
    vector<State*>          m_States;
    size_t                  m_uiIndex;
    State*                  m_pParentState;
    uint                    m_uiSerializationMask;
};

o_h_end


#else // state_Track_h__
#include "Track.classdef.h"
#endif
