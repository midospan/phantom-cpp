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

#ifndef state_RuntimeTrack_h__
#define state_RuntimeTrack_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "RuntimeTrack.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, state, Event)
o_declare(class, phantom, state, State)
/* *********************************************** */

o_h_begin

class o_export RuntimeTrack : public Track
{
    friend class RuntimeClass;
    friend class RuntimeState;
    friend class RuntimeTransition;
    friend class RuntimeStateMachine;

public:

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:
    
    RuntimeTrack(const string& a_strName 
        , size_t a_uiIndex
        , size_t a_uiTotalTrackCount
        , size_t a_uiStateMachineDataOffset
        , bitfield bf = bitfield())
            : Track(a_strName
            , a_uiIndex
            , bf)
            , m_uiCurrentStateIndex (a_uiIndex)
            , m_uiTransitStateIndex (m_uiCurrentStateIndex+a_uiTotalTrackCount)
            , m_uiHistoryStateIndex (2*a_uiTotalTrackCount)
            , m_uiStateMachineDataOffset(a_uiStateMachineDataOffset)
    {

    }
    o_destructor ~RuntimeTrack(void) {}
    
    boolean transit(void* a_pObject, RuntimeState* a_pNextState);
    
    void enter(void* a_pObject);
    void update(void* a_pObject);
    void leave(void* a_pObject);

    State* handleEvent(void* a_pObject, Event* a_pEvent);

    void solveTransitions(void* a_pObject);
    void setup(void* a_pObject);

protected:
    size_t    m_uiStateMachineDataOffset;
    size_t    m_uiCurrentStateIndex;
    size_t    m_uiTransitStateIndex;
    size_t    m_uiHistoryStateIndex;

};

o_h_end


#else // state_RuntimeTrack_h__
#include "RuntimeTrack.classdef.h"
#endif
