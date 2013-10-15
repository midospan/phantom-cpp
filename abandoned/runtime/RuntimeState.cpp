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
#include <phantom/state/runtime/RuntimeState.h>
/* *********************************************** */

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

RuntimeState::RuntimeState( const string& a_strName 
, reflection::InstanceMethod* a_pEnterMethod
, reflection::InstanceMethod* a_pUpdateMethod
, reflection::InstanceMethod* a_pLeaveMethod
, bitfield modifiers /*= bitfield()*/) 
    : State(a_strName, modifiers)
    , m_pEnterMethod(a_pEnterMethod)
    , m_pUpdateMethod(a_pUpdateMethod)
    , m_pLeaveMethod(a_pLeaveMethod)
    , m_pEnterSignal(NULL)
    , m_pLeaveSignal(NULL)
{

}

RuntimeState::~RuntimeState( void )
{
}

boolean RuntimeState::equals( Object* a_pObject ) const
{
    if(a_pObject == this) return true;
    if(NOT(is<RuntimeState>(a_pObject))) return false;
    if(static_cast<RuntimeState*>(a_pObject)->getName() != getName()) return false;
    reflection::Class* pThisOwner = getOwnerStateMachine()->getOwnerClass();
    reflection::Class* pOtherOwner = static_cast<RuntimeState*>(a_pObject)->getOwnerStateMachine()->getOwnerClass();
    reflection::Type::ERelation relation = pOtherOwner->getRelationWith(pThisOwner);
    return relation == reflection::Type::eRelation_Equal
        OR relation == reflection::Type::eRelation_Child
        OR relation == reflection::Type::eRelation_Parent;
}

RuntimeState* RuntimeState::handleEvent( void* a_pObject, Event* a_pEvent )
{
    {
        EventReactionMap::iterator it;
        if((it = m_EventReactions.find(a_pEvent->getId())) != m_EventReactions.end())
        {
            it->second->react(a_pObject, a_pEvent);
            return this;
        }
    }
    {
        o_foreach(Track* pTrack, m_Tracks)
        {
            State* pHandler = static_cast<RuntimeTrack*>(pTrack)->handleEvent(a_pObject, a_pEvent);
            if(pHandler)
            {
                return static_cast<RuntimeState*>(pHandler);
            }
        }
    }
    return NULL;
}

o_cpp_end
