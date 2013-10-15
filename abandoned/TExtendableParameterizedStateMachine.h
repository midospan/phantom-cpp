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

#ifndef util_TExtendableParameterizedStateMachine_h__
#define util_TExtendableParameterizedStateMachine_h__



/* ****************** Includes ******************* */
#include <phantom/util/TNativeStateMachine.h>
/* **************** Declarations ***************** */

/* *********************************************** */




o_h_begin


template<typename _ObjectType, typename _Parameter>

class TExtendableParameterizedStateMachine
{
    enum EInternalState 
    {
        eInternalState_Initialized,
        eInternalState_Updating,
        eInternalState_Terminated,
    };

    typedef TExtendableParameterizedStateMachine<_ObjectType,_Parameter> current_type;


public:
    typedef uint (_ObjectType::*state_function)(SMPhase,uint,_Parameter);

    class StateFuncCollection 
    {
    public:
        StateFuncCollection()
        {

        }
        uint size() const { return content.size(); }
        void    ensureSize(uint count)
        {
            while(content.size() < count)
                content.push_back(NULL);
        }
        void    add(state_function func) { content.push_back(func); }

        state_function&    operator[](uint a_eState)
        {
            o_assert(a_eState < content.size());
            return content[a_eState];
        }
    protected:
        std::vector<state_function>    content;
    };

    class StateTransitionCollection 
    {
    protected:
        struct Ter
        {
            Ter(uint    a_current,            uint    a_event,            uint    a_next) 
                : current(a_current), event(a_event), next(a_next){        }
            uint    current;
            uint    event;
            uint    next;
        };
    public:
        StateTransitionCollection (current_type* sm)
            : m_pSm(sm)
        {
        }
        
        uint&    operator()(uint a_eState, uint a_eEvent) 
        {
            o_assert(a_eState < m_pSm->stateCount());
            uint count = content.size();
            for(uint i=0;i<count; ++i)
            {
                if(content[i].current == a_eState AND content[i].event == a_eEvent)
                {
                    return content[i].next;
                }
            }
            content.push_back(Ter(a_eState, a_eEvent, a_eState));
            return content[content.size()-1].next;
        }

        uint    operator()(uint a_eState, uint a_eEvent) const
        {
            o_assert(a_eState < m_pSm->stateCount());
            uint count = content.size();
            for(uint i=0;i<count; ++i)
            {
                if(content[i].current == a_eState AND content[i].event == a_eEvent)
                {
                    return content[i].next;
                }
            }
            return a_eState;
        }
    protected:
        std::vector<Ter> content;
        current_type*    m_pSm;
    };




    TExtendableParameterizedStateMachine() 
        : m_eInternalState(eInternalState_Terminated)    
        , m_pOwner(NULL)
        , m_eCurrentState((uint)0)
        , m_StateTransitions(getThis())
    {
    }

    current_type*    getThis() const { return const_cast<current_type*>(this); }

    void setOwner(_ObjectType* a_pOwner) { m_pOwner = a_pOwner; }

    ~TExtendableParameterizedStateMachine(void)     
    {
    }

    uint stateCount() const {  return m_StateFuncs.size(); }

    state_function&    operator[](uint a_eState)
    {
        return m_StateFuncs[a_eState];
    }

    uint&    operator()(uint a_eState, uint a_eEvent)
    {
        return m_StateTransitions(a_eState, a_eEvent);
    }

    void        initialize(uint a_eInitialState, _Parameter _param = _Parameter() )
    {
        o_assert(m_eInternalState == eInternalState_Terminated);
        m_eCurrentState = a_eInitialState;
        (m_pOwner->*m_StateFuncs[m_eCurrentState])(eEnter, m_eCurrentState, _param);
        m_eInternalState = eInternalState_Initialized;
    }
    void    terminate(_Parameter _param = _Parameter())
    {
        o_assert(m_eInternalState == eInternalState_Initialized);
        (m_pOwner->*m_StateFuncs[m_eCurrentState])(eLeave, m_eCurrentState, _param);
        m_eInternalState = eInternalState_Terminated;
    }

    void    ensureStateCount(uint count)
    {
        m_StateFuncs.ensureSize(count);
    }

    void    postEvent(uint a_eEvent)
    {
        if(m_eInternalState != eInternalState_Updating)
        {
            treatEvent(a_eEvent, _Parameter());
        }
        else
        {
            m_EventQueue.push_back(a_eEvent);
        }
    }

protected:
    void    treatEvent(uint a_eEvent, _Parameter _parameter)
    {
        uint transitionState = m_eCurrentState;
        while(!m_EventQueue.empty())
        {
            transitionState = m_StateTransitions(m_eCurrentState, m_EventQueue.front());
            m_EventQueue.pop_front();
        }
        if(transitionState != m_eCurrentState)
        {
            setCurrentState(transitionState, _parameter);
        }
    }

public:
    void        update(_Parameter _parameter)
    {
        o_assert(m_eInternalState == eInternalState_Initialized);
        m_eInternalState = eInternalState_Updating;
        uint transitionState = m_eCurrentState;
        while(!m_EventQueue.empty())
        {
            transitionState = m_StateTransitions(m_eCurrentState, m_EventQueue.front());
            m_EventQueue.pop_front();
        }
        if(transitionState != m_eCurrentState)
        {
            setCurrentState(transitionState, _parameter);
        }
        uint newState = (m_pOwner->*m_StateFuncs[m_eCurrentState])(eUpdate, m_eCurrentState, _parameter);
        if(newState != m_eCurrentState) 
        {
            setCurrentState(newState, _parameter);
        }
        m_eInternalState = eInternalState_Initialized;
    }
    void        setCurrentState(uint a_eNewState, _Parameter _parameter)
    {
        if(a_eNewState == m_eCurrentState) return;
        uint    eOldState = m_eCurrentState;
        (m_pOwner->*m_StateFuncs[eOldState])(eLeave, a_eNewState, _parameter);
        m_eCurrentState = a_eNewState;
        (m_pOwner->*m_StateFuncs[a_eNewState])(eEnter, eOldState, _parameter);

    }

    uint        getCurrentState() const { o_assert(m_eInternalState == eInternalState_Initialized); return m_eCurrentState; }

    boolean            hasReactionTo(uint event) const { return m_StateTransitions(m_eCurrentState, event) != m_eCurrentState; }

protected:
    _ObjectType*                m_pOwner;
    EInternalState                m_eInternalState;
    uint                        m_eCurrentState;
    StateFuncCollection            m_StateFuncs;    
    StateTransitionCollection    m_StateTransitions;
    std::list<uint>                m_EventQueue;

};

o_h_end


#endif //utils_TExtendableParameterizedStateMachine