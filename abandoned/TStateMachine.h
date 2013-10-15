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

#ifndef util_TStateMachine_h__
#define util_TStateMachine_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

enum SMPhase
{
    eEnter,
    eUpdate,
    eLeave,
};



o_h_begin




template<typename _ObjectType, typename _EnumState, uint t_uiStateCount, typename _EnumEvent>
class TStateMachine
{
    enum EInternalState 
    {
        eInternalState_Initialized,
        eInternalState_Terminated,
    };

    
public:
    typedef _EnumState (_ObjectType::*state_function)(SMPhase,_EnumState);

    class StateFuncCollection 
    {
    public:
        StateFuncCollection()
        {
            memset(content, 0, sizeof(content));
        }
        boolean full() const
        {
            for(uint i = 0; i<t_uiStateCount; ++i)
            {
                if(content[i] == NULL) return false;
            }
            return true;
        }
        state_function&    operator[](_EnumState a_eState)
        {
            o_assert(a_eState < t_uiStateCount);
            return content[a_eState];
        }
    protected:
        state_function    content[t_uiStateCount];
    };

    class StateTransitionCollection 
    {
    protected:
        struct Ter
        {
            Ter(_EnumState    a_current,            _EnumEvent    a_event,            _EnumState    a_next) 
                : current(a_current), event(a_event), next(a_next){        }
            _EnumState    current;
            _EnumEvent    event;
            _EnumState    next;
        };
    public:
        StateTransitionCollection ()
        {
        }
        boolean full() const
        {
            for(uint i = 0; i<t_uiStateCount; ++i)
            {
                if(content[i] == NULL) return false;
            }
            return true;
        }

        _EnumState&    operator()(_EnumState a_eState, _EnumEvent a_eEvent) 
        {
            o_assert(a_eState < t_uiStateCount);
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

        _EnumState    operator()(_EnumState a_eState, _EnumEvent a_eEvent) const
        {
            o_assert(a_eState < t_uiStateCount);
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
    };


    

    TStateMachine() 
        : m_eInternalState(eInternalState_Terminated)        
        , m_eCurrentState((_EnumState)0)
        , m_pOwner(NULL)
    {

    }
    o_destructor ~TStateMachine(void)     {}

    void setOwner(_ObjectType* a_pOwner) { m_pOwner == a_pOwner; }

    state_function&    operator[](_EnumState a_eState)
    {
        return m_StateFuncs[a_eState];
    }

    _EnumState&    operator()(_EnumState a_eState, _EnumEvent a_eEvent)
    {
        return m_StateTransitions(a_eState, a_eEvent);
    }

    void        initialize(_EnumState a_eInitialState  )
    {
        o_assert(m_pOwner);
        o_assert(m_eInternalState == eInternalState_Terminated);
        o_assert(m_StateFuncs.full());
        m_eCurrentState = a_eInitialState;
        (m_pOwner->*m_StateFuncs[m_eCurrentState])(eEnter, m_eCurrentState);
        m_eInternalState = eInternalState_Initialized;
    }
    void    terminate()
    {
        o_assert(m_eInternalState == eInternalState_Initialized);
        (m_pOwner->*m_StateFuncs[m_eCurrentState])(eLeave, m_eCurrentState);
        m_eInternalState = eInternalState_Terminated;
    }

    void    postEvent(_EnumEvent a_eEvent)
    {
        m_EventQueue.push_back(a_eEvent);
    }

    void        update()
    {
        o_assert(m_eInternalState == eInternalState_Initialized);
        _EnumState transitionState = m_eCurrentState;
        while(!m_EventQueue.empty())
        {
            transitionState = m_StateTransitions(m_eCurrentState, m_EventQueue.front());
            m_EventQueue.pop_front();
        }
        if(transitionState != m_eCurrentState)
        {
            setCurrentState(transitionState);
        }
        _EnumState newState = (m_pOwner->*m_StateFuncs[m_eCurrentState])(eUpdate, m_eCurrentState);
        if(newState == m_eCurrentState) return;
        setCurrentState(newState);
    }
    void        setCurrentState(_EnumState a_eNewState)
    {
        if(a_eNewState == m_eCurrentState) return;
        _EnumState    eOldState = m_eCurrentState;
        (m_pOwner->*m_StateFuncs[eOldState])(eLeave, a_eNewState);
        m_eCurrentState = a_eNewState;
        (m_pOwner->*m_StateFuncs[a_eNewState])(eEnter, eOldState);

    }

    _EnumState        getCurrentState() const { o_assert(m_eInternalState == eInternalState_Initialized); return m_eCurrentState; }

    boolean            hasReactionTo(_EnumEvent event) const { return m_StateTransitions(m_eCurrentState, event) != m_eCurrentState; }

protected:
    _ObjectType*            m_pOwner;
    EInternalState            m_eInternalState;
    _EnumState                m_eCurrentState;
    StateFuncCollection        m_StateFuncs;    
    StateTransitionCollection m_StateTransitions;
    std::list<_EnumEvent>    m_EventQueue;
    
};

o_h_end


#endif //utils_TStateMachine