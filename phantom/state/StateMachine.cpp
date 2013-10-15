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
/* ** The Class Header must be the last #include * */
#include "StateMachine.h"
/* *********************************************** */

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

StateMachine::StateMachine( bitfield a_Modifiers )
: LanguageElement("", a_Modifiers)
, m_uiTrackCount(0) 
{
}

StateMachine::~StateMachine( void )
{
    if(m_Tracks.size())
    {
        // Delete all the tracks recursively starting from the root one
        o_dynamic_delete m_Tracks[0];
    }
}

uint StateMachine::addEvent( const string& name )
{
    o_assert(getEventId(name) == 0xffffffff, "An event with the same name already exists");
    uint id = m_EventNames.size();
    m_EventNames.push_back(name);
    m_EventIds[name] = id;
    return id;
}

const string& StateMachine::getEventName( uint a_uiId ) const
{
    return m_EventNames[a_uiId];
}

void StateMachine::setRootTrack( Track* a_pRootTrack )
{
    o_assert(m_Tracks.empty());
    registerTrack(a_pRootTrack);
    a_pRootTrack->getTrackCountCascade(m_uiTrackCount);
}

Track* StateMachine::getTrack( const string& a_strName ) const
{
    o_foreach(Track* pTrack, m_Tracks)
    {
        if(pTrack->getName() == a_strName) return pTrack;
    }
    return NULL;
}

State* StateMachine::getState( const string& a_strName ) const
{
    o_foreach(State* pState, m_States)
    {
        if(pState->getName() == a_strName) return pState;
    }
    return NULL;
}

uint StateMachine::getEventId( const string& a_strName ) const
{
    auto found = m_EventIds.find(a_strName);
    if(found != m_EventIds.end()) return found->second;
    return 0xffffffff;
}

reflection::Signature* StateMachine::StateMethodSignature()
{
    static reflection::Signature*    s_Value = NULL;
    if(s_Value == NULL)
    {
        s_Value = o_new(reflection::Signature)();
        s_Value->parse(o_CS("void()"));
        phantom::registerSingleton(s_Value);
        s_Value->setShared();
    }
    return s_Value;
}

void StateMachine::registerTrack( Track* a_pTrack )
{
    o_assert(getTrack(a_pTrack->getName()) == NULL);
    a_pTrack->setOwnerStateMachine(this);
    a_pTrack->m_uiIndex = m_Tracks.size();
    m_Tracks.push_back(a_pTrack);
}

void StateMachine::registerState( State* a_pState )
{
    o_assert(getState(a_pState->getName()) == NULL);
    a_pState->setOwnerStateMachine(this);
    a_pState->m_uiIndex = m_States.size();
    m_States.push_back(a_pState);
}

void StateMachine::postRandomEvent( void* a_pObject, vector<uint>* eventIds /*= nullptr*/ )
{
    float randRatio = ((float)(rand())) / RAND_MAX ;
    if(randRatio == 1.f) 
        randRatio = 0.999f;
    if(eventIds)
    {
        float r = eventIds->size() * randRatio;
        uint id = (*eventIds)[(uint)r];
        o_assert(id < m_EventIds.size());
        postEvent(a_pObject, id);
    }
    else 
    {
        float r = m_EventIds.size() * randRatio;
        postEvent(a_pObject, (uint)r);
    }
}

o_cpp_end
