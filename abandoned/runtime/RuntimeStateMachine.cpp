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
/* ** The Class Header must be the last #include * */
#include "RuntimeStateMachine.h"
/* *********************************************** */

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

RuntimeStateMachine::RuntimeStateMachine( size_t a_uiEventQueueOffset 
, size_t a_uiEventQueuePointerOffset
, size_t a_uiHistoryStateOffset
, bitfield bf) 
: m_uiEventQueueOffset(a_uiEventQueueOffset)
, m_uiEventQueuePointerOffset(a_uiEventQueuePointerOffset)
, m_uiHistoryStateOffset(a_uiHistoryStateOffset)
{

}

void RuntimeStateMachine::initialize( Object* a_pObject )
{
    *reinterpret_cast<RuntimeState**>(reinterpret_cast<byte*>(a_pObject)+m_uiHistoryStateOffset) = NULL;
    *reinterpret_cast<int32*>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueuePointerOffset) = -1;
    dispatchQueuedEvents(a_pObject);
    static_cast<RuntimeTrack*>(m_Tracks[0])->enter(a_pObject);
}

void RuntimeStateMachine::update( Object* a_pObject )
{
    o_assert(false, "not working");
    //a_pObject->setNativeFlag(eNativeFlag_UpdatingStateMachine, true);

    //a_pObject->setNativeFlag(eNativeFlag_DispatchingStateEvents, true);
    dispatchQueuedEvents(a_pObject);
    static_cast<RuntimeTrack*>(m_Tracks[0])->solveTransitions(a_pObject);
    //a_pObject->setNativeFlag(eNativeFlag_DispatchingStateEvents, false);

    static_cast<RuntimeTrack*>(m_Tracks[0])->update(a_pObject);

    //a_pObject->setNativeFlag(eNativeFlag_UpdatingStateMachine, false);
}

void RuntimeStateMachine::terminate( Object* a_pObject )
{
    static_cast<RuntimeTrack*>(m_Tracks[0])->leave(a_pObject);
    *reinterpret_cast<int32*>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueuePointerOffset) = -1;
    *reinterpret_cast<RuntimeState**>(reinterpret_cast<byte*>(a_pObject)+m_uiHistoryStateOffset) = NULL;
}

void RuntimeStateMachine::postEvent( Object* a_pObject, Event* a_pEvent )
{
    o_error(false, "not implemented");
    if(NOT(isQueued(a_pObject, a_pEvent)))
    {
        //if(a_pObject->testNativeFlags(eNativeFlag_UpdatingStateMachine))
        {
            int32& ptr = *reinterpret_cast<int32*>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueuePointerOffset);
            o_assert(ptr < eEventQueueSize);
            (*reinterpret_cast<Event***>(reinterpret_cast<byte*>(a_pObject)+m_uiEventQueueOffset))[++ptr] = a_pEvent;
        }
        //else
        {
            dispatchEvent(a_pObject, a_pEvent);
            static_cast<RuntimeTrack*>(m_Tracks[0])->solveTransitions(a_pObject);
        }
    }
}

void RuntimeStateMachine::setup( Object* a_pObject )
{
    static_cast<RuntimeTrack*>(m_Tracks[0])->setup(a_pObject);
}

o_cpp_end
