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

#ifndef state_runtime_RuntimeStateMachine_h__
#define state_runtime_RuntimeStateMachine_h__



/* ****************** Includes ******************* */
#include <phantom/state/StateMachine.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "RuntimeStateMachine.classdef.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_h_begin

class o_export RuntimeStateMachine : public StateMachine
{
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

    friend class RuntimeClass;
    friend class RuntimeState;
    friend class RuntimeTrack;

public:    
    RuntimeStateMachine(size_t a_uiEventQueueOffset
        , size_t a_uiEventQueuePointerOffset
        , size_t a_uiHistoryStateOffset
        , bitfield bf = bitfield());
    o_destructor ~RuntimeStateMachine(void) {}

    void                    initialize()
    {
        StateMachine::initialize();
    }

    void                    terminate()
    {
        StateMachine::terminate();
    }

    /// The basic UML behavior to redefine in derived classes
    virtual void            initialize(Object* a_pObject);
    virtual void            update(Object* a_pObject);
    virtual void            terminate(Object* a_pObject);
    virtual void            postEvent( Object* a_pObject, Event* a_pEvent );
    virtual void            setup(Object* a_pObject);

    virtual size_t            getEventQueueOffset() const { return m_uiEventQueueOffset; }
    virtual size_t            getEventQueuePointerOffset() const { return m_uiEventQueuePointerOffset; }

    boolean    isQueued( Object* a_pObject, Event* a_pEvent )
    {
        Event** ppEvents = *reinterpret_cast<Event***>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueueOffset);
        int32& ptr = *reinterpret_cast<int32*>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueuePointerOffset);
        int32 i = 0;
        for(;i<=ptr;++i)
        {
            if(ppEvents[i]->getId() == a_pEvent->getId()) return true;
        }
        return false;
    }

    void dispatchQueuedEvents( Object* a_pObject )
    {
        Event** ppEvents = reinterpret_cast<Event**>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueueOffset);
        int32& ptr = *reinterpret_cast<int32*>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueuePointerOffset);
        if(ptr < 0) return;
        int32 i = 0;
        for(;i<=ptr;++i)
        {
            dispatchEvent(a_pObject, ppEvents[i]);
        }
        ptr = -1;
    }

    void    dispatchEvent( Object* a_pObject, Event* a_pEvent )
    {
        if(m_Tracks.empty()) return;
        State*    reactiveStates[eMaxDispatchingEventPass];
        int32 pass = 0;
        while(    (pass < eMaxDispatchingEventPass) )
        {
            State* pReactiveState = static_cast<RuntimeTrack*>(m_Tracks[0])->handleEvent(a_pObject, a_pEvent);
            if(pReactiveState == NULL) 
            {
                return;
            }
            int32 i = 0;
            for(;i<pass;++i)
            {
                if(pReactiveState == reactiveStates[i]) 
                {
                    // The same state has reacted to the same event
                    return;
                }
            }
            reactiveStates[pass++] = pReactiveState;
        }
    }

protected:
    uint                    m_uiMostDerivedTrackCount;
    size_t                    m_uiTransitStateOffset;
    size_t                    m_uiEventQueueOffset;
    size_t                    m_uiEventQueuePointerOffset;
    size_t                    m_uiHistoryStateOffset;
};

o_h_end


#else // state_runtime_RuntimeStateMachine_h__
#include "RuntimeStateMachine.classdef.h"
#endif
