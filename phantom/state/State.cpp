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
#include <phantom/state/State.h>
#include <phantom/state/State.hxx>
/* *********************************************** */
o_registerN((phantom, state), State);

o_namespace_begin(phantom, state) 

reflection::Class* const State::metaType = o_type_of(phantom::state::State);

State::State( const string& a_strName , bitfield modifiers /*= 0*/) 
    : StateMachineElement(a_strName, modifiers)
    , m_pParentTrack(NULL)
    , m_uiKey(0xffffffff)
    , m_uiIndexInTrack(0xffffffff)
    , m_uiIndex(0xffffffff)
{

}

State::State(const string& a_strName, uint a_uiOrderingFactor, bitfield modifiers /*= 0*/)
    : StateMachineElement(a_strName, modifiers)
    , m_pParentTrack(NULL)
    , m_uiOrderingFactor(a_uiOrderingFactor)
, m_uiKey(0xffffffff)
, m_uiIndex(0xffffffff)
{

}

State::~State( void )
{
}

void State::addTrack( Track* a_pTrack )
{
    o_assert(getOwnerStateMachine(), "a State must be attached to a track attached itself to a StateMachine to receive child tracks");
    m_Tracks.push_back(a_pTrack);
    a_pTrack->setParentState(this);
    getOwnerStateMachine()->registerTrack(a_pTrack);
}

void State::removeTrack( Track* a_pTrack )
{
    track_vector::iterator it = m_Tracks.begin();
    for(;it != m_Tracks.end(); ++it)
    {
        if((*it) == a_pTrack) break;
    }
    if(it != m_Tracks.end())
    {
        m_Tracks.erase(it);
    }
    a_pTrack->m_pParentState = NULL;
}


void State::replaceTrack( Track* a_pOld, Track* a_pNew )
{
    track_vector::iterator it = m_Tracks.begin();
    for(;it != m_Tracks.end(); ++it)
    {
        if((*it) == a_pOld) break;
    }
    o_assert(it != m_Tracks.end());
    *it = a_pNew;
    a_pOld->m_pParentState = NULL;
    a_pNew->m_pParentState = this;
}

Track* State::getTrack( const string& a_strName ) const
{
    track_vector::const_iterator it = m_Tracks.begin();
    for( ; it != m_Tracks.end();++it)
    {
        if((*it)->getName() == a_strName) return *it;
    }
    return NULL;
}

bool State::equals( reflection::LanguageElement* a_pOther ) const
{
    if(a_pOther == this) return true;
    if(NOT(is<State>(a_pOther))) return false;
    if(static_cast<State*>(a_pOther)->getName() != getName()) return false;
    reflection::Class* pThisOwner = getOwnerStateMachine()->getOwnerClass();
    reflection::Class* pOtherOwner = static_cast<State*>(a_pOther)->getOwnerStateMachine()->getOwnerClass();
    reflection::Type::ERelation relation = pOtherOwner->getRelationWith(pThisOwner);
    return relation == reflection::Type::eRelation_Equal
        OR relation == reflection::Type::eRelation_Child
        OR relation == reflection::Type::eRelation_Parent;
}

Track* State::getTrackCascade( const string& a_strName ) const
{
    o_foreach(Track* pTrack, m_Tracks)
    {
        if(pTrack->getName() == a_strName)
        {
            return pTrack;
        }
        o_foreach(State* pState, pTrack->m_States)
        {
            Track* pTrack = pState->getTrackCascade(a_strName);
            if(pTrack) return pTrack;
        }
    }
    return NULL;
}

o_namespace_end(phantom, state)
