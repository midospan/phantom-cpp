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

#ifndef state_RuntimeState_h__
#define state_RuntimeState_h__



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "RuntimeState.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export RuntimeState : public State
{
    friend class RuntimeClass;
    friend class RuntimeTrack;
    friend class RuntimeStateMachine;
    friend class RuntimeTransition;

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    RuntimeState(const string& a_strName
        , reflection::InstanceMethod* a_pEnterMethod
        , reflection::InstanceMethod* a_pUpdateMethod
        , reflection::InstanceMethod* a_pLeaveMethod
        , bitfield modifiers = bitfield());
    o_destructor ~RuntimeState(void);

    void            setEnterSignal(reflection::Signal* a_pSignal) { m_pEnterSignal = a_pSignal; }
    void            setLeaveSignal(reflection::Signal* a_pSignal) { m_pLeaveSignal = a_pSignal; }

    reflection::Signal*            getEnterSignal() const { return m_pEnterSignal ; }
    reflection::Signal*            getLeaveSignal() const { return m_pLeaveSignal ; }
    
    void             activate(void* a_pObject)
    {
        //bool bPrev = a_pObject->testNativeFlags(Object::eNativeFlag_UpdatingStateMachine);
        //phantom::setObjectFlag(a_pObject, eNativeFlag_UpdatingStateMachine);
        static_cast<RuntimeTrack*>(m_pParentTrack)->transit(a_pObject, this);
        //phantom::unsetObjectFlag(a_pObject, eNativeFlag_UpdatingStateMachine);
    }
    void             enter(void* a_pObject)
    {
        if(m_pEnterSignal) m_pEnterSignal->invoke(a_pObject, o_no_arg);
        if(m_pEnterMethod) m_pEnterMethod->invoke(a_pObject, o_no_arg);
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<RuntimeTrack*>(pTrack)->enter(a_pObject);
        }
    }
    void             update(void* a_pObject)
    {
        if(m_pUpdateMethod) m_pUpdateMethod->invoke(a_pObject, o_no_arg);
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<RuntimeTrack*>(pTrack)->update(a_pObject);
        }
    }
    void             leave(void* a_pObject)
    {
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<RuntimeTrack*>(pTrack)->leave(a_pObject);
        }
        if(m_pLeaveMethod) m_pLeaveMethod->invoke(a_pObject, o_no_arg);
        if(m_pLeaveSignal) m_pLeaveSignal->invoke(a_pObject, o_no_arg);
    }
    
    RuntimeState*    handleEvent(void* a_pObject, Event* a_pEvent );

    virtual boolean    equals(Object* a_pObject) const; 

protected:
    reflection::InstanceMethod* m_pEnterMethod;
    reflection::InstanceMethod* m_pUpdateMethod;
    reflection::InstanceMethod* m_pLeaveMethod;
    reflection::Signal*            m_pEnterSignal;
    reflection::Signal*            m_pLeaveSignal;
};

o_h_end


#else // state_RuntimeState_h__
#include "RuntimeState.classdef.h"
#endif
