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

#ifndef state_TTrack_h__
#define state_TTrack_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, state, native)

template <typename _TrackClass>
class native_track_registrer
{
public:
    native_track_registrer()
    {
        _TrackClass::Instance();
    }
};

template<typename t_ObjectClass, bool t_has_statechart>
class root_state_chart_helper
{
public:
    class Root
    {

    };
};

template<typename t_ObjectClass>
class root_state_chart_helper<t_ObjectClass, true>
{ 
    o_compiler_specific_friend phantom::detail::template_arg_friend_helper<t_ObjectClass>::type; 
    typedef void root_statechart_marker;

protected: 
    o_forceinline 
    root_state_chart_helper()            {} 

public:
    class Root 
    {
        friend class phantom::state::native::native_track_registrer<Root>;
        friend class phantom::state::native::TNativeTrack<t_ObjectClass>;
        Root() {}

    public: 
        typedef phantom::state::native::TNativeTrack<t_ObjectClass> placeholder_type;
        
        static placeholder_type* Instance()
        {
            static placeholder_type*    s_Instance = NULL;
            if(s_Instance == NULL)
            {
                s_Instance = o_new(placeholder_type)(o_CS("Root"), 0, 0);
                TNativeStateMachine<t_ObjectClass>::Instance()->setRootTrack(s_Instance);
            }
            return s_Instance;
        }
    private:
        static const character*        RESERVED_getRoot() { return o_CS("Root"); }
    };

    typedef Root Root;
protected:
    phantom::state::native::native_track_registrer<Root> RESERVED_Root_registrer;
};


template<typename t_ObjectClass>
class root_statechart 
    : public root_state_chart_helper<t_ObjectClass, phantom::has_statechart_cascade<t_ObjectClass>::value>
{
public:
    o_forceinline root_statechart() {} 
    o_forceinline root_statechart(uint i)    {}
};


#define TNativeTrack_smdataptr(_object_) \
    ((phantom::state::native::state_machine_data<t_ObjectClass>*)(static_cast<root_object_class*>(static_cast<t_ObjectClass*>(_object_))->PHANTOM_CODEGEN_m_smdataptr))

/*

template <typename t_ObjectClass, bool t_has_statechart>
class TNativeTrackHelper;
template <typename t_ObjectClass>
class TNativeTrackHelper <t_ObjectClass, false> : public Track
{
public:    
    typedef TNativeState<t_ObjectClass>                    state_class;
    typedef TNativeTrackHelper<t_ObjectClass, false>    self_type;
    typedef t_ObjectClass                                object_class;
    typedef TNativeStateMachine<t_ObjectClass>            statemachine_class;

    friend class State;
    friend class TNativeStateMachine<t_ObjectClass>;

    TNativeTrackHelper( const string& a_strName
        , bitfield bf = 0 )
        : Track(a_strName
        , statemachine_class::NextTrackIndex()
        , bf)
    {

    }
    TNativeTrackHelper( const string& a_strName
        , uint a_iIndex
        , bitfield bf = 0 )
        : Track(a_strName
        , a_iIndex
        , bf)
    {

    }

    o_static_assert(sizeof(t_ObjectClass) == 0);
    o_destructor ~TNativeTrackHelper(void)     {}

    phantom::state::State * getCurrentState(void *) const { o_exception(exception::reflection_runtime_exception, "class doesn't have an user defined state machine"); return NULL; }
    phantom::state::State * getTransitState(void *) const { o_exception(exception::reflection_runtime_exception, "class doesn't have an user defined state machine"); return NULL; }
    phantom::boolean        isActive(void *) const { o_exception(exception::reflection_runtime_exception, "class doesn't have an user defined state machine"); return false; }
    void                    setCurrentState(void *,phantom::state::State *) const { o_exception(exception::reflection_runtime_exception, "class doesn't have an user defined state machine"); }
    void                    setTransitState(void *,phantom::state::State *) const { o_exception(exception::reflection_runtime_exception, "class doesn't have an user defined state machine"); }
};*/



template <typename t_ObjectClass>
class TNativeTrack : public Track
{
public:    
    typedef TNativeState<t_ObjectClass>         state_class;
    typedef TNativeTrack<t_ObjectClass>         self_type;
    typedef t_ObjectClass                       object_class;
    typedef TNativeStateMachine<t_ObjectClass>    statemachine_class;
    typedef o_NESTED_TYPE first_super_statechart_class_of<t_ObjectClass>::type        root_object_class;
    typedef phantom::state::native::state_machine_data<t_ObjectClass> instance_data;

    friend class State;
    friend class TNativeStateMachine<t_ObjectClass>;

    TNativeTrack( const string& a_strName
        , bitfield bf )
            : Track(a_strName
            , bf)
    {

    }
    TNativeTrack( const string& a_strName
        , int a_iIndex
        , bitfield bf )
        : Track(a_strName
        , a_iIndex
        , bf)
    {

    }
    o_destructor ~TNativeTrack(void)     {}

    o_forceinline State*    parent_state() const { return static_cast<State*>(m_pParentState); }

    void transit(instance_data* smdataptr, state_class* a_pNextState)
    {
        object_class* pObject = (object_class*)smdataptr->owner;
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        state_class*& rpTransitState = smdataptr->transit_states[m_uiIndex]; 
        if(rpCurrentState == NULL) /// Track isn't active
        {
            if(m_pParentState) /// if it's not the root track
            {
                rpTransitState = a_pNextState;
                static_cast<self_type*>(
                    static_cast<state_class*>(m_pParentState)->m_pParentTrack
                )->transit(smdataptr, static_cast<state_class*>(m_pParentState));
            }
            else /// the root track
            {
                rpTransitState = NULL;
                rpCurrentState = a_pNextState;
                smdataptr->lock();
                a_pNextState->enter(smdataptr);
                smdataptr->unlock();
            }
        }
        else if (rpCurrentState != a_pNextState)
        {
            state_class* pPreviousState = rpCurrentState;
            rpTransitState = NULL;
            State*& rpHistoryState = smdataptr->history_state;
            rpHistoryState = a_pNextState;
            smdataptr->lock();
            rpHistoryState = a_pNextState;
            pPreviousState->leave(smdataptr);
            rpCurrentState = a_pNextState;
            rpHistoryState = pPreviousState;
            a_pNextState->enter(smdataptr);
            smdataptr->unlock();
        }
    }

    virtual boolean isActive(void* a_pObject) const
    {
        return TNativeTrack_smdataptr(static_cast<object_class*>(a_pObject))->current_states[m_uiIndex] != NULL;
    }

    inline void enter(instance_data* smdataptr)
    {
        o_Track_TraceEnter();
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        state_class* pTransitState = smdataptr->transit_states[m_uiIndex];
        o_assert(rpCurrentState == NULL) ;
        if(pTransitState == NULL)
        {
            pTransitState = static_cast<state_class*>(m_States[0]);
        }
        else
        {
            smdataptr->transit_states[m_uiIndex] = NULL;
        }
        rpCurrentState = pTransitState;
        smdataptr->lock();
        pTransitState->enter(smdataptr);
        smdataptr->unlock();
    }

    inline void update(instance_data* smdataptr)
    {
        smdataptr->current_states[m_uiIndex]->update(smdataptr);
    }

    inline void leave(instance_data* smdataptr)
    {
        o_Track_TraceLeave();
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        smdataptr->lock();
        rpCurrentState->leave(smdataptr);
        smdataptr->unlock();
        rpCurrentState = NULL;
    }

};

#undef TNativeTrack_smdataptr

o_namespace_end(phantom, state, native)

    o_traits_specialize_all_super_traitNTTS(
    (phantom,state,native)
    , (typename)
    , (t_Ty)
    , TNativeTrack
    , (Track)
    )

#endif
