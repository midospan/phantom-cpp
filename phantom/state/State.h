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

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, state)

struct state_compilation_data
{
    state_compilation_data() 
        : m_pEnterMemberFunction(0)
        , m_pUpdateMemberFunction(0)
        , m_pLeaveMemberFunction(0)
        , m_pEnterClosure(0)
        , m_pUpdateClosure(0)
        , m_pLeaveClosure(0)
        , m_bCompiled(0)
    {

    }
    reflection::closure_call_delegate   m_ClosureCallDelegate;
    reflection::InstanceMemberFunction* m_pEnterMemberFunction;
    reflection::InstanceMemberFunction* m_pUpdateMemberFunction;
    reflection::InstanceMemberFunction* m_pLeaveMemberFunction;
    void*                               m_pEnterClosure;
    void*                               m_pUpdateClosure;
    void*                               m_pLeaveClosure;
    bool                                m_bCompiled;
};

class o_export State : public StateMachineElement
{
    o_language_element;

    friend class Track;
    friend class StateMachine;

protected:
    typedef vector<Track*>                track_vector;

public:
    static reflection::Class* const metaType;

public:
    State(const string& a_strName, modifiers_t modifiers = 0);
    o_destructor ~State(void);

    virtual State* asState() const { return (State*)this; }

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

    virtual bool    equals(reflection::LanguageElement* a_pObject) const;

    boolean         isEmpty() const { return m_Tracks.empty(); }

    Track*          getTrackCascade(const string& a_strName) const;

    uint            getOrderingFactor() const {return m_uiOrderingFactor;}

    int             getLevel() const 
    {
        return m_pParentTrack 
                    ? m_pParentTrack->getLevel() + 1 
                    : 0;
    }

    void copyHierarchy(StateMachine* a_pStateMachine, State* a_pSourceState);

    reflection::InstanceMemberFunction* getEnterMemberFunction(void) const 
    { 
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pEnterMemberFunction; 
    }
    reflection::InstanceMemberFunction* getUpdateMemberFunction(void) const 
    { 
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pUpdateMemberFunction; 
    }
    reflection::InstanceMemberFunction* getLeaveMemberFunction(void) const 
    { 
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pLeaveMemberFunction; 
    }

    reflection::InstanceMemberFunction* createEnterMemberFunction(void);
    reflection::InstanceMemberFunction* createUpdateMemberFunction(void);
    reflection::InstanceMemberFunction* createLeaveMemberFunction(void);

    void setEnterClosure(void* a_pClosure)
    {
        o_assert(m_pCompilationData);
        m_pCompilationData->m_pEnterClosure = a_pClosure;
    }

    void setLeaveClosure(void* a_pClosure)
    {
        o_assert(m_pCompilationData);
        m_pCompilationData->m_pLeaveClosure = a_pClosure;
    }

    void setUpdateClosure(void* a_pClosure)
    {
        o_assert(m_pCompilationData);
        m_pCompilationData->m_pUpdateClosure = a_pClosure;
    }

    virtual void*   getEnterClosure() const 
    {
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pEnterClosure;
    }

    virtual void*   getUpdateClosure() const 
    {
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pUpdateClosure;
    }

    virtual void*   getLeaveClosure() const 
    {
        o_assert(m_pCompilationData);
        return m_pCompilationData->m_pLeaveClosure;
    }

    void enter( dynamic_state_machine_data* smdataptr );
    void update( dynamic_state_machine_data* smdataptr );
    void leave( dynamic_state_machine_data* smdataptr );

protected:
    State(const string& a_strName, uint a_uiOrderingFactor, modifiers_t modifiers = 0);
    
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
    state_compilation_data* m_pCompilationData;
};

o_namespace_end(phantom, state)

#endif
