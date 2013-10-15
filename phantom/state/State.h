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

#ifndef state_State_h__
#define state_State_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "State.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin


class o_export State : public StateMachineElement
{
    friend class Track;
    friend class StateMachine;

protected:
    typedef vector<Track*>                track_vector;
    
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    State(const string& a_strName, bitfield modifiers = bitfield());
    o_destructor ~State(void);

    void            addTrack(Track* a_pTrack);
    void            removeTrack(Track* a_pTrack);
    void            replaceTrack( Track* a_pOld, Track* a_pNew );

    Track*          getTrack(const string& a_strName) const;
    inline Track*   getTrack(uint a_uiIndex) const    { return m_Tracks[a_uiIndex]; }
    inline Track*   getParentTrack() const            { return m_pParentTrack;    }
    inline int      getParentTrackIndex() const            { return m_pParentTrack ? m_pParentTrack->getIndex() : -1; }
    inline size_t   getIndexInTrack() const { return m_uiIndexInTrack; }
    inline size_t   getIndex() const { return m_uiIndex; }
    inline size_t   getTrackCount(void) const        { return m_Tracks.size(); }
    inline uint     getKey() const { return m_uiKey; }

    virtual boolean equals(Object* a_pObject) const;

    boolean         isEmpty() const { return m_Tracks.empty(); }

    Track*          getTrackCascade(const string& a_strName) const;

    uint            getOrderingFactor() const {return m_uiOrderingFactor;}

    int             getLevel() const 
    {
        return m_pParentTrack 
                    ? m_pParentTrack->getLevel() + 1 
                    : 0;
    }

    virtual generic_member_func_ptr   getEnterGenericMemberFunctionPointer() const = 0;
    virtual generic_member_func_ptr   getUpdateGenericMemberFunctionPointer() const = 0;
    virtual generic_member_func_ptr   getLeaveGenericMemberFunctionPointer() const = 0;

protected:
    State(const string& a_strName, uint a_uiOrderingFactor, bitfield modifiers = bitfield());
    
    void            setOrderingFactor(uint a_uiOrderingFactor)
    {
        m_uiOrderingFactor = a_uiOrderingFactor;
    }

protected:
    Track*              m_pParentTrack;
    track_vector        m_Tracks;
    uint                m_uiOrderingFactor;
    uint                m_uiKey;
    size_t              m_uiIndexInTrack;
    size_t              m_uiIndex;
};

o_h_end

/*

o_begin_phantom_namespace

template<>
class serializer<state::State>
{
    static void serialize(state::State const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
    {
        *reinterpret_cast<uint*>(a_pOutBuffer) = a_pInstance->getParentTrack()->getIndex();
        a_pOutBuffer += sizeof(uint);
    }
    static void deserialize(state::State* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) 
    {
        uint uiIndex = *reinterpret_cast<uint*>(a_pInBuffer);
         = a_pInstance->getParentTrack()->getIndex();

    }
    static void serialize(state::State const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) {}
    static void deserialize(state::State* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) {}
    
};

o_end_phantom_namespace

*/



#else // state_State_h__
#include "State.classdef.h"
#endif
